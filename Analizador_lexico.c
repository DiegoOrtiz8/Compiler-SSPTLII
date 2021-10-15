#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Son los tokens que reconocer� el analizador */
enum {FIN = 0, ID = 256, NUM, DO, GOTO, VOID, BREAK, DOUBLE, IF, SIZEOF, VOLATILE, CASE, ELSE,
INT, STATIC, WHILE, CHAR, ENUM, LONG, STRUCT, CONST, TYPEDEF, FLOAT, RETURN, DEFAULT, FOR, UNSIGNED, THEN};

char buffer[500];
char * yytext;
char * p;
int yyleng;

#define MAXIMO 25
struct {
char * nombre;
int * token;
}

tabla[MAXIMO] = {"do", DO, "goto", GOTO, "void", VOID, "break", BREAK, "double", DOUBLE, "if", IF,
"sizeof", SIZEOF, "volatile", VOLATILE, "case", CASE, "else", ELSE, "int", INT, "static", STATIC,
"while", WHILE, "char", CHAR, "enum", ENUM, "long", LONG, "struct", STRUCT, "const", CONST, "typedef", TYPEDEF,
"float", FLOAT, "return", RETURN, "default", DEFAULT, "for", FOR, "unsigned", UNSIGNED, "then", THEN};

int yylex(void);

int main() {
    int t;
    while ((t=yylex()) != FIN) {
        switch(t) {
            case NUM:
                // Numeros
                printf("Numero '%s' de %d digitos\n\n", yytext, yyleng);
                system("pause");
                system("cls");
                break;
            case ID:
                // Identificadores
                printf("Id '%s' de %d caracteres\n\n", yytext, yyleng);
                system("pause");
                system("cls");
                break;
            case DO:
            case GOTO:
            case VOID:
            case BREAK:
            case DOUBLE:
            case IF:
            case SIZEOF:
            case VOLATILE:
            case CASE:
            case ELSE:
            case INT:
            case STATIC:
            case WHILE:
            case CHAR:
            case ENUM:
            case LONG:
            case STRUCT:
            case CONST:
            case TYPEDEF:
            case FLOAT:
            case RETURN:
            case DEFAULT:
            case FOR:
            case UNSIGNED:
            case THEN:
                // Palabras Reservadas
                printf("Palabra reservada '%s' de %d caracteres\n\n", yytext, yyleng);
                system("pause");
                system("cls");
                break;
            default:
                // Operadores Aritmeticos
                if((t == '+') || (t == '-') || (t == '*') || (t == '/') || (t == '%')) {
                    printf("Operador Aritmetico '%c'\n\n", t);
                    system("pause");
                    system("cls");
                    break;
                }
                // Operadores Relacionales
                if((t == '<') || (t == '>') || (t == '=')) {
                    printf("Operador Relacional '%c'\n\n", t);
                    system("pause");
                    system("cls");
                    break;
                }
                // Simbolos
                if((t == '(') || (t == ')') || (t == '{') || (t == '}') || (t == '[') || (t == ']') || (t == '$')
                || (t == '@') || (t == '#') || (t == '^') || (t == '?')){
                    printf("Simbolo '%c'\n\n", t);
                    system("pause");
                    system("cls");
                    break;
                }
                // Caracteres
                printf("Es el caracter '%c'\n\n",t);
                system("pause");
                system("cls");
                break;
        }
    }
    return EXIT_SUCCESS;
}

int yylex(void)
{
    printf("Escribe una palabra:\tCTRL + C para salir\n");
    int c;
    /*Filtramos los espacios*/
    while((c=getchar()) == ' ' || c == '\n' || c == '\t');

    if(c==EOF)
        return FIN;
    yytext = buffer;
    p = buffer;
    if(isdigit(c)) {
        do {
            *p = c;
            p++;
            c = getchar();
        }while(isdigit(c));
    if(c != EOF) ungetc(c,stdin);
    *p = 0;
    yyleng = p - yytext;
    return NUM;
    }
    else if (isalpha(c)) {
    int i;
    do {
        *p = c;
        p++;
        c = getchar();
    }while(isalnum(c));
    if(c != EOF) ungetc(c,stdin);
    *p = 0;
    yyleng = p - yytext;
    for(i = 0; i < MAXIMO; i++)
        if(strcmp(tabla[i].nombre, yytext) == 0)
            return tabla[i].token;
    return ID;
    }
    else return c;
}
