SELECT trs.month, trs.day, trs.atm_location, trs.transaction_type, trs.amount, p.name
  FROM atm_transactions AS trs
  JOIN bank_accounts AS acc
    ON acc.account_number = trs.account_number
  JOIN people AS p
    ON p.id = acc.person_id
 WHERE p.id IN (250277, 864400);