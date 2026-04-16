const int LED_PINS[] = {2, 3, 4, 5, 6, 7};
const int NUM_LEDS = 6;
const int BOTON_PIN = 8;

int patronActual = 0;           
bool ultimoEstadoBoton = LOW;   
unsigned long ultimoTiempoDebounce = 0; 
const unsigned long tiempoDebounce = 50; 

bool cambiarPatron = false;

void setup() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
  pinMode(BOTON_PIN, INPUT);
}

void loop() {
  cambiarPatron = false; 
  switch (patronActual) {
    case 0: patronSecuencia();      break;
    case 1: patronCarrusel();       break;
    case 2: patronParpadeo();       break;
    case 3: patronAleatorio();      break;
    case 4: patronOndaAscendente(); break;
  }
}

void leerBoton() {
  bool estadoBoton = digitalRead(BOTON_PIN);
  
  if (estadoBoton == HIGH && ultimoEstadoBoton == LOW) {
    if ((millis() - ultimoTiempoDebounce) > tiempoDebounce) {
      patronActual++;
      if (patronActual > 4) patronActual = 0;
      
      cambiarPatron = true; 
      apagarTodos();
      ultimoTiempoDebounce = millis();
    }
  }
  ultimoEstadoBoton = estadoBoton;
}

void apagarTodos() {
  for (int i = 0; i < NUM_LEDS; i++) digitalWrite(LED_PINS[i], LOW);
}

void pausaInteractiva(int ms) {
  unsigned long inicio = millis();
  while (millis() - inicio < ms) {
    leerBoton();
    if (cambiarPatron) break;
  }
}

void patronSecuencia() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (cambiarPatron) return;
    digitalWrite(LED_PINS[i], HIGH);
    pausaInteractiva(150);
    digitalWrite(LED_PINS[i], LOW);
  }
}

void patronCarrusel() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (cambiarPatron) return;
    digitalWrite(LED_PINS[i], HIGH);
    if (i > 0) digitalWrite(LED_PINS[i-1], LOW);
    else digitalWrite(LED_PINS[NUM_LEDS-1], LOW);
    pausaInteractiva(150);
  }
  if (!cambiarPatron) digitalWrite(LED_PINS[NUM_LEDS-1], LOW);
}

void patronParpadeo() {
  int contador = 0;
  while (contador < 3) {
    if (cambiarPatron) return;
    for (int i = 0; i < NUM_LEDS; i++) digitalWrite(LED_PINS[i], HIGH);
    pausaInteractiva(250);
    
    if (cambiarPatron) return;
    for (int i = 0; i < NUM_LEDS; i++) digitalWrite(LED_PINS[i], LOW);
    pausaInteractiva(250);
    contador++;
  }
}

void patronAleatorio() {
  if (cambiarPatron) return;
  int r = random(0, NUM_LEDS);
  digitalWrite(LED_PINS[r], HIGH);
  pausaInteractiva(100);
  digitalWrite(LED_PINS[r], LOW);
}

void patronOndaAscendente() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (cambiarPatron) return;
    digitalWrite(LED_PINS[i], HIGH);
    pausaInteractiva(100);
  }
  for (int i = NUM_LEDS - 1; i >= 0; i--) {
    if (cambiarPatron) return;
    digitalWrite(LED_PINS[i], LOW);
    pausaInteractiva(100);
  }
}