//
// Created by sulvto on 18-4-30.
//
#include "type.h"

#ifndef TOYJVM_CLASSREADER_H
#define TOYJVM_CLASSREADER_H

// ConstantPool tag
#define CONSTANT_Class              7
#define CONSTANT_Fieldref           9
#define CONSTANT_Methodref          10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String             8
#define CONSTANT_Integer            3
#define CONSTANT_Float              4
#define CONSTANT_Long               5
#define CONSTANT_Double             6
#define CONSTANT_NameAndType        12
#define CONSTANT_Utf8               1
#define CONSTANT_MethodHandle       15
#define CONSTANT_MethodType         16
#define CONSTANT_InvokeDynamic      18

// 通用格式
struct Unparsed_attributeInfo {
    u1 *info;
};

struct ConstantValue_attributeInfo {
    u2 constant_value_index;
};

struct ExceptionTable {
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_pc;
};

struct Code_attributeInfo {
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1 *code;
    u2 exception_table_length;
    struct ExceptionTable *exceptionTable;
    u2 attributes_count;
    struct AttributeInfo *attributes;
};

union AttributeInfoUnion {
    struct Unparsed_attributeInfo       unparsed;
    struct ConstantValue_attributeInfo  constant_value;
    struct Code_attributeInfo           code;
};

struct AttributeInfo {
    u2 attribute_name_index;
    u4 attribute_length;
    union AttributeInfoUnion info;
};

struct CONSTANT_Class_info {
    u2 name_index;
};

struct CONSTANT_Fieldref_info {
    u2 class_index;
    u2 name_and_type_index;
};

struct CONSTANT_Methodref_info {
    u2 class_index;
    u2 name_and_type_index;
};

struct CONSTANT_InterfaceMethodref_info {
    u2 class_index;
    u2 name_and_type_index;
};

struct CONSTANT_String_info {
    u2 string_index;
};

struct CONSTANT_Integer_info {
    u4 bytes;
};

struct CONSTANT_Float_info {
    u4 bytes;
};

struct CONSTANT_Long_info {
    u4 high_bytes;
    u4 low_bytes;
};

struct CONSTANT_Double_info {
    u4 high_bytes;
    u4 low_bytes;
};

struct CONSTANT_NameAndType_info {
    u2 name_index;
    u2 descriptor_index;
};

struct CONSTANT_Utf8_info {
    u2 length;
    u1 *bytes;
};

struct CONSTANT_MethodHandle_info {
    u1 reference_kind;
    u2 reference_index;
};

struct CONSTANT_MethodType_info {
    u2 descriptor_index;
};

struct CONSTANT_InvokeDynamic_info {
    u2 bootstrap_method_attr_index;
    u2 name_and_type_index;
};

union ConstantInfo {
    struct CONSTANT_Class_info class_info;
    struct CONSTANT_Fieldref_info fieldref_info;
    struct CONSTANT_Methodref_info methodref_info;
    struct CONSTANT_InterfaceMethodref_info interfaceMethodref_info;
    struct CONSTANT_String_info string_info;
    struct CONSTANT_Integer_info integer_info;
    struct CONSTANT_Float_info float_info;
    struct CONSTANT_Long_info long_info;
    struct CONSTANT_Double_info double_info;
    struct CONSTANT_NameAndType_info nameAndType_info;
    struct CONSTANT_Utf8_info utf8_info;
    struct CONSTANT_MethodHandle_info methodHandle_info;
    struct CONSTANT_MethodType_info methodType_info;
    struct CONSTANT_InvokeDynamic_info invokeDynamic_info;
};

struct ConstantPoolInfo {
    u1 tag;
    union ConstantInfo info;
};


struct MemberInfo {
    u2              access_flags;
    u2              name_index;
    u2              descriptor_index;
    u2              attributes_count;
    struct AttributeInfo   *attributes;
};

struct ClassFile {
    u4                      magic;
    u2                      minor_version;
    u2                      major_version;
    u2                      constant_pool_count;
    struct ConstantPoolInfo *constant_pool_info;
    u2                      access_flags;
    u2                      this_class;
    u2                      super_class;
    u2                      interfaces_count;
    u2                      *interfaces;
    u2                      fields_count;
    struct MemberInfo       *fields;
    u2                      methods_count;
    struct MemberInfo       *methods;
    u2                      attributes_count;
    struct AttributeInfo    *attributes;
};

struct s_class_data {
    // 1024??
    u1  data[1024];
    int length;
    int index;
};

struct s_class_data readClassFile(const char *);

struct ClassFile parseClassContent(struct s_class_data *class_data);

void printClassInfo(struct ClassFile *);

char *memberName(const struct MemberInfo *, const struct ConstantPoolInfo *);

char *descriptor(const struct MemberInfo *, const struct ConstantPoolInfo *);

char *attributeName(const u2, const struct ConstantPoolInfo *);

char *className(const u2 class_index, const struct ConstantPoolInfo *constant_pool_info);

char *ConstantPoolInfo_getUtf8String(const struct ConstantPoolInfo *constant_pool_info, const u2 index);

struct CONSTANT_NameAndType_info ConstantPoolInfo_getNameAndType(const struct ConstantPoolInfo *constant_pool_info,
                                                                 const u2 index);

struct AttributeInfo *constantValueAttribute(const struct MemberInfo *member,
                                             struct ConstantPoolInfo *constant_pool_info);

struct AttributeInfo *codeAttribute(const struct MemberInfo *member,
                                             struct ConstantPoolInfo *constant_pool_info);


#endif //TOYJVM_CLASSREADER_H
