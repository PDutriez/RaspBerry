/*
 * File:   hardware.c
 * Author: pdutriez
 *
 * Created on 31 de octubre de 2018, 12:00
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hardware.h"

#define CANTPORTS   8


static int out(void);
static int export(void);




const static char* gpio[CANTPORTS]={"17","4","18","23","24","25","22","27"};

int changeled(unsigned int bit,unsigned int value)//Funcion para modificar los LEDS de la RPI
{
	char valor='0'+value;
	printf("%c",valor);
	FILE * handler;
	char pin[50];//Arreglo utilizado como string del comando
	sprintf(pin,"/sys/class/gpio/gpio%s/value", gpio[bit]);//Cargamos el comando del puerto correspondiente
	if(value==1 || value==0)
	{
					if ((handler = fopen(pin,"w")) == NULL) //Verificamos la veracidad del handler
					{
								printf("Cannot open device. Try again later.\n");
								return 0;
					}
					else
					{
								printf("Device successfully opened\n");
								if(fputc(valor,handler)==-1) // Set pin high
								{
											printf("Clr_Pin: Cannot write to file. Try again later.\n");
											return 0;
								}
								else
								{
											printf("Write to file %s successfully done.\n",gpio[bit]);
								}
					}
								fclose(handler);
								return 1;

	}
	else
	{
					printf("Value out of range\n");
					return 0;
	}
}

int expoutall(void)
{
	int verify=1;
	if(export())
			printf("Exportados los pins\n");
	else
			verify=0;
	if(out())
			printf("Seteados como salida los pines\n");
	else
			verify=0;

	return verify;
}
int unexport(void)
{
	FILE * handle_export;
	int nWritten, counter;
	for(counter=0;counter<CANTPORTS;++counter)
	{
//ESTABLECEMOS EL EXPORT DEL PIN
				if ((handle_export=  fopen("/sys/class/gpio/unexport","w")) == NULL)
				{
						printf("Cannot open EXPORT File. Try again later.\n");
						return 0;
				}
				nWritten=fputs(gpio[counter],handle_export);

				if (nWritten==-1)
				{
						printf("Cannot EXPORT PIN . Try again later.\n");
						return 0;
				}
				else
						printf("EXPORT File closed succesfully\n");

				fclose(handle_export);
	}
	return 1;
}

static int export(void)
{
	FILE * handle_export;
	int nWritten, counter;
	for(counter=0;counter<CANTPORTS;++counter)
	{
//ESTABLECEMOS EL EXPORT DEL PIN
				if ((handle_export=  fopen("/sys/class/gpio/export","w")) == NULL)
				{
						printf("Cannot open EXPORT File. Try again later.\n");
						return 0;
				}
				nWritten=fputs(gpio[counter],handle_export);

				if (nWritten==-1)
				{
						printf("Cannot EXPORT PIN . Try again later.\n");
						return 0;
				}
				else
						printf("EXPORT File opened succesfully\n");

				fclose(handle_export);
	}
	return 1;
}

static int out(void)
{
	FILE * handle_direction;
	int nWritten, counter;
	char outdirection[50];//Arreglo utilizado como string del comando

	for(counter=0;counter<CANTPORTS;++counter)
	{
//ABRIMOS UN PUNTERO AL ARCHIVO PARA PODER MODIFICAR EL ARCHIVO
		sprintf(outdirection,"/sys/class/gpio/gpio%s/direction", gpio[counter]);
		if ((handle_direction= fopen(outdirection,"w")) == NULL)//Abrimos el archivo
		{
			printf("Cannot open DIRECTION File");
			return 0;
		}

		if ((nWritten=fputs("out",handle_direction))==-1)//Lo seteamos como salida
		{
			printf("Cannot open DIRECTION pin. Try again later.\n");
			return 0;
		}
		else
		{
			printf("DIRECTION File for PIN opened succesfully\n");
		}
		fclose(handle_direction);
	}

	return 1;
}
