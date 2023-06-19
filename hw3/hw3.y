%code requires {
   #include "token.h"
}

%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "SymbolTable.h"
#include "SymbolDesc.h"

#define Trace(t)        printf(t)
extern FILE *yyin;
int yylex(void);
extern "C"
{
    int yyparse(void);
    int yywrap()
    {
        return 1;
    }
}

void yyerror(char *s);
FILE *output;
Hash *idtab, *current_idtab;
bool has_error = false;
int varList[255]={-1};
int size = 0;
int LabelIndex = 0;
std::string ClassName;
int hasMain = 0;
int hasProgram = 0;
int loop_number = 0;
std::vector<int> exitLabels = std::vector<int>(255, -1);
int if_number = 0;
std::vector<int> ifLabels = std::vector<int>(255, -1);

union uDependency{
	int low;
	int high;
	int baseType;
	int retType;
	int argType;
	
	int _int;
	bool _bool;
	double _real;
	char * _str;
	void * value;
};

struct SymbolDesc
{
    int symtype = vunknown;
    bool readonly = false;
    bool global = false;
    bool hasValue = false;
	bool returnByFun = false;
    int iValue;
    char * sValue;
    bool bValue;
    std::vector<uDependency> symdeps;
    int symindex;
};

// class variable{
// public:

// 	std::string type;
// }


// class Layer{
// public:
// 	std::vector<variable> varList;
// }

// std::vector<Layer> scope;
// int number_scope = 0;

char* SymType2Str(int type){
	switch(type){
	case sinteger :
		return "int";
	case sreal :
		return "float";
	case sboolean :
		return "bool";
	case sstring :
		return "java.lang.String";
	case none :
		return "void";
	default:
		return "unknown";
	}
}
std::string SymType2JBStr(int type){
	switch(type){
	case sinteger :
		return "int";
	case sreal :
		return "float";
	case sboolean :
		return "bool";
	case sstring :
		return "java.lang.String";
	case sarray :
		return "array";
	case sfunction :
		return "function";
	case sprocedure :
		return "procedure";
	case none :
		return "void";
	default:
		return "unknown";
	}
}


int Symbol2Token(int symbol){
	switch(symbol){
		case SymbolType::sinteger:
			return  TokenType::vint;
		break;
		case SymbolType::sreal:
			return  TokenType::vreal;
		break;
		case SymbolType::sstring:
			return  TokenType::vstring;
		break;
		case SymbolType::sboolean:
			return  TokenType::vbool;
		break;
		case SymbolType::none:
			return TokenType::blank;
		break;
		default:
			return TokenType::vunknown;
		break;
	}
}

int Token2Symbol(int token){
	switch(token){
		case vint:
			return sinteger;
		break;
		case vreal : 
			return sreal;
		break;
		case vstring :
			return sstring;
		break;
		case vbool :
			return sboolean;
		break;
		case blank:
			return none;
		break;
		default:
			return sunknown;
		break;
	}
}

std::vector<std::map<std::string,SymbolDesc>> SymTableStack;
std::vector<int> SymTableIndexStack;
std::vector<int> SCOPERET;

void InitialTableStack(){
	SymTableStack.push_back(std::map<std::string,SymbolDesc>());
	SymTableIndexStack.push_back(0);
}

void ENTERSCOPE(){
	SymTableStack.push_back(std::map<std::string,SymbolDesc>());
	SymTableIndexStack.push_back(0);
	//number_scope++;
	//scope.push_back(
}

void LEAVESCOPE(){
	SymTableStack.pop_back();
	SymTableIndexStack.pop_back();
}


int GETSCOPERETURN(){
	if(SCOPERET.size()==0){
		return SymbolType::none;
	}
	else {
		return SCOPERET.back();
	}
}



bool seize(std::string id,SymbolDesc *& sd){
	for(int i = SymTableStack.size() - 1 ; i>=0;--i){
		if(SymTableStack[i].count(id)){
			sd = &(SymTableStack[i][id]);
			return true;
		}
	}
	return false;
}

bool seize(std::string id,SymbolDesc & sd){
	for(int i = SymTableStack.size() - 1 ; i>=0;--i){
		if(SymTableStack[i].count(id)){
			sd = (SymTableStack[i][id]);
			return true;
		}
	}
	return false;
}

bool inScope(std::string id){
	if(SymTableStack.back().count(id)){
		return true;
	}
	return false;
}

bool insert(std::string id,SymbolDesc& sd){
	if(inScope(id)){
		return false;
	}
	if(sd.symtype <= SymbolType::sarray){
		//Variable IDs
		if(!sd.readonly){
			//Non Constant Variable IDs
			if(SymTableStack.size()==1){
				//Global Non Constant Variable IDs
				sd.global = true;
				fprintf(output, "\tfield static %s %s", SymType2JBStr(sd.symtype).c_str(), id.c_str());
                                if(sd.hasValue){
                                        if(sd.symtype == sinteger){
                                                fprintf(output, " = %d", sd.iValue);
                                        }else if(sd.symtype == sboolean){
                                                if(sd.bValue){
                                                        fprintf(output, " = true");
                                                }else{
                                                        fprintf(output, " = false");
                                                }
                                        }else if(sd.symtype == sstring){
                                                fprintf(output, " = %s", sd.sValue);
                                        }else if(sd.symtype == sreal){
                                                fprintf(output, " = %d", sd.iValue);
                                        }
                                }
                                fprintf(output, "\n");
			}
			else{
				//Local Non Constan Variable IDs
				sd.symindex = (SymTableIndexStack.back())++;
				if(sd.hasValue){
					if(!sd.returnByFun){
						if(sd.symtype == sinteger){
							// printf("...%s %d...", id.c_str(), sd.iValue);
							fprintf(output, "sipush %d\n", sd.iValue);
						}else if(sd.symtype == sboolean){
							if(sd.bValue){
								fprintf(output, "iconst_1\n");
							}
							else {
								fprintf(output, "iconst_0\n");
							}
						}else if(sd.symtype == sstring){
							fprintf(output, "\t\tldc %s\n", sd.sValue);
						}else if(sd.symtype == sreal){
							fprintf(output, "sipush %d\n", sd.iValue);
						}
					}
					
				}else{
					if(!sd.returnByFun){
						if(sd.symtype == sinteger){
							fprintf(output, "sipush %d\n", 0);
						}else if(sd.symtype == sboolean){
							fprintf(output, "iconst_1\n");
						}else if(sd.symtype == sstring){
							fprintf(output, "\t\tldc %s\n", "");
						}else if(sd.symtype == sreal){
							fprintf(output, "sipush %d\n", 0);
						}
					}
				}
				switch(sd.symtype){
					case SymbolType::sinteger:
						fprintf(output, "istore %d\n",  sd.symindex);
						break;
					case SymbolType::sreal:
						fprintf(output, "fstore  %d\n", sd.symindex);
						break;
					case SymbolType::sstring:
						fprintf(output, "astore  %d\n", sd.symindex);
						break;	
				}	
			}
		}
	}
	else{
		//Unknown,Function,Procedure IDs
	}
	SymTableStack.back()[id] = sd;
	return true;
}

