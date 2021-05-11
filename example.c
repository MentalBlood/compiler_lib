typedef struct State {
	int i;
	char c;
} State;

void exampleStateTransform(State *state, char **copy_from, int *copy_n) {

}

#include "Keyword.c"
#define keywords_number 6

Keyword keywords[keywords_number] = {
	{"\n", 'n', exampleStateTransform},
	{"<!--", 'o', exampleStateTransform},
	{"-->", 'c', exampleStateTransform},
	{"(param)", 'p', exampleStateTransform},
	{"(ref)", 'r', exampleStateTransform},
	{"(optional)", '?', exampleStateTransform}
};

#include "main.c"