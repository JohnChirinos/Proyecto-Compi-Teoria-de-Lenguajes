%{
   #include "sintactico.hpp"
   #include <stdio.h>
   #include <stdlib.h>

   #pragma warning(disable: 4273 6011 4267)

   int columna = 1;
   int linea = 1;
   extern int yyerror(const char *s);
%}

%option outfile="escaner.cpp"
%option noyywrap

NUMERO   [0-9]+(\.[0-9]+)?
IDENTIFICADOR   [a-zA-Z_][a-zA-Z0-9_]*

%%




"IF"        { 
		columna += strlen(yytext);
		return IF; 
	    }
	    
"THEN"      { 
		columna += strlen(yytext);
		return THEN; 
	    }
	    
"ELSE"      { 
		columna += strlen(yytext);
		return ELSE; 
	    }
	    
"END"       { 
		columna += strlen(yytext);
		return END; 
	    }
	    
"REPEAT"    { 
		columna += strlen(yytext);
		return REPEAT; 
	    }
	    
"UNTIL"     { 
		columna += strlen(yytext);
		return UNTIL; 	
	    }
	    
"READ"      { 
		columna += strlen(yytext);
		return READ; 
	    }
	    
"WRITE"     { 
		columna += strlen(yytext);
		return WRITE; 
	    }
	    
":="        { 
		columna += strlen(yytext);
		return ASIGNACION; 
	    }
	    
";"         { 
		columna += strlen(yytext);
		return PUNTOYCOMA; 
	    }
	    
"+"         { 
		columna += strlen(yytext);
		return MAS; 
	    }
	    
"-"         { 	
		columna += strlen(yytext);
		return MENOS; 
	    }
	    
"*"         { 
		columna += strlen(yytext);
		return MULTIPLICACION; 
	    }
	    
"/"         { 
		columna += strlen(yytext);
		return DIVISION; 
	    }
	    
"("         { 	
		columna += strlen(yytext);
		return PARENTESIS_IZQ; 
	    }
	    
")"         { 
		columna += strlen(yytext);
		return PARENTESIS_DER; 
	    }
	    
"<"         { 
		columna += strlen(yytext);
		return MENOR; 
	    }
	    
">"         { 
		columna += strlen(yytext);
		return MAYOR; 
	    }
	    
"="         { 
		columna += strlen(yytext);
		return IGUAL; 
	    }
	    
"<>"        { 
		columna += strlen(yytext);
		return DIFERENTE; 
	    }
	    
		
"<="        { 
		columna += strlen(yytext);
		return MENOR_IGUAL; 
	    }
	    
">="        { 	
		columna += strlen(yytext);
		return MAYOR_IGUAL; 	
	    }
	    
{NUMERO}    { 
		columna += strlen(yytext);
		yylval.numero = (float)atof(yytext); return NUMERO; 
	    }
	    
{IDENTIFICADOR}  { 
			columna += strlen(yytext);
			yylval.texto = strdup(yytext); 
			return IDENTIFICADOR; 
		 }

[\t] {
	 columna += strlen(yytext);
      }
      
[\n] { 
	linea++; 
	columna = 1;
     }

. yyerror("Caracter invalido");

%%

int yywrap(void)
{
    return 1;
}