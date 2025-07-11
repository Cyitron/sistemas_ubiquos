#include <WiFi.h>
#include <HTTPClient.h>

/* WiFi settings */
const char* ssid     = "Galaxya30sgabriel";
const char* password = "iham8066";

/* ThingSpeak settings */
const char* server = "api.thingspeak.com";
const char* apiKey = APIKEY;

#define SENSOR_PIN   15
#define RELE_PIN      4

const float pulsesPerLiter    = 500;     // Ajustar após calibração real
const unsigned long debounceMicros = 5000;
const float thresholdFlowRate = 66.0;

volatile unsigned long pulseCount      = 0;
volatile unsigned long lastPulseMicros = 0;

unsigned long lastReportMillis = 0;

void IRAM_ATTR pulseCounter() {
  unsigned long now = micros();
  if (now - lastPulseMicros >= debounceMicros) {
    pulseCount++;
    lastPulseMicros = now;
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(SENSOR_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), pulseCounter, RISING);

  pinMode(RELE_PIN, OUTPUT);
  digitalWrite(RELE_PIN, HIGH);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
}

void loop() {
  // 1) Leitura da Serial em "tempo real"
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    if (cmd == 'A') {
      digitalWrite(RELE_PIN, HIGH);
      Serial.println("Relé LIGADO");
    }
    else if (cmd == 'D') {
      digitalWrite(RELE_PIN, LOW);
      Serial.println("Relé DESLIGADO");
    }
  }

  // 2) Envio ao ThingSpeak a cada 10 s
  unsigned long now = millis();
  if (now - lastReportMillis >= 10000) {
    // suspende interrupção para leitura segura dos pulsos
    detachInterrupt(digitalPinToInterrupt(SENSOR_PIN));

    // calcula vazão e volume
    float flowRate    = (pulseCount / pulsesPerLiter) * 60.0;  // L/min
    static float totalLitres = 0;
    totalLitres      += pulseCount / pulsesPerLiter;

    // Aplica um limiar mínimo para ruído (opcional)
    if (flowRate < 0.1) flowRate = 0;

    // Aciona o relé se ultrapassar o limite configurado
    if (flowRate >= thresholdFlowRate) {
      digitalWrite(RELE_PIN, HIGH);
      Serial.println("Limiar atingido! Relé LIGADO");
    } else {
      digitalWrite(RELE_PIN, LOW);
      Serial.println("Abaixo do limiar. Relé DESLIGADO");
    }

    // debug serial
    Serial.printf("Flow rate: %.2f L/min  |  Total: %.3f L\n", flowRate, totalLitres);

    // monta URL e envia
    String url = String("http://") + server +
                 "/update?api_key=" + apiKey +
                 "&field1=" + String(flowRate, 2) +
                 "&field2=" + String(totalLitres, 3);

    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(url);
      int code = http.GET();
      Serial.printf("ThingSpeak HTTP code: %d\n", code);
      http.end();
    } else {
      Serial.println("WiFi desconectado, pulando envio");
    }

    // reseta o contador e reativa a interrupção
    pulseCount = 0;
    lastReportMillis = now;
    attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), pulseCounter, RISING);
  }
}
