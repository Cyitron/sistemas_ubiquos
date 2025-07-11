# Sistema de Monitoramento de Fluxo d’Água na Rede de Fornecimento Residencial para Detecção de Vazamentos e Desperdício de Água

## 1. Título do Projeto
**Sistema de Monitoramento de Fluxo d’Água na Rede de Fornecimento na Entrada de Residências para Detecção de Vazamentos e Desperdício de Água**

## 2. Introdução

### 2.1 Apresentação Geral do Problema e Área de Estudo
Residências, condomínios e demais edificações contam com extensas redes de tubulação para o fornecimento de água potável. Essas estruturas estão constantemente expostas à ação do tempo, variações de temperatura e à própria erosão causada pela passagem da água, o que favorece o surgimento de falhas e vazamentos ao longo do tempo. Em muitos casos, esses problemas ocorrem de forma silenciosa e progressiva, dificultando sua detecção imediata. Como consequência, a identificação de vazamentos costuma ocorrer apenas após o recebimento de uma conta de água anormalmente elevada, ou de forma subjetiva, por observações casuais dos moradores. Essa abordagem tardia e imprecisa pode levar a prejuízos financeiros e ao desperdício de um recurso essencial.

### 2.2 Objetivo Geral do Projeto
Este projeto tem como objetivo desenvolver um sistema automatizado para detecção de vazamentos na rede de fornecimento de água de residências, utilizando sensores de fluxo para coletar dados em tempo real. Através da análise de variações anômalas no padrão de consumo, o sistema visa oferecer uma resposta precisa e assertiva quanto à existência de possíveis vazamentos. Com essas informações, será possível acionar profissionais para manutenção corretiva de forma mais ágil e eficiente, contribuindo para a redução do desperdício de água e a prevenção de prejuízos.

## 3. Motivação

### 3.1 Justificativa para o Desenvolvimento do Projeto
Este projeto surge a partir das dificuldades enfrentadas por moradores do litoral norte do Rio Grande do Sul que possuem casas de veraneio. Esses proprietários geralmente passam apenas algumas semanas por ano em suas residências litorâneas, permanecendo o restante do tempo no interior do estado. Caso ocorra um vazamento ou rompimento de cano durante a ausência, o deslocamento fora de temporada para resolver o problema pode exigir centenas de quilômetros de viagem, além de causar grandes desperdícios e prejuízos. A proposta visa evitar esse cenário, permitindo que o problema seja identificado remotamente e solucionado com agilidade.

### 3.2 Relevância do Tema e Problemas que Pretende Resolver
A proposta é relevante enquanto o desperdício de água continuar sendo uma preocupação crítica para a sociedade. Ao possibilitar a detecção automatizada e remota de vazamentos, o sistema pretende reduzir significativamente a perda de água potável, que pode atingir milhares de litros por dia em casos não identificados. Além disso, transfere a responsabilidade de monitoramento do usuário para um sistema automatizado, evitando prejuízos econômicos e permitindo decisões mais assertivas.

### 3.3 Potenciais Impactos Sociais, Econômicos e Técnicos
O sistema proposto possui impactos positivos diretos. Do ponto de vista ambiental, contribui com a preservação da água ao evitar desperdícios prolongados. No aspecto econômico, proporciona economia financeira aos usuários ao evitar cobranças indevidas por consumo excessivo causado por vazamentos ocultos. Tecnologicamente, o projeto oferece uma ferramenta que facilita a identificação da necessidade de manutenção especializada, evitando danos maiores e prolongados na infraestrutura hidráulica das residências.

## 4. Descrição da Proposta

### 4.1 Detalhamento da Solução Proposta
O sistema será composto por um sensor de vazão instalado na tubulação principal de água, na entrada das residências. Esse sensor será responsável por medir continuamente o fluxo de água e enviar os dados coletados via conexão Wi-Fi para a plataforma de monitoramento ThingSpeak. A visualização dos dados será feita em tempo real, permitindo o acompanhamento constante do consumo de água. Caso o sistema detecte um volume de água anormal em determinado intervalo de tempo — sugerindo um possível vazamento — um alerta será gerado na plataforma. Além disso, haverá a possibilidade de interromper remotamente o fornecimento de água por meio do acionamento de uma trava mecânica, evitando maiores prejuízos.

### 4.2 Principais Funcionalidades
- Medição contínua do fluxo de água na tubulação de entrada da residência.  
- Envio e exibição dos dados em tempo real em uma plataforma web (ThingSpeak).  
- Geração de alertas quando os dados indicarem consumo anômalo.  
- Possibilidade de interrupção remota do fornecimento de água.

### 4.3 Abordagem e Tecnologias Utilizadas
- **Hardware:** ESP32, sensor de fluxo YF-403, válvula solenóide 12v, 2 polegadas  
- **Software (Backend):** Linguagem C utilizando o ambiente de desenvolvimento Arduino IDE  
- **Interface Web (Frontend):** Plataforma ThingSpeak para exibição dos dados

## 5. Requisitos

### 5.1 Requisitos Funcionais
A seguir, são listadas as funcionalidades essenciais que o sistema deverá oferecer:

- Medir continuamente o volume de água que passa pela tubulação a cada segundo.
- Enviar e disponibilizar os dados coletados na plataforma de monitoramento ThingSpeak.
- Gerar alertas automáticos, em qualquer horário do dia, quando houver consumo de água além do esperado.
- Permitir a interrupção remota do fornecimento de água a qualquer momento por meio da plataforma web.

### 5.2 Requisitos Não Funcionais

