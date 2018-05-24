//
// Created by sulvto on 18-5-24.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "methoddescriptor.h"

static char *parseFieldType(char *descriptor, int *offset);

static char *parseObjectType(char *descriptor, int *offset);

static char *parseArrayType(char *descriptor, int *offset);



// FieldType table
// 字符                  类型            含义
//  B                   byte
//  C                   char
//  D                   double
//  F                   float
//  I                   int
//  J                   long
//  L ClassName;        reference       ClassName 类的实例
//  S                   short
//  Z                   boolean
//  [                   reference       一个一维数组
//


/**
 *  MethodDescriptor:
 *      ({ParameterDescriptor})ReturnDescriptor
 *  ParameterDescriptor:
 *      FieldType
 *  ReturnDescriptor:
 *      FieldType
 *      VoidDescriptor
 *  VoidDescriptor:
 *      V
 */
struct MethodDescriptor *MethodDescriptor_parse(char *descriptor) {
    size_t length = strlen(descriptor);
    int index = 0;
    struct MethodDescriptor *result = (struct MethodDescriptor*) malloc(sizeof(struct MethodDescriptor));
    result->parameter_type_index = 0;

    if (descriptor[index++] != '(') {
        return NULL;
    }

    // ParameterDescriptor
    while (1) {
        char *string = parseFieldType(descriptor, &index);
        if (string == NULL) {
            break;
        } else {
            result->parameter_types[parameter_type_index++] = string;
        }
    }
    
    if (descriptor[index++] != ')') {
        return NULL;
    }

    // VoidDescriptor
    if (descriptor[index]=='V') {
        result->return_type = "V";
    } else {
        char *string = parseFieldType(descriptor, &index);
        if (string == NULL) {
            result->return_type = string;
        } else {
            printf("Error!\n");
        }
    }


    if (index != length) {
        printf("error!\n");
    }

    return result;
}


static char *parseFieldType(char *descriptor, int *offset) {
    switch (descriptor[*offset++]) {
        case 'B': return "B";
        case 'C': return "C";
        case 'D': return "D";
        case 'F': return "F";
        case 'I': return "I";
        case 'J': return "J";
        case 'S': return "S";
        case 'Z': return "Z";
        case 'L': return parseObjectType(descriptor, offset);
        case '[': return parseArrayType(descriptor, offset);
        default:
            *offset--;
            return NULL;
    }
}

static char *parseObjectType(char *descriptor, int *offset) {
    char *p = &descriptor[*offset];
    char *str = strchr(p, ';');

    if (str == NULL) {
        printf("ERR!\n");
        return NULL;
    }

    char copy[255];
    int i = 0;
    while (p != str) {
        copy[i++] = *p++;
    }

    copy[i++] = *p; // ;
    copy[i] = '\0';

    *offset += i;

    char *result = malloc((size_t) i);
    strcpy(result, copy);

    return result;
}

static char *parseArrayType(char *descriptor, int *offset) {
    int start = *offset - 1;
    parseFieldType(descriptor, offset);
    int end = *offset;

    char *str, *p;
    p = str = malloc((size_t) (end - start + 1));

    while (start < end) {
        *p++ = descriptor[start++];
    }

    *p = '\0';

    return str;
}