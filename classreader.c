//
// Created by sulvto on 18-4-24.
//
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <zlib.h>
#include <zip.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "type.h"
#include "classreader.h"

// Attribute
const char *ATTRIBUTE_ConstantValue = "ConstantValue";
const char *ATTRIBUTE_Code = "Code";
const char *ATTRIBUTE_Deprecated = "Deprecated";
const char *ATTRIBUTE_Exceptions = "Exceptions";
const char *ATTRIBUTE_LineNumberTable = "LineNumberTable";
const char *ATTRIBUTE_LocalVariableTable = "LocalVariableTable";
const char *ATTRIBUTE_SourceFile = "SourceFile";
const char *ATTRIBUTE_Synthetic = "Synthetic";


static char *utf8String(struct CONSTANT_Utf8_info *utf8_info);

void freeString(char **str);


u1 readU1(struct s_class_data *class_data) {
    return class_data->data[class_data->index++];
}

u2 readU2(struct s_class_data *class_data) {
    u2 d = readU1(class_data);
    return d << 8 | readU1(class_data);
}

u4 readU4(struct s_class_data *class_data) {
    u4 d = readU2(class_data);
    return d << 16 | readU2(class_data);
}

u8 readU8(struct s_class_data *class_data) {
    u8 d = readU4(class_data);
    return d << 32 | readU4(class_data);
}

u2 *readU2s(struct s_class_data *class_data) {
    int n = readU2(class_data);
    u2 d[n];

    for (int i = 0; i < n; i++) {
        d[i] = readU2(class_data);
    }

    return d;
}


void readAndCheckMagic(struct s_class_data *class_data, struct ClassFile *class_file) {
    class_file->magic = readU4(class_data);

    // 16 -> 10
    // CAFEBABE -> 3405691582
    if (class_file->magic != 3405691582) {
        printf("Class format error: magic!\n");
        exit(1);
    }
}

void readAndCheckVersion(struct s_class_data *class_data, struct ClassFile *class_file) {
    class_file->minor_version = readU2(class_data);
    class_file->major_version = readU2(class_data);

    switch (class_file->major_version) {
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
            if (class_file->minor_version == 0) {
                break;
            }
        default:
            printf("Un supported class version(%u.%u) error!\n", class_file->major_version, class_file->minor_version);
            exit(1);
    }

}

