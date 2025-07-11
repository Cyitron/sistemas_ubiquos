# Monitoramento de Vazão com ESP32 e Envio para ThingSpeak

Este projeto utiliza um ESP32 para monitorar a vazão de água por meio de um sensor de fluxo, controlar um relé com base em um volume acumulado e enviar os dados para a plataforma ThingSpeak a cada 10 segundos. Abaixo estão as explicações das partes principais do código.

## Bibliotecas

- `WiFi.h`: Responsável pela conexão do ESP32 à rede Wi-Fi.
- `HTTPClient.h`: Usada para enviar requisições HTTP ao servidor ThingSpeak.

## Configurações

- `ssid` e `password`: Devem ser preenchidos com os dados da sua rede Wi-Fi.
- `server`: Endereço do servidor ThingSpeak.
- `apiKey`: Chave de API do seu canal ThingSpeak.
- `SENSOR_PIN`: Pino conectado ao sensor de vazão.
- `RELE_PIN`: Pino conectado ao relé.
- `pulsesPerLiter`: Define quantos pulsos equivalem a 1 litro, baseado no modelo do sensor.
- `debounceMicros`: Tempo mínimo entre pulsos para evitar contagens falsas por ruído.
- `ThreshHold`: Volume em litros que, ao ser atingido, aciona o relé automaticamente.

## Variáveis Importantes

- `pulseCount`: Total de pulsos válidos registrados (via interrupção).
- `lastPulseMicros`: Marca de tempo do último pulso registrado.
- `lastReportMillis`: Controla o intervalo entre os envios de dados ao servidor.
- `totalLitres`: Volume acumulado de água medido desde o início.

## Interrupção

A função `pulseCounter()` é chamada automaticamente a cada pulso detectado no sensor. Para evitar leituras erradas por ruído elétrico, o tempo entre pulsos é verificado usando `debounceMicros`.

## Setup

- Inicializa a comunicação serial.
- Configura os pinos do sensor e do relé.
- Estabelece conexão com o Wi-Fi.
- Ativa a interrupção no pino do sensor.

## Loop Principal

- Verifica se há comandos via porta serial:
  - `A`: Liga o relé.
  - `D`: Desliga o relé.
- A cada 10 segundos:
  - Desativa a interrupção para leitura segura do contador.
  - Calcula a vazão instantânea (L/min).
  - Atualiza o volume acumulado.
  - Compara o volume com o limiar para acionar ou desligar o relé automaticamente.
  - Envia os dados para o ThingSpeak nos campos `field1` (vazão) e `field2` (volume total).
  - Reseta o contador de pulsos e reativa a interrupção.

## Considerações

- Calibre corretamente o valor de `pulsesPerLiter` para garantir a precisão das leituras.
- Certifique-se de que o canal no ThingSpeak tenha pelo menos dois campos configurados.
- O relé pode ser usado para acionar alarmes, válvulas ou sistemas de aviso com base no volume de água medido.
