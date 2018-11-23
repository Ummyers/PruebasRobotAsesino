## PruebasRobotAsesino
El repositorio es para las pruebas del programa final para la competencia de minisumo.

Se esta usando MSP-EXP430G2553 de la fabrica Texas Instruments

Asi como los siguientes componentes: 

* item 1 Un regulador LD33V que convierte 5V a 3.3V el cual usa un condensador #104 (100 nanofaradios) que se conecta entre la entrada del voltaje y GND, un condensador de 10 microfaradios que va de la salida del voltaje a GND. 

* item 2 Un regulador L7805CV que convierte 12V a 5V el cual usa un condensador #104 que va entre la salida y GND, un condensador #334 que es de 330 nanofaradios que se conecta con GND y la entrada de voltaje. 

* item 3 Para controlar los motores usamos un driver L293D, 
ETC...


Algunas especificaciones del MSP:

El pin 1 es VCC que debe recibir a lo mas 3.3 Volts del pin 1 al 16 va un condensador de 1 nanoFaradio, del pin 16 al 20, una resistencia de 47K.
