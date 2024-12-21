#include <Arduino.h>

// Definir los pines de los LEDs
#define D1 13
#define D2 12
#define D3 14
#define D4 27

#define D 2
#define LM35 34 // Definir el pin del sensor LM35

void setup() {
  // Configurar el pin del LM35 como entrada
  pinMode(LM35, INPUT);
  // Configurar los pines de los LEDs como salidas
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  //solo se usará como testigo
  pinMode(D, OUTPUT);
  

  // Inicializar comunicación serial para depuración
  Serial.begin(115200);
}

void loop() {

  // Leer el valor analógico del LM35
  int  analogo = analogRead(LM35);
  //led testigo
  digitalWrite(D, HIGH);
  delay(100);
  digitalWrite(D, LOW);
  delay(100);

  // Convertir el valor analógico a temperatura en grados Celsius
  float voltage = (analogo / 4095.0) * 3.3; // ESP32 tiene ADC de 12 bits y Vref de 3.3V
  float temperatura = voltage * 100.0; // LM35 proporciona 10mV por grado Celsius
  // Imprimir el valor analógico y el voltaje en el monitor serial
  Serial.print("Valor analógico: ");
  Serial.println(analogo);
  Serial.print("Voltaje: ");
  Serial.print(voltage);
  Serial.println(" V");
  // Imprimir la temperatura en el monitor serial
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");
  Serial.println("=====================================");

  // Controlar los LEDs según la temperatura
  if (temperatura >=0 && temperatura < 30.0) {
    digitalWrite(D1, HIGH);
    digitalWrite(D2, LOW);
    digitalWrite(D3, LOW);
    digitalWrite(D4, LOW);

  } else if (temperatura >= 30.0 && temperatura < 59.0) {
    digitalWrite(D1, LOW);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, LOW);
    digitalWrite(D4, LOW);
  } 
  else if (temperatura >= 60.0 && temperatura < 100.0) {
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D3, HIGH); //es la temperatur a ala que la mayoría de las vacterias muere igualmente no quieres tocar
    digitalWrite(D4, LOW);
  }
  else if (temperatura >= 100.0) {
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D3, LOW);
    digitalWrite(D4, HIGH); //Este led solo se enciende cuando la temperatura se ha elegvado a niveles críticos
    Serial.println("!ALERTA! No tocar");
    
  }

  // Esperar un segundo antes de la próxima lectura
  delay(100);
}