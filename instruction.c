//
// Created by sulvto on 18-4-30.
//

#include "rtda.h"
#include "bytecode.h"
#include "instruction.h"
#include <stdlib.h>
#include <math.h>

void nop_fetchOp(union Context *context, struct Bytecode *data)
{
    // noting to do
}

void branch_fetchOp(union Context *context, struct Bytecode *data)
{
    context->offset = readBytecodeU2(data);
}

void branch(struct Frame *frame, int offset)
{
    int pc = frame->thread->pc;
    frame->nextPC = pc + offset;
}

void index8_fetchOp(union Context *context, struct Bytecode *data)
{
    context->index = readBytecodeU1(data);
}

void index16_fetchOp(union Context *context, struct Bytecode *data)
{
    context->index = readBytecodeU2(data);
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

void bipush_fetchOp(union Context *context, struct Bytecode *bytecode_data)
{
    // TODO byte int
    context->bi = readU1(bytecode_data);
}

void bipush_exe(union Context *context, struct Frame *frame)
{
    u1 bi = context->bi;
    pushInt(bi, frame->operand_stack);

}

void sipush_fetchOp(union Context *context, struct Bytecode *bytecode_data)
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
    pushSlot(slot, frame->operand_stack);
    pushSlot(slot, frame->operand_stack);
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
//    pushFloat(fmod(b, a), frame->operand_stack);
}

void drem_exe(union Context *context, struct Frame *frame)
{
    double a = popDouble(frame->operand_stack);
    double b = popDouble(frame->operand_stack);
    if (a == 0) {
        // TODO
    }
//    pushDouble(fmod(b, a), frame->operand_stack);
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
    struct Object *v2 = popRef(frame->operand_stack);
    struct Object *v1 = popRef(frame->operand_stack);
    if (v2 != v1) {
        branch(frame, context->offset);
    }
}

void if_acmpne_exe(union Context *context, struct Frame *frame)
{
    struct Object *v2 = popRef(frame->operand_stack);
    struct Object *v1 = popRef(frame->operand_stack);
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

struct Instruction makeInstruction(FetchOperands fetchOperands, Execute execute)
{
    struct Instruction inst;
    inst.fetchOperands = fetchOperands;
    inst.execute = execute;
    return inst;
}

struct Instruction newInstruction(u1 opcode)
{
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
            return makeInstruction(nop_fetchOp, getstatic_exe);
        } else if (PUTSTATIC == opcode) {
            return makeInstruction(nop_fetchOp, putstatic_exe);
        } else if (GETFIELD == opcode) {
            return makeInstruction(nop_fetchOp, getfield_exe);
        } else if (PUTFIELD == opcode) {
            return makeInstruction(nop_fetchOp, putfield_exe);
        } else if (INVOKEVIRTUAL == opcode) {
            return makeInstruction(nop_fetchOp, invokevirtual_exe);
        } else if (INVOKESPECIAL == opcode) {
            return makeInstruction(nop_fetchOp, invokespecial_exe);
        } else if (INVOKESTATIC == opcode) {
            return makeInstruction(nop_fetchOp, invokestatic_exe);
        } else if (INVOKEINTERFACE == opcode) {
            return makeInstruction(nop_fetchOp, invokeinterface_exe);
        } else if (INVOKEDYNAMIC == opcode) {
            return makeInstruction(nop_fetchOp, invokedynamic_exe);
        } else if (NEW == opcode) {
            return makeInstruction(nop_fetchOp, new_exe);
        } else if (NEWARRAY == opcode) {
            return makeInstruction(nop_fetchOp, newarray_exe);
        } else if (ANEWARRAY == opcode) {
            return makeInstruction(nop_fetchOp, anewarray_exe);
        } else if (ARRAYLENGTH == opcode) {
            return makeInstruction(nop_fetchOp, arraylength_exe);
        } else if (ATHROW == opcode) {
            return makeInstruction(nop_fetchOp, athrow_exe);
        } else if (CHECKCAST == opcode) {
            return makeInstruction(nop_fetchOp, checkcast_exe);
        } else if (INSTANCEOF == opcode) {
            return makeInstruction(nop_fetchOp, instanceof_exe);
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
        } else  {
            // TODO
        }
}