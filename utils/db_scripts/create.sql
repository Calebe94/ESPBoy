/*
 * SQLite CREATE TABLE examples.
 * Created by Alvin Alexander, http://alvinalexander.com
 * Released under the Creative Commons License.
 * References:
    - https://sqlite.org/withoutrowid.html
    - https://www.tutorialspoint.com/sqlite/index.htm
    - https://sqlite.org/lang.html
    - https://www.sqlite.org/datatype3.html
 */

/***************
* CREATE TABLES
***************/
--
-- user: Create the user information.
-- Can add more than one user to ESPBoy
--
CREATE TABLE IF NOT EXISTS user_info(
   id INTEGER PRIMARY KEY,
   username TEXT NOT NULL,          -- User name or user nickname 
   user_passwd TEXT DEFAULT NULL,   -- User Password, if the user doesn't want a password it should be NULL
   gender INTEGER,                  -- User gender, 0 to Female, 1 to Male, 2 to other.
   recent_played TEXT               -- User recently played game.
);

--
-- audio
--
CREATE TABLE IF NOT EXISTS audio( 
   initialized INTEGER PRIMARY KEY, -- Is audio module initiated? (Boolean)
   mod_state INTEGER,               -- Is audio module ON? (Boolean)
   volume INTEGER                   -- Audio volume: from 0 to 100
) WITHOUT ROWID;

--
-- wifi
--
CREATE TABLE IF NOT EXISTS wifi( 
   initialized INTEGER PRIMARY KEY, -- Is wifi module initiated? (boolean)
   mod_state INTEGER,               -- Is wifi connected? (boolean)
   wifi_ssid TEXT DEFAULT NULL,                  -- Last Wifi ssid connected
   wifi_password TEXT DEFAULT NULL               -- Last wifi password connected 
) WITHOUT ROWID;

--
-- battery
--
CREATE TABLE IF NOT EXISTS battery( 
   initialized INTEGER PRIMARY KEY, -- Is battery module initiated? (boolean)
   mod_state INTEGER,               -- Is battery charging? (boolean)  
   bat_level INTEGER                -- Battery level: from 0 to 100%
) WITHOUT ROWID;

--
-- software
--
CREATE TABLE IF NOT EXISTS software( 
   espidf_version TEXT PRIMARY KEY, -- ESP-IDF version 
   app_version TEXT,                -- ESPBoy firmware version
   compile_datetime TEXT            -- When ESPBoy firmware was compiled
) WITHOUT ROWID;

/********************
* INSERT INFO TABLES
********************/
--
-- user
--
INSERT INTO user_info (id, username, user_passwd, gender) VALUES (0, 'admin', 'admin', 1);

--
-- audio
--
INSERT INTO audio (initialized, mod_state, volume) VALUES (0, 0, 0);

--
-- battery
--
INSERT INTO battery (initialized, mod_state, bat_level) VALUES (0, 0, 0);

--
-- wifi
--
INSERT INTO wifi (initialized, mod_state, wifi_ssid, wifi_password) VALUES (0, 0, NULL, NULL);

--
-- software
--
INSERT INTO software (espidf_version, app_version, compile_datetime) VALUES ('stable', 'rev0.9', '21-01-2019');

/********************
* UPDATE INFO TABLES
********************/
--
-- user
--
UPDATE user_info SET id=0, username='Guest', user_passwd=NULL, gender=2; 

--
-- audio
--
UPDATE audio SET initialized=1, mod_state=1, volume=100;

--
-- battery
--
UPDATE battery SET initialized=1, mod_state=1 , bat_level=100;

--
-- wifi
--
UPDATE wifi SET initialized=1, mod_state=1, wifi_ssid='Fator', wifi_password='11058283';

--
-- software
--
UPDATE software SET espidf_version='stable',app_version='rev0.9', compile_datetime='21-01-2019';