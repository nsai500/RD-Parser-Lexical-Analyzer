#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct symboltable{
char name[50];
char type[10];
int size;
}*symbol_table;

symbol_table st[1000];
int cur = 0;

int res,p_res;
FILE *fp2;
const char *identifier = "id";
const char *number = "num";

void insert(char buff[],char type[],int size){
	strcpy(st[cur]->name,buff);
	strcpy(st[cur]->type,type);
	st[cur++]->size = size;
}

int search(char buff[]){
	for(int i=0;i<cur;i++){
		if(strcmp(st[i]->name,buff) == 0) return i+1;
	}
	return -1;
}

int compare(char a[]){
	if(strcmp(a,"if") == 0 || strcmp(a,"else") == 0 || strcmp(a,"printf") == 0 || strcmp(a,"return") == 0 || strcmp(a,"for") == 0 || strcmp(a,"while") == 0 || strcmp(a,"do") == 0 || strcmp(a,"case") == 0 || strcmp(a,"switch") == 0 || strcmp(a,"default") == 0 || strcmp(a,"break") == 0 || strcmp(a,"goto") == 0 || strcmp(a,"continue") == 0 || strcmp(a,"scanf") == 0) return 1;
	else if(strcmp(a,"int") == 0) return 2;
	else if(strcmp(a,"char") == 0) return 3;
	else if(strcmp(a,"double") == 0) return 4;
	else if(strcmp(a,"float") == 0) return 5;
	else if(strcmp(a,"main") == 0) return 6;
	else if(strcmp(a,"void") == 0) return 7;
	else return 0;
}

void displaySym(){
	printf("\n\t\tSymbol Table\nIndex\tName\t\tType\tSize\n");
	for(int i=0;i<cur;i++) printf("%d\t%s\t\t%s\t%d\n",i+1,st[i]->name,st[i]->type,st[i]->size);
}

void init(){
	for(int i=0;i<1000;i++) st[i] = (struct symboltable *) malloc(sizeof(struct symboltable));
	fp2 = fopen("out2.txt","w");
}

