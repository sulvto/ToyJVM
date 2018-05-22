//
// Created by sulvto on 18-5-11.
//

#ifndef TOYJVM_NATIVE_H
#define TOYJVM_NATIVE_H

typedef void(*NativeMethod)(struct Frame *);

void NativeMethod_register(const char *class_name, const char *method_name, const char *method_descriptor, NativeMethod method);

NativeMethod NativeMethod_find(char *class_name, char *method_name, char *method_descriptor);


#endif // TOYJVM_NATIVE_H
