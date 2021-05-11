typedef struct State {
	int i;
	char c;
} State;

void exampleStateTransform(State *state, char **copy_from, int *copy_n) {

}

#include "Keyword.c"

Keyword keywords[] = {
	{"\n", 'n', exampleStateTransform},
	{"<!--", 'o', exampleStateTransform},
	{"-->", 'c', exampleStateTransform},
	{"(param)", 'p', exampleStateTransform},
	{"(ref)", 'r', exampleStateTransform},
	{"(optional)", '?', exampleStateTransform},
	{""}
};

#include "main.c"