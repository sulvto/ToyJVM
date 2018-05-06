//
// Created by sulvto on 18-5-1.
//

#include <stdlib.h>
#include <string.h>
#include "class.h"
#include "rtda.h"
#include "classreader.h"
#include "flags.h"
#include "map.h"

struct Field *lookupField(struct Class *_class, char *name, char *descriptor);

struct Method *lookupMethodInInterfaces(struct Class **interfaces, u2 count, char *name, char *descriptor);

struct Method *lookupMethod(struct Class *_class, char *name, char *descriptor);

struct Method *lookupInterfaceMethod(struct Class *_class, char *name, char *descriptor);

struct Class *ClassLoader_defineClass(struct ClassLoader *loader, struct s_class_data *class_data);

struct Class *ClassLoader_loadNonArrayClass(struct ClassLoader *loader, const char *name);

int Class_isAccessibleTo(struct Class *_this, struct Class *_other);

int Method_isAccessibleTo(struct Method *_this, struct Class *_other);

int Field_isAccessibleTo(struct Field *_this, struct Class *_other);





int isPublic      (u2 access_flags) {
    return ACC_PUBLIC & access_flags == 0;
}
int isPrivate     (u2 access_flags) {
    return ACC_PRIVATE & access_flags == 0;
}
int isProtected   (u2 access_flags) {
    return ACC_PROTECTED & access_flags == 0;
}
int isStatic      (u2 access_flags) {
    return ACC_STATIC & access_flags == 0;
}
int isFinal       (u2 access_flags) {
    return ACC_FINAL & access_flags == 0;
}
int isSuper       (u2 access_flags) {
    return ACC_SUPER & access_flags == 0;
}
int isSynchronized   (u2 access_flags) {
    return ACC_SYNCHRONIZED & access_flags == 0;
}
int isVolatile    (u2 access_flags) {
    return ACC_VOLATILE & access_flags == 0;
}
int isBridge      (u2 access_flags) {
    return ACC_BRIDGE & access_flags == 0;
}
int isTransient   (u2 access_flags) {
    return ACC_TRANSIENT & access_flags == 0;
}
int isVarargs     (u2 access_flags) {
    return ACC_VARARGS & access_flags == 0;
}
int isNative      (u2 access_flags) {
    return ACC_NATIVE & access_flags == 0;
}
int isInterface   (u2 access_flags) {
    return ACC_INTERFACE & access_flags == 0;
}
int isAbstract    (u2 access_flags) {
    return ACC_ABSTRACT & access_flags == 0;
}
int isStrict      (u2 access_flags) {
    return ACC_STRICT & access_flags == 0;
}
int isSynthetic   (u2 access_flags) {
    return ACC_SYNTHETIC & access_flags == 0;
}
int isAnnotation  (u2 access_flags) {
    return ACC_ANNOTATION & access_flags == 0;
}
int isEnum        (u2 access_flags) {
    return ACC_ENUM & access_flags == 0;
}


void verify(struct Class *_class) {
    prepare(_class);
}

void prepare(struct Class *_class) {
    calcInstanceFieldSlotIds(_class);
    calcStaticFieldSlotIds(_class);
    allocAndInitStaticVars(_class);
}

u4 isLongOrDouble(struct Field *field) {
    return (strcmp("J", field->descriptor) == 0) || (strcmp("D", field->descriptor) == 0);
}


void calcInstanceFieldSlotIds(struct Class *_class) {
    u4 slot_id = 0;
    if (_class->super_class != NULL) {
        slot_id = _class->super_class->interface_slot_count;
    }

    for (int i = 0; i < _class->fields_count; ++i) {
        struct Field *field = &_class->fields[i];
        if (field->access_flags != ACC_STATIC) {
            field->slot_id = slot_id;
            slot_id++;
            if (isLongOrDouble(field)) {
                slot_id++;
            }
        }
    }

    _class->interface_slot_count = slot_id;
}

void calcStaticFieldSlotIds(struct Class *_class) {
    u4 slot_id = 0;

    for (int i = 0; i < _class->fields_count; ++i) {
        struct Field *field = &_class->fields[i];
        if (field->access_flags == ACC_STATIC) {
            field->slot_id = slot_id;
            slot_id++;
            if (isLongOrDouble(field)) {
                slot_id++;
            }
        }
    }

    _class->interface_slot_count = slot_id;
}