void readConstantPool(struct s_class_data *class_data, struct ClassFile *class_file) {
    u2 count = class_file->constant_pool_count = readU2(class_data);
    printf("readConstantPool constant_pool_count: %d\n", count);
    class_file->constant_pool_info = (struct ConstantPoolInfo *) malloc(sizeof(struct ConstantPoolInfo) * count);

    u2 index = 0;
    for (int i = 1; i < count; i++) {

        struct ConstantPoolInfo *cp_info = &class_file->constant_pool_info[index++];
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
            struct CONSTANT_Methodref_info *methodref_info = &constantInfo->methodref_info;
            methodref_info->class_index = readU2(class_data);
            methodref_info->name_and_type_index = readU2(class_data);
        } else if (tag == CONSTANT_InterfaceMethodref) {
            struct CONSTANT_InterfaceMethodref_info *interfaceMethodref_info = &constantInfo->interfaceMethodref_info;
            interfaceMethodref_info->class_index = readU2(class_data);
            interfaceMethodref_info->name_and_type_index = readU2(class_data);
        } else if (tag == CONSTANT_String) {
            struct CONSTANT_String_info *string_info = &constantInfo->string_info;
            string_info->string_index = readU2(class_data);
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

struct ExceptionTable readExceptionTable(struct s_class_data *class_data) {
    struct ExceptionTable exceptionTable;
    exceptionTable.start_pc = readU2(class_data);
    exceptionTable.end_pc = readU2(class_data);
    exceptionTable.handler_pc = readU2(class_data);
    exceptionTable.catch_pc = readU2(class_data);

    return exceptionTable;
}


struct AttributeInfo *readAttributes(struct s_class_data *class_data,
                                    struct ConstantPoolInfo *constant_pool_info) {
    struct AttributeInfo *attributeInfo = (struct AttributeInfo *) malloc(sizeof(struct AttributeInfo));

    u2 attribute_name_index = readU2(class_data);
    u4 attribute_length = readU4(class_data);

    attributeInfo->attribute_name_index = attribute_name_index;
    attributeInfo->attribute_length = attribute_length;

    char *attr_name = attributeName(attribute_name_index, constant_pool_info);

    attributeInfo->info = (union AttributeInfoUnion *) malloc(sizeof(union AttributeInfoUnion));
    if (strcmp(ATTRIBUTE_ConstantValue, attr_name) == 0) {
        attributeInfo->info->constant_value = (struct ConstantValue_attributeInfo *) malloc(
                sizeof(struct ConstantValue_attributeInfo));
        attributeInfo->info->constant_value->constant_value_index = readU2(class_data);
    } else if (strcmp(ATTRIBUTE_Code, attr_name) == 0) {
        attributeInfo->info->code = (struct Code_attributeInfo *) malloc(sizeof(struct Code_attributeInfo));
        attributeInfo->info->code->max_stack = readU2(class_data);
        attributeInfo->info->code->max_locals = readU2(class_data);
        u4 code_length = readU4(class_data);
        attributeInfo->info->code->code_length = code_length;
        attributeInfo->info->code->code = (u1 *) malloc(sizeof(u1) * code_length);
        for (int i = 0; i < code_length; i++) {
            attributeInfo->info->code->code[i] = readU1(class_data);
        }
        u2 exception_table_length = readU2(class_data);
        attributeInfo->info->code->exception_table_length = exception_table_length;
        attributeInfo->info->code->exceptionTable = (struct ExceptionTable *) malloc(
                sizeof(struct ExceptionTable) * exception_table_length);
        for (int j = 0; j < exception_table_length; ++j) {
            attributeInfo->info->code->exceptionTable[j] = readExceptionTable(class_data);
        }

        u2 attributes_count = readU2(class_data);
        attributeInfo->info->code->attributes_count = attributes_count;
        attributeInfo->info->code->attributes = (struct AttributeInfo *) malloc(sizeof(struct AttributeInfo) * attributes_count);
        for (int k = 0; k < attributes_count; ++k) {
            attributeInfo->info->code->attributes[k] = *readAttributes(class_data, constant_pool_info);
        }

    } else {
        attributeInfo->info->unparsed = (struct Unparsed_attributeInfo *) malloc(sizeof(struct Unparsed_attributeInfo));

        attributeInfo->info->unparsed->info = (u1 *) malloc(sizeof(u1) * attribute_length);

        for (int i = 0; i < attribute_length; i++) {
            attributeInfo->info->unparsed->info[i] = readU1(class_data);
        }
    }

    freeString(&attr_name);
    return attributeInfo;
}

struct MemberInfo readMember(struct s_class_data *class_data, struct ConstantPoolInfo *constantPool) {
    struct MemberInfo memberInfo;
    memberInfo.access_flags = readU2(class_data);
    memberInfo.name_index = readU2(class_data);
    memberInfo.descriptor_index = readU2(class_data);
    memberInfo.attributes_count = readU2(class_data);

    memberInfo.attributes = (struct AttributeInfo *) malloc(sizeof(struct AttributeInfo) * memberInfo.attributes_count);

    for (int i = 0; i < memberInfo.attributes_count; i++) {
        memberInfo.attributes[i] = *readAttributes(class_data, constantPool);
    }

    return memberInfo;
}

void readFields(struct s_class_data *class_data, struct ClassFile *class_file) {
    int count = class_file->fields_count = readU2(class_data);

    class_file->fields = (struct MemberInfo *) malloc(sizeof(struct MemberInfo) * count);

    for (int i = 0; i < count; i++) {
        class_file->fields[i] = readMember(class_data, class_file->constant_pool_info);
    }

}

void readMethods(struct s_class_data *class_data, struct ClassFile *class_file) {
    int count = class_file->methods_count = readU2(class_data);

    class_file->methods = (struct MemberInfo *) malloc(sizeof(struct MemberInfo) * count);

    for (int i = 0; i < count; i++) {
        class_file->methods[i] = readMember(class_data, class_file->constant_pool_info);
    }
}

static int readJAR(const char *path, const char *class_name, struct s_class_data *class_data) {
    struct zip *p_zip;

    p_zip = zip_open(path, 0, &errno);

    int fileCount;
    fileCount = zip_get_num_files(p_zip);
    unsigned int i;

    for (i = 0; i < fileCount ; i++) {
        struct zip_stat zip_stat;
        zip_stat_init(&zip_stat);
        zip_stat_index(p_zip, i, 0, &zip_stat);
//        printf("%dth file name is [%s]\n", i, zip_stat.name);

        if (strcmp(class_name, zip_stat.name) == 0) {
            struct zip_file *pzip_file = zip_fopen_index(p_zip, i, 0);
            class_data->data = (u1) malloc(sizeof(u1) * zip_stat.size);
            class_data->index = 0;
            class_data->length = zip_stat.size;
            // FIXME Segmentation fault 2018-5-22 01:14:00
            zip_fread(pzip_file, class_data->data, zip_stat.size);

            /* close archive */
            if (zip_close(p_zip) < 0) {
                fprintf(stderr, "can't close zip archive '%s'\n", path);
                return 0;
            }

            return 1;
        }
    }

    return 0;
}


static int readRootClasspath(const char *class_name, struct s_class_data *class_data) {
    const char *jar_path = "/usr/java/jre1.8.0_172-amd64/lib/";

    DIR *dp;
    struct dirent *dirp;

    if ((dp = opendir(jar_path)) == NULL) {
        return 0;
    }

    while ((dirp = readdir(dp)) != NULL) {
        if (strcmp(dirp->d_name, ".") == 0 ||
            strcmp(dirp->d_name, "..") == 0) {
            continue;
        }

        if (strstr(dirp->d_name, ".jar") != NULL || strstr(dirp->d_name, ".JAR") != NULL) {
            char path[1024];
            if (readJAR(strcat(strcpy(path, jar_path), dirp->d_name), class_name, class_data)) {
                return 1;
            }
        }
    }

    closedir(dp);
    return 0;
}

static int readExtClasspath(const char *class_name, struct s_class_data *class_data) {
    const char *jar_path = "/usr/java/jre1.8.0_172-amd64/lib/ext";

    return 0;
}

static int readUserClasspath(const char *class_name, struct s_class_data *class_data) {
    FILE *f;
    f = fopen(class_name, "r");
    int i = 0;
    u1 buf;
    // TODO 1024 ?/?
    class_data->data = (u1*) malloc(sizeof(u1) * 1024);

    while (fread(&buf, sizeof(u1), 1, f) != 0) {
        class_data->data[i++] = buf;
    }

    class_data->index = 0;
    class_data->length = i;
    return 1;
}

void freeClassData(struct s_class_data **class_data) {

    for (int i = 0; i < 1024; ++i) {
        free(&(*class_data)->data[i]);
    }

    (*class_data)->data = NULL;

    free(*class_data);
    *class_data = NULL;
}

struct s_class_data *readClassFile(const char *class_name) {
    struct s_class_data *class_data = malloc(sizeof(struct s_class_data));

    char search[strlen(class_name) + 7];
    strcpy(search, class_name);

    if (strstr(search, ".class") == NULL) {
        // add .class
        // java/lang/Object  -->  java/lang/Object.class
        strcat(search, ".class");
    }

    if (readRootClasspath(search, class_data)) {
        return class_data;
    }

    if (readExtClasspath(search, class_data)) {
        return class_data;
    }

    if (readUserClasspath(search, class_data)) {
        return class_data;
    }

    return NULL;
}

struct ClassFile parseClassContent(struct s_class_data *class_data) {
    struct ClassFile class_file;
    readAndCheckMagic(class_data, &class_file);
    readAndCheckVersion(class_data, &class_file);
    readConstantPool(class_data, &class_file);
    printf("readConstantPool\n");
    class_file.access_flags = readU2(class_data);
    class_file.this_class = readU2(class_data);
    class_file.super_class = readU2(class_data);
    class_file.interfaces_count = readU2(class_data);
    printf("readFields\n");
    // TODO interfaces
    readFields(class_data, &class_file);
    readMethods(class_data, &class_file);
    class_file.attributes_count = readU2(class_data);
    class_file.attributes = (struct AttributeInfo *) malloc(sizeof(struct AttributeInfo) * class_file.attributes_count);

    for (int i = 0; i < class_file.attributes_count; i++) {
        class_file.attributes[i] = *readAttributes(class_data, class_file.constant_pool_info);
    }

    return class_file;
}

static char *utf8String(struct CONSTANT_Utf8_info *utf8_info) {
    u2 length = utf8_info->length;
    char *result = (char *) malloc((length + 1) * sizeof(char));
    for (int i = 0; i < length; ++i) {
        u1 byte = utf8_info->bytes[i];
        if (byte < 127) {
            result[i] = byte;
        } else {
            printf("TODO byte >= 127 \n");
            // TODO
            result[i] = '#';
        }
    }

    result[length] = '\0';

    return result;
}

struct CONSTANT_Utf8_info *utf8Info(const u2 index, const struct ConstantPoolInfo *constant_pool_info) {
    return &constant_pool_info[index - 1].info.utf8_info;
}

struct CONSTANT_Class_info *classInfo(const u2 index, const struct ConstantPoolInfo *constant_pool_info) {
    return &constant_pool_info[index - 1].info.class_info;
}

char *className(const u2 class_index, struct ConstantPoolInfo *constant_pool_info) {
    struct CONSTANT_Class_info *class_info = classInfo(class_index, constant_pool_info);
   return ConstantPoolInfo_getUtf8String(constant_pool_info, class_info->name_index);
}

char *memberName(struct MemberInfo *member, struct ConstantPoolInfo *constant_pool_info) {
    return ConstantPoolInfo_getUtf8String(constant_pool_info, member->name_index);
}

char *descriptor(struct MemberInfo *member, struct ConstantPoolInfo *constant_pool_info) {
    return ConstantPoolInfo_getUtf8String(constant_pool_info, member->descriptor_index);
}

char *attributeName(const u2 attribute_name_index, struct ConstantPoolInfo *constant_pool_info) {
    return ConstantPoolInfo_getUtf8String(constant_pool_info, attribute_name_index);
}

char *ConstantPoolInfo_getUtf8String(struct ConstantPoolInfo *constant_pool_info, const u2 index) {
    struct CONSTANT_Utf8_info *info = utf8Info(index, constant_pool_info);
    return utf8String(info);
}


struct CONSTANT_NameAndType_info ConstantPoolInfo_getNameAndType(const struct ConstantPoolInfo *constant_pool_info,
                                                                 const u2 index) {
    return constant_pool_info[index - 1].info.nameAndType_info;
}

void freeString(char **str) {
    printf("freeString\n");
    size_t len = strlen(*str);
//    char *tmp = *str;
//    printf("freeString %p\n", &tmp );
//    printf("freeString %p\n", &(*tmp++) );
//    for (int i = 0; i <= len; ++i) {
//        printf("freeString 1 %c\n", *tmp );
//        printf("freeString 1 %p\n", tmp++ );
//        printf("freeString 1 %c\n", *(tmp+1) );
////        free(tmp);
//        printf("freeString 2 %c\n", *tmp );
//    }
//    tmp = NULL;
//    *str = NULL;
}

struct AttributeInfo *codeAttribute(const struct MemberInfo *member,
                                             struct ConstantPoolInfo *constant_pool_info) {
    for (int i = 0; i < member->attributes_count; ++i) {
        char *name = attributeName(member->attributes[i].attribute_name_index, constant_pool_info);

        if (strcmp(ATTRIBUTE_Code, name) == 0) {
            return &member->attributes[i];
        }
        freeString(&name);
    }

    return NULL;
}

struct AttributeInfo *constantValueAttribute(const struct MemberInfo *member,
                                             struct ConstantPoolInfo *constant_pool_info) {
    for (int i = 0; i < member->attributes_count; ++i) {
        char *name = attributeName(member->attributes[i].attribute_name_index, constant_pool_info);
        if (strcmp(ATTRIBUTE_ConstantValue, name) == 0) {
            freeString(&name);
            return &member->attributes[i];
        }
    }

    return NULL;
}

void printClassInfo(struct ClassFile *class_file) {
    printf("version: %d.%d\n", class_file->major_version, class_file->minor_version);
    printf("constants count: %u\n", class_file->constant_pool_count);
    printConstantPoolUtf8Info(class_file->constant_pool_info, class_file->constant_pool_count);
    printf("access flags: 0x%x\n", class_file->access_flags);
    printf("this class: %d\n", class_file->this_class);
    printf("super class: %d\n", class_file->super_class);
    printf("interfaces: %d\n", class_file->interfaces_count);
    printf("fields count: %d\n", class_file->fields_count);
    printf("methods count: %d\n", class_file->methods_count);
    for (int i = 0; i < class_file->methods_count; ++i) {
        printMemberInfo(&class_file->fields[i]);
    }
}

void printConstantPoolUtf8Info(struct ConstantPoolInfo *constant_pool_info, u2 count) {
    printf("\tprintUtf8 \n");

    for (int i = 0; i < count; ++i) {
        struct ConstantPoolInfo info = constant_pool_info[i];

        if (info.tag == 1) {
            printf("\t\t ConstantPool index: %d \n", i);
            printf("\t\t ");
            printUtf8Info(&info);
        }
    }
}


void printUtf8Info(struct ConstantPoolInfo *utf8) {
    printUtf8(&utf8->info.utf8_info);
}

void printUtf8(struct CONSTANT_Utf8_info *utf8_info) {
    printf("[%d] ", utf8_info->length);

    for (int j = 0; j < utf8_info->length; ++j) {
        printf("%x ", utf8_info->bytes[j]);
    }
    printf("\n");
}

void printMemberInfo(struct MemberInfo *member_info) {
    printf("\t member_info:\n");
    printf("\t\t access_flags:%d\n", member_info->access_flags);
    printf("\t\t name_index:%d\n", member_info->name_index);
    printf("\t\t descriptor_index:%d\n", member_info->descriptor_index);
}
//
//int main() {
//    struct s_class_data class_data = readClassFile("Test.class");
//    struct ClassFile class_file = parseClassContent(&class_data);
//    printClassInfo(&class_file);
//}
