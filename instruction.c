//
// Created by sulvto on 18-4-30.
//

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "rtda.h"
#include "bytecode.h"
#include "classloader.h"
#include "classref.h"
#include "array.h"
#include "instruction.h"
#include "flags.h"
#include "native.h"

// array type
#define AT_BOOLEAN  4
#define AT_BYTE     5
#define AT_CHAR     6
#define AT_SHORT    7
#define AT_INT      8
#define AT_LONG     9
#define AT_FLOAT    10
#define AT_DOUBLE   11


Object newObject(Class _class);

int Object_isInterfaceOf(Object _this, Class _other);

void initClass(Thread thread, Class _class);

Class getPrimitiveArrayClass(ClassLoader loader, unsigned int atype);

void scheduleClinit(Thread thread, Class _class);

Class arrayClass(Class _this);

static void invokeMethod(Frame invoker_frame, Method method);

static int findAndGotoExceptionHandler(Thread thread, Object ex);

static int handlerUncaughtException(Thread thread, Object ex);

void nop_fetchOp(union Context *context, struct Bytecode *data) {
    // noting to do
}

void branch_fetchOp(union Context *context, struct Bytecode *data) {
    context->offset = readBytecodeU2(data);
}

void branch(Frame frame, int offset) {
    Thread thread = Frame_thread(frame);
    int pc = Thread_getPc(thread);
    Frame_setNextPC(frame, pc + offset);
}

void index8_fetchOp(union Context *context, struct Bytecode *data) {
    context->index = readBytecodeU1(data);
}

void index16_fetchOp(union Context *context, struct Bytecode *data) {
    context->index = readBytecodeU2(data);
}

void nop_exe(union Context *context, Frame frame) {

}

void aconst_null_exe(union Context *context, Frame frame) {
    Frame_pushRef(frame, NULL);
}

void iconst_m1_exe(union Context *context, Frame frame) {
    Frame_pushInt(frame, -1);
}

void iconst_0_exe(union Context *context, Frame frame) {
    Frame_pushInt(frame, 0);
}

void iconst_1_exe(union Context *context, Frame frame) {
    Frame_pushInt(frame, 1);
}

void iconst_2_exe(union Context *context, Frame frame) {
    Frame_pushInt(frame, 2);
}

void iconst_3_exe(union Context *context, Frame frame) {
    Frame_pushInt(frame, 3);
}

void iconst_4_exe(union Context *context, Frame frame) {
    Frame_pushInt(frame, 4);
}

void iconst_5_exe(union Context *context, Frame frame) {
    Frame_pushInt(frame, 5);
}

void lconst_0_exe(union Context *context, Frame frame) {
    Frame_pushLong(frame, 0);
}

void lconst_1_exe(union Context *context, Frame frame) {
    Frame_pushLong(frame, 1);
}

void fconst_0_exe(union Context *context, Frame frame) {
    Frame_pushFloat(frame, 0.0);
}

void fconst_1_exe(union Context *context, Frame frame) {
    Frame_pushFloat(frame, 1.0);
}

void fconst_2_exe(union Context *context, Frame frame) {
    Frame_pushFloat(frame, 2.0);
}

void dconst_0_exe(union Context *context, Frame frame) {
    Frame_pushDouble(frame, 0.0);
}

void dconst_1_exe(union Context *context, Frame frame) {
    Frame_pushDouble(frame, 1.0);
}

void bipush_fetchOp(union Context *context, struct Bytecode *bytecode_data) {
    // TODO byte int
    context->bi = readBytecodeU1(bytecode_data);
}

void bipush_exe(union Context *context, Frame frame) {
    u1 bi = context->bi;
    Frame_pushInt(frame, bi);

}

void sipush_fetchOp(union Context *context, struct Bytecode *bytecode_data) {
    // TODO short int
    context->si = readBytecodeU2(bytecode_data);
}

void sipush_exe(union Context *context, Frame frame) {
    short si = context->si;
    Frame_pushInt(frame, si);
}

void ldc_exe(union Context *context, Frame frame) {

}

void ldc_w_exe(union Context *context, Frame frame) {

}

void ldc2_w_exe(union Context *context, Frame frame) {

}

void iload(Frame frame, const unsigned int index) {
    int i = Frame_getInt(frame, index);
    Frame_pushInt(frame, i);
}

void lload(Frame frame, const unsigned int index) {
    long l = Frame_getLong(frame, index);
    Frame_pushLong(frame, l);
}

void fload(Frame frame, const unsigned int index) {
    float f = Frame_getFloat(frame, index);
    Frame_pushFloat(frame, f);
}

void dload(Frame frame, const unsigned int index) {
    double d = Frame_getDouble(frame, index);
    Frame_pushDouble(frame, d);
}

void iload_exe(union Context *context, Frame frame) {
    iload(frame, context->index);
}

void lload_exe(union Context *context, Frame frame) {
    lload(frame, context->index);
}

void fload_exe(union Context *context, Frame frame) {
    fload(frame, context->index);
}

void dload_exe(union Context *context, Frame frame) {
    dload(frame, context->index);
}

void aload_exe(union Context *context, Frame frame) {

}

void iload_0_exe(union Context *context, Frame frame) {
    iload(frame, 0);
}

void iload_1_exe(union Context *context, Frame frame) {
    iload(frame, 1);
}

void iload_2_exe(union Context *context, Frame frame) {
    iload(frame, 2);
}

void iload_3_exe(union Context *context, Frame frame) {
    iload(frame, 3);
}

void lload_0_exe(union Context *context, Frame frame) {
    lload(frame, 0);
}

void lload_1_exe(union Context *context, Frame frame) {
    lload(frame, 1);
}

void lload_2_exe(union Context *context, Frame frame) {
    lload(frame, 2);
}

void lload_3_exe(union Context *context, Frame frame) {
    lload(frame, 3);
}

void fload_0_exe(union Context *context, Frame frame) {
    fload(frame, 0);
}

void fload_1_exe(union Context *context, Frame frame) {
    fload(frame, 1);
}

void fload_2_exe(union Context *context, Frame frame) {
    fload(frame, 2);
}

void fload_3_exe(union Context *context, Frame frame) {
    fload(frame, 3);
}

void dload_0_exe(union Context *context, Frame frame) {
    dload(frame, 0);
}

void dload_1_exe(union Context *context, Frame frame) {
    dload(frame, 1);
}

void dload_2_exe(union Context *context, Frame frame) {
    dload(frame, 2);
}

void dload_3_exe(union Context *context, Frame frame) {
    dload(frame, 3);
}

void aload_0_exe(union Context *context, Frame frame) {

}

void aload_1_exe(union Context *context, Frame frame) {

}

void aload_2_exe(union Context *context, Frame frame) {

}

void aload_3_exe(union Context *context, Frame frame) {

}

void iaload_exe(union Context *context, Frame frame) {

}

void laload_exe(union Context *context, Frame frame) {

}

void faload_exe(union Context *context, Frame frame) {

}

void daload_exe(union Context *context, Frame frame) {

}

void aaload_exe(union Context *context, Frame frame) {

}

void baload_exe(union Context *context, Frame frame) {

}

void caload_exe(union Context *context, Frame frame) {

}

void saload_exe(union Context *context, Frame frame) {

}

void istore(Frame frame, const unsigned int index) {
    int i = Frame_popInt(frame);
    Frame_setInt(frame, index, i);
}

void lstore(Frame frame, const unsigned int index) {
    long l = Frame_popLong(frame);
    Frame_setLong(frame, index, l);
}

void fstore(Frame frame, const unsigned int index) {
    float f = Frame_popFloat(frame);
    Frame_setFloat(frame, index, f);
}

void dstore(Frame frame, const unsigned int index) {
    double d = Frame_popDouble(frame);
    Frame_setDouble(frame, index, d);
}

void istore_exe(union Context *context, Frame frame) {
    istore(frame, context->index);
}

void lstore_exe(union Context *context, Frame frame) {
    lstore(frame, context->index);
}

void fstore_exe(union Context *context, Frame frame) {
    fstore(frame, context->index);
}

void dstore_exe(union Context *context, Frame frame) {
    dstore(frame, context->index);
}

void astore_exe(union Context *context, Frame frame) {

}

void istore_0_exe(union Context *context, Frame frame) {
    istore(frame, 0);
}

void istore_1_exe(union Context *context, Frame frame) {
    istore(frame, 1);
}

void istore_2_exe(union Context *context, Frame frame) {
    istore(frame, 2);
}

void istore_3_exe(union Context *context, Frame frame) {
    istore(frame, 3);
}

void lstore_0_exe(union Context *context, Frame frame) {
    lstore(frame, 0);
}

