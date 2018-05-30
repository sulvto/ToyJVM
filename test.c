//
// Created by sulvto on 18-5-1.
//

#include <string.h>
#include <zlib.h>
#include "map.h"
#include "type.h"

int classNameCmp(char *a, char *b) {
    if (a == NULL && b == NULL) {
        return 1;
    }

    return strcmp(a, b);
}

int stringHashCode(char *string) {
    int hash = 0;

    for (int i = 0; i < strlen(string); ++i) {
        hash = hash * 31 + string[i];
    }
    printf("hash %s\n", string);
    printf("hash %d\n", hash);
    return hash;
}

int main() {

    Map_T map = Map_new(1000, classNameCmp, stringHashCode);
    char *key = "ssss";
    Map_put(map, "ssss", "aaaa");

    char *result = (char *) Map_get(map, "ssss");
    printf("%s\n", "a");
    printf("%s\n", result);
    return 0;
}
