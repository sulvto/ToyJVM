//
// Created by sulvto on 18-5-1.
//

#ifndef TOYJVM_CLASS_H
#define TOYJVM_CLASS_H

#include "type.h"
#include "rtda.h"

struct Field {
    u2 access_flags;
    char *name;
    char *descriptor;
    u4      slot_id;
    u2 const_value_index;
    struct Class *_class;
};

struct Method {
    u2      access_flags;
    char    *name;
    char    *descriptor;
    u4      max_stack;
    u4      max_locals;
    u4      code_length;
    u1      *code;
};

struct ConstantPool {
    struct Class    *_class;
    u4              size;
    struct Constant *constant;
};

struct Class {
    u2                      access_flags;
    char                    *name;
    char                    *super_class_name;
    char                    **interface_name;
    u2                      constant_pool_count;
    struct ConstantPool     *constant_pool;
    u2                      fields_count;
    struct Field            *fields;
    u2                      methods_count;
    struct Method           *methods;
    struct ClassLoader      *loader;
    struct Class            *super_class;
    u2                      interface_count;
    struct Class            **interface_class;
    u4                      interface_slot_count;
    u4                      static_slot_count;
    struct Slots            *static_vars;
};

struct ClassLoader {
    // map
};

#endif //TOYJVM_CLASS_H
