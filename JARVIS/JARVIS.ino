/* Facultad de Ciencias, UNAM
 *  @Autor Muñiz Patiño, Andrea Fernanda
 *  @Fecha 29/Noviembre/2018
 *  @versión FINAL
 *  COmpetencia de Robótica
 */
 //------------PINES-------------

//------------SONARES-----------
//La salida del trigger es la misma para los dos sonares.
#define TRIGGER 19 
//Sonar localizado en el frente
#define ECHO 14

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
//NOTA: Consultar EAGLE para dudas y aclaraciones

//-------Variables-------------
//Variable para calcular la distancia del robot enemigo
const float sonido = 34300.0;
int valueI = 120;
int valueGiroI = 120;
int valueGiroLLI = 250;

int valueGiro = 120;
int valueGiroLL = 250;
int valueAsesinar = 250;

int tiempoTornado = 0;

// Variables para la calibración
//float minAr = 1023.0;
//float maxAr = 0.0;

float minAb = 1023.0; 
float minC = 1023.0; 
float maxAb = 0.0; 
float maxC = 0.0;
float sensorValueAr, sensorValueAb, sensorValueC; 

float sensorArriba, sensorAbajo, sensorCentral;

void setup() {
  //Serial.begin(9600);
  pinMode(motor_p12, OUTPUT);  
  pinMode(motor_p13, OUTPUT);
  pinMode(motor_p9, OUTPUT);
  pinMode(motor_p10, OUTPUT);  
  
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(infraArriba, INPUT);
  pinMode(infraAbajo, INPUT);
  pinMode(infraCentral, INPUT);
  while (millis() < 4000) {
      calibrar();
    }//END Millis WHILE
    
    //-------------INCERTIDUMBRE
    // 01:03 se modifica a 3% la incertidumbre
    // 02:42 se modifica a 5% la incertidumbre, pinshe negro
 // maxAr = maxAr + (maxAr * .05);
  maxAb = maxAb + (maxAb * .05);
  maxC = maxC + (maxC * .05);
  
     /*
      * 
  Serial.println("Sensor Arriba");
  Serial.println(minAr);
  Serial.println(maxAr);
  Serial.println("Sensor Abajo");
  Serial.println(minAb);
  Serial.println(maxAb);
  Serial.println("Sensor Central");
  Serial.println(minC);  
  Serial.println(maxC);
  Serial.println("-----------------");
  delay(1000);
      */
}

void loop() {

  sensorArriba = analogRead(infraArriba);
  sensorAbajo = analogRead(infraAbajo);

  if((sensorAbajo > minAb)&&(sensorAbajo < maxAb)){ 
      //Serial.println("entro al primer if");
      iniciarTrigger();  
    //Si tenemos pegado el robot empujar lo mas que se pueda
    float distanciaFrente = calcularDistanciaFrente();
    //El siguiente if es para cuando el robot esta demasiado cerca
   if((distanciaFrente >= 2.00)&&(distanciaFrente < 33.00)){
          empujar(true); 
      }else{
        girar();
        tiempoTornado++;
        if(tiempoTornado >= 300){
          analogWrite(motor_p13, 80);
          analogWrite(motor_p12, 0);
          analogWrite(motor_p9, 80); 
          analogWrite(motor_p10, 0);
          tiempoTornado = 0;
        }
      }
    }else{ 
      //Retrocede y luego gira, para no caer xD supuestamente
      //Serial.println("entro al else"); 
     analogWrite(motor_p13, valueI);
     analogWrite(motor_p12, 0);
     analogWrite(motor_p9, valueI); 
     analogWrite(motor_p10, 0);
     
     analogWrite(motor_p13, 0);
     analogWrite(motor_p12, valueGiroLLI);
     analogWrite(motor_p9, valueGiroI);
     analogWrite(motor_p10, 0);
    }
  
}//END LOOP

//----------------METODOS AUXILIARES-------------------------
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
    delay(100);
    analogWrite(motor_p12, a);
    analogWrite(motor_p13, b);
    
    analogWrite(motor_p9, a);
    analogWrite(motor_p10, b);
    
    
}//END empujar

/* Método GIRAR derecha/izquierda
*/
  void girar(){
      analogWrite(motor_p12, valueGiroLL);
      analogWrite(motor_p13, 0);  
          
      analogWrite(motor_p9, 0);
      analogWrite(motor_p10, valueGiro);  
      //delay(300);
      //En vez de poner delay, hay que regular la velocidad
}//END girar

void calibrar(){
      //-------------SENSOR ABAJO--------------------
      sensorValueAb = analogRead(infraAbajo);     
       if (sensorValueAb > maxAb) {
        maxAb = sensorValueAb;
      }      
      // Registrar el valor mínimo del sensor
      if (sensorValueAb < minAb) {
        minAb = sensorValueAb;
      }
      //------------SENSOR CENTRAL-------------------
      int sensorValueC = analogRead(infraCentral);
      if (sensorValueC > maxC) {
        maxC = sensorValueC;
      }      
      // Registrar el valor mínimo del sensor
      if (sensorValueC < minC) {
        minC = sensorValueC;
      }
}//END calibrar

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
}//END iniciarTrigger



