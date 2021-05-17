#include <stdio.h>
#include <stdlib.h>

#include "KeywordData.c"
#include "argparse.c"

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
			if (ferror( f ) != 0) {
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

size_t compile(
	char *input_file_path,
	char *output_file_path,
	Tree *keywords
) {
	char *s = readFile(input_file_path);
	char *c = s;
	
	char *result = malloc(sizeof(char) * compile__chunk_size);
	char *result_end = result;

	TreeNode *n = &keywords->root;
	State state;
	char *copy_from;
	int copy_n;
	for (; *c; c++) {
		if (n->children[(int)*c])
			n = n->children[(int)*c];
		else {
			if (n->value) {
				NodeData *current_keyword_data = n->value;
				current_keyword_data->stateTransform(&c, &state, &copy_from, &copy_n);
				memcpy(result_end, copy_from, copy_n);
				result_end += copy_n;
				current_keyword_data->last_inclusion = c - current_keyword_data->length;
				--c;
			}
			n = &keywords->root;
		}
	}

	size_t result_length = result_end - result;

	FILE *f = fopen(output_file_path, "w");
	if (f != NULL) 
		fwrite(result, sizeof(char), result_length, f);
	fclose(f);
	
	return result_length;
}

char *main__default_extensions[] = {"xml", "txt", ""};

int main(int argc, char *argv[]) {
	Tree *keywords_data = createTree();
	Keyword *current_keyword = keywords;
	for (; current_keyword->keyword[0] != 0; current_keyword++)
		addKeyword(
			keywords_data,
			current_keyword->keyword,
			current_keyword->stateTransform
		);

	char *input_file_path = getStrArg("i", "template.txt", argc, argv);
	char *output_file_path = getStrArg("o", "compiled_template.py", argc, argv);
	char **extensions = getListArg("e", main__default_extensions, argc, argv);

	size_t result_length = compile(input_file_path, output_file_path, keywords_data);
	printf("%s -> %s (%I64d chars)\n", input_file_path, output_file_path, result_length);

	return 0;
}