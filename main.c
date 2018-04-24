//
// 
//


#include <stdio.h>


// options
enum option_type { HELP_FLAG, VERSOPN_FLAG, CP_OPTION };

struct s_options {
	enum option_type type;
	const char *label;
	const char *class;
	const char *message;
	char **args;
}

static char **argv;
static s_options *op;
static char **emsg =  "Command line stntax error: ";

void handleflags(int i, FILE *err) 
{
	for (int j = 0; op[j].label; j++) {
		if (strncmp(&argv[i][1], op[j].label, strlen(op[j].label)) == 0) break;
	}

	if (op[j].label == 0) {
		fprintf(err, "%sundefined option.\n", emsg);
	} else if(op[j].type == HELP_FLAG) {
		 
	} else {
		fprintf(err, "%s missing argument.\n", emsg);
	}

}


int OptInit(char **a, struct s_options *o, FILE *err) 
{
	argv = a;
	op = o;
	if (argv && op) {
		for (int i = 0; argv[i]; i++) {
			if (argv[i][0]== '-') {
				handleflags[i];
			}
		}
	}
}

int main(int argc, char **argv) 
{
	static struct s_options options[] = {
		{HELP_FLAG, "help", null, "print help message", argv},
		{HELP_FLAG, "?", null, "print help message", argv},
		{HELP_FLAG, "version", null, "print version and exit", argv},
		{HELP_FLAG, "classpath", null, "classpath", argv},
		{HELP_FLAG, "cp", null, "classpath", argv}
	};

	OptInit(argv, options, stderr);
}
