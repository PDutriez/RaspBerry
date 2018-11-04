/*******************************************************************************
 * Liberías utilizadas
 ******************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include "puerto.h"
#include "LED.h"
#include "Addons.h"
#include <time.h>
/*******************************************************************************
 * variables propias de este archivo
 ******************************************************************************/
static int num_mask;    //Mascara para la funcion bit_counter
static int input;
/*******************************************************************************
 * funcion que hace de contador de bits de 0 a 255
 ******************************************************************************/
void bit_counter (void)
{
    while(((input=getchar())!='n' && input!='N' )|| (input!= 'q' && input != 'Q'))
    {
        for (num_mask =0;num_mask <= 255; num_mask++)
        {
            maskOn ('a', num_mask);
            show_port ('a');
            sec_timer ();
            if (num_mask >= 255)      //Esto lo forzara a un ciclo hasta que
            {                         //que vuelvan a presionar la tecla o
                num_mask = 0;         //o cierren el programa
            }
        }
    }
}
/*******************************************************************************
 * timer para las diferentes funciones que usamos
 ******************************************************************************/
void sec_timer (void)
{
    long int time_init = time (NULL);
    long int time_end;
    int on_off = 1;
    int secs = 1;                 //segundos a esperar, tiene una demora de 1s aprox
    while (on_off)                //por si se busca mucha precision para el tiempo
    {
        if (secs >= 1)
        {
            time_end = time (NULL);
            if (time_end >= (time_init + secs) )
            {
                on_off = 0;
            }
        }
        else
        {
            printf ("\nerror, los segundos ingresados no son validos\n");
        }
    }
}

/*******************************************************************************
 * funcion del auto fantastico, la luz va de una punta a la otra
 ******************************************************************************/
void boomerang(void)
{
    int counter;
    maskOff ('a', MASK);
    show_port ('a');
    while(((input=getchar())!='f' && input!='F' )|| (input!= 'q' && input != 'Q'))
    {
      for(counter=0;counter<=7;++counter)   //ida del bit 0 al 7
      {
        bitSet('a',counter);
        show_port ('a');
        bitClr('a',counter);
        show_port ('a');
        sec_timer ();
      }
      for(counter=7;0<=counter;--counter)   //vuelta del bit 7 al 0
      {
        bitSet('a',counter);
        show_port ('a');
        bitClr('a',counter);
        show_port ('a');
        sec_timer ();
      }
    }
}
