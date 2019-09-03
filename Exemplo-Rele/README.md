# Exemplo Relé

O Twino Board conta com um transistor capaz de ativar componentes que exigem correntes elevadas, sua saída é controlada pela porta P3.3 do microcontrolador. Este exemplo conta com funções para alternar o estado do relé, além disso é possível definir intervalos específicos para alternar este estado.

***

## Bibliotecas
- #### clock.h
Responsável por configurar todos os sistemas de clock do microcontrolador.

**void clock_init() -** inicializa e seleciona as configurações dos clocks.

- #### rele.h
Re todas as funções relacionadas ao relé.

**void rele_init() -** inicializa as postas do relé e do LED de indicação.

**void rele_on() -** ativa o relé e o LED de indicação.
 
**void rele_off() -** desativa o relé e o LED de indicação.

**void rele_time(unsigned int tempo) -** define o período de ativação do relé e do LED de indicação.

**#pragma vector=TIMER2_B0_VECTOR -** rotina de interrupção do timer B2 para alternar o estado do relé e do LED.

- #### includes.h
Incorpora todas as anteriores no código principal.