void allocAndInitStaticVars(struct Class *_class) {
    _class->static_vars = newSlots(_class->static_slot_count);
    for (int i = 0; i < _class->fields_count; ++i) {
        struct Field *field = &_class->fields[i];
        if (field->access_flags == ACC_STATIC && field->access_flags == ACC_FINAL) {
            initStaticFinalVar(_class, field);
        }
    }
}

void initStaticFinalVar(struct Class *_class, struct Field *field) {
    struct Slots *slots = _class->static_vars;
    struct ConstantPool *constantPool = _class->constant_pool;
    u4 slot_id = field->slot_id;
    if (field->const_value_index > 0) {
        if (strcmp(field->descriptor, "Z") == 0) {
        } else if (strcmp(field->descriptor, "Z") == 0) {
        } else if (strcmp(field->descriptor, "B") == 0) {
        } else if (strcmp(field->descriptor, "C") == 0) {
        } else if (strcmp(field->descriptor, "S") == 0) {
        } else if (strcmp(field->descriptor, "I") == 0) {
            int value = constantPool->constants[field->const_value_index].int_value;
            setInt(field->const_value_index, value, slots);
        } else if (strcmp(field->descriptor, "J") == 0) {
            long value = constantPool->constants[field->const_value_index].long_value;
            setLong(field->const_value_index, value, slots);
        } else if (strcmp(field->descriptor, "F") == 0) {
            float value = constantPool->constants[field->const_value_index].float_value;
            setFloat(field->const_value_index, value, slots);
        } else if (strcmp(field->descriptor, "D") == 0) {
            double value = constantPool->constants[field->const_value_index].double_value;
            setDouble(field->const_value_index, value, slots);
        } else if (strcmp(field->descriptor, "Ljava/lang/String") == 0) {
            char *string = constantPool->constants[field->const_value_index].string;
//            set
            printf("Ljava/lang/String\n");
        } else {
            // TODO
            printf("initStaticFinalVar else\n");
        }
    }
}

void link(struct Class *_class) {
    verify(_class);
    prepare(_class);
}
struct ConstantPool *ConstantPool_free(struct ConstantPool *constant_pool) {
    // TODO
}

struct ConstantPool *ConstantPool_new(struct Class *_class, struct ClassFile *class_file) {
    u2 count = class_file->constant_pool_count;

    struct ConstantPool *constant_pool = (struct ConstantPool *) malloc(sizeof(struct ConstantPool));;
    constant_pool->_class = _class;
    constant_pool->size = count;
    constant_pool->constants = (union Constant *) malloc(sizeof(union Constant) * count);
    for (int i = 0; i < count; ++i) {
        struct ConstantPoolInfo constant_pool_info = class_file->constant_pool_info[i];
        switch (constant_pool_info.tag) {
            case CONSTANT_Class: {
                struct ClassRef *class_ref = (struct ClassRef *) malloc(sizeof(struct ClassRef));

                class_ref->constant_pool = constant_pool;
                class_ref->_class = NULL;
                className(class_file, class_file->constant_pool_info, class_ref->class_name);
                constant_pool->constants[i].class_ref = class_ref;
                break;
            }
            case CONSTANT_Methodref: {
                struct MethodRef *method_ref = (struct MethodRef *) malloc(sizeof(struct MethodRef));
                method_ref->_class = NULL;
                method_ref->method = NULL;
                method_ref->constant_pool = constant_pool;
                // name and type
                struct CONSTANT_NameAndType_info nameAndType_info = ConstantPoolInfo_getNameAndType(
                        class_file->constant_pool_info,
                        constant_pool_info.info.methodref_info.name_and_type_index);
                ConstantPoolInfo_getUtf8String(class_file->constant_pool_info, nameAndType_info.name_index,
                                               method_ref->name);
                ConstantPoolInfo_getUtf8String(class_file->constant_pool_info, nameAndType_info.descriptor_index,
                                               method_ref->descriptor);

                className(class_file->this_class, class_file->constant_pool_info, method_ref->class_name);
                constant_pool->constants[i].method_ref = method_ref;
                break;
            }
            case CONSTANT_Fieldref: {
                struct FieldRef *field_ref = (struct FieldRef *) malloc(sizeof(struct FieldRef));
                field_ref->_class = NULL;
                field_ref->field = NULL;
                field_ref->constant_pool = constant_pool;
                // name and type
                struct CONSTANT_NameAndType_info nameAndType_info = ConstantPoolInfo_getNameAndType(
                        class_file->constant_pool_info,
                        constant_pool_info.info.fieldref_info.name_and_type_index);
                ConstantPoolInfo_getUtf8String(class_file->constant_pool_info, nameAndType_info.name_index,
                                               field_ref->name);
                ConstantPoolInfo_getUtf8String(class_file->constant_pool_info, nameAndType_info.descriptor_index,
                                               field_ref->descriptor);

                className(class_file->this_class, class_file->constant_pool_info, field_ref->class_name);

                constant_pool->constants[i].field_ref = field_ref;
                break;
            }
            case CONSTANT_InterfaceMethodref: {
                // TODO
                struct InterfaceMethodRef *interface_method_ref = (struct InterfaceMethodRef *) malloc(sizeof(struct InterfaceMethodRef));;
                interface_method_ref->_class = NULL;
                interface_method_ref->method = NULL;
                interface_method_ref->constant_pool = constant_pool;
                // name and type
                struct CONSTANT_NameAndType_info nameAndType_info = ConstantPoolInfo_getNameAndType(
                        class_file->constant_pool_info,
                        constant_pool_info.info.interfaceMethodref_info.name_and_type_index);
                ConstantPoolInfo_getUtf8String(class_file->constant_pool_info, nameAndType_info.name_index,
                                               interface_method_ref->name);
                ConstantPoolInfo_getUtf8String(class_file->constant_pool_info, nameAndType_info.descriptor_index,
                                               interface_method_ref->descriptor);

                className(class_file->this_class, class_file->constant_pool_info, interface_method_ref->class_name);

                constant_pool->constants[i].interface_method_ref = interface_method_ref;
                break;
            }
            default:
                // TODO
                break;
        }
    }
    return constant_pool;
}

