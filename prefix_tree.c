#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_SIZE 32
#define ALPHABET_SIZE 128

typedef struct TreeNode {
	NodeData *value;
	struct TreeNode **children;
} TreeNode;

typedef struct Tree {
	TreeNode root;
} Tree;

Tree* createTree() {
	struct Tree* tree = malloc(sizeof(struct Tree));
	tree->root.value = NULL;
	tree->root.children = calloc(ALPHABET_SIZE, sizeof(TreeNode*));
	return tree;
}

int treeInsert(Tree* tree, const char *word, NodeData *data) {
	TreeNode *node = &tree->root;
	int i;
	int word_len = (int)strlen(word);
	for (i = 0; i < word_len; i++) {
		int letter = (int)word[i];
		if (letter == -1) {
			printf("failed to insert due to invalid character in word\n");
			return 0;
		}

		TreeNode *parent = node;
		node = node->children[letter];

		if (!node) {
			node = malloc(sizeof(TreeNode));
			node->value = NULL;
			node->children = calloc(ALPHABET_SIZE, sizeof(TreeNode*));
			parent->children[letter] = node;
		}
	}

	node->value = data;
	return 1;
}

void freeNodes(TreeNode *node) {
	if (node == NULL) return;
	
	free(node->value);
	TreeNode** children = node->children;
	int i = 0;
	for (; i < ALPHABET_SIZE; i++) {
		if (children[i] == NULL) continue;
		freeNodes(children[i]);
	}
	free(children);
	free(node);
}

void clearTree(Tree*tree) {
	int i = 0;
	for (; i < ALPHABET_SIZE; i++) {
		if (tree->root.children[i] == NULL) continue;
		freeNodes(tree->root.children[i]);
		tree->root.children[i] = NULL;
	}
}

NodeData* treeGet(TreeNode *node, const char *word) {
	int i;
	int word_len = (int)strlen(word);
	for (i = 0; i < word_len; i++) {
		int letter = (int)word[i];
		if (letter == -1)
			return NULL;
		node = node->children[letter];
		if (!node)
			return NULL;
	}
	return node->value;
}

NodeData* dictionaryLookup(Tree *tree, const char *word) {
	int i;
	int word_len = (int)strlen(word);
	for (i = 0; i < word_len; i++) {
		int letter = (int)word[i];
		if (letter == -1)
			return NULL;
	}

	return treeGet(&tree->root, word);
}