bool insert(std::vector<std::string> list,SymbolDesc& sd){
	bool success = true;
	for(int i = 0 ; i < list.size() ; ++i){
		insert(list[i],sd);
	}
	return success;
}

bool insert(std::string id,SymbolDesc& sd,int scope){
	std::map<std::string,SymbolDesc> & EarlyScope =   SymTableStack[SymTableStack.size()-1-scope];
	int & EarlySymIndex = SymTableIndexStack[SymTableIndexStack.size()-scope];
	if(EarlyScope.count(id)){
		return false;
	}
	if(sd.symtype <= SymbolType::sarray){
		//Variable IDs
		if(!sd.readonly){
			//Non Constant Variable IDs
			if(SymTableStack.size() - scope == 1){
				//Global Non Constant Variable IDs
				sd.global = true;
				fprintf(output, "field static %s %s\n", SymType2JBStr(sd.symtype).c_str(), id.c_str());
			}
			else{
				//Local Non Constan Variable IDs
				sd.symindex = EarlySymIndex++;
				// switch(sd.symtype){
				// 	case SymbolType::sinteger:
				// 	fprintf(output, "istore %d\n",  sd.symindex);
				// 	break;
				// 	case SymbolType::sreal:
				// 	fprintf(output, "fstore  %d\n", sd.symindex);
				// 	break;
				// 	case SymbolType::sstring:
				// 	fprintf(output, "astore  %d\n", sd.symindex);
				// 	break;
				// }		
			}
		}
	}
	else{
		//Unknown,Function,Procedure IDs
	}
	EarlyScope[id] = sd;
	return true;
}

bool insertArg(std::string id,SymbolDesc& sd){
	if(inScope(id)){
		return false;
	}
	sd.symindex = (SymTableIndexStack.back())++;
	SymTableStack.back()[id] = sd;
	return true;
}

void insertList(int type){
        varList[size++] = type;
}

void resetList(){
        int i = 0;
        for(i;i<255;i++){
                varList[i] = -1;
        }
}

// void printList(){
// 	for(auto it = varList
// }

bool matchArgs(std::vector<int>& list,SymbolDesc & sd){
	if(list.size()  != sd.symdeps.size() - 1){
		return false;
	}
	else{
		for(int i = 0; i < list.size();++i){
			if(list[i] !=sd.symdeps[i+1].argType) return false;
		}	
	}
	return true;
}

// ast_node_t* n(ast_node_type_t t, YYLTYPE l) { return new_ast_node(t, l.first_line, l.first_column); }
// void vid(ast_node_t *n, LinkedList *v) { if (v) ast_node_set_value_identifier(n, v); }
// void vopt(ast_node_t *n, int v) { ast_node_set_value_operatr(n, v); }
// void vint(ast_node_t *n, int v) { ast_node_set_value_integer(n, v); }
// void vstr(ast_node_t *n, char *v) { ast_node_set_value_string(n, v); }
// void ich(ast_node_t *n, ast_node_t *child) { ast_node_insert_child(n, child); }
// void isb(ast_node_t *n, ast_node_t *sibling) { ast_node_insert_sibling(n, sibling); }
// void esp(LinkedList *sid) { current_idtab = idtab_entry_idtab_create(current_idtab, sid); }
// void lsp() { if (current_idtab->upper_idtab) current_idtab = current_idtab->upper_idtab; }
%}

%union {
    Token                    token;
}

%start program

%token DE ME SE AE NE EQ GE LE ASSIGN AND OR NOT

%left '>' '<' LE EQ GE NE

%left '+' '-'
%left '*' '/' MOD
%left UMINUS

%nonassoc LOWER_THAN_ELSE
%token ELSE
%nonassoc ELSE

%token BREAK CHAR CASE CLASS CONTINUE DECLARE DO IF EXIT FOR FUNCTION LOOP PRINT PRINTLN RETURN VAR REAL ARRAY OF END PROCEDURE CONST CBEGIN PUT GET RESULT WHEN SKIP THEN DEFAULT DECREASING IN
%token <token> TRUE
%token <token> FALSE


%type <token> boolean
%type <token> type returnType argument arguments
%type <token> expression declaration_value integer_expression bool_expresssion comparison expression_list
%token <token> str id
%token <token> integer
%token <token> real
%token <token> KW_STRING INT FLOAT BOOL

%%
program:	{
				fprintf(output, "class %s {\n", ClassName.c_str());
				resetList();
			}
			body
			{

				if(!hasMain){
					hasMain = 1;
					hasProgram = 1;
					ENTERSCOPE();
					SymbolDesc * sd = new SymbolDesc();
					sd->symtype = SymbolType::sfunction;
					uDependency dep;
					dep.retType = SymbolType::none;
					sd->symdeps.push_back(dep);
					SCOPERET.push_back(dep.retType);

					// 產生 main 函式
					fprintf(output, "\tmethod public static ");
					fprintf(output, "%s ", SymType2Str(SymbolType::none));
					fprintf(output, "%s", "main");
					fprintf(output, "(");
					fprintf(output, "java.lang.String[])\n");
					fprintf(output, "\tmax_stack 15\n\tmax_locals 15\n");
					insert("main",*sd,1);
					fprintf(output, "\t{\n");

					
					$<token>$._ptr = sd;
					sd->returnByFun = false;
				}
				else{
					// 什麼都不做
				}
				if(!hasProgram){
					fprintf(output, "\tmethod public static void main(java.lang.String[])\n");
					fprintf(output, "\tmax_stack 15\n");
					fprintf(output, "\tmax_locals 15\n");
					fprintf(output, "\t{\n");
				}else{
					// 什麼都不做
				}
				fprintf(output, "\t\treturn\n");
				fprintf(output, "\t}\n");
				fprintf(output, "}\n");
			};
