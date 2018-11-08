/* Prueba 2.0
* Muñiz Patiño Andrea Fernanda
* Versión 1.0
* Sobre la práctica: 
* Integrando el sensor sonar y otro sensor infrarrojo. 
*/
#define motor1 5
#define motor2 7
#define segMotor1 14
#define segMotor2 19
#define sensor1 6 //Pin de lectura analogica
#define sensor2 2 //Pin de lectura analogica
//Cuando hago lecturas analogicas no puedo usar los pines 3,4. 
int valor;

void setup() {
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(segMotor1, OUTPUT);
  pinMode(segMotor2, OUTPUT);
  Serial.begin(9600);
}

//No se toma aún a consideración el sensor 2
void loop() {
  valor = analogRead(sensor1);
  Serial.println(valor);
  delay(500);
  if(valor < 50){
     digitalWrite(5, 0);
     digitalWrite(7, 1);
     //OTRO MOTOR
     digitalWrite(14,0);
     digitalWrite(19,1);
     
     
  }else{
     digitalWrite(5, 1);
     digitalWrite(7, 0);
     //OTRO MOTOR
     digitalWrite(14,1);
     digitalWrite(19,0);
  }
  
}
