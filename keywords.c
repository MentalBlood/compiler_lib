typedef struct State {
	int i;
	char c;
} State;

typedef struct KeywordData {
	char *last_inclusion;
	int length;
	char last_symbol;
	void (*stateTransform)(State *state, char **copy_from, int *copy_n);
} KeywordData;

typedef struct Keywords {
	Tree *tree;
	KeywordData **data;
} Keywords;

Keywords* createKeywordsData(int number_of_keywords) {
	Keywords *result = malloc(sizeof(Keywords));
	result->tree = createTree();
	result->data = calloc(number_of_keywords, sizeof(KeywordData*));
	return result;
}

void addKeyword(
	Keywords *keywords,
	char *keyword,
	char symbol,
	void (*stateTransform)(State *state, char **copy_from, int *copy_n)
) {
	char *value_to_insert = malloc(sizeof(char) * 2);
	value_to_insert[0] = symbol;
	value_to_insert[1] = 0;
	treeInsert(keywords->tree, keyword, value_to_insert);

	KeywordData *data = malloc(sizeof(KeywordData));
	data->last_inclusion = NULL;
	char *k = keyword;
	for (; *k; k++);
	data->length = k - keyword;
	data->last_symbol = *k;
	data->stateTransform = stateTransform;
	keywords->data[(int)symbol] = data;
}