typedef struct Keyword {
	char *keyword;
	void (*stateTransform)(char *current_character, State *state, char **copy_from, int *copy_n);
} Keyword;