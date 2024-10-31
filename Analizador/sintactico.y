%token NUMERO
%token IDENTIFICADOR
%token IF THEN ELSE END REPEAT UNTIL READ WRITE ASIGNACION PUNTOYCOMA
%token MAS MENOS MULTIPLICACION DIVISION
%token MENOR MAYOR IGUAL DIFERENTE MENOR_IGUAL MAYOR_IGUAL
%token PARENTESIS_IZQ PARENTESIS_DER

%{
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   
   extern unsigned int columna;
   extern unsigned int linea;
   extern int yylex();
   extern FILE *yyin;
   int yyerror(const char *s);
   
   #pragma warning(disable: 4996 4065 6385 6262)
%}

%union {
   float numero;
   char* texto;
}

%type <numero> expresion expresion_simple termino factor NUMERO
%type <texto> instruccion instruccion_if instruccion_repeat instruccion_asignacion instruccion_read instruccion_write secuencia_instrucciones programa IDENTIFICADOR

%output "sintactico.cpp"

%%

programa:
      secuencia_instrucciones
;

secuencia_instrucciones:
      secuencia_instrucciones PUNTOYCOMA instruccion
    | instruccion
;

instruccion:
      instruccion_if
    | instruccion_repeat
    | instruccion_asignacion
    | instruccion_read
    | instruccion_write
    | error {
                  yyerror("Error en la instrucción.");
            }
;

instruccion_if:
      IF expresion THEN secuencia_instrucciones END {
      
      						    }
      						    
    | IF expresion THEN secuencia_instrucciones ELSE secuencia_instrucciones END {
    
    										 }
;

instruccion_repeat:
      REPEAT secuencia_instrucciones UNTIL expresion {
                          
                                                     }
;

instruccion_asignacion:
      IDENTIFICADOR ASIGNACION expresion
;

instruccion_read:
      READ IDENTIFICADOR {
      
                         }
;

instruccion_write:
      WRITE expresion {
      			   printf("%f\n", $2); // Se imprime el valor de la expresión
      		      }
;

expresion:
      expresion_simple MENOR expresion_simple {
       						   $$ = ($1 < $3);
      					      }
      					      
    | expresion_simple MAYOR expresion_simple {
       						   $$ = ($1 > $3);
      					      }
      					      
    | expresion_simple IGUAL expresion_simple {
       						   $$ = ($1 == $3);
      					      }
    
    | expresion_simple DIFERENTE expresion_simple {
       						      $$ = ($1 != $3);
      					      	  }
    
    | expresion_simple MENOR_IGUAL expresion_simple {
       						   	 $$ = ($1 <= $3);
      					      	    }
      					      	  
    | expresion_simple MAYOR_IGUAL expresion_simple {
       						   	 $$ = ($1 >= $3);
      					      	    }
    
    | expresion_simple {
    				$$ = $1;
    		       }
;

expresion_simple:
      expresion_simple MAS termino {
      					$$ = $1 + $3;	
      				   }
    | expresion_simple MENOS termino {
      					$$ = $1 - $3;	
      				     }
    | termino {
    		 $$ = $1;
    	      }
;

termino:
      termino MULTIPLICACION factor {
      					$$ = $1 * $3;
      				    }
    | termino DIVISION factor {
      				$$ = $1 / $3;
      			      }
    | factor {
    		$$ = $1;
    	     }
;

factor:
      PARENTESIS_IZQ expresion PARENTESIS_DER {
      						  $$ = $2;
      					      }
    | NUMERO {
    		$$ = $1;
    	     }
    | IDENTIFICADOR {
    			$$ = $1;
    	     	    }	
    | error {
    		yyerror("Error en la instrucción.");
    	    }
;

%%

int yyerror(const char *s) 
{

   char mensaje[100];

   if ( !strcmp( s, "parse error" ) )
      strcpy( mensaje, "Error de sintaxis" );
   else
      strcpy( mensaje, s );

   exit( 1 ); /* Sale del programa */

   return 0;
}


int main(int argc, char * argv[])
{

   ++argv;
   --argc;  
   if (argc > 0)
        yyin = fopen( argv[0], "r" );
   else
        yyin = stdin;
 
   yyparse();
   return 0;
}

