# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added 

* Start using [**lvgl**](https://github.com/littlevgl/lvgl) graphical library. 
* File structure. Added software folder to store software files (espidf project and utils folder).
* File structure. Added hardware folder to store pdf and csv files such as BOM, schematics and PCB layouts.
* Audio p2 connector can be detected.
* Audio amplifier now can be turned on/off if the p2 connector is detected.
* Battery level can be mesured.

### Removed

* lvgl and lv_examples (KairOS will be added soon).