typedef struct Keyword {
	char *keyword;
	void (*stateTransform)(State *state, char **copy_from, int *copy_n);
} Keyword;