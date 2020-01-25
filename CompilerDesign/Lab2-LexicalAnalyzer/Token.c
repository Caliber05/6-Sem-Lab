#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{
	char lexname[2];
	unsigned int row;
	unsigned int col;
	char type[20];
}*token;

token getNextToken(char *str,int r,int c,char *t){
	token temp=(token)malloc(sizeof(struct node));
	strcpy(temp->lexname,str);
	temp->row=r;
	temp->col=c;
	strcpy(temp->type,t);
	return temp;
}


int main(){
	char ca,buf[10],inname[100];
	printf("Enter input filename: ");
	scanf(" %s", inname);	
	FILE *fp=fopen(inname,"r");
	if(fp==NULL){
		printf("Can't open the file\n");
		exit(0);
	}

	int line=1,columns=1;
	ca=fgetc(fp);

	while(ca!=EOF){
		int i=0;
		if(ca=='\"'){
			ca=getc(fp);
			while(ca!='\"')
				ca=getc(fp);
		}
		else if(ca=='\n'){
			line++;
			columns=0;
		}
		else if(ca=='#'){
			fread(buf,7,1,fp);
			if(strcmp(buf,"include")==0 || strcmp(buf,"INCLUDE")==0 || strncmp(buf,"define",6)==0 || strncmp(buf,"DEFINE",6)==0){
				ca=getc(fp);
				while(ca!='\n')
					ca=getc(fp);					
			}						
		}
		else if(ca=='+' || ca=='-' || ca=='*' || ca=='/' || ca=='%'){
			buf[i++]=ca;
			buf[i]='\0';
			token temp=getNextToken(buf,line,columns,"Arithmetic");
			printf("< \'%s\' , %d , %d , %s >\n",temp->lexname,temp->row,temp->col,temp->type );
			columns++;
		}
		else if(ca=='&'){
			buf[i++]=ca;
			ca=getc(fp);
			if(ca=='&'){
				buf[i++]=ca;
				buf[i]='\0';
				token temp=getNextToken(buf,line,columns,"Logical");
				printf("< \'%s\' , %d , %d , %s >\n",temp->lexname,temp->row,temp->col,temp->type );
				columns++;
			}
			columns++;
		}
		else if(ca=='|'){
			buf[i++]=ca;
			ca=getc(fp);
			if(ca=='|'){
				buf[i++]=ca;
				buf[i]='\0';
				token temp=getNextToken(buf,line,columns,"Logical");
				printf("< \'%s\' , %d , %d , %s >\n",temp->lexname,temp->row,temp->col,temp->type );
				columns++;
			}
			columns++;
		}
		else if(ca=='!'){
			buf[i++]=ca;
			buf[i]='\0';
			token temp=getNextToken(buf,line,columns,"Logical");
			printf("< \'%s\' , %d , %d , %s >\n",temp->lexname,temp->row,temp->col,temp->type );
			columns++;
		}
		else if(ca == '='){
			buf[i++]=ca;
			ca=fgetc(fp);
			if(ca =='='){
				buf[i++]=ca;
				buf[i]='\0';
				token temp=getNextToken(buf,line,columns,"Relational");
				printf("< \'%s\' , %d , %d , %s >\n",temp->lexname,temp->row,temp->col,temp->type );
				columns++;
			}
			else{
				buf[i]='\0';
				token temp=getNextToken(buf,line,columns,"Assignment");
				printf("< \'%s\' , %d , %d , %s >\n",temp->lexname,temp->row,temp->col,temp->type );
				columns++;
			}
		}
		else if(ca=='?' || ca==':' || ca==';' || ca==',' || ca=='(' || ca==')' || ca=='[' || ca==']' || ca=='{' || ca=='}'){
			buf[i++]=ca;
			buf[i]='\0';
			token temp=getNextToken(buf,line,columns,"Special Symbol");
			printf("< \'%s\' , %d , %d , %s >\n",temp->lexname,temp->row,temp->col,temp->type );
			columns++;
		}
		else{
			if(ca=='<' || ca=='>' || ca=='!'){
				buf[i++]=ca;
				ca=fgetc(fp);
				if(ca == '='){
					buf[i++]=ca;
					columns++;
				}
				buf[i]='\0';
				token temp=getNextToken(buf,line,columns,"Relational");
				printf("< \'%s\' , %d , %d , %s >\n",temp->lexname,temp->row,temp->col,temp->type );
				columns++;
			}
			else
				buf[i]='\0';
		}
		columns++;
		ca=getc(fp);		
	}
}
