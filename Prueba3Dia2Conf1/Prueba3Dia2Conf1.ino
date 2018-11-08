/* Prueba 3 dia 2 configuracion 1.0 
* Muñiz Patiño Andrea Fernanda
* Sobre la práctica: 
* Consiste en probar el sonar xD
*/
#define TRIGGER 19
#define ECHO 15
//Para probar los motores

#define motor1 5
#define motor2 7
//#define LED 7
const float sonido = 34300.0;

void setup() {
  //La velocidad en la que se puede comunicar con el MSP
  Serial.begin(9600);
  
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
 // pinMode(LED, OUTPUT);
}

void loop() {
  iniciarTrigger();
  float distancia = calcularDistancia();
  if( distancia < 20.0 && distancia >= 10.0){
    prenderMotores();
  }
}

//----------------------METODOS------------------------------
//Prende el motor en la dirección indicada
void prenderMotores(){
     digitalWrite(14,0);
     digitalWrite(19,1);
}

//Devuelve un float
float calcularDistancia()
{
  // La función pulseIn obtiene el tiempo que tarda en cambiar entre estados, en este caso a HIGH
  unsigned long tiempo = pulseIn(ECHO, HIGH); 
  // Obtenemos la distancia en cm, hay que convertir el tiempo en segudos ya que está en microsegundos
  // por eso se multiplica por 0.000001
  float distancia = tiempo * 0.000001 * sonido / 2.0;
  Serial.print(distancia);
  Serial.print("cm");
  Serial.println();
  delay(500);
 
  return distancia;
}

//Metodo que inicia la secuencia pertinente del sonar
void iniciarTrigger()
{
  // Ponemos el Triiger en estado bajo y esperamos 2 ms
  digitalWrite(TRIGGER, 0);
  delayMicroseconds(2);
 
  // Ponemos el pin Trigger a estado alto y esperamos 10 ms
  digitalWrite(TRIGGER, 1);
  delayMicroseconds(10);
 
  // Comenzamos poniendo el pin Trigger en estado bajo
  digitalWrite(TRIGGER, 0);
}

