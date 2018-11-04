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

static FILE * handle_export;
static FILE * handle_direction;
static FILE * handler;
const static char* gpio[CANTPORTS]={"17","4","18","23","24","25","22","27"};

void changeled(unsigned int bit, unsigned int value)
{
	char pin[50];
	sprintf(pin,"sys/class/gpio/gpio%s/value", gpio[bit]);
	if ((handler = fopen(pin,"w")) == NULL) //Verificamos la veracidad del handler
				{
								printf("Cannot open device. Try again later.\n");
								exit(1);
				}
				else
				{
								printf("Device successfully opened\n");
								if(value==1 || value==0)
								{
										if(fputc(value+'0',handler)==-1) // Set pin high
										{
												printf("Clr_Pin: Cannot write to file. Try again later.\n");
												exit(1);
										}
										else
												printf("Write to file %s successfully done.\n",gpio[bit]);
								}
								else
											printf("Value out of range\n");
								fclose(handler);
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


static int export(void)
{
	int nWritten;
	if ((handle_export=  fopen("/sys/class/gpio/export","w")) == NULL)
	{
		printf("Cannot open EXPORT File. Try again later.\n");
		exit(1);
	}
	int counter;
	for(counter=0;counter<CANTPORTS;++counter)
	{
//ESTABLECEMOS EL EXPORT DEL PIN
		nWritten=fputs(gpio[counter],handle_export);
		if (nWritten==-1)
		{
			printf("Cannot EXPORT PIN . Try again later.\n");
			exit(1);
		}
		else
			printf("EXPORT File opened succesfully\n");
	}
	fclose(handle_export);
	return 1;
}

static int out(void)
{
	int nWritten;
	int counter;
	char outdirection[50];
	for(counter=0;counter<CANTPORTS;++counter)
	{
//ABRIMOS UN PUNTERO AL ARCHIVO PARA PODER MODIFICAR EL ARCHIVO
		sprintf(outdirection,"/sys/class/gpio/gpio%s/direction", gpio[counter]);
		if ((handle_direction= fopen(outdirection,"w")) == NULL)
		{
			printf("Cannot open DIRECTION File");
			exit(1);
		}
		if ((nWritten=fputs("out",handle_direction))==-1)
		{
			printf("Cannot open DIRECTION pin. Try again later.\n");
			exit(1);
		}
		else
		{
			printf("DIRECTION File for PIN opened succesfully\n");
		}
		fclose(handle_direction);
	}

	return 1;
}
