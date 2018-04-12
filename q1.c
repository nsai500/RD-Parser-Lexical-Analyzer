#include <stdio.h>
#include "lab6_1.c"

int error = 0;
FILE *fp1;
char buf[100];

void Program();
void declarations();
void datatype();
void identifier_list();
void idd1();
void assign_stat();
void idd2();
void statement_list();
void statement();
void expn();
void eprime();
void simple_expn();
void seprime();
void term();
void tprime();
void factor();
void relop();
void addop();
void mulop();
void decision_stat();
void looping_stat();
void dprime();

void Program(){
	getNextToken(&fp1,buf);
	if(strcmp(buf,"main") == 0){
		getNextToken(&fp1,buf);
		if(strcmp(buf,"(") == 0){
			getNextToken(&fp1,buf);
			if(strcmp(buf,")") == 0){  
				getNextToken(&fp1,buf);			
				if(strcmp(buf,"{") == 0){
					declarations();
					statement_list();
					getNextToken(&fp1,buf);
					if(strcmp(buf,"}") != 0) if(error == 0){ error = 12; printf("\nError:%d at %s\n",error,buf); }
				}else if(error == 0){ error = 1; printf("\nError:%d at %s\n",error,buf); }
			}else if(error == 0){ error = 2; printf("\nError:%d at %s\n",error,buf); }
		}else if(error == 0){ error = 3; printf("\nError:%d at %s\n",error,buf); }
	}else if(error == 0){ error = 4; printf("\nError:%d at %s\n",error,buf); }
}

void statement_list(){
	FILE *fp3;
	fp3 = fopen ("input.txt", "r");
	int pos = ftell(fp1);
	fseek(fp3,pos,SEEK_CUR);
	getNextToken(&fp3,buf);
	if(strcmp(buf,"id") == 0 || strcmp(buf,"if") == 0 || strcmp(buf,"while") == 0  || strcmp(buf,"for") == 0){
		statement();
		statement_list();
	}
}

void statement(){
	FILE *fp3;
	fp3 = fopen ("input.txt", "r");
	int pos = ftell(fp1);
	fseek(fp3,pos,SEEK_CUR);
	getNextToken(&fp3,buf);
	if(strcmp(buf,"id") == 0){
		assign_stat();
		getNextToken(&fp1,buf);
		if(strcmp(buf,";") != 0) if(error == 0){ error = 15; printf("\nError:%d at %s\n",error,buf); }
	}else if(strcmp(buf,"if") == 0) decision_stat();
	else if(strcmp(buf,"for") == 0 || strcmp(buf,"while") == 0) looping_stat();
	else if(error == 0){ error = 51; printf("\nError:%d at %s\n",error,buf); }
}

void declarations(){
		FILE *fp3;
		fp3 = fopen ("input.txt", "r");
		int pos = ftell(fp1);
		fseek(fp3,pos,SEEK_CUR);
		getNextToken(&fp3,buf);
		if(strcmp(buf,"int") == 0 || strcmp(buf,"char") == 0){
			datatype();
			identifier_list();
			getNextToken(&fp1,buf);
			if(strcmp(buf,";") == 0){
				declarations();
			}else if(error == 0){ error = 5; printf("\nError:%d at %s\n",error,buf); }
		}
}

void datatype(){
	getNextToken(&fp1,buf);
	if(strcmp(buf,"int") != 0 && strcmp(buf,"char") != 0) if(error == 0){ error = 6; printf("\nError:%d at %s\n",error,buf); }
}

void identifier_list(){
	getNextToken(&fp1,buf);
	if(strcmp(buf,"id") == 0){
		idd1();
	}else if(error == 0){ error = 7; printf("\nError:%d at %s\n",error,buf); }
}

