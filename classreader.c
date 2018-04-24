//
// Created by sulvto on 18-4-24.
//


struct s_class {
	u32				magic;
	u16				minorVersion;
	u16 			majorVersion;
	ConstantPool 	constant_pool;
	u16				access_flags;
	u16				this_class;
	u16 			super_class;
	u16[]			interfaces;
	MemberInfo[]	fields;
	MemberInfo[] 	methods;
	AttributeInfo[]	attributes;	
}

struct s_class_data {
	u8 data[];
	int index;
};


u8 readU8(s_class_data *class_data)
{
	return class_data->data[class_data->index++];
}

u16 readU16(s_class_data *class_data) 
{
	u16 d = readU8(class_data);
	d = d << 8;
	return d | readU8(class_data);
}

u32 readU32(s_class_data *class_data)
{
	u32 d = readU16(class_data);
	d = d << 16;              	
    return d | readU16(class_data);
}

u64 readU64(s_class_data *class_data) 
{
	u64 d = readU32(class_data);
    d = d << 32;
    return d | readU32(class_data);
}

u16 *readU16s(s_class_data *class_data)
{
	int n = readU16(class_data);
	u16 d[n];

	for (int i=0; i < n; i++) {
		d[i] = readU16();
	}
	
	return d;
}



void readAndCheckMagic(s_class_data *class_data, s_class *class)
{
	class->magic = readU32(s_class_data);
	if (class->magic != 0xCAFEBASE) {
		printf("Class format error: magic!");
		exit(1);
	}
}

void readAndCheckVersion(s_class_data *class_data, s_class *class)
{
	class->minorVersion = readU16(s_class_data);
	class->majorVersion = readU16(s_class_data);

	switch (class->majorVersion)
		case 45: return;
		case 46:
		case 47:
		case 48:
		case 49:
		case 50:
		case 51:
		case 52:
			return;
		default:
			printf("Un supported class version error!");
			exit(1);
}

s_class *parse(u8 []data) 
{
	s_class class;
	s_class_data class_data;
	readAndCheckMagic(s_class_data, s_class);
	readAndCheckVersion(s_class_data, s_class);

}
