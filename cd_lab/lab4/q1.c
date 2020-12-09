// symbol table program
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define tableLength 30
// define structure of the token
struct token
{
	char lexeme[128];
	int row, col;
	char type[32];
};

//for the symbol table
typedef struct listElement* listPtr; 
struct listElement
{
	struct token tok;
	listPtr next;
};

listPtr TABLE[tableLength];

void initialize()
{
	for(int i = 0; i < tableLength; i++)
	{
		TABLE[i] = NULL;
	}
}

int m = 0;

listPtr createTable(struct token tkn)
{
	return NULL;
}

void addTable(struct token tkn, int c, char* dbuf)
{
	// check whether the token is a variablename
	// then we create a symbol table
	if(c == '(')
	{
		int flag = 0;
		createTable(tkn);
	}
	else
	{
		int a =2;
	}
		
}

int row = 1, col = 1;
char buff[2048];

const char special_symbols[] = {'!', '$', '%', '^', '(',
								')', '{', '}', '[', ']', ';',
								',', '.'};
const char* keywords[] = {"int", "return", "for", "while", "do",
							"else", "case", "break", "unsigned",
							"const"};

const char* datatypes[]  = {"int", "float", "double", "char", "long"};

const char arithmetic_symbols[] = {'*', '/'};

int isKeyword(char* str)
{
	int len = sizeof(keywords) / sizeof(char *); 
	for(int i = 0; i < len; i++)
	{
		if(strcmp(str, keywords[i]) == 0)
		{
			return 1;
		}
	}
	return 0;
}

int charBelongs(int c, const char* arr)
{
	int len;
	if(arr == special_symbols)
	{
		len = sizeof(special_symbols) / sizeof(char);
	}
	else if(arr == arithmetic_symbols)
	{
		len = sizeof(arithmetic_symbols) / sizeof(char);
	}
	
	for(int i = 0; i < len; i++)
	{
		if(c == arr[i])
		{
			return 1;
		}
	}
	return 0;
}


void fillToken(struct token* t, char c, int row, int col, char* type)
{
	t->row = row;
	t->col = col;
	t->lexeme[0] = c;
	t->lexeme[1] = '\0';
	strcpy(t->type, type);
}

struct token getNextToken(FILE *f1)
{

