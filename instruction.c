//
// Created by sulvto on 18-4-30.
//

#include "rtda.h"
#include "bytecode.h"
#include "instruction.h"
#include <stdlib.h>

void nop_fetchOp(union Context *context, struct BytecodeData *data)
{
    // noting to do
}

void branch_fetchOp(union Context *context, struct BytecodeData *data)
{
    context->offset = readU2(data);
}

void branch(struct Frame *frame, int offset)
{
    int pc = frame->thread->pc;
    frame->nextPC = pc + offset;
}

void index8_fetchOp(union Context *context, struct BytecodeData *data)
{
    context->index = readU1(data);
}

void index16_fetchOp(union Context *context, struct BytecodeData *data)
{
    context.index = readU2(data);
}


void nop_exe(union Context *context, struct Frame *frame)
{

}


void aconst_null_exe(union Context *context,struct Frame *frame)
{
    pushRef(NULL, frame->operand_stack);
}

void iconst_m1_exe(union Context *context, struct Frame *frame)
{
    pushInt(-1, frame->operand_stack);
}

void iconst_0_exe(union Context *context, struct Frame *frame)
{
    pushInt(0, frame->operand_stack);
}

void iconst_1_exe(union Context *context, struct Frame *frame)
{
    pushInt(1, frame->operand_stack);
}

void iconst_2_exe(union Context *context, struct Frame *frame)
{
    pushInt(2, frame->operand_stack);
}

void iconst_3_exe(union Context *context, struct Frame *frame)
{
    pushInt(3, frame->operand_stack);
}

void iconst_4_exe(union Context *context, struct Frame *frame)
{
    pushInt(4, frame->operand_stack);
}

void iconst_5_exe(union Context *context, struct Frame *frame)
{
    pushInt(5, frame->operand_stack);
}

void lconst_0_exe(union Context *context, struct Frame *frame)
{
    pushLong(0, frame->operand_stack);
}

void lconst_1_exe(union Context *context, struct Frame *frame){
    pushLong(1, frame->operand_stack);
}

void fconst_0_exe(union Context *context, struct Frame *frame)
{
    pushFloat(0.0, frame->operand_stack);
}

void fconst_1_exe(union Context *context, struct Frame *frame)
{
    pushFloat(1.0, frame->operand_stack);
}

void fconst_2_exe(union Context *context, struct Frame *frame)
{
    pushFloat(2.0, frame->operand_stack);
}

void dconst_0_exe(union Context *context, struct Frame *frame)
{
    pushDouble(0.0, frame->operand_stack);
}

void dconst_1_exe(union Context *context, struct Frame *frame)
{
    pushDouble(1.0, frame->operand_stack);
}

void bipush_fetchOp(union Context *context, struct BytecodeData *bytecode_data)
{
    // TODO byte int
    context->bi = readU1(bytecode_data);
}

void bipush_exe(union Context *context, struct Frame *frame)
{
    u1 bi = context->bi;
    pushInt(bi, frame->operand_stack);

}

void sipush_fetchOp(union Context *context, struct BytecodeData *bytecode_data)
{
    // TODO short int
    context->si = readU2(bytecode_data);
}

void sipush_exe(union Context *context, struct Frame *frame)
{
    short si = context->si;
    pushInt(si, frame->operand_stack);
}

void ldc_exe(union Context *context, struct Frame *frame){

}

void ldc_w_exe(union Context *context, struct Frame *frame){

}

void ldc2_w_exe(union Context *context, struct Frame *frame){

}

void iload(struct Frame *frame, const unsigned int index)
{
    int i = getInt(index, frame->localVars);
    pushInt(i, frame->operand_stack);
}

void lload(struct Frame *frame, const unsigned int index)
{
    long l = getLong(index, frame->localVars);
    pushLong(l, frame->operand_stack);
}

void fload(struct Frame *frame, const unsigned int index)
{
    float f = getFloat(index, frame->localVars);
    pushFloat(f, frame->operand_stack);
}

void dload(struct Frame *frame, const unsigned int index)
{
    double d = getDouble(index, frame->localVars);
    pushDouble(d, frame->operand_stack);
}

void iload_exe(union Context *context, struct Frame *frame)
{
    iload(frame, context->index);
}

void lload_exe(union Context *context, struct Frame *frame)
{
    lload(frame, context->index);
}

void fload_exe(union Context *context, struct Frame *frame)
{
    fload(frame, context->index);
}

void dload_exe(union Context *context, struct Frame *frame)
{
    dload(frame, context->index);
}

void aload_exe(union Context *context, struct Frame *frame){

}

void iload_0_exe(union Context *context, struct Frame *frame)
{
    iload(frame, 0);
}

void iload_1_exe(union Context *context, struct Frame *frame)
{
    iload(frame, 1);
}

void iload_2_exe(union Context *context, struct Frame *frame)
{
    iload(frame, 2);
}

void iload_3_exe(union Context *context, struct Frame *frame)
{
    iload(frame, 3);
}

void lload_0_exe(union Context *context, struct Frame *frame)
{
    lload(frame, 0);
}

void lload_1_exe(union Context *context, struct Frame *frame)
{
    lload(frame, 1);
}

void lload_2_exe(union Context *context, struct Frame *frame)
{
    lload(frame, 2);
}

