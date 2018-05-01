//
// Created by sulvto on 18-4-30.
//

#ifndef TOYJVM_INSTRUCTION_H
#define TOYJVM_INSTRUCTION_H

#include "type.h"
#include "rtda.h"
#include "bytecode.h"

const u1 NOP = 0x00;
const u1 ACONST_NULL = 0x01;
const u1 ICONST_M1 = 0x02;
const u1 ICONST_0 = 0x03;
const u1 ICONST_1 = 0x04;
const u1 ICONST_2 = 0x05;
const u1 ICONST_3 = 0x06;
const u1 ICONST_4 = 0x07;
const u1 ICONST_5 = 0x08;
const u1 LCONST_0 = 0x09;
const u1 LCONST_1 = 0x0a;
const u1 FCONST_0 = 0x0b;
const u1 FCONST_1 = 0x0c;
const u1 FCONST_2 = 0x0d;
const u1 DCONST_0 = 0x0e;
const u1 DCONST_1 = 0x0f;
const u1 BIPUSH = 0x10;
const u1 SIPUSH = 0x11;
const u1 LDC = 0x12;
const u1 LDC_W = 0x13;
const u1 LDC2_W = 0x14;
const u1 ILOAD = 0x15;
const u1 LLOAD = 0x16;
const u1 FLOAD = 0x17;
const u1 DLOAD = 0x18;
const u1 ALOAD = 0x19;
const u1 ILOAD_0 = 0x1a;
const u1 ILOAD_1 = 0x1b;
const u1 ILOAD_2 = 0x1c;
const u1 ILOAD_3 = 0x1d;
const u1 LLOAD_0 = 0x1e;
const u1 LLOAD_1 = 0x1f;
const u1 LLOAD_2 = 0x20;
const u1 LLOAD_3 = 0x21;
const u1 FLOAD_0 = 0x22;
const u1 FLOAD_1 = 0x23;
const u1 FLOAD_2 = 0x24;
const u1 FLOAD_3 = 0x25;
const u1 DLOAD_0 = 0x26;
const u1 DLOAD_1 = 0x27;
const u1 DLOAD_2 = 0x28;
const u1 DLOAD_3 = 0x29;
const u1 ALOAD_0 = 0x2a;
const u1 ALOAD_1 = 0x2b;
const u1 ALOAD_2 = 0x2c;
const u1 ALOAD_3 = 0x2d;
const u1 IALOAD = 0x2e;
const u1 LALOAD = 0x2f;
const u1 FALOAD = 0x30;
const u1 DALOAD = 0x31;
const u1 AALOAD = 0x32;
const u1 BALOAD = 0x33;
const u1 CALOAD = 0x34;
const u1 SALOAD = 0x35;
const u1 ISTORE = 0x36;
const u1 LSTORE = 0x37;
const u1 FSTORE = 0x38;
const u1 DSTORE = 0x39;
const u1 ASTORE = 0x3a;
const u1 ISTORE_0 = 0x3b;
const u1 ISTORE_1 = 0x3c;
const u1 ISTORE_2 = 0x3d;
const u1 ISTORE_3 = 0x3e;
const u1 LSTORE_0 = 0x3f;
const u1 LSTORE_1 = 0x40;
const u1 LSTORE_2 = 0x41;
const u1 LSTORE_3 = 0x42;
const u1 FSTORE_0 = 0x43;
const u1 FSTORE_1 = 0x44;
const u1 FSTORE_2 = 0x45;
const u1 FSTORE_3 = 0x46;
const u1 DSTORE_0 = 0x47;
const u1 DSTORE_1 = 0x48;
const u1 DSTORE_2 = 0x49;
const u1 DSTORE_3 = 0x4a;
const u1 ASTORE_0 = 0x4b;
const u1 ASTORE_1 = 0x4c;
const u1 ASTORE_2 = 0x4d;
const u1 ASTORE_3 = 0x4e;
const u1 IASTORE = 0x4f;
const u1 LASTORE = 0x50;
const u1 FASTORE = 0x51;
const u1 DASTORE = 0x52;
const u1 AASTORE = 0x53;
const u1 BASTORE = 0x54;
const u1 CASTORE = 0x55;
const u1 SASTORE = 0x56;
const u1 POP = 0x57;
const u1 POP2 = 0x58;
const u1 DUP = 0x59;
const u1 DUP_X1 = 0x5a;
const u1 DUP_X2 = 0x5b;
const u1 DUP2 = 0x5c;
const u1 DUP2_X1 = 0x5d;
const u1 DUP2_X2 = 0x5e;
const u1 SWAP = 0x5f;
const u1 IADD = 0x60;
const u1 LADD = 0x61;
const u1 FADD = 0x62;
const u1 DADD = 0x63;
const u1 ISUB = 0x64;
const u1 LSUB = 0x65;
const u1 FSUB = 0x66;
const u1 DSUB = 0x67;
const u1 IMUL = 0x68;
const u1 LMUL = 0x69;
const u1 FMUL = 0x6a;
const u1 DMUL = 0x6b;
const u1 IDIV = 0x6c;
const u1 LDIV = 0x6d;
const u1 FDIV = 0x6e;
const u1 DDIV = 0x6f;
const u1 IREM = 0x70;
const u1 LREM = 0x71;
const u1 FREM = 0x72;
const u1 DREM = 0x73;
const u1 INEG = 0x74;
const u1 LNEG = 0x75;
const u1 FNEG = 0x76;
const u1 DNEG = 0x77;
const u1 ISHL = 0x78;
const u1 LSHL = 0x79;
const u1 ISHR = 0x7a;
const u1 LSHR = 0x7b;
const u1 IUSHR = 0x7c;
const u1 LUSHR = 0x7d;
const u1 IAND = 0x7e;
const u1 LAND = 0x7f;
const u1 IOR = 0x80;
const u1 LOR = 0x81;
const u1 IXOR = 0x82;
const u1 LXOR = 0x83;
const u1 IINC = 0x84;
const u1 I2L = 0x85;
const u1 I2F = 0x86;
const u1 I2D = 0x87;
const u1 L2I = 0x88;
const u1 L2F = 0x89;
const u1 L2D = 0x8a;
const u1 F2I = 0x8b;
const u1 F2L = 0x8c;
const u1 F2D = 0x8d;
const u1 D2I = 0x8e;
const u1 D2L = 0x8f;
const u1 D2F = 0x90;
const u1 I2B = 0x91;
const u1 I2C = 0x92;
const u1 I2S = 0x93;
const u1 LCMP = 0x94;
const u1 FCMPL = 0x95;
const u1 FCMPG = 0x96;
const u1 DCMPL = 0x97;
const u1 DCMPG = 0x98;
const u1 IFEQ = 0x99;
const u1 IFNE = 0x9a;
const u1 IFLT = 0x9b;
const u1 IFGE = 0x9c;
const u1 IFGT = 0x9d;
const u1 IFLE = 0x9e;
const u1 IF_ICMPEQ = 0x9f;
const u1 IF_ICMPNE = 0xa0;
const u1 IF_ICMPLT = 0xa1;
const u1 IF_ICMPGE = 0xa2;
const u1 IF_ICMPGT = 0xa3;
const u1 IF_ICMPLE = 0xa4;
const u1 IF_ACMPEQ = 0xa5;
const u1 IF_ACMPNE = 0xa6;
const u1 GOTO = 0xa7;
const u1 JSR = 0xa8;
const u1 RET = 0xa9;
const u1 TABLESWITCH = 0xaa;
const u1 LOOKUPSWITCH = 0xab;
const u1 IRETURN = 0xac;
const u1 LRETURN = 0xad;
const u1 FRETURN = 0xae;
const u1 DRETURN = 0xaf;
const u1 ARETURN = 0xb0;
const u1 RETURN = 0xb1;
const u1 GETSTATIC = 0xb2;
const u1 PUTSTATIC = 0xb3;
const u1 GETFIELD = 0xb4;
const u1 PUTFIELD = 0xb5;
const u1 INVOKEVIRTUAL = 0xb6;
const u1 INVOKESPECIAL = 0xb7;
const u1 INVOKESTATIC = 0xb8;
const u1 INVOKEINTERFACE = 0xb9;
const u1 INVOKEDYNAMIC = 0xba;
const u1 NEW = 0xbb;
const u1 NEWARRAY = 0xbc;
const u1 ANEWARRAY = 0xbd;
const u1 ARRAYLENGTH = 0xbe;
const u1 ATHROW = 0xbf;
const u1 CHECKCAST = 0xc0;
const u1 INSTANCEOF = 0xc1;
const u1 MONITORENTER = 0xc2;
const u1 MONITOREXIT = 0xc3;
const u1 WIDE = 0xc4;
const u1 MULTIANEWARRAY = 0xc5;
const u1 IFNULL = 0xc6;
const u1 IFNONNULL = 0xc7;
const u1 GOTO_W = 0xc8;
const u1 JSR_W = 0xc9;


union Context {
    int index;
    int offset;
    u1 bi;
    short si;
};

typedef void(*Execute)(union Context *, struct Frame *);

typedef void(*FetchOperands)(union Context *, struct BytecodeData *);


struct Instruction {
    FetchOperands fetchOperands;
    Execute execute;
};


struct Instruction newInstruction(u1 opcode);

#endif //TOYJVM_INSTRUCTION_H
