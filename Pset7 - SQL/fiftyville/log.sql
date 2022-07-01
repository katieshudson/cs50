-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Start with crime_scene_reports table to understand 1) what info I have and how it's represented 2) how many crimes have taken place, are there patterns?
SELECT * FROM crime_scene_reports;

-- View information in interviwes table for the month of July
SELECT * FROM interviews WHERE month = 7;

-- Pull witness names for those who mention bakery in their testimony and to understand WHEN they were interviewed (ie. on the date of crime?)
 SELECT month, day, name, transcript FROM interviews WHERE month = 7 AND transcript LIKE "%bakery%";

 -- Look into security footage from bakery parking lot on July 28th
 SELECT * FROM bakery_security_logs WHERE month = 7 and day = 28;

 -- Narrow search in parking lot for exits only, within 10 min of the 10:15 crime on July 28th
 SELECT * FROM bakery_security_logs WHERE month = 7 AND day = 28 AND activity = "exit" AND hour >= 10 AND hour <= 11 AND minute <= 26;

 -- Pull a list of license plates that exited the parking lot, within 10 min of 10:15am crime on July 28th
 SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND activity = "exit" AND hour >= 10 AND hour <= 11 AND minute <= 26;

 -- Pull a list of withdraw transactions from Leggett Street on July 28th 2021 and their amounts
 SELECT id, account_number, atm_location, transaction_type, amount FROM atm_transactions WHERE month = 7 AND day = 28 AND year = 2021 AND transaction_type = "withdraw" AND atm_location = "Leggett Street";

 -- Pull a list of license plates and names from people table and bakery security logs of people exiting between 10 and 11 am to develop suspect list
 SELECT people.name, people.license_plate, bakery_security_logs.license_plate FROM people INNER JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate WHERE bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.activity = "exit" AND bakery_security_logs.hour >= 10 AND bakery_security_logs.hour <11;

-- Pulling personal information for each suspect based on their exiting of the parking lot
SELECT name, license_plate, passport_number, phone_number FROM people WHERE license_plate LIKE "5P2BI95";
SELECT name, license_plate, passport_number, phone_number FROM people WHERE license_plate LIKE "94KL13X";
SELECT name, license_plate, passport_number, phone_number FROM people WHERE license_plate LIKE "6P58WS2";
SELECT name, license_plate, passport_number, phone_number FROM people WHERE license_plate LIKE "4328GD8";
SELECT name, license_plate, passport_number, phone_number FROM people WHERE license_plate LIKE "G412CB7";
SELECT name, license_plate, passport_number, phone_number FROM people WHERE license_plate LIKE "L93JTIZ";
SELECT name, license_plate, passport_number, phone_number FROM people WHERE license_plate LIKE "322W7JE";
SELECT name, license_plate, passport_number, phone_number FROM people WHERE license_plate LIKE "0NTHK55";

-- Looking up phone call conversations on July 28th that lasted less than 1 minute
SELECT * FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;

-- Look up all flights that left from Fiftyville on July 29th 2021
SELECT * FROM flights WHERE month = 7 AND day = 29 AND year = 2021;

-- Look up airport ID for fiftville
SELECT city, id FROM airports WHERE id IN (SELECT origin_airport_id FROM flights WHERE month = 7 AND day = 29 AND year = 2021)

-- Look up airport IDs for other cities that left from
SELECT city, id FROM airports WHERE id IN (SELECT destination_airport_id FROM flights WHERE month = 7 AND day = 29 AND year = 2021);

-- look up flight number for fiftyville to newyork flight
SELECT origin_airport_id, destination_airport_id, id FROM flights WHERE destination_airport_id = 4 AND year = 2021 AND month = 7 AND day = 29;

-- look up passenger log for flight 36 on July 29th 2021
SELECT * FROM passengers WHERE flight_id = 36;

-- Join people and passenger tables to compare passport numbers for flight # 36
SELECT people.name, people.passport_number, passengers.passport_number, passengers.flight_id FROM people INNER JOIN passengers ON people.passport_number = passengers.passport_number WHERE passengers.flight_id = 36;

-- Look up who Sofia, Bruce and Kelsey called
SELECT name, phone_number FROM people WHERE phone_number LIKE "%(996) 555-8899%";
SELECT name, phone_number FROM people WHERE phone_number LIKE "%(375) 555-8161%";


-- Look up bank account numbers that match ATM transaction bank accounts from Leggett Street
SELECT account_number FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street");

-- Find person_id based on bank account number
SELECT person_id FROM bank_accounts WHERE account_number = 49610011;

-- Find name based on person_id
SELECT name FROM people WHERE id = 686048;

-- create nested query that merges the 2 queries above ^^ finding the name basedon the people id and bank account number
SELECT name FROM people WHERE id IN(SELECT person_id FROM bank_accounts WHERE account_number = 49610011);
SELECT name FROM people WHERE id IN(SELECT person_id FROM bank_accounts WHERE account_number = 86363979);
SELECT name FROM people WHERE id IN(SELECT person_id FROM bank_accounts WHERE account_number = 26013199);
SELECT name FROM people WHERE id IN(SELECT person_id FROM bank_accounts WHERE account_number = 16153065);
SELECT name FROM people WHERE id IN(SELECT person_id FROM bank_accounts WHERE account_number = 28296815);
SELECT name FROM people WHERE id IN(SELECT person_id FROM bank_accounts WHERE account_number = 25506511);
SELECT name FROM people WHERE id IN(SELECT person_id FROM bank_accounts WHERE account_number = 28500762);
SELECT name FROM people WHERE id IN(SELECT person_id FROM bank_accounts WHERE account_number = 76054385);
SELECT name FROM people WHERE id IN(SELECT person_id FROM bank_accounts WHERE account_number = 81061156);