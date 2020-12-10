// symbol table program
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define tableLength 30
// define structure of the token

int findSize(char* str)
{
	if(strcmp(str, "int") == 0)
	{
		return 4;
	}
	else if(strcmp(str, "char") == 0)
	{
		return 1;
	}
	else if(strcmp(str, "float") == 0)
	{
		return 8;
	}
	else
	{
		return 0;
	}
}

typedef struct token* Tokenptr;
struct token
{
	char lexeme[128];
	int row, col;
	char type[32];
};

//for the symbol table
typedef struct tableName* tableNameptr;
struct tableName
{
	Tokenptr tok;
	Tokenptr list[5];
};

tableNameptr TABLE[tableLength];

void initialize()
{
	for(int i = 0; i < tableLength; i++)
	{
		TABLE[i] = NULL;
	}
}

void initialize2(int num)
{
	for(int i = 0; i < 5; i++)
	{
		TABLE[num]->list[i] = NULL;
	}
}

int m = 0;

void createTable(Tokenptr tkn)
{
			//printf("token lexeme is: %s \n", tkn->lexeme);
	int newTable = false;
	for(int i = 0; i < tableLength; i++)
	{
		if(TABLE[i] == NULL)
		{

			newTable = true;
			break;
		}
		else
		{
			//int
			char* name = TABLE[i]->tok->lexeme;
			if(strcmp(name, tkn->lexeme) == 0)
			{
				//printf("this lexeme is already present as a function\n");
			}
		}
	}

	if(newTable)
	{
				//printf("token lexeme is: %s \n", tkn->lexeme);
		int pos = -1;
		for(int i = 0; i < tableLength; i++)
		{
			if(TABLE[i] == NULL)
			{

				pos = i;
				TABLE[i] = (tableNameptr)malloc(sizeof(struct tableName));
				TABLE[i]->tok = tkn;
				initialize2(i);
				//printf("here inside with pos = %d \n", pos);
				break;
			}
		}
				//printf("token lexeme is: %s \n", tkn->lexeme);
		//tableNameptr newFun;
		//newFun->tok = tkn;
		//printf("token lexeme before is: %s \n", tkn->lexeme);
		//TABLE[pos]->tok = tkn;
		//printf("token lexeme after is: %s \n", TABLE[pos]->tok->lexeme);
	}
}

void browseTable()
{
	//printf("here\n");
	for(int i = 0; i < tableLength; i++)
	{
		if(TABLE[i] == NULL)
		{
			break;
		}
		else
		{
			//printf("here 2\n");
			for(int j = 0; j < 5; j++)
			{
				Tokenptr tp =  TABLE[i]->list[j];
				if(tp == NULL)
				{
					//printf("here 2\n");
					break;
				}
				else
				{

					printf("%s \t %s \t %d \n", tp->lexeme, tp->type, findSize(tp->type));
				}
			}
		}
	}
}
				

// add a new variable to the table
void addTable(Tokenptr tkn, char* dbuf, Tokenptr func_token)
{

	// first we find the pointer to the  correct table
	int pos = 0;
	for(int i = 0; i < tableLength; i++)
	{
		if(strcmp(TABLE[i]->tok->lexeme, func_token->lexeme) == 0)
		{
			pos = i;
			break;
		}
	}

	for(int j = 0; j < 5; j++)
	{
		if(TABLE[pos]->list[j] != NULL)
		{
						//printf("here 2\n");
			if(strcmp(TABLE[pos]->list[j]->lexeme,tkn->lexeme) == 0)
			{
				//printf("already present in the table \n");
				break;
			}
		}
		if(TABLE[pos]->list[j] == NULL)
		{

			TABLE[pos]->list[j] = (Tokenptr)malloc(sizeof(struct token));
			TABLE[pos]->list[j] = tkn;
			break;
		}
	}

	//printf("%s is a variablename of type %s \n", tkn->lexeme, dbuf);
}

