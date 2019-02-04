#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := ESPBoy

EXTRA_COMPONENT_DIRS :=	$(abspath components/Apps) \
						$(abspath components/Libs) \
						$(abspath components/Kernel) \
						$(abspath components/Drivers) \
						$(abspath components/Res) \

include $(IDF_PATH)/make/project.mk

ota: app
	curl ${ESP32_IP}:8032 --data-binary @- < build/$(PROJECT_NAME).bin