// hasProgram == 1 代表此檔案有程式，不是空檔案
body:  	body declaration	{
							if(!hasProgram)
								hasProgram = 1;
						}
        | body function	{
							if(!hasProgram)
								hasProgram = 1;
						}
        | body procedure{
							if(!hasProgram)
								hasProgram = 1;
						}
        | body {
				// hasMain == 1 代表已經有 main 函式了
				if(!hasMain){
					hasMain = 1;

					ENTERSCOPE();
					SymbolDesc * sd = new SymbolDesc();
					sd->symtype = SymbolType::sfunction;
					uDependency dep;
					dep.retType = SymbolType::none;
					sd->symdeps.push_back(dep);
					SCOPERET.push_back(dep.retType);

					// 產生 main 函式
					fprintf(output, "\tmethod public static ");
					fprintf(output, "%s ", SymType2Str(SymbolType::none));
					fprintf(output, "%s", "main");
					fprintf(output, "(");
					fprintf(output, "java.lang.String[])\n");
					fprintf(output, "\tmax_stack 15\n\tmax_locals 15\n");
					insert("main",*sd,1);
					fprintf(output, "\t{\n");

					
					$<token>$._ptr = sd;
					sd->returnByFun = false;
				}
				else{
					// 什麼都不做
				}
		}		
		statement{
							if(!hasProgram)
								hasProgram = 1;
						}
		|
        ;


fd:     END id
        |
        ;

function:       FUNCTION id {
                    ENTERSCOPE();
                }
				 '(' arguments ')' returnType{

					SymbolDesc * sd = new SymbolDesc();	
					std::vector<int> * varlist2 =(std::vector<int> *)$5._ptr;
					SymbolDesc * retype = (SymbolDesc*)$7._ptr; 
					sd->symtype = SymbolType::sfunction;
					uDependency dep;
					dep.retType = $7.type;
					// printf("<%d>", dep.retType);
					sd->symdeps.push_back(dep);
					SCOPERET.push_back(dep.retType);
					fprintf(output, "\tmethod public static ");
					fprintf(output, "%s ", SymType2Str($7.type));
					fprintf(output, "%s", $2._str);
					fprintf(output, "(");
					if(strcmp($2._str, "main") != 0){
							// if(varList != NULL){
							//         int i = 0;
							//         for(i;i<255 && varList[i]!=-1;i++){
							//                 if(i!=0){
							//                         fprintf(output, ", ");
							//                 }
							//                 fprintf(output, "%s", SymType2Str(varList[i]));
							//         }
							// }
							if(varlist2 != nullptr) {
								for(int i = 0 , j = varlist2->size() ;  i < j; ++i){
									dep.argType = (*varlist2)[i];
									sd->symdeps.push_back(dep);
									if(i!=0){
										fprintf(output, ", ");
									}
									fprintf(output, "%s", SymType2Str((*varlist2)[i]));
								}
							}
							fprintf(output, ")\n");
							resetList();
					}else{
							fprintf(output, "java.lang.String[])\n");  
							//fprintf(output, ""); 
					}
					$<token>$._ptr = sd;
					fprintf(output, "\tmax_stack 15\n\tmax_locals 15\n");
					delete varlist2,retype;
					sd->returnByFun = false;
					insert(std::string($2._str),*sd,1);	
					fprintf(output, "\t{\n");
					delete sd;
                }
				 statements fun_re statements fd	{
					fprintf(output, "\t}\n");
					LEAVESCOPE();
                 }
                ;

fun_re:	return
		| condition_r
		;

// no return
procedure:  PROCEDURE id {
            	            ENTERSCOPE();
            }
        	'(' arguments ')'{
						// ENTERSCOPE();
						SymbolDesc * sd = new SymbolDesc();	
						std::vector<int> * varlist2 =(std::vector<int> *)$5._ptr;
						sd->symtype = SymbolType::sprocedure;
						uDependency dep;
						dep.retType = SymbolType::none;
						sd->symdeps.push_back(dep);
                        fprintf(output, "\tmethod public static ");
						fprintf(output, "%s ", SymType2Str(SymbolType::none));
                        fprintf(output, "%s", $2._str);
                        fprintf(output, "(");
                        if(strcmp($2._str, "main") != 0){
								if(varlist2 != nullptr) {
									for(int i = 0 , j = varlist2->size() ;  i < j; ++i){
										dep.argType = (*varlist2)[i];
										sd->symdeps.push_back(dep);
										if(i!=0){
                                            fprintf(output, ", ");
                                        }
										fprintf(output, "%s", SymType2Str((*varlist2)[i]));
									}
								}
                                fprintf(output, ")\n");
                                resetList();
                        }else{ 
                                // printf("procedure 名稱 不能為 main\n"); 
                        }
						$<token>$._ptr = sd;
                        fprintf(output, "\tmax_stack 15\n\tmax_locals 15\n");
						delete varlist2;
						sd->returnByFun = false;
						sd->returnByFun = false;
						insert(std::string($2._str),*sd,1);	
						fprintf(output, "\t{\n");
						delete sd;
                }
                 statements fd	{
								fprintf(output, "\t\treturn\n");
								fprintf(output, "\t}\n");
								LEAVESCOPE();
                 }
                ;

arguments: arguments argument{
				SymbolDesc sd;
				uDependency value;
                // int i = 0;
                // for(i;i<255 && varList[i]!=-1;i++){
                //         printf("%d", varList[i]);
                // }
				sd.symtype = Token2Symbol($2.type);
				value.value = $2._ptr;
                                
				sd.symdeps.push_back(value);
				//printf("");
				insertArg($2._str, sd);
				$$ = $1;
				//printf("%d", sd.symtype);
				$$.type = TokenType::typeList;
				((std::vector<int>*)$$._ptr)->push_back(sd.symtype);
                //insertList($2.type);
        }
            |/*empty*/{
				$$.type = TokenType::typeList;
				$$._ptr = new std::vector<int>();
			}
            ;
