const int RelePin = 4; // pino ao qual o Módulo Relé está conectado
int incomingByte;      // variavel para ler dados recebidos pela serial

void setup() {
  Serial.begin(115200); // inicializa a comunicação serial em 9600bps
  pinMode(RelePin, OUTPUT); // seta o pino como saída
  digitalWrite(RelePin, LOW); // seta o pino com nivel logico baixo
}

void loop() {
  if (Serial.available() > 0) {
    // verifica se tem algum dado na serial
    incomingByte = Serial.read();  //lê o primeiro dado do buffer da serial

    if (incomingByte == 'A') {     //se for A
      digitalWrite(RelePin, HIGH); //aciona o pino
    } 

    if (incomingByte == 'D') {     //se for D
      digitalWrite(RelePin, LOW);  //desativa o pino
    }
  }
}

