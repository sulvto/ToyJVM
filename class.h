//
// Created by sulvto on 18-5-1.
//

#ifndef TOYJVM_CLASS_H
#define TOYJVM_CLASS_H

#include "type.h"
#include "rtda.h"
#include "classreader.h"
#include "map.h"

struct Field {
    u2      access_flags;
    char    *name;
    char    *descriptor;
    u4      slot_id;
    u2      const_value_index;
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
    struct Class *_class;
    u4      arg_count;
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

    // bool, 0 or 1
    u2                      init_started;
};

struct ClassLoader {
    // Map_T<char *, Class>
    Map_T class_map;
};

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

union Constant {
    int                         int_value;
    long                        long_value;
    float                       float_value;
    double                      double_value;
    char                        *string;
    struct MethodRef            *method_ref;
    struct ClassRef             *class_ref;
    struct FieldRef             *field_ref;
    struct InterfaceMethodRef   *interface_method_ref;
};

struct ConstantPool {
    struct Class    *_class;
    u2              size;
    union Constant *constants;
};

struct ClassLoader *ClassLoader_new();

struct ClassLoader *ClassLoader_free(struct ClassLoader *);

struct Class *ClassLoader_loadClass(struct ClassLoader *loader, const char *name);

void initClass(struct Thread *, struct Class*);

struct Object *newObject(struct Class *_class);

int Object_isInterfaceOf(struct Object *_this, struct Class *_other);

int Class_isSuperClassOf(struct Class *_this, struct Class *_other);

int Class_isImplements(struct Class *_this, struct Class *_other);

char *Class_packageName(struct Class *_this);

int Class_isArray(struct Class *_this);

Object *Class_newArray(struct Class *_this, const unsigned int count);

struct Class *Class_arrayClass(struct Class *_this);




struct Method *resolvedInterfaceMethod(struct InterfaceMethodRef *interface_method_ref);

struct Method *resolvedMethod(struct MethodRef *method_ref);

struct Field *resolvedField(struct FieldRef *field_ref);

struct Method *lookupMethodInClass(struct Class *_class, char *name, char *descriptor);




#define resolvedClass(ref, result)  \
    if (ref->_class == NULL) {      \
        resolveClassRef(ref);       \
    }                               \
    result = ref->_class;           \


#define resolveClassRef(ref)                                    \
    struct Class *d = ref->constant_pool->_class;               \
    struct Class *c = ClassLoader_loadClass(d->loader, ref->class_name);    \
    if (Class_isAccessibleTo(c, d) == 0) {                              \
        printf("java.lang.IllegalAccessError");                 \
    }                                                           \
    ref->_class = c;                                            \


#endif //TOYJVM_CLASS_H
