/* Pines de los sensores  2,5,6,7
* Muñiz Patiño Andrea Fernanda
* Sobre la práctica: 
* Calibrando sensores infrarrojos
*/
#define sensor 5 //Pin de lectura analogica
//Cuando hago lecturas analogicas no puedo usar los pines 3,4. 
int valor;

void setup() {
  pinMode(sensor, INPUT);
  Serial.begin(9600);
}

void loop() {
  valor = analogRead(sensor);
  Serial.println(valor);
  delay(50);
  
}
