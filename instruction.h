//
// Created by sulvto on 18-4-30.
//

#ifndef TOYJVM_INSTRUCTION_H
#define TOYJVM_INSTRUCTION_H

#include "type.h"
#include "rtda.h"
#include "bytecode.h"

#define NOP             0x00
#define ACONST_NULL     0x01
#define ICONST_M1       0x02
#define ICONST_0        0x03
#define ICONST_1        0x04
#define ICONST_2        0x05
#define ICONST_3        0x06
#define ICONST_4        0x07
#define ICONST_5        0x08
#define LCONST_0        0x09
#define LCONST_1        0x0a
#define FCONST_0        0x0b
#define FCONST_1        0x0c
#define FCONST_2        0x0d
#define DCONST_0        0x0e
#define DCONST_1        0x0f
#define BIPUSH          0x10
#define SIPUSH          0x11
#define LDC             0x12
#define LDC_W           0x13
#define LDC2_W          0x14
#define ILOAD           0x15
#define LLOAD           0x16
#define FLOAD           0x17
#define DLOAD           0x18
#define ALOAD           0x19
#define ILOAD_0         0x1a
#define ILOAD_1         0x1b
#define ILOAD_2         0x1c
#define ILOAD_3         0x1d
#define LLOAD_0         0x1e
#define LLOAD_1         0x1f
#define LLOAD_2         0x20
#define LLOAD_3         0x21
#define FLOAD_0         0x22
#define FLOAD_1         0x23
#define FLOAD_2         0x24
#define FLOAD_3         0x25
#define DLOAD_0         0x26
#define DLOAD_1         0x27
#define DLOAD_2         0x28
#define DLOAD_3         0x29
#define ALOAD_0         0x2a
#define ALOAD_1         0x2b
#define ALOAD_2         0x2c
#define ALOAD_3         0x2d
#define IALOAD          0x2e
#define LALOAD          0x2f
#define FALOAD          0x30
#define DALOAD          0x31
#define AALOAD          0x32
#define BALOAD          0x33
#define CALOAD          0x34
#define SALOAD          0x35
#define ISTORE          0x36
#define LSTORE          0x37
#define FSTORE          0x38
#define DSTORE          0x39
#define ASTORE          0x3a
#define ISTORE_0        0x3b
#define ISTORE_1        0x3c
#define ISTORE_2        0x3d
#define ISTORE_3        0x3e
#define LSTORE_0        0x3f
#define LSTORE_1        0x40
#define LSTORE_2        0x41
#define LSTORE_3        0x42
#define FSTORE_0        0x43
#define FSTORE_1        0x44
#define FSTORE_2        0x45
#define FSTORE_3        0x46
#define DSTORE_0        0x47
#define DSTORE_1        0x48
#define DSTORE_2        0x49
#define DSTORE_3        0x4a
#define ASTORE_0        0x4b
#define ASTORE_1        0x4c
#define ASTORE_2        0x4d
#define ASTORE_3        0x4e
#define IASTORE         0x4f
#define LASTORE         0x50
#define FASTORE         0x51
#define DASTORE         0x52
#define AASTORE         0x53
#define BASTORE         0x54
#define CASTORE         0x55
#define SASTORE         0x56
#define POP             0x57
#define POP2            0x58
#define DUP             0x59
#define DUP_X1          0x5a
#define DUP_X2          0x5b
#define DUP2            0x5c
#define DUP2_X1         0x5d
#define DUP2_X2         0x5e
#define SWAP            0x5f
#define IADD            0x60
#define LADD            0x61
#define FADD            0x62
#define DADD            0x63
#define ISUB            0x64
#define LSUB            0x65
#define FSUB            0x66
#define DSUB            0x67
#define IMUL            0x68
#define LMUL            0x69
#define FMUL            0x6a
#define DMUL            0x6b
#define IDIV            0x6c
#define LDIV            0x6d
#define FDIV            0x6e
#define DDIV            0x6f
#define IREM            0x70
#define LREM            0x71
#define FREM            0x72
#define DREM            0x73
#define INEG            0x74
#define LNEG            0x75
#define FNEG            0x76
#define DNEG            0x77
#define ISHL            0x78
#define LSHL            0x79
#define ISHR            0x7a
#define LSHR            0x7b
#define IUSHR           0x7c
#define LUSHR           0x7d
#define IAND            0x7e
#define LAND            0x7f
#define IOR             0x80
#define LOR             0x81
#define IXOR            0x82
#define LXOR            0x83
#define IINC            0x84
#define I2L             0x85
#define I2F             0x86
#define I2D             0x87
#define L2I             0x88
#define L2F             0x89
#define L2D             0x8a
#define F2I             0x8b
#define F2L             0x8c
#define F2D             0x8d
#define D2I             0x8e
#define D2L             0x8f
#define D2F             0x90
#define I2B             0x91
#define I2C             0x92
#define I2S             0x93
#define LCMP            0x94
#define FCMPL           0x95
#define FCMPG           0x96
#define DCMPL           0x97
#define DCMPG           0x98
#define IFEQ            0x99
#define IFNE            0x9a
#define IFLT            0x9b
#define IFGE            0x9c
#define IFGT            0x9d
#define IFLE            0x9e
#define IF_ICMPEQ       0x9f
#define IF_ICMPNE       0xa0
#define IF_ICMPLT       0xa1
#define IF_ICMPGE       0xa2
#define IF_ICMPGT       0xa3
#define IF_ICMPLE       0xa4
#define IF_ACMPEQ       0xa5
#define IF_ACMPNE       0xa6
#define GOTO            0xa7
#define JSR             0xa8
#define RET             0xa9
#define TABLESWITCH     0xaa
#define LOOKUPSWITCH    0xab
#define IRETURN         0xac
#define LRETURN         0xad
#define FRETURN         0xae
#define DRETURN         0xaf
#define ARETURN         0xb0
#define RETURN          0xb1
#define GETSTATIC       0xb2
#define PUTSTATIC       0xb3
#define GETFIELD        0xb4
#define PUTFIELD        0xb5
#define INVOKEVIRTUAL   0xb6
#define INVOKESPECIAL   0xb7
#define INVOKESTATIC    0xb8
#define INVOKEINTERFACE 0xb9
#define INVOKEDYNAMIC   0xba
#define NEW             0xbb
#define NEWARRAY        0xbc
#define ANEWARRAY       0xbd
#define ARRAYLENGTH     0xbe
#define ATHROW          0xbf
#define CHECKCAST       0xc0
#define INSTANCEOF      0xc1
#define MONITORENTER    0xc2
#define MONITOREXIT     0xc3
#define WIDE            0xc4
#define MULTIANEWARRAY  0xc5
#define IFNULL          0xc6
#define IFNONNULL       0xc7
#define GOTO_W          0xc8
#define JSR_W           0xc9


union Context {
    int index;
    int offset;
    u1 bi;
    short si;
};

typedef void(*Execute)(union Context *, struct Frame *);

typedef void(*FetchOperands)(union Context *, struct Bytecode *);


struct Instruction {
    FetchOperands fetchOperands;
    Execute execute;
};


struct Instruction newInstruction(u1 opcode);

#endif //TOYJVM_INSTRUCTION_H
