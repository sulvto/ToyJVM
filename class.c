//
// Created by sulvto on 18-5-1.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "type.h"
#include "flags.h"
#include "class.h"
#include "classref.h"

#define Field_T Field

#define Method_T Method

#define Class_T Class

struct Field_T {
    u2      access_flags;
    char    *name;
    char    *descriptor;
    u4      slot_id;
    u2      const_value_index;
    Class_T _class;
};


struct Method_T {
    u2      access_flags;
    char    *name;
    char    *descriptor;
    u4      max_stack;
    u4      max_locals;
    u4      code_length;
    u1      *code;
    Class_T _class;
    u4      arg_count;
};

struct Class_T {
    u2                      access_flags;
    char                    *name;
    char                    *super_class_name;
    char                    **interface_name;
    u2                      constant_pool_count;
    ConstantPool            constant_pool;
    u2                      fields_count;
    Field_T                 *fields;
    u2                      methods_count;
    Method_T                *methods;
    void                    *loader;
    Class_T                 super_class;
    u2                      interface_count;
    Class_T                 *interface_class;
    u4                      interface_slot_count;
    u4                      static_slot_count;
    void                    *static_vars;

    // bool, 0 or 1
    u2                      init_started;
};


Field_T lookupField(Class_T _class, char *name, char *descriptor);

Method_T lookupMethod(Class_T _class, char *name, char *descriptor);

static Method_T lookupInterfaceMethod(Class_T _class, char *name, char *descriptor);


static char *getArrayClassName(char *class_name);


void resolveFieldRef(struct FieldRef *field_ref);

static void resolveInterfaceMethodRef(struct InterfaceMethodRef *interface_method_ref);

Method_T Class_lookupMethod(Class_T _class, char *name, char *descriptor) {
    Method method = Class_lookupMethodInClass(_class, name, descriptor);
    if (method == NULL) {
        method = lookupMethodInInterfaces(_class->interface_class, _class->interface_count, name, descriptor);
    }

    return method;
}

Method_T Class_lookupMethodInClass(Class_T _class, char *name, char *descriptor) {
    for (int i = 0; i < _class->methods_count; ++i) {
        Method method = _class->methods[i];
        if (strcmp(method->name, name) == 0 && strcmp(method->descriptor, descriptor) == 0) {
            return method;
        }
    }

    return NULL;
}



Field_T Class_lookupField(Class_T _class, char *name, char *descriptor) {
    for (int i = 0; i < _class->fields_count; ++i) {
        Field field = _class->fields[i];
        if (strcmp(field->name, name) == strcmp(field->descriptor, descriptor) == 0) {
            return field;
        }
    }

    for (int j = 0; j < _class->interface_count; ++j) {
        Field field = lookupField(_class->interface_class[j], name, descriptor);
        if (field != NULL) {
            return field;
        }
    }

    if (_class->super_class != NULL) {
        return lookupField(_class->super_class, name, descriptor);
    }

    return NULL;
}

Field_T *newFields(Class_T _class, struct ClassFile *class_file) {
    u2 fields_count = class_file->fields_count;
    Field_T *fields = (Field_T*) malloc(sizeof(struct Field) * fields_count);
    //
    for (int i = 0; i < fields_count; ++i) {
        fields[i]->_class = _class;
        copyFieldInfo(&class_file->fields[i], fields[i], class_file->constant_pool_info);
    }

    return fields;
}

Method_T *newMethods(Class_T _class, struct ClassFile *class_file) {
    u2 count = class_file->methods_count;
    Method_T *methods = (Method_T*) malloc(sizeof(struct Method) * count);
    for (int i = 0; i < count; ++i) {
        methods[i]->_class = _class;
        copyMethodInfo(&class_file->methods[i], methods[i], class_file->constant_pool_info);
        // TODO
        if (isNative(methods[i]->access_flags)) {
            // TODO
        }
    }

    return methods;
}


void copyFieldInfo(struct MemberInfo *field_info, Field_T field, struct ConstantPoolInfo *constant_pool_info) {
    field->access_flags = field_info->access_flags;
    field->name = memberName(field_info, constant_pool_info);
    field->descriptor = descriptor(field_info, constant_pool_info);
    struct AttributeInfo *attribute_info = constantValueAttribute(field_info, constant_pool_info);
    if (attribute_info != NULL) {
        field->const_value_index = attribute_info->info.constant_value.constant_value_index;
    }
}

void copyMethodInfo(struct MemberInfo *method_info, Method_T method, struct ConstantPoolInfo *constant_pool_info) {
    method->access_flags = method_info->access_flags;
    method->name = memberName(method_info, constant_pool_info);
    method->descriptor = descriptor(method_info, constant_pool_info);
    struct AttributeInfo *attribute_info = codeAttribute(method_info, constant_pool_info);
    if (attribute_info != NULL) {
        method->code = attribute_info->info.code.code;
        method->max_locals = attribute_info->info.code.max_locals;
        method->max_stack = attribute_info->info.code.max_stack;
        method->code_length = attribute_info->info.code.code_length;
    }
}

