#include <WiFi.h>             // Biblioteca para conexão Wi-Fi
#include <HTTPClient.h>       // Biblioteca para envio de requisições HTTP

// =================== CONFIGURAÇÕES ===================

// Dados da rede Wi-Fi
const char* ssid     = "INTERNETNAME";      // Substitua pelo nome da sua rede Wi-Fi
const char* password = "INTERNETPASSWORD";  // Substitua pela senha da sua rede Wi-Fi

// Configurações do ThingSpeak
const char* server = "api.thingspeak.com";  // Endereço do servidor ThingSpeak
const char* apiKey = "APIKEY";              // Chave de API fornecida pelo ThingSpeak

// Definições de hardware
#define SENSOR_PIN   15     // Pino digital do ESP32 conectado ao sinal do sensor de fluxo
#define RELE_PIN      4     // Pino digital conectado ao relé

// Constantes do sensor
const float pulsesPerLiter    = 500.0;   // Pulsos por litro (definido pelo modelo do sensor, ajustar após calibração)
const unsigned long debounceMicros = 5000; // Debounce para ignorar pulsos falsos (5ms)
const float ThreshHold = 100.0;    // Limiar de vazão para acionar o relé (em L totais)

// Variáveis compartilhadas entre interrupção e loop principal
volatile unsigned long pulseCount      = 0;    // Contador de pulsos acumulados
volatile unsigned long lastPulseMicros = 0;    // Marca de tempo do último pulso válido

// Variáveis auxiliares para controle de tempo e medições
unsigned long lastReportMillis = 0;           // Última vez que o ThingSpeak foi atualizado

// =================== INTERRUPÇÃO ===================

// Função de interrupção para contar pulsos do sensor
void IRAM_ATTR pulseCounter() {
  unsigned long now = micros();                            // Captura o tempo atual em microssegundos
  if (now - lastPulseMicros >= debounceMicros) {           // Verifica se o tempo desde o último pulso é suficiente
    pulseCount++;                                           // Incrementa o contador de pulsos válidos
    lastPulseMicros = now;                                 // Atualiza o tempo do último pulso
  }
}

// =================== SETUP ===================

void setup() {
  Serial.begin(115200);                                    // Inicializa comunicação serial

  pinMode(SENSOR_PIN, INPUT_PULLUP);                       // Define o pino do sensor como entrada com pull-up
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), pulseCounter, RISING); // Configura interrupção no sinal do sensor

  pinMode(RELE_PIN, OUTPUT);                               // Define pino do relé como saída
  digitalWrite(RELE_PIN, HIGH);                            // Inicialmente o relé está desligado (depende da lógica do relé)

  // Conexão Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado!");
}

// =================== LOOP PRINCIPAL ===================

void loop() {
  // 1) Controle manual via Serial (teclando A ou D)
  if (Serial.available() > 0) {
    char cmd = Serial.read();                            // Lê comando recebido pela porta serial
    if (cmd == 'A') {
      digitalWrite(RELE_PIN, HIGH);                      // Liga o relé
      Serial.println("Relé LIGADO");
    } else if (cmd == 'D') {
      digitalWrite(RELE_PIN, LOW);                       // Desliga o relé
      Serial.println("Relé DESLIGADO");
    }
  }

  // 2) Envio ao ThingSpeak a cada 10 segundos
  unsigned long now = millis();
  if (now - lastReportMillis >= 10000) { // 10.000 ms = 10 s

    // Desativa interrupções temporariamente para leitura segura dos pulsos
    detachInterrupt(digitalPinToInterrupt(SENSOR_PIN));

    // Cálculo da vazão: (pulsos / pulses por litro) * 60 para obter L/min
    float flowRate = (pulseCount / pulsesPerLiter) * 60.0;

    // Acumula o volume total lido (litros)
    static float totalLitres = 0;
    totalLitres += pulseCount / pulsesPerLiter;

    // Aplica limiar mínimo para ignorar ruído
    if (flowRate < 0.1) flowRate = 0;

    // Ação automática no relé com base no fluxo
    if (totalLitres >= ThreshHold) {
      digitalWrite(RELE_PIN, HIGH);                      // Liga o relé (vazão anormal)
      Serial.println("Limiar atingido! Relé LIGADO");
    } else {
      digitalWrite(RELE_PIN, LOW);                       // Desliga o relé (uso normal)
      Serial.println("Abaixo do limiar. Relé DESLIGADO");
    }

    // Imprime no monitor serial os dados
    Serial.printf("Vazão: %.2f L/min  |  Volume Total: %.3f L\n", flowRate, totalLitres);

    // Monta a URL de envio ao ThingSpeak com os dados nos campos 1 e 2
    String url = String("http://") + server +
                 "/update?api_key=" + apiKey +
                 "&field1=" + String(flowRate, 2) +
                 "&field2=" + String(totalLitres, 3);

    // Envia os dados via HTTP GET
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(url);                    // Prepara a requisição
      int code = http.GET();             // Envia a requisição GET
      Serial.printf("ThingSpeak HTTP code: %d\n", code); // Mostra resposta (200 = sucesso)
      http.end();                        // Encerra conexão
    } else {
      Serial.println("Wi-Fi desconectado, pulando envio");
    }

    // Reseta o contador de pulsos para próxima medição
    pulseCount = 0;
    lastReportMillis = now;

    // Reativa interrupções
    attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), pulseCounter, RISING);
  }
}
