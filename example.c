typedef struct State {
	int i;
	char c;
} State;

void exampleStateTransform(char **current_character, State *state, char **copy_from, int *copy_n) {

}

#include "Keyword.c"

Keyword keywords[] = {
	{"some_keyword", exampleStateTransform},
	{""}
};

#include "main.c"