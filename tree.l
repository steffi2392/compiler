%option noyywrap

%{
#include <string.h>
#include "tree.tab.h"

int lexLookup(char *);

int lineNumber = 1;
#define MAXTOKENLENGTH 201

char savedIdText[MAXTOKENLENGTH];
char savedLiteralText[MAXTOKENLENGTH];
%}

white [ \t]+
letter [A-Za-z]
digit [0-9]
id ({letter}|_)({letter}|{digit}|_)*
integer    {digit}+    
float {integer}"."{integer}?|[+-]?"."{integer}

%x string
%x comment

%%

\n {lineNumber++;}
{white}     /* SKIP */
{id}        return lexLookup(yytext);

{integer}       return NUM;
{float}     return FNUM;

\"          BEGIN(string); 

<string>\n   return BADTOKEN;
<string>\\\" { yymore(); }
<string>\"   {
  BEGIN(INITIAL);               /* go back to normal state */
  yytext[--yyleng] = '\0';      /* remove the trailing double-quote */
  strncpy(savedLiteralText, yytext, MAXTOKENLENGTH - 1);
  return STRING;
 }
<string>.    { yymore(); }


"/*"            BEGIN(comment) ;
<comment><<EOF>> {printf("Error: EOF is within a comment "); return BADTOKEN;} 
<comment>\n     lineNumber++;  
<comment>"*/"   BEGIN(INITIAL);
<comment>.

"&&"	     return AND;
"||" 	     return OR;
"!"          return '!';
"++"         return INCREMENT;
"--"         return DECREMENT; 

";"          return ';';
"="          return '=';
"+"          return '+';
"-"          return '-';
"*"          return '*';
"/"          return '/';  
"#"          return '#';
"<"          return '<';
">"          return '>';
"<="         return LEQ;
">="         return GEQ;
"=="         return ISEQUAL;
"!="         return NOTEQUAL;
"("          return '(';
")"          return ')';
"{"          return '{';
"}"          return '}';
"["          return '[';
"]"          return ']';
","          return ','; 
"%"	     return '%'; 
<<EOF>>      return 0;
.            return BADTOKEN;

%%

int lexLookup(char *s) {
  struct combo {
    char *keyword;
    int token;
  };
  typedef struct combo combo;

  const int KWCOUNT = 12;

  static combo keywords[] =
    { { "int", INT },
      { "while", WHILE },
      { "for", FOR },
      { "do" , DO },
      { "double" , DOUBLE},
      { "read" , READ },
      { "print" , PRINT },
      { "if" , IF },
      { "else" , ELSE},
      { "return" , RETURN } ,
      { "void" , VOID} ,    
      { NULL, ID }
    };

  combo *kw;

  keywords[KWCOUNT-1].keyword = s;

  for (kw = keywords; strcmp(kw->keyword, s) != 0; kw++)
    ;
	  
  return kw->token;
}