	struct token tkn;
	tkn.row = -1;
	int c, gotToken = 0;
	c = fgetc(f1);
	while(!gotToken && c != EOF)
	{
		//check if character is a special symbol
		//printf("the value of c is: %c \n" , c); 
		
		/*
		if(charBelongs(c, special_symbols))
		{
			
			fillToken(&tkn, c, row, col, "special_sym");
			col++;
			gotToken = 1;
		}
		// check for * and /
		else if(charBelongs(c, arithmetic_symbols))
		{
			fillToken(&tkn, c, row, col, "arithmetic_sym");
			gotToken = 1;
			col++;
		}
		else if(c == '+')
		{
			int n = fgetc(f1);
			if(n != '+')
			{
				fillToken(&tkn, c, row, col, "arithmetic_op");
				gotToken = 1;
				col++;
				fseek(f1, -1, SEEK_CUR);
			}
			else
			{
				fillToken(&tkn, c, row, col, "unary_op");
				strcpy(tkn.lexeme, "++");
				gotToken = 1;
				col += 2;
			}
		}
		else if(c == '-')
		{
			int n = fgetc(f1);
			if(n != '-')
			{
				fillToken(&tkn, c, row, col, "arithmetic_op");
				gotToken = 1;
				col++;
				fseek(f1, -1, SEEK_CUR);
			}
			else
			{
				fillToken(&tkn, c, row, col, "unary_op");
				strcpy(tkn.lexeme, "--");
				gotToken = 1;
				col += 2;
			}
		}
		else if(c == '=')
		{
			int n = fgetc(f1);
			if(n == '=')
			{
				gotToken = 1;
				col += 2;
				fillToken(&tkn, c, row, col, "relational_op");
				strcpy(tkn.lexeme, "==");
			}
			else
			{
				fillToken(&tkn, c, row, col, "assignment_op");
				gotToken = 1;
				col++;
				fseek(f1, -1, SEEK_CUR);
			}
		}
		else if(isdigit(c))
		{
			tkn.row = row;
			tkn.col = col;
			tkn.lexeme[0] = c;
			int pos = 1;
			while((c =fgetc(f1)) != EOF && isdigit(c))
			{
				tkn.lexeme[pos++] = c;
				col++;
			}
			tkn.lexeme[pos] = '\0';
			strcpy(tkn.type, "number");
			gotToken = 1;
			fseek(f1, -1, SEEK_CUR);
		}
		else if(c == '#')
		{
			while((c = fgetc(f1)) != EOF && c != '\n');
			row++;
			col = 1;
		}
		else if(c == '\n')
		{
			row++;
			col = 1;
			c = fgetc(f1);
			if(c == '#')
			{
				while((c = fgetc(f1)) != EOF && c != '\n');
				row++;
				col = 1;
			}
		}
		else if(c == ' ')
		{
			col++;
		}
		
		*/
		if(isalpha(c) || c == '_')
		{
			//printf("here \n");
			tkn.row = row;
			tkn.col = col;
			tkn.lexeme[0] = c;
			int pos = 1;
			c = fgetc(f1);
			//printf("the value of c is: %c \n" , c); 
			while(c != EOF && isalnum(c))
			{
				tkn.lexeme[pos++] = c;
				col++;
				c = fgetc(f1);
			}
			tkn.lexeme[pos] = '\0';
			//printf("the value of lexeme is: %s \n" , tkn.lexeme); 
			if(isKeyword(tkn.lexeme))
			{
				strcpy(tkn.type, "keyword");
			}
			else
			{
				//printf("the value of c is: %c \n" , c); 
				strcpy(tkn.type, "identifier");
			}
			gotToken = 1;
					//printf("here again \n"); 
			fseek(f1, -1, SEEK_CUR);
			//printf("the value of c is: %c \n" , c);
			 
		}
		else
		{
			c = fgetc(f1);
			col++;
		}
		
		/*
		else if(c == '/')
		{
			int n = fgetc(f1);
			if(n == '/')
			{
				while((c = fgetc(f1)) != EOF && c != '\n')
				{
					col++;
				}
				row++;
				col = 1;
			}
			else if(c == '*')
			{
				do
				{
					while(c != '*')
					{
						c = getc(f1);
					}
					c = fgetc(f1);
				}while(c != '/');
			}
			else
			{
				fillToken(&tkn, c, row, col, "arithmetic_op");
				gotToken = 1;
				fseek(f1, -1, SEEK_CUR); 
			}
		}
		else if(c == '"')
		{
			tkn.row = row;
			tkn.col = col;
			tkn.lexeme[0] = c;
			int pos = 1;
			while((c = fgetc(f1)) != EOF && c != '"')
			{
				tkn.lexeme[pos++] = c;
				col++;
			}
			tkn.lexeme[pos++] = c;
			tkn.lexeme[pos] = '\0';
			gotToken = 1;
			strcpy(tkn.type, "string");
		}
		else if(c == '<' || c == '>' || c == '!')
		{
				fillToken(&tkn, c, row, col, "relational_op");
                col++;
                int n = fgetc(f1);
                if(n == '=') 
                {
					col++;
                    strcat(tkn.lexeme, "=");
                } 
                else 
                {
                    if(c == '!')
                      {
                        strcpy(tkn.type, "logical_op");
                      }
                    fseek(f1, -1, SEEK_CUR);
                  }
                gotToken = 1;
               } 
        else if(c == '&' || c == '|') 
        {
                int d = fgetc(f1);
                if(c == d) 
                {
                    tkn.lexeme[0] = tkn.lexeme[1] = c;
                    tkn.lexeme[2] = '\0';
                    tkn.row = row;
                    tkn.col = col; 
                    ++col; 
                    gotToken = 1;
                    strcpy(tkn.type, "LOGICAL OPERATOR");
                } 
                else 
                {
                    fseek(f1, -1, SEEK_CUR);
                }
                col++;
        } 
        else 
        {
            col++;
        }
        c = fgetc(f1);
    }
    //printf("<%s, %d, %d, %s>\n", tkn.lexeme, tkn.row, tkn.col, tkn.type);
    return tkn;
    */
	}
	return tkn;
    
}		
		
int main()
{
	FILE *f1 = fopen("example.c", "r");
	if(f1 == NULL)
	{
		printf(" file opening error \n");
		return 0;
	}
	struct token tkn = getNextToken(f1);
	while(tkn.row != -1)
	{
		
		printf("<%s, %d, %d, %s>\n", tkn.lexeme, tkn.row, tkn.col, tkn.type);
		tkn = getNextToken(f1);
	}
	fclose(f1);
}			
		
	
	