struct Field *newFields(struct Class *_class, struct ClassFile *class_file) {
    u2 fields_count = class_file->fields_count;
    struct Field *fields = (struct Field *) malloc(sizeof(struct Field) * fields_count);
    //
    for (int i = 0; i < fields_count; ++i) {
        fields[i]._class = _class;
        copyFieldInfo(&class_file->attributes[i], &fields[i], class_file->constant_pool_info);
    }
}

void copyFieldInfo(struct MemberInfo *field_info, struct Field *field, struct ConstantPoolInfo *constant_pool_info) {
    field->access_flags = field_info->access_flags;
    memberName(field_info, constant_pool_info, field->name);
    descriptor(field_info, constant_pool_info, field->descriptor);
    struct AttributeInfo *attribute_info = constantValueAttribute(field_info, constant_pool_info);
    if (attribute_info != NULL) {
        field->const_value_index = attribute_info->info.constant_value.constant_value_index;
    }
}

struct Class *newClass(struct ClassFile *class_file) {
    struct Class *_class = (struct Class *) malloc(sizeof(struct Class));

    _class->access_flags = class_file->access_flags;

    className(class_file->this_class, class_file->constant_pool_info, &_class->name);
    className(class_file->super_class, class_file->constant_pool_info, &_class->super_class_name);
    // interfaces_count
    _class->constant_pool_count = class_file->constant_pool_count;
    _class->constant_pool = ConstantPool_new(_class, class_file);
    _class->fields = newFields(_class, class_file);
    _class->methods = newMethods(_class, class_file);
}


struct ClassLoader *ClassLoader_new() {
    struct ClassLoader *loader = (struct ClassLoader *) malloc(sizeof(struct ClassLoader));
    loader->class_map = Map_new(1000, NULL, NULL);
    return loader;
}

struct ClassLoader *ClassLoader_free(struct ClassLoader *_this) {

}

struct Class *ClassLoader_loadClass(struct ClassLoader *loader, const char *name) {
    struct Class *_class = (struct Class *) Map_get(loader->class_map, name);
    if (_class != NULL) {
        return _class;
    }
    return ClassLoader_loadNonArrayClass(loader, name);
}

struct Class *ClassLoader_loadNonArrayClass(struct ClassLoader *loader, const char *name) {
    struct s_class_data class_data = readClassFile(name);
    struct Class *_class = ClassLoader_defineClass(loader, &class_data);
    link(_class);
    printf("[Loaded %s from %s]\n", name, "from");
    return _class;
}

void resolveSuperClass(struct Class *_class) {
    if (strcmp(_class->name, "java/lang/Object") != 0) {
        _class->super_class = ClassLoader_loadClass(_class->loader, _class->super_class_name);
    } else {
        _class->super_class = NULL;
    }
}

