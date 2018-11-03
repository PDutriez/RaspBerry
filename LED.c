/*******************************************************************************
 * Liberías utilizadas
 ******************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include "puerto.h"
#include "LED.h"

/*******************************************************************************
 * variables propias de este archivo
 ******************************************************************************/
static int input;
/******************************************************************************/

/*******************************************************************************
 * función principal, analiza el input y responde segun corresponda
 ******************************************************************************/
int main ()
{
    printf ("Ingrese el numero de LED o el comando\n");
    while ((input= getchar ()) != 'q' && input != 'Q')
    {
        /***********************************************************************
        * primero revisa se se trata de un numero de led
        ***********************************************************************/
        if((input <= '9') && (input >= '0'))
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
        else if ((input == 't') || (input == 'T'))
        {
            maskToggle ('a', MASK);
            show_port ('a');
        }
        /***********************************************************************
        * si se presiona la letra 'S' prende todos los bits
        ***********************************************************************/
        else if ((input == 's') || (input == 'S'))
        {
            maskOn ('a', MASK);
            show_port ('a');
        }
        /***********************************************************************
        * si se presiona la letra 'C' apaga todos los bits
        ***********************************************************************/
        else if ((input == 'c') || (input == 'C'))
        {
            maskOff ('a', MASK);
            show_port ('a');
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
    for (int bit_number=7; bit_number>=0; --bit_number)
    {
        printf("\nRegistro:%c\tBit:%d\tValor:%d\n",Port_A,bit_number,bitGet(Port_A,bit_number));
    }
    printf ("\n");
}