void lload_3_exe(union Context *context, struct Frame *frame)
{
    lload(frame, 3);
}

void fload_0_exe(union Context *context, struct Frame *frame)
{
    fload(frame, 0);
}

void fload_1_exe(union Context *context, struct Frame *frame)
{
    fload(frame, 1);
}

void fload_2_exe(union Context *context, struct Frame *frame)
{
    fload(frame, 2);
}

void fload_3_exe(union Context *context, struct Frame *frame)
{
    fload(frame, 3);
}

void dload_0_exe(union Context *context, struct Frame *frame)
{
    dload(frame, 0);
}

void dload_1_exe(union Context *context, struct Frame *frame)
{
    dload(frame, 1);
}

void dload_2_exe(union Context *context, struct Frame *frame)
{
    dload(frame, 2);
}

void dload_3_exe(union Context *context, struct Frame *frame)
{
    dload(frame, 3);
}

void aload_0_exe(union Context *context, struct Frame *frame)
{

}

void aload_1_exe(union Context *context, struct Frame *frame)
{

}

void aload_2_exe(union Context *context, struct Frame *frame)
{

}

void aload_3_exe(union Context *context, struct Frame *frame)
{

}

void iaload_exe(union Context *context, struct Frame *frame)
{

}

void laload_exe(union Context *context, struct Frame *frame)
{

}

void faload_exe(union Context *context, struct Frame *frame)
{

}

void daload_exe(union Context *context, struct Frame *frame)
{

}

void aaload_exe(union Context *context, struct Frame *frame)
{

}

void baload_exe(union Context *context, struct Frame *frame)
{

}

void caload_exe(union Context *context, struct Frame *frame)
{

}

void saload_exe(union Context *context, struct Frame *frame)
{

}

void istore(struct Frame *frame, const unsigned int index)
{
    int i = popInt(frame->operand_stack);
    setInt(index, i, frame->localVars);
}

void lstore(struct Frame *frame, const unsigned int index)
{
    long l = popLong(frame->operand_stack);
    setLong(index, l, frame->localVars);
}

void fstore(struct Frame *frame, const unsigned int index)
{
    float f = popFloat(frame->operand_stack);
    setFloat(index, f, frame->localVars);
}

void dstore(struct Frame *frame, const unsigned int index)
{
    double d = popDouble(frame->operand_stack);
    setDouble(index, d, frame->localVars);
}


void istore_exe(union Context *context, struct Frame *frame)
{
    istore(frame, context->index);
}

void lstore_exe(union Context *context, struct Frame *frame)
{
    lstore(frame, context->index);
}

void fstore_exe(union Context *context, struct Frame *frame)
{
    fstore(frame, context->index);
}

void dstore_exe(union Context *context, struct Frame *frame)
{
    dstore(frame, context->index);
}

void astore_exe(union Context *context, struct Frame *frame)
{

}

void istore_0_exe(union Context *context, struct Frame *frame)
{
    istore(frame, 0);
}

void istore_1_exe(union Context *context, struct Frame *frame)
{
    istore(frame, 1);
}

void istore_2_exe(union Context *context, struct Frame *frame)
{
    istore(frame, 2);
}

void istore_3_exe(union Context *context, struct Frame *frame)
{
    istore(frame, 3);
}

void lstore_0_exe(union Context *context, struct Frame *frame)
{
    lstore(frame, 0);
}

void lstore_1_exe(union Context *context, struct Frame *frame)
{
    lstore(frame, 1);
}

void lstore_2_exe(union Context *context, struct Frame *frame)
{
    lstore(frame, 2);
}

void lstore_3_exe(union Context *context, struct Frame *frame)
{
    lstore(frame, 3);
}

void fstore_0_exe(union Context *context, struct Frame *frame)
{
    fstore(frame, 0);
}

void fstore_1_exe(union Context *context, struct Frame *frame)
{
    fstore(frame, 1);
}

void fstore_2_exe(union Context *context, struct Frame *frame)
{
    fstore(frame, 2);
}

void fstore_3_exe(union Context *context, struct Frame *frame)
{
    fstore(frame, 3);
}

void dstore_0_exe(union Context *context, struct Frame *frame)
{
    dstore(frame, 0);
}

void dstore_1_exe(union Context *context, struct Frame *frame)
{
    dstore(frame, 1);
}

void dstore_2_exe(union Context *context, struct Frame *frame)
{
    dstore(frame, 2);
}

void dstore_3_exe(union Context *context, struct Frame *frame)
{
    dstore(frame, 3);
}

void astore_0_exe(union Context *context, struct Frame *frame) {

}

void astore_1_exe(union Context *context, struct Frame *frame) {

}

void astore_2_exe(union Context *context, struct Frame *frame) {

}

void astore_3_exe(union Context *context, struct Frame *frame) {

}

void iastore_exe(union Context *context, struct Frame *frame) {

}

void lastore_exe(union Context *context, struct Frame *frame) {

}

void fastore_exe(union Context *context, struct Frame *frame) {

}

void dastore_exe(union Context *context, struct Frame *frame) {

}

void aastore_exe(union Context *context, struct Frame *frame) {

}

void bastore_exe(union Context *context, struct Frame *frame) {

}

void castore_exe(union Context *context, struct Frame *frame) {

}