/* arguments: argument arguments{
				SymbolDesc sd;
				uDependency value;
                int i = 0;
                for(i;i<255 && varList[i]!=-1;i++){
                        // printf("%d", varList[i]);
                }
				sd.symtype = Token2Symbol($1.type);
				value.value = $1._ptr;
                                
				sd.symdeps.push_back(value);
				insert($1._str, sd);
                insertList($1.type);
        }
            |
            ; */
/* 
arguments: argument
		|  arguments argument
		; */

argument: id ':' type  seperator{
        $$ = $1;
		$$.type = $3.type;
};

seperator: ','
            |/*empty*/
            ;

returnType:':' type{
                $$.type = $2.type;
            }
            ;

statements:/*empty*/
    | statement statements
    ;

statements_r:   /*empty*/
                | statement_r statements_r
                ;

type:   KW_STRING  {$$.type = sstring;}
        | INT   {$$.type = sinteger;}
        | BOOL  {$$.type = sboolean;}
        | FLOAT {$$.type = sreal;}
        ;

statement_tmp: declaration
        | block
        | loop
		| expression
        | id ASSIGN expression{
			SymbolDesc * pSD;
			if(seize(std::string($1._str),pSD)){
				if(pSD->readonly){
					//Error("Assignment to Readonly Variable!");
				}
				else if(pSD->symtype != Token2Symbol($3.type)){
					//Error("Type Unmatch");
				}
				else {
					if(pSD->global){
						fprintf(output, "putstatic %s %s.%s\n", SymType2JBStr(pSD->symtype).c_str(), ClassName.c_str(), $1._str);
					}
					else{
						switch(pSD->symtype){
							case SymbolType::sinteger:
							fprintf(output, "istore %d\n",  pSD->symindex);
							break;
							case SymbolType::sreal:
							fprintf(output, "fstore  %d\n", pSD->symindex);
							break;
							case SymbolType::sstring:
							fprintf(output, "astore  %d\n", pSD->symindex);
							break;
						}
					}
				}
			}
		}
        | GET id
        | PUT {
                fprintf(output, "\t\tgetstatic java.io.PrintStream java.lang.System.out\n");
        } expression{
                fprintf(output, "\t\tinvokevirtual void java.io.PrintStream.print(");
                switch($3.type){
		case vint:
			fprintf(output, "int");
			break;
		case vreal:
			fprintf(output, "float");
			break;
		case vbool:
			fprintf(output, "boolean");
			break;
		case vstring:
			fprintf(output, "java.lang.String");
			break;
		case blank:
			fprintf(output, "void");
		default:
			break;
		}
                fprintf(output, ")\n");
        }
        | PRINTLN {
                fprintf(output, "\t\tgetstatic java.io.PrintStream java.lang.System.out\n");
        }expression{
                fprintf(output, "\t\tinvokevirtual void java.io.PrintStream.println(");
                switch($3.type){
		case vint:
			fprintf(output, "int");
			break;
		case vreal:
			fprintf(output, "float");
			break;
		case vbool:
			fprintf(output, "boolean");
			break;
		case vstring:
			fprintf(output, "java.lang.String");
			break;
		case blank:
			fprintf(output, "void");
		default:
			break;
		}
                fprintf(output, ")\n");
        }
        | SKIP{
			fprintf(output, "getstatic java.io.PrintStream java.lang.System.out\n");
			fprintf(output, "invokevirtual void java.io.PrintStream.println()\n");
		}
        | EXIT exit_optional{
			
			//fprintf(output, "goto L%d\n", LabelIndex - 4);
			//fprintf(output, "goto L%d\n", $<token>2._int - 1);
		}
        ;



// _r 代表包含return，沒有則不含
statement_r:    statement_tmp
                | condition_r
                | return
                ;

statement:      statement_tmp
                | condition
                ;

return: RESULT expression	{
								fprintf(output, "\t\t");

								// 判斷 回傳型態
								// 選擇 不同型態 的 return
								switch($2.type){
								// int
								case SymbolType::sinteger:
								fprintf(output, "ireturn\n");
								break;
								// double
								case SymbolType::sreal:
								fprintf(output, "dreturn\n");
								break;
								// string
								case SymbolType::sstring:
								fprintf(output, "areturn\n");
								break;
								// array
								case SymbolType::sarray:
								fprintf(output, "areturn\n");
								break;
								// 其他
								default:
								fprintf(output, "ireturn\n");
								break;
							}
							}
		| RETURN			{
								fprintf(output, "\t\t");
								fprintf(output, "return\n");
							}
        ;

exit_optional: WHEN expression{
					if(exitLabels[loop_number - 1] == -1){
						exitLabels[loop_number - 1] = LabelIndex;
					}
					fprintf(output, "ifne L%d\n", LabelIndex++);

				}
                |
                ;


