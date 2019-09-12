# Exemplo Sensor de Temperatura

#### Introdução

O Twino Board conta com o sensor de temperatura MCP9808 utilizando o protocolo I2C para a comunicação. Este exemplo conta com funções para fazer a comunição I2C com o módulo, bem como sua leitura e velocidade de requisão de dados. Além disso, também é possível definir a resolução dos dados obtidos pelo sensor de temperatura.

#### Funcionamento do código principal

Verifica se a temperatura está acima (LED na cor vermelha) ou abaixo (LED na cor verde) de 30 °C.
A leitura é feita a cada 10 segundos, o LED na cor azul indica esse precesso.

***

## Bibliotecas
- #### clock.h
Responsável por configurar todos os sistemas de clock do microcontrolador.

**void clock_init() -** inicializa e seleciona as configurações dos clocks.

- #### temp.h 
**void temp_init() -** inicializa o sensor de temperatura e define sua resolução.

**void temp_time(unsigned int tempo) -** define o tempo, em segundos, entre requisição de dados do sensor de temperatura.

**float read_temp() -** faz a leitura e conversão dos dados de temperatura.

**#pragma vector=TIMER0_B0_VECTOR -** rotina de interrupção do timer B0 retirar o microcontrolador do LPM0 (Low Power Mode 0).

- #### TI_USCI_I2C_master.h
Biblioteca disponibilizada pela Texas Instruments, toda documentação pode ser encontrada [aqui](http://www.ti.com/lit/an/slaa382a/slaa382a.pdf).

- #### includes.h
Incorpora todas as anteriores no código principal.