void sastore_exe(union Context *context, struct Frame *frame) {

}

void pop_exe(union Context *context, struct Frame *frame)
{
    popSlot(frame->operand_stack);
}

void pop2_exe(union Context *context, struct Frame *frame)
{
    popSlot(frame->operand_stack);
    popSlot(frame->operand_stack);
}

void dup_exe(union Context *context, struct Frame *frame)
{
    struct Slot slot = popSlot(frame->operand_stack);
    pushSlot(slot);
    pushSlot(slot);
}

void dup_x1_exe(union Context *context, struct Frame *frame) {

}

void dup_x2_exe(union Context *context, struct Frame *frame) {

}

void dup2_exe(union Context *context, struct Frame *frame) {

}

void dup2_x1_exe(union Context *context, struct Frame *frame) {

}

void dup2_x2_exe(union Context *context, struct Frame *frame) {

}

void swap_exe(union Context *context, struct Frame *frame)
{
    struct Slot slot1 = popSlot(frame->operand_stack);
    struct Slot slot2 = popSlot(frame->operand_stack);
    pushSlot(slot1, frame->operand_stack);
    pushSlot(slot2, frame->operand_stack);
}

void iadd_exe(union Context *context, struct Frame *frame)
{
    int a = popInt(frame->operand_stack);
    int b = popInt(frame->operand_stack);
    pushInt(a + b, frame->operand_stack);
}

void ladd_exe(union Context *context, struct Frame *frame)
{
    long a = popLong(frame->operand_stack);
    long b = popLong(frame->operand_stack);
    pushLong(a + b, frame->operand_stack);
}

void fadd_exe(union Context *context, struct Frame *frame)
{
    float a = popFloat(frame->operand_stack);
    float b = popFloat(frame->operand_stack);
    pushFloat(a + b, frame->operand_stack);
}

void dadd_exe(union Context *context, struct Frame *frame)
{
    double a = popDouble(frame->operand_stack);
    double b = popDouble(frame->operand_stack);
    pushDouble(a + b, frame->operand_stack);
}

void isub_exe(union Context *context, struct Frame *frame)
{
    int a = popInt(frame->operand_stack);
    int b = popInt(frame->operand_stack);
    pushInt(a - b, frame->operand_stack);
}

void lsub_exe(union Context *context, struct Frame *frame)
{
    long a = popLong(frame->operand_stack);
    long b = popLong(frame->operand_stack);
    pushLong(a - b, frame->operand_stack);
}

void fsub_exe(union Context *context, struct Frame *frame)
{
    float a = popFloat(frame->operand_stack);
    float b = popFloat(frame->operand_stack);
    pushFloat(a - b, frame->operand_stack);
}

void dsub_exe(union Context *context, struct Frame *frame)
{
    double a = popDouble(frame->operand_stack);
    double b = popDouble(frame->operand_stack);
    pushDouble(a - b, frame->operand_stack);
}

void imul_exe(union Context *context, struct Frame *frame)
{
    int a = popInt(frame->operand_stack);
    int b = popInt(frame->operand_stack);
    pushInt(a * b, frame->operand_stack);
}

void lmul_exe(union Context *context, struct Frame *frame)
{
    long a = popLong(frame->operand_stack);
    long b = popLong(frame->operand_stack);
    pushLong(a * b, frame->operand_stack);
}

void fmul_exe(union Context *context, struct Frame *frame)
{
    float a = popFloat(frame->operand_stack);
    float b = popFloat(frame->operand_stack);
    pushFloat(a * b, frame->operand_stack);
}

void dmul_exe(union Context *context, struct Frame *frame)
{
    double a = popDouble(frame->operand_stack);
    double b = popDouble(frame->operand_stack);
    pushDouble(a * b, frame->operand_stack);
}

void idiv_exe(union Context *context, struct Frame *frame)
{
    int a = popInt(frame->operand_stack);
    int b = popInt(frame->operand_stack);
    if (a == 0) {
        // TODO
    }

    div_t result = div(b, a);

    pushInt(result.quot, frame->operand_stack);
}

void ldiv_exe(union Context *context, struct Frame *frame)
{
    long a = popLong(frame->operand_stack);
    long b = popLong(frame->operand_stack);
    if (a == 0) {
        // TODO
    }

    ldiv_t result = ldiv(b, a);

    pushLong(result.quot, frame->operand_stack);
}

void fdiv_exe(union Context *context, struct Frame *frame)
{
    float a = popFloat(frame->operand_stack);
    float b = popFloat(frame->operand_stack);
    if (a == 0) {
        // TODO
    }
    pushFloat(b / a, frame->operand_stack);
}

void ddiv_exe(union Context *context, struct Frame *frame)
{
    double a = popDouble(frame->operand_stack);
    double b = popDouble(frame->operand_stack);
    if (a == 0) {
        // TODO
    }
    pushDouble(b / a, frame->operand_stack);
}

void irem_exe(union Context *context, struct Frame *frame)
{
    int a = popInt(frame->operand_stack);
    int b = popInt(frame->operand_stack);
    if (a == 0) {
        // TODO
    }

    div_t result = div(b, a);

    pushInt(result.rem, frame->operand_stack);
}

