#include <stdio.h>
#include <stdlib.h>

int main() 
{
	FILE *a, *b;

	fa = fopen("q1in.c", "r");
	fb = fopen("q1out.c", "w");

	char ch;
	do {
		ch = getc(fa);
		if (ch != ' ' && ch != '\t')
			putc(ch, fb);
		else
		{
			putc(' ', fb);
			while(ch == ' ' || ch == '\t')
				ch = getc(fa);
			ungetc(ch, fa);
		}
	} while (ch != EOF);

	fclose(fa);
	fclose(fb);

	return 0;
}