declaration_value: integer_expression{
					$$.returnByFun = false;
				}
            | '(' expression ')'{
                $$ = $2;
            }
            | id '(' expression_list ')'{
				SymbolDesc * pSD;
				$$.returnByFun = true;
				std::string idName = std::string($1._str);
				delete $1._str;

				if(seize(idName,pSD)){
					std::vector<int> * list = (std::vector<int>*)$3._ptr;
					if(pSD->symtype != SymbolType::sfunction){
						//Error(id + ": Is not a Function");
					}
					else if(!matchArgs(*list,*pSD)){
						//Error("Argument type Unmatch");
					}
					else{
						fprintf(output, "invokestatic %s %s.%s(", SymType2JBStr(pSD->symdeps[0].retType).c_str(), ClassName.c_str(), idName.c_str());
						for(int i = 0 ; i < list->size();++i ){
							fprintf(output, "%s", SymType2JBStr((*list)[i]).c_str());
							if(i != list->size()-1){
								fprintf(output, ", ");
							}
						}
						fprintf(output, ")\n");

						$$.type = Symbol2Token(pSD->symdeps[0].retType);
						//$$.type = SymbolType::sfunction;
						delete list;
					}
				}
				else {
					$$.type = TokenType::blank;
				}
			}
            | bool_expresssion{
				$$.returnByFun = false;
			}
            | comparison
            | id{
                SymbolDesc * pSD;
				$$.returnByFun = false;
				if(seize(std::string($1._str),pSD)){
					$$.type = Symbol2Token(pSD->symtype);
					
					if(pSD->readonly){
						switch(pSD->symtype){
							case SymbolType::sinteger:
							fprintf(output, "sipush %d\n", pSD->symdeps[0]._int);
							$$.type = TokenType::vint;
							break;
							case SymbolType::sboolean:
							if(pSD->symdeps[0]._bool){
								fprintf(output, "iconst_1\n");
							}
							else {
								fprintf(output, "iconst_0\n");
							}
							$$.type = TokenType::vbool;
							break;
							case SymbolType::sstring:
							fprintf(output, "ldc %s\n", pSD->symdeps[0]._str);
							$$.type = TokenType::vstring;
							break;
							case SymbolType::sreal:
							fprintf(output, "ldc %sf\n", pSD->symdeps[0]._real);
							break;
							default:
							break;

						}
					}
					else {
						//If ID is a Variable.
						if(pSD->global){
							//If ID is global variable.
							fprintf(output, "getstatic");
							switch(pSD->symtype){
								case SymbolType::sinteger:
								fprintf(output, " int ");
								$$.type = TokenType::vint;
								break;
								case SymbolType::sreal:
								fprintf(output, " float ");
								$$.type = TokenType::vreal;
								break;
								case SymbolType::sstring:
								fprintf(output, " java.lang.String ");
								$$.type = TokenType::vstring;
								break;
								/*case SymbolType::boolean:
								jbfile << " boolean ";
								$$.type = TokenType::vbool;
								break;
								case SymbolType::array:
								jbfile << " array ";
								$$.type = TokenType::varray;
								break;*/
								default:
								break;
							}
							fprintf(output, "%s.%s\n", ClassName.c_str(), $1._str);
						}
						else{
							//If ID is local variable.
							switch(pSD->symtype){
								case SymbolType::sinteger:
								fprintf(output, "iload %d\n", pSD->symindex);
								$$.type = TokenType::vint;
								break;
								case SymbolType::sreal:
								fprintf(output, "fload %d\n", pSD->symindex);
								$$.type = TokenType::vreal;
								break;
								case SymbolType::sstring:
								fprintf(output, "aload %d\n", pSD->symindex);
								$$.type = TokenType::vstring;
								break;
								/*case SymbolType::boolean:
								jbfile << "cload " << <<endl;
								break;
								case SymbolType::std::string:
								jbfile << "sload " << <<endl;
								break;
								case SymbolType::array:
								jbfile << "aload " << <<endl;
								break;*/
								default:
								break;
							}
						}
					}
				}
				else {
				}
				delete $1._str;
            }
            | integer {
                $$ = $1;
                $$.type = vint;
				$$.returnByFun = false;
                //fprintf(output, "sipush %d\n", $1._int);
            }
            | str {
                $$ = $1;
                $$.type = vstring;
				$$.returnByFun = false;
                //fprintf(output, "\t\tldc %s\n", $1._str);
            }
            | boolean {
                $$ = $1;
                $$.type = vbool;
				$$.returnByFun = false;
                //fprintf(output, "ldc %s\n", $1);
            }
            | real {
                $$ = $1;
                $$.type = vreal;
				$$.returnByFun = false;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
                //fprintf(output, "ldc %s\n", $1);
            }
            ;


expression: integer_expression{
				$$.returnByFun = false;
			}
            | '(' expression ')'{
                $$ = $2;
            }
            | id '(' expression_list ')'{
				SymbolDesc * pSD;
				std::string idName = std::string($1._str);
				delete $1._str;

				if(seize(idName,pSD)){
					std::vector<int> * list = (std::vector<int>*)$3._ptr;
					if((pSD->symtype != SymbolType::sfunction) && (pSD->symtype != SymbolType::sprocedure)){
						// printf("%s: Is not a Function", idName);
					}
					else if(!matchArgs(*list,*pSD)){
						// printf("Argument type Unmatch");
					}
					else{
						fprintf(output, "invokestatic %s %s.%s(", SymType2JBStr(pSD->symdeps[0].retType).c_str(), ClassName.c_str(), idName.c_str());
						for(int i = 0 ; i < list->size();++i ){
							fprintf(output, "%s", SymType2JBStr((*list)[i]).c_str());
							if(i != list->size()-1){
								fprintf(output, ", ");
							}
						}
						fprintf(output, ")\n");

						$$.type = Symbol2Token(pSD->symdeps[0].retType);
						$$.returnByFun = true;
						//$$.type = SymbolType::sfunction;
						delete list;
					}
				}
				else {
					$$.type = TokenType::blank;
				}
				delete pSD;
			}
            | bool_expresssion{
				$$.returnByFun = false;
			}
            | comparison{
				$$.returnByFun = false;
			}
            | id{
                SymbolDesc * pSD;
				$$.returnByFun = false;
				if(seize(std::string($1._str),pSD)){
					$$.type = Symbol2Token(pSD->symtype);
					if(pSD->readonly){
						switch(pSD->symtype){
							case SymbolType::sinteger:
							fprintf(output, "sipush %d\n", pSD->symdeps[0]._int);
							$$.type = TokenType::vint;
							break;
							case SymbolType::sboolean:
							if(pSD->symdeps[0]._bool){
								fprintf(output, "iconst_1\n");
							}
							else {
								fprintf(output, "iconst_0\n");
							}
							$$.type = TokenType::vbool;
							break;
							case SymbolType::sstring:
							fprintf(output, "ldc %s\n", pSD->symdeps[0]._str);
							$$.type = TokenType::vstring;
							break;
							case SymbolType::sreal:
							fprintf(output, "ldc %sf\n", pSD->symdeps[0]._real);
							break;
							default:
							break;

						}
					}
					else {
						//If ID is a Variable.
						if(pSD->global){
							//If ID is global variable.
							fprintf(output, "getstatic");
							switch(pSD->symtype){
								case SymbolType::sinteger:
								fprintf(output, " int ");
								$$.type = TokenType::vint;
								break;
								case SymbolType::sreal:
								fprintf(output, " float ");
								$$.type = TokenType::vreal;
								break;
								case SymbolType::sstring:
								fprintf(output, " java.lang.String ");
								$$.type = TokenType::vstring;
								break;
								default:
								break;
							}
							fprintf(output, "%s.%s\n", ClassName.c_str(), $1._str);
						}
						else{
							//If ID is local variable.
							switch(pSD->symtype){
								case SymbolType::sinteger:
								fprintf(output, "iload %d\n", pSD->symindex);
								$$.type = TokenType::vint;
								break;
								case SymbolType::sreal:
								fprintf(output, "fload %d\n", pSD->symindex);
								$$.type = TokenType::vreal;
								break;
								case SymbolType::sstring:
								fprintf(output, "aload %d\n", pSD->symindex);
								$$.type = TokenType::vstring;
								break;
								default:
								break;
							}
						}
					}
				}
				else {
				}
				delete $1._str;
				delete pSD;
            }
			| id '[' expression ']' {
				// array 的部分
				$$.type = vint;
			}
            | integer {
                $$ = $1;
                $$.type = vint;
				$$.returnByFun = false;
                fprintf(output, "sipush %d\n", $1._int);
            }
            | str {
                $$ = $1;
                $$.type = vstring;
				$$.returnByFun = false;
                fprintf(output, "\t\tldc %s\n", $1._str);
            }
            | boolean {
                $$ = $1;
                $$.type = vbool;
				$$.returnByFun = false;
                //fprintf(output, "ldc %s\n", $1);
            }
            | real {
                $$ = $1;
                $$.type = vreal;
				$$.returnByFun = false;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
                //fprintf(output, "ldc %s\n", $1);
            }
            ;

