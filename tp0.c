#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NOMBRE 20
#define MAX_NUMEROS 20
const char TIPO_NORMAL ='N';
const char TIPO_FUEGO='F';
const char TIPO_AGUA = 'A';
const char TIPO_PLANTA = 'P';
const char TIPO_ELECTRICO = 'E';
const char TIPO_ROCA = 'R';
const char LIMITADOR = ';';

enum TIPO { NORMAL, FUEGO, AGUA, PLANTA, ELECTRICO, ROCA };

struct ataque {
	char nombre[20];
	enum TIPO tipo;
	unsigned int poder;
};


bool existe_un_nombre(char nombre[MAX_NOMBRE], char* texto, char separador,int*posicion)
{
	
	*posicion=0;
	bool nombre_encontrado= false;

	while(texto[*posicion] != separador && texto[*posicion] != 0){
        nombre[*posicion] = texto[*posicion];
        (*posicion)++;
		nombre_encontrado= true;

    }
	nombre[*posicion] = 0;
	
    return nombre_encontrado;
}


enum TIPO tipo(char* texto, int* posicion)
{
    enum TIPO tipo_buscado;
	(*posicion)++;
	if(texto[*posicion] == TIPO_ELECTRICO){
        tipo_buscado = ELECTRICO;
	}else if(texto[*posicion] == TIPO_ROCA){
		tipo_buscado = ROCA;
	}else if(texto[*posicion] == TIPO_AGUA){
		tipo_buscado = AGUA;
	}else if(texto[*posicion] == TIPO_FUEGO){
		tipo_buscado = FUEGO;
	}else if(texto[*posicion] == TIPO_NORMAL){
		tipo_buscado = NORMAL;
	}else{
		tipo_buscado = PLANTA;
	}

	(*posicion)++;


	return tipo_buscado;
}



bool existe_un_tipo(char* texto,int posicion,char separador)
{
	posicion++;
	
	return (texto[posicion]  != 0 && (texto[posicion] == TIPO_AGUA || texto[posicion] == TIPO_ELECTRICO || 
	    texto[posicion] == TIPO_FUEGO || texto[posicion] ==TIPO_NORMAL || texto[posicion] == TIPO_PLANTA || texto[posicion] == TIPO_ROCA) );
}



bool existe_un_poder(char* texto, int posicion)
{
	return texto[posicion] != 0;
}



int numero(char* texto, int* posicion)
{
	char numeros[MAX_NUMEROS];
    
	int i=0;
	while ( texto[*posicion] != 0 && texto[*posicion] != LIMITADOR){
		
		numeros[i] = texto[*posicion];
		(*posicion)++;
		i++;
	}
    numeros[i] = 0;
	

	return atoi(numeros);

}
struct ataque *parsear_ataque(char *texto, struct ataque *ataque)
{
	
    
    int posicion=0;
    char nombre[MAX_NOMBRE];
	enum TIPO tipo_buscado;
	int numero_buscado=0;
	

	if(strlen(texto) >0){
		if(existe_un_nombre(nombre,texto,LIMITADOR,&posicion)){
			strcpy(ataque->nombre,nombre);

			if(existe_un_tipo(texto,posicion,LIMITADOR)){
				tipo_buscado = tipo(texto,&posicion);
				
				ataque->tipo = tipo_buscado;
				posicion++;
				
				if(existe_un_poder(texto,posicion)){
					numero_buscado = numero(texto,&posicion);
					ataque->poder = (unsigned int)numero_buscado;
					
					return ataque;
				}
				
			}   
		}

	}
	return NULL;
}

int main()
{
	struct ataque un_ataque;
	int errores = 0;

	if (parsear_ataque("", &un_ataque) != NULL) {
		printf("Se espera que no se pueda parsear un string vacío D:\n");
		errores++;
	} else
		printf("Parseo de un string vacío 👍\n");

	if (parsear_ataque("Rayo;E;", &un_ataque) != NULL) {
		printf("Se espera que no se pueda parsear un string incorrecto D:\n");
		errores++;
	} else
		printf("Parseo de un string incorrecto 👍\n");


	if (parsear_ataque("Rayo;E;5", &un_ataque) == NULL) {
		printf("Se espera que se pueda parsear un string correcto D:\n");
		errores++;
	} else if (strcmp(un_ataque.nombre, "Rayo") == 0 &&
		un_ataque.tipo == ELECTRICO && un_ataque.poder == 5) {
		printf("Parseo de un string correcto 👍\n");
	} else {
		printf("Se parseó el string pero los valores son incorrectos 🤔\n");
		errores++;
	}
	

	return errores;
}