void lstore_1_exe(union Context *context, Frame frame) {
    lstore(frame, 1);
}

void lstore_2_exe(union Context *context, Frame frame) {
    lstore(frame, 2);
}

void lstore_3_exe(union Context *context, Frame frame) {
    lstore(frame, 3);
}

void fstore_0_exe(union Context *context, Frame frame) {
    fstore(frame, 0);
}

void fstore_1_exe(union Context *context, Frame frame) {
    fstore(frame, 1);
}

void fstore_2_exe(union Context *context, Frame frame) {
    fstore(frame, 2);
}

void fstore_3_exe(union Context *context, Frame frame) {
    fstore(frame, 3);
}

void dstore_0_exe(union Context *context, Frame frame) {
    dstore(frame, 0);
}

void dstore_1_exe(union Context *context, Frame frame) {
    dstore(frame, 1);
}

void dstore_2_exe(union Context *context, Frame frame) {
    dstore(frame, 2);
}

void dstore_3_exe(union Context *context, Frame frame) {
    dstore(frame, 3);
}

void astore_0_exe(union Context *context, Frame frame) {

}

void astore_1_exe(union Context *context, Frame frame) {

}

void astore_2_exe(union Context *context, Frame frame) {

}

void astore_3_exe(union Context *context, Frame frame) {

}

void iastore_exe(union Context *context, Frame frame) {

}

void lastore_exe(union Context *context, Frame frame) {

}

void fastore_exe(union Context *context, Frame frame) {

}

void dastore_exe(union Context *context, Frame frame) {

}

void aastore_exe(union Context *context, Frame frame) {

}

void bastore_exe(union Context *context, Frame frame) {

}

void castore_exe(union Context *context, Frame frame) {

}

void sastore_exe(union Context *context, Frame frame) {

}

void pop_exe(union Context *context, Frame frame) {
    Frame_popSlot(frame);
}

void pop2_exe(union Context *context, Frame frame) {
    Frame_popSlot(frame);
    Frame_popSlot(frame);
}

void dup_exe(union Context *context, Frame frame) {
    Slot slot = Frame_popSlot(frame);
    Frame_pushSlot(frame, slot);
    Frame_pushSlot(frame, slot);
}

void dup_x1_exe(union Context *context, Frame frame) {

}

void dup_x2_exe(union Context *context, Frame frame) {

}

void dup2_exe(union Context *context, Frame frame) {

}

void dup2_x1_exe(union Context *context, Frame frame) {

}

void dup2_x2_exe(union Context *context, Frame frame) {

}

void swap_exe(union Context *context, Frame frame) {
    Slot slot1 = Frame_popSlot(frame);
    Slot slot2 = Frame_popSlot(frame);
    Frame_pushSlot(frame, slot1);
    Frame_pushSlot(frame, slot2);
}

void iadd_exe(union Context *context, Frame frame) {
    int a = Frame_popInt(frame);
    int b = Frame_popInt(frame);
    printf("iadd %d\n", a + b);
    Frame_pushInt(frame, a + b);
}

void ladd_exe(union Context *context, Frame frame) {
    long a = Frame_popLong(frame);
    long b = Frame_popLong(frame);
    Frame_pushLong(frame, a + b);
}

void fadd_exe(union Context *context, Frame frame) {
    float a = Frame_popFloat(frame);
    float b = Frame_popFloat(frame);
    Frame_pushFloat(frame, a + b);
}

void dadd_exe(union Context *context, Frame frame) {
    double a = Frame_popDouble(frame);
    double b = Frame_popDouble(frame);
    Frame_pushDouble(frame, a + b);
}

void isub_exe(union Context *context, Frame frame) {
    int a = Frame_popInt(frame);
    int b = Frame_popInt(frame);
    Frame_pushInt(frame, a - b);
}

void lsub_exe(union Context *context, Frame frame) {
    long a = Frame_popLong(frame);
    long b = Frame_popLong(frame);
    Frame_pushLong(frame, a - b);
}

void fsub_exe(union Context *context, Frame frame) {
    float a = Frame_popFloat(frame);
    float b = Frame_popFloat(frame);
    Frame_pushFloat(frame, a - b);
}

void dsub_exe(union Context *context, Frame frame) {
    double a = Frame_popDouble(frame);
    double b = Frame_popDouble(frame);
    Frame_pushDouble(frame, a - b);
}

void imul_exe(union Context *context, Frame frame) {
    int a = Frame_popInt(frame);
    int b = Frame_popInt(frame);
    Frame_pushInt(frame, a * b);
}

void lmul_exe(union Context *context, Frame frame) {
    long a = Frame_popLong(frame);
    long b = Frame_popLong(frame);
    Frame_pushLong(frame, a * b);
}

void fmul_exe(union Context *context, Frame frame) {
    float a = Frame_popFloat(frame);
    float b = Frame_popFloat(frame);
    Frame_pushFloat(frame, a * b);
}

void dmul_exe(union Context *context, Frame frame) {
    double a = Frame_popDouble(frame);
    double b = Frame_popDouble(frame);
    Frame_pushDouble(frame, a * b);
}

void idiv_exe(union Context *context, Frame frame) {
    int a = Frame_popInt(frame);
    int b = Frame_popInt(frame);
    if (a == 0) {
        // TODO
    }

    div_t result = div(b, a);

    Frame_pushInt(frame, result.quot);
}

void ldiv_exe(union Context *context, Frame frame) {
    long a = Frame_popLong(frame);
    long b = Frame_popLong(frame);
    if (a == 0) {
        // TODO
    }

    ldiv_t result = ldiv(b, a);

    Frame_pushLong(frame, result.quot);
}

void fdiv_exe(union Context *context, Frame frame) {
    float a = Frame_popFloat(frame);
    float b = Frame_popFloat(frame);
    if (a == 0) {
        // TODO
    }
    Frame_pushFloat(frame, b / a);
}

void ddiv_exe(union Context *context, Frame frame) {
    double a = Frame_popDouble(frame);
    double b = Frame_popDouble(frame);
    if (a == 0) {
        // TODO
    }
    Frame_pushDouble(frame, b / a);
}

void irem_exe(union Context *context, Frame frame) {
    int a = Frame_popInt(frame);
    int b = Frame_popInt(frame);
    if (a == 0) {
        // TODO
    }

    div_t result = div(b, a);

    Frame_pushInt(frame, result.rem);
}

void lrem_exe(union Context *context, Frame frame) {
    long a = Frame_popLong(frame);
    long b = Frame_popLong(frame);
    if (a == 0) {
        // TODO
    }

    ldiv_t result = ldiv(b, a);

    Frame_pushLong(frame, result.rem);
}

void frem_exe(union Context *context, Frame frame) {
    float a = Frame_popFloat(frame);
    float b = Frame_popFloat(frame);
    if (a == 0) {
        // TODO
    }
//    pushFloat(fmod(b, a), frame->operand_stack);
}

void drem_exe(union Context *context, Frame frame) {
    double a = Frame_popDouble(frame);
    double b = Frame_popDouble(frame);
    if (a == 0) {
        // TODO
    }
//    pushDouble(fmod(b, a), frame->operand_stack);
}

void ineg_exe(union Context *context, Frame frame) {
    int a = Frame_popInt(frame);
    int b = Frame_popInt(frame);
    Frame_pushInt(frame, a + b);
}

void lneg_exe(union Context *context, Frame frame) {
    long a = Frame_popLong(frame);
    long b = Frame_popLong(frame);
    Frame_pushLong(frame, a + b);
}

void fneg_exe(union Context *context, Frame frame) {
    float a = Frame_popFloat(frame);
    float b = Frame_popFloat(frame);
    Frame_pushFloat(frame, a + b);
}

void dneg_exe(union Context *context, Frame frame) {
    double a = Frame_popDouble(frame);
    double b = Frame_popDouble(frame);
    Frame_pushDouble(frame, a + b);

}

void ishl_exe(union Context *context, Frame frame) {

}

void lshl_exe(union Context *context, Frame frame) {

}

void ishr_exe(union Context *context, Frame frame) {

}

void lshr_exe(union Context *context, Frame frame) {

}

void iushr_exe(union Context *context, Frame frame) {

}

void lushr_exe(union Context *context, Frame frame) {

}

void iand_exe(union Context *context, Frame frame) {
    int v2 = Frame_popInt(frame);
    int v1 = Frame_popInt(frame);
    Frame_pushInt(frame, v1 & v2);
}

void land_exe(union Context *context, Frame frame) {
    long v2 = Frame_popLong(frame);
    long v1 = Frame_popLong(frame);
    Frame_pushLong(frame, v1 & v2);
}

