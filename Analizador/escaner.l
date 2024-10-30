%{
   #include "sintactico.hpp"
   #include <stdio.h>
   #include <stdlib.h>

   int columna = 1;
   int linea = 1;
   extern int yyerror(const char *s);
%}

%option outfile="escaner.cpp"
%option noyywrap


NUMERO   [0-9]+(\.[0-9]+)?
IDENTIFICADOR   [a-zA-Z_][a-zA-Z0-9_]*

%%

[ \t\n]+     ;   


"IF"        { 
		return IF; 
	    }
	    
"THEN"      { 
		return THEN; 
	    }
	    
"ELSE"      { 
		return ELSE; 
	    }
	    
"END"       { 
		return END; 
	    }
	    
"REPEAT"    { 
		return REPEAT; 
	    }
	    
"UNTIL"     { 
		return UNTIL; 	
	    }
	    
"READ"      { 
		return READ; 
	    }
	    
"WRITE"     { 
		return WRITE; 
	    }
	    
":="        { 
		return ASIGNACION; 
	    }
	    
";"         { 
		return PUNTOYCOMA; 
	    }
	    
"+"         { 
		return MAS; 
	    }
	    
"-"         { 	
		return MENOS; 
	    }
	    
"*"         { 
		return MULTIPLICACION; 
	    }
	    
"/"         { 
		return DIVISION; 
	    }
	    
"("         { 	
		return PARENTESIS_IZQ; 
	    }
	    
")"         { 
		return PARENTESIS_DER; 
	    }
	    
"<"         { 
		return MENOR; 
	    }
	    
">"         { 
		return MAYOR; 
	    }
	    
"="         { 
		return IGUAL; 
	    }
	    
"<>"        { 
		return DIFERENTE; 
	    }
	    
		
"<="        { 
		return MENOR_IGUAL; 
	    }
	    
">="        { 	
		return MAYOR_IGUAL; 	
	    }
	    
{NUMERO}    { 
		yylval.numero = atof(yytext); return NUMERO; 
	    }
	    
{IDENTIFICADOR}  { 
			yylval.texto = strdup(yytext); return IDENTIFICADOR; 
		 }

.           

%%
