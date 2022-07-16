-- Active: 1657258549497@@127.0.0.1@3306
CREATE TABLE transactions (
  id INTEGER PRIMARY KEY,
  user_id INTEGER NOT NULL,
  transaction_type TEXT NOT NULL,
  stock TEXT NOT NULL,
  amount INTEGER NOT NULL,
  price_per REAL NOT NULL,
  timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
  FOREIGN KEY (user_id)
    REFERENCES users (id)
      ON DELETE CASCADE
      ON UPDATE NO ACTION
);

CREATE INDEX user_index ON transactions (user_id);
CREATE INDEX timestamp_index ON transactions(timestamp);
