typedef struct State {
	int i;
	char c;
} State;

void exampleStateTransform(State *state, char **copy_from, int *copy_n) {

}

#include "Keyword.c"

Keyword keywords[] = {
	{"some_keyword", exampleStateTransform},
	{""}
};

#include "main.c"