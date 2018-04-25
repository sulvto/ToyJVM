//
// Created by sulvto on 18-4-24.
//
#include <stdio.h>
#include "type.h"

struct ConstantPool {

};

struct AttributeInfo {

};

struct MemberInfo {
	struct ConstantPool	    cp;
	u16				        accessFlags;
	u16				        nameIndex;
	u16				        descriptorIndex;
    struct AttributeInfo    *attributes;
};

struct s_class {
	u32				        magic;
	u16				        minorVersion;
	u16 	        		majorVersion;
	struct ConstantPool 	constantPool;
	u16				        accessFlags;
	u16				        thisClass;
	u16 			        superClass;
	u16				        *interfaces;
	struct MemberInfo		*fields;
	struct MemberInfo 		*methods;
	struct AttributeInfo	*attributes;
};

struct s_class_data {
	u8 *data;
    int length;
	int index;
};


u8 readU8(struct s_class_data *class_data)
{
	return class_data->data[class_data->index++];
}

u16 readU16(struct s_class_data *class_data)
{
	u16 d = readU8(class_data);
	d = d << 8;
	return d | readU8(class_data);
}

u32 readU32(struct s_class_data *class_data)
{
	u32 d = readU16(class_data);
	d = d << 16;
    return d | readU16(class_data);
}

u64 readU64(struct s_class_data *class_data)
{
	u64 d = readU32(class_data);
    d = d << 32;
    return d | readU32(class_data);
}

u16 *readU16s(struct s_class_data *class_data)
{
	int n = readU16(class_data);
	u16 d[n];

	for (int i=0; i < n; i++) {
		d[i] = readU16(class_data);
	}

	return d;
}



void readAndCheckMagic(struct s_class_data *class_data, struct s_class *_class)
{
	_class->magic = readU32(class_data);

    // 16 -> 10
    // CAFEBABE -> 3405691582
	if (_class->magic != 3405691582) {
		printf("Class format error: magic!\n");
		exit(1);
	}
}

void readAndCheckVersion(struct s_class_data *class_data, struct s_class *_class)
{
	_class->minorVersion = readU16(class_data);
	_class->majorVersion = readU16(class_data);

	switch (_class->majorVersion) {
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
            if (_class->minorVersion == 0) {
                break;
            }
        default:
            printf("Un supported class version(%u.%u) error!\n", _class->majorVersion, _class->minorVersion);
            exit(1);
    }

}

struct ConstantPool readConstantPool(struct s_class_data *class_data)
{
    int count = readU16(class_data);
    ConstantPool cp;
    // TODO

}


struct AttributeInfo *readAttributes(struct s_class_data *class_data)
{

}

struct MemberInfo readMember(struct s_class_data *class_data, struct ConstantPool *cp)
{
    struct MemberInfo memberInfo;
    memberInfo.cp = *cp;
    memberInfo.accessFlags = readU16(class_data);
    memberInfo.nameIndex = readU16(class_data);
    memberInfo.descriptorIndex = readU16(class_data);
    memberInfo.attributes = readAttributes(class_data, cp);

    return memberInfo;
}

struct MemberInfo *readMembers(struct s_class_data *class_data, struct ConstantPool *cp)
{
    int count = readU8(class_data);
    struct MemberInfo members[count];

    for (int i=0; i<count; i++) {
        members[i] = readMember(class_data, cp);
    }

    return members;
}


struct s_class_data readClass(const char *className)
{
    FILE *f;
    f = fopen(className, "r");
    printf("class_data open %s\n", className);
    struct s_class_data class_data;
    u8 data[1024];
    int i = 0;
    u8 buf;
    while (fread(&buf, sizeof(u8), 1, f) != 0) {
        data[i] = buf;
        i++;
    }
    class_data.data = &data;

    class_data.index = 0;
    class_data.length = i;

    return class_data;
}

struct s_class parseClass(struct s_class_data *class_data)
{
	struct s_class _class;
	readAndCheckMagic(class_data, &_class);
	readAndCheckVersion(class_data, &_class);
    _class.constantPool = readConstantPool(class_data);
    _class.accessFlags= readU16(class_data);
    _class.thisClass = readU16(class_data);
    _class.superClass = readU16(class_data);
    _class.interfaces = readU16(class_data);
    _class.fields = readMembers(class_data, _class.constantPool);
    _class.methods = readMembers(class_data, _class.constantPool);
    _class.attributes = readAttributes(class_data);
    return _class;
}

void printClassInfo(struct s_class *_class) {
    printf("version: %d.%d\n", _class->majorVersion, _class->minorVersion);
//    printf("constants count: %v\n", _class->constant_pool);
    printf("access flags: %c\n", _class->access_flags);
    printf("this class: %c\n", _class->this_class);
    printf("super class: \n");
    printf("interfaces: \n");
    printf("fields count: \n");
    printf("methods count: \n");
}

int main()
{
    struct s_class_data class_data = readClass("Test.class");
    struct s_class _class = parseClass(&class_data);
    printClassInfo(&_class);
}
