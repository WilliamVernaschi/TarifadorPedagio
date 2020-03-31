#ifndef	_DELAYS_H_
#define _DELAYS_H_

//=====================================================================================
// Escola SENAI "A. Jacob Lafer"
// 
// Curso Técnico de Eletroeletrônica
// Disciplina: Desenvolvimento de Sistemas Eletrônicos
// Ano: 2016
// Rotina de Temporização via Software - Delays (Adaptada)
// Versão: B
//=====================================================================================

//=====================================================================================
//	BIBLIOTECAS
//=====================================================================================
#include <delays.h>

//=====================================================================================
//	DEFINIÇÕES DE CONSTANTES
//=====================================================================================
#define _XTAL_FREQ	20000000				// Define a frequência do cristal em Hz

//=====================================================================================
//	DECLARAÇÃO DAS SUBROTINAS
//=====================================================================================
void Delay_s (unsigned char delay);
void Delay_ms (unsigned char delay);
void Delay_us (unsigned char delay);

//=====================================================================================
//	CONFIGURAÇÃO DA BIBLIOTECA
//=====================================================================================
#ifdef	_XTAL_FREQ
#define	_TIME	_XTAL_FREQ/4000000
#else
#define _TIME	1
#endif

//=====================================================================================
//	SUBROTINA DE TEMPORIZAÇÃO PARA SEGUNDOS
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
//	SUBROTINA DE TEMPORIZAÇÃO PARA MILISSEGUNDOS
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
//	SUBROTINA DE TEMPORIZAÇÃO PARA MICROSSEGUNDOS
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