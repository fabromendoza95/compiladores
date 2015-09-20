#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "lexico.h"
FILE *archivo;
FILE *salida;
token t;
char msj[5*TAMLEX];
char id[TAMLEX];
int numlinea = 1;


void error(int numlinea,char* mensaje)
{
	printf("Lin: %d. Error Lexico: %s\n",numlinea,mensaje);
}

void getToken(){
	int i = 0;
	int estado,aceptado;
	char c = 0;
	salida = fopen("output.txt","w");
	while((c=fgetc(archivo)) != EOF){
		//printf("linea actual: %d\n",numlinea);
		if ( c == '\t'){
			fputc('\t',salida);
		}
		else if(c ==' '){
			fputc('\t',salida);
		}
        else if(c == '\n'){
			fputc('\n',salida);
            numlinea ++;
        }
		else if (c == '['){
            id[0] = c;
            id[1] = '\0';
			fputs("L_CORCHETE",salida);
			printf("linea: %d - componente lexixo: %s - lexema: %s \n",numlinea,"L_CORCHETE",id);
		}
		else if(c == ']'){
            id[0] = c;
            id[1] = '\0';
			fputs("R_CORCHETE",salida);
            printf("linea: %d - %s \n",numlinea,id);
		}
		else if(c == '{'){
            printf("entre en left llave\n");
            id[0] = c;
            id[1] = '\0';
			fputs("L_LLAVE",salida);
			printf("linea: %d - %s \n",numlinea,id);
		}
		else if(c == '}'){
            
            id[0] = c;
            id[1] = '\0';
			fputs("R_LLAVE",salida);
			printf("linea: %d - %s \n",numlinea,id);
		}
		else if(c == ','){
            
            id[0] = c;
            id[1] = '\0';
			fputs("COMA",salida);
			printf("linea: %d - %s \n",numlinea,id);
		}
		else if(c == ':'){
            
            id[0] = c;
            id[1] = '\0';
			fputs("DOS_PUNTOS",salida);
			printf("linea: %d - %s \n",numlinea,id);
		}
		else if(c == '"'){
			ungetc(c,archivo);
			estado = 1;
			aceptado = 0;
            i = 0;
			while(!aceptado){
				switch(estado){
					case 1:
						c = fgetc(archivo);
						if (c == '"'){
                            id[i++] = c;
							estado = 2;
						}
						break;
					case 2:
						c = fgetc(archivo);
						if (c == '"'){
                            id[i++] = c;
							estado = 3;
							//printf("cambio de estado 2 a 3\n");
						}
						else{
                            id[i++] = c;
							estado = 2;
						}
						break;
					case 3:
						aceptado = 1;
                        id[i] = '\0';
						break;
				}
			}
			if (aceptado){
				printf("linea: %d - %s \n",numlinea,id);
				fputs("LITERAL_CADENA",salida);
			}
			
		}
		else if(isalpha(c)){
			//si es una palabra reservada  true
			int i;
			if (c=='t' || c=='T'){//la palabra reservada true
				ungetc(c,archivo);
				estado = 1;
				aceptado = 0;
				i = 0;
				while(!aceptado){
					switch (estado){
						case 1:
							c = fgetc(archivo);
							if (c=='t'){
								estado = 2;
								id[i++] = c;
							}
							else if(c=='T'){
								estado = 3;
								id[i++] = c;
							}
							break;
						case 2:
							c = fgetc(archivo);
							if(c=='r'){
								estado = 4;
								id[i++] = c;
							}
							break;
						case 3:
							c = fgetc(archivo);
							if(c=='R'){
								estado = 5;
								id[i++] = c;
							}
							break;
						case 4:
							c = fgetc(archivo);
							if(c=='u'){
								estado = 6;
								id[i++] = c;
							}
							break;
						case 5:
							c = fgetc(archivo);
							if(c=='U'){
								estado = 7;
								id[i++] = c;
							}
							break;
						case 6:
							c = fgetc(archivo);
							if (c=='e'){
								estado = 8;
								id[i++] = c;
							}
							break;
						case 7:
							c = fgetc(archivo);
							if (c=='E'){
								estado = 9;
								id[i++] = c;
							}
							break;
						case 8:
							aceptado = 1;
							id[i] = '\0';
							break;
						case 9:
							aceptado = 1;
							id[i] = '\0';
							break;
					}
				}
				if (aceptado){
					fputs("PR_TRUE",salida);
                    printf("linea: %d - %s \n",numlinea,id);
                }
			}
			else if(c=='f' || c=='F'){
				ungetc(c,archivo);
				estado = 1;
				aceptado = 0;
				i = 0;
				while(!aceptado){
					switch (estado){
						case 1:
							c = fgetc(archivo);
							if(c=='f'){
								estado = 2;
								id[i++] = c;
							}
							else if(c=='F'){
								estado = 3;
								id[i++] = c;
							}
							break;
						case 2:
							c = fgetc(archivo);
							if(c=='a'){
								estado = 4;
								id[i++] = c;
							}
							break;
						case 3:
							c = fgetc(archivo);
							if(c=='A'){
								estado = 5;
								id[i++] = c;
							}
							break;
						case 4:
							c = fgetc(archivo);
							if(c=='l'){
								estado = 6;
								id[i++] = c;
							}
							break;
						case 5:
							c = fgetc(archivo);
							if(c=='L'){
								estado = 7;
								id[i++] = c;
							}
							break;
						case 6:
							c = fgetc(archivo);
							if(c=='s'){
								estado = 8;
								id[i++] = c;
							}
							break;
						case 7:
							c = fgetc(archivo);
							if(c=='S'){
								estado = 9;
								id[i++] = c;
							}
							break;
						case 8:
							c = fgetc(archivo);
							if(c=='e'){
								estado = 10;
								id[i++] = c;
							}
							break;
						case 9:
							c = fgetc(archivo);
							if(c=='E'){
								estado = 11;
								id[i++] = c;
							}
							break;
						case 10:
							aceptado = 1;
							id[i] = '\0';
							break;
						case 11:
							aceptado = 1;
							id[i] = '\0';
							break;
					}
				}
				if(aceptado){
					fputs("PR_FALSE",salida);
    	    	    printf("linea: %d - %s \n",numlinea,id);
            	}
			}
			else if (c=='n' || c=='N'){//la palabra reservada null
				ungetc(c,archivo);
				estado = 1;
				aceptado = 0;
				i = 0;
				while(!aceptado){
					switch (estado){
						case 1:
							c = fgetc(archivo);
							if (c=='n'){
								estado = 2;
								id[i++] = c;
							}
							else if(c=='N'){
								estado = 3;
							id[i++] = c;
							}
							break;
						case 2:
							c = fgetc(archivo);
							if(c=='u'){
								estado = 4;
								id[i++] = c;
							}
							break;
						case 3:
							c = fgetc(archivo);
							if(c=='U'){
								estado = 5;
								id[i++] = c;
							}
							break;
						case 4:
							c = fgetc(archivo);
							if(c=='l'){
								estado = 6;
								id[i++] = c;
							}
							break;
						case 5:
							c = fgetc(archivo);
							if(c=='L'){
								estado = 7;
								id[i++] = c;
							}
							break;
						case 6:
							c = fgetc(archivo);
							if (c=='l'){
								estado = 8;
								id[i++] = c;
							}
							break;
						case 7:
							c = fgetc(archivo);
							if (c=='L'){
								estado = 9;
								id[i++] = c;
							}
							break;
						case 8:
							aceptado = 1;
							id[i] = '\0';
							break;
						case 9:
							aceptado = 1;
							id[i] = '\0';
							break;
					}
				}
				if (aceptado){
					fputs("PR_NULL",salida);
    	    	 	printf("linea: %d - %s \n",numlinea,id);
            	}			
			}
			
		}	
		else if(isdigit(c)){
			//si es un numero
			ungetc(c,archivo);
			estado = 1;
			aceptado = 0;
			i = 0;
			while(!aceptado && estado != -1){
				switch (estado){
					case 1:
						c = fgetc(archivo);
						if(isdigit(c)){
							id[i++] = c;
							estado = 2;
						}
						else{
							
							estado = -1;
						}
						break;
					case 2:
						c = fgetc(archivo);
						if(isdigit(c)){
							id[i++] = c;
							estado = 2;
						}
						else if(c == '.'){
							id[i++] = c;
							estado = 3;
						}
						else if(tolower(c) == 'e'){
							id[i++] = c;
							estado = 4;
							}
						else{
							id[i] = '\0';
							aceptado = 1;
						}
						break;
					case 3:
						c = fgetc(archivo);
						if(isdigit(c)){
							id[i++] = c;
							estado = 5;
						}
						else{
							estado = -1;
						}
						break;
					case 4:
						c = fgetc(archivo);
						if(isdigit(c)){
							id[i++] = c;
							estado = 7;
						}
						else if(c == '+' || c == '-'){
							id[i++] = c;
							estado = 6;
						}
						else{
							estado = -1;
						}
						break;
					case 5:
						c = fgetc(archivo);
						if(isdigit(c)){
							id[i++] = c;
							estado = 5;
						}
						else if(tolower(c) == 'e'){
							id[i++] = c;
							estado = 4;
						}
						else{
							id[i] = '\0';
							aceptado = 1;
						}
						break;
					case 6:
						c = fgetc(archivo);
						if(isdigit(c)){
							id[i++] = c;
							estado = 7;
						}
						else{
							estado = -1;
						}
						break;
					case 7:
						c = fgetc(archivo);
						if (isdigit(c)){
							estado = 7;
							id[i++] = c;
						}
						else{
							id[i] = '\0';
							aceptado = 1;
						}
						break;
					case -1:
					//informe del error lexico
                        sprintf(msj,"no se esperaba %c",c);
						error(numlinea,msj);
						break;
				}
			}
			if(aceptado){
				fputs("LITERAL_NUM",salida);
	            printf("linea: %d - %s \n",numlinea,id);
			}
		}
        
	}
    
}
int main(int argc, char* args[]){
    char c = 0;
	if ((archivo=fopen(args[1],"rt"))){
        getToken();
	}
	else{
		printf("Error no se pudo abrir el archivo\n");
	}
	fclose(archivo);
    return 0;
}
