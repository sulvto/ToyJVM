//
// Created by sulvto on 18-5-18.
//

#ifndef TOYJVM_CONSTANTPOOL_H
#define TOYJVM_CONSTANTPOOL_H

#include "class.h"

#define ConstantPool_T ConstantPool
typedef struct ConstantPool_T *ConstantPool_T;


void ConstantPool_free(ConstantPool_T);

ConstantPool_T ConstantPool_new(Class _class, struct ClassFile *class_file);

int ConstantPool_intValue(ConstantPool_T, int);

long ConstantPool_longValue(ConstantPool_T, int);

float ConstantPool_floatValue(ConstantPool_T, int);

double ConstantPool_doubleValue(ConstantPool_T, int);

char *ConstantPool_stringValue(ConstantPool_T, int);

void *ConstantPool_fieldRef(ConstantPool_T, int);

void *ConstantPool_methodRef(ConstantPool_T, int);

void *ConstantPool_interfaceMethodRef(ConstantPool_T, int);

void *ConstantPool_classRef(ConstantPool_T, int);

Class ConstantPool_class(ConstantPool_T);

#endif //TOYJVM_CONSTANTPOOL_H
