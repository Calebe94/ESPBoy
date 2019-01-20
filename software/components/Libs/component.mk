#
# Component Makefile
#
# This Makefile can be left empty. By default, it will take the sources in the
# src/ directory, compile them and link them into lib(subdirectory_name).a
# in the build directory. This behaviour is entirely configurable,
# please read the ESP-IDF documents if you need to do this.
#

# COMPONENT_DEPENDS := nofrendo

COMPONENT_SRCDIRS := . \
	Collections-C/src/ \
	Sort/src/ \
	circular_linked_list \
	dynamic_list \
	esp32-ota-server \
	linked_list \
	lvgl \
	sqlite3_connector \
	# sqlite3 \
	
COMPONENT_ADD_INCLUDEDIRS := . \
	.. \
	Collections-C/src/include/ \
	Sort/inc/ \
	circular_linked_list \
	dynamic_list \
	esp32-ota-server/include \
	linked_list \
	lvgl \
	sqlite3_connector \
	# sqlite3 \
