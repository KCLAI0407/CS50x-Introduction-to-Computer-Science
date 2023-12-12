-- Keep a log of any SQL queries you execute as you solve the mystery.

-- find the description from the crime_scene_reports
SELECT description FROM crime_scene_reports
WHERE month = 7 AND day = 28 AND year = 2021 AND street = 'Humphrey Street';

/*+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
|                                                                                                       description                                                                                                        |
+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
| Littering took place at 16:36. No known witnesses.                                                                                                                                                                       |
+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+*/

-- take a look at the transcript of the interviewers
SELECT name, transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;

/*+---------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
|  name   |                                                                                                                                                     transcript                                                                                                                                                      |
+---------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| Jose    | “Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”                                                                                                                               |
| Eugene  | “I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”                                                                                                                                                                                      |
| Barbara | “You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.                                                                                                                   |
| Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
| Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
| Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
| Lily    | Our neighboring courthouse has a very annoying rooster that crows loudly at 6am every day. My sons Robert and Patrick took the rooster to a city far, far away, so it may never bother us again. My sons have successfully arrived in Paris.                                                                        |
+---------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+*/

-- Check the atm record
SELECT account_number, transaction_type, amount FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street';
/*+----------------+------------------+--------+
| account_number | transaction_type | amount |
+----------------+------------------+--------+
| 28500762       | withdraw         | 48     |
| 28296815       | withdraw         | 20     |
| 76054385       | withdraw         | 60     |
| 49610011       | withdraw         | 50     |
| 16153065       | withdraw         | 80     |
| 86363979       | deposit          | 10     |
| 25506511       | withdraw         | 20     |
| 81061156       | withdraw         | 30     |
| 26013199       | withdraw         | 35     |
+----------------+------------------+--------+*/

-- Check the earliest flight destination
SELECT * FROM airports WHERE id IN (SELECT destination_airport_id  FROM flights WHERE day = 29 AND month = 7 AND year = 2021 ORDER BY hour, minute LIMIT 1);
/*+----+--------------+-------------------+---------------+
| id | abbreviation |     full_name     |     city      |
+----+--------------+-------------------+---------------+
| 4  | LGA          | LaGuardia Airport | New York City |
+----+--------------+-------------------+---------------+*/

-- Check who had a call less than a minute
-- (caller)
SELECT * FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60);
/*+--------+---------+----------------+-----------------+---------------+
|   id   |  name   |  phone_number  | passport_number | license_plate |
+--------+---------+----------------+-----------------+---------------+
| 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
| 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
| 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
| 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
| 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
| 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
| 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
| 907148 | Carina  | (031) 555-6622 | 9628244268      | Q12B3Z3       |
+--------+---------+----------------+-----------------+---------------+*/

-- (receiver)
SELECT * FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60);
/*+--------+------------+----------------+-----------------+---------------+
|   id   |    name    |  phone_number  | passport_number | license_plate |
+--------+------------+----------------+-----------------+---------------+
| 250277 | James      | (676) 555-6554 | 2438825627      | Q13SVG6       |
| 251693 | Larry      | (892) 555-8872 | 2312901747      | O268ZZ0       |
| 484375 | Anna       | (704) 555-2131 | NULL            | NULL          |
| 567218 | Jack       | (996) 555-8899 | 9029462229      | 52R0Y8U       |
| 626361 | Melissa    | (717) 555-1342 | 7834357192      | NULL          |
| 712712 | Jacqueline | (910) 555-3251 | NULL            | 43V0R5D       |
| 847116 | Philip     | (725) 555-3243 | 3391710505      | GW362R6       |
| 864400 | Robin      | (375) 555-8161 | NULL            | 4V16VO0       |
| 953679 | Doris      | (066) 555-9701 | 7214083635      | M51FA04       |
+--------+------------+----------------+-----------------+---------------+*/


-- Find the theft basic on 1. Theft of the CS50 duck took place at 10:15am, and 'Sometime within ten minutes of the theft', 2. They take the earliest flight, 3. He/She withdraw money at Leggett Street, 3. have a call within 1 minute.
SELECT * FROM people WHERE passport_number IN (SELECT passport_number FROM passengers
WHERE flight_id IN (SELECT flights.id FROM flights JOIN airports ON airports.id = flights.destination_airport_id
WHERE destination_airport_id = 4 AND day = 29 AND month = 7 AND year = 2021 ORDER BY hour, minute LIMIT 1))
AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60)
AND id IN (SELECT person_id FROM bank_accounts
WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'))
AND license_plate IN (SELECT license_plate FROM bakery_security_logs
WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND 15 < minute AND minute <= 15+10 AND activity = 'exit');

/*+--------+-------+----------------+-----------------+---------------+
|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+-------+----------------+-----------------+---------------+*/

-- Find the accomplice

SELECT * FROM people
WHERE phone_number IN
(SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60 AND caller = '(367) 555-5533');

/*+--------+-------+----------------+-----------------+---------------+
|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 864400 | Robin | (375) 555-8161 | NULL            | 4V16VO0       |
+--------+-------+----------------+-----------------+---------------+*/


