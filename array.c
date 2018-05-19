//
// Created by sulvto on 18-5-14.
//
#include <stddef.h>
#include <stdio.h>
#include "rtda.h"
#include "class.h"
#include "array.h"


Object newArray(Class _this, const unsigned int count) {
    char *name = Class_name(_this);
    if (name[0] == '[') {
        // TODO ERROR
        printf("Not array class: %s\n", name);
    }
    switch (name[1]) {
        case 'Z':
            break;
        case 'B':
            break;
        case 'C':
            break;
        case 'S':
            break;
        case 'I':
            break;
        case 'J':
            break;
        case 'F':
            break;
        case 'D':
            break;
        default:return NULL;
    }
}
