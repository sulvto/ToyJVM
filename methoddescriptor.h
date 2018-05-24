//
// Created by sulvto on 18-5-24.
//

#ifndef TOYJVM_METHODDESCRIPTOR_H
#define TOYJVM_METHODDESCRIPTOR_H

struct MethodDescriptor {
    unsigned int parameter_type_count;
    char *parameter_types[255];
    char *return_type;
};

struct MethodDescriptor *MethodDescriptor_parse(char *descriptor);


#endif //TOYJVM_METHODDESCRIPTOR_H
