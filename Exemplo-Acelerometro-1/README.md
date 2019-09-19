# Exemplo Acelerômetro 1

#### Introdução

O Twino Board conta com um módulo acelerômetro que utiliza o protocolo I2C para a comunicação. Este exemplo conta com funções para fazer a comunicação I2C com o módulo. Além disso, também é possível selecionar os modos de operação bem como velocidade e sensibilidade de detecção.

#### Funcionamento do código principal

Verifica a orientação do Twino Board, informando-a através de um LED com as seguintes cores.

* Azul caso esteja na vertical;
* Verde caso esteja na horizontal;
* Vermelho caso o Twino Board esteja virado para baixo.

***

## Bibliotecas
- #### clock.h
Responsável por configurar todos os sistemas de clock do microcontrolador.

**void clock_init() -** inicializa e seleciona as configurações dos clocks.

- #### accel.h 
**void accel_init(char mode) -** inicializa o módulo acelerômetro de acordo com o modo escolhido, detecção de movimento (_Motion_) ou detecção de orientação (_Orientation_).

**unsigned char accel_status() -** verifica e retorna o valor do registrador de status do módulo acelerômetro.

**#pragma vector=PORT3_VECTOR -** rotina de interrupção da porta P3 para intentificar o sinal do módulo acelerômetor e retirar o microcontrolador do LPM0 (Low Power Mode 0).

- #### TI_USCI_I2C_master.h
Biblioteca disponibilizada pela Texas Instruments, toda documentação pode ser encontrada [aqui](http://www.ti.com/lit/an/slaa382a/slaa382a.pdf).

- #### includes.h
Incorpora todas as anteriores no código principal.