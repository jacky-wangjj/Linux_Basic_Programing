#include<stdio.h>
#include<string.h>

char *substring(char *source, char *sub)
{
	char *index;
	int len_source = strlen(source);
	int len_sub = strlen(sub);

	if(len_sub > len_source)
		return NULL;
	while((index = source++) != '\0')
	{
		if(strncmp(index, sub, len_sub) == 0)
			return index;
	}
}
int main()
{
	char *source = "abcd bcda";
	char *sub = "bc";
	char *index;
	index = substring(source, sub);
	printf("source=%s  len=%d\nsub=%s  len=%d\nindex=%s\n",source,strlen(source),sub,strlen(sub),index);

	return 0;
}

