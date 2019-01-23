#!/bin/bash
. ${IDF_PATH}/add_path.sh
esptool.py --chip esp32 --port "$1" --baud $((230400*4)) read_flash -fs 4MB 1M
