/* Prueba de vuelo 37, quinto día, configuracion, el torneo se recorrio
*  9 de Nociembre del 2018
*  Semestre 2019-1
*  Los pines de los motores van de acuerdo a la orientación del MSP, estan alineados con el MSP
*/

//Arriba

#define motor_p12 12
#define motor_p13 13
//Abajo en la placa 
#define motor_p9 9
#define motor_p10 10

int value = 30; //Velocidad del motor
int valueGiro = 50; //Velocidad necesaria para girar

void setup() {
  pinMode(motor_p12, OUTPUT);  
  pinMode(motor_p13, OUTPUT);
  pinMode(motor_p9, OUTPUT);
  pinMode(motor_p10, OUTPUT);

}

void loop() {
  delay(200);
  //Sirve para dar vueltas :D 
  analogWrite(motor_p12, 0);
  analogWrite(motor_p13, valueGiro);
  analogWrite(motor_p9, valueGiro);
  analogWrite(motor_p10, 0);

  delay(100);

  //Ir derecho 
    analogWrite(motor_p12, 0);
  analogWrite(motor_p13, value);

  analogWrite(motor_p9, 0);
  analogWrite(motor_p10, value);

  delay(100);
  
  //Ir de reversa
    analogWrite(motor_p12, value);
  analogWrite(motor_p13, 0);

  analogWrite(motor_p9, value);
  analogWrite(motor_p10, 0);
}
