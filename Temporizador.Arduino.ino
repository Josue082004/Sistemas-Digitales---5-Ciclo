struct Analizador {
  int pin;
  bool estadoAnterior;
  unsigned long tiempoUltimoCambio;
  unsigned long tHigh, tLow;
  float frecuencia, dutyCycle;

  Analizador(int p) : pin(p), estadoAnterior(LOW), tiempoUltimoCambio(0), tHigh(0), tLow(0), frecuencia(0), dutyCycle(0) {}

  void procesar() {
    bool estadoActual = digitalRead(pin);

    // Algoritmo 1: Detección de flancos
    if (estadoActual != estadoAnterior) {
      unsigned long tiempoActual = micros();
      unsigned long duracion = tiempoActual - tiempoUltimoCambio;

      if (estadoAnterior == HIGH) { 
        // Acaba de pasar de HIGH a LOW -> Terminó el tiempo en ALTO
        tHigh = duracion;
      } else { 
        // Acaba de pasar de LOW a HIGH -> Terminó el tiempo en BAJO
        tLow = duracion;
        
      //Algoritmo 2 y 3: Cálculo de Periodo y Frecuencia (en el flanco ascendente
        unsigned long periodo = tHigh + tLow;
        if (periodo > 0) {
          frecuencia = 1000000.0 / periodo;
          dutyCycle = (tHigh * 100.0) / periodo;
        }
      }
      tiempoUltimoCambio = tiempoActual;
      estadoAnterior = estadoActual;
    }
  }
};

Analizador canal555(2);
Analizador canalFF(3); 

unsigned long cronometroVisualizacion = 0;

void setup() {
  Serial.begin(115200);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  Serial.println("Freq555: Duty555: FreqFF: DutyFF:"); 
}

void loop() {
  // Algoritmo 5: Ejecución multicanal
  canal555.procesar();
  canalFF.procesar();
  if (millis() - cronometroVisualizacion > 200) {
    // Canal 1
    Serial.print(canal555.frecuencia); Serial.print(" ");
    Serial.print(canal555.dutyCycle);   Serial.print(" ");
    // Canal 2
    Serial.print(canalFF.frecuencia);   Serial.print(" ");
    Serial.println(canalFF.dutyCycle);
    
    cronometroVisualizacion = millis();
  }
}