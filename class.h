//
// Created by sulvto on 18-5-1.
//

#ifndef TOYJVM_CLASS_H
#define TOYJVM_CLASS_H

#include "type.h"
#include "map.h"
#include "rtda.h"
#include "classreader.h"

#define Field_T Field
typedef struct Field_T *Field;

#define Method_T Method
typedef struct Method_T *Method;

#define Class_T Class
typedef struct Class_T *Class;


Class_T Class_new(struct ClassFile *class_file);

Method_T Class_lookupInterfaceMethod(Class_T _class, char *name, char *descriptor);

void *Class_loader(Class_T);

int Class_isSuperClassOf(Class_T _this, Class_T _other);

int Class_isImplements(Class_T _this, Class_T _other);

char *Class_packageName(Class_T _this);

int Class_isArray(Class_T _this);

Method_T Class_getClinitMethod(Class_T _class);

int Class_isAccessibleTo(Class_T _this, Class_T other);

int Class_isSubInterfaceOf(Class_T _this, Class_T _other);

int Class_isSubClassOf(Class_T _this, Class_T _other);

Method_T Class_getMainMethod(Class_T _class);

Method_T Class_lookupMethod(Class_T _class, char *name, char *descriptor);

Field_T Class_lookupField(Class_T _class, char *name, char *descriptor);

Class *Class_interface(Class_T _class);

int Class_isInterface(Class_T);

//Method_T resolvedInterfaceMethod(struct InterfaceMethodRef *interface_method_ref);
//
//Method_T resolvedMethod(struct MethodRef *method_ref);
//
//Field_T resolvedField(struct FieldRef *field_ref);

Method_T Class_lookupMethodInClass(Class_T _class, char *name, char *descriptor);

Method_T lookupMethodInInterfaces(Class_T *interfaces, u2 count, char *name, char *descriptor);


int Field_isPublic(Field_T _this);

int Field_isPrivate(Field_T _this);

int Field_isProtected(Field_T _this);

int Field_isStatic(Field_T _this);

int Field_isFinal(Field_T _this);

int Field_isAccessibleTo(Field_T _this, Class_T other);

int Method_isAccessibleTo(Method_T _this, Class_T _other);

u4 Method_maxLocals(Method_T _this);

u4 Method_maxStack(Method_T _this);

int Method_isPublic(Method_T _this);

int Method_isPrivate(Method_T _this);

int Method_isProtected(Method_T _this);

int Method_isStatic(Method_T _this);

int Method_namecmp(Method_T _this, const char *name);

int Method_classcmp(Method_T _this, Class_T _class);

int Method_argCount(Method_T _this);

#undef Field_T
#undef Method_T
#undef Class_T

#endif //TOYJVM_CLASS_H
