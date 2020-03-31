#ifndef	_DELAYS_H_
#define _DELAYS_H_

//=====================================================================================
// Escola SENAI "A. Jacob Lafer"
// 
// Curso T�cnico de Eletroeletr�nica
// Disciplina: Desenvolvimento de Sistemas Eletr�nicos
// Ano: 2016
// Rotina de Temporiza��o via Software - Delays (Adaptada)
// Vers�o: B
//=====================================================================================

//=====================================================================================
//	BIBLIOTECAS
//=====================================================================================
#include <delays.h>

//=====================================================================================
//	DEFINI��ES DE CONSTANTES
//=====================================================================================
#define _XTAL_FREQ	20000000				// Define a frequ�ncia do cristal em Hz

//=====================================================================================
//	DECLARA��O DAS SUBROTINAS
//=====================================================================================
void Delay_s (unsigned char delay);
void Delay_ms (unsigned char delay);
void Delay_us (unsigned char delay);

//=====================================================================================
//	CONFIGURA��O DA BIBLIOTECA
//=====================================================================================
#ifdef	_XTAL_FREQ
#define	_TIME	_XTAL_FREQ/4000000
#else
#define _TIME	1
#endif

//=====================================================================================
//	SUBROTINA DE TEMPORIZA��O PARA SEGUNDOS
//=====================================================================================
void Delay_s (unsigned char delay)
{
	unsigned char i,j;

	i = _TIME * 10;
	
	while (i--)
	{
		j = delay;
		while (j--) Delay1KTCYx (100);
	}
}

//=====================================================================================
//	SUBROTINA DE TEMPORIZA��O PARA MILISSEGUNDOS
//=====================================================================================
void Delay_ms (unsigned char delay)
{
	unsigned char i,j;

	i = _TIME;
	
	while (i--)
	{
		j = delay;
		while (j--) Delay1KTCYx (1);
	}
}

//=====================================================================================
//	SUBROTINA DE TEMPORIZA��O PARA MICROSSEGUNDOS
//=====================================================================================
void Delay_us (unsigned char delay)
{
	unsigned char i,j;
	
	i = _TIME;
	
	while (i--)
	{
		j = delay;
		while (j--);
	}
}
//=====================================================================================

#endif	// _DELAYS_H_