void ior_exe(union Context *context, Frame frame) {
    int v2 = Frame_popInt(frame);
    int v1 = Frame_popInt(frame);
    Frame_pushInt(frame, v1 | v2);
}

void lor_exe(union Context *context, Frame frame) {
    long v2 = Frame_popLong(frame);
    long v1 = Frame_popLong(frame);
    Frame_pushLong(frame, v1 | v2);
}

void ixor_exe(union Context *context, Frame frame) {

}

void lxor_exe(union Context *context, Frame frame) {

}

void iinc_exe(union Context *context, Frame frame) {
    int v = Frame_popInt(frame);
    Frame_pushInt(frame, v + 1);
}

void i2l_exe(union Context *context, Frame frame) {

}

void i2f_exe(union Context *context, Frame frame) {

}

void i2d_exe(union Context *context, Frame frame) {

}

void l2i_exe(union Context *context, Frame frame) {

}

void l2f_exe(union Context *context, Frame frame) {

}

void l2d_exe(union Context *context, Frame frame) {

}

void f2i_exe(union Context *context, Frame frame) {

}

void f2l_exe(union Context *context, Frame frame) {

}

void f2d_exe(union Context *context, Frame frame) {

}

void d2i_exe(union Context *context, Frame frame) {

}

void d2l_exe(union Context *context, Frame frame) {

}

void d2f_exe(union Context *context, Frame frame) {

}

void i2b_exe(union Context *context, Frame frame) {

}

void i2c_exe(union Context *context, Frame frame) {

}

void i2s_exe(union Context *context, Frame frame) {

}

void lcmp_exe(union Context *context, Frame frame) {
    long v2 = Frame_popLong(frame);
    long v1 = Frame_popLong(frame);
    if (v1 > v2) {
        Frame_pushInt(frame, 1);
    } else if (v1 == v2) {
        Frame_pushInt(frame, 0);
    } else {
        Frame_pushInt(frame, -1);
    }
}

void fcmpl_exe(union Context *context, Frame frame) {

}

void fcmpg_exe(union Context *context, Frame frame) {

}

void dcmpl_exe(union Context *context, Frame frame) {

}

void dcmpg_exe(union Context *context, Frame frame) {

}

void ifeq_exe(union Context *context, Frame frame) {
    int v = Frame_popInt(frame);
    if (v == 0) {
        branch(frame, context->offset);
    }
}

void ifne_exe(union Context *context, Frame frame) {
    int v = Frame_popInt(frame);
    if (v != 0) {
        branch(frame, context->offset);
    }
}

void iflt_exe(union Context *context, Frame frame) {
    int v = Frame_popInt(frame);
    if (v < 0) {
        branch(frame, context->offset);
    }
}

void ifge_exe(union Context *context, Frame frame) {
    int v = Frame_popInt(frame);
    if (v >= 0) {
        branch(frame, context->offset);
    }
}

void ifgt_exe(union Context *context, Frame frame) {
    int v = Frame_popInt(frame);
    if (v > 0) {
        branch(frame, context->offset);
    }
}

void ifle_exe(union Context *context, Frame frame) {
    int v = Frame_popInt(frame);
    if (v <= 0) {
        branch(frame, context->offset);
    }
}

void if_icmpeq_exe(union Context *context, Frame frame) {
    int v2 = Frame_popInt(frame);
    int v1 = Frame_popInt(frame);
    if (v2 == v1) {
        branch(frame, context->offset);
    }
}

void if_icmpne_exe(union Context *context, Frame frame) {
    int v2 = Frame_popInt(frame);
    int v1 = Frame_popInt(frame);
    if (v2 != v1) {
        branch(frame, context->offset);
    }
}

void if_icmplt_exe(union Context *context, Frame frame) {
    int v2 = Frame_popInt(frame);
    int v1 = Frame_popInt(frame);
    if (v2 < v1) {
        branch(frame, context->offset);
    }

}

void if_icmpge_exe(union Context *context, Frame frame) {
    int v2 = Frame_popInt(frame);
    int v1 = Frame_popInt(frame);
    if (v2 >= v1) {
        branch(frame, context->offset);
    }

}

void if_icmpgt_exe(union Context *context, Frame frame) {
    int v2 = Frame_popInt(frame);
    int v1 = Frame_popInt(frame);
    if (v2 > v1) {
        branch(frame, context->offset);
    }

}

void if_icmple_exe(union Context *context, Frame frame) {
    int v2 = Frame_popInt(frame);
    int v1 = Frame_popInt(frame);
    if (v2 <= v1) {
        branch(frame, context->offset);
    }

}

void if_acmpeq_exe(union Context *context, Frame frame) {
    Object v2 = Frame_popRef(frame);
    Object v1 = Frame_popRef(frame);
    if (v2 != v1) {
        branch(frame, context->offset);
    }
}

void if_acmpne_exe(union Context *context, Frame frame) {
    Object v2 = Frame_popRef(frame);
    Object v1 = Frame_popRef(frame);
    if (v2 != v1) {
        branch(frame, context->offset);
    }
}

void goto_exe(union Context *context, Frame frame) {
    branch(frame, context->offset);
}

void jsr_exe(union Context *context, Frame frame) {

}

void ret_exe(union Context *context, Frame frame) {

}

void tableswitch_exe(union Context *context, Frame frame) {

}

void lookupswitch_exe(union Context *context, Frame frame) {

}

void ireturn_exe(union Context *context, Frame frame) {
    Thread thread = Frame_thread(frame);
    Frame current_frame = Thread_popFrame(thread);
    Frame invoker_frame = Thread_topFrame(thread);
    int value = Frame_popInt(current_frame);
    Frame_pushInt(invoker_frame, value);
}

void lreturn_exe(union Context *context, Frame frame) {
    Thread thread = Frame_thread(frame);
    Frame current_frame = Thread_popFrame(thread);
    Frame invoker_frame = Thread_topFrame(thread);
    long value = Frame_popLong(current_frame);
    Frame_pushLong(invoker_frame, value);
}

void freturn_exe(union Context *context, Frame frame) {
    Thread thread = Frame_thread(frame);
    Frame current_frame = Thread_popFrame(thread);
    Frame invoker_frame = Thread_topFrame(thread);
    float value = Frame_popFloat(current_frame);
    Frame_pushFloat(invoker_frame, value);

}

void dreturn_exe(union Context *context, Frame frame) {
    Thread thread = Frame_thread(frame);
    Frame current_frame = Thread_popFrame(thread);
    Frame invoker_frame = Thread_topFrame(thread);
    double value = Frame_popDouble(current_frame);
    Frame_pushDouble(invoker_frame, value);
}

void areturn_exe(union Context *context, Frame frame) {
    Thread thread = Frame_thread(frame);
    Frame current_frame = Thread_popFrame(thread);
    Frame invoker_frame = Thread_topFrame(thread);
    Object value = Frame_popRef(current_frame);
    Frame_pushRef(invoker_frame, value);
}

void return_exe(union Context *context, Frame frame) {
    Thread thread = Frame_thread(frame);
    Thread_popFrame(thread);
}

void getstatic_exe(union Context *context, Frame frame) {
    Class current_class = Frame_method(frame);
    FieldRef field_ref = ConstantPool_fieldRef(Class_getConstantPool(current_class), context->index);
    Class _class = FieldRef_class(field_ref);
    Field field = FieldRef_resolvedField(field_ref);
    // TODO

    if (!Field_isStatic(field)) {
        printf("java.lang.IncompatibleClassChangeError");
    }

    u4 slot_id = Field_getSlotId(field);
    Slots slots = Class_getStaticVars(_class);
    char *descriptor = Field_descriptor(field);
    switch (descriptor[0]) {
        case 'Z':
        case 'B':
        case 'C':
        case 'S':
        case 'I':
            Frame_pushInt(frame, getInt(slot_id, slots));
            break;
        case 'F':
            Frame_pushFloat(frame, getFloat(slot_id, slots));
            break;
        case 'J':
            Frame_pushLong(frame, getLong(slot_id, slots));
            break;
        case 'D':
            Frame_pushDouble(frame, getDouble(slot_id, slots));
            break;
        case 'L':
        case '[':
            Frame_pushRef(frame, getRef(slot_id, slots));
            break;
        default:
            break;
    }
}

