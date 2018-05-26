//
// Created by sulvto on 18-5-11.
//

#include <string.h>
#include <stdlib.h>
#include "map.h"
#include "rtda.h"
#include "native.h"

void emptyNativeMethod(struct Frame *frame);

static Map_T NATIVE_METHOD_MAP;

void init() {
    if (NATIVE_METHOD_MAP == NULL) {
        NATIVE_METHOD_MAP = Map_new(1000, NULL, NULL);
    }
}


char *nativeMethodKey(const char *class_name, const char *method_name, const char *method_descriptor) {
    char class_name_cp[strlen(class_name)];
    char method_name_cp[strlen(method_name)];
    char method_descriptor_cp[strlen(method_descriptor)];
    strcpy(class_name_cp, class_name);
    strcpy(method_name_cp, method_name);
    strcpy(method_descriptor_cp, method_descriptor);

    char *key = (char *) malloc(strlen(class_name) + strlen(method_name) + strlen(method_descriptor) + 3);
    key = strcat(class_name_cp, "~");
    key = strcat(method_name_cp, "~");
    key = strcat(method_descriptor_cp, "~");

    return key;
}

void NativeMethod_register(const char *class_name, const char *method_name, const char *method_descriptor, NativeMethod method) {
    init();

    char *key = nativeMethodKey(class_name, method_name, method_descriptor);
    Map_put(NATIVE_METHOD_MAP, key, method);
}

NativeMethod NativeMethod_find(char *class_name, char *method_name, char *method_descriptor) {
    init();

    char *key = nativeMethodKey(class_name, method_name, method_descriptor);
    void *method = Map_get(NATIVE_METHOD_MAP, key);

    if (method != NULL) {
        return method;
    }

    if (strcmp(method_descriptor, "()V") && strcmp(method_name, "registerNatives")) {
        return emptyNativeMethod;
    }

    return NULL;
}

void emptyNativeMethod(struct Frame *frame) {
    // do noting
}