#
# Component Makefile
#
# This Makefile can be left empty. By default, it will take the sources in the
# src/ directory, compile them and link them into lib(subdirectory_name).a
# in the build directory. This behaviour is entirely configurable,
# please read the ESP-IDF documents if you need to do this.
#


COMPONENT_ADD_INCLUDEDIRS := . \
	nofrendo \
	nofrendo/cpu \
	nofrendo/libsnss \
	nofrendo/nes \
	nofrendo/sndhrdw \
	launcher \
	user_data \

COMPONENT_SRCDIRS := . \
	nofrendo \
	nofrendo/cpu \
	nofrendo/libsnss \
	nofrendo/nes \
	nofrendo/sndhrdw \
	nofrendo/mappers \
	launcher \
	user_data \

CFLAGS += -Wno-error=char-subscripts -Wno-error=attributes -DNOFRENDO_DEBUG


# COMPONENT_DEPENDS := nofrendo
# COMPONENT_SRCDIRS := nofrendo
# COMPONENT_ADD_INCLUDEDIRS := $(COMPONENT_SRCDIRS) ..

