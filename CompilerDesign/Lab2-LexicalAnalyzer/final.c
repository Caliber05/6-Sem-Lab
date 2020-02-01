#include <stdbool.h> 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

bool isDelimiter(char ch) 
{ 
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||  
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||  
        ch == '<' || ch == '=' || ch=='\t') 
        return (true); 
    return (false); 
}
bool isLB(char *ch){
	if (ch[0] == '(' ||  
        ch[0] == '[' || ch[0] == '{' )
        return(true);
    return(false);
} 
bool isRB(char *ch){
	if ( ch[0] == ')' ||  
         ch[0] == ']' ||  ch[0] == '}')
        return(true);
    return(false);
} 


bool isOperator(char ch) 
{ 
    if (ch == '+' || ch == '-' || ch == '*' ||  
        ch == '/' || ch == '>' || ch == '<' ) 
        return (true); 
    return (false); 
} 

bool isAssOperator(char ch) 
{ 
    if (ch == '=') 
        return (true); 
    return (false); 
} 

bool validIdentifier(char* str) 
{ 
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' || 
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||  
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||  
        str[0] == '9' || isDelimiter(str[0]) == true&&!strcmp(str,"\t")) 
        return (false); 
    return (true); 
} 

bool isKeyword(char* str) 
{ 
    if (!strcmp(str, "if") || !strcmp(str, "else") || 
        !strcmp(str, "while") || !strcmp(str, "do") ||  
        !strcmp(str, "break") ||  
         !strcmp(str, "continue") || !strcmp(str, "int") 
        || !strcmp(str, "double") || !strcmp(str, "float") 
        || !strcmp(str, "return") || !strcmp(str, "char") 
        || !strcmp(str, "case") || !strcmp(str, "char") 
        || !strcmp(str, "sizeof") || !strcmp(str, "long") 
        || !strcmp(str, "short") || !strcmp(str, "typedef") 
        || !strcmp(str, "switch") || !strcmp(str, "unsigned") 
        || !strcmp(str, "void") || !strcmp(str, "static") 
        || !strcmp(str, "struct") || !strcmp(str, "goto")) 
        return (true); 
    return (false); 
} 

bool isRealNumber(char* str) 
{ 
    int i, len = strlen(str); 
    bool hasDecimal = true; 
  
    if (len == 0) 
        return (false); 
    for (i = 0; i < len; i++) { 
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' && str[i] != '.' ||  
            (str[i] == '-' && i > 0)) 
            return (false); 
        if (str[i] == '.') 
            hasDecimal = true; 
    } 
    return (hasDecimal); 
} 
  
 
char* subString(char* str, int left, int right) 
{ 
    int i; 
    char* subStr = (char*)malloc( 
                  sizeof(char) * (right - left + 2)); 
  
    for (i = left; i <= right; i++) 
        subStr[i - left] = str[i]; 
    subStr[right - left + 1] = '\0'; 
    return (subStr); 
} 
  

int main() 
{ 
	
	char str[100];
     
	FILE *fa, *fb;

	fa = fopen("program2.c", "r");
	fb = fopen("q1out.c", "w");

	char ch,cb;
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



     int colno = 0,lineno = 0; 
    
    int i = 0; 
  

    fb = fopen("program2.c", "r");
	do {

		ch = getc(fb);
		
		if(ch == '\n')
		{	
						int left = 0, right = 0; 
			int len = strlen(str);
			while (right <= len && left <= right) 
            { 
        if (isDelimiter(str[right]) == false) 
            right++; 
  
        if (isDelimiter(str[right]) == true && left == right) 
        { 
            if (isOperator(str[right]) == true) 
                printf("<'%c' OPERATOR  %d %d>\n", str[right],lineno,colno+left); 
            else if (isAssOperator(str[right]) == true) 
                printf("<'%c' ASSIGNMENT OPERATOR  %d %d>\n", str[right],lineno,colno+left); 
            
  
            right++; 
            left = right; 
        } 
       
        else if (isDelimiter(str[right]) == true && left != right 
                   || (right == len && left != right)) { 
            char* subStr = subString(str, left, right - 1); 
  
            if (isKeyword(subStr) == true) 
                printf("<'%s' KEYWORD  %d  %d>\n", subStr,lineno,colno+left);

  
          
            else if (isRealNumber(subStr) == true) 
                printf("<'%s' NUMBER  %d  %d>\n", subStr,lineno,colno+left);
                else if (isLB(subStr) == true) 
                printf("<'%s' LB  %d  %d>\n", subStr,lineno,colno+left); 
                else if (isRB(subStr) == true) 
                printf("<'%s' RB  %d  %d>\n", subStr,lineno,colno+left); 
  
            else if (validIdentifier(subStr) == true
                     && isDelimiter(str[right - 1]) == false) 
                printf("<'%s' IDENTIFIER %d  %d>\n", subStr,lineno,colno+left);
             
  
            else if (validIdentifier(subStr) == false
                     && isDelimiter(str[right - 1]) == false) 
                printf("<'%s' NON IDENTIFIER  %d  %d>\n", subStr,lineno,colno+left); 
            
            left = right; 
        } 
    } 
			i=0;
			memset(str,0,100);
			lineno++;
			colno = 0;

		}
	else if(ch == '\t')
			{
                colno += 4;
			}
		else if(ch == '/')
        {

			cb = getc(fb);
			if (cb=='/')
			{
				while(ch!='\n')
					ch = getc(fb);

			}
			else if (cb =='*')
			{
				do{
					while(ch!='*')
						ch = getc(fb);
					ch = getc(fb);

				}while(ch!='/');
		}
		}
		else
        {	
			str[i++] = ch;
		}
	} while (ch != EOF);


    return (0); 
} 