- **Desempenho:** O sistema deve operar em tempo real, garantindo alta disponibilidade para leitura e transmissão dos dados.
- **Escalabilidade:** A arquitetura deve suportar a adição de novos sensores e o monitoramento de múltiplas residências sem perda de desempenho.
- **Confiabilidade:** Os alertas devem ser emitidos apenas em situações que realmente indiquem comportamento anômalo, minimizando falsos positivos.
- **Manutenibilidade:** O sistema deve ser projetado de forma modular e clara, facilitando atualizações e correções futuras.

## 6. Diagrama de Comunicação

O diagrama a seguir representa o fluxo de dados e a comunicação entre os componentes do sistema, incluindo o sensor de vazão, o microcontrolador ESP32, a plataforma de monitoramento ThingSpeak e a válvula solenóide.

![Diagrama de Comunicação](./imgs/diagramaUbiquosComunicacao.png)

### Descrição dos Componentes

- **Sensor de Vazão YF-403:** Responsável por medir a quantidade de água que passa pela tubulação.
- **ESP32:** Microcontrolador que lê os dados do sensor e os transmite via Wi-Fi.
- **Rede Wi-Fi:** Canal de comunicação entre o ESP32 e a internet.
- **Plataforma ThingSpeak:** Interface web para visualização em tempo real, geração de alertas e controle remoto do sistema.
- **Válvula Solenóide:** Componente responsavel por interromper e permitir a passagem do fluxo d'água.

## 7. Diagrama elétrico

![Diagrama Elétrico](./imgs/EsquemaEletricoUbiquos.png).

## 8. Metodologia de Desenvolvimento

O desenvolvimento do sistema será dividido em etapas sequenciais, permitindo validações constantes e entregas incrementais. A seguir, estão descritas as principais fases do projeto:

- **Levantamento de Requisitos e Definição do Escopo:**
  Identificação das necessidades do usuário, funcionalidades essenciais e limites do projeto.

- **Montagem do Protótipo de Hardware:**
  Instalação e testes do sensor de fluxo YF-403 com o microcontrolador ESP32, garantindo leituras confiáveis.

- **Programação do ESP32:**
  Desenvolvimento do firmware em C, utilizando a IDE Arduino para configurar o sensor, realizar as leituras e transmitir os dados via Wi-Fi.

- **Integração com a Plataforma ThingSpeak:**
  Configuração dos agentes e templates no ThingSpeak para receber, armazenar e exibir os dados capturados em tempo real.

- **Implementação de Alertas:**
  Definição de limiares de consumo para disparo automático de alertas e testes de confiabilidade desses alertas.

- **Teste de Atuação Remota:**
  Desenvolvimento e validação de um sistema remoto para controle de um atuador (como uma válvula elétrica) para interrupção do fornecimento de água.

- **Testes e Validação do Sistema:**
  Execução de testes em cenários controlados e ajustes para garantir robustez, sensibilidade adequada e baixo índice de falsos positivos.

- **Documentação e Entrega Final:**
  Elaboração de documentação técnica e orientações de uso do sistema.

## 9. Resultados Esperados

Ao final do desenvolvimento, espera-se que o sistema esteja plenamente funcional, sendo capaz de monitorar em tempo real o fluxo de água na tubulação principal de uma residência e identificar padrões de consumo anômalos que indiquem a existência de vazamentos.

Entre os principais resultados esperados, destacam-se:

- **Monitoramento contínuo e remoto:** leitura e transmissão dos dados de fluxo de água em tempo real por meio da plataforma ThingSpeak.
- **Detecção automatizada de vazamentos:** identificação de consumo excessivo fora de horários comuns ou em ausência de moradores, gerando alertas automáticos.
- **Capacidade de atuação remota:** acionamento de um mecanismo para interrupção do fornecimento de água, minimizando o desperdício até a resolução do problema.
- **Facilidade de visualização dos dados:** uso de uma plataforma web robusta para análise dos dados coletados e acompanhamento histórico do consumo.

### Impactos Esperados

- **Ambiental:** redução no desperdício de água potável ao permitir respostas rápidas a vazamentos.
- **Econômico:** diminuição de custos com contas de água elevadas devido a vazamentos não percebidos.
- **Operacional:** menor necessidade de inspeções presenciais ou intervenções tardias por parte dos usuários, principalmente em residências que permanecem longos períodos desocupadas.

### Benefícios e Possíveis Melhorias Futuras

- Expansão do sistema para múltiplos pontos de medição dentro de uma residência.
- Integração com outros sistemas de automação residencial (smart home).
- Aplicação do modelo em condomínios, com suporte a múltiplas unidades habitacionais.
- Melhoria na precisão dos alertas utilizando aprendizado de máquina para identificar padrões específicos de uso.

## 10. Conclusão

Este projeto propõe o desenvolvimento de um sistema de monitoramento de fluxo d'água com foco na detecção precoce de vazamentos na entrada da rede de fornecimento de residências. Utilizando um sensor de vazão integrado ao microcontrolador ESP32 e conectado à plataforma ThingSpeak, o sistema visa oferecer monitoramento em tempo real, emissão de alertas automáticos e, eventualmente, a capacidade de interromper remotamente o fornecimento de água, prevenindo desperdícios e prejuízos.

A importância do projeto se destaca em contextos onde o acesso imediato à residência não é possível, como casas de veraneio, e onde o desperdício de água pode resultar em custos elevados e danos ao meio ambiente. Ao automatizar o processo de detecção de vazamentos, o sistema também reduz a dependência de observações humanas tardias e imprecisas.

Quanto ao futuro do projeto, espera-se que a solução possa ser escalada para atender múltiplas residências, com melhorias na inteligência de detecção, integração com sistemas de automação residencial e uso de painéis gráficos mais detalhados para facilitar a análise de dados históricos. A arquitetura modular e a utilização de tecnologias abertas favorecem a continuidade do desenvolvimento e a personalização da solução para diferentes contextos.
