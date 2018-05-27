//
// Created by sulvto on 18-5-14.
//

#include "type.h"
#include "flags.h"

int isPublic      (u2 access_flags) {
    return ACC_PUBLIC & access_flags;
}
int isPrivate     (u2 access_flags) {
    return ACC_PRIVATE & access_flags;
}
int isProtected   (u2 access_flags) {
    return ACC_PROTECTED & access_flags;
}
int isStatic      (u2 access_flags) {
    return ACC_STATIC & access_flags;
}
int isFinal       (u2 access_flags) {
    return ACC_FINAL & access_flags;
}
int isSuper       (u2 access_flags) {
    return ACC_SUPER & access_flags;
}
int isSynchronized   (u2 access_flags) {
    return ACC_SYNCHRONIZED & access_flags;
}
int isVolatile    (u2 access_flags) {
    return ACC_VOLATILE & access_flags;
}
int isBridge      (u2 access_flags) {
    return ACC_BRIDGE & access_flags;
}
int isTransient   (u2 access_flags) {
    return ACC_TRANSIENT & access_flags;
}
int isVarargs     (u2 access_flags) {
    return ACC_VARARGS & access_flags;
}
int isNative      (u2 access_flags) {
    return ACC_NATIVE & access_flags;
}
int isInterface   (u2 access_flags) {
    return ACC_INTERFACE & access_flags;
}
int isAbstract    (u2 access_flags) {
    return ACC_ABSTRACT & access_flags;
}
int isStrict      (u2 access_flags) {
    return ACC_STRICT & access_flags;
}
int isSynthetic   (u2 access_flags) {
    return ACC_SYNTHETIC & access_flags;
}
int isAnnotation  (u2 access_flags) {
    return ACC_ANNOTATION & access_flags;
}
int isEnum        (u2 access_flags) {
    return ACC_ENUM & access_flags;
}
