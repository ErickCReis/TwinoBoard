# Exemplo Display

O Twino Board conta com um LED RGB que pode ser configurado independentemente, este exemplo conta com algumas funções que facilitam sua manipulação.

***

## Bibliotecas
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

**void display_time(unsigned int tempo_ms) -** liga o display fazendo-o piscar a cada *tempo_ms* milissegundos.

**void display_set_color(led_color cor) -** atualiza a cor do display.

**void display_next_color() -** define com a mudança de cores acontece.

**void display_enable_rand() -** habilita a sequência de mudança de cores.

**void display_disable_rand() -** desabilita a sequência de mudança de cores.

- #### includes.h
Incorpora todas as anteriores no código principal.