void putstatic_exe(union Context *context, Frame frame) {
    Method current_method = Frame_method(frame);

    Class current_class = Method_class(current_method);
    struct FieldRef *field_ref = ConstantPool_fieldRef(Class_getConstantPool(current_class), context->index);
    Field field = FieldRef_resolvedField(field_ref);
    Class _class = Field_class(field);

    if (!Class_initStarted(_class)) {
        Frame_revertNextPC(frame);
        initClass(Frame_thread(frame), _class);
        return;
    }

    // TODO

    if (!Field_isStatic(field)) {
        printf("java.lang.IncompatibleClassChangeError");
    }

    if (Field_isFinal(field)) {
        if (current_class != _class || Method_namecmp(current_method, "<clinit>") == 1) {
            printf("java.lang.IllegalAccessError");
        }
    }

    u4 slot_id = Field_getSlotId(field);
    Slots slots = Class_getStaticVars(_class);

    switch (Field_descriptor(field)[0]) {
        case 'Z':
        case 'B':
        case 'C':
        case 'S':
        case 'I':
            setInt(slot_id, Frame_popInt(frame), slots);
            break;
        case 'F':
            setFloat(slot_id, Frame_popFloat(frame), slots);
            break;
        case 'J':
            setLong(slot_id, Frame_popLong(frame), slots);
            break;
        case 'D':
            setDouble(slot_id, Frame_popDouble(frame), slots);
            break;
        case 'L':
        case '[':
            setRef(slot_id, Frame_popRef(frame), slots);
            break;
        default:
            break;
    }
}

void getfield_exe(union Context *context, Frame frame) {
    Method current_method = Frame_method(frame);
    Class current_class = Method_class(current_method);
    FieldRef field_ref = ConstantPool_fieldRef(Class_getConstantPool(current_class), context->index);
    Field field = FieldRef_resolvedField(field_ref);
    Class _class = Field_class(field);

    // TODO

    if (Field_isStatic(field)) {
        printf("java.lang.IncompatibleClassChangeError");
    }

    if (Field_isFinal(field)) {
        if (current_class != _class || Method_namecmp(current_method, "<init>") == 1) {
            printf("java.lang.IllegalAccessError");
        }
    }

    u4 slot_id = Field_getSlotId(field);
    struct Object *ref = Frame_popRef(frame);
    if (ref == NULL) {
        printf("java.lang.NullPointerException");
    }

    Slots slots = Object_getFields(ref);

    switch (Field_descriptor(field)[0]) {
        case 'Z':
        case 'B':
        case 'C':
        case 'S':
        case 'I':
            Frame_pushInt(frame, getInt(slot_id, slots));
            break;
        case 'F':
            Frame_pushFloat(frame, getFloat(slot_id, slots));
            break;
        case 'J':
            Frame_pushLong(frame, getLong(slot_id, slots));
            break;
        case 'D':
            Frame_pushDouble(frame, getDouble(slot_id, slots));
            break;
        case 'L':
        case '[':
            Frame_pushRef(frame, getRef(slot_id, slots));
            break;
        default:
            break;
    }
}

void putfield_exe(union Context *context, Frame frame) {
    Method current_method = Frame_method(frame);
    Class current_class = Method_class(current_method);
    FieldRef field_ref = ConstantPool_fieldRef(Class_getConstantPool(current_class), context->index);
    Field field = FieldRef_resolvedField(field_ref);
    Class _class = Field_class(field);
    // TODO

    if (Field_isStatic(field)) {
        printf("java.lang.IncompatibleClassChangeError");
    }

    if (Field_isFinal(field)) {
        if (current_class != _class || Method_namecmp(current_method, "<init>") == 1) {
            printf("java.lang.IllegalAccessError");
        }
    }

    u4 slot_id = Field_getSlotId(field);

    switch (Field_descriptor(field)[0]) {
        case 'Z':
        case 'B':
        case 'C':
        case 'S':
        case 'I': {
            int value = Frame_popInt(frame);
            Object ref = Frame_popRef(frame);
            if (ref == NULL) {
                printf("java.lang.NullPointerException");
            }

            Object_setInt(ref, slot_id, value);
            break;
        }
        case 'F': {
            float value = Frame_popFloat(frame);
            Object ref = Frame_popRef(frame);
            if (ref == NULL) {
                printf("java.lang.NullPointerException");
            }

            Object_setFloat(ref, slot_id, value);
            break;
        }
        case 'J': {
            long value = Frame_popLong(frame);
            Object ref = Frame_popRef(frame);
            if (ref == NULL) {
                printf("java.lang.NullPointerException");
            }

            Object_setLong(ref, slot_id, value);
            break;
        }
        case 'D': {
            double d = Frame_popDouble(frame);
            Object ref = Frame_popRef(frame);
            if (ref == NULL) {
                printf("java.lang.NullPointerException\n");
            }

            Object_setDouble(ref, slot_id, d);
            break;
        }
        case 'L':
        case '[': {
            Object value = Frame_popRef(frame);
            Object ref = Frame_popRef(frame);
            if (ref == NULL) {
                printf("java.lang.NullPointerException");
            }

            Object_setRef(ref, slot_id, value);
            break;
        }
        default:
            break;
    }
}


void invokevirtual_exe(union Context *context, Frame frame) {
    Class current_class = Method_class((Method)Frame_method(frame));
    MethodRef method_ref = ConstantPool_methodRef(Class_getConstantPool(current_class), context->index);

    Method resolved_method = MethodRef_resolvedMethod(method_ref);

    if (Method_isStatic(resolved_method)) {
        printf("java.lang.IncompatibleClassChangeError");
    }

    OperandStack stack = Frame_stack(frame);
    Object ref = getRefFromStackTop(stack, Method_argCount(resolved_method) - 1);
    if (ref == NULL) {
        if (strcmp(MethodRef_name(method_ref), "println") == 0) {
            // TODO
            _println(stack, MethodRef_descriptor(method_ref));
        } else {
            printf("java.lang.NullPointerException");
        }
    }

    if (Method_isProtected(resolved_method) &&
        Class_isSuperClassOf(Method_class(resolved_method), current_class) &&
        strcmp(Class_packageName(Method_class(resolved_method)), Class_packageName(current_class)) != 0 &&
            Object_getClass(ref) != current_class &&
        !Class_isSuperClassOf(Object_getClass(ref), current_class)
            ) {
        printf("java.lang.IllegalAccessError");
    }

    Method invoke_method = Class_lookupMethodInClass(Object_getClass(ref), MethodRef_name(method_ref), MethodRef_descriptor(method_ref));

    if (invoke_method == NULL || Method_isAbstract(invoke_method)) {
        printf("java.lang.AbstractMethodError");
    }

    invokeMethod(frame, invoke_method);

}

void invokespecial_exe(union Context *context, Frame frame) {
    Class current_class = Method_class((Method)Frame_method(frame));
    MethodRef method_ref = ConstantPool_methodRef(Class_getConstantPool(current_class), context->index);
    Class resolved_class = MethodRef_resolvedClass(method_ref);

    Method resolved_method = MethodRef_resolvedMethod(method_ref);

    if (Method_namecmp(resolved_method, "<init>") == 0 && Method_class(resolved_method) != resolved_class) {
        printf("java.lang.NoSuchMethodError");
    }

    if (Method_isStatic(resolved_method)) {
        printf("java.lang.IncompatibleClassChangeError");
    }

    // get ref from top
    Object ref = getRefFromStackTop(Frame_stack(frame), Method_argCount(resolved_method));
    if (ref == NULL) {
        printf("java.lang.NullPointerException");
    }

    if (Method_isProtected(resolved_method) &&
        Class_isSuperClassOf(Method_class(resolved_method), current_class) &&
        strcmp(Class_packageName(Method_class(resolved_method)), Class_packageName(current_class)) != 0 &&
        Object_getClass(ref) != current_class &&
        !Class_isSuperClassOf(Object_getClass(ref), current_class)
            ) {
        printf("java.lang.IllegalAccessError");
    }

    Method invoke_method = resolved_method;
    if (Class_isSuper(current_class) &&
        Class_isSuperClassOf(resolved_class, current_class) &&
        Method_namecmp(resolved_method, "<init>") != 0) {
        invoke_method = MethodRef_lookupMethodInClass(method_ref, Class_getSuperClass(current_class));
    }

    if (invoke_method == NULL || Method_isAbstract(invoke_method)) {
        printf("java.lang.AbstractMethodError");
    }

    invokeMethod(frame, invoke_method);
}




void _println(struct OperandStack *stack, char *descriptor) {
    if (strcmp(descriptor, "(Z)V") == 0) {
        printf("%v\n", popInt(stack) != 0);
    } else if (strcmp(descriptor, "(C)V") == 0) {
        printf("%c\n", popInt(stack));
    } else if (strcmp(descriptor, "(B)V") == 0) {
        printf("%v\n", popInt(stack));
    } else if (strcmp(descriptor, "(S)V") == 0) {
        printf("%v\n", popInt(stack));
    } else if (strcmp(descriptor, "(I)V") == 0) {
        printf("%v\n", popInt(stack));
    } else if (strcmp(descriptor, "(F)V") == 0) {
        printf("%v\n", popFloat(stack));
    } else if (strcmp(descriptor, "(J)V") == 0) {
        printf("%v\n", popLong(stack));
    } else if (strcmp(descriptor, "(D)V") == 0) {
        printf("%v\n", popDouble(stack));
    } else {
        // TODO
        printf("println: %s\n", descriptor);
    }
    popRef(stack);
}

