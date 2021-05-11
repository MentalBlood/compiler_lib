// -bool_arg_name -str_arg_name some_string -list_arg_name some list values

#include <string.h>

int getBoolArg(char *name, int argc, char *argv[]) {
	int i = 0;
	for (; i < argc; i++)
		if ((argv[i][0] == '-') && !strcmp(name, argv[i] + 1))
			return 1;
	return 0;
}

char* getStrArg(char *name, char *default_value, int argc, char *argv[]) {
	int i = 0;
	for (; i < argc; i++)
		if ((argv[i][0] == '-') && !strcmp(name, argv[i] + 1))
			if (i + 1 < argc)
				return argv[i + 1];
	return default_value;
}

char** getListArg(char *name, char **default_value, int argc, char *argv[]) {
	int found = 0;
	int values_number = 0;
	int allocated = 2;
	char **result = malloc(sizeof(char*) * allocated);
	int i = 0;
	for (; i < argc; i++)
		if ((argv[i][0] == '-') && !strcmp(name, argv[i] + 1)) {
			found = 1;
			int j = i + 1;
			for (; j < argc; j++) {
				if (argv[j][0] == '-')
					break;
				values_number += 1;
				if ((values_number + 1) < allocated) {
					allocated *= 2;
					result = (char**)realloc(result, sizeof(char*) * allocated);
				}
				result[values_number - 1] = argv[j];
			}
			break;
		}
	if (!found)
		return default_value;
	result[values_number] = "";
	return result;
}