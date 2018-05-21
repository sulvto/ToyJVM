//
// Created by sulvto on 18-5-18.
//
#include <stdlib.h>
#include "classref.h"
#include "class.h"
#include "constantpool.h"

#define ConstantPool_T ConstantPool


union Constant {
    int                         int_value;
    long                        long_value;
    float                       float_value;
    double                      double_value;
    char                        *string;
    void                        *method_ref;
    void                        *class_ref;
    void                        *field_ref;
    void                        *interface_method_ref;
};

struct ConstantPool_T {
    Class           _class;
    u2              size;
    union Constant *constants;
};


void ConstantPool_free(ConstantPool_T constant_pool) {
    // TODO
}

ConstantPool_T ConstantPool_new(Class _class, struct ClassFile *class_file) {
    u2 count = class_file->constant_pool_count;

    ConstantPool_T constant_pool = (ConstantPool_T) malloc(sizeof(struct ConstantPool));;
    constant_pool->_class = _class;
    constant_pool->size = count;
    constant_pool->constants = (union Constant *) malloc(sizeof(union Constant) * count);

    for (int i = 0; i < count; ++i) {
        struct ConstantPoolInfo constant_pool_info = class_file->constant_pool_info[i];
        switch (constant_pool_info.tag) {
            case CONSTANT_Class: {
                char *class_name = ConstantPoolInfo_getUtf8String(class_file->constant_pool_info,
                                                                  constant_pool_info.info.class_info.name_index);

                constant_pool->constants[i].class_ref = ClassRef_new(class_name, constant_pool);
                break;
            }
            case CONSTANT_Methodref: {
                // name and type
                struct CONSTANT_NameAndType_info nameAndType_info = ConstantPoolInfo_getNameAndType(
                        class_file->constant_pool_info,
                        constant_pool_info.info.methodref_info.name_and_type_index);
                char *name = ConstantPoolInfo_getUtf8String(class_file->constant_pool_info,
                                                            nameAndType_info.name_index);

                char *descriptor = ConstantPoolInfo_getUtf8String(class_file->constant_pool_info,
                                                                  nameAndType_info.descriptor_index);

                char *class_name = className(class_file->this_class, class_file->constant_pool_info);
                constant_pool->constants[i].method_ref = MethodRef_new(name, descriptor, class_name, constant_pool);
                break;
            }
            case CONSTANT_Fieldref: {
                // name and type
                struct CONSTANT_NameAndType_info nameAndType_info = ConstantPoolInfo_getNameAndType(
                        class_file->constant_pool_info,
                        constant_pool_info.info.fieldref_info.name_and_type_index);

                char *name = ConstantPoolInfo_getUtf8String(class_file->constant_pool_info,
                                                            nameAndType_info.name_index);

                char *descriptor = ConstantPoolInfo_getUtf8String(class_file->constant_pool_info,
                                                                  nameAndType_info.descriptor_index);

                char *class_name = className(class_file->this_class, class_file->constant_pool_info);

                constant_pool->constants[i].field_ref = FieldRef_new(name, descriptor, class_name, constant_pool);
                break;
            }
            case CONSTANT_InterfaceMethodref: {
                // TODO
                // name and type
                struct CONSTANT_NameAndType_info nameAndType_info = ConstantPoolInfo_getNameAndType(
                        class_file->constant_pool_info,
                        constant_pool_info.info.interfaceMethodref_info.name_and_type_index);
                char *name = ConstantPoolInfo_getUtf8String(class_file->constant_pool_info,
                                                            nameAndType_info.name_index);

                char *descriptor = ConstantPoolInfo_getUtf8String(class_file->constant_pool_info,
                                                                  nameAndType_info.descriptor_index);

                char *class_name = className(class_file->this_class, class_file->constant_pool_info);

                constant_pool->constants[i].interface_method_ref = InterfaceMethodRef_new(name, descriptor, class_name, constant_pool);
                break;
            }
            default:
                // TODO
                break;
        }
    }
    return constant_pool;
}


int ConstantPool_intValue(ConstantPool_T constant_pool, int index) {
    return constant_pool->constants[index].int_value;
}

long ConstantPool_longValue(ConstantPool_T constant_pool, int index) {
    return constant_pool->constants[index].long_value;
}

float ConstantPool_floatValue(ConstantPool_T constant_pool, int index) {
    return constant_pool->constants[index].float_value;
}

double ConstantPool_doubleValue(ConstantPool_T constant_pool, int index) {
    return constant_pool->constants[index].double_value;
}

char *ConstantPool_stringValue(ConstantPool_T constant_pool, int index) {
    return constant_pool->constants[index].string;
}

void *ConstantPool_fieldRef(ConstantPool_T constant_pool, int index) {
    return constant_pool->constants[index].field_ref;
}

void *ConstantPool_methodRef(ConstantPool_T constant_pool, int index) {
    return constant_pool->constants[index].method_ref;
}

void *ConstantPool_interfaceMethodRef(ConstantPool_T constant_pool, int index) {
    return constant_pool->constants[index].interface_method_ref;
}

void *ConstantPool_classRef(ConstantPool_T constant_pool, int index) {
    return constant_pool->constants[index].class_ref;
}

Class ConstantPool_class(ConstantPool_T constant_pool) {
    return constant_pool->_class;
}