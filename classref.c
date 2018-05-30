//
// Created by sulvto on 18-5-17.
//

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "class.h"
#include "classref.h"
#include "classloader.h"
#include "flags.h"
#include "constantpool.h"

#define ClassRef_T              ClassRef
#define MethodRef_T             MethodRef
#define FieldRef_T              FieldRef
#define InterfaceMethodRef_T    InterfaceMethodRef

static Class FieldRef_resolvedClass(FieldRef_T field_ref);
static void InterfaceMethodRef_resolveInterfaceMethodRef(InterfaceMethodRef_T interface_method_ref);

struct ClassRef_T {
    ConstantPool constant_pool;
    Class               _class;
    char                *class_name;
};

struct MethodRef_T {
    ConstantPool constant_pool;
    Class               _class;
    char                *class_name;
    Method              method;
    char                *name;
    char                *descriptor;
};

struct FieldRef_T {
    ConstantPool constant_pool;
    Class             _class;
    char                *class_name;
    Field              field;
    char                *name;
    char                *descriptor;
};

struct InterfaceMethodRef_T {
    ConstantPool     constant_pool;
    Class                 _class;
    char                    *class_name;
    Method                method;
    char                    *name;
    char                    *descriptor;
};

ClassRef_T ClassRef_new(char *class_name, struct ConstantPool *constant_pool) {
    ClassRef_T class_ref = (ClassRef) malloc(sizeof(struct ClassRef));
    class_ref->_class = NULL;
    class_ref->class_name = class_name;
    class_ref->constant_pool = constant_pool;
    return class_ref;
}

MethodRef_T MethodRef_new(char *name, char *descriptor, char *class_name, ConstantPool constant_pool) {
    struct MethodRef *method_ref = (struct MethodRef *) malloc(sizeof(struct MethodRef));
    method_ref->name = name;
    method_ref->descriptor = descriptor;
    method_ref->_class = NULL;
    method_ref->class_name = class_name;
    method_ref->method = NULL;
    method_ref->constant_pool = constant_pool;
    return method_ref;
}

FieldRef_T FieldRef_new(char *name, char *descriptor, char *class_name, ConstantPool constant_pool) {
    struct FieldRef *field_ref = (struct FieldRef *) malloc(sizeof(struct FieldRef));
    field_ref->name = name;
    field_ref->descriptor = descriptor;
    field_ref->_class = NULL;
    field_ref->class_name = class_name;
    field_ref->field = NULL;
    field_ref->constant_pool = constant_pool;
    return field_ref;
}

Class FieldRef_class(FieldRef_T field_ref) {
    return field_ref->_class;
}

InterfaceMethodRef_T InterfaceMethodRef_new(char *name, char *descriptor, char *class_name, ConstantPool constant_pool) {
    struct InterfaceMethodRef *interface_method_ref = (struct InterfaceMethodRef *) malloc(sizeof(struct InterfaceMethodRef));;
    interface_method_ref->name = name;
    interface_method_ref->descriptor = descriptor;
    interface_method_ref->_class = NULL;
    interface_method_ref->class_name = class_name;
    interface_method_ref->method = NULL;
    interface_method_ref->constant_pool = constant_pool;
    return interface_method_ref;
}

Class ClassRef_resolvedClass(ClassRef_T ref) {
    if (ref->_class == NULL) {
        ClassRef_resolveClassRef(ref);
    }
    return ref->_class;
}

Class ClassRef_class(ClassRef_T class_ref) {
    return class_ref->_class;
}

void ClassRef_resolveClassRef(ClassRef_T ref)         {
    Class d = ConstantPool_class(ref->constant_pool);
    Class c = ClassLoader_loadClass(Class_loader(d), ref->class_name);
    if (Class_isAccessibleTo(c, d) == 0) {
        printf("java.lang.IllegalAccessError");
    }
    ref->_class = c;
}

Class MethodRef_resolvedClass(MethodRef_T method_ref) {
    if (method_ref->_class == NULL) {
        MethodRef_resolveClassRef(method_ref);
    }
    return method_ref->_class;
}

void MethodRef_resolveClassRef( MethodRef_T method_ref)         {
    Class d = ConstantPool_class(method_ref->constant_pool);
    Class c = ClassLoader_loadClass(Class_loader(d), method_ref->class_name);
    if (Class_isAccessibleTo(c, d) == 0) {
        printf("java.lang.IllegalAccessError");
    }
    method_ref->_class = c;
}
void InterfaceMethodRef_resolveClassRef( InterfaceMethodRef_T method_ref) {
    Class d = ConstantPool_class(method_ref->constant_pool);
    Class c = ClassLoader_loadClass(Class_loader(d), method_ref->class_name);
    if (Class_isAccessibleTo(c, d) == 0) {
        printf("java.lang.IllegalAccessError");
    }
    method_ref->_class = c;
}

