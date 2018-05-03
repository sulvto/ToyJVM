//
// Created by sulvto on 18-5-1.
//

#ifndef TOYJVM_CLASS_H
#define TOYJVM_CLASS_H

#include "type.h"
#include "rtda.h"
#include "classreader.h"

struct Field {
    u2      access_flags;
    char    *name;
    char    *descriptor;
    u4      slot_id;
    u2      const_value_index;
    struct Class *_class;
};

union Constant {
    struct MethodRef method_ref;
    struct ClassRef class_ref;
    struct FieldRef field_ref;
    struct InterfaceMethodRef interface_method_ref;
};

struct Method {
    u2      access_flags;
    char    *name;
    char    *descriptor;
    u4      max_stack;
    u4      max_locals;
    u4      code_length;
    u1      *code;
    struct Class *_class;
    u4      arg_count;
};

struct ConstantPool {
    struct Class    *_class;
    u2              size;
    union Constant *constants;
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

struct Class *loadClass(const char *name);


struct ClassRef {
    struct ConstantPool *constant_pool;
    struct Class        *_class;
    char                *class_name;
};

struct MethodRef {
    struct ConstantPool *constant_pool;
    struct Class        *_class;
    char                *class_name;
    struct Method       *method;
    char                *name;
    char                *descriptor;
};

struct FieldRef {
    struct ConstantPool *constant_pool;
    struct Class        *_class;
    char                *class_name;
    struct Field        *field;
    char                *name;
    char                *descriptor;
};

struct InterfaceMethodRef {
    struct ConstantPool *constant_pool;
    struct Class        *_class;
    char                *class_name;
    struct Method       *method;
    char                *name;
    char                *descriptor;
};

struct Object *newObject(struct Class *_class);

int Object_isInterfaceOf(struct Object *_this, struct Class *_class);

int Class_isInterface(struct Class *_this);

int Class_isAbstract(struct Class *_this);

struct Field *resolvedField(struct FieldRef *field_ref);



#define resolvedClass(ref, result) \
    if (ref->_class == NULL) {    \
        resolveClassRef(ref); \
    }   \

    result = ref->_class;   \

#define resolveClassRef(ref) \
    struct Class *d = ref->constant_pool->_class; \
    struct Class *c = loadClass(d->loader, ref->class_name); \
    if (isAccessible(c, d) == 0) { \
        printf("java.lang.IllegalAccessError"); \
    } \
    ref->_class = c; \


#endif //TOYJVM_CLASS_H
