//
// Created by sulvto on 18-5-14.
//

#include "flags.h"

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
