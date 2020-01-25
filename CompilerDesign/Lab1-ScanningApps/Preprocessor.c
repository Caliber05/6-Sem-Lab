#include <stdio.h>
#include <stdlib.h>

int main() 
{
	FILE *fa, *fb;

	fa = fopen("in.c", "r");
	if(fa == NULL)
	{
		printf("Cannot open file\n");
		exit(0);
	}
	fb = fopen("out.c", "w");

	char ch;
	do {
		ch = getc(fa); 
		if (ch == '#') { 
			while (ch != '\n') { 
				ch = getc(fa);
			}
		}
		putc(ch, fb);
	} while (ch != EOF);

	fclose(fa);
	fclose(fb);

	return 0;
}