void invokestatic_exe(union Context *context, Frame frame) {
    Method method = Frame_method(frame);
    ConstantPool constant_pool = Class_getConstantPool(Method_class(method));
    MethodRef method_ref = ConstantPool_methodRef(constant_pool, context->index);
    Method resolved_method = MethodRef_resolvedMethod(method_ref);

    if (!Method_isStatic(resolved_method)) {
        printf("java.lang.IncompatibleClassChangeError");
    }

    Class _class = Method_class(resolved_method);
    if (!Class_initStarted(_class)) {
        Frame_revertNextPC(frame);
        initClass(Frame_thread(frame), _class);
        return;
    }

    invokeMethod(frame, resolved_method);
}

void invokeinterface_fetchOp(union Context *context, struct Bytecode *data) {
    context->index = readBytecodeU2(data);
    readBytecodeU1(data);       // count
    readBytecodeU1(data);       // must be 0
}

void invokeinterface_exe(union Context *context, Frame frame) {
    Class current_class = Method_class((Method)Frame_method(frame));
    ConstantPool constant_pool = Class_getConstantPool(current_class);
    InterfaceMethodRef interface_method_ref = ConstantPool_interfaceMethodRef(constant_pool, context->index);
    Method resolved_method = InterfaceMethodRef_resolvedInterfaceMethod(interface_method_ref);
    if (Method_isStatic(resolved_method) || Method_isPrivate(resolved_method)) {
        printf("java.lang.IncompatibleClassChangeError");
    }

    Object ref = getRefFromStackTop(Frame_stack(frame), Method_argCount(resolved_method) - 1);
    if (ref == NULL) {
        printf("java.lang.NullPointerException");
    }

    Class method_class = InterfaceMethodRef_resolvedClass(interface_method_ref);
    if (!Class_isImplements(Object_getClass(ref), method_class)) {
        printf("java.lang.IncompatibleClassChangeError");
    }

    Method invoke_method = InterfaceMethodRef_lookupMethodInClass(interface_method_ref, Object_getClass(ref));
    if (invoke_method == NULL || Method_isAbstract(invoke_method)) {
        printf("java.lang.AbstractMethodError");
    }

    if (!Method_isPublic(invoke_method)) {
        printf("java.lang.IllegalAccessError");
    }

    invokeMethod(frame, invoke_method);
}

void invokedynamic_exe(union Context *context, Frame frame) {

}

void invokenative(union Context *context, Frame frame) {
    Method method = Frame_method(frame);
    char *class_name = Class_name(Method_class(method));
    char *name = Method_name(method);
    char *descriptor = Method_descriptor(method);
    NativeMethod nativeMethod = NativeMethod_find(class_name, name, descriptor);

    if (nativeMethod == NULL) {
        // TODO
        printf("java.lang.UnsatisfieLinkError: %s.%s%s\n", class_name, name, descriptor);
    }
    nativeMethod(frame);
    
}

void new_exe(union Context *context, Frame frame) {
    Class current_class = Method_class((Method)Frame_method(frame));
    ClassRef class_ref = ConstantPool_classRef(Class_getConstantPool(current_class), context->index);
    // TODO free?
    Class _class = ClassRef_resolvedClass(class_ref);

    if (!Class_initStarted(_class)) {
        Frame_revertNextPC(frame);
        initClass(Frame_thread(frame), _class);
        return;
    }

    if (Class_isInterface(_class) || Class_isAbstract(_class)) {
        printf("java.lang.InstantiationError");
    }

    struct Object *ref = newObject(_class);

    Frame_pushRef(frame, ref);
}

void newarray_fetchOp(union Context *context, struct Bytecode *data) {
    context->atype = readBytecodeU2(data);
}

void newarray_exe(union Context *context, Frame frame) {
    int count = Frame_popInt(frame);
    if (count < 0) {
        printf("java.lang.NegativeArraySizeException\n");
    }

    Class current_class = Method_class((Method)Frame_method(frame));
    ClassLoader loader = Class_loader(current_class);
    Class array_class = getPrimitiveArrayClass(loader, context->atype);
    Object array = newArray(array_class, count);
    Frame_pushRef(frame, array);
}

Class getPrimitiveArrayClass(ClassLoader loader, unsigned int atype) {

    switch (atype) {
        case AT_BOOLEAN:
            return ClassLoader_loadClass(loader, "[Z");
        case AT_BYTE:
            return ClassLoader_loadClass(loader, "[B");
        case AT_CHAR:
            return ClassLoader_loadClass(loader, "[C");
        case AT_SHORT:
            return ClassLoader_loadClass(loader, "[S");
        case AT_INT:
            return ClassLoader_loadClass(loader, "[I");
        case AT_LONG:
            return ClassLoader_loadClass(loader, "[J");
        case AT_FLOAT:
            return ClassLoader_loadClass(loader, "[F");
        case AT_DOUBLE:
            return ClassLoader_loadClass(loader, "[D");
        default:    printf("Invalid atype!\n");
    }
}

void anewarray_exe(union Context *context, Frame frame) {
    Class current_class = Method_class((Method)Frame_method(frame));
    ClassRef class_ref = ConstantPool_classRef(Class_getConstantPool(current_class), context->index);
    ClassRef_resolveClassRef(class_ref);
    int count = Frame_popInt(frame);
    if (count < 0) {
        printf("java.lang.NegativeArraySizeException\n");
    }

    Class array_class = arrayClass(ClassRef_class(class_ref));
    Object array = newArray(array_class, count);
    pushRef(array, Frame_stack(frame));
}


static char *getArrayClassName(char *class_name) {
    if (class_name[0] == '[') {
        return strcat("[", class_name);
    }

    if (strcmp("void", class_name) == 0) {
        return "[V";
    } else if (strcmp("boolean", class_name) == 0) {
        return "[Z";
    } else if (strcmp("byte", class_name) == 0) {
        return "[B";
    } else if (strcmp("char", class_name) == 0) {
        return "[C";
    } else if (strcmp("short", class_name) == 0) {
        return "[S";
    } else if (strcmp("int", class_name) == 0) {
        return "[I";
    } else if (strcmp("long", class_name) == 0) {
        return "[J";
    } else if (strcmp("float", class_name) == 0) {
        return "[F";
    } else if (strcmp("double", class_name) == 0) {
        return "[D";
    }

    return strcat(strcat("[L", class_name), ";");
}

Class arrayClass(Class _this) {
    char *array_class_name = getArrayClassName(Class_name(_this));
    return ClassLoader_loadClass(Class_loader(_this), array_class_name);
}

void arraylength_exe(union Context *context, Frame frame) {
    // TODO
}

void athrow_exe(union Context *context, Frame frame) {
    Object ex = Frame_popRef(frame);
    if (ex == NULL) {
        printf("java.lang.NullPointerException\n");
    }

    Thread thread = Frame_thread(frame);

    if (!findAndGotoExceptionHandler(thread, ex)) {
        handleUncaughtException(thread, ex);
    }
}

static int findAndGotoExceptionHandler(Thread thread, Object ex) {
    while (1) {
    Frame frame = Thread_currentFrame(thread);
    int pc = Frame_getNextPC(frame) - 1;

    Method method = Frame_method(frame);
    int handler_pc = Method_findExceptionHandler(method, Object_getClass(ex), pc);

        if (handler_pc > 0) {
            OperandStack stack = Frame_stack(frame);
            OperandStack_clear(stack);
            // TODO stack clear
            Frame_pushRef(frame, ex);
            Frame_setNextPC(frame, handler_pc);

            return 1;
        }

        Thread_popFrame(thread);
        if (Thread_isStackEmpty(thread)) {
            break;
        }
    }

    return 0;
}

static void handleUncaughtException(Thread thread, Object ex) {

}

void checkcast_exe(union Context *context, Frame frame) {

}

void instanceof_exe(union Context *context, Frame frame) {
    OperandStack stack = Frame_stack(frame);
    struct Object *ref = popRef(stack);
    if (ref == NULL) {
        pushInt(0, stack);
        return;
    }

    Class current_class = Method_class((Method)Frame_method(frame));
    ClassRef class_ref = ConstantPool_classRef(Class_getConstantPool(current_class), context->index);

    ClassRef_resolveClassRef(class_ref);

    if (Object_isInterfaceOf(ref, ClassRef_class(class_ref))) {
        pushInt(1, stack);
    } else {
        pushInt(0, stack);
    }
}

