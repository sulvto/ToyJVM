//
// Created by sulvto on 18-5-1.
//

#include <string.h>
#include <zlib.h>
#include "type.h"

//const unsigned
char *test = "(ppppppppppppppppppppppppppppppppppppppppppppppppppppp)";

char *test2 = "[aaaa]";

void getName(char **name, int s) {
    size_t len = (s == 1) ? strlen(test) : strlen(test2);
    *name = malloc(len + 1);



    for (int i = 0; i < len; ++i) {
        (*name)[i] = (s == 1) ? test[i] : test2[i];
    }

    (*name)[len] = '\0';

    printf("getName %d %p %s\n", strlen(*name), &*name, *name);

}

void g(char **name, int s) {
    getName(name, s);
}

struct A {
    char *name;
    char *desc;
};
int main() {
    struct A a;


        printf("name :%p, %s\n", a.name, a.name);
    g(&a.desc, 2);
    printf("name :%p, %s\n", &a.name, a.name);
    g(&a.name, 1);

    printf("name :%p, %s\n", &a.name, a.name);
    printf("desc :%p, %s\n", &a.desc,a.desc);

    return 0;
}
