/* Prueba de vuelo 37, 
* Muñiz Patiño Andrea Fernanda
* 18/Noviembre/2018
*/
//------------PINES-------------
//La salida del trigger es la misma para los dos sonares.
#define TRIGGER 19 
//Sonar localizado en el frente
#define ECHO 15
//Sonar localizado en la parte de atrás
#define ECHO2 14

//Arriba
#define motor_p12 12
#define motor_p13 13
//Abajo en la placa 
#define motor_p9 9
#define motor_p10 10
//Consultar EAGLE para dudas y aclaraciones

//-------Variables-------------
//Variable para calcular la distancia del robot enemigo
const float sonido = 34300.0;
int value = 70;
int valueGiro = 100;
int valueAsesinar = 150;
boolean espera = true;
/*
 * La comunicación serial es unicamente para las pruebas.
 */
void setup() {
  Serial.begin(9600);
  pinMode(motor_p12, OUTPUT);  
  pinMode(motor_p13, OUTPUT);
  pinMode(motor_p9, OUTPUT);
  pinMode(motor_p10, OUTPUT);
  
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(ECHO2, INPUT);
}

void loop() {
  iniciarTrigger();
  if(espera){
    delay(5000);
    espera = false; 
  }else{
    //Si tenemos pegado el robot empujar lo mas que se pueda
    float distanciaFrente = calcularDistanciaFrente();
    //El siguiente if es para cuando el robot esta demasiado cerca
   if((distanciaFrente > 2.00)&&(distanciaFrente < 30.00)){
          empujar(); 
      }else{
        girar();
      }
  } 
}


//---------------METODOS AUXILIARES---------------------------
/* Método que intenta sacar al enemigo de la pista
 * 
*/
 void empujar(){
    analogWrite(motor_p12, 0);
    analogWrite(motor_p13, valueAsesinar);
    analogWrite(motor_p9, 0);
    analogWrite(motor_p10, valueAsesinar);
}
/* Método GIRAR derecha/izquierda
*/
  void girar(){
      analogWrite(motor_p12, 0);
      analogWrite(motor_p13, 0);      
      analogWrite(motor_p9, 0);
      analogWrite(motor_p10, 0);  
      delay(100);
}
 
/*Devuelve un float que es el valor de la distancia de un objeto con respecto al robot
 * ----------------------------------------------------------------------------------
 */
float calcularDistanciaFrente(){
  // La función pulseIn obtiene el tiempo que tarda en cambiar entre estados, en este caso a HIGH
  unsigned long tiempo = pulseIn(ECHO, HIGH); 
  // Obtenemos la distancia en cm, hay que convertir el tiempo en segudos ya que está en microsegundos
  // por eso se multiplica por 0.000001
  float distancia = tiempo * 0.000001 * sonido / 2.0;
  Serial.print(distancia);
  Serial.print("cm");
  Serial.println();
  //delay(500);
  return distancia;
}
/*Metodo que inicia la secuencia del sonar
 * --------------------------------------------------
*/
void iniciarTrigger()
{
  // Ponemos el Trigger en estado bajo y esperamos 2 ms
  digitalWrite(TRIGGER, 0);
  delayMicroseconds(2);
  // Ponemos el pin Trigger a estado alto y esperamos 10 ms
  digitalWrite(TRIGGER, 1);
  delayMicroseconds(10);
  // Comenzamos poniendo el pin Trigger en estado bajo
  digitalWrite(TRIGGER, 0);
}

