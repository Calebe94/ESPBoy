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
CREATE TABLE user (
  id INTEGER PRIMARY KEY,
  username TEXT NOT NULL,
);

--
-- audio
--
CREATE TABLE audio (
--   id INTEGER PRIMARY KEY,
  initialized INTEGER ,     --  Shows if the module was initialized or not during the boot process
  mod_state INTEGER ,       --  State of the module, it can be ON(1) or OFF(0)
  volume INTEGER ,
) WITHOUT ROWID;

--
-- wifi
--
CREATE TABLE user (
--   id INTEGER PRIMARY KEY,
  wifi_ssid TEXT,
  wifi_password TEXT,
  mod_state TEXT,
) WITHOUT ROWID;

--
-- battery
--
CREATE TABLE user (
--   id INTEGER PRIMARY KEY,
  bat_level INTEGER,
  ischarging TEXT,
  mod_state TEXT,
) WITHOUT ROWID;

--
-- software
--
CREATE TABLE software (
--   id INTEGER PRIMARY KEY,
  bat_level INTEGER,
  espidf_version TEXT,
  app_version TEXT,
  compile_datetime TEXT,
) WITHOUT ROWID;