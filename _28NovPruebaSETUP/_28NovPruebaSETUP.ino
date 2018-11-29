/* 
 *   Facultad de Ciencias, UNAM
 *  @Autor Muñiz Patiño, Andrea Fernanda
 *  @Fecha 28/Novimebre/2018
 *  @versión 3.0
*                        LLANTA
* -----------------------------
* -                           - 
* -                           -
* -S P                      S P         
* -O I                      O I
* -N N                      N N
* -A 1                      A 1
* -R 4                      R 5
* -                           - 
* -                           - 
* ------------------------------
*                         LLANTA                        
*/
//------------PINES-------------
//La salida del trigger es la misma para los dos sonares.
#define TRIGGER 19 
//Sonar localizado en el frente
#define ECHO 14
//Sonar localizado en la parte de atrás

//---------INFRARROJOS------------
//Infrarrojo Arriba BETA
#define infraArriba 5
//Infrarrojo Abajo GAMMA
#define infraAbajo  2
//Infrarrojo Cental ALFA
#define infraCentral 7

//-----------MOTORES---------------
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
int valueGiro = 75;
/* El motor de los pines 11 y 12
 * esta chueco por lo cual hay que compensar la falta de fuerza 
 * para eso la nueva variable
 */
int valueGiroLL = 150;
int valueAsesinar = 120;

void setup() {
  Serial.begin(9600);
  pinMode(motor_p12, OUTPUT);  
  pinMode(motor_p13, OUTPUT);
  pinMode(motor_p9, OUTPUT);
  pinMode(motor_p10, OUTPUT);  
  
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(infraArriba, INPUT);
  pinMode(infraAbajo, INPUT);
  pinMode(infraCentral, INPUT); 
  //PODEMOS hacer la calibración aqui
  //---------------------------------
  
  delay(3000);
}

void loop() {
  iniciarTrigger();  
    //Si tenemos pegado el robot empujar lo mas que se pueda
    float distanciaFrente = calcularDistanciaFrente();
    //El siguiente if es para cuando el robot esta demasiado cerca
    //SE DISMINUYE EL INTEVALO PARA PRUEBA D GIRO
   if((distanciaFrente >= 2.00)&&(distanciaFrente < 33.00)){
          empujar(true); 
      }else{
        girar();
      }
}//END LOOP


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
      analogWrite(motor_p12, valueGiroLL);
      analogWrite(motor_p13, 0);  
          
      analogWrite(motor_p9, 0);
      analogWrite(motor_p10, valueGiro);  
      delay(100);
      //En vez de poner delay, hay que regular la velocidad
}
 
/*Devuelve un float que es el valor de la distancia de un objeto con respecto al robot
 * ----------------------------------------------------------------------------------
 */
float calcularDistanciaFrente(){
  // La función pulseIn obtiene el tiempo que tarda en cambiar entre estados, en este caso a HIGH
  unsigned long tiempo = pulseIn(ECHO, HIGH ); 
  // Obtenemos la distancia en cm, hay que convertir el tiempo en segudos ya que está en microsegundos
  // por eso se multiplica por 0.000001
  float distancia = tiempo * 0.000001 * sonido / 2.0;
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