expression_list: {
					$$.type = TokenType::typeList;
					$$._ptr = new std::vector<int>();
				}
                |expression{
					$$.type = TokenType::typeList;
					std::vector<int> & list = *(new std::vector<int>());
					list.push_back(Token2Symbol($1.type));
					$$._ptr = &list;
				}
				|expression_list ',' expression{
					$$ = $1;
					std::vector<int> & list = *(std::vector<int>*)$$._ptr;
					list.push_back(Token2Symbol($3.type));
				}
                ;

boolean: TRUE   { $$._bool = 1; }
        |FALSE  { $$._bool = 0; }
        ;

integer_expression: expression '+' expression{
						$$._int = $1._int + $3._int;
						$$.type = vint;
						fprintf(output, "\t\tiadd\n"); 
                    }
                    | '-' expression   %prec UMINUS{
						$$._int = -$2._int;
                        $$.type = TokenType::vint;
						fprintf(output, "ineg\n");
                    }
                    | expression '-' expression{
						$$._int = $1._int - $3._int;
						$$.type = TokenType::vint;
						fprintf(output, "isub\n");
		   			}
                    | expression '*' expression{
						$$.type = TokenType::vint;
						$$._int = $1._int * $3._int;
						fprintf(output, "imul\n");
					}
                    | expression '/' expression{
						$$._int = $1._int / $3._int;
						$$.type = TokenType::vint;
						fprintf(output, "idiv\n");
					}
                    | expression MOD expression{
						$$._int = $1._int % $3._int;
						$$.type = TokenType::vint;
						fprintf(output, "irem\n");
					}
                    ;

bool_expresssion:  '!' expression{
                        $$.type = TokenType::vbool;
						fprintf(output, "iconst_1\n");
                        fprintf(output, "ixor\n");
                }
                | expression '&' expression{
                        $$.type = TokenType::vbool;
                        fprintf(output, "iand\n");
                }
                | expression '|' expression{
                        $$.type = TokenType::vbool;
                        fprintf(output, "ior\n");
                }
                ;

endif: END IF {
	LEAVESCOPE();
}

condition: IF expression IF_PREACT THEN statements %prec LOWER_THAN_ELSE  {	
			if($2.type != TokenType::vbool){
				//Error("Expression must be boolean");
			}
			fprintf(output, "L%d:\n", $<token>3._int-1);
		} endif
         | IF expression IF_PREACT THEN statements ELSE  {
			fprintf(output, "goto L%d\n", $<token>3._int);
			fprintf(output, "L%d:\n", $<token>3._int - 1);
		} 
		statements  {	
			if($2.type != TokenType::vbool){
				//Error("Expression must be boolean");
			}
			fprintf(output, "L%d:\n", $<token>3._int);
		} endif
        ;

condition_r: IF expression IF_PREACT THEN statements_r %prec LOWER_THAN_ELSE  {	
			if($2.type != TokenType::vbool){
				// printf("Expression must be boolean");
			}
			fprintf(output, "L%d:\n", $<token>3._int-1);
		} endif
         | IF expression IF_PREACT THEN statements_r ELSE  {
			fprintf(output, "goto L%d\n", $<token>3._int);
			fprintf(output, "L%d:\n", $<token>3._int - 1);
		} 
		statements_r  {	
			if($2.type != TokenType::vbool){
				// printf("Expression must be boolean");
			}
			fprintf(output, "L%d:\n", $<token>3._int);
		} endif
        ;

IF_PREACT: {
		fprintf(output, "ifeq L%d\n", LabelIndex++);
		$<token>$._int = LabelIndex++;
		// // printf("%d", LabelIndex);

		ENTERSCOPE();
		if_number++;
	}
	;

block: CBEGIN{
				ENTERSCOPE();
} 
statements END{
	LEAVESCOPE();
}
        ;

