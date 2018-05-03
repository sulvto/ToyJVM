//
// Created by sulvto on 18-5-1.
//

#include "class.h"
#include "rtda.h"
#include "classreader.h"
#include "flags.h"

void verify(struct Class *_class)
{
    prepare(_class);
}

void prepare(struct Class *_class)
{
    calcInstanceFieldSlotIds(_class);
    calcStaticFieldSlotIds(_class);
    allocAndInitStaticVars(_class);
}

u4 isLongOrDouble(struct Field *field)
{
    return (strcmp("J", field->descriptor) == 0) || (strcmp("D", field->descriptor) == 0);
}


void calcInstanceFieldSlotIds(struct Class *_class)
{
    u4 slot_id = 0;
    if (_class->super_class != NULL) {
        slot_id = _class->super_class->interface_slot_count;
    }

    for (int i = 0; i < _class->fields_count; ++i) {
        struct Field *field = &_class->fields[i];
        if (field->access_flags != ACC_STATIC) {
            field->slot_id = slot_id;
            slot_id++;
            if (isLongOrDouble(field)) {
                slot_id++;
            }
        }
    }

    _class->interface_slot_count = slot_id;
}

void calcStaticFieldSlotIds(struct Class *_class)
{
    u4 slot_id = 0;

    for (int i = 0; i < _class->fields_count; ++i) {
        struct Field *field = &_class->fields[i];
        if (field->access_flags == ACC_STATIC) {
            field->slot_id = slot_id;
            slot_id++;
            if (isLongOrDouble(field)) {
                slot_id++;
            }
        }
    }

    _class->interface_slot_count = slot_id;
}

void allocAndInitStaticVars(struct Class *_class)
{
    _class->static_vars = newSlots(_class->static_slot_count);
    for (int i = 0; i < _class->fields_count; ++i) {
        struct Field *field = &_class->fields[i];
        if (field->access_flags == ACC_STATIC && field->access_flags == ACC_FINAL) {
            initStaticFinalVar(_class, field);
        }
    }
}

void initStaticFinalVar(struct Class *_class, struct Field *field)
{
    struct Slots *slots = _class->static_vars;
    struct ConstantPool *constantPool= _class->constant_pool;
    u4 slot_id = field->slot_id;
    if (field.const_value_index > 0) {
        switch (field->descriptor) {
            case "Z":
            case "B":
            case "C":
            case "S":
                break;
            case "I":
                int value = getConstent(field.const_value_index);
                setInt(field.const_value_index, value, slots);
                break;
            case "J":
                Long value = getConstent(field.const_value_index);
                setLong(field.const_value_index, value, slots);
                break;
            case "F":
                float value = getConstent(field.const_value_index);
                setFloat(field.const_value_index, value, slots);
                break;
            case "D":
                double value = getConstent(field.const_value_index);
                setDouble(field.const_value_index, value, slots);
            case "Ljava/lang/String":
                // TODO
                printf("Ljava/lang/String\n");
                break;
        }
    }
}

void link(struct Class *_class)
{
    verify(_class);
    prepare(_class);
}

struct ConstantPool newConstantPool(struct Class *_class, struct  ClassFile *class_file)
{
    u2 count = class_file->constant_pool_count;

