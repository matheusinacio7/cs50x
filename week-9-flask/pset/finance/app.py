import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    user_id = session.get("user_id")
    user = db.execute("SELECT * FROM users WHERE id = ?", user_id)[0]
    stocks = []
    total_value = 0
    user_stocks = db.execute("SELECT * FROM shares WHERE user_id = ?", user_id)

    if not len(user_stocks):
        return render_template("index.html", total_value=total_value, stocks=stocks, cash=user["cash"])

    for user_stock in user_stocks:
        stock = {}
        quote = lookup(user_stock["stock"])
        if quote is None:
            continue
        stock["symbol"] = user_stock["stock"]
        stock["shares"] = int(user_stock["amount"])
        stock["price"] = float(quote["price"])
        total_value += stock["price"] * stock["shares"]
        stocks.append(stock)

    return render_template("index.html", total_value=total_value, stocks=stocks, cash=user["cash"])


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")
    else:
        user_id = session.get("user_id")
        stock_symbol = request.form.get("symbol")
        amount = int(request.form.get("shares"))
        if amount < 1:
            return apology("You must buy at least one share", 400)
        quoted = lookup(stock_symbol)
        if quoted is None:
            return apology("Could not find that stock", 404)

        price = float(quoted["price"])
        user = db.execute("SELECT * FROM users WHERE id = ?", user_id)[0]
        user_cash = int(user["cash"])
        total_cost = price * amount
        if total_cost > user_cash:
            return apology("You dont have enough cash to buy that much stock", 400)
        user_new_cash = user_cash - total_cost

        db.execute("UPDATE users SET cash = ? WHERE id = ?", user_new_cash, user_id)
        db.execute("INSERT INTO transactions (user_id, transaction_type, stock, amount, price_per) VALUES (?, ?, ?, ?, ?)", user_id, "BUY", quoted["symbol"], amount, price)
        user_shares = db.execute("SELECT * FROM shares WHERE user_id = ? AND stock = ?", user_id, quoted["symbol"])
        if user_shares:
            db.execute("UPDATE shares SET amount = ? WHERE user_id = ? AND stock = ?", user_shares[0]["amount"] + amount, user_id, stock_symbol)
        else:
            db.execute("INSERT INTO SHARES (user_id, stock, amount) VALUES (?, ?, ?)", user_id, stock_symbol, amount)
        return redirect("/")


@app.route("/history")
@login_required
def history():
    user_id = session.get("user_id")
    user_transactions = db.execute("SELECT * FROM transactions WHERE user_id = ?", user_id)
    for i in range(len(user_transactions)):
        user_transactions[i]["amount"] = int(user_transactions[i]["amount"])
        user_transactions[i]["price_per"] = float(user_transactions[i]["price_per"])
    return render_template("history.html", transactions=user_transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        quoted = lookup(symbol)
        if quoted is None:
            return apology("no stock with that symbol", 400)
        return render_template("quoted.html", quoted=quoted)


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")
    else:
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not all([confirmation, username, password, confirmation == password]):
            return apology("invalid username and/or password", 400)

        hashed_password = generate_password_hash(password)

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hashed_password)
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    user_id = session.get("user_id")
    user_shares = db.execute("SELECT * FROM shares WHERE user_id = ?", user_id)
    if request.method == "GET":
        return render_template("sell.html", shares=user_shares)
    else:
        amount = int(request.form.get("shares"))
        symbol = request.form.get("symbol")

        user_stock = next((s for s in user_shares if s["stock"] == symbol), [None])
        if not user_stock:
            return apology("You dont have shares of that stock to sell", 403)
        
        if any([not amount, amount > user_stock["amount"]]):
            return apology("You don't have that many shares to sell", 403)

        quoted = lookup(symbol)
        if quoted is None:
            return apology("Could not find that stock", 404)

        price = float(quoted["price"])
        user = db.execute("SELECT * FROM users WHERE id = ?", user_id)[0]
        user_cash = int(user["cash"])
        total_price = price * amount
        user_new_cash = user_cash + total_price
        db.execute("UPDATE users SET cash = ? WHERE id = ?", user_new_cash, user_id)
        db.execute("INSERT INTO transactions (user_id, transaction_type, stock, amount, price_per) VALUES (?, ?, ?, ?, ?)", user_id, "SELL", quoted["symbol"], amount, price)

        if amount == user_stock["amount"]:
            db.execute("DELETE FROM SHARES WHERE user_id = ? AND stock = ?", user_id, symbol)
        else:
            db.execute("UPDATE shares SET amount = ? WHERE user_id = ? AND stock = ?", user_stock["amount"] - amount, user_id, symbol)

        return redirect("/")


@app.route("/deposit", methods=["GET", "POST"])
@login_required
def deposit():
    if request.method == "GET":
        return render_template("deposit.html")
    else:
        user_id = session.get("user_id")
        amount = float(request.form.get("amount"))

        if not amount or amount < 500:
            return apology("you must deposit at least 500 USD", 400)

        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", amount, user_id)
        return redirect("/")
