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

--
-- user
--
CREATE TABLE user_info( id INTEGER PRIMARY KEY, username TEXT NOT NULL  );

--
-- audio
--
CREATE TABLE audio( initialized INTEGER PRIMARY KEY, mod_state INTEGER, volume INTEGER ) WITHOUT ROWID;

--
-- wifi
--
CREATE TABLE user ( initialized INTEGER PRIMARY KEY, mod_state TEXT, wifi_ssid TEXT, wifi_password TEXT) WITHOUT ROWID;

--
-- battery
--
CREATE TABLE battery ( initialized INTEGER PRIMARY KEY, bat_level INTEGER, ischarging TEXT, mod_state TEXT ) WITHOUT ROWID;

--
-- software
--
CREATE TABLE software ( espidf_version TEXT PRIMARY KEY, app_version TEXT, compile_datetime TEXT ) WITHOUT ROWID;