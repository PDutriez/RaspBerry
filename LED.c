/*******************************************************************************
 * Liberías utilizadas
 ******************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "puerto.h"
#include "LED.h"
#include "hardware.h"
#include "Addons.h"
#include "nonblock.h"
/*******************************************************************************
 * variables propias de este archivo
 ******************************************************************************/
static int input;
static char flag_car;
static char flag_count;
static char flag_blink;
/******************************************************************************/

/*******************************************************************************
 * función principal, analiza el input y responde segun corresponda
 ******************************************************************************/
int main ()
{
    nonblock(NB_ENABLE);
    printf ("Ingrese el numero de LED o el comando\n");
    if(expoutall())
    {
      flag_car=0; //Iniciamos con el flag en 0
      flag_count=0; //Iniciamos con el flag en 0
      while (input!= 'q' && input!= 'Q')
      {
          if(kbhit())
          {
              input=getchar();
          }
          else
          {
              input=0;
          }
          /***********************************************************************
          * primero revisa si se trata de un numero de led
          ***********************************************************************/
          if((input!='\n' || input))
          {
              if(((input <= '9') && (input >= '0'))&&(flag_car!=1)&&(flag_count!=1)&&(flag_blink!=1))
              {
                  int counter=0;
                  do{
                      counter=(counter*10)+input;
                    }
                  while((input=getchar()) != '\n');
      //No se va a utilizar ahora pero en un futuro necesitaremos entrada de 2 digitos
                  if ((counter <= '7') && (counter >= '0'))
                  {
                      counter-='0';
                      bitSet ('a', counter);
                      show_port ('a');
                  }
                  else
                  printf("\nValor fuera del rango.\n");
              }
              /***********************************************************************
              * como el puerto solo tiene 8 espacios avisa en caso de que el numero
              * no coincida con alguno de ellos
              ***********************************************************************/

              /***********************************************************************
              * si se presiona la letra 'T' todos los bits cambian a su opuesto
              ***********************************************************************/
              else if (((input == 't') || (input == 'T'))&&(flag_car!=1)&&(flag_count!=1)&&(flag_blink!=1))
              {
                  maskToggle ('a', MASK);
                  show_port ('a');
              }
              /***********************************************************************
              * si se presiona la letra 'S' prende todos los bits
              ***********************************************************************/
              else if (((input == 's') || (input == 'S'))&&(flag_car!=1)&&(flag_count!=1)&&(flag_blink!=1))
              {
                  maskOn ('a', MASK);
                  show_port ('a');
              }
              /***********************************************************************
              * si se presiona la letra 'C' apaga todos los bits
              ***********************************************************************/
              else if (((input == 'c') || (input == 'C'))&&(flag_car!=1)&&(flag_count!=1)&&(flag_blink!=1))
              {
                  maskOff ('a', MASK);
                  show_port ('a');
              }
              else if (((input == 'f') || (input == 'F'))&&(flag_count!=1)&&(flag_blink!=1))
              {
                  if(flag_car==0)
                      flag_car=1;
                  else if(flag_car==1)
                      flag_car=0;
              }
              else if (((input == 'n') || (input == 'N'))&&(flag_car!=1)&&(flag_blink!=1))
              {
                if(flag_count==0)
                    flag_count=1;
                else if(flag_count==1)
                    flag_count=0;
              }
              else if (((input == 'b') || (input == 'B'))&&(flag_car!=1)&&(flag_count!=1))
              {
                  if(flag_blink==0)
                      flag_blink=1;
                  else if(flag_blink==1)
                      flag_blink=0;
              }
              /***********************************************************************
              * en caso de tocar cualquier otra letra (excepto la Q, pues con ella
              * se termina el programa)se notificará que no hay acciones disponibles
              ***********************************************************************/
              else  if(input!='\0' && input!='\n')
                  printf ("El comando ingresado no es válido\n");
              /***********************************************************************
              * para finalizar, muestra el puerto en la pantalla para que se puedan
              * apreciar los cambios realizados
              ***********************************************************************/
          }
          if(flag_car)
            boomerang();
          if(flag_count)
            bit_counter();
          if(flag_blink)
            blink();

      }
      unexport();
    }
    return 0;
}

/*******************************************************************************
 * función secundaria, muestra el puerto indicado en la pantalla
 ******************************************************************************/
void show_port (char Port_A)
{
    printf ("\n\nEstado del puerto A:\n");
    /***************************************************************************
    * toma cada bit e imprime el valor que le corresponde en la pantalla
    ***************************************************************************/
    int bit_number;
    for (bit_number=7; bit_number>=0; --bit_number)
    {
        printf("\nRegistro:%c\tBit:%d\tValor:%d\n",Port_A,bit_number,bitGet(Port_A,bit_number));
	       changeled(bit_number,bitGet(Port_A,bit_number));
    }
    printf ("\n");
}
