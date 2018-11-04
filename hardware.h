#ifndef HARDWARE_H
#define HARDWARE_H
int changeled(unsigned int bit,unsigned int value);
//Se encarga de modificar los leds de la RASPBERRYPI

int expoutall(void);
//Se encarga de mandar todos los comandos necesarios para iniciar el uso de la RPI

void closeall(void);
//Se encarga de cerrar todos los punteros a file utlizados para la RPI
#endif
