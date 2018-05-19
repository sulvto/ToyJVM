//
// Created by sulvto on 18-5-14.
//

#ifndef TOYJVM_CLASSLOADER_H
#define TOYJVM_CLASSLOADER_H

#include "class.h"

#define ClassLoader_T ClassLoader
typedef struct ClassLoader_T *ClassLoader_T;

ClassLoader_T ClassLoader_new();

ClassLoader_T ClassLoader_free(ClassLoader_T _this);

Class ClassLoader_loadClass(ClassLoader_T _this, char *name);

#undef ClassLoader_T

#endif //TOYJVM_CLASSLOADER_H