Class_T Class_new(struct ClassFile *class_file) {
    Class_T _class = (Class_T) malloc(sizeof(struct Class));
    _class->access_flags = class_file->access_flags;
    _class->name = className(class_file->this_class, class_file->constant_pool_info);
    _class->super_class_name = className(class_file->super_class, class_file->constant_pool_info);
    // interfaces_count
    _class->constant_pool_count = class_file->constant_pool_count;
    _class->constant_pool = ConstantPool_new(_class, class_file);
    _class->fields = newFields(_class, class_file);
    _class->methods = newMethods(_class, class_file);
    return _class;
}


char *Class_packageName(Class_T _this) {
    // java/lang/Object
    char *c = strrchr(_this->name, '/');
    if (c != NULL) {
        // /Object
        c++;
        // Object
        return c;
    }
    return NULL;
}

void *Class_loader(Class_T _class) {
    return _class->loader;
}

Class *Class_interface(Class_T _class) {
    return _class->interface_class;
}

int Class_isAccessibleTo(Class_T _this, Class_T other) {
    return isPublic(_this->access_flags) || strcmp(Class_packageName(_this), Class_packageName(other)) == 0;
}

int Class_isSubInterfaceOf(Class_T _this, Class_T other) {
    for (int i = 0; i < _this->interface_count; ++i) {
        Class_T iface = _this->interface_class[i];
        if (iface == other || Class_isSubInterfaceOf(iface, other)) {
            return 1;
        }
    }

    return 0;
}

int Class_isImplements(Class_T _this, Class_T other) {
    Class_T c = _this;
    for (c = _this; c != NULL ; c = c->super_class) {
        for (int i = 0; i < c->interface_count; ++i) {
            struct Class *iface = c->interface_class[i];
            if (other == iface && Class_isSubInterfaceOf(other, iface)) {
                return 1;
            }
        }
    }
    return 0;
}

int Class_isSubClassOf(Class_T _this, Class_T other) {
    Class_T c = _this->super_class;

    while (c != NULL) {
        if (c == other) {
            return 1;
        } else {
            c = c->super_class;
        }
    }

    return 0;
}

int Class_isSuperClassOf(Class_T _this, Class_T other) {
    return Class_isSubClassOf(other, _this);
}

int Class_isInterface(Class_T _class) {
    return isInterface(_class->access_flags);
}

int Field_isAccessibleTo(Field_T _this, Class_T other) {
    if (isPublic(_this->access_flags)) {
        return 1;
    }

    if (isProtected(_this->access_flags)) {
        return _this->_class == other || Class_isSubClassOf(_this->_class, other) ||
               strcmp(Class_packageName(_this->_class), Class_packageName(other)) == 0;
    }

    if (!isPrivate(_this->access_flags)) {
        return strcmp(Class_packageName(_this->_class), Class_packageName(other)) == 0;
    }

    return _this->_class == other;
}


int Method_isAccessibleTo(Method_T _this, Class_T other) {
    if (isPublic(_this->access_flags)) {
        return 1;
    }

    if (isProtected(_this->access_flags)) {
        return _this->_class == other || Class_isSubClassOf(_this->_class, other) ||
               strcmp(Class_packageName(_this->_class), Class_packageName(other)) == 0;
    }

    if (!isPrivate(_this->access_flags)) {
        return strcmp(Class_packageName(_this->_class), Class_packageName(other)) == 0;
    }

    return _this->_class == other;
}


u4 Method_maxLocals(Method_T _this) {
    return _this->max_locals;
}

u4 Method_maxStack(Method_T _this) {
    return _this->max_stack;
}


static Method_T Class_getStaticMethod(Class_T _class, char *name, char *descriptor) {
    return NULL;
}

Method_T Class_getClinitMethod(Class_T _class) {
    return Class_getStaticMethod(_class, "<clinit>", "()V");
}


Method_T Class_getMainMethod(Class_T _class) {

    for (int i = 0; i < _class->methods_count; ++i) {
        Method method = _class->methods[i];

        if (strcmp("main", method->name) == 0) {
            return method;
        }
    }

    return NULL;
}


Method_T Class_lookupInterfaceMethod(Class_T _class, char *name, char *descriptor) {
    for (int i = 0; i < _class->methods_count; ++i) {
        Method method = _class->methods[i];
        if (strcmp(method->name, name) == 0 && strcmp(method->descriptor, descriptor) == 0) {
            return method;
        }
    }

    return lookupMethodInInterfaces(_class->interface_class, _class->interface_count, name, descriptor);
}


Method_T lookupMethodInInterfaces(Class_T *interfaces, u2 count, char *name, char *descriptor) {
    struct Method *method;

    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < interfaces[i]->methods_count; ++j) {
            method = &interfaces[i]->methods[j];
            if (strcmp(method->name, name) == 0 && strcmp(method->descriptor, descriptor) == 0) {
                return method;
            }
        }

        method = lookupMethodInInterfaces(interfaces[i]->interface_class, interfaces[i]->interface_count, name,
                                          descriptor);
        if (method != NULL) {
            return method;
        }
    }

    return NULL;
}
