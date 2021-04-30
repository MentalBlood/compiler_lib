#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_SIZE 32
#define ALPHABET_SIZE 128

#define false 0
#define true 1

typedef struct TreeNode {
	char *value;
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

void printInvalidWord(const char *word, int index) {
	printf("  word: \"%s\"\n", word);
	printf("         ");
	int i = 0;
	for (; i < index; i++)
		printf(" ");
	printf("^\n");
}

int treeInsert(Tree* tree, const char *word, char *description) {
	// printf("%s: %s\n", word, description);
	TreeNode *node = &tree->root;
	int i;
	int word_len = (int)strlen(word);
	for (i = 0; i < word_len; i++) {
		int letter = (int)word[i];
		if (letter == -1) {
			// invalid character in the string, cannot be inserted into the tree
			printf("failed to insert due to invalid character in word\n");
			printInvalidWord(word, i);
			printf("  description: \"%s\"\n", description);
			return false;
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

	int description_len = (int)strlen(description);
	node->value = malloc(sizeof(char) * (description_len + 1));
	strncpy_s(node->value, sizeof(char) * (description_len + 1), description, description_len);
	return true;
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

char* treeGet(TreeNode *node, const char *word) {
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

char* dictionaryLookup(Tree*tree, const char *word) {
	int i;
	int word_len = (int)strlen(word);
	for (i = 0; i < word_len; i++) {
		int letter = (int)word[i];
		if (letter == -1) {
			printInvalidWord(word, i);
			return NULL;
		}
	}

	char *description = treeGet(&tree->root, word);
	return description;
}