/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hardware.c
 * Author: pdutriez
 *
 * Created on 31 de octubre de 2018, 12:00
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define CANTPORTS   8

static FILE * handlers[CANTPORTS];
static char* pin[CANTPORTS];
const static char* gpio[CANTPORTS]={"17","4","18","23","24","25","22","27"}

/*
 * 
 */
int main(int argc, char** argv) 
{

    return (EXIT_SUCCESS);
}

bool create_open(FILE ** handlers,char ** pins,char ** gpios,const unsigned int cant)
{
    for(int counter=0;counter<cant;++counter)
    {
        sprintf(pins[counter],"sys/class/gpio/gpio"%s"/value", gpios[counter]); //Cremos el puntero al LED

        if ((handlers[counter] = fopen(pins[counter],"w")) == NULL) //Verificamos la veracidad del handler
        {
                printf("Cannot open device. Try again later.\n");
                exit(1);
        }
        else
        {
                printf("Device successfully opened\n");
        }
    }
}

