/* Prueba de vuelo 37, dia tercero configuración atrasado.
* Muñiz Patiño Andrea Fernanda
* Versión 1.0
* Sobre la práctica: 
* Consiste en usar el sensor sonar, para determinar la distancia a un objeto.
*/
#define TRIGGER 19 
#define ECHO 15

const float sonido = 34300.0;

void setup() {
  //La velocidad en la que se puede comunicar con el MSP
  Serial.begin(9600);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  
}

void loop() {
  iniciarTrigger();
  //calcularDistancia();
}

void calcularDistancia()
{
  // La función pulseIn obtiene el tiempo que tarda en cambiar entre estados, en este caso a HIGH
  unsigned long tiempo = pulseIn(ECHO, HIGH,30000); 
  // Obtenemos la distancia en cm, hay que convertir el tiempo en segudos ya que está en microsegundos
  // por eso se multiplica por 0.000001
  //float distancia = tiempo * 0.000001 * sonido / 2.0;
  float distancia = tiempo/58;
    Serial.println(tiempo);
  //Veremos que pasa con el tiempo.
  Serial.print(distancia);
  Serial.print("cm");
  Serial.println();
  delay(50);
 
  //return distancia;
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
 
}



