#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include "lex_analyzer.h"


FILE* f1;
struct token tkn;

void prog();
void dec();
void ilist();
void iprime();
void dtype();
void slist();
void s();
void AS();
void expn();
void eprime();
void se();
void seprime();
void t();
void tprime();
void f();
void relop();
void ao();
void mo();
void updatecurrent();


void invalid();
void valid();
void statement();
void looping_stat();
void dprime();
void decision_stat();

void updatecurrent()
{
	tkn=getNextToken(f1);
}

void prog()
{
	updatecurrent();
	if(strcmp(tkn.lexeme,"main")==0)
	{
		updatecurrent();
		if(strcmp(tkn.lexeme,"(")==0)
		{
			updatecurrent();
			if(strcmp(tkn.lexeme,")")==0)
			{
				updatecurrent();
				if(strcmp(tkn.lexeme,"{")==0)
				{
					statement();
					updatecurrent();
					if(strcmp(tkn.lexeme,"}")!=0)
						invalid();
				}
				else
					invalid();
			}
			else
				invalid();
		}
		else
			invalid();
	}
	else
		invalid();
}

void dec()
{
	updatecurrent();
	if(strcmp(tkn.lexeme,"int")==0||strcmp(tkn.lexeme,"char")==0)
	{
		dtype();
		ilist();
		if(strcmp(tkn.lexeme,";")==0)
		{
			dec();
		}
		else
			invalid();
	}
	else
		return;
}

void slist()
{
	if(strcmp(tkn.type,"identifier")==0)
	{
		s();
		if(strcmp(tkn.type,"identifier")==0)
		{
			slist();
		}
	}
	else 
		return;
}

void s()
{
	AS();
	updatecurrent();
	if(strcmp(tkn.lexeme,";")!=0)
		invalid();
}

void AS()
{
	if(strcmp(tkn.type,"identifier")==0)
	{
		updatecurrent();
		if(strcmp(tkn.lexeme,"=")==0)
		{
			expn();
		}
		else
			invalid();
	}
	else 
		invalid();
}

void expn()
{
	se();
	eprime();	
}

void se()
{
	t();
	seprime();
}

void t()
{
	f();
	tprime();
}

void f()
{
	updatecurrent();
	if(strcmp(tkn.type,"identifier")!=0&&strcmp(tkn.type,"number")!=0)
		invalid();
}

void seprime()
{
	if(strcmp(tkn.lexeme,"+")==0||strcmp(tkn.lexeme,"-")==0)
	{
		ao();
		t();
		seprime();
	}
	else
		return;
}

void tprime()
{
	if(strcmp(tkn.lexeme,"*")==0||strcmp(tkn.lexeme,"/")==0||strcmp(tkn.lexeme,"%")==0)
	{
		mo();
		f();
		tprime();
	}
	else
		return;
}

void eprime()
{
	if(strcmp(tkn.lexeme,"==")==0||strcmp(tkn.lexeme,"!=")==0||strcmp(tkn.lexeme,"<=")==0||strcmp(tkn.lexeme,">=")==0||strcmp(tkn.lexeme,"<")==0||strcmp(tkn.lexeme,">")==0)
	{
		relop();
		se();
	}
	else
		return;
}

void relop()
{
	updatecurrent();
	if(strcmp(tkn.lexeme,"==")!=0&&strcmp(tkn.lexeme,"!=")!=0&&strcmp(tkn.lexeme,"<=")!=0&&strcmp(tkn.lexeme,">=")!=0&&strcmp(tkn.lexeme,">")!=0&&strcmp(tkn.lexeme,"<")!=0)
		invalid();
}

void ao()
{
	updatecurrent();
	if(strcmp(tkn.lexeme,"+")!=0&&strcmp(tkn.lexeme,"-")!=0)
		invalid();
}

void mo()
{
	updatecurrent();
	if(strcmp(tkn.lexeme,"*")!=0&&strcmp(tkn.lexeme,"/")!=0&&strcmp(tkn.lexeme,"%")!=0)
		invalid();
}

void dtype()
{
	if(strcmp(tkn.lexeme,"int")!=0&&strcmp(tkn.lexeme,"char")!=0)
		invalid();
}

void ilist()
{
	updatecurrent();
	printf("the  lexeme of the token is: %s and its type is: %s \n",tkn.lexeme, tkn.type );
	if(strcmp(tkn.type,"identifier")!=0)
		invalid();
	iprime();
}

void iprime()
{
	updatecurrent();
	if(strcmp(tkn.lexeme,",")==0)
		ilist();
	else if(strcmp(tkn.lexeme,"[")==0)
	{
		updatecurrent();
		if(strcmp(tkn.lexeme,"num")==0)
		{
			updatecurrent();
			if(strcmp(tkn.lexeme,"]")==0)
			{
				updatecurrent();
				if(strcmp(tkn.lexeme,",")==0)
				{
					ilist();
				}
				else
					return;
			}
			else
				invalid();
		}
		else invalid();
	}
	else 
		return;
}




void invalid(struct token* tkn)
{
	printf("error at row: %d, col: %d for lexeme \" %s \" \n", tkn->row, tkn->col, tkn->lexeme);
	printf("-----------------ERROR!----------------\n");
	exit(0);
}

void valid()
{
	printf("----------------SUCCESS!---------------\n");
	exit(0);
}

void statement()
{
	assign_stat();
	decision_stat();
	looping_stat();
}

void decision_stat()
{
	tkn = getNextToken(f1);
	if(strcmp(tkn.lexeme, "if") == 0)
	{
		tkn = getNextToken(f1);
		if(strcmp(tkn.lexeme, "(") == 0)
		{
			expn();
			tkn = getNextToken(f1);
			if(strcmp(tkn.lexeme, ")"))
			{
				if(strcmp(tkn.lexeme, "{") == 0)
				{
					statement();
					tkn = getNextToken(f1);
					if(strcmp(tkn.lexeme, "}") == 0)
					{
						//dprime();
					}
				}
			}
		}
	}
	else
	{
		return;
	}
}

void assign_stat()
{
	dec();
	ilist();
	AS();
}

void looping_stat()
{
	tkn = getNextToken(f1);
	if(strcmp(tkn.lexeme, "while") == 0 || strcmp(tkn.lexeme, "for") == 0)
	{
		tkn = getNextToken(f1);
		if(strcmp(tkn.lexeme, "(") == 0)
		{
			expn();
			tkn = getNextToken(f1);
			if(strcmp(tkn.lexeme, ")") == 0)
			{
				tkn = getNextToken(f1);
				if(strcmp(tkn.lexeme, "{") == 0)
				{
					statement();
				}
				tkn = getNextToken(f1);
				if(strcmp(tkn.lexeme, "}") == 0)
				{
					return;
				}
			}
		}
	}
}


int main()
{

	//initialize();
	//initialize_list();
	f1 = fopen("op.c","r");
	// now we generate the tokens
	if(f1==NULL)
	{
	  	printf("Error! File cannot be opened!\n");
	  	return 0;
	}

	prog();
	valid();
}