void lrem_exe(union Context *context, struct Frame *frame)
{
    long a = popLong(frame->operand_stack);
    long b = popLong(frame->operand_stack);
    if (a == 0) {
        // TODO
    }

    ldiv_t result = ldiv(b, a);

    pushLong(result.rem, frame->operand_stack);
}

void frem_exe(union Context *context, struct Frame *frame)
{
    float a = popFloat(frame->operand_stack);
    float b = popFloat(frame->operand_stack);
    if (a == 0) {
        // TODO
    }
    pushFloat(b % a, frame->operand_stack);
}

void drem_exe(union Context *context, struct Frame *frame)
{
    double a = popDouble(frame->operand_stack);
    double b = popDouble(frame->operand_stack);
    if (a == 0) {
        // TODO
    }
    pushDouble(b % a, frame->operand_stack);
}

void ineg_exe(union Context *context, struct Frame *frame)
{
    int a = popInt(frame->operand_stack);
    int b = popInt(frame->operand_stack);
    pushInt(a + b, frame->operand_stack);
}

void lneg_exe(union Context *context, struct Frame *frame)
{
    long a = popLong(frame->operand_stack);
    long b = popLong(frame->operand_stack);
    pushLong(a + b, frame->operand_stack);
}

void fneg_exe(union Context *context, struct Frame *frame)
{
    float a = popFloat(frame->operand_stack);
    float b = popFloat(frame->operand_stack);
    pushFloat(a + b, frame->operand_stack);

}

void dneg_exe(union Context *context, struct Frame *frame)
{
    double a = popDouble(frame->operand_stack);
    double b = popDouble(frame->operand_stack);
    pushDouble(a + b, frame->operand_stack);

}

void ishl_exe(union Context *context, struct Frame *frame)
{

}

void lshl_exe(union Context *context, struct Frame *frame)
{

}

void ishr_exe(union Context *context, struct Frame *frame)
{

}

void lshr_exe(union Context *context, struct Frame *frame)
{

}

void iushr_exe(union Context *context, struct Frame *frame)
{

}

void lushr_exe(union Context *context, struct Frame *frame)
{

}

void iand_exe(union Context *context, struct Frame *frame)
{
    int v2 = popInt(frame->operand_stack);
    int v1 = popInt(frame->operand_stack);
    pushInt(v1 & v2, frame->operand_stack);
}

void land_exe(union Context *context, struct Frame *frame)
{
    long v2 = popLong(frame->operand_stack);
    long v1 = popLong(frame->operand_stack);
    pushLong(v1 & v2, frame->operand_stack);
}

void ior_exe(union Context *context, struct Frame *frame)
{
    int v2 = popInt(frame->operand_stack);
    int v1 = popInt(frame->operand_stack);
    pushInt(v1 | v2, frame->operand_stack);
}

void lor_exe(union Context *context, struct Frame *frame)
{
    long v2 = popLong(frame->operand_stack);
    long v1 = popLong(frame->operand_stack);
    pushLong(v1 | v2, frame->operand_stack);
}

void ixor_exe(union Context *context, struct Frame *frame)
{

}

void lxor_exe(union Context *context, struct Frame *frame)
{

}

void iinc_exe(union Context *context, struct Frame *frame)
{
    int v = popInt(frame->operand_stack);
    pushInt(v + 1, frame->operand_stack);
}

void i2l_exe(union Context *context, struct Frame *frame)
{

}

void i2f_exe(union Context *context, struct Frame *frame)
{

}

void i2d_exe(union Context *context, struct Frame *frame)
{

}

void l2i_exe(union Context *context, struct Frame *frame)
{

}

void l2f_exe(union Context *context, struct Frame *frame)
{

}

void l2d_exe(union Context *context, struct Frame *frame)
{

}

void f2i_exe(union Context *context, struct Frame *frame)
{

}

void f2l_exe(union Context *context, struct Frame *frame)
{

}

void f2d_exe(union Context *context, struct Frame *frame)
{

}

void d2i_exe(union Context *context, struct Frame *frame)
{

}

void d2l_exe(union Context *context, struct Frame *frame)
{

}

void d2f_exe(union Context *context, struct Frame *frame)
{

}

void i2b_exe(union Context *context, struct Frame *frame)
{

}

void i2c_exe(union Context *context, struct Frame *frame)
{

}

void i2s_exe(union Context *context, struct Frame *frame)
{

}

void lcmp_exe(union Context *context, struct Frame *frame)
{
    long v2 = popLong(frame->operand_stack);
    long v1 = popLong(frame->operand_stack);
    if (v1 > v2) {
        pushInt(1, frame->operand_stack);
    } else if (v1 == v2) {
        pushInt(0, frame->operand_stack);
    } else {
        pushInt(-1, frame->operand_stack);
    }
}

void fcmpl_exe(union Context *context, struct Frame *frame)
{

}

void fcmpg_exe(union Context *context, struct Frame *frame)
{

}

void dcmpl_exe(union Context *context, struct Frame *frame)
{

}

void dcmpg_exe(union Context *context, struct Frame *frame)
{

}

void ifeq_exe(union Context *context, struct Frame *frame)
{
    int v = popInt(frame->operand_stack);
    if (v == 0) {
        branch(frame, context->offset);
    }
}

void ifne_exe(union Context *context, struct Frame *frame)
{
    int v = popInt(frame->operand_stack);
    if (v != 0) {
        branch(frame, context->offset);
    }
}