void monitorenter_exe(union Context *context, Frame frame) {

}

void monitorexit_exe(union Context *context, Frame frame) {

}

void wide_exe(union Context *context, Frame frame) {

}

void multianewarray_exe(union Context *context, Frame frame) {

}

void ifnull_exe(union Context *context, Frame frame) {
    struct Object *ref = Frame_popRef(frame);
    if (ref == NULL) {
        branch(frame, context->offset);
    }
}

void ifnonnull_exe(union Context *context, Frame frame) {
    struct Object *ref = Frame_popRef(frame);
    if (ref != NULL) {
        branch(frame, context->offset);
    }
}

void goto_w_exe(union Context *context, Frame frame) {

}

void jsr_w_exe(union Context *context, Frame frame) {

}

struct Instruction makeInstruction(FetchOperands fetchOperands, Execute execute) {
    struct Instruction inst;
    inst.fetchOperands = fetchOperands;
    inst.execute = execute;
    return inst;
}

struct Instruction newInstruction(u1 opcode) {
    if (NOP == opcode) {
        return makeInstruction(nop_fetchOp, nop_exe);
    } else if (ACONST_NULL == opcode) {
        return makeInstruction(nop_fetchOp, aconst_null_exe);
    } else if (ICONST_M1 == opcode) {
        return makeInstruction(nop_fetchOp, iconst_m1_exe);
    } else if (ICONST_0 == opcode) {
        return makeInstruction(nop_fetchOp, iconst_0_exe);
    } else if (ICONST_1 == opcode) {
        return makeInstruction(nop_fetchOp, iconst_1_exe);
    } else if (ICONST_2 == opcode) {
        return makeInstruction(nop_fetchOp, iconst_2_exe);
    } else if (ICONST_3 == opcode) {
        return makeInstruction(nop_fetchOp, iconst_3_exe);
    } else if (ICONST_4 == opcode) {
        return makeInstruction(nop_fetchOp, iconst_4_exe);
    } else if (ICONST_5 == opcode) {
        return makeInstruction(nop_fetchOp, iconst_5_exe);
    } else if (LCONST_0 == opcode) {
        return makeInstruction(nop_fetchOp, lconst_0_exe);
    } else if (LCONST_1 == opcode) {
        return makeInstruction(nop_fetchOp, lconst_1_exe);
    } else if (FCONST_0 == opcode) {
        return makeInstruction(nop_fetchOp, fconst_0_exe);
    } else if (FCONST_1 == opcode) {
        return makeInstruction(nop_fetchOp, fconst_1_exe);
    } else if (FCONST_2 == opcode) {
        return makeInstruction(nop_fetchOp, fconst_2_exe);
    } else if (DCONST_0 == opcode) {
        return makeInstruction(nop_fetchOp, dconst_0_exe);
    } else if (DCONST_1 == opcode) {
        return makeInstruction(nop_fetchOp, dconst_1_exe);
    } else if (BIPUSH == opcode) {
        return makeInstruction(bipush_fetchOp, bipush_exe);
    } else if (SIPUSH == opcode) {
        return makeInstruction(sipush_fetchOp, sipush_exe);
    } else if (LDC == opcode) {
        return makeInstruction(nop_fetchOp, ldc_exe);
    } else if (LDC_W == opcode) {
        return makeInstruction(nop_fetchOp, ldc_w_exe);
    } else if (LDC2_W == opcode) {
        return makeInstruction(nop_fetchOp, ldc2_w_exe);
    } else if (ILOAD == opcode) {
        return makeInstruction(index8_fetchOp, iload_exe);
    } else if (LLOAD == opcode) {
        return makeInstruction(nop_fetchOp, lload_exe);
    } else if (FLOAD == opcode) {
        return makeInstruction(nop_fetchOp, fload_exe);
    } else if (DLOAD == opcode) {
        return makeInstruction(nop_fetchOp, dload_exe);
    } else if (ALOAD == opcode) {
        return makeInstruction(nop_fetchOp, aload_exe);
    } else if (ILOAD_0 == opcode) {
        return makeInstruction(nop_fetchOp, iload_0_exe);
    } else if (ILOAD_1 == opcode) {
        return makeInstruction(nop_fetchOp, iload_1_exe);
    } else if (ILOAD_2 == opcode) {
        return makeInstruction(nop_fetchOp, iload_2_exe);
    } else if (ILOAD_3 == opcode) {
        return makeInstruction(nop_fetchOp, iload_3_exe);
    } else if (LLOAD_0 == opcode) {
        return makeInstruction(nop_fetchOp, lload_0_exe);
    } else if (LLOAD_1 == opcode) {
        return makeInstruction(nop_fetchOp, lload_1_exe);
    } else if (LLOAD_2 == opcode) {
        return makeInstruction(nop_fetchOp, lload_2_exe);
    } else if (LLOAD_3 == opcode) {
        return makeInstruction(nop_fetchOp, lload_3_exe);
    } else if (FLOAD_0 == opcode) {
        return makeInstruction(nop_fetchOp, fload_0_exe);
    } else if (FLOAD_1 == opcode) {
        return makeInstruction(nop_fetchOp, fload_1_exe);
    } else if (FLOAD_2 == opcode) {
        return makeInstruction(nop_fetchOp, fload_2_exe);
    } else if (FLOAD_3 == opcode) {
        return makeInstruction(nop_fetchOp, fload_3_exe);
    } else if (DLOAD_0 == opcode) {
        return makeInstruction(nop_fetchOp, dload_0_exe);
    } else if (DLOAD_1 == opcode) {
        return makeInstruction(nop_fetchOp, dload_1_exe);
    } else if (DLOAD_2 == opcode) {
        return makeInstruction(nop_fetchOp, dload_2_exe);
    } else if (DLOAD_3 == opcode) {
        return makeInstruction(nop_fetchOp, dload_3_exe);
    } else if (ALOAD_0 == opcode) {
        return makeInstruction(nop_fetchOp, aload_0_exe);
    } else if (ALOAD_1 == opcode) {
        return makeInstruction(nop_fetchOp, aload_1_exe);
    } else if (ALOAD_2 == opcode) {
        return makeInstruction(nop_fetchOp, aload_2_exe);
    } else if (ALOAD_3 == opcode) {
        return makeInstruction(nop_fetchOp, aload_3_exe);
    } else if (IALOAD == opcode) {
        return makeInstruction(nop_fetchOp, iaload_exe);
    } else if (LALOAD == opcode) {
        return makeInstruction(nop_fetchOp, laload_exe);
    } else if (FALOAD == opcode) {
        return makeInstruction(nop_fetchOp, faload_exe);
    } else if (DALOAD == opcode) {
        return makeInstruction(nop_fetchOp, daload_exe);
    } else if (AALOAD == opcode) {
        return makeInstruction(nop_fetchOp, aaload_exe);
    } else if (BALOAD == opcode) {
        return makeInstruction(nop_fetchOp, baload_exe);
    } else if (CALOAD == opcode) {
        return makeInstruction(nop_fetchOp, caload_exe);
    } else if (SALOAD == opcode) {
        return makeInstruction(nop_fetchOp, saload_exe);
    } else if (ISTORE == opcode) {
        return makeInstruction(index8_fetchOp, istore_exe);
    } else if (LSTORE == opcode) {
        return makeInstruction(nop_fetchOp, lstore_exe);
    } else if (FSTORE == opcode) {
        return makeInstruction(nop_fetchOp, fstore_exe);
    } else if (DSTORE == opcode) {
        return makeInstruction(nop_fetchOp, dstore_exe);
    } else if (ASTORE == opcode) {
        return makeInstruction(nop_fetchOp, astore_exe);
    } else if (ISTORE_0 == opcode) {
        return makeInstruction(nop_fetchOp, istore_0_exe);
    } else if (ISTORE_1 == opcode) {
        return makeInstruction(nop_fetchOp, istore_1_exe);
    } else if (ISTORE_2 == opcode) {
        return makeInstruction(nop_fetchOp, istore_2_exe);
    } else if (ISTORE_3 == opcode) {
        return makeInstruction(nop_fetchOp, istore_3_exe);
    } else if (LSTORE_0 == opcode) {
        return makeInstruction(nop_fetchOp, lstore_0_exe);
    } else if (LSTORE_1 == opcode) {
        return makeInstruction(nop_fetchOp, lstore_1_exe);
    } else if (LSTORE_2 == opcode) {
        return makeInstruction(nop_fetchOp, lstore_2_exe);
    } else if (LSTORE_3 == opcode) {
        return makeInstruction(nop_fetchOp, lstore_3_exe);
    } else if (FSTORE_0 == opcode) {
        return makeInstruction(nop_fetchOp, fstore_0_exe);
    } else if (FSTORE_1 == opcode) {
        return makeInstruction(nop_fetchOp, fstore_1_exe);
    } else if (FSTORE_2 == opcode) {
        return makeInstruction(nop_fetchOp, fstore_2_exe);
    } else if (FSTORE_3 == opcode) {
        return makeInstruction(nop_fetchOp, fstore_3_exe);
    } else if (DSTORE_0 == opcode) {
        return makeInstruction(nop_fetchOp, dstore_0_exe);
    } else if (DSTORE_1 == opcode) {
        return makeInstruction(nop_fetchOp, dstore_1_exe);
    } else if (DSTORE_2 == opcode) {
        return makeInstruction(nop_fetchOp, dstore_2_exe);
    } else if (DSTORE_3 == opcode) {
        return makeInstruction(nop_fetchOp, dstore_3_exe);
    } else if (ASTORE_0 == opcode) {
        return makeInstruction(nop_fetchOp, astore_0_exe);
    } else if (ASTORE_1 == opcode) {
        return makeInstruction(nop_fetchOp, astore_1_exe);
    } else if (ASTORE_2 == opcode) {
        return makeInstruction(nop_fetchOp, astore_2_exe);
    } else if (ASTORE_3 == opcode) {
        return makeInstruction(nop_fetchOp, astore_3_exe);
    } else if (IASTORE == opcode) {
        return makeInstruction(nop_fetchOp, iastore_exe);
    } else if (LASTORE == opcode) {
        return makeInstruction(nop_fetchOp, lastore_exe);
    } else if (FASTORE == opcode) {
        return makeInstruction(nop_fetchOp, fastore_exe);
    } else if (DASTORE == opcode) {
        return makeInstruction(nop_fetchOp, dastore_exe);
    } else if (AASTORE == opcode) {
        return makeInstruction(nop_fetchOp, aastore_exe);
    } else if (BASTORE == opcode) {
        return makeInstruction(nop_fetchOp, bastore_exe);
    } else if (CASTORE == opcode) {
        return makeInstruction(nop_fetchOp, castore_exe);
    } else if (SASTORE == opcode) {
        return makeInstruction(nop_fetchOp, sastore_exe);
    } else if (POP == opcode) {
        return makeInstruction(nop_fetchOp, pop_exe);
    } else if (POP2 == opcode) {
        return makeInstruction(nop_fetchOp, pop2_exe);
    } else if (DUP == opcode) {
        return makeInstruction(nop_fetchOp, dup_exe);
    } else if (DUP_X1 == opcode) {
        return makeInstruction(nop_fetchOp, dup_x1_exe);
    } else if (DUP_X2 == opcode) {
        return makeInstruction(nop_fetchOp, dup_x2_exe);
    } else if (DUP2 == opcode) {
        return makeInstruction(nop_fetchOp, dup2_exe);
    } else if (DUP2_X1 == opcode) {
        return makeInstruction(nop_fetchOp, dup2_x1_exe);
    } else if (DUP2_X2 == opcode) {
        return makeInstruction(nop_fetchOp, dup2_x2_exe);
    } else if (SWAP == opcode) {
        return makeInstruction(nop_fetchOp, swap_exe);
    } else if (IADD == opcode) {
        return makeInstruction(nop_fetchOp, iadd_exe);
    } else if (LADD == opcode) {
        return makeInstruction(nop_fetchOp, ladd_exe);
    } else if (FADD == opcode) {
        return makeInstruction(nop_fetchOp, fadd_exe);
    } else if (DADD == opcode) {
        return makeInstruction(nop_fetchOp, dadd_exe);
    } else if (ISUB == opcode) {
        return makeInstruction(nop_fetchOp, isub_exe);
    } else if (LSUB == opcode) {
        return makeInstruction(nop_fetchOp, lsub_exe);
    } else if (FSUB == opcode) {
        return makeInstruction(nop_fetchOp, fsub_exe);
    } else if (DSUB == opcode) {
        return makeInstruction(nop_fetchOp, dsub_exe);
    } else if (IMUL == opcode) {
        return makeInstruction(nop_fetchOp, imul_exe);
    } else if (LMUL == opcode) {
        return makeInstruction(nop_fetchOp, lmul_exe);
    } else if (FMUL == opcode) {
        return makeInstruction(nop_fetchOp, fmul_exe);
    } else if (DMUL == opcode) {
        return makeInstruction(nop_fetchOp, dmul_exe);
    } else if (IDIV == opcode) {
        return makeInstruction(nop_fetchOp, idiv_exe);
    } else if (LDIV == opcode) {
        return makeInstruction(nop_fetchOp, ldiv_exe);
    } else if (FDIV == opcode) {
        return makeInstruction(nop_fetchOp, fdiv_exe);
    } else if (DDIV == opcode) {
        return makeInstruction(nop_fetchOp, ddiv_exe);
    } else if (IREM == opcode) {
        return makeInstruction(nop_fetchOp, irem_exe);
    } else if (LREM == opcode) {
        return makeInstruction(nop_fetchOp, lrem_exe);
    } else if (FREM == opcode) {
        return makeInstruction(nop_fetchOp, frem_exe);
    } else if (DREM == opcode) {
        return makeInstruction(nop_fetchOp, drem_exe);
    } else if (INEG == opcode) {
        return makeInstruction(nop_fetchOp, ineg_exe);
    } else if (LNEG == opcode) {
        return makeInstruction(nop_fetchOp, lneg_exe);
    } else if (FNEG == opcode) {
        return makeInstruction(nop_fetchOp, fneg_exe);
    } else if (DNEG == opcode) {
        return makeInstruction(nop_fetchOp, dneg_exe);
    } else if (ISHL == opcode) {
        return makeInstruction(nop_fetchOp, ishl_exe);
    } else if (LSHL == opcode) {
        return makeInstruction(nop_fetchOp, lshl_exe);
    } else if (ISHR == opcode) {
        return makeInstruction(nop_fetchOp, ishr_exe);
    } else if (LSHR == opcode) {
        return makeInstruction(nop_fetchOp, lshr_exe);
    } else if (IUSHR == opcode) {
        return makeInstruction(nop_fetchOp, iushr_exe);
    } else if (LUSHR == opcode) {
        return makeInstruction(nop_fetchOp, lushr_exe);
    } else if (IAND == opcode) {
        return makeInstruction(nop_fetchOp, iand_exe);
    } else if (LAND == opcode) {
        return makeInstruction(nop_fetchOp, land_exe);
    } else if (IOR == opcode) {
        return makeInstruction(nop_fetchOp, ior_exe);
    } else if (LOR == opcode) {
        return makeInstruction(nop_fetchOp, lor_exe);
    } else if (IXOR == opcode) {
        return makeInstruction(nop_fetchOp, ixor_exe);
    } else if (LXOR == opcode) {
        return makeInstruction(nop_fetchOp, lxor_exe);
    } else if (IINC == opcode) {
        return makeInstruction(nop_fetchOp, iinc_exe);
    } else if (I2L == opcode) {
        return makeInstruction(nop_fetchOp, i2l_exe);
    } else if (I2F == opcode) {
        return makeInstruction(nop_fetchOp, i2f_exe);
    } else if (I2D == opcode) {
        return makeInstruction(nop_fetchOp, i2d_exe);
    } else if (L2I == opcode) {
        return makeInstruction(nop_fetchOp, l2i_exe);
    } else if (L2F == opcode) {
        return makeInstruction(nop_fetchOp, l2f_exe);
    } else if (L2D == opcode) {
        return makeInstruction(nop_fetchOp, l2d_exe);
    } else if (F2I == opcode) {
        return makeInstruction(nop_fetchOp, f2i_exe);
    } else if (F2L == opcode) {
        return makeInstruction(nop_fetchOp, f2l_exe);
    } else if (F2D == opcode) {
        return makeInstruction(nop_fetchOp, f2d_exe);
    } else if (D2I == opcode) {
        return makeInstruction(nop_fetchOp, d2i_exe);
    } else if (D2L == opcode) {
        return makeInstruction(nop_fetchOp, d2l_exe);
    } else if (D2F == opcode) {
        return makeInstruction(nop_fetchOp, d2f_exe);
    } else if (I2B == opcode) {
        return makeInstruction(nop_fetchOp, i2b_exe);
    } else if (I2C == opcode) {
        return makeInstruction(nop_fetchOp, i2c_exe);
    } else if (I2S == opcode) {
        return makeInstruction(nop_fetchOp, i2s_exe);
    } else if (LCMP == opcode) {
        return makeInstruction(nop_fetchOp, lcmp_exe);
    } else if (FCMPL == opcode) {
        return makeInstruction(nop_fetchOp, fcmpl_exe);
    } else if (FCMPG == opcode) {
        return makeInstruction(nop_fetchOp, fcmpg_exe);
    } else if (DCMPL == opcode) {
        return makeInstruction(nop_fetchOp, dcmpl_exe);
    } else if (DCMPG == opcode) {
        return makeInstruction(nop_fetchOp, dcmpg_exe);
    } else if (IFEQ == opcode) {
        return makeInstruction(branch_fetchOp, ifeq_exe);
    } else if (IFNE == opcode) {
        return makeInstruction(branch_fetchOp, ifne_exe);
    } else if (IFLT == opcode) {
        return makeInstruction(branch_fetchOp, iflt_exe);
    } else if (IFGE == opcode) {
        return makeInstruction(branch_fetchOp, ifge_exe);
    } else if (IFGT == opcode) {
        return makeInstruction(branch_fetchOp, ifgt_exe);
    } else if (IFLE == opcode) {
        return makeInstruction(branch_fetchOp, ifle_exe);
    } else if (IF_ICMPEQ == opcode) {
        return makeInstruction(nop_fetchOp, if_icmpeq_exe);
    } else if (IF_ICMPNE == opcode) {
        return makeInstruction(nop_fetchOp, if_icmpne_exe);
    } else if (IF_ICMPLT == opcode) {
        return makeInstruction(nop_fetchOp, if_icmplt_exe);
    } else if (IF_ICMPGE == opcode) {
        return makeInstruction(nop_fetchOp, if_icmpge_exe);
    } else if (IF_ICMPGT == opcode) {
        return makeInstruction(nop_fetchOp, if_icmpgt_exe);
    } else if (IF_ICMPLE == opcode) {
        return makeInstruction(nop_fetchOp, if_icmple_exe);
    } else if (IF_ACMPEQ == opcode) {
        return makeInstruction(nop_fetchOp, if_acmpeq_exe);
    } else if (IF_ACMPNE == opcode) {
        return makeInstruction(nop_fetchOp, if_acmpne_exe);
    } else if (GOTO == opcode) {
        return makeInstruction(nop_fetchOp, goto_exe);
    } else if (JSR == opcode) {
        return makeInstruction(nop_fetchOp, jsr_exe);
    } else if (RET == opcode) {
        return makeInstruction(nop_fetchOp, ret_exe);
    } else if (TABLESWITCH == opcode) {
        return makeInstruction(nop_fetchOp, tableswitch_exe);
    } else if (LOOKUPSWITCH == opcode) {
        return makeInstruction(nop_fetchOp, lookupswitch_exe);
    } else if (IRETURN == opcode) {
        return makeInstruction(nop_fetchOp, ireturn_exe);
    } else if (LRETURN == opcode) {
        return makeInstruction(nop_fetchOp, lreturn_exe);
    } else if (FRETURN == opcode) {
        return makeInstruction(nop_fetchOp, freturn_exe);
    } else if (DRETURN == opcode) {
        return makeInstruction(nop_fetchOp, dreturn_exe);
    } else if (ARETURN == opcode) {
        return makeInstruction(nop_fetchOp, areturn_exe);
    } else if (RETURN == opcode) {
        return makeInstruction(nop_fetchOp, return_exe);
    } else if (GETSTATIC == opcode) {
        return makeInstruction(index16_fetchOp, getstatic_exe);
    } else if (PUTSTATIC == opcode) {
        return makeInstruction(index16_fetchOp, putstatic_exe);
    } else if (GETFIELD == opcode) {
        return makeInstruction(index16_fetchOp, getfield_exe);
    } else if (PUTFIELD == opcode) {
        return makeInstruction(index16_fetchOp, putfield_exe);
    } else if (INVOKEVIRTUAL == opcode) {
        return makeInstruction(index16_fetchOp, invokevirtual_exe);
    } else if (INVOKESPECIAL == opcode) {
        return makeInstruction(index16_fetchOp, invokespecial_exe);
    } else if (INVOKESTATIC == opcode) {
        return makeInstruction(index16_fetchOp, invokestatic_exe);
    } else if (INVOKEINTERFACE == opcode) {
        return makeInstruction(invokeinterface_fetchOp, invokeinterface_exe);
    } else if (INVOKEDYNAMIC == opcode) {
        return makeInstruction(nop_fetchOp, invokedynamic_exe);
    } else if (INVOKENATIVE == opcode) {
        return makeInstruction(nop_fetchOp, invokenative_exe);
    } else if (NEW == opcode) {
        return makeInstruction(index16_fetchOp, new_exe);
    } else if (NEWARRAY == opcode) {
        return makeInstruction(newarray_fetchOp, newarray_exe);
    } else if (ANEWARRAY == opcode) {
        return makeInstruction(index16_fetchOp, anewarray_exe);
    } else if (ARRAYLENGTH == opcode) {
        return makeInstruction(nop_fetchOp, arraylength_exe);
    } else if (ATHROW == opcode) {
        return makeInstruction(nop_fetchOp, athrow_exe);
    } else if (CHECKCAST == opcode) {
        return makeInstruction(nop_fetchOp, checkcast_exe);
    } else if (INSTANCEOF == opcode) {
        return makeInstruction(index16_fetchOp, instanceof_exe);
    } else if (MONITORENTER == opcode) {
        return makeInstruction(nop_fetchOp, monitorenter_exe);
    } else if (MONITOREXIT == opcode) {
        return makeInstruction(nop_fetchOp, monitorexit_exe);
    } else if (WIDE == opcode) {
        return makeInstruction(nop_fetchOp, wide_exe);
    } else if (MULTIANEWARRAY == opcode) {
        return makeInstruction(nop_fetchOp, multianewarray_exe);
    } else if (IFNULL == opcode) {
        return makeInstruction(branch_fetchOp, ifnull_exe);
    } else if (IFNONNULL == opcode) {
        return makeInstruction(branch_fetchOp, ifnonnull_exe);
    } else if (GOTO_W == opcode) {
        return makeInstruction(nop_fetchOp, goto_w_exe);
    } else if (JSR_W == opcode) {
        return makeInstruction(nop_fetchOp, jsr_w_exe);
    } else {
        // TODO
        printf("Unsupported opcode: 0x%x\n", opcode);
    }
}


