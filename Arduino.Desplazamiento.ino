#include <Arduino.h>

const int LED_PIN = 13;
byte estadoLed = 0;
int contador = 0;
int varInt = 12;          
byte varByte = 10;        
long varLong = 100000L;
float varFloat = 3.1416;
bool varBool = true;

void imprimirBinario(byte valor) {
  for (int i = 7; i >= 0; i--) {
    Serial.print(bitRead(valor, i)); 
  }
  Serial.println();
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);

  Serial.println("--- Resultados Operaciones Bitwise ---");
  
  Serial.print("AND (00001100 & 00001010):      "); 
  imprimirBinario(varInt & varByte); 
  
  Serial.print("OR  (00001100 | 00001010):      "); 
  imprimirBinario(varInt | varByte); 
  
  Serial.print("XOR (00001100 ^ 00001010):      "); 
  imprimirBinario(varInt ^ varByte); 
  
  Serial.print("NOT (~00001010):                "); 
  imprimirBinario(~varByte);   
  
  Serial.print("Shift L (00001010 << 1):        "); 
  imprimirBinario(varByte << 1);     
  
  Serial.println("-----------------------------------------------");

  estadoLed = estadoLed | (1 << 0);
}

void loop() {
  estadoLed = estadoLed ^ 0b00000001;
  if ((estadoLed & 1) == 1) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  delay(500);
  contador = (contador + 1) % 8;
  Serial.print("Desplazamiento (1 << ");
  Serial.print(contador);
  Serial.print("): ");
  Serial.println(1 << contador);
  delay(500);
  
}
