#ifndef _APP_OBJECT_H_
#define _APP_OBJECT_H_

#include "lvgl.h"

typedef struct _app_object {
    lv_indev_t * indev;
    lv_obj_t * src;
    void * params;
    void (*init)(const struct _app_object *);
    void (*update)(const struct _app_object *);
    void (*deinit)(const struct _app_object *);
}app_t;

#define APP_INIT(object)    object.init(&object)

#define APP_UPDATE(object)  object.update(&object)

#define APP_DEINIT(object)  object.deinit(&object)

#endif