//
// Created by sulvto on 18-5-11.
//

#ifndef TOYJVM_NATIVEMETHOD_H
#define TOYJVM_NATIVEMETHOD_H

void NativeMethod_register(char *class_name, char *method_name, char *method_descriptor, struct NativeMethod *method);

void NativeMethod_find(char *class_name, char *method_name, char *method_descriptor);


#endif //TOYJVM_NATIVEMETHOD_H
