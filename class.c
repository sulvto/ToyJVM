//
// Created by sulvto on 18-5-1.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "type.h"
#include "flags.h"
#include "class.h"
#include "IS.h"
#include "classref.h"
#include "methoddescriptor.h"

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

struct ExceptionHandler {
    int start_pc;
    int end_pc;
    int handler_pc;
    // ClassRef
    struct ClassRef *catch_type;
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
    u4      exception_table_count;
    struct ExceptionHandler *exception_table;
};

struct Class_T {
    u2                      access_flags;
    char                    *name;
    char                    *super_class_name;
    char                    **interface_name;
    u2                      constant_pool_count;
    void                    *constant_pool;
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


static char *getArrayClassName(char *class_name);

static void injectCodeAttribute(Method_T, char*);

static void Method_calcArgCount(Method_T _this, struct MethodDescriptor *method_descriptor);


void copyFieldInfo(struct MemberInfo *field_info, Field_T field, struct ConstantPoolInfo *constant_pool_info) {
    field->access_flags = field_info->access_flags;

    char *name = memberName(field_info, constant_pool_info);
    field->name = malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(field->name, name);

    char *desc = descriptor(field_info, constant_pool_info);
    field->descriptor = malloc(sizeof(char) * (strlen(desc) + 1));
    strcpy(field->descriptor, desc);

    struct AttributeInfo *attribute_info = constantValueAttribute(field_info, constant_pool_info);
    if (attribute_info != NULL) {
        field->const_value_index = attribute_info->info->constant_value->constant_value_index;
    }
}

void copyMethodInfo(struct MemberInfo *method_info, Method_T method, struct ConstantPoolInfo *constant_pool_info) {
    method->access_flags = method_info->access_flags;
    char *name = memberName(method_info, constant_pool_info);
    char *desc = descriptor(method_info, constant_pool_info);
    method->name = malloc(sizeof(char) * strlen(name));
    method->descriptor = malloc(sizeof(char) * strlen(desc));
    strcpy(method->name, name);
    strcpy(method->descriptor, desc);

    struct AttributeInfo *attribute_info = codeAttribute(method_info, constant_pool_info);
    if (attribute_info != NULL) {
        method->code = attribute_info->info->code->code;
        method->max_locals = attribute_info->info->code->max_locals;
        method->max_stack = attribute_info->info->code->max_stack;
        method->code_length = attribute_info->info->code->code_length;
    }
}

Field_T *newFields(Class_T _class, struct ClassFile *class_file) {
    u2 fields_count = class_file->fields_count;
    Field_T *fields = malloc(fields_count * sizeof(Field_T));

    for (int i = 0; i < fields_count; ++i) {
        fields[i] = malloc(sizeof(Field_T));
        fields[i]->_class = _class;
        copyFieldInfo(&class_file->fields[i], fields[i], class_file->constant_pool_info);
    }

    return fields;
}

Method_T newMethod(Class_T _class, struct ClassFile *class_file, struct MemberInfo       *member_info) {
    Method_T method = malloc(sizeof(Method_T));
    method ->_class = _class;
    copyMethodInfo(member_info, method, class_file->constant_pool_info);
    struct MethodDescriptor *method_descriptor = MethodDescriptor_parse(method->descriptor);
    Method_calcArgCount(method, method_descriptor);
    if (Method_isNative(method)) {
        injectCodeAttribute(method, method_descriptor->return_type);
    }
    return method;
}

static void Method_calcArgCount(Method_T _this, struct MethodDescriptor *method_descriptor) {

    for (int i = 0; i < method_descriptor->parameter_type_count; ++i) {
        char *str = method_descriptor->parameter_types[i];
        _this->arg_count++;

        if (strcmp(str, "J") || strcmp(str, "D")) {
            _this->arg_count++;
        }
    }
}

Method_T *newMethods(Class_T _class, struct ClassFile *class_file) {
    u2 count = class_file->methods_count;
    Method_T *methods = (Method_T *) malloc(sizeof(struct Method) * count);

    for (int i = 0; i < count; ++i) {
        methods[i] = newMethod(_class, class_file, &class_file->methods[i]);
    }

    return methods;
}

static void injectCodeAttribute(Method_T _this, char *return_type) {
    _this->max_stack = 4;
    _this->max_locals = _this->arg_count;
    _this->code = (u1 *) malloc(sizeof(u1) * 2);

    _this->code[0] = INVOKENATIVE;

    switch (return_type[0]) {
        case 'V': _this->code[1] = RETURN;  break;
        case 'D': _this->code[1] = DRETURN; break;
        case 'F': _this->code[1] = FRETURN; break;
        case 'J': _this->code[1] = LRETURN; break;
        case 'L':
        case '[': _this->code[1] = ARETURN; break;
        default: _this->code[1] = IRETURN;  break;
    }
}

Class_T Class_new(struct ClassFile *class_file) {
    Class_T _class = (Class_T) malloc(sizeof(struct Class));
    _class->access_flags = class_file->access_flags;
    _class->name = className(class_file->this_class, class_file->constant_pool_info);
    if (class_file->super_class != 0) {
        _class->super_class_name = className(class_file->super_class,
                                             class_file->constant_pool_info);
    }
    // interfaces_count
    _class->interface_count = class_file->interfaces_count;
    _class->constant_pool_count = class_file->constant_pool_count;

    _class->fields_count = class_file->fields_count;
    _class->fields = newFields(_class, class_file);
    _class->methods_count = class_file->methods_count;
    _class->methods = newMethods(_class, class_file);
    return _class;
}

Class_T Class_newArrayClass(u2 access_flags,char *name, void *loader, Class_T super_class, Class_T cloneable_class, Class_T serializable_class) {
    Class _class = (Class_T) malloc(sizeof(struct Class));

    _class->access_flags = access_flags;
    _class->name = name;
    _class->loader = loader;
    _class->init_started = 1;
    _class->super_class = super_class;
    _class->super_class_name = super_class->name;
    _class->interface_count = 2;
    _class->interface_class = (Class *) malloc(2 * sizeof(struct Class));
    _class->interface_class[0] = cloneable_class;
    _class->interface_class[1] = serializable_class;
    return _class;
}

int Class_initStarted(Class_T _this) {
    return _this->init_started;
}

void Class_init(Class_T _this) {
    _this->init_started = 1;
}

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
        Field field = Class_lookupField(_class->interface_class[j], name, descriptor);
        if (field != NULL) {
            return field;
        }
    }

    if (_class->super_class != NULL) {
        return Class_lookupField(_class->super_class, name, descriptor);
    }

    return NULL;
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