Object newObject(Class _class) {
    Object object = (Object) malloc(sizeof(struct Object *));
    Object_setClass(object, _class);
    Object_setFields(object, newSlots(Class_getInterfaceSlotCount(_class)));
    // TODO
    return NULL;
}

int Object_isInterfaceOf(Object _this, Class _other) {
    Class s = Object_getClass(_this);
    Class t = _other;

    if (s == t) {
        return 1;
    }

    if (Class_isInterface(s)) {
        if (Class_isInterface(t)) {
            return s == t || Class_isSubInterfaceOf(s, t);
        } else {
            return strcmp(Class_name(t), "java/lang/Object") == 0;
        }
    } else {
        if (Class_isInterface(t)) {
            return Class_isImplements(s, t);
        } else {
            return s == t || Class_isSubClassOf(s, t);
        }
    }
}


void initSuperClass(Thread thread, Class _class) {
    if (!Class_isInterface(_class)) {
        Class super_class = Class_getSuperClass(_class);
        if (super_class != NULL && !Class_isInterface(super_class)) {
            initClass(thread, super_class);
        }
    }
}

void scheduleClinit(Thread thread, Class _class) {
    Method clinit = Class_getClinitMethod(_class);
    if (clinit != NULL) {
        Frame frame = newFrame(thread, Method_maxLocals(clinit), Method_maxStack(clinit), clinit);
        Thread_pushFrame(thread, frame);
    }
}

void initClass(Thread thread, Class _class) {
    Class_init(_class);
    scheduleClinit(thread, _class);
    initSuperClass(thread, _class);
}

static void invokeMethod(Frame invoker_frame, Method method) {
    Thread thread = Frame_thread(invoker_frame);
    Frame new_frame = newFrame(thread, Method_maxLocals(method), Method_maxStack(method), method);
    Thread_pushFrame(thread, new_frame);
    u4 arg_count = Method_argCount(method);
    if (arg_count > 0) {
        for (int i = arg_count - 1; i >= 0; --i) {
            Slot slot = Frame_popSlot(invoker_frame);
            setSlot(i, slot, Frame_localVars(new_frame));
        }
    }
}