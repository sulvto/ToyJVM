//
// Created by sulvto on 18-5-22.
//

#include "rtda.h"
#include "array.h"

static int checkArrayCopy(Object src, Object desc) {
    Class src_class = Object_getClass(src);
    Class desc_class = Object_getClass(desc);

    if (!Class_isArray(src_class) || !Class_isArray(desc_class)) {
        return 0;
    }


    // TODO ComponentClass

    return 1;
}

void arraycopy(Frame frame) {
    Slots vars = Frame_localVars(frame);
    Object src = getRef(0, vars);
    int src_pos = getInt(1, vars);
    Object desc = getRef(2, vars);
    int desc_pos = getInt(3, vars);
    int length = getInt(4, vars);

    if (src == NULL || desc == NULL) {
        printf("java.lang.NullPointerException\n");
    }

    if (!checkArrayCopy(src, desc)) {
        printf("java.lang.ArrayStoreException\n");
    }

    if (src_pos < 0 || desc_pos < 0 || length < 0 || src_pos + length > Object_arrayLength(src) ||
        desc_pos + length > Object_arrayLength(desc)) {
        printf("java.lang.IndexOutOfBoundsException\n");
    }

    ArrayCopy(src, src_pos, desc, desc_pos, length);
}