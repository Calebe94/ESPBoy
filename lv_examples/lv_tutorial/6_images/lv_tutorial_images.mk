CSRCS += lv_tutorial_images.c
CSRCS += red_flower.c

DEPPATH += --dep-path lv_examples/lv_tutorial/6_images
VPATH += :lv_examples/lv_tutorial/6_images

CFLAGS += "-I$(LVGL_DIR)/lv_examples/lv_tutorial/6_images"
