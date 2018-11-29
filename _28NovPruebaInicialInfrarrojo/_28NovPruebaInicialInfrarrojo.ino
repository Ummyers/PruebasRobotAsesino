/*  Facultad de Ciencias, UNAM
 *  @Autor Muñiz Patiño, Andrea Fernanda
 *  @Fecha 27/Novimebre/2018
 *  @versión 3.0
 *  
 *  Con este progama revise que las conexiones con los pines al
 *  circuito fueran correctos, con cada infrarrojo verifique
 *  que estuviera recibiendo una señal analogica.  
 * 
 * Esquema del ROBOT
 *                      LLANTA 
 * ---------------------------
 * - beta                    -
 * -                         -
 * -                         -
 * -                       alfa
 * -                         -
 * -                         -
 * - gamma                   -
 * ---------------------------
 *                      LLANTA
 * 
 * 
 */
//Probando los infrarrojos
#define motor_p9 9
#define motor_p10 10
#define motor_p12 12
#define motor_p13 13

//---------INFRARROJOS------------
//Infrarrojo Arriba BETA
#define infraArriba 5
//Infrarrojo Abajo GAMMA
#define infraAbajo  2
//Infrarrojo Cental ALFA
#define infraCentral 7

//-----------VARIABLES-------------
//Se usaran cuando pasemos a PWD para la velocidad de los motores
int value = 150;
int valueGiro = 100;
int valueAsesinar = 150;
// Variables para la calibración
int sensorMin = 1023; 
int sensorMax = 0;
int sensorArriba, sensorAbajo, sensorCentral;

void setup() {
  pinMode(motor_p9, OUTPUT);
  pinMode(motor_p10, OUTPUT); 
  pinMode(motor_p12, OUTPUT);
  pinMode(motor_p13, OUTPUT); 

  pinMode(infraArriba, INPUT);
  pinMode(infraAbajo, INPUT);
  pinMode(infraCentral, INPUT); 
}

void loop() {
  while (millis() < 5000) {
      //Leer lo que el sensor arroje
     int sensorValue = analogRead(infraArriba);
      // Registrar el valor máximo del sensor
      if (sensorValue > sensorMax) {
        sensorMax = sensorValue;
      }      
      // Registrar el valor mínimo del sensor
      if (sensorValue < sensorMin) {
        sensorMin = sensorValue;
      }
    }

  sensorArriba = analogRead(infraArriba);
  sensorAbajo = analogRead(infraAbajo);
  sensorCentral = analogRead(infraCentral);

  if((sensorArriba > sensorMin)&&(sensorArriba < sensorMax)){  
   analogWrite(motor_p13, value);
   analogWrite(motor_p12, 0);
   analogWrite(motor_p9, 0);
   analogWrite(motor_p10, value);
  }else{ 
   analogWrite(motor_p13, 0);
   analogWrite(motor_p12, 0);
   analogWrite(motor_p9, 0);
   analogWrite(motor_p10, 0);
  }
}//END LOOP