void idd1(){
	FILE *fp3;
	fp3 = fopen ("input.txt", "r");
	int pos = ftell(fp1);
	fseek(fp3,pos,SEEK_CUR);
	getNextToken(&fp3,buf);
	if(strcmp(buf,",") == 0){
		getNextToken(&fp1,buf);
		identifier_list();
	}else if(strcmp(buf,"[") == 0){
		getNextToken(&fp1,buf);
		getNextToken(&fp1,buf);
		if(strcmp(buf,"num") == 0){
			getNextToken(&fp1,buf);
			if(strcmp(buf,"]") == 0){
				idd2();
			}else if(error == 0){ error = 14; printf("\nError:%d at %s\n",error,buf); }
		}else if(error == 0){ error = 15; printf("\nError:%d at %s\n",error,buf); }
	}
}

void idd2(){
	FILE *fp3;
	fp3 = fopen ("input.txt", "r");
	int pos = ftell(fp1);
	fseek(fp3,pos,SEEK_CUR);
	getNextToken(&fp3,buf);
	if(strcmp(buf,",") == 0){
		getNextToken(&fp1,buf);
		identifier_list();
	}
}

void assign_stat(){
	getNextToken(&fp1,buf);
	if(strcmp(buf,"id") == 0){
		getNextToken(&fp1,buf);
		if(strcmp(buf,"=") == 0) expn();
		else if(error == 0){ error = 8; printf("\nError:%d at %s\n",error,buf); }
	}else if(error == 0){ error = 9; printf("\nError:%d at %s\n",error,buf); }
}

void decision_stat(){
	getNextToken(&fp1,buf);
	if(strcmp(buf,"if") == 0){
		getNextToken(&fp1,buf);
		if(strcmp(buf,"(") == 0){
			expn();
			getNextToken(&fp1,buf);
			if(strcmp(buf,")") == 0){
				getNextToken(&fp1,buf);
				if(strcmp(buf,"{") == 0){
					statement_list();
					getNextToken(&fp1,buf);
					if(strcmp(buf,"}") == 0){
						dprime();
					}else if(error == 0){error = 35; printf("\nError:%d at %s\n",error,buf); }	
				}else if(error == 0){error = 34; printf("\nError:%d at %s\n",error,buf); }	
			}else if(error == 0){error = 33; printf("\nError:%d at %s\n",error,buf); }	
		}else if(error == 0){error = 32; printf("\nError:%d at %s\n",error,buf); }
	}else if(error == 0){error = 31; printf("\nError:%d at %s\n",error,buf); }
}

void dprime(){
	FILE *fp3;
	fp3 = fopen ("input.txt", "r");
	int pos = ftell(fp1);
	fseek(fp3,pos,SEEK_CUR);
	getNextToken(&fp3,buf);
	if(strcmp(buf,"else") == 0){
		getNextToken(&fp1,buf);
		getNextToken(&fp1,buf);
		if(strcmp(buf,"{") == 0){
			statement_list();
			getNextToken(&fp1,buf);
			if(strcmp(buf,"}") != 0 && error == 0){ error = 43; printf("\nError:%d at %s\n",error,buf); }
		}else if(error == 0){error = 42; printf("\nError:%d at %s\n",error,buf); }	
	}
}

void looping_stat(){
	FILE *fp3;
	fp3 = fopen ("input.txt", "r");
	int pos = ftell(fp1);
	fseek(fp3,pos,SEEK_CUR);
	getNextToken(&fp3,buf);
	if(strcmp(buf,"for") == 0){
		getNextToken(&fp1,buf);
		getNextToken(&fp1,buf);
		if(strcmp(buf,"(") == 0){
			assign_stat();
			getNextToken(&fp1,buf);
			if(strcmp(buf,";") == 0){
				expn();
				getNextToken(&fp1,buf);
				if(strcmp(buf,";") == 0){
					assign_stat();
					getNextToken(&fp1,buf);
					if(strcmp(buf,")") == 0){
						getNextToken(&fp1,buf);
						if(strcmp(buf,"{") == 0){
							statement_list();
							getNextToken(&fp1,buf);
							if(strcmp(buf,"}") != 0) if(error == 0){error = 74; printf("\nError:%d at %s\n",error,buf);}
						}else if(error == 0){error = 73; printf("\nError:%d at %s\n",error,buf); }	
					}else if(error == 0){error = 72; printf("\nError:%d at %s\n",error,buf); }	
				}else if(error == 0){error = 76; printf("\nError:%d at %s\n",error,buf); }	
			}else if(error == 0){error = 75; printf("\nError:%d at %s\n",error,buf); }	
		}else if(error == 0){error = 71; printf("\nError:%d at %s\n",error,buf); }	
	}else if(strcmp(buf,"while") == 0){
		getNextToken(&fp1,buf);
		getNextToken(&fp1,buf);
		if(strcmp(buf,"(") == 0){
			expn();
			getNextToken(&fp1,buf);
			if(strcmp(buf,")") == 0){
				getNextToken(&fp1,buf);
				if(strcmp(buf,"{") == 0){
					statement_list();
					getNextToken(&fp1,buf);
					if(strcmp(buf,"}") != 0) if(error == 0){error = 65; printf("\nError:%d at %s\n",error,buf);}
				}else if(error == 0){error = 64; printf("\nError:%d at %s\n",error,buf); }	
			}else if(error == 0){error = 63; printf("\nError:%d at %s\n",error,buf); }	
		}else if(error == 0){error = 62; printf("\nError:%d at %s\n",error,buf); }
	}else if(error == 0){ error = 61; printf("\nError:%d at %s\n",error,buf); }
}

