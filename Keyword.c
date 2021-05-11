typedef struct Keyword {
	char *keyword;
	char symbol;
	void (*stateTransform)(State *state, char **copy_from, int *copy_n);
} Keyword;