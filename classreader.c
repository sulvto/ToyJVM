//
// Created by sulvto on 18-4-24.
//
#include <stdio.h>
#include "type.h"
#include "classreader.h"


// ConstantPool tag
const u1 CONSTANT_Class = 7;
const u1 CONSTANT_Fieldref = 9;
const u1 CONSTANT_Methodref = 10;
const u1 CONSTANT_InterfaceMethodref = 11;
const u1 CONSTANT_String = 8;
const u1 CONSTANT_Integer = 3;
const u1 CONSTANT_Float = 4;
const u1 CONSTANT_Long = 5;
const u1 CONSTANT_Double = 6;
const u1 CONSTANT_NameAndType = 12;
const u1 CONSTANT_Utf8 = 1;
const u1 CONSTANT_MethodHandle = 15;
const u1 CONSTANT_MethodType = 16;
const u1 CONSTANT_InvokeDynamic = 18;

// Attribute
const char *ATTRIBUTE_ConstantValue = "ConstantValue";
const char *ATTRIBUTE_Code = "Code";
const char *ATTRIBUTE_Deprecated = "Deprecated";
const char *ATTRIBUTE_Exceptions = "Exceptions";
const char *ATTRIBUTE_LineNumberTable = "LineNumberTable";
const char *ATTRIBUTE_LocalVariableTable = "LocalVariableTable";
const char *ATTRIBUTE_SourceFile = "SourceFile";
const char *ATTRIBUTE_Synthetic = "Synthetic";


u1 readU1(struct s_class_data *class_data) {
    return class_data->data[class_data->index++];
}

u2 readU2(struct s_class_data *class_data)
{
    u2 d = readU1(class_data);
    return d << 8 | readU1(class_data);
}

u4 readU4(struct s_class_data *class_data)
{
	u4 d = readU2(class_data);
    return d << 16 | readU2(class_data);
}

u8 readU8(struct s_class_data *class_data)
{
	u8 d = readU4(class_data);
    return d << 32 | readU4(class_data);
}

u2 *readU2s(struct s_class_data *class_data)
{
	int n = readU2(class_data);
	u2 d[n];

	for (int i=0; i < n; i++) {
		d[i] = readU2(class_data);
	}

	return d;
}



void readAndCheckMagic(struct s_class_data *class_data, struct ClassFile *_class)
{
	_class->magic = readU4(class_data);

    // 16 -> 10
    // CAFEBABE -> 3405691582
	if (_class->magic != 3405691582) {
		printf("Class format error: magic!\n");
		exit(1);
	}
}

void readAndCheckVersion(struct s_class_data *class_data, struct ClassFile *_class)
{
	_class->minor_version = readU2(class_data);
	_class->major_version = readU2(class_data);

	switch (_class->major_version) {
        case 45:
            break;
        case 46:
        case 47:
        case 48:
        case 49:
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
            if (_class->minor_version == 0) {
                break;
            }
        default:
            printf("Un supported class version(%u.%u) error!\n", _class->major_version, _class->minor_version);
            exit(1);
    }

}