void resolveInterfaces(struct Class *_class) {

}

struct Class *parseClass(struct s_class_data *class_data) {
    struct ClassFile class_file = parseClassContent(class_data);
    return newClass(&class_file);
}

struct Class *ClassLoader_defineClass(struct ClassLoader *loader, struct s_class_data *class_data) {
    struct Class *_class = parseClass(class_data);
    _class->loader = loader;
    resolveSuperClass(_class);
    resolveInterfaces(_class);
    Map_put(loader->class_map, _class->name, _class);
    return _class;
}

struct Method *resolvedInterfaceMethod(struct InterfaceMethodRef *interface_method_ref) {
    if (interface_method_ref->method == NULL) {
        resolveInterfaceMethodRef(interface_method_ref);
    }

    return interface_method_ref->method;
}

void resolveInterfaceMethodRef(struct InterfaceMethodRef *interface_method_ref) {
    struct Class *d = interface_method_ref->constant_pool->_class;
    struct Class *c;
    resolvedClass(interface_method_ref, c);

    if (!isInterface(c->access_flags)) {
        printf("java.lang.IncompatibleClassChangeError");
    }

    struct Method *method = lookupInterfaceMethod(c, interface_method_ref->name, interface_method_ref->descriptor);

    if (method == NULL) {
        printf("java.lang.NoSuchMethodError");
    }

    if (!Method_isAccessibleTo(method, d)) {
        printf("java.lang.IllegalAccessError");
    }

    interface_method_ref->method = method;
}

struct Method *lookupInterfaceMethod(struct Class *_class, char *name, char *descriptor) {
    for (int i = 0; i < _class->methods_count; ++i) {
        if (strcmp(_class->methods[i].name, name) == 0 && strcmp(_class->methods[i].descriptor, descriptor) == 0) {
            return &_class->methods[i];
        }
    }

    return lookupMethodInInterfaces(_class->interface_class, _class->interface_count, name, descriptor);
}

struct Method *resolvedMethod(struct MethodRef *method_ref) {
    if (method_ref->method == NULL) {
        resolveMethodRef(method_ref);
    }

    return method_ref->method;
}

void resolveMethodRef(struct MethodRef *method_ref) {
    struct Class *d = method_ref->constant_pool->_class;
    struct Class *c;
    resolvedClass(method_ref, c);

    if (isInterface(c->access_flags)) {
        printf("java.lang.IncompatibleClassChangeError");
    }

    struct Method *method = lookupMethod(c, method_ref->name, method_ref->descriptor);

    if (method == NULL) {
        printf("java.lang.NoSuchMethodError");
    }

    if (!Method_isAccessibleTo(method, d)) {
        printf("java.lang.IllegalAccessError");
    }

    method_ref->method = method;
}

struct Method *lookupMethod(struct Class *_class, char *name, char *descriptor) {
    struct Method *method = lookupMethodInClass(_class, name, descriptor);
    if (method == NULL) {
        method = lookupMethodInInterfaces(_class->interface_class, _class->interface_count, name, descriptor);
    }

    return method;
}

struct Method *lookupMethodInClass(struct Class *_class, char *name, char *descriptor) {
    for (int i = 0; i < _class->methods_count; ++i) {
        if (strcmp(_class->methods[i].name, name) == 0 && strcmp(_class->methods[i].descriptor, descriptor) == 0) {
            return &_class->methods[i];
        }
    }

    return NULL;
}

struct Method *lookupMethodInInterfaces(struct Class **interfaces, u2 count, char *name, char *descriptor) {
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


struct Field *resolvedField(struct FieldRef *field_ref) {
    if (field_ref->field == NULL) {
        resolveFieldRef(field_ref);
    }

    return field_ref->field;
}

void resolveFieldRef(struct FieldRef *field_ref) {
    struct Class *d = field_ref->constant_pool->_class;
    struct Class *c;
    resolvedClass(field_ref, c);
    struct Field *field = lookupField(c, field_ref->name, field_ref->descriptor);

    if (field == NULL) {
        printf("java.lang.NoSuchFieldError");
    }

    if (!Field_isAccessibleTo(field, d)) {
        printf("java.lang.IllegalAccessError");
    }

    field_ref->field = field;
}

struct Field *lookupField(struct Class *_class, char *name, char *descriptor) {
    for (int i = 0; i < _class->fields_count; ++i) {
        if (strcmp(_class->fields[i].name, name) == strcmp(_class->fields[i].descriptor, descriptor) == 0) {
            return &_class->fields[i];
        }
    }

