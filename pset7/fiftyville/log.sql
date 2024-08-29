-- Keep a log of any SQL queries you execute as you solve the mystery.
select id, description from crime_scene_reports WHERE year = 2023 and month = 7 and day = 28 and street = 'Humphrey Street';
-- id = 295, description: theft at 10:15am, 3 witnesses
select id, name, transcript from interviews WHERE year = 2023 and month = 7 and day = 28 and transcript LIKE "%bakery%";
--interviewee: 161,162,163: ruth, eugene, raymond --> within ten minutes thief was at bakery parking lot.
--thief withdraw money early morning from ATM on Leggett Street. thief plan to take earliest flight out of town.
--phone call < 1 minutes, accompliance purchase ticket
select id, license_plate, hour, minute from bakery_security_logs where year = 2023 and month = 7 and day = 28 and hour = 10 and minute >=5 and minute <=25;
--id: 258-267
select id, account_number from atm_transactions where year = 2023 and month = 7 and day = 28 and atm_location = 'Leggett Street' and transaction_type = 'withdraw';
--id: 246, 264, 266, 267, 269, 288, 313, 336
select id, caller, receiver from phone_calls where year = 2023 and month = 7 and day = 28 and duration <= 60;
-- id: 221,224,233,234,251,254,255,261,279,281
select name, phone_number, passport_number, license_plate from people where id IN (select person_id from bank_accounts where account_number IN (select account_number from atm_transactions
where year = 2023 and month = 7 and day = 28 and atm_location = 'Leggett Street' and transaction_type = 'withdraw' ));
--
select hour, minute, license_plate from bakery_security_logs where license_plate IN (select license_plate from people where id IN (select person_id from bank_accounts where account_number IN (select account_number from atm_transactions
where year = 2023 and month = 7 and day = 28 and atm_location = 'Leggett Street' and transaction_type = 'withdraw' ))); --> 94KL13X, 4328GD8, L93JTIZ, 322W7JE
select id, destination_airport_id, hour, minute from flights where origin_airport_id =( select id from airports where year = 2023 and month = 7 and day = 29 and city = 'Fiftyville');
-- earliest flight: 8:20 id = 36 dest_id = 4
select city from airports where id = 4; -- NYC
select caller, receiver from phone_calls where year = 2023 and month = 7 and day = 28;
select passport_number from passengers where flight_id = 36;
select name, passport_number from people where license_plate in ('94KL13X', '4328GD8', 'L93JTIZ', '322W7JE');
-- iman(709...), luca(849..), diana(359..), bruce(577..)
--> suspect: bruce, luca
select phone_number from people where name = "Bruce"; -- (367) 555-5533
select receiver from phone_calls where caller = '(367) 555-5533' and year = 2023 and month = 7 and day = 28 and duration <= 60;
-- (375) 555-8161
select name from people where phone_number = '(375) 555-8161';
