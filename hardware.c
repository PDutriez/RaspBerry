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

static int write(void);
static int out(void);
static int export(void);

static FILE * handle_export;
static FILE * handle_direction;
static FILE * handlers[CANTPORTS];
static char * outdirection[CANTPORTS];
static char* pin[CANTPORTS];
const static char* gpio[CANTPORTS]={"17","4","18","23","24","25","22","27"};

void ledon(unsigned int bit)
{	
	if(fputc('1' ,handlers[bit])==-1) // Set pin high
	{
		printf("Clr_Pin: Cannot write to file. Try again later.\n");
		exit(1);
	}
	else
		printf("Write to file %s successfully done.\n",pin[bit]);
			
	
}
void ledoff(unsigned int bit)
{
	if(fputc('0' ,handlers[bit])==-1) // Set pin low
	{
		printf("Clr_Pin: Cannot write to file. Try again later.\n");
		exit(1);
	}
	else
		printf("Write to file %s successfully done.\n",pin[bit]);
	

}

int createall(void)
{
	int counter;    	
	for(counter=0;counter<CANTPORTS;++counter)
    	{
    		sprintf(pin[counter],"sys/class/gpio/gpio""%s""/value", gpio[counter]); //Cremos el puntero al LED
        	sprintf(outdirection[counter],"sys/class/gpio/gpio""%s""/direction", gpio[counter]); //Cremos el puntero al LED
	}
	return 1;
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
	if(write())
		printf("Preparados los LEDs\n");
	else
		verify=0;	
	return verify;
}

void closeall(void)
{
	int count;	
	for(count=0;count<CANTPORTS;++count)
	{
		fclose(handlers[count]);
	}
	fclose(handle_export);
	fclose(handle_direction);
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
	return 1;
}

static int out(void)
{
	int nWritten;
	int counter;	
	for(counter=0;counter<CANTPORTS;++counter)	
	{
//ABRIMOS UN PUNTERO AL ARCHIVO PARA PODER MODIFICAR EL ARCHIVO
		if ((handle_direction= fopen(outdirection[counter],"w")) == NULL)
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
	}

	return 1;
}
static int write(void)
{
	int counter;	
	for(counter=0;counter<CANTPORTS;++counter)	
	{
		if ((handlers[counter] = fopen(pin[counter],"w")) == NULL) //Verificamos la veracidad del handler
        	{
        	        printf("Cannot open device. Try again later.\n");
        	        exit(1);
        	}
        	else
        	{
        	        printf("Device successfully opened\n");
        	}
	}
	return 1;
}
