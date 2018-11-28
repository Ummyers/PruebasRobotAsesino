/* Prueba de vuelo 37, 
* Muñiz Patiño Andrea Fernanda
* Ultima modificación, 23 de Noviembre. Revisar comentarios
* Se hicieron pruebas pues el pulso del trigger no se detectaba.
*/
//------------PINES-------------
//La salida del trigger es la misma para los dos sonares.
#define TRIGGER 19 
//Sonar localizado en el frente
#define ECHO 14
//Sonar localizado en la parte de atrás
#define ECHO2 15

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
int valueAsesinar = 200;
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
  /*
   * Si dejamos esta configuración de orden, detecta con los dos sensores pero
   * el intervalo de tiempo no es el correcto xD 
   */
  if(espera){
    //Debe esperar 5 segundos 
    delay(5000);
    espera = false; 
  }else{
    iniciarTrigger();
    //Si tenemos pegado el robot empujar lo mas que se pueda
    float distanciaFrente = calcularDistancia(true);
      float distanciaAtras = calcularDistancia(false);
    //El siguiente if es para cuando el robot esta demasiado cerca
   if((distanciaFrente >= 2.00)&&(distanciaFrente < 30.00)){
          empujar(true); 
    }   
    if((distanciaAtras >= 2.00)&&(distanciaAtras < 30.00)){
        empujar(false);
      }else{
        girar();
      }
  }//END espera de 5 segundos
}//END loop

//---------------METODOS AUXILIARES---------------------------
/* Método que intenta sacar al enemigo de la pista, aumentando la velocidad
 * @param boolean direccion
 * TRUE empuja hacia adelante
 * FALSE empuja hacia atrás
*/
 void empujar(boolean direccion){
  int a = 0;
  int b = 0;
  if(direccion){
    b = valueAsesinar;
  }else{
    a = valueAsesinar;
  }
    analogWrite(motor_p12, a);
    analogWrite(motor_p13, b);
    
    analogWrite(motor_p9, a);
    analogWrite(motor_p10, b);
    
}
/* Método GIRAR derecha/izquierda
*/
 void girar(){
      analogWrite(motor_p12, valueGiro);
      analogWrite(motor_p13, 0);      
      analogWrite(motor_p9, 0);
      analogWrite(motor_p10, valueGiro);  
      delay(100);
      //En vez de poner delay, hay que regular la velocidad
}
 
/*Devuelve un float que es el valor de la distancia de un objeto con respecto al robot
 * ----------------------------------------------------------------------------------
 * La función pulseIn obtiene el tiempo que tarda en cambiar entre estados.
 * Es decir mide el tiempo en que las onda repotan con el objeto y regresan al sensor. 
 * @param boolean sensor 
 * TRUE sensor delantero
 * FALSE sensor trasero 
 */
float calcularDistancia(boolean sensor){
  unsigned long tiempo; 
  //Si es el sensor delantero es ECHO pin 14
   if(sensor){
     tiempo = pulseIn(ECHO, HIGH ); 
  //Si es el sensor trasero es ECHO pin 15
   }else{
     tiempo = pulseIn(ECHO2, HIGH);
   }
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

