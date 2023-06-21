// Libreria y pines para el sensor de temperatura y ventilador
#include <dht.h>
dht DHT;
#define DHT11_PIN 8
char ventilador;
int PinVent = 2;

// Pines y variables para LEd
int G=13;
int B=11;
int R=12;
char Led;
int enc_led = 0;
char color;

// Pin y variables para alarma y sensor de distancia
char alarma;
const int PinTrig = 7;
const int PinEcho = 6;
const float VelSon = 34000.0;
float distancia;

//Pin y variables para sensor de humedad y riego con bomba
float humedad;
int PinHum = 5;
int PinBomba = 3;
char bomba;

void setup() {
  // Pines de tira led
  Serial.begin(9600);
  for(int i = 11;i<14;i++){
    pinMode(i,OUTPUT);
  }
  
  // Pin para ventilador
  pinMode(PinVent, OUTPUT);

  // Pin para bombaa
  pinMode(PinBomba, OUTPUT);

  // Pin para alarma 
  pinMode(4, OUTPUT);

  // Pines de sensor ultrasonico para distancia
  pinMode(PinTrig, OUTPUT);
  pinMode(PinEcho, INPUT);

  // Pin para lectura de humedad
  pinMode(PinHum, INPUT);

  // Pin para lectura de temperatura
  pinMode(8, INPUT);

  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(R,LOW);
  digitalWrite(G,LOW);
  digitalWrite(B,LOW);
  
}

void loop() {
  DHT.read11(DHT11_PIN);
  iniciarTrigger();
  unsigned long tiempo = pulseIn(PinEcho, HIGH);
  distancia = tiempo * 0.000001 * VelSon / 2.0;
  humedad = analogRead(5)*100/1024;
  
  // Control de ventilador
  ventilador = Serial.read();
  Serial.print(ventilador);
  Serial.print("\t");
  if(ventilador == '2')
  {
    digitalWrite(2,HIGH);
  }
  
  if(ventilador == '1')
  {
    digitalWrite(2,LOW);
  }

  // Control de bomba
  bomba = Serial.read();
  Serial.print(bomba);
  Serial.print("\t");
  if(bomba == '2')
  {
    digitalWrite(3,HIGH);
  }
  if(bomba == '1')
  {
    digitalWrite(3,LOW);
  }

  //Control de encendido de tira LED
  Led = Serial.read();
  Serial.print(Led);
  Serial.print("\t");
  if(Led == '1')
  {
    enc_led = 1;
   
  }
  if(Led == '2')
  {
    enc_led = 0;
    
  }

  // Control de color de tira LED
  color = Serial.read();
  Serial.print(color);
  Serial.print("\t");
  if(enc_led == 1)
  { 
    if(color == '1')
    {
      digitalWrite(R, LOW);
      digitalWrite(G, LOW);
      digitalWrite(B, HIGH);
    }
    if(color == '2')
    {
      digitalWrite(R, HIGH);
      digitalWrite(G, LOW);
      digitalWrite(B, LOW);
    }
  }
  if(enc_led == 0)
  {
    digitalWrite(R, LOW);
    digitalWrite(G, LOW);
    digitalWrite(B, LOW);
  }
  
  // Control de alarma
  alarma = Serial.read();
  Serial.print(alarma);
  Serial.print("\t");
  if(alarma == '1')
  {
    digitalWrite(4, HIGH);
  }
  if(alarma == '2')
  {
    digitalWrite(4, LOW);
  }

  // Imprimir valores de sensores
  Serial.print(DHT.temperature);
  Serial.print("\t"); 
  Serial.print(humedad);
  Serial.print("\t"); 
  Serial.println(distancia);
  delay(800);

}

// Rutina para sensor ultrasonico
void iniciarTrigger()
{
  // Ponemos el Triiger en estado bajo y esperamos 2 ms
  digitalWrite(PinTrig, LOW);
  delayMicroseconds(2);
  
  // Ponemos el pin Trigger a estado alto y esperamos 10 ms
  digitalWrite(PinTrig, HIGH);
  delayMicroseconds(10);
  
  // Comenzamos poniendo el pin Trigger en estado bajo
  digitalWrite(PinTrig, LOW);
}