loop: LOOP {
		ENTERSCOPE();
		loop_number++;

		fprintf(output, "L%d:\n", LabelIndex++);
		// $<token>$._int = LabelIndex++;
	}
	statements  END LOOP{
		
		fprintf(output, "goto L%d\n", LabelIndex - 4);
		fprintf(output, "L%d:\n", exitLabels[loop_number - 1]);
		
		
		LEAVESCOPE();
	}
    | FOR id ':' expression {
			ENTERSCOPE();

			SymbolDesc sd;
			uDependency value;

			sd.symtype = Token2Symbol($4.type);
			sd.iValue = $4._int;
			value.value = $4._ptr;
							
			sd.symdeps.push_back(value);
			sd.returnByFun = false;

			SymbolDesc * pSD;
			std::string idName = std::string($2._str);

			if(seize(idName, pSD)){
				if(pSD->readonly){
					// printf("Assignment to Readonly Variable!");
				}
				else if(pSD->symtype != Token2Symbol($4.type)){
					// printf("Type Unmatch");
				}
				else {
					if(pSD->global){
						fprintf(output, "putstatic %s %s.%s\n", SymType2JBStr(pSD->symtype).c_str(), ClassName.c_str(), $2._str);
					}
					else{
						switch(pSD->symtype){
							case SymbolType::sinteger:
							fprintf(output, "istore %d\n",  pSD->symindex);
							break;
							case SymbolType::sreal:
							fprintf(output, "fstore  %d\n", pSD->symindex);
							break;
							case SymbolType::sstring:
							fprintf(output, "astore  %d\n", pSD->symindex);
							break;
						}
					}
				}
			}
			$<token>$._int = LabelIndex;
			fprintf(output, "L%d:\n", LabelIndex++);
			// $<token>$._int = LabelIndex++;
			
			// If ID is a Variable.
			if(pSD->global){
				//If ID is global variable.
				fprintf(output, "getstatic");
				switch(pSD->symtype){
					case SymbolType::sinteger:
					fprintf(output, " int ");
					break;
					case SymbolType::sreal:
					fprintf(output, " float ");
					break;
					case SymbolType::sstring:
					fprintf(output, " java.lang.String ");
					break;
					default:
					break;
				}
				fprintf(output, "%s.%s\n", ClassName.c_str(), $2._str);
			}
			else{
				// If ID is local variable.
				switch(pSD->symtype){
					case SymbolType::sinteger:
					fprintf(output, "iload %d\n", pSD->symindex);
					break;
					case SymbolType::sreal:
					fprintf(output, "fload %d\n", pSD->symindex);
					break;
					case SymbolType::sstring:
					fprintf(output, "aload %d\n", pSD->symindex);
					break;
					case SymbolType::sboolean:
					fprintf(output, "iload %d\n", pSD->symindex);
					break;
					default:
					break;
				}
			}
			delete pSD;
		}
		'.' '.' expression {
			std::string L1 = "L" + std::to_string(LabelIndex++);
			std::string L2 = "L" + std::to_string(LabelIndex++);
			fprintf(output, "isub\n");
			fprintf(output, "ifgt %s\n", L1.c_str());
			fprintf(output, "iconst_0\n");
			fprintf(output, "goto %s\n", L2.c_str());
			fprintf(output, "%s:\n", L1.c_str());
			fprintf(output, "iconst_1\n");
			fprintf(output, "%s:\n", L2.c_str());
			fprintf(output, "ifne L%d\n", LabelIndex);
			$<token>$._int = LabelIndex++;
		}
		statements { 
			SymbolDesc * pSD;
			if(seize(std::string($2._str),pSD)){
				if(pSD->global){
					// If ID is global variable.
					fprintf(output, "getstatic");
					switch(pSD->symtype){
						case SymbolType::sinteger:
						fprintf(output, " int ");
						break;
						case SymbolType::sreal:
						fprintf(output, " float ");
						break;
						case SymbolType::sstring:
						fprintf(output, " java.lang.String ");
						break;
						default:
						break;
					}
					fprintf(output, "%s.%s\n", ClassName.c_str(), $2._str);
				}
				else{
					// If ID is local variable.
					switch(pSD->symtype){
						case SymbolType::sinteger:
						fprintf(output, "iload %d\n", pSD->symindex);
						break;
						case SymbolType::sreal:
						fprintf(output, "fload %d\n", pSD->symindex);
						break;
						case SymbolType::sstring:
						fprintf(output, "aload %d\n", pSD->symindex);
						break;
						case SymbolType::sboolean:
						fprintf(output, "iload %d\n", pSD->symindex);
						break;
						default:
						break;
					}
				}
				fprintf(output, "sipush 1\n");
				fprintf(output, "iadd\n");
				if(pSD->global){
					fprintf(output, "putstatic %s %s.%s\n", SymType2JBStr(pSD->symtype).c_str(), ClassName.c_str(), $2._str);
				}
				else{
					switch(pSD->symtype){
						case SymbolType::sinteger:
						fprintf(output, "istore %d\n",  pSD->symindex);
						break;
						case SymbolType::sreal:
						fprintf(output, "fstore  %d\n", pSD->symindex);
						break;
						case SymbolType::sstring:
						fprintf(output, "astore  %d\n", pSD->symindex);
						break;
					}
				}
				fprintf(output, "goto L%d\n", $<token>5._int);
				fprintf(output, "L%d:\n", $<token>9._int);
				
			}
			LEAVESCOPE();
			delete pSD;
		}
		 END FOR
    ;

comparison: expression '<' expression{
				$$.type = TokenType::vbool;
				std::string L1 = "L" + std::to_string(LabelIndex++);
				std::string L2 = "L" + std::to_string(LabelIndex++);
				fprintf(output, "isub\n");
				fprintf(output, "iflt %s\n", L1.c_str());
				fprintf(output, "iconst_0\n");
				fprintf(output, "goto %s\n", L2.c_str());
				fprintf(output, "%s:\n", L1.c_str());
				fprintf(output, "iconst_1\n");
				fprintf(output, "%s:\n", L2.c_str());
			}
            | expression LE expression{
				$$.type = TokenType::vbool;
				std::string L1 = "L" + std::to_string(LabelIndex++);
				std::string L2 = "L" + std::to_string(LabelIndex++);
				fprintf(output, "isub\n");
				fprintf(output, "ifle %s\n", L1.c_str());
				fprintf(output, "iconst_0\n");
				fprintf(output, "goto %s\n", L2.c_str());
				fprintf(output, "%s:\n", L1.c_str());
				fprintf(output, "iconst_1\n");
				fprintf(output, "%s:\n", L2.c_str());
			}
            | expression EQ expression{
				$$.type = TokenType::vbool;
				std::string L1 = "L" + std::to_string(LabelIndex++);
				std::string L2 = "L" + std::to_string(LabelIndex++);
				fprintf(output, "isub\n");
				fprintf(output, "ifeq %s\n", L1.c_str());
				fprintf(output, "iconst_0\n");
				fprintf(output, "goto %s\n", L2.c_str());
				fprintf(output, "%s:\n", L1.c_str());
				fprintf(output, "iconst_1\n");
				fprintf(output, "%s:\n", L2.c_str());
			}
            | expression '>' expression{
				$$.type = TokenType::vbool;
				std::string L1 = "L" + std::to_string(LabelIndex++);
				std::string L2 = "L" + std::to_string(LabelIndex++);
				fprintf(output, "isub\n");
				fprintf(output, "ifgt %s\n", L1.c_str());
				fprintf(output, "iconst_0\n");
				fprintf(output, "goto %s\n", L2.c_str());
				fprintf(output, "%s:\n", L1.c_str());
				fprintf(output, "iconst_1\n");
				fprintf(output, "%s:\n", L2.c_str());
			}
            | expression GE expression{
				$$.type = TokenType::vbool;
				std::string L1 = "L" + std::to_string(LabelIndex++);
				std::string L2 = "L" + std::to_string(LabelIndex++);
				fprintf(output, "isub\n");
				fprintf(output, "ifge %s\n", L1.c_str());
				fprintf(output, "iconst_0\n");
				fprintf(output, "goto %s\n", L2.c_str());
				fprintf(output, "%s:\n", L1.c_str());
				fprintf(output, "iconst_1\n");
				fprintf(output, "%s:\n", L2.c_str());
			}
            | expression NE expression{
				$$.type = TokenType::vbool;
				std::string L1 = "L" + std::to_string(LabelIndex++);
				std::string L2 = "L" + std::to_string(LabelIndex++);
				fprintf(output, "isub\n");
				fprintf(output, "ifne %s\n", L1.c_str());
				fprintf(output, "iconst_0\n");
				fprintf(output, "goto %s\n", L2.c_str());
				fprintf(output, "%s:\n", L1.c_str());
				fprintf(output, "iconst_1\n");
				fprintf(output, "%s:\n", L2.c_str());
			}
            ;

