-- Active: 1657258549497@@127.0.0.1@3306
-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Understand table structure
.schema;

-- See crime scene reports from the street on that day
SELECT *
  FROM crime_scene_reports
 WHERE year >= 2021
   AND month = 7
   AND day IN (28, 29, 30, 31)
   AND street = 'Humphrey Street';

-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

-- Check the security logs
SELECT *
  FROM bakery_security_logs
 WHERE year = 2021
   AND month = 7
   AND day = 28;

-- Will see all plates that entered before 10:15am and exited after

SELECT ent.hour, ent.minute, ent.activity, ext.hour, ext.minute, ext.activity, ent.license_plate
  FROM
      (SELECT *
         FROM bakery_security_logs
        WHERE year = 2021
          AND month = 7
          AND day = 28
          AND ((hour < 10) OR (hour = 10 AND minute < 15))
          AND activity = 'entrance') AS ent
      INNER JOIN
          (SELECT *
             FROM bakery_security_logs
            WHERE year = 2021
              AND month = 7
              AND day = 28
              AND ((hour > 10) OR (hour = 10 AND minute > 15))
              AND activity = 'exit') AS ext
        ON ent.license_plate = ext.license_plate
  ORDER BY ext.minute ASC;

-- Suspects:
-- 10|14|entrance|17|15|exit|13FNH73
-- 9|15|entrance|10|16|exit|5P2BI95 *****
-- 8|23|entrance|10|18|exit|94KL13X ****
-- 9|20|entrance|10|18|exit|6P58WS2 ****
-- 10|8|entrance|17|18|exit|R3G7486
-- 9|14|entrance|10|19|exit|4328GD8 ***
-- 9|28|entrance|10|20|exit|G412CB7 **
-- 8|18|entrance|10|21|exit|L93JTIZ **
-- 8|36|entrance|10|23|exit|322W7JE **
-- 8|42|entrance|10|23|exit|0NTHK55 **
-- 8|34|entrance|10|35|exit|1106N58 *

-- Let's see the interviews and cross some info

SELECT *
  FROM interviews
 WHERE year = 2021
   AND month = 7
   AND day = 28;

-- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.  - Ruth

-- I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money. - Eugene

-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. - Raymond

-- Let's see phone calls then
SELECT *
  FROM phone_calls
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND duration < 60;

-- id |caller        | receiver     
-- 221|(130) 555-0289|(996) 555-8899|2021|7|28|51
-- 224|(499) 555-9472|(892) 555-8872|2021|7|28|36
-- 233|(367) 555-5533|(375) 555-8161|2021|7|28|45
-- 251|(499) 555-9472|(717) 555-1342|2021|7|28|50
-- 254|(286) 555-6063|(676) 555-6554|2021|7|28|43
-- 255|(770) 555-1861|(725) 555-3243|2021|7|28|49
-- 261|(031) 555-6622|(910) 555-3251|2021|7|28|38
-- 279|(826) 555-1652|(066) 555-9701|2021|7|28|55
-- 281|(338) 555-6650|(704) 555-2131|2021|7|28|54


-- Lets see some people phone numbers and license plates
SELECT caller
  FROM phone_calls
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND duration < 60;
-- Got the result and mapped into an array using javascript

-- Selected the license plates manually
SELECT *
  FROM people
 WHERE phone_number IN ('(130) 555-0289',
                        '(499) 555-9472',
                        '(367) 555-5533',
                        '(499) 555-9472',
                        '(286) 555-6063',
                        '(770) 555-1861',
                        '(031) 555-6622',
                        '(826) 555-1652',
                        '(338) 555-6650')
   AND license_plate IN ('5P2BI95', '94KL13X',
                        '6P58WS2', '4328GD8',
                        'G412CB7', 'L93JTIZ',
                        '322W7JE', '0NTHK55',
                        '1106N58');

-- id    |name |phone_number  |passport  |license_plate
-- 398010|Sofia|(130) 555-0289|1695452385|G412CB7
-- 449774|Taylor|(286) 555-6063|1988161715|1106N58
-- 514354|Diana|(770) 555-1861|3592750733|322W7JE
-- 560886|Kelsey|(499) 555-9472|8294398571|0NTHK55
-- 686048|Bruce|(367) 555-5533|5773159633|94KL13X

