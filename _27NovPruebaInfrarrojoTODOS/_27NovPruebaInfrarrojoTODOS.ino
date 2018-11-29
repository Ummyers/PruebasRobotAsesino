/*  Facultad de Ciencias, UNAM
 *  @Autor Muñiz Patiño, Andrea Fernanda
 *  @Fecha 27/Novimebre/2018
 *  @versión 3.0
 *  
 *  Con este progama revise que las conexiones con los pines al
 *  circuito fueran correctos, con cada infrarrojo verifique
 *  que estuviera recibiendo una señal analogica.  
 *  
 *  12:35 intentare hacer el giro para el sentido contrario para ver si así jala
 *  02:58 no funciono JAJAJAJAJA
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
int valueI = 120;
int valueGiroI = 250;
int valueGiroLLI = 200;


// Variables para la calibración
float minAr = 1023.0;
float minAb = 1023.0; 
float minC = 1023.0; 
float maxAr = 0.0;
float maxAb = 0.0; 
float maxC = 0.0;
float sensorValueAr, sensorValueAb, sensorValueC; 

float sensorArriba, sensorAbajo, sensorCentral;

//-------------------SETUP------------------------
void setup() {
  pinMode(motor_p9, OUTPUT);
  pinMode(motor_p10, OUTPUT); 
  pinMode(motor_p12, OUTPUT);
  pinMode(motor_p13, OUTPUT); 

  pinMode(infraArriba, INPUT);
  pinMode(infraAbajo, INPUT);
  pinMode(infraCentral, INPUT); 
  while (millis() < 4000) {
      calibrar();
    }//END Millis WHILE
    //-------------INCERTIDUMBRE
    // 01:03 se modifica a 3% la incertidumbre
    // 02:42 se modifica a 5% la incertidumbre, pinshe negro
  maxAr = maxAr + (maxAr * .05);
  maxAb = maxAb + (maxAb * .05);
  maxC = maxC + (maxC * .05);
    Serial.begin(9600);
     //Comunicación Serial
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
}

void loop() {

  sensorArriba = analogRead(infraArriba);
  sensorAbajo = analogRead(infraAbajo);
 /*
  * Serial.print("SENSOR ARRIBA VALOR ");
  Serial.println(sensorArriba);
  Serial.print("SENSOR ABAJO VALOR ");
  Serial.println(sensorAbajo);
  */
   
  if((sensorAbajo > minAb)&&(sensorAbajo < maxAb)){ 
    //Serial.println("entro al primer if");
   analogWrite(motor_p13, valueI);//ET
   analogWrite(motor_p12, 0);
   analogWrite(motor_p9, 0);
   analogWrite(motor_p10, valueI);//ET
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
  //BETA (arriba) detecta parametros validos pero GAMMA no
  if((sensorArriba < maxAr)&&(sensorAbajo > maxAb)){
    //Serial.println("AQUIESTAEL...");
   analogWrite(motor_p13, 0);
   analogWrite(motor_p12, valueGiroLLI);
   analogWrite(motor_p9, valueGiroI);
   analogWrite(motor_p10, 0);
   //La siguiente linea no se usara en este programa segun los calculos
  }
  
}//END LOOP

//----------------METODOS AUXILIARES-------------------------

void calibrar(){
//---------------SENSOR ARRIBA----------------
      //Leer lo que el sensor arroje
      sensorValueAr = analogRead(infraArriba);
      // Registrar el valor máximo del sensor
      if (sensorValueAr > maxAr) {
        maxAr = sensorValueAr;
      }      
      // Registrar el valor mínimo del sensor
      if (sensorValueAr < minAr) {
        minAr = sensorValueAr;
      }
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
}