int isIPfunction(char* str)
{
	if((strcmp(str,"printf") == 0) || (strcmp(str, "scanf") == 0))
	{
		return 1;
	}
	return 0;
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

int isDatatype(char* str)
{
	int len = sizeof(datatypes) / sizeof(char *); 
	for(int i = 0; i < len; i++)
	{
		if(strcmp(str, datatypes[i]) == 0)
		{
			return 1;
		}
	}
	return 0;
}

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


struct token checkforalpha(FILE* f1)
{
	token tkn;
	int pos = 0;
	char c = fgetc(f1);
	char dbuf[32];
	int gotToken = 1;

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

	int isDT = 0;
	if(isDatatype(tkn.lexeme))
	{
		int len = sizeof(datatypes) / sizeof(char *); 
		for(int i = 0; i < len; i++)
		{
			if(strcmp(tkn.lexeme, datatypes[i]) == 0)
			{
				isDT = 1;
				//strcpy
				strcpy(dbuf, datatypes[i]);
				strcpy(tkn.type, datatypes[i]);
				break;
			}
		}
	}
	return tkn;
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
	char dbuf[32];
	char buf[32];
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
		*/
		if(c == '#')
		{
			while((c = fgetc(f1)) != EOF && c != '\n');
			row++;
			col = 1;
		}

		/*
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
		
		else if(isalpha(c) || c == '_')
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

			int isDT = 0;
			if(isDatatype(tkn.lexeme))
			{
				int len = sizeof(datatypes) / sizeof(char *); 
				for(int i = 0; i < len; i++)
				{
					if(strcmp(tkn.lexeme, datatypes[i]) == 0)
					{
						isDT = 1;
						//strcpy
						strcpy(dbuf, datatypes[i]);
						break;
					}
				}
			}

			c = fgetc(f1);
			
			// if the lexeme is a function
			if(!isIPfunction(tkn.lexeme) && c == '(' )
			{
				Tokenptr t = &tkn;
				createTable(t);

				//printf("token pointing to %s \n", t->lexeme);
				// check for closing brackets
				char* parameter_type;
				int param = false;
				while(c != EOF && c != ')')
				{
					token newtkn = checkforalpha(f1);
					if(strcmp(newtkn.lexeme, " ") != 0 && strcmp(newtkn.lexeme, "int") != 0)
					{
						//printf("%s \t %s \t %d \n", newtkn.lexeme, dbuf, findSize(newtkn.type));
						strcpy(newtkn.type, dbuf);
						//printf("newtkn is %s  and type is %s\n", newtkn.lexeme, dbuf);
						addTable(&newtkn, dbuf, t);
					}
					c = fgetc(f1);
					/*
					if(strcmp(newtkn.type, "identifier") == 0)
					{
						if(param)
						{
							addTable(&newtkn, parameter_type, &newtkn);
						}
						else
						{
							strcpy(dbuf, "int");
							addTable(&newtkn, dbuf, &newtkn);
						}
					}
					else
					{
						strcpy(parameter_type, newtkn.type);
						param = true;

					}
					c = fgetc(f1);
					*/
				}

				if(c == '{')
				{
					while(c != EOF && c != '}')
					{
						printf("done \n");
						c = fgetc(f1);
					}
				}
				//printf("lexeme %s is a function \n", tkn.lexeme);

			}
			 
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
		*/
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
		else
		{
			c = fgetc(f1);
			col++;
		}

		/*
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
	initialize();
	FILE *f1 = fopen("example.c", "r");
	if(f1 == NULL)
	{
		printf(" file opening error \n");
		return 0;
	}
	struct token tkn = getNextToken(f1);
	while(tkn.row != -1)
	{
		
		//printf("<%s, %d, %d, %s>\n", tkn.lexeme, tkn.row, tkn.col, tkn.type);
		tkn = getNextToken(f1);
	}
    browseTable();
	fclose(f1);
}			
		
	
	