void iflt_exe(union Context *context, struct Frame *frame)
{
    int v = popInt(frame->operand_stack);
    if (v < 0) {
        branch(frame, context->offset);
    }
}

void ifge_exe(union Context *context, struct Frame *frame)
{
    int v = popInt(frame->operand_stack);
    if (v >= 0) {
        branch(frame, context->offset);
    }
}

void ifgt_exe(union Context *context, struct Frame *frame)
{
    int v = popInt(frame->operand_stack);
    if (v > 0) {
        branch(frame, context->offset);
    }
}

void ifle_exe(union Context *context, struct Frame *frame)
{
    int v = popInt(frame->operand_stack);
    if (v <= 0) {
        branch(frame, context->offset);
    }
}

void if_icmpeq_exe(union Context *context, struct Frame *frame)
{
    int v2 = popInt(frame->operand_stack);
    int v1 = popInt(frame->operand_stack);
    if (v2 == v1) {
        branch(frame, context->offset);
    }
}

void if_icmpne_exe(union Context *context, struct Frame *frame)
{
    int v2 = popInt(frame->operand_stack);
    int v1 = popInt(frame->operand_stack);
    if (v2 != v1) {
        branch(frame, context->offset);
    }
}

void if_icmplt_exe(union Context *context, struct Frame *frame)
{
    int v2 = popInt(frame->operand_stack);
    int v1 = popInt(frame->operand_stack);
    if (v2 < v1) {
        branch(frame, context->offset);
    }

}

void if_icmpge_exe(union Context *context, struct Frame *frame)
{
    int v2 = popInt(frame->operand_stack);
    int v1 = popInt(frame->operand_stack);
    if (v2 >= v1) {
        branch(frame, context->offset);
    }

}

void if_icmpgt_exe(union Context *context, struct Frame *frame)
{
    int v2 = popInt(frame->operand_stack);
    int v1 = popInt(frame->operand_stack);
    if (v2 > v1) {
        branch(frame, context->offset);
    }

}

void if_icmple_exe(union Context *context, struct Frame *frame)
{
    int v2 = popInt(frame->operand_stack);
    int v1 = popInt(frame->operand_stack);
    if (v2 <= v1) {
        branch(frame, context->offset);
    }

}

void if_acmpeq_exe(union Context *context, struct Frame *frame)
{
    Object *v2 = popRef(frame->operand_stack);
    Object *v1 = popRef(frame->operand_stack);
    if (v2 != v1) {
        branch(frame, context->offset);
    }
}

void if_acmpne_exe(union Context *context, struct Frame *frame)
{
    Object *v2 = popRef(frame->operand_stack);
    Object *v1 = popRef(frame->operand_stack);
    if (v2 != v1) {
        branch(frame, context->offset);
    }
}

void goto_exe(union Context *context, struct Frame *frame)
{
    branch(frame, context->offset);
}

void jsr_exe(union Context *context, struct Frame *frame)
{

}

void ret_exe(union Context *context, struct Frame *frame)
{

}

void tableswitch_exe(union Context *context, struct Frame *frame)
{

}

void lookupswitch_exe(union Context *context, struct Frame *frame)
{

}

void ireturn_exe(union Context *context, struct Frame *frame)
{

}

void lreturn_exe(union Context *context, struct Frame *frame)
{

}

void freturn_exe(union Context *context, struct Frame *frame)
{

}

void dreturn_exe(union Context *context, struct Frame *frame)
{

}

void areturn_exe(union Context *context, struct Frame *frame)
{

}

void return_exe(union Context *context, struct Frame *frame)
{

}

void getstatic_exe(union Context *context, struct Frame *frame)
{

}

void putstatic_exe(union Context *context, struct Frame *frame)
{

}

void getfield_exe(union Context *context, struct Frame *frame)
{

}

void putfield_exe(union Context *context, struct Frame *frame)
{

}

void invokevirtual_exe(union Context *context, struct Frame *frame)
{

}

void invokespecial_exe(union Context *context, struct Frame *frame)
{

}

void invokestatic_exe(union Context *context, struct Frame *frame)
{

}

void invokeinterface_exe(union Context *context, struct Frame *frame)
{

}

void invokedynamic_exe(union Context *context, struct Frame *frame)
{

}

void new_exe(union Context *context, struct Frame *frame)
{

}

void newarray_exe(union Context *context, struct Frame *frame)
{

}

void anewarray_exe(union Context *context, struct Frame *frame)
{

}

void arraylength_exe(union Context *context, struct Frame *frame)
{

}

void athrow_exe(union Context *context, struct Frame *frame)
{

}

void checkcast_exe(union Context *context, struct Frame *frame)
{

}

void instanceof_exe(union Context *context, struct Frame *frame)
{

}

void monitorenter_exe(union Context *context, struct Frame *frame)
{

}

void monitorexit_exe(union Context *context, struct Frame *frame)
{

}

void wide_exe(union Context *context, struct Frame *frame)
{

}

void multianewarray_exe(union Context *context, struct Frame *frame)
{

}

void ifnull_exe(union Context *context, struct Frame *frame)
{
    struct Object *ref = popRef(frame->operand_stack);
    if (ref == NULL) {
        branch(frame, context->offset);
    }
}

