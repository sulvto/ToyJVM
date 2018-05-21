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
#include "constantpool.h"

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

static void initStaticFinalVar(Class _class, Field field);


ClassLoader_T ClassLoader_new() {
    struct ClassLoader *loader = (struct ClassLoader *) malloc(sizeof(struct ClassLoader));
    loader->class_map = Map_new(1000, NULL, NULL);
    return loader;
}

ClassLoader_T ClassLoader_free(ClassLoader_T _this) {
    // TODO
    return NULL;
}

Class ClassLoader_loadClass(ClassLoader_T _this, char *name) {
    Class _class = (Class) Map_get(_this->class_map, name);
    if (_class != NULL) {
        return _class;
    }

    if (name[0] == '[') {
        return ClassLoader_loadArrayClass(_this, name);
    } else {
        return ClassLoader_loadNonArrayClass(_this, name);
    }
}

Class ClassLoader_loadArrayClass(ClassLoader_T _this, const char *name) {
    Class super_class = ClassLoader_loadClass(_this, "java/lang/Object");
    Class cloneable_class = ClassLoader_loadClass(_this, "java/lang/Cloneable");
    Class serializable_class = ClassLoader_loadClass(_this, "java/io/Serializable");
    // TODO ACC_PUBLIC
    Class _class = Class_newArrayClass(ACC_PUBLIC, name, _this, super_class, cloneable_class, serializable_class);
    Map_put(_this->class_map, name, _class);
    return _class;
}

Class ClassLoader_loadNonArrayClass(ClassLoader_T _this, const char *name) {

    struct s_class_data *class_data = readClassFile(name);
    if (class_data == NULL) {
        printf("class not found: %s\n", name);
        return NULL;
    } else {
        printf("readClassFile success\n");
        Class _class = ClassLoader_defineClass(_this, class_data);
//        freeClassData(&class_data);
        link(_class);
        printf("[Loaded %s from %s]\n", name, "from");
        return _class;
    }
}


void resolveSuperClass(Class _class) {
    if (strcmp(Class_name(_class), "java/lang/Object") != 0) {
        // FIXME load java/lang/Object
        printf("_class->super_class_name %s\n", Class_superClassName(_class));
        Class_setSuperClass(_class, ClassLoader_loadClass(Class_loader(_class), Class_superClassName(_class)));
    } else {
        Class_setSuperClass(_class, NULL);
    }
}

void resolveInterfaces(Class _class) {

}


static Class parseClass(struct s_class_data *class_data) {
    struct ClassFile class_file = parseClassContent(class_data);
    Class _class = Class_new(&class_file);
    Class_setConstantPool(_class, ConstantPool_new(_class, &class_file));
    return _class;
}

static Class ClassLoader_defineClass(ClassLoader loader, struct s_class_data *class_data) {
    Class _class = parseClass(class_data);
    Class_setLoader(_class, loader);
    resolveSuperClass(_class);
    resolveInterfaces(_class);
    Map_put(loader->class_map, Class_name(_class), _class);
    return _class;
}

static u4 isLongOrDouble(Field field) {
    return (strcmp("J", Field_descriptor(field)) == 0) || (strcmp("D", Field_descriptor(field)) == 0);
}

static void calcInstanceFieldSlotIds(Class _class) {
    u4 slot_id = 0;
    Class super_class = Class_getSuperClass(_class);

    if (super_class != NULL) {
        slot_id = Class_getInterfaceSlotCount(super_class);
    }

    u4 fields_count = Class_fieldsCount(_class);
    Field *fields = Class_fields(_class);

    for (int i = 0; i < fields_count; ++i) {
        Field field = fields[i];
        if (!Field_isStatic(field)) {
            Field_setSlotId(field, slot_id);
            slot_id++;
            if (isLongOrDouble(field)) {
                slot_id++;
            }
        }
    }

    Class_setInterfaceSlotCount(_class, slot_id);
}



static void calcStaticFieldSlotIds(Class _class) {
    u4 slot_id = 0;

    u4 fields_count = Class_fieldsCount(_class);
    Field *fields = Class_fields(_class);
    for (int i = 0; i < fields_count; ++i) {
        struct Field *field = fields[i];
        if (Field_isStatic(field)) {
            Field_setSlotId(field, slot_id);
            slot_id++;
            if (isLongOrDouble(field)) {
                slot_id++;
            }
        }
    }

    Class_setInterfaceSlotCount(_class, slot_id);
}

static void initStaticFinalVar(Class _class, Field field) {
    Slots slots = Class_getStaticVars(_class);
    ConstantPool constantPool = Class_getConstantPool(_class);
    u4 slot_id = Field_getSlotId(field);
    u2 const_value_index = Field_constValueIndex(field);
    char *descriptor = Field_descriptor(field);

    if (const_value_index > 0) {
        if (strcmp(descriptor, "Z") == 0) {
        } else if (strcmp(descriptor, "Z") == 0) {
        } else if (strcmp(descriptor, "B") == 0) {
        } else if (strcmp(descriptor, "C") == 0) {
        } else if (strcmp(descriptor, "S") == 0) {
        } else if (strcmp(descriptor, "I") == 0) {
            int value = ConstantPool_intValue(constantPool, const_value_index);
            setInt(const_value_index, value, slots);
        } else if (strcmp(descriptor, "J") == 0) {
            long value = ConstantPool_longValue(constantPool, const_value_index);
            setLong(const_value_index, value, slots);
        } else if (strcmp(descriptor, "F") == 0) {
            float value = ConstantPool_floatValue(constantPool, const_value_index);
            setFloat(const_value_index, value, slots);
        } else if (strcmp(descriptor, "D") == 0) {
            double value = ConstantPool_doubleValue(constantPool, const_value_index);
            setDouble(const_value_index, value, slots);
        } else if (strcmp(descriptor, "Ljava/lang/String;") == 0) {
            char *string = ConstantPool_stringValue(constantPool, const_value_index);
//            set
            // TODO
            printf("Ljava/lang/String\n");
        } else {
            // TODO
            printf("initStaticFinalVar else\n");
        }
    }
}

static void allocAndInitStaticVars(Class _class) {
    Class_setStaticVars(_class, newSlots(Class_staticSlotCount(_class)));
    u4 fields_count = Class_fieldsCount(_class);
    Field *fields = Class_fields(_class);
    for (int i = 0; i < fields_count; i++) {
        Field field = fields[i];
        if (Field_isStatic(field) && Field_isFinal(field)) {
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
