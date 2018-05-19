//
// Created by sulvto on 18-5-17.
//

#ifndef TOYJVM_CLASSREF_H
#define TOYJVM_CLASSREF_H

#include "type.h"
#include "rtda.h"
#include "class.h"
#include "constantpool.h"

#define ClassRef_T ClassRef
typedef struct ClassRef_T *ClassRef_T;

#define MethodRef_T MethodRef
typedef struct MethodRef_T *MethodRef;

#define FieldRef_T FieldRef
typedef struct FieldRef_T *FieldRef;

#define InterfaceMethodRef_T InterfaceMethodRef
typedef struct InterfaceMethodRef_T *InterfaceMethodRef;

ClassRef_T ClassRef_new(char *class_name, ConstantPool constant_pool);

Class ClassRef_class(ClassRef_T class_ref);

Class ClassRef_resolvedClass(ClassRef_T ref);

void ClassRef_resolveClassRef(ClassRef_T ref);

MethodRef_T MethodRef_new(char *name, char *descriptor, char *class_name, ConstantPool constant_pool);

Class MethodRef_resolvedClass(MethodRef_T method_ref);

void MethodRef_resolveClassRef(MethodRef_T method_ref);

char *MethodRef_name(MethodRef_T method_ref);

char *MethodRef_descriptor(MethodRef_T method_ref);

void MethodRef_resolveMethodRef(MethodRef_T method_ref);

Method MethodRef_resolvedMethod(MethodRef_T method_ref);

Method MethodRef_lookupMethodInClass(MethodRef_T method_ref, Class _class);

FieldRef_T FieldRef_new(char *name, char *descriptor, char *class_name, ConstantPool constant_pool);

Class FieldRef_class(FieldRef_T field_ref);

Field FieldRef_resolvedField(FieldRef_T field_ref);

InterfaceMethodRef_T InterfaceMethodRef_new(char *name, char *descriptor, char *class_name, ConstantPool constant_pool);

Class InterfaceMethodRef_resolvedClass( InterfaceMethodRef_T interface_method_ref);

Method InterfaceMethodRef_resolvedInterfaceMethod(InterfaceMethodRef_T interface_method_ref);

Method InterfaceMethodRef_lookupMethodInClass(InterfaceMethodRef_T interface_method_ref, Class _class);

#endif //TOYJVM_CLASSREF_H