    struct ConstantPool *constant_pool = (struct ConstantPool *) malloc(sizeof(struct ConstantPool));;
    constant_pool._class = _class;
    constant_pool.size = count;
    constant_pool.constants = (union Constant *) malloc(sizeof(union Constant) * count);
    for (int i = 0; i < count; ++i) {
        struct ConstantPoolInfo constant_pool_info = class_file->constant_pool[i];
            switch (constant_pool_info.tag) {
                case CONSTANT_Class:
                    struct ClassRef class_ref;
                    class_ref.constant_pool = constant_pool;
                    class_ref._class = NULL;
                    className(class_file, class_file->constant_pool, class_ref.class_name);
                    break;
                case CONSTANT_Methodref:
                    struct MethodRef method_ref;
                    method_ref._class = NULL;
                    method_ref.method = NULL;
                    method_ref.constant_pool = constant_pool;
                    // name and type
                    struct CONSTANT_NameAndType_info nameAndType_info = ConstantPoolInfo_getNameAndType(class_file->constant_pool,
                                                    constant_pool_info.info.methodref_info.name_and_type_index);
                    ConstantPoolInfo_getUtf8String(class_file->constant_pool, nameAndType_info.name_index,
                                             method_ref.name);
                    ConstantPoolInfo_getUtf8String(class_file->constant_pool, nameAndType_info.descriptor_index,
                                             method_ref.descriptor);

                    className(class_file->this_class, class_file->constant_pool, &method_ref.class_name);
                    // TODO ? method_ref
                    break;
                case CONSTANT_Fieldref:
                    struct FieldRef field_ref;
                    field_ref._class = NULL;
                    field_ref.field = NULL;
                    field_ref.constant_pool = constant_pool;
                    // name and type
                    struct CONSTANT_NameAndType_info nameAndType_info = ConstantPoolInfo_getNameAndType(class_file->constant_pool,
                                                                                                        constant_pool_info.info.fieldref_info.name_and_type_index);
                    ConstantPoolInfo_getUtf8String(class_file->constant_pool, nameAndType_info.name_index,
                                                   field_ref.name);
                    ConstantPoolInfo_getUtf8String(class_file->constant_pool, nameAndType_info.descriptor_index,
                                                   field_ref.descriptor);

                    className(class_file->this_class, class_file->constant_pool, &field_ref.class_name);

                    break;
                case CONSTANT_InterfaceMethodref_info:
                    // TODO
                    struct InterfaceMethodRef interface_method_ref;
                    interface_method_ref._class = NULL;
                    interface_method_ref.method = NULL;
                    interface_method_ref.constant_pool = constant_pool;
                    // name and type
                    struct CONSTANT_NameAndType_info nameAndType_info = ConstantPoolInfo_getNameAndType(class_file->constant_pool,
                                                                                                        constant_pool_info.info.interfaceMethodref_info.name_and_type_index);
                    ConstantPoolInfo_getUtf8String(class_file->constant_pool, nameAndType_info.name_index,
                                                   interface_method_ref.name);
                    ConstantPoolInfo_getUtf8String(class_file->constant_pool, nameAndType_info.descriptor_index,
                                                   interface_method_ref.descriptor);

                    className(class_file->this_class, class_file->constant_pool, &interface_method_ref.class_name);
                    break;
                default:
                // TODO
            }
    }

}

struct Field *newFields(struct Class *_class, struct ClassFile *class_file)
{
    u2 fields_count = class_file->fields_count;
    struct Field *fields = (struct Field *) malloc(sizeof(struct Field) * fields_count);
    //
    for (int i = 0; i < fields_count; ++i) {
        fields[i]._class = _class;
        copyFieldInfo(&class_file->attributes[i], &fields[i], class_file->constant_pool);
    }
}

void copyFieldInfo(struct MemberInfo *field_info, struct Field *field, struct ConstantPoolInfo *constant_pool)
{
    field->access_flags = field_info->access_flags;
    memberName(field_info, constant_pool, field->name);
    descriptor(field_info, constant_pool, field->descriptor);
    struct AttributeInfo *attribute_info = constantValueAttribute(field_info, constant_pool);
    if (attribute_info != NULL) {
        field->const_value_index = attribute_info->info.constant_value.constant_value_index;
    }
}

struct Class newClass(struct ClassFile *class_file)
{
    struct Class _class;

    _class->access_flags = class_file->access_flags;

    className(class_file->this_class, class_file->constant_pool, &_class->name);
    className(class_file->super_class, class_file->constant_pool, &_class.super_class_name);
    // interfaces_count
    _class.constant_pool_count = class_file->constant_pool_count;
    _class.constant_pool = newConstantPool(_class, class_file);
    _class.fields = newFields(_class, class_file);
    _class.methods = newFields(_class, class_file);
}

struct Class *loadClass(const struct ClassLoader *loader, const char *name)
{
    // map find
    return loadNonArrayClass(name);
}

struct Class *loadNonArrayClass(const char *name)
{
    struct s_class_data class_data = readClassFile(name);
    struct Class *_class = defineClass(class_data);
    link(_class);
    printf("[Loaded %s from %s]\n", name, "from");
    return _class;
}

void resolveSuperClass(struct Class *_class)
{
    if (strcmp(_class->name, "java/lang/Object") != 0) {
        _class->super_class = loadClass(_class->super_class_name);
    } else {
        _class->super_class = NULL;
    }
}

void resolveInterfaces(struct Class *_class)
{

}

struct Class *defineClass(struct s_class_data *class_data)
{
    struct Class *_class = parseClass(class_data);
    resolveSuperClass(_class);
    resolveInterfaces(_class);
    // map to
    return readClassFile(name);
}

struct Class *parseClass(struct s_class_data *class_data)
{
    struct ClassFile class_file = parseClassContent(class_data);
    return newClass(&class_file);
}



struct Class *resolvedField(struct FieldRef *field_ref)
{
    if (field_ref->field == NULL) {
        resolveFieldRef(field_ref);
    }

    return class_ref->_class;
}

void resolveFieldRef(struct FieldRef *field_ref)
{
    struct Class *d = field_ref->constant_pool->_class;
    struct Class *c;
    resolvedClass(field_ref, c);
    // TODO

}