void ifnonnull_exe(union Context *context, struct Frame *frame)
{
    struct Object *ref = popRef(frame->operand_stack);
    if (ref != NULL) {
        branch(frame, context->offset);
    }
}

void goto_w_exe(union Context *context, struct Frame *frame)
{

}

void jsr_w_exe(union Context *context, struct Frame *frame)
{

}


struct Instruction *newInstruction(u1 opcode)
{
    switch (opcode) {
        case NOP:
            return {nop_fetchOp, nop_exe};
        case ACONST_NULL:
            return {nop_fetchOp, aconst_null_exe};
        case ICONST_M1:
            return {nop_fetchOp, iconst_m1_exe};
        case ICONST_0:
            return {nop_fetchOp, iconst_0_exe};
        case ICONST_1:
            return {nop_fetchOp, iconst_1_exe};
        case ICONST_2:
            return {nop_fetchOp, iconst_2_exe};
        case ICONST_3:
            return {nop_fetchOp, iconst_3_exe};
        case ICONST_4:
            return {nop_fetchOp, iconst_4_exe};
        case ICONST_5:
            return {nop_fetchOp, iconst_5_exe};
        case LCONST_0:
            return {nop_fetchOp, lconst_0_exe};
        case LCONST_1:
            return {nop_fetchOp, lconst_1_exe};
        case FCONST_0:
            return {nop_fetchOp, fconst_0_exe};
        case FCONST_1:
            return {nop_fetchOp, fconst_1_exe};
        case FCONST_2:
            return {nop_fetchOp, fconst_2_exe};
        case DCONST_0:
            return {nop_fetchOp, dconst_0_exe};
        case DCONST_1:
            return {nop_fetchOp, dconst_1_exe};
        case BIPUSH:
            return {bipush_fetchOp, bipush_exe};
        case SIPUSH:
            return {sipush_fetchOp, sipush_exe};
        case LDC:
            return {nop_fetchOp, ldc_exe};
        case LDC_W:
            return {nop_fetchOp, ldc_w_exe};
        case LDC2_W:
            return {nop_fetchOp, ldc2_w_exe};
        case ILOAD:
            return {index8_fetchOp, iload_exe};
        case LLOAD:
            return {nop_fetchOp, lload_exe};
        case FLOAD:
            return {nop_fetchOp, fload_exe};
        case DLOAD:
            return {nop_fetchOp, dload_exe};
        case ALOAD:
            return {nop_fetchOp, aload_exe};
        case ILOAD_0:
            return {nop_fetchOp, iload_0_exe};
        case ILOAD_1:
            return {nop_fetchOp, iload_1_exe};
        case ILOAD_2:
            return {nop_fetchOp, iload_2_exe};
        case ILOAD_3:
            return {nop_fetchOp, iload_3_exe};
        case LLOAD_0:
            return {nop_fetchOp, lload_0_exe};
        case LLOAD_1:
            return {nop_fetchOp, lload_1_exe};
        case LLOAD_2:
            return {nop_fetchOp, lload_2_exe};
        case LLOAD_3:
            return {nop_fetchOp, lload_3_exe};
        case FLOAD_0:
            return {nop_fetchOp, fload_0_exe};
        case FLOAD_1:
            return {nop_fetchOp, fload_1_exe};
        case FLOAD_2:
            return {nop_fetchOp, fload_2_exe};
        case FLOAD_3:
            return {nop_fetchOp, fload_3_exe};
        case DLOAD_0:
            return {nop_fetchOp, dload_0_exe};
        case DLOAD_1:
            return {nop_fetchOp, dload_1_exe};
        case DLOAD_2:
            return {nop_fetchOp, dload_2_exe};
        case DLOAD_3:
            return {nop_fetchOp, dload_3_exe};
        case ALOAD_0:
            return {nop_fetchOp, aload_0_exe};
        case ALOAD_1:
            return {nop_fetchOp, aload_1_exe};
        case ALOAD_2:
            return {nop_fetchOp, aload_2_exe};
        case ALOAD_3:
            return {nop_fetchOp, aload_3_exe};
        case IALOAD:
            return {nop_fetchOp, iaload_exe};
        case LALOAD:
            return {nop_fetchOp, laload_exe};
        case FALOAD:
            return {nop_fetchOp, faload_exe};
        case DALOAD:
            return {nop_fetchOp, daload_exe};
        case AALOAD:
            return {nop_fetchOp, aaload_exe};
        case BALOAD:
            return {nop_fetchOp, baload_exe};
        case CALOAD:
            return {nop_fetchOp, caload_exe};
        case SALOAD:
            return {nop_fetchOp, saload_exe};
        case ISTORE:
            return {index8_fetchOp, istore_exe};
        case LSTORE:
            return {nop_fetchOp, lstore_exe};
        case FSTORE:
            return {nop_fetchOp, fstore_exe};
        case DSTORE:
            return {nop_fetchOp, dstore_exe};
        case ASTORE:
            return {nop_fetchOp, astore_exe};
        case ISTORE_0:
            return {nop_fetchOp, istore_0_exe};
        case ISTORE_1:
            return {nop_fetchOp, istore_1_exe};
        case ISTORE_2:
            return {nop_fetchOp, istore_2_exe};
        case ISTORE_3:
            return {nop_fetchOp, istore_3_exe};
        case LSTORE_0:
            return {nop_fetchOp, lstore_0_exe};
        case LSTORE_1:
            return {nop_fetchOp, lstore_1_exe};
        case LSTORE_2:
            return {nop_fetchOp, lstore_2_exe};
        case LSTORE_3:
            return {nop_fetchOp, lstore_3_exe};
        case FSTORE_0:
            return {nop_fetchOp, fstore_0_exe};
        case FSTORE_1:
            return {nop_fetchOp, fstore_1_exe};
        case FSTORE_2:
            return {nop_fetchOp, fstore_2_exe};
        case FSTORE_3:
            return {nop_fetchOp, fstore_3_exe};
        case DSTORE_0:
            return {nop_fetchOp, dstore_0_exe};
        case DSTORE_1:
            return {nop_fetchOp, dstore_1_exe};
        case DSTORE_2:
            return {nop_fetchOp, dstore_2_exe};
        case DSTORE_3:
            return {nop_fetchOp, dstore_3_exe};
        case ASTORE_0:
            return {nop_fetchOp, astore_0_exe};
        case ASTORE_1:
            return {nop_fetchOp, astore_1_exe};
        case ASTORE_2:
            return {nop_fetchOp, astore_2_exe};
        case ASTORE_3:
            return {nop_fetchOp, astore_3_exe};
        case IASTORE:
            return {nop_fetchOp, iastore_exe};
        case LASTORE:
            return {nop_fetchOp, lastore_exe};
        case FASTORE:
            return {nop_fetchOp, fastore_exe};
        case DASTORE:
            return {nop_fetchOp, dastore_exe};
        case AASTORE:
            return {nop_fetchOp, aastore_exe};
        case BASTORE:
            return {nop_fetchOp, bastore_exe};
        case CASTORE:
            return {nop_fetchOp, castore_exe};
        case SASTORE:
            return {nop_fetchOp, sastore_exe};
        case POP:
            return {nop_fetchOp, pop_exe};
        case POP2:
            return {nop_fetchOp, pop2_exe};
        case DUP:
            return {nop_fetchOp, dup_exe};
        case DUP_X1:
            return {nop_fetchOp, dup_x1_exe};
        case DUP_X2:
            return {nop_fetchOp, dup_x2_exe};
        case DUP2:
            return {nop_fetchOp, dup2_exe};
        case DUP2_X1:
            return {nop_fetchOp, dup2_x1_exe};
        case DUP2_X2:
            return {nop_fetchOp, dup2_x2_exe};
        case SWAP:
            return {nop_fetchOp, swap_exe};
        case IADD:
            return {nop_fetchOp, iadd_exe};
        case LADD:
            return {nop_fetchOp, ladd_exe};
        case FADD:
            return {nop_fetchOp, fadd_exe};
        case DADD:
            return {nop_fetchOp, dadd_exe};
        case ISUB:
            return {nop_fetchOp, isub_exe};
        case LSUB:
            return {nop_fetchOp, lsub_exe};
        case FSUB:
            return {nop_fetchOp, fsub_exe};
        case DSUB:
            return {nop_fetchOp, dsub_exe};
        case IMUL:
            return {nop_fetchOp, imul_exe};
        case LMUL:
            return {nop_fetchOp, lmul_exe};
        case FMUL:
            return {nop_fetchOp, fmul_exe};
        case DMUL:
            return {nop_fetchOp, dmul_exe};
        case IDIV:
            return {nop_fetchOp, idiv_exe};
        case LDIV:
            return {nop_fetchOp, ldiv_exe};
        case FDIV:
            return {nop_fetchOp, fdiv_exe};
        case DDIV:
            return {nop_fetchOp, ddiv_exe};
        case IREM:
            return {nop_fetchOp, irem_exe};
        case LREM:
            return {nop_fetchOp, lrem_exe};
        case FREM:
            return {nop_fetchOp, frem_exe};
        case DREM:
            return {nop_fetchOp, drem_exe};
        case INEG:
            return {nop_fetchOp, ineg_exe};
        case LNEG:
            return {nop_fetchOp, lneg_exe};
        case FNEG:
            return {nop_fetchOp, fneg_exe};
        case DNEG:
            return {nop_fetchOp, dneg_exe};
        case ISHL:
            return {nop_fetchOp, ishl_exe};
        case LSHL:
            return {nop_fetchOp, lshl_exe};
        case ISHR:
            return {nop_fetchOp, ishr_exe};
        case LSHR:
            return {nop_fetchOp, lshr_exe};
        case IUSHR:
            return {nop_fetchOp, iushr_exe};
        case LUSHR:
            return {nop_fetchOp, lushr_exe};
        case IAND:
            return {nop_fetchOp, iand_exe};
        case LAND:
            return {nop_fetchOp, land_exe};
        case IOR:
            return {nop_fetchOp, ior_exe};
        case LOR:
            return {nop_fetchOp, lor_exe};
        case IXOR:
            return {nop_fetchOp, ixor_exe};
        case LXOR:
            return {nop_fetchOp, lxor_exe};
        case IINC:
            return {nop_fetchOp, iinc_exe};
        case I2L:
            return {nop_fetchOp, i2l_exe};
        case I2F:
            return {nop_fetchOp, i2f_exe};
        case I2D:
            return {nop_fetchOp, i2d_exe};
        case L2I:
            return {nop_fetchOp, l2i_exe};
        case L2F:
            return {nop_fetchOp, l2f_exe};
        case L2D:
            return {nop_fetchOp, l2d_exe};
        case F2I:
            return {nop_fetchOp, f2i_exe};
        case F2L:
            return {nop_fetchOp, f2l_exe};
        case F2D:
            return {nop_fetchOp, f2d_exe};
        case D2I:
            return {nop_fetchOp, d2i_exe};
        case D2L:
            return {nop_fetchOp, d2l_exe};
        case D2F:
            return {nop_fetchOp, d2f_exe};
        case I2B:
            return {nop_fetchOp, i2b_exe};
        case I2C:
            return {nop_fetchOp, i2c_exe};
        case I2S:
            return {nop_fetchOp, i2s_exe};
        case LCMP:
            return {nop_fetchOp, lcmp_exe};
        case FCMPL:
            return {nop_fetchOp, fcmpl_exe};
        case FCMPG:
            return {nop_fetchOp, fcmpg_exe};
        case DCMPL:
            return {nop_fetchOp, dcmpl_exe};
        case DCMPG:
            return {nop_fetchOp, dcmpg_exe};
        case IFEQ:
            return {branch_fetchOp, ifeq_exe};
        case IFNE:
            return {branch_fetchOp, ifne_exe};
        case IFLT:
            return {branch_fetchOp, iflt_exe};
        case IFGE:
            return {branch_fetchOp, ifge_exe};
        case IFGT:
            return {branch_fetchOp, ifgt_exe};
        case IFLE:
            return {branch_fetchOp, ifle_exe};
        case IF_ICMPEQ:
            return {nop_fetchOp, if_icmpeq_exe};
        case IF_ICMPNE:
            return {nop_fetchOp, if_icmpne_exe};
        case IF_ICMPLT:
            return {nop_fetchOp, if_icmplt_exe};
        case IF_ICMPGE:
            return {nop_fetchOp, if_icmpge_exe};
        case IF_ICMPGT:
            return {nop_fetchOp, if_icmpgt_exe};
        case IF_ICMPLE:
            return {nop_fetchOp, if_icmple_exe};
        case IF_ACMPEQ:
            return {nop_fetchOp, if_acmpeq_exe};
        case IF_ACMPNE:
            return {nop_fetchOp, if_acmpne_exe};
        case GOTO:
            return {nop_fetchOp, goto_exe};
        case JSR:
            return {nop_fetchOp, jsr_exe};
        case RET:
            return {nop_fetchOp, ret_exe};
        case TABLESWITCH:
            return {nop_fetchOp, tableswitch_exe};
        case LOOKUPSWITCH:
            return {nop_fetchOp, lookupswitch_exe};
        case IRETURN:
            return {nop_fetchOp, ireturn_exe};
        case LRETURN:
            return {nop_fetchOp, lreturn_exe};
        case FRETURN:
            return {nop_fetchOp, freturn_exe};
        case DRETURN:
            return {nop_fetchOp, dreturn_exe};
        case ARETURN:
            return {nop_fetchOp, areturn_exe};
        case RETURN:
            return {nop_fetchOp, return_exe};
        case GETSTATIC:
            return {nop_fetchOp, getstatic_exe};
        case PUTSTATIC:
            return {nop_fetchOp, putstatic_exe};
        case GETFIELD:
            return {nop_fetchOp, getfield_exe};
        case PUTFIELD:
            return {nop_fetchOp, putfield_exe};
        case INVOKEVIRTUAL:
            return {nop_fetchOp, invokevirtual_exe};
        case INVOKESPECIAL:
            return {nop_fetchOp, invokespecial_exe};
        case INVOKESTATIC:
            return {nop_fetchOp, invokestatic_exe};
        case INVOKEINTERFACE:
            return {nop_fetchOp, invokeinterface_exe};
        case INVOKEDYNAMIC:
            return {nop_fetchOp, invokedynamic_exe};
        case NEW:
            return {nop_fetchOp, new_exe};
        case NEWARRAY:
            return {nop_fetchOp, newarray_exe};
        case ANEWARRAY:
            return {nop_fetchOp, anewarray_exe};
        case ARRAYLENGTH:
            return {nop_fetchOp, arraylength_exe};
        case ATHROW:
            return {nop_fetchOp, athrow_exe};
        case CHECKCAST:
            return {nop_fetchOp, checkcast_exe};
        case INSTANCEOF:
            return {nop_fetchOp, instanceof_exe};
        case MONITORENTER:
            return {nop_fetchOp, monitorenter_exe};
        case MONITOREXIT:
            return {nop_fetchOp, monitorexit_exe};
        case WIDE:
            return {nop_fetchOp, wide_exe};
        case MULTIANEWARRAY:
            return {nop_fetchOp, multianewarray_exe};
        case IFNULL:
            return {branch_fetchOp, ifnull_exe};
        case IFNONNULL:
            return {branch_fetchOp, ifnonnull_exe};
        case GOTO_W:
            return {nop_fetchOp, goto_w_exe};
        case JSR_W:
            return {nop_fetchOp, jsr_w_exe};
        // TODO
    }
}