void getNextToken(FILE **fp1,char *buf)
{	
	char c = fgetc(*fp1);
	while(c != EOF){
		int i = 0;
		buf[0] = '\0';
		if(c == ' ' || c == '\t') c = fgetc(*fp1);
		else if(c == '"'){
			buf[i++] = c;
			c = fgetc(*fp1);
			if(c != '\''){
				while(c != '"'){
					buf[i++] = c;
					c = fgetc(*fp1);					
				}
				buf[i++] = c;
				buf[i] = '\0';
				fprintf(fp2,"<print %s> ",buf);
				return;
				c = fgetc(*fp1);
			}			
		}else if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%'){
			buf[i++] = c;
			c = fgetc(*fp1);
			if(c == '+' || c == '-' || c == '*' || c == '/' || c == '='){
				buf[i++] = c;
				buf[i] = '\0';
				fprintf(fp2,"<%s> ",buf);
				return;
				c = fgetc(*fp1);
			}else{
				buf[i] = '\0';
				fprintf(fp2,"<%s> ",buf);
				fseek(*fp1,-1,SEEK_CUR);
				return;
			}
		}else if(c == '{' || c == '}' || c == '[' || c == ']' || c == '(' || c == ')' || c == ';' || c == ',' || c == ':' || c == '?' || c == '&'){
			fprintf(fp2,"<%c> ",c);
			buf[i++] = c;
			buf[i] = '\0';
			return;
			c = fgetc(*fp1);
		}else if(c == '\n'){
			fprintf(fp2,"\n");
			c = fgetc(*fp1);
		}else if(c == '<' || c == '>' || c == '=' || c == '!'){
			buf[i++] = c;
			c = fgetc(*fp1);
			if(c == '='){
				buf[i++] = c;
				buf[i] = '\0';
				fprintf(fp2,"<%s> ",buf);
				return;
				c = fgetc(*fp1);
			}else{
				buf[i] = '\0';
				fprintf(fp2,"<%s> ",buf);
				fseek(*fp1,-1,SEEK_CUR);
				return;
			}
		}else if(c >= 48 && c <= 57){
			buf[i++] = c;
			c = fgetc(*fp1);
			while((c >= 48 && c <= 57) || c =='.'){
				buf[i++] = c;
				c = fgetc(*fp1);
			}
			buf[i] = '\0';
			fprintf(fp2,"<num,%s> ",buf);
			fseek(*fp1,-1,SEEK_CUR);
			strcpy(buf,number);
			return;
		}else{
			if(c <= 122 && c >= 97){
				buf[i++] = c;
				c = fgetc(*fp1);
				while(c != ' ' && c != ';' && c != '(' && c != ')' && c != '>' && c != '<' && c != '=' && c != '+' && c != '-' && c != '*' && c != '/' && c != '{' && c != ',' && c != ':' && c != '?' && c != '[' && c != ']' && c != '!' && c != '%' && c != '}'){
					buf[i++] = c;
					c = fgetc(*fp1);
				}
				buf[i] = '\0';
				res = compare(buf);
				if(res == 1 || res == 2 || res == 3 || res == 4 || res ==5 || res == 7){
					fprintf(fp2,"<%s> ",buf);
					fseek(*fp1,-1,SEEK_CUR);
					if(res != 0) p_res = res;
					return;
				}else if(res == 6){
					int res2;
					if((res2 = search(buf)) == -1){
						insert(buf,"FUNC",-1);
						fprintf(fp2,"<id,%d> ",cur);
						fseek(*fp1,-1,SEEK_CUR);
						if(res != 0) p_res = res;
						return;
					}
				}else if(res == 0){
						if(p_res == 7){
							int res2;
							if((res2 = search(buf)) == -1){
								insert(buf,"FUNC",-1);
								fprintf(fp2,"<id,%d> ",cur);
								fseek(*fp1,-1,SEEK_CUR);
								if(res != 0) p_res = res;
								strcpy(buf,identifier);
								return;
							}
						}
						int res2;
						if((res2 = search(buf)) == -1){
							if(p_res == 2 || p_res == 3 || p_res == 4 || p_res ==5){
								while(c == ' ') c = fgetc(*fp1);
								if(c == '('){
									if((res2 = search(buf)) == -1){
										insert(buf,"FUNC",-1);
										fprintf(fp2,"<id,%d> ",cur);
										fseek(*fp1,-1,SEEK_CUR);
										if(res != 0) p_res = res;
										strcpy(buf,identifier);
										return;
									}
								}else if(c == '['){
									c = fgetc(*fp1);
									while(c == ' ') c = fgetc(*fp1);
									char buf2[10];
									int z = 0;
									int arr_size = 0;
									if(c >= 48 && c <= 57){
										buf2[z++] = c;
										arr_size = arr_size*10 + c - '0';
										c = fgetc(*fp1);
										while(c >= 48 && c <= 57){
											buf2[z++] = c;
											arr_size = arr_size*10 + c - '0';
											c = fgetc(*fp1);
										}
										buf2[z] = '\0';
									}
									if(p_res == 2) insert(buf,"int",4*arr_size);
									else if(p_res == 3) insert(buf,"char",1*arr_size);
									else if(p_res == 4) insert(buf,"double",8*arr_size);
									else insert(buf,"float",4*arr_size);
									fprintf(fp2,"<id,%d> ",cur);
									//fprintf(fp2,"<[> ");
									//fprintf(fp2,"<num,%s> ",buf2);
									fseek(*fp1,-1,SEEK_CUR);//for retracting ]
									fseek(*fp1,-(z+1),SEEK_CUR);//for retracting till [
									if(res != 0) p_res = res;
									strcpy(buf,identifier);
									return;
								}else{
									if(p_res == 2) insert(buf,"int",4);
									else if(p_res == 3) insert(buf,"char",1);
									else if(p_res == 4) insert(buf,"double",8);
									else insert(buf,"float",4);
									fprintf(fp2,"<id,%d> ",cur);
									fseek(*fp1,-1,SEEK_CUR);
									if(res != 0) p_res = res;
									strcpy(buf,identifier);
									return;
								}
							}
					}else fprintf(fp2,"<id,%d> ",res2); fseek(*fp1,-1,SEEK_CUR); if(res != 0) p_res = res; strcpy(buf,identifier); return;
				}
			}
		}
	}
}