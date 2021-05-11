typedef struct NodeData {
	char *last_inclusion;
	int length;
	char last_symbol;
	void (*stateTransform)(State *state, char **copy_from, int *copy_n);
} NodeData;

#include "prefix_tree.c"

void addKeyword(
	Tree *keywords,
	char *keyword,
	void (*stateTransform)(State *state, char **copy_from, int *copy_n)
) {
	NodeData *data = malloc(sizeof(NodeData));
	data->last_inclusion = NULL;
	char *k = keyword;
	for (; *k; k++);
	data->length = k - keyword;
	data->last_symbol = *k;
	data->stateTransform = stateTransform;

	treeInsert(keywords, keyword, data);
}