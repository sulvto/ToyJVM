//
// 
//


#include <stdio.h>
#include <string.h>
#include "rtda.h"
#include "type.h"
#include "class.h"
#include "classreader.h"
#include "bytecode.h"
#include "interpreter.h"
#include "map.h"
#include "classloader.h"
#include "native.h"

//
//// options
//enum option_type { HELP_FLAG, VERSOPN_FLAG, CP_OPTION };
//
//struct s_options {
//	enum option_type type;
//	const char *label;
//	const char *class;
//	const char *message;
//	char **args;
//}
//
//static char **argv;
//static s_options *op;
//static char **emsg =  "Command line stntax error: ";
//
//void handleflags(int i, FILE *err)
//{
//	for (int j = 0; op[j].label; j++) {
//		if (strncmp(&argv[i][1], op[j].label, strlen(op[j].label)) == 0) break;
//	}
//
//	if (op[j].label == 0) {
//		fprintf(err, "%sundefined option.\n", emsg);
//	} else if(op[j].type == HELP_FLAG) {
//
//	} else {
//		fprintf(err, "%s missing argument.\n", emsg);
//	}
//
//}
//

//int OptInit(char **a, struct s_options *o, FILE *err)
//{
//	argv = a;
//	op = o;
//	if (argv && op) {
//		for (int i = 0; argv[i]; i++) {
//			if (argv[i][0]== '-') {
//				handleflags[i];
//			}
//		}
//	}
//}


void registerNativeMethod() {
    NativeMethod_register("java/lang/System", "arraycopy", "(Ljava/lang/Object;ILjava/lang/Object;II)V", NULL);
}

int main(int argc, char **argv) {
//	static struct s_options options[] = {
//		{HELP_FLAG, "help", null, "print help message", argv},
//		{HELP_FLAG, "?", null, "print help message", argv},
//		{HELP_FLAG, "version", null, "print version and exit", argv},
//		{HELP_FLAG, "classpath", null, "classpath", argv},
//		{HELP_FLAG, "cp", null, "classpath", argv}
//	};
//
//	OptInit(argv, options, stderr);

    registerNativeMethod();

    ClassLoader loader = ClassLoader_new();
    Class _class = ClassLoader_loadClass(loader, "/home/qinchao/development/workspace/ToyJVM/Test.class");
    printf("Class_getMainMethod \n");
    Method mainMethod = Class_getMainMethod(_class);

    if (mainMethod != NULL) {
        interpret(mainMethod);
    } else {
        printf("Main method not found in class! \n");
    }

}