Class InterfaceMethodRef_resolvedClass( InterfaceMethodRef_T method_ref)         {
    if (method_ref->_class == NULL) {
        InterfaceMethodRef_resolveClassRef(method_ref);
    }

    return method_ref->_class;
}

void MethodRef_resolveMethodRef(MethodRef_T method_ref) {
    Class d = ConstantPool_class(method_ref->constant_pool);
    Class c = MethodRef_resolvedClass(method_ref);

    if (Class_isInterface(c)) {
        printf("java.lang.IncompatibleClassChangeError\n");
        exit(1);
    }

    Method method = Class_lookupMethod(c, method_ref->name, method_ref->descriptor);

    if (method == NULL) {
        printf("java.lang.NoSuchMethodError\n");
        exit(1);
    }

    if (!Method_isAccessibleTo(method, d)) {
        printf("java.lang.IllegalAccessError\n");
        exit(1);
    }

    method_ref->method = method;
}

Method MethodRef_resolvedMethod(MethodRef_T method_ref) {
    if (method_ref->method == NULL) {
        MethodRef_resolveMethodRef(method_ref);
    }

    return method_ref->method;
}


Method MethodRef_lookupMethodInClass(MethodRef_T method_ref, Class _class) {
    return Class_lookupMethodInClass(_class, method_ref->name, method_ref->descriptor);
}


char *MethodRef_name(MethodRef_T method_ref) {
    return method_ref->name;
}

char *MethodRef_descriptor(MethodRef_T method_ref) {
    return method_ref->descriptor;
}

Method InterfaceMethodRef_lookupMethodInClass(InterfaceMethodRef_T interface_method_ref, Class _class) {
    return Class_lookupMethodInClass(_class, interface_method_ref->name, interface_method_ref->descriptor);
}

static void InterfaceMethodRef_resolveInterfaceMethodRef(InterfaceMethodRef_T interface_method_ref) {
    Class d = ConstantPool_class(interface_method_ref->constant_pool);
    Class c =    InterfaceMethodRef_resolvedClass(interface_method_ref);

    if (!Class_isInterface(c)) {
        printf("java.lang.IncompatibleClassChangeError");
    }

    Method method = Class_lookupInterfaceMethod(c, interface_method_ref->name, interface_method_ref->descriptor);

    if (method == NULL) {
        printf("java.lang.NoSuchMethodError");
    }

    if (!Method_isAccessibleTo(method, d)) {
        printf("java.lang.IllegalAccessError");
    }

    interface_method_ref->method = method;
}

Method InterfaceMethodRef_resolvedInterfaceMethod(InterfaceMethodRef_T interface_method_ref) {
    if (interface_method_ref->method == NULL) {
        InterfaceMethodRef_resolveInterfaceMethodRef(interface_method_ref);
    }

    return interface_method_ref->method;
}



Field FieldRef_resolvedField(FieldRef_T field_ref) {
    if (field_ref->field == NULL) {
        FieldRef_resolveFieldRef(field_ref);
    }

    return field_ref->field;
}

void FieldRef_resolveFieldRef( FieldRef_T field_ref) {
    Class d = ConstantPool_class(field_ref->constant_pool);
    Class c = FieldRef_resolvedClass(field_ref);
    Field field = Class_lookupField(c, field_ref->name, field_ref->descriptor);

    if (field == NULL) {
        printf("java.lang.NoSuchFieldError");
    }

    if (!Field_isAccessibleTo(field, d)) {
        printf("java.lang.IllegalAccessError");
    }

    field_ref->field = field;
}

void FieldRef_resolveClassRef(FieldRef_T field_ref) {
    Class d = ConstantPool_class(field_ref->constant_pool);
    Class c = ClassLoader_loadClass(Class_loader(d), field_ref->class_name);
    if (Class_isAccessibleTo(c, d) == 0) {
        printf("java.lang.IllegalAccessError\n");
        exit(1);
    }
    field_ref->_class = c;
}

static Class FieldRef_resolvedClass(FieldRef_T field_ref) {
    if (field_ref->_class == NULL) {
        FieldRef_resolveClassRef(field_ref);
    }
    return field_ref->_class;
}
