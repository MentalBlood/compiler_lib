#include <stdio.h>
#include <stdlib.h>

#include "prefix_tree.c"
#include "KeywordData.c"

char* readFile(char *file_path) {
	char *source = NULL;
	FILE* f = NULL;
	fopen_s(&f, file_path, "r");
	if (f != NULL) {
		if (fseek(f, 0L, SEEK_END) == 0) {
			long bufsize = ftell(f);
			if (bufsize == -1) {
				fclose(f);
				return NULL;
			}

			if (fseek(f, 0L, SEEK_SET) != 0) {
				fclose(f);
				return NULL;
			}

			source = malloc(sizeof(char) * (bufsize + 3));

			size_t newLen = fread(source, sizeof(char), bufsize, f);
			if ( ferror( f ) != 0 ) {
				free(source);
				fclose(f);
				return NULL;
			} else
				source[newLen++] = '\0';
		}
		fclose(f);
	}
	return source;
}

#define compile__chunk_size 100000

char* compile(
	char *file_path,
	Keywords *keywords
) {
	char *s = readFile(file_path);
	char *c = s;
	
	char *result = malloc(sizeof(char) * compile__chunk_size);
	char *result_end = result;

	keywords->data[(int)'n']->last_inclusion = s;
	TreeNode *n = &keywords->tree->root;
	State state;
	char *copy_from;
	int copy_n;
	for (; *c; c++) {
		if (n->children[(int)*c])
			n = n->children[(int)*c];
		else {
			if (n->value) {
				KeywordData *current_keyword_data = keywords->data[(int)n->value[0]];
				if (n->value[0] == '?') {
					current_keyword_data->stateTransform(&state, &copy_from, &copy_n);
					memcpy(result_end, copy_from, copy_n);
					printf("?\n");
				}
				current_keyword_data->last_inclusion = c - current_keyword_data->length;
				--c;
			}
			n = &keywords->tree->root;
		}
	}

	*result_end = 0;
	result = (char*)realloc(result, sizeof(char) * (result_end - result + 1));
	
	return result;
}

int main(void) {
	Keywords *keywords_data = createKeywordsData(128);
	int i = 0;
	for (; i < keywords_number; i++)
		addKeyword(
			keywords_data,
			keywords[i].keyword,
			keywords[i].symbol,
			keywords[i].stateTransform
		);

	return 0;
}