void readConstantPool(struct s_class_data *class_data, struct ClassFile *_class)
{
    u2 count = _class->constant_pool_count = readU2(class_data);
    _class->constant_pool = (struct ConstantPoolInfo*) malloc(sizeof(struct ConstantPoolInfo) * count);

    u2 index = 0;
    for (int i = 1; i < count; i++) {

        struct ConstantPoolInfo *cp_info = &_class->constant_pool[index++];
        u1 tag = cp_info->tag = readU1(class_data);

        union ConstantInfo *constantInfo = &cp_info->info;

        if (tag == CONSTANT_Class) {
            struct CONSTANT_Class_info *class_info = &constantInfo->class_info;
            class_info->name_index = readU2(class_data);
        } else if (tag == CONSTANT_Fieldref) {
            struct CONSTANT_Fieldref_info *fieldref_info = &constantInfo->fieldref_info;
            fieldref_info->class_index = readU2(class_data);
            fieldref_info->name_and_type_index = readU2(class_data);
        } else if (tag == CONSTANT_Methodref) {
            struct CONSTANT_Methodref_info methodref_info;
            methodref_info.class_index = readU2(class_data);
            methodref_info.name_and_type_index = readU2(class_data);
            constantInfo->methodref_info = methodref_info;
        } else if (tag == CONSTANT_InterfaceMethodref) {
            struct CONSTANT_InterfaceMethodref_info interfaceMethodref_info;
            interfaceMethodref_info.class_index = readU2(class_data);
            interfaceMethodref_info.name_and_type_index = readU2(class_data);
            constantInfo->interfaceMethodref_info = interfaceMethodref_info;
        } else if (tag == CONSTANT_String) {
            struct CONSTANT_String_info string_info;
            string_info.string_index = readU2(class_data);
            constantInfo->string_info = string_info;
        } else if (tag == CONSTANT_Integer) {
            struct CONSTANT_Integer_info integer_info;
            integer_info.bytes = readU4(class_data);
            constantInfo->integer_info = integer_info;
        } else if (tag == CONSTANT_Float) {
            struct CONSTANT_Float_info float_info;
            float_info.bytes = readU4(class_data);
            constantInfo->float_info = float_info;
        } else if (tag == CONSTANT_Long) {
            struct CONSTANT_Long_info long_info;
            long_info.high_bytes = readU4(class_data);
            long_info.low_bytes -= readU4(class_data);
            constantInfo->long_info = long_info;
        } else if (tag == CONSTANT_Double) {
            struct CONSTANT_Double_info double_info;
            double_info.high_bytes = readU4(class_data);
            constantInfo->double_info = double_info;
        } else if (tag == CONSTANT_NameAndType) {
            struct CONSTANT_NameAndType_info nameAndType_info;
            nameAndType_info.name_index = readU2(class_data);
            nameAndType_info.descriptor_index = readU2(class_data);
            constantInfo->nameAndType_info = nameAndType_info;
        } else if (tag == CONSTANT_Utf8) {
            struct CONSTANT_Utf8_info *utf8_info = &constantInfo->utf8_info;
            utf8_info->length = readU2(class_data);
            utf8_info->bytes = (u1 *) malloc(sizeof(u1) * utf8_info->length);
            for (u2 j = 0; j < utf8_info->length; j++) {
                utf8_info->bytes[j] = readU1(class_data);
            }
        } else if (tag == CONSTANT_MethodHandle) {
            struct CONSTANT_MethodHandle_info methodHandle_info;
            methodHandle_info.reference_kind = readU1(class_data);
            methodHandle_info.reference_index = readU2(class_data);
            constantInfo->methodHandle_info = methodHandle_info;
        } else if (tag == CONSTANT_MethodType) {
            struct CONSTANT_MethodType_info methodType_info;
            methodType_info.descriptor_index = readU2(class_data);
            constantInfo->methodType_info = methodType_info;
        } else if (tag == CONSTANT_InvokeDynamic) {
            struct CONSTANT_InvokeDynamic_info invokeDynamic_info;
            invokeDynamic_info.bootstrap_method_attr_index = readU2(class_data);
            invokeDynamic_info.name_and_type_index = readU2(class_data);
            constantInfo->invokeDynamic_info = invokeDynamic_info;
        } else {
            printf("tag %x\n", tag);
            printf("Class format error! constant pool tag!\n");
            exit(1);
        }
    }
}

struct ExceptionTable readExceptionTable(struct s_class_data *class_data)
{
    struct ExceptionTable exceptionTable;
    exceptionTable.start_pc = readU2(class_data);
    exceptionTable.end_pc = readU2(class_data);
    exceptionTable.handler_pc = readU2(class_data);
    exceptionTable.catch_pc = readU2(class_data);

    return exceptionTable;
}


union AttributeInfo readAttributes(struct s_class_data *class_data, const struct ConstantPoolInfo *constant_pool)
{
    union AttributeInfo attributeInfo;

    u2 attribute_name_index = readU2(class_data);
    u4 attribute_length = readU4(class_data);

    char attrName[1024];
    attributeName(attribute_name_index, constant_pool, &attrName);

    if (strcmp(ATTRIBUTE_ConstantValue, attrName) == 0) {

        struct ConstantValue_attributeInfo constantValue;
        constantValue.attribute_name_index = attribute_name_index;
        constantValue.attribute_length = attribute_length;
        constantValue.constantValue_index = readU2(class_data);
        attributeInfo.constantValue = constantValue;
    }else if (strcmp(ATTRIBUTE_Code, attrName) == 0) {

        struct Code_attributeInfo code;
        code.attribute_name_index = attribute_name_index;
        code.attribute_length = attribute_length;
        code.max_stack = readU2(class_data);
        code.max_locals = readU2(class_data);
        code.code_length = readU4(class_data);
        code.code = (u1 *) malloc(sizeof(u1) * code.code_length);
        for (int i = 0; i < code.code_length; i++) {
            code.code[i] = readU1(class_data);
        }
        code.exception_table_length = readU2(class_data);
        code.exceptionTable = (struct ExceptionTable *) malloc(
                sizeof(struct ExceptionTable) * code.exception_table_length);
        for (int j = 0; j < code.exception_table_length; ++j) {
            code.exceptionTable[j] = readExceptionTable(class_data);
        }
        code.attributes_count = readU2(class_data);
        code.attributes = (union AttributeInfo *) malloc(sizeof(union AttributeInfo) * code.attributes_count);
        for (int k = 0; k < code.attributes_count; ++k) {
            code.attributes[k] = readAttributes(class_data, constant_pool);
        }
        attributeInfo.code = code;
    } else {
        printf("Unparsed_attributeInfo\n");

        struct Unparsed_attributeInfo unparsed;

        unparsed.attribute_name_index = attribute_name_index;
        unparsed.attribute_length = attribute_length;

        unparsed.info = (u1 *) malloc(sizeof(u1) * attribute_length);

        for (int i = 0; i < attribute_length; i++) {
            unparsed.info[i] = readU1(class_data);
        }
        attributeInfo.unparsed = unparsed;
    }

    return attributeInfo;
}

