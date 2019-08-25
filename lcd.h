// =======================================================================
// Escola SENAI "A. Jacob Lafer"
//
// Curso:		Técnico de Eletroeletrônica
// Disciplina:	Sistemas Eletrônicos Digitais
//
// Biblioteca:	Controle de Display LCD 2x16 e 4x16 no modo 4 bits
//
// Descrição:	
//
// Ano:			2018
// Revisão:		D
//
// Autor:		Prof. Cleisson
// =======================================================================

#ifndef _LCD_H_
#define _LCD_H_

//=====================================================================================
//	BIBLIOTECAS
//=====================================================================================
#include <delays.h>

//=====================================================================================
//	DECLARAÇÃO DAS SUBROTINAS
//=====================================================================================
void InicializaLCD	(void);
void ComandoLCD		(unsigned char comando);
void EscreveLCD		(unsigned char dado);
void StringLCD		(const rom unsigned char *dado);
void NumeroLCD		(unsigned int numero);
void PosicionaLCD	(unsigned char linha, unsigned char coluna);
void LimpaLCD		(void);

//=====================================================================================
//	DEFINIÇÕES DE HARDWARE
//=====================================================================================
#define RS_LCD		PORTEbits.RE0
#define EN_LCD		PORTEbits.RE1
#define RW_LCD		PORTEbits.RE2
#define D4_LCD		PORTDbits.RD4
#define D5_LCD		PORTDbits.RD5
#define D6_LCD		PORTDbits.RD6
#define D7_LCD		PORTDbits.RD7

#define T_RS_LCD	TRISEbits.RE0
#define T_EN_LCD	TRISEbits.RE1
#define T_RW_LCD	TRISEbits.RE2
#define T_D4_LCD	TRISDbits.RD4
#define T_D5_LCD	TRISDbits.RD5
#define T_D6_LCD	TRISDbits.RD6
#define T_D7_LCD	TRISDbits.RD7

//=====================================================================================
//	SUBROTINA DE INICIALIZAÇÃO NO MODO 4 BITS DO LCD
//=====================================================================================
void InicializaLCD (void)
{
	unsigned char ADCON1_bkp;
	
	ADCON1_bkp = ADCON1;
	ADCON1 = (ADCON1 & 0xF0) | 0x0A;
	
	T_RS_LCD = 0;
	T_RW_LCD = 0;
	T_EN_LCD = 0;
	T_D4_LCD = 0;
	T_D5_LCD = 0;
	T_D6_LCD = 0;
	T_D7_LCD = 0;

	ComandoLCD (0x33);
	ComandoLCD (0x32);
	ComandoLCD (0x28);
	ComandoLCD (0x28);
	ComandoLCD (0x0C);
	ComandoLCD (0x06);
	ComandoLCD (0x01);
	
	ADCON1 = ADCON1_bkp;
}

//=====================================================================================
//	SUBROTINA DE CONTROLE DO LCD
//=====================================================================================
void ComandoLCD (unsigned char comando)
{
	unsigned char ADCON1_bkp;
	
	ADCON1_bkp = ADCON1;
	ADCON1 = (ADCON1 & 0xF0) | 0x0A;
	
	RS_LCD = 0;
	RW_LCD = 0;
	EN_LCD = 0;
	
	D7_LCD = (comando & 0x80) >> 7;
	D6_LCD = (comando & 0x40) >> 6;
	D5_LCD = (comando & 0x20) >> 5;
	D4_LCD = (comando & 0x10) >> 4;
	EN_LCD = 1;
	Delay10TCYx(50);
	EN_LCD = 0;
	Delay10TCYx(50);

	D7_LCD = (comando & 0x08) >> 3;
	D6_LCD = (comando & 0x04) >> 2;
	D5_LCD = (comando & 0x02) >> 1;
	D4_LCD = (comando & 0x01);
	EN_LCD = 1;
	Delay10TCYx(50);
	EN_LCD = 0;
	Delay1KTCYx(10);
	
	ADCON1 = ADCON1_bkp;
}

//=====================================================================================
//	SUBROTINA DE ESCRITA DE CARACTER DO LCD
//=====================================================================================
void EscreveLCD (unsigned char dado)
{
	unsigned char ADCON1_bkp;
	
	ADCON1_bkp = ADCON1;
	ADCON1 = (ADCON1 & 0xF0) | 0x0A;
	
	RS_LCD = 1;
	RW_LCD = 0;
	EN_LCD = 0;
	
	D7_LCD = (dado & 0x80) >> 7;
	D6_LCD = (dado & 0x40) >> 6;
	D5_LCD = (dado & 0x20) >> 5;
	D4_LCD = (dado & 0x10) >> 4;
	EN_LCD = 1;
	Delay10TCYx(50);
	EN_LCD = 0;
	Delay10TCYx(50);
	
	D7_LCD = (dado & 0x08) >> 3;
	D6_LCD = (dado & 0x04) >> 2;
	D5_LCD = (dado & 0x02) >> 1;
	D4_LCD = (dado & 0x01);
	EN_LCD = 1;
	Delay10TCYx(50);
	EN_LCD = 0;
	Delay1KTCYx(10);
	
	ADCON1 = ADCON1_bkp;
}

//=====================================================================================
//	SUBROTINA DE ESCRITA DE TEXTO DO LCD
//=====================================================================================
void StringLCD (const rom unsigned char *dado)
{
	while (*dado != '\0')
	{
		EscreveLCD(*dado);
		++ dado;
	}
}

//=====================================================================================
//	SUBROTINA DE POSICIONAMENTO DO CURSOR DE ESCRITA DO LCD
//=====================================================================================
void PosicionaLCD (unsigned char linha, unsigned char coluna)
{
	-- coluna;

	switch (linha)
	{
		case 1:
			ComandoLCD(0x80 + coluna);
		break;

		case 2:
			ComandoLCD(0xC0 + coluna);
		break;

		case 3:
			ComandoLCD(0x90 + coluna);
		break;

		case 4:
			ComandoLCD(0xD0 + coluna);
		break;

		default:
		break;	
	}
}

//=====================================================================================
//	SUBROTINA PARA ESCREVER UM NÚMERO DE UMA VARIÁVEL NO LCD
//=====================================================================================
void NumeroLCD (unsigned int numero)
{
	unsigned char x[5];
	unsigned char i;
	unsigned char j;
	
	x[4] = numero / 10000;
	numero = numero % 10000;
	x[3] = numero / 1000;
	numero = numero % 1000;
	x[2] = numero / 100;
	numero = numero % 100;
	x[1] = numero / 10;
	x[0] = numero % 10;
	
	for (i = 4; (x[i] == 0)&&(i > 0) ; --i);
	
	j = 4 - i;
	
	do
	{
		EscreveLCD(x[i] + 0x30);
		--i;
	} while (i != 0xFF);
	
	while (j > 0)
	{
		EscreveLCD(' ');
		--j;
	}		
}	
//=====================================================================================
//	SUBROTINA PARA APAGAR O CONTEÚDO ESCRITO NO LCD
//=====================================================================================
void LimpaLCD (void)
{
	ComandoLCD(0x01);
}
//=====================================================================================

#endif	// _LCD_H_