void expn(){
	simple_expn();
	eprime();
}

void simple_expn(){
	term();
	seprime();
}

void eprime(){
	FILE *fp3;
	fp3 = fopen ("input.txt", "r");
	int pos = ftell(fp1);
	fseek(fp3,pos,SEEK_CUR);
	getNextToken(&fp3,buf);
	if(strcmp(buf,"==") == 0 || strcmp(buf,"!=") == 0 ||  strcmp(buf,"<=") == 0 ||  strcmp(buf,">=") == 0 || strcmp(buf,">") == 0 || strcmp(buf,"<") == 0){
		relop();
		simple_expn();
	}
}

void seprime(){
	FILE *fp3;
	fp3 = fopen ("input.txt", "r");
	int pos = ftell(fp1);
	fseek(fp3,pos,SEEK_CUR);
	getNextToken(&fp3,buf);
	if(strcmp(buf,"+") == 0 || strcmp(buf,"-") == 0){
		addop();
		term();
		seprime();
	}
}

void term(){
	factor();
	tprime();
}

void tprime(){
	FILE *fp3;
	fp3 = fopen ("input.txt", "r");
	int pos = ftell(fp1);
	fseek(fp3,pos,SEEK_CUR);
	getNextToken(&fp3,buf);
	if(strcmp(buf,"*") == 0 || strcmp(buf,"/") == 0 || strcmp(buf,"%") == 0){
		mulop();
		factor();
		tprime();
	}
}

void factor(){
	getNextToken(&fp1,buf);
	if(strcmp(buf,"id") != 0 && strcmp(buf,"num") != 0) if(error == 0){ error = 15; printf("\nError:%d at %s\n",error,buf); }
}

void relop(){
	getNextToken(&fp1,buf);
	if(!(strcmp(buf,"==") == 0 || strcmp(buf,"!=") == 0 ||  strcmp(buf,"<=") == 0 ||  strcmp(buf,">=") == 0 || strcmp(buf,">") == 0 || strcmp(buf,"<") == 0)) if(error == 0){ error = 16; printf("\nError:%d at %s\n",error,buf); }
}

void addop(){
	getNextToken(&fp1,buf);
	if(strcmp(buf,"+") != 0 && strcmp(buf,"-") != 0) if(error == 0){ error = 17; printf("\nError:%d at %s\n",error,buf); }
}

void mulop(){
	getNextToken(&fp1,buf);
	if(strcmp(buf,"*") != 0 && strcmp(buf,"/") != 0 && strcmp(buf,"%") != 0) if(error == 0){ error = 18; printf("\nError:%d at %s\n",error,buf); }
}

void main()
{
	fp1 = fopen("input.txt","r");
	init();
	/*while(!feof(fp1)){
		getNextToken(&fp1,buf);
		if(feof(fp1)) break;
		printf("%s\n",buf);
	}*/
	Program();
	if(error == 0) printf("Accepted\n");
	else printf("\nRejected\n");
	displaySym();
}