struct MemberInfo readMember(struct s_class_data *class_data, const struct ConstantPoolInfo *constantPool)
{
    struct MemberInfo memberInfo;
    memberInfo.access_flags = readU2(class_data);
    memberInfo.name_index = readU2(class_data);
    memberInfo.descriptor_index = readU2(class_data);
    memberInfo.attributes_count = readU2(class_data);

    memberInfo.attributes = (union AttributeInfo *) malloc(sizeof(union AttributeInfo) * memberInfo.attributes_count);

    for (int i = 0; i < memberInfo.attributes_count; i++) {
        memberInfo.attributes[i] = readAttributes(class_data, constantPool);
    }

    return memberInfo;
}

void readFields(const struct s_class_data *class_data, struct ClassFile *_class)
{
    int count = _class->fields_count = readU2(class_data);

    _class->fields = (struct MemberInfo *) malloc(sizeof(struct MemberInfo) * count);

    for (int i=0; i<count; i++) {
        _class->fields[i] = readMember(class_data, _class->constant_pool);
    }

}

void readMethods(const struct s_class_data *class_data, struct ClassFile *_class)
{
    int count = _class->methods_count = readU2(class_data);

    _class->methods = (struct MemberInfo *) malloc(sizeof(struct MemberInfo) * count);

    for (int i=0; i<count; i++) {
        _class->methods[i] = readMember(class_data, _class->constant_pool);
    }

}


struct s_class_data readClass(const char *className)
{
    FILE *f;
    f = fopen(className, "r");
    struct s_class_data class_data;
    int i = 0;
    u1 buf;
    while (fread(&buf, sizeof(u1), 1, f) != 0) {
        class_data.data[i++] = buf;
    }

    class_data.index = 0;
    class_data.length = i;

    return class_data;
}

struct ClassFile parseClass(struct s_class_data *class_data)
{
	struct ClassFile _class;
	readAndCheckMagic(class_data, &_class);
	readAndCheckVersion(class_data, &_class);
    readConstantPool(class_data, &_class);
    _class.access_flags = readU2(class_data);
    _class.this_class = readU2(class_data);
    _class.super_class = readU2(class_data);
    _class.interfaces_count = readU2(class_data);
    // TODO interfaces
    readFields(class_data, &_class);
    printf("readMethods \n");
    readMethods(class_data, &_class);
    printf("attributes_count \n");
    _class.attributes_count = readU2(class_data);
    _class.attributes = (union AttributeInfo *) malloc(sizeof(union AttributeInfo) * _class.attributes_count);

    for (int i = 0; i < _class.attributes_count; i++) {
        _class.attributes [i] = readAttributes(class_data, _class.constant_pool);
    }

    return _class;
}

void utf8String(const struct CONSTANT_Utf8_info *utf8_info, char *c)
{
    u2 length = utf8_info->length;

    for (int i = 0; i < length; ++i) {
        u1 byte = utf8_info->bytes[i];
        if(byte < 127) {
            c[i] = toascii(byte);
        } else {
            // TODO
            c[i] = '~';
        }
    }

    c[length] = '\0';
}

struct CONSTANT_Utf8_info *utf8Info(const u2 index, const struct ConstantPoolInfo *constant_pool)
{
    return &constant_pool[index - 1].info.utf8_info;
}


void methodName(const struct MemberInfo *method, const struct ConstantPoolInfo *constant_pool, char *name)
{
    struct CONSTANT_Utf8_info *utf8_info = utf8Info(method->name_index, constant_pool);
    utf8String(utf8_info, name);
}

void attributeName(const u2 attribute_name_index, const struct ConstantPoolInfo *constant_pool, char *name)
{
    struct CONSTANT_Utf8_info *utf8_info = utf8Info(attribute_name_index, constant_pool);
    utf8String(utf8_info, name);
}


void printClassInfo(struct ClassFile *_class) {
    printf("version: %d.%d\n", _class->major_version, _class->minor_version);
    printf("constants count: %u\n", _class->constant_pool_count);
    printf("access flags: 0x%x\n", _class->access_flags);
    printf("this class: %d\n", _class->this_class);
    printf("super class: %d\n", _class->super_class);
    printf("interfaces: %d\n", _class->interfaces_count);
    printf("fields count: %d\n", _class->fields_count);
    printf("methods count: %d\n", _class->methods_count);
}

void printConstantPoolUtf8Info(struct ConstantPoolInfo *constant_pool, u2 count)
{
    printf("printUtf8 \n");

    for (int i = 0; i < count; ++i) {
        struct ConstantPoolInfo info = constant_pool[i];

        if (info.tag == 1) {
            printf("ConstantPool index: %d \n", i);
            printUtf8Info(&info);
        }
    }
}


void printUtf8Info(struct ConstantPoolInfo *utf8)
{
    printUtf8(&utf8->info.utf8_info);
}



void printUtf8(struct CONSTANT_Utf8_info *utf8_info)
{
    for (int j = 0; j < utf8_info->length; ++j) {
        printf("%x ", utf8_info->bytes[j]);
    }
    printf("\n");
}

 int main()
{
    struct s_class_data class_data = readClass("Test.class");
    struct ClassFile _class = parseClass(&class_data);
    printClassInfo(&_class);
}
