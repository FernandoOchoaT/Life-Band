#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

// Definición de pines
const int sensorPin = A0; // Pin analógico donde está conectado el sensor
const int LED_PIN = 2; // Pin para indicar detección de pulso (opcional)

// Variables globales
int sensorValue = 0; // Valor leído del sensor
int lastSensorValue = 0; // Último valor leído del sensor
unsigned long lastBeatTime = 0; // Tiempo del último latido
int threshold = 550; // Umbral para detectar un latido
int BPM = 0; // Frecuencia cardíaca en BPM
unsigned long lastMeasureTime = 0; // Tiempo de la última medición válida
const int MIN_BEAT_INTERVAL = 300; // Intervalo mínimo entre latidos en milisegundos (para evitar detecciones dobles)

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT); // Configura el pin del LED como salida
}

void loop() {
  sensorValue = analogRead(sensorPin); // Leer valor del sensor

  unsigned long currentTime = millis();
  
  // Si se detecta un latido
  if (sensorValue > threshold && lastSensorValue <= threshold) {
    unsigned long timeSinceLastBeat = currentTime - lastBeatTime;

    if (timeSinceLastBeat > MIN_BEAT_INTERVAL) { // Asegurarse de que no es un falso positivo
      lastBeatTime = currentTime;

      BPM = 60000 / timeSinceLastBeat; // Calcular BPM
      lastMeasureTime = currentTime;
      
      Serial.print("Frecuencia Cardiaca: ");
      Serial.print(BPM);
      Serial.println(" BPM");

      // Ejemplo de cómo indicar la detección de un latido con un LED (opcional)
      digitalWrite(LED_PIN, HIGH); // Enciende el LED
      delay(50); // Breve tiempo de encendido del LED
      digitalWrite(LED_PIN, LOW); // Apaga el LED
    }
  }

  // Si no se ha detectado un latido en los últimos 2 segundos, resetear el BPM
  if (currentTime - lastMeasureTime > 2000) {
    BPM = 0;
  }

  lastSensorValue = sensorValue; // Actualizar el último valor del sensor
  delay(100); // Pequeña pausa para estabilizar lecturas
}
