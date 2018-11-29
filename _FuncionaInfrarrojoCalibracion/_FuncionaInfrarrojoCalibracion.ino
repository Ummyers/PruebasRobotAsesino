/*  Facultad de Ciencias, UNAM
 *  @Autor Muñiz Patiño, Andrea Fernanda
 *  @Fecha 27/Novimebre/2018
 *  @versión 3.0
 *   
 *   12:30 am Funciona este programa para que se mantenga en una zona
 *   de un mismo color
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
int value = 120;
int valueGiro = 250;
int valueGiroLL = 200;
int valueAsesinar = 250;

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
  maxAr = maxAr + (maxAr * .05);
  maxAb = maxAb + (maxAb * .05);
  maxC = maxC + (maxC * .05);
    Serial.begin(9600);
}

void loop() {
  /*Comunicación Serial
   *  Serial.println("Sensor Arriba");
  Serial.println(minAr);
  Serial.println(maxAr);
  Serial.println("Sensor Abajo");
  Serial.println(minAb);
  Serial.println(maxAb);
  Serial.println("Sensor Central");
  Serial.println(minC);  
  Serial.println(maxC);
  delay(1000);
  
  sensorCentral = analogRead(infraCentral);
    if(sensorCentral > maxC){ 
       analogWrite(motor_p13, value);//ET
       analogWrite(motor_p12, 0);
       analogWrite(motor_p9, 0);
       analogWrite(motor_p10, value);//ET
    }
    //GIRA Y LUEGO RETROCEDE
   */
  sensorArriba = analogRead(infraArriba);
  sensorAbajo = analogRead(infraAbajo);
  
  if((sensorArriba > minAr)&&(sensorArriba < maxAr)&&(sensorAbajo > minAb)&&(sensorAbajo < maxAb)){  
   analogWrite(motor_p13, value);//ET
   analogWrite(motor_p12, 0);
   analogWrite(motor_p9, 0);
   analogWrite(motor_p10, value);//ET
  }else{ 
//Intentando dar vuelta sin un motor
   analogWrite(motor_p13, 0);
   analogWrite(motor_p12, 0);
   analogWrite(motor_p9, valueGiro);
   analogWrite(motor_p10, 0);

   analogWrite(motor_p13, value);
   analogWrite(motor_p12, 0);
   analogWrite(motor_p9, value);
   analogWrite(motor_p10, 0);
   
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
