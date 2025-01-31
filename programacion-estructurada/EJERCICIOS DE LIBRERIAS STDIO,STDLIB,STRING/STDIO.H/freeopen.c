#include <stdio.h>

int main() {
	char texto[256];
	freopen("test.txt", "w", stdout);
	fgets(texto, 256, stdin);
	printf("xd");
	puts(texto);
	fclose(stdout);
	
	freopen("con", "w", stdout);
	freopen("test.txt", "r", stdin);
	fgets(texto, 256, stdin);
	puts(texto);
	return 0;
}