    for (int j = 0; j < _class->interface_count; ++j) {
        struct Field *field = lookupField(_class->interface_class[j], name, descriptor);
        if (field != NULL) {
            return field;
        }
    }

    if (_class->super_class != NULL) {
        return lookupField(_class->super_class, name, descriptor);
    }

    return NULL;
}


char *Class_packageName(struct Class *_this) {
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

int Class_isAccessibleTo(struct Class *_this, struct Class *_other) {
    return isPublic(_this->access_flags) || strcmp(Class_packageName(_this), Class_packageName(_other)) == 0;
}

int Class_isSubInterfaceOf(struct Class *_this, struct Class *_other) {
    for (int i = 0; i < _this->interface_count; ++i) {
        struct Class *iface = _this->interface_class[i];
        if (iface == _other || Class_isSubInterfaceOf(iface, _other)) {
            return 1;
        }
    }

    return 0;
}

int Class_isImplements(struct Class *_this, struct Class *_other) {
    struct Class *c = _this;
    for (c = _this; c != NULL ; c = c->super_class) {
        for (int i = 0; i < c->interface_count; ++i) {
            struct Class *iface = c->interface_class[i];
            if (_other == iface && Class_isSubInterfaceOf(_other, iface)) {
                return 1;
            }
        }
    }
    return 0;
}

int Class_isSubClassOf(struct Class *_this, struct Class *_other) {
    struct Class *c = _this->super_class;

    while (c != NULL) {
        if (c == _other) {
            return 1;
        } else {
            c = c->super_class;
        }
    }

    return 0;
}

int Class_isSuperClassOf(struct Class *_this, struct Class *_other) {
    return Class_isSubClassOf(_other, _this);
}


int Object_isInterfaceOf(struct Object *_this, struct Class *_other) {
    struct Class *s = _this->_class;
    struct Class *t = _other;

    if (s == t) {
        return 1;
    }

    if (isInterface(s)) {
        if (isInterface(t)) {
            return s == t || Class_isSubInterfaceOf(s, t);
        } else {
            return strcmp(t->name, "java/lang/Object") == 0;
        }
    } else {
        if (isInterface(t)) {
            return Class_isImplements(s, t);
        } else {
            return s == t || Class_isSubClassOf(s, t);
        }
    }
}

int Field_isAccessibleTo(struct Field *_this, struct Class *_other) {
    if (isPublic(_this->access_flags)) {
        return 1;
    }

    if (isProtected(_this->access_flags)) {
        return _this->_class == _other || Class_isSubClassOf(_this->_class, _other) ||
               strcmp(Class_packageName(_this->_class), Class_packageName(_other)) == 0;
    }

    if (!isPrivate(_this->access_flags)) {
        return strcmp(Class_packageName(_this->_class), Class_packageName(_other)) == 0;
    }

    return _this->_class == _other;
}


int Method_isAccessibleTo(struct Method *_this, struct Class *_other) {
    if (isPublic(_this->access_flags)) {
        return 1;
    }

    if (isProtected(_this->access_flags)) {
        return _this->_class == _other || Class_isSubClassOf(_this->_class, _other) ||
               strcmp(Class_packageName(_this->_class), Class_packageName(_other)) == 0;
    }

    if (!isPrivate(_this->access_flags)) {
        return strcmp(Class_packageName(_this->_class), Class_packageName(_other)) == 0;
    }

    return _this->_class == _other;
}

struct Object *newObject(struct Class *_class) {
    struct Object *object = (struct Object *) malloc(sizeof(struct Object));
    object->_class = _class;
    object->fields = newSlots(_class->interface_slot_count);
}

void initSuperClass(struct Thread *thread, struct Class *_class) {

}

void initClass(struct Thread *thread, struct Class *_class) {
    _class->init_started = 1;
    scheduleClinit(thread, _class);
    initSuperClass(thread, _class);
}

struct Method *getStaticMethod(struct Class *_class, char *name, char *descriptor) {

}

struct Method *getClinitMethod(struct Class *_class) {
    return getStaticMethod(_class, "<clinit>", "()V");
}

void scheduleClinit(struct Thread *thread, struct Class *_class) {
    struct Method *clinit = getClinitMethod(_class);
    if (clinit != NULL) {
        struct Frame *frame = newFrame(thread, clinit);
        pushFrame(frame, thread);
    }
}