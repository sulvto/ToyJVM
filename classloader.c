//
// Created by sulvto on 18-5-14.
//

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "type.h"
#include "map.h"
#include "flags.h"
#include "classloader.h"
#include "class.c"

#define ClassLoader_T ClassLoader

struct ClassLoader_T {
    // Map_T<char *, Class>
    Map_T class_map;
};

static void link(Class _class);

static void prepare(Class _class);

static void verify(Class _class);

static Class ClassLoader_defineClass(ClassLoader loader, struct s_class_data *class_data);

Class ClassLoader_loadNonArrayClass(ClassLoader_T _this, const char *name);

Class ClassLoader_loadArrayClass(ClassLoader_T _this, const char *name);



ClassLoader_T ClassLoader_new() {
    struct ClassLoader *loader = (struct ClassLoader *) malloc(sizeof(struct ClassLoader));
    loader->class_map = Map_new(1000, NULL, NULL);
    return loader;
}

ClassLoader_T ClassLoader_free(ClassLoader_T _this) {
    return NULL;
}

Class ClassLoader_loadClass(ClassLoader_T _this, char *name) {
    Class _class = (Class) Map_get(_this->class_map, name);
    if (_class != NULL) {
        return _class;
    }

    if (_class->name[0] == '[') {
        return ClassLoader_loadArrayClass(_this, name);
    } else {
        return ClassLoader_loadNonArrayClass(_this, name);
    }
}

Class ClassLoader_loadArrayClass(ClassLoader_T _this, const char *name) {
    Class _class = (struct Class *) malloc(sizeof(struct Class));
    // TODO ACC_PUBLIC
    _class->access_flags = ACC_PUBLIC;
    _class->name = name;
    _class->loader = _this;
    _class->init_started = 1;
    _class->super_class = ClassLoader_loadClass(_this, "java/lang/Object");
    _class->interface_count = 2;
    _class->interface_class = (Class*) malloc(sizeof(struct Class) * 2);

    _class->interface_class[0] = ClassLoader_loadClass(_this, "java/lang/Cloneable");
    _class->interface_class[1] = ClassLoader_loadClass(_this, "java/io/Serializable");

    Map_put(_this->class_map, name, _class);

    return _class;
}

Class ClassLoader_loadNonArrayClass(ClassLoader_T _this, const char *name) {
    struct s_class_data *class_data = readClassFile(name);
    printf("readClassFile success\n");
    Class _class = ClassLoader_defineClass(_this, class_data);
    link(_class);
    printf("[Loaded %s from %s]\n", name, "from");
    return _class;
}


void resolveSuperClass(Class _class) {
    if (strcmp(_class->name, "java/lang/Object") != 0) {
        // FIXME load java/lang/Object
        printf("_class->super_class_name %s\n", _class->super_class_name);
        _class->super_class = ClassLoader_loadClass(_class->loader, _class->super_class_name);
    } else {
        _class->super_class = NULL;
    }
}

void resolveInterfaces(Class _class) {

}


static struct Class *parseClass(struct s_class_data *class_data) {
    struct ClassFile class_file = parseClassContent(class_data);
    return Class_new(&class_file);
}

static Class ClassLoader_defineClass(ClassLoader loader, struct s_class_data *class_data) {
    Class _class = parseClass(class_data);
    _class->loader = loader;
    resolveSuperClass(_class);
    resolveInterfaces(_class);
    Map_put(loader->class_map, _class->name, _class);
    return _class;
}

static u4 isLongOrDouble(Field field) {
    return (strcmp("J", field->descriptor) == 0) || (strcmp("D", field->descriptor) == 0);
}

static void calcInstanceFieldSlotIds(Class _class) {
    u4 slot_id = 0;
    if (_class->super_class != NULL) {
        slot_id = _class->super_class->interface_slot_count;
    }

    for (int i = 0; i < _class->fields_count; ++i) {
        Field field = _class->fields[i];
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



static void calcStaticFieldSlotIds(Class _class) {
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

static void initStaticFinalVar(Class _class, Field field) {
    Slots slots = _class->static_vars;
    ConstantPool constantPool = _class->constant_pool;
    u4 slot_id = field->slot_id;
    if (field->const_value_index > 0) {
        if (strcmp(field->descriptor, "Z") == 0) {
        } else if (strcmp(field->descriptor, "Z") == 0) {
        } else if (strcmp(field->descriptor, "B") == 0) {
        } else if (strcmp(field->descriptor, "C") == 0) {
        } else if (strcmp(field->descriptor, "S") == 0) {
        } else if (strcmp(field->descriptor, "I") == 0) {
            int value = ConstantPool_intValue(constantPool, field->const_value_index);
            setInt(field->const_value_index, value, slots);
        } else if (strcmp(field->descriptor, "J") == 0) {
            long value = ConstantPool_longValue(constantPool, field->const_value_index);
            setLong(field->const_value_index, value, slots);
        } else if (strcmp(field->descriptor, "F") == 0) {
            float value = ConstantPool_floatValue(constantPool, field->const_value_index);
            setFloat(field->const_value_index, value, slots);
        } else if (strcmp(field->descriptor, "D") == 0) {
            double value = ConstantPool_doubleValue(constantPool, field->const_value_index);
            setDouble(field->const_value_index, value, slots);
        } else if (strcmp(field->descriptor, "Ljava/lang/String;") == 0) {
            char *string = ConstantPool_stringValue(constantPool, field->const_value_index);
//            set
            printf("Ljava/lang/String\n");
        } else {
            // TODO
            printf("initStaticFinalVar else\n");
        }
    }
}

static void allocAndInitStaticVars(Class _class) {
    _class->static_vars = newSlots(_class->static_slot_count);
    for (int i = 0; i < _class->fields_count; ++i) {
        Field field = _class->fields[i];
        if (field->access_flags == ACC_STATIC && field->access_flags == ACC_FINAL) {
            initStaticFinalVar(_class, field);
        }
    }
}

static void link(Class _class) {
    verify(_class);
    prepare(_class);
}


static void verify(Class _class) {
    prepare(_class);
}

static void prepare(Class _class) {
    calcInstanceFieldSlotIds(_class);
    calcStaticFieldSlotIds(_class);
    allocAndInitStaticVars(_class);
}
