#include <stdio.h>

int main()
{
	char buf[512] = {0};
	scanf("%511s", buf);
	printf("stdin :%s\n", buf);

	FILE *file = fopen("/Users/Yarique/childTestResult", "w");

	printf("stdin :%s\n", buf);
	fprintf(file, "stdin :%s\n", buf);

	fclose(file);

	return 0;
}
