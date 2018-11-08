/* Prueba para motores con el sensor infrarrojo en el pin 2,5,6,7
* Muñiz Patiño Andrea Fernanda
* Versión 1.0
* Sobre la práctica: 
* Sensor infrarrojo, que dado el valor del sensor mueve el motor. 
*/
#define motor1 13
#define motor2 12

#define segMotor1 9
#define segMotor2 10

#define sensor 2 //Pin de lectura analogica
//Cuando hago lecturas analogicas no puedo usar los pines 3,4. 
int valor;

void setup() {
  pinMode(sensor, INPUT);
  
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  
  pinMode(segMotor1, OUTPUT);
  pinMode(segMotor2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  valor = analogRead(sensor);
/*Dado el valor del infrarrojo será el sentido de las llantas
 * Se esta usando analogWrite para darle la velocidad a las llantas
*/
  Serial.println(valor);
  delay(500);
  if(valor < 200){
     analogWrite(motor1, 0);
     analogWrite(motor2, 50);
     delay(10);
     
     //OTRO MOTOR
     digitalWrite(9,0);
     digitalWrite(10,1);
     
  }else{
     analogWrite(13, 50);
     analogWrite(12, 0);
     //OTRO MOTOR
     digitalWrite(9,1);
     digitalWrite(10,0);
  }
  
}
