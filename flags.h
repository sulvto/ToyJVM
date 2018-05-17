//
// Created by sulvto on 18-5-1.
//

#ifndef TOYJVM_FLAGS_H
#define TOYJVM_FLAGS_H

#define ACC_PUBLIC      0x0001
#define ACC_PRIVATE     0x0002
#define ACC_PROTECTED   0x0004
#define ACC_STATIC      0x0008
#define ACC_FINAL       0x0010
#define ACC_SUPER       0x0020
#define ACC_SYNCHRONIZED   0x0020
#define ACC_VOLATILE    0x0040
#define ACC_BRIDGE      0x0040
#define ACC_TRANSIENT   0x0080
#define ACC_VARARGS     0x0080
#define ACC_NATIVE      0x0100
#define ACC_INTERFACE   0x0200
#define ACC_ABSTRACT    0x0400
#define ACC_STRICT      0x0800
#define ACC_SYNTHETIC   0x1000
#define ACC_ANNOTATION  0x2000
#define ACC_ENUM        0x4000


int isPublic(u2 access_flags);

int isPrivate(u2 access_flags);

int isProtected(u2 access_flags);

int isStatic(u2 access_flags);

int isFinal(u2 access_flags);

int isSuper(u2 access_flags);

int isSynchronized(u2 access_flags);

int isVolatile(u2 access_flags);

int isBridge(u2 access_flags);

int isTransient(u2 access_flags);

int isVarargs(u2 access_flags);

int isNative(u2 access_flags);

int isInterface(u2 access_flags);

int isAbstract(u2 access_flags);

int isStrict      (u2 access_flags);
int isSynthetic   (u2 access_flags);
int isAnnotation  (u2 access_flags);
int isEnum        (u2 access_flags);


#endif //TOYJVM_FLAGS_H