-- lets see who got a flight thhe day after the theft from these suspects
SELECT f.month, f.day, f.hour, f.minute, f.destination_airport_id, p.passport_number
  FROM flights AS f
  JOIN airports AS a
    ON a.id = f.origin_airport_id
  JOIN passengers AS p
    ON p.flight_id = f.id
 WHERE a.city = 'Fiftyville'
   AND f.year = 2021
   AND p.passport_number IN ('1695452385',
                             '1988161715',
                             '3592750733',
                             '8294398571',
                             '5773159633')
  ORDER BY (f.year * 1000 + f.month * 100 + f.day) ASC;

-- month|day|hour|minute|destination_airport_id|passport_number
-- 7|29|16|0|6|3592750733
-- 7|29|8|20|4|1695452385
-- 7|29|8|20|4|5773159633
-- 7|29|8|20|4|8294398571
-- 7|29|8|20|4|1988161715
-- 7|30|10|19|5|3592750733

-- Let's see who did an atm transaction that day
SELECT p.name, p.id, p.phone_number, p.license_plate, trs.amount
  FROM (SELECT *
          FROM atm_transactions
         WHERE year = 2021
           AND month = 7
           AND day = 28
           AND transaction_type = 'withdraw'
           AND atm_location = 'Leggett Street') AS trs
  JOIN bank_accounts AS acc
    ON trs.account_number = acc.account_number
  JOIN people AS p
    ON acc.person_id = p.id
 WHERE p.license_plate IN ('5P2BI95', '94KL13X',
                          '6P58WS2', '4328GD8',
                          'G412CB7', 'L93JTIZ',
                          '322W7JE', '0NTHK55',
                          '1106N58')
  AND p.passport_number IN ( '1695452385',
                             '1988161715',
                             '8294398571',
                             '5773159633')
  AND p.phone_number IN ('(130) 555-0289',
                        '(499) 555-9472',
                        '(367) 555-5533',
                        '(499) 555-9472',
                        '(286) 555-6063',
                        '(770) 555-1861',
                        '(031) 555-6622',
                        '(826) 555-1652',
                        '(338) 555-6650');
-- Prime suspects:
-- Bruce|686048|(367) 555-5533|94KL13X
-- Taylor|449774|(286) 555-6063|1106N58

-- Lets see who each of them called

-- Bruce|(367) 555-5533
-- 233|(367) 555-5533|(375) 555-8161
-- Taylor|(286) 555-6063|
-- 254|(286) 555-6063|(676) 555-6554

SELECT *
  FROM people
 WHERE phone_number IN ('(375) 555-8161', '(676) 555-6554');

-- Taylor called James
-- 250277|James|(676) 555-6554|2438825627|Q13SVG6
-- Bruce called Robin
-- 864400|Robin|(375) 555-8161||4V16VO0

-- Lets see transactions for those people
SELECT trs.month, trs.day, trs.atm_location, trs.transaction_type, trs.amount, p.name
  FROM atm_transactions AS trs
  JOIN bank_accounts AS acc
    ON acc.account_number = trs.account_number
  JOIN people AS p
    ON p.id = acc.person_id
 WHERE p.id IN (250277, 864400);

-- 7|26|Daboin Sanchez Drive|withdraw|25|Robin
-- 7|27|Carvalho Road|deposit|55|Robin
-- 7|29|Blumberg Boulevard|deposit|90|Robin
-- 7|30|Daboin Sanchez Drive|deposit|10|Robin
-- 7|30|Leggett Street|withdraw|10|Robin
-- 7|30|Humphrey Lane|deposit|15|Robin
-- 7|31|Carvalho Road|deposit|100|Robin
-- 7|31|Carvalho Road|withdraw|35|Robin
-- 8|1|Daboin Sanchez Drive|deposit|40|Robin
-- 8|1|Blumberg Boulevard|withdraw|5|Robin
-- 8|1|Humphrey Lane|withdraw|40|Robin

-- Two suspects left.. lets see the cities they went to
SELECT *
  FROM airports
 WHERE id = 4;

--  4|LGA|LaGuardia Airport|New York City

-- Bruce is a higher suspect due to day of leaving