char *Class_name(Class_T _this) {
    return _this->name;
}

u2 Class_fieldsCount(Class_T _this) {
    return _this->fields_count;
}

Field_T *Class_fields(Class_T _this) {
    return _this->fields;
}

void Class_setInterfaceSlotCount(Class_T _this, u4 interface_slot_count) {
    _this->interface_slot_count = interface_slot_count;
}

u4 Class_getInterfaceSlotCount(Class_T _this) {
    return _this->interface_slot_count;
}

void Class_setLoader(Class_T _this, void *loader) {
    _this->loader = loader;
}

void Class_setSuperClass(Class_T _this, Class_T super_class) {
    _this->super_class = super_class;
}

Class_T Class_getSuperClass(Class_T _this) {
    return _this->super_class;
}

char *Class_superClassName(Class_T _this) {
    return _this->super_class_name;
}

void *Class_getConstantPool(Class_T _this) {
    return _this->constant_pool;
}

void Class_setConstantPool(Class_T _this, void *constant_pool) {
    _this->constant_pool = constant_pool;
}

Slots Class_getStaticVars(Class_T _this) {
    return _this->static_vars;
}

void Class_setStaticVars(Class_T _this, Slots static_vars) {
    _this->static_vars = static_vars;
}

u4 Class_staticSlotCount(Class_T _this) {
    return _this->static_slot_count;
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

int Class_isInterface(Class_T _this) {
    return isInterface(_this->access_flags);
}

int Class_isAbstract(Class_T _this) {
    return isAbstract(_this->access_flags);
}

int Class_isSuper(Class_T _this) {
    return isSuper(_this->access_flags);
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

int Field_isFinal(Field_T _this) {
    return isFinal(_this->access_flags);
}

int Field_isStatic(Field_T _this) {
    return isStatic(_this->access_flags);
}

u2 Field_constValueIndex(Field_T _this) {
    return _this->const_value_index;
}

char *Field_descriptor(Field_T _this) {
    return _this->descriptor;
}

u4 Field_getSlotId(Field_T _this) {
    return _this->slot_id;
}

void Field_setSlotId(Field_T _this, u4 slot_id) {
    _this->slot_id = slot_id;
}

Class_T Field_class(Field_T _this) {
    return _this->_class;
}

int Method_findExceptionHandler(Method_T _this, Class_T ex_class, int pc) {
    for (int i = 0; i < _this->exception_table_count; ++i) {
        struct ExceptionHandler handler = _this->exception_table[i];
        if (pc >= handler.start_pc && pc < handler.end_pc) {
            if(handler.catch_type == NULL) {
                // catch all
                return handler.handler_pc;
            }

            Class catch_class = ClassRef_resolvedClass(handler.catch_type);

            if (catch_class == ex_class || Class_isSuperClassOf(catch_class, ex_class)) {
                return handler.handler_pc;
            }
        }
    }

    return -1;
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

int Method_isStatic(Method_T _this) {
    return isStatic(_this->access_flags);
}

int Method_isNative(Method_T _this) {
    return isNative(_this->access_flags);
}

int Method_isAbstract(Method_T _this) {
    return isAbstract(_this->access_flags);
}

int Method_isPrivate(Method_T _this) {
    return isPrivate(_this->access_flags);
}

int Method_isProtected(Method_T _this) {
    return isProtected(_this->access_flags);
}

int Method_isPublic(Method_T _this) {
    return isPublic(_this->access_flags);
}

u4 Method_argCount(Method_T _this) {
    return _this->arg_count;
}

u4 Method_maxLocals(Method_T _this) {
    return _this->max_locals;
}

u4 Method_maxStack(Method_T _this) {
    return _this->max_stack;
}

int Method_namecmp(Method_T _this, const char *name) {
    return strcmp(_this->name, name);
}

char *Method_name(Method_T _this) {
    return _this->name;
}

char *Method_descriptor(Method_T _this) {
    return _this->descriptor;
}

int Method_classcmp(Method_T _this, Class_T _class) {
    return _this->_class == _class;
}

Class_T Method_class(Method_T _this) {
    return _this->_class;
}

u1 *Method_code(Method_T _this) {
    return _this->code;
}

static Method_T Class_getStaticMethod(Class_T _class, char *name, char *descriptor) {
    for (int i = 0; i < _class->methods_count; ++i) {
        Method method = _class->methods[i];
        if (Method_isStatic(method) &&
            strcmp(method->name, name) == 0 &&
            strcmp(method->descriptor, descriptor) == 0) {

            return method;
        }
    }
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
            method = interfaces[i]->methods[j];
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