declaration: constant_declaration
            |variable_declaration
            |arrays_declaration
            ;

constant_declaration: CONST id ASSIGN declaration_value{
						if (($4.type < SymbolType::sarray) && ($4.type < SymbolType::sarray)){
							char * name = $2._str;
							SymbolDesc sd;
							uDependency value;

							sd.symtype = Token2Symbol($4.type);
							sd.readonly = true;
							sd.hasValue = true;
							if($4.type == vint){
								sd.iValue = $4._int;
							}else if($4.type == vbool){
								sd.bValue = $4._bool;
							}else if($4.type == vstring){
								sd.sValue = $4._str;
							}else if($4.type == vbool){
								sd.iValue = $4._int;
							}
							value.value = $4._ptr;
							sd.returnByFun = $4.returnByFun;
							sd.symdeps.push_back(value);
							insert(std::string(name),sd);
							delete name;
						}else{
							// printf("declaration 型態錯誤\n" );
						}
                    }
                    | CONST id ':' type ASSIGN declaration_value {
						if (($4.type < SymbolType::sarray) && ($4.type < SymbolType::sarray)){
							if ($4.type == $6.type){
								char * name = $2._str;
								SymbolDesc sd;
								uDependency value;

								sd.symtype = Token2Symbol($4.type);
								sd.readonly = true;
								sd.hasValue = true;
								if($4.type == vint){
									sd.iValue = $6._int;
								}else if($4.type == vbool){
									sd.bValue = $6._bool;
								}else if($4.type == vstring){
									sd.sValue = $6._str;
								}else if($4.type == vbool){
									sd.iValue = $6._int;
								}
								value.value = $6._ptr;
								sd.returnByFun = $6.returnByFun;
								sd.symdeps.push_back(value);

								insert(std::string(name),sd);
								delete name;
							}
						}else{
							// printf("declaration 型態錯誤或型態不一樣\n" );
						}
                    }
                    ;

variable_declaration: VAR id ':' type{ 
			std::string name($2._str);
			SymbolDesc sd;
			sd.symtype = Token2Symbol($4.type);
			sd.returnByFun = false;
			insert(std::string(name),sd);
		    }
                    | VAR id ASSIGN declaration_value{ 
						if (($4.type < SymbolType::sarray) && ($4.type < SymbolType::sarray)){
							char * name = $2._str;
							SymbolDesc sd;
							uDependency value;
							sd.symtype = Token2Symbol($4.type);
							sd.hasValue = true;
							if($4.type == vint){
								sd.iValue = $4._int;
							}else if($4.type == vbool){
								sd.bValue = $4._bool;
							}else if($4.type == vstring){
								sd.sValue = $4._str;
							}else if($4.type == vbool){
								sd.iValue = $4._int;
							}
							value.value = $4._ptr;
							sd.returnByFun = $4.returnByFun;
							sd.symdeps.push_back(value);
							insert(std::string(name),sd);
							delete name;
						}else{
							// printf("declaration 型態錯誤\n" );
						}
		    		}
                    | VAR id ':' type ASSIGN declaration_value{ 
						if (($4.type < SymbolType::sarray) && ($4.type < SymbolType::sarray)){
							if ($4.type == $6.type){
								char * name = $2._str;
								SymbolDesc sd;
								uDependency value;
								sd.symtype = Token2Symbol($4.type);
								sd.hasValue = true;
								if($4.type == vint){
									sd.iValue = $6._int;
								}else if($4.type == vbool){
									sd.bValue = $6._bool;
								}else if($4.type == vstring){
									sd.sValue = $6._str;
								}else if($4.type == vbool){
									sd.iValue = $6._int;
								}
								value.value = $6._ptr;
								sd.returnByFun = $6.returnByFun;
								sd.symdeps.push_back(value);
								insert(std::string(name),sd);
								delete name;
							}
						}else{
							// printf("declaration 型態錯誤或型態不一樣\n" );
						}
		    		}
                    ;

arrays_declaration: VAR id ':' ARRAY integer '.' '.' integer OF type{
						SymbolDesc sd;
						uDependency value;
						value.low = $5._int;
						value.high = $8._int;
						
						sd.returnByFun = $10.returnByFun;
						sd.symtype = SymbolType::sarray;
						sd.symdeps.push_back(value);
						insert($2._str, sd);
					}
                    ;

%%

void yyerror(char *msg)
{
    fprintf(stderr, "%s\n", msg);
}
int main(int argc, char **argv)
{
    /* open the source program file */
    if (argc != 2)
    {
        printf("Usage: sc filename\n");
        exit(1);
    }
    yyin = fopen(argv[1], "r"); /* open input file */

	// 改 classname 為 wholename(完整檔案名稱)
	char *filename = strtok(argv[1], ".");
	char *wholeName;
	ClassName = filename;
	sprintf(wholeName, "%s.jasm", filename);

    output = fopen(wholeName, "w");
    InitialTableStack();
    /* perform parsing */
    if (yyparse() == 1)             /* parsing */
        yyerror("Parsing error !"); /* syntax error */

	fclose(yyin);
    fclose(output);
}