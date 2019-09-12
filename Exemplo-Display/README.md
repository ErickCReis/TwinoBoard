# Exemplo Display

#### Introdução

O Twino Board conta com um LED RGB que pode ser configurado independentemente atráves das portas P1.0, P1.1 e P1.2. Este exemplo conta com fuções para alternar o estado do display bem como sua cor, além disso é possível definir intervalos específicos para alternar o estado do display.

#### Funcionamento do código principal

Pisca os LEDs em uma sequencia de cores predefinida a cada dois segundos.

***

### Bibliotecas
- #### clock.h
Responsável por configurar todos os sistemas de clock do microcontrolador.

**void clock_init() -** inicializa e seleciona as configurações dos clocks.

- #### display.h
Realiza todas a interações necessárias com o LED RGB.

**INTERRUPT_LIMIT -** auxiliar de contagem que permite reduzir o numéro de interações relizadas na interupção. 

**led_color -** dado que contém cores predefinidas assim como os respectivos códigos para acionar a cores pelos pinos de saída. 

**void display_init() -** configura os pinos como saída e os inicializa desligados.

**void display_on(led_color cor) -** liga o display de forma estática com a cor enviada no parâmetro *cor*.

**void display_off() -** desliga o o display e para o timer de contagem.

**void display_time(unsigned int tempo_ms) -** liga o display fazendo-o piscar a cada "tempo_ms" milissegundos.

**void display_set_color(led_color cor) -** atualiza a cor do display.

**void display_next_color() -** define com a mudança de cores acontece.

**void display_enable_rand() -** habilita a sequência de mudança de cores.

**void display_disable_rand() -** desabilita a sequência de mudança de cores.

**#pragma vector=TIMER1_B0_VECTOR -** rotina de interrupção do timer B1 para alternar o estado e a cor do display.

- #### includes.h
Incorpora todas as anteriores no código principal.