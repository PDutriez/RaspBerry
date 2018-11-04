#ifndef HARDWARE_H
#define HARDWARE_H
void ledon(unsigned int bit);//Se encarga de prender los leds de la RASPBERRYPI
void ledoff(unsigned int bit);//Se encarga de apagar los leds de la RASPBERRYPI
int createall(void);//Se encara de crear strings de las linias de comando de los leds
int expoutall(void);//Se encarga de mandar todos los comandos necesarios para iniciar el uso de la RPI
void closeall(void);//Se encarga de cerrar todos los punteros a file utlizados para la RPI
#endif
