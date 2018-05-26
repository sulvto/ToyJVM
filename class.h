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
typedef struct Field_T *Field_T;

#define Method_T Method
typedef struct Method_T *Method_T;

#define Class_T Class
typedef struct Class_T *Class_T;


Class_T Class_new(struct ClassFile *class_file);

Class_T Class_newArrayClass(u2 access_flags, char *name, void *loader, Class_T super_class, Class_T cloneable_class, Class_T serializable_class);

Method_T Class_lookupInterfaceMethod(Class_T _class, char *name, char *descriptor);

void *Class_loader(Class_T);

char *Class_name(Class_T _this);

int Class_isSuperClassOf(Class_T _this, Class_T _other);

int Class_isImplements(Class_T _this, Class_T _other);

char *Class_packageName(Class_T _this);

void *Class_getConstantPool(Class_T _this);

void Class_setConstantPool(Class_T _this, void *constant_pool);

Slots Class_getStaticVars(Class_T);

void Class_setStaticVars(Class_T, Slots);

void Class_setInterfaceSlotCount(Class_T, u4);

u4 Class_getInterfaceSlotCount(Class_T);

void Class_setLoader(Class_T, void *);

void Class_setSuperClass(Class_T _this, Class_T super_class);

Class_T Class_getSuperClass(Class_T _this);

char *Class_superClassName(Class_T);

u4 Class_staticSlotCount(Class_T);

int Class_isArray(Class_T _this);

u2 Class_fieldsCount(Class_T _this);

Field_T *Class_fields(Class_T _this);

Method_T Class_getClinitMethod(Class_T _class);

int Class_isAccessibleTo(Class_T _this, Class_T other);

int Class_isSubInterfaceOf(Class_T _this, Class_T _other);

int Class_isSubClassOf(Class_T _this, Class_T _other);

Method_T Class_getMainMethod(Class_T _class);

Method_T Class_lookupMethod(Class_T _class, char *name, char *descriptor);

Field_T Class_lookupField(Class_T _class, char *name, char *descriptor);

Class *Class_interface(Class_T _class);

int Class_isInterface(Class_T);

int Class_isAbstract(Class_T);

int Class_isSuper(Class_T);

void Class_init(Class_T);

int Class_initStarted(Class_T);

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

u2 Field_constValueIndex(Field_T);

char *Field_descriptor(Field_T);

u4 Field_getSlotId(Field_T);

void Field_setSlotId(Field_T, u4);

Class_T Field_class(Field_T);

int Method_findExceptionHandler(Method_T _this, Class_T _class, int pc);

int Method_isAccessibleTo(Method_T _this, Class_T _other);

u4 Method_maxLocals(Method_T _this);

u4 Method_maxStack(Method_T _this);

int Method_isPublic(Method_T _this);

int Method_isAbstract(Method_T);

int Method_isPrivate(Method_T _this);

int Method_isProtected(Method_T _this);

int Method_isStatic(Method_T _this);

int Method_isNative(Method_T _this);


int Method_namecmp(Method_T _this, const char *name);

char *Method_name(Method_T _this);

char *Method_descriptor(Method_T _this);

int Method_classcmp(Method_T _this, Class_T _class);

Class_T Method_class(Method_T _this);

u4 Method_argCount(Method_T _this);

u1 *Method_code(Method_T _this);

#undef Class_T
#undef Method_T
#undef Field_T

#endif //TOYJVM_CLASS_H
