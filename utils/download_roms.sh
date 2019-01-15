#!/bin/bash

BASE_URL="https://archive.org/download/"
FILENAME=$(basename "$BASE_URL$1")

echo "Downloading: "$FILENAME

ROM_PATH=$HOME

wget $BASE_URL$1 -P $ROM_PATH

ZIP_FILE="$ROM_PATH$FILENAME"
#ls $ROM_PATH$FILENAME

echo "$ZIP_FILE"

#unzip "$ROM_PATH$FILENAME" -d $ROM_PATH

#rm $ROM_PATH* 
