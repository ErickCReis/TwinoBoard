#include "TI_USCI_I2C_master.h"

int readOp = 0;
signed int byteCtr;
unsigned char *TI_receive_field;
unsigned char *TI_transmit_field;

unsigned char read_reg[2];
/*
 * Prepara modulo I2C para recepcao
 */
void TI_USCI_I2C_receiveinit(unsigned char slave_address,
		unsigned char prescale) {
	P1SEL1 |= SDA_PIN + SCL_PIN;   //configura pinos para funcao I2C
	UCB0CTLW0 = UCSWRST; // coloca modulo I2C em modo reset
	UCB0CTLW0 |= (UCMST | UCMODE_3 | UCSYNC); // configura MSP como mestre da comunicacao I2C
	UCB0CTLW0 |= UCSSEL_2;  // utiliza SMCLK como base
	UCB0BR0 = prescale; // configura prescaler (SCL = SMCLK/prescaler)
	UCB0BR1 = 0;
	UCB0I2CSA = slave_address; // configura endereco do escravo desejado
	UCB0CTLW0 &= ~UCSWRST; // coloca o modulo I2C em modo de operacao
	UCB0IE = /*UCNACKIE |*/ UCRXIE | UCTXIE; // habilita interrupcoes de transmissao, recepcao e NACK
}

/*
 * Prepara modulo I2C para transmissao
 */
void TI_USCI_I2C_transmitinit(unsigned char slave_address,
		unsigned char prescale) {
	P1SEL1 |= SDA_PIN + SCL_PIN;  //configura pinos para funcao I2C
	P1DIR |= SDA_PIN + SCL_PIN;
	UCB0CTLW0 = UCSWRST;   // coloca modulo I2C em modo reset
	UCB0CTLW0 |= UCMST + UCMODE_3 + UCSYNC; // configura MSP como mestre da comunicacao I2C
	UCB0CTLW0 |= UCSSEL_2;   // utiliza SMCLK como base
	UCB0BR0 = prescale; // configura prescaler (SCL = SMCLK/prescaler)
	UCB0BR1 = 0;
	UCB0I2CSA = slave_address;  // configura endereco do escravo desejado
	UCB0CTLW0 &= ~UCSWRST; // coloca o modulo I2C em modo de operacao
	UCB0IE = /*UCNACKIE |*/ UCTXIE; // habilita interrupcoes de transmissao e NACK
}

/*
 * Recebe mensagem do escravo
 */
void TI_USCI_I2C_receive(unsigned int byteCount, unsigned char *field) {
	UCB0CTLW0 &= ~UCTR;	// configura MSP como receptor
	TI_receive_field = field;	// aponta para variavel que recebera a mensagem
	if (byteCount == 1) {	// recepcao de apenas um byte
		byteCtr = 0;
		__disable_interrupt();
		UCB0CTLW0 |= UCTXSTT;  // I2C start
		while (UCB0CTLW0 & UCTXSTT); // verifica se o start foi enviado
		UCB0CTLW0 |= UCTXSTP;  // I2C stop
		__enable_interrupt();
	} else if (byteCount > 1) {	// recepcao de 2 ou mais bytes
		byteCtr = byteCount - 2;
		UCB0CTLW0 |= UCTXSTT; // I2C start
	}
}

/*
 * Transmite mensagem para escravo
 */
void TI_USCI_I2C_transmit(unsigned int byteCount, unsigned char *field, int op) {
	TI_transmit_field = field;	// aponta para variavel que contem a mensagem a ser trasmitida
	byteCtr = byteCount;
	readOp = op;
	while (UCB0CTLW0 & UCTXSTP);	// espera que o barramento esteja livre
	UCB0CTLW0 |= UCTR + UCTXSTT; // envia condicao de start
}

/*
 * Verifica a disponibilidade do barramento I2C
 */
void wait_for_i2c_bus() {
	while (UCB0STAT & UCBBUSY); // retorna status do barramento
}

/*
 * Recebe o conteudo de um registrador em um dispositivo escravo
 */
void read_register(unsigned char sladdr, unsigned char reg_addr, unsigned char num_bytes, char prescaler){
	UCB0CTLW0 |= UCTXSTP;
	wait_for_i2c_bus();
	TI_USCI_I2C_receiveinit(sladdr, prescaler);	// prepara modulo para recepcao
	wait_for_i2c_bus();
	TI_USCI_I2C_transmit(1, (unsigned char[] ) {reg_addr}, 1); // envia para o escravo o numero do registrador a ser lido. Nao gera stop
	__delay_cycles(500);
	TI_USCI_I2C_receive(num_bytes,read_reg); // gera repeated start e recebe mensagem do escravo
	wait_for_i2c_bus();
}

#pragma vector = USCI_B0_VECTOR
__interrupt void USCIB0_ISR(void) {
	switch (UCB0IV) {
	case USCI_I2C_UCNACKIFG:	// interrupcao de NACK
		if (UCB0STAT & UCNACKIFG) {  // escravo enviou NACK; cancelar comunicacao
			UCB0CTLW0 |= UCTXSTP;	// gera stop
			UCB0STAT &= ~UCNACKIFG;	// limpar flag de NACK
		}
		break;

	case USCI_I2C_UCRXIFG0:	// interrupcao de recepcao
		if (byteCtr == 0) {	// se recebeu a quantidade de dados desejados
			UCB0CTLW0 |= UCTXSTP;  // gera stop
			*TI_receive_field = UCB0RXBUF; // copia ultimo byte do buffer para a variavel desejada
			TI_receive_field++;
		} else { // se ainda nao recebeu a quantidade desejada
			*TI_receive_field = UCB0RXBUF; // copia byte do buffer para a variavel desejada
			TI_receive_field++; //aponta para a proxima posicao da variavel
			byteCtr--;	// decrementa o contador de bytes
		}
		break;

	case USCI_I2C_UCTXIFG0:	// interrupcao de transmissao
		if (byteCtr == 0) { // se transmitiu a quantidade de bytes desejados
			if (readOp == 0) // se proxima operacao nao for de leitura
				UCB0CTLW0 |= UCTXSTP;  //gera stop
			UCB0IFG &= ~UCTXIFG0; //limpa flag de interrupcao de transmissao
		} else { // se ainda nao recebeu a quantidade desejada
			byteCtr--; //decrementa contador de bytes
			UCB0TXBUF = *TI_transmit_field; //copia proxima posicao da variavel para o buffer de transmissao
			TI_transmit_field++; // aponta para a proxima posicao da variavel
		}
		break;
	}
}

