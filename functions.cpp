#include <string.h>

void trim(char *str)
{
	int i = 0, j;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (i > 0)
	{
		for (j = 0; j < strlen(str); j++)
			str[j] = str[j + i];
		str[j] = '\0';
	}
	i = strlen(str) - 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i--;
	if (i < (strlen(str) - 1))
		str[i + 1] = '\0';
}