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
 * funcion que hace de contador de bits de 0 a 255
 ******************************************************************************/
void bit_counter (void)
{
    static unsigned char num_mask=0; //Mascara para la funcion bit_counter
    maskOff ('a', MASK);//Limpiamos los LEDS
    show_port ('a');
    maskOn ('a', num_mask);
    show_port ('a');
    sec_timer ();
    ++num_mask;

}
/*******************************************************************************
 * timer para las diferentes funciones que usamos
 ******************************************************************************/
void sec_timer (void)
{
    float time_init = time (NULL);
    float time_end;
    int on_off = 1;
    int secs = 1;                 //segundos a esperar, tiene una demora de 1s aprox
    while (on_off)                //por si se busca mucha precision para el tiempo
    {
        if (secs >= 0)
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
            on_off=0;
        }
    }
}

/*******************************************************************************
 * funcion del auto fantastico, la luz va de una punta a la otra
 ******************************************************************************/
void boomerang(void)
{
    static char counter=-1;
    static char direction=0;//0=IaD , 1=DaI
    maskOff ('a', MASK);//Limpiamos los LEDS
    show_port ('a');

      if(direction==0)   //ida del bit 0 al 7
      {
        if(++counter<=7)
        {
            bitSet('a',counter);
            show_port ('a');
            sec_timer ();
        }
        else
            direction=1;
      }
      if(direction==1)   //vuelta del bit 7 al 0
      {
        if(--direction>=0)
        {
            bitSet('a',counter);
            show_port ('a');
            sec_timer ();
        }
        else
            direction=0;
      }
}
/*******************************************************************************
 * funcion de blink, va alternando los LEDS
 ******************************************************************************/
void blink(void)
{
    maskToggle ('a', MASK);
    show_port ('a');
    sec_timer();
}
