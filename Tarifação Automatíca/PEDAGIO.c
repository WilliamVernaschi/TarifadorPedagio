//----BIBLIOTECAS ---- //
#include <p18f4550.h>
#include <delays.h>
#include "lcd.h"
#include <timers.h>

//--------------------//

//----- CONFIGURAÇÕES MICRO CONTROLADOR ----//
#pragma config	FOSC	=	HS
#pragma config	PWRT	=	ON
#pragma config	PBADEN	=	OFF
#pragma config	WDT	=		OFF
#pragma config	LVP	=		OFF
//------------------------------------------//
	
//----------------- DEFINES ----------------//
#define LED_VERDE 			PORTDbits.RD1
#define LED_VERMELHO 		PORTDbits.RD0
#define CONTROL 			PORTCbits.RC2
#define SENSOR_SAIDA		PORTBbits.RB5
#define MOEDEIRO_SINAL		PORTBbits.RB0
#define ACIONA_MANUAL		PORTAbits.RA4
//-----------------------------------------//

//declaração das constantes
#define ON 					1	
#define OFF 				0
#define CONST_T_TIMER0 (65536-416)
#define CONST_T_TIMER1 (65536-416)
const char ValorPago = 				1;
const char Ang_Neg90 =				10;
const char Ang_Neg60 =				11;
const char Ang_Neg30 =				13;
const char Ang_0 = 					15;
const char Ang_30 =					16;
const char Ang_60 =					18;
const char Ang_90 =					20;



//=====================================================================================
//				DECLARAÇÃO DAS VARI�VEIS
//=====================================================================================
// 1bit

struct
{
	unsigned char f_00:1;
	unsigned char f_01:1;
	unsigned char f_02:1;
	unsigned char f_03:1;
	unsigned char f_04:1;
	unsigned char f_05:1;
	unsigned char f_06:1;
	unsigned char f_07:1;	
	unsigned char f_08:1;
}Flags;

#define f_sensor 			Flags.f_00
#define f_tempo	 			Flags.f_01
#define f_a		 			Flags.f_02
#define f_b		 			Flags.f_03
#define f_c		 			Flags.f_04
#define f_medindo 			Flags.f_05
#define f_medindoH 			Flags.f_06
#define f_medindoL 			Flags.f_07
#define f_contagem_feita	Flags.f_08

// 8bits
unsigned char	c_teste	= 0x00;
unsigned char	tecla	= 0x00;
unsigned char	dado	= 0x00;
unsigned char	dado1	= 0x00;
unsigned char	cont_250ms	= 0x00;
unsigned char	cont_100ms	= 0x00;
unsigned char pulso = 			180;
unsigned char AcionaServo = 	0;

//16 bits
unsigned int	c_teste1 = 0x00;
unsigned int	in_ad = 0x00;
unsigned int i = 				0;
unsigned int ContadorPulsos = 	0;
unsigned int ContagemReal = 	0;
unsigned int ContagemCent = 	0;
unsigned int cont_tempo = 	0;



//=====================================================================================
//				DECLARAÇÃO DAS ROTINAS
//=====================================================================================
void Int_Alta (void);
void Trata_Alta (void);
void Trata_Timer0(void);
void Trata_Timer1(void);
void MostraValorLCD();
void CentavosParaReal();
void PosicionaServo (float Angle);
void conta_pulso (void);


//=====================================================================================
//					Verificação das INTERRUPÇÕES
//=====================================================================================
#pragma code Alta = 0x08	//Como se fosse o ORG0000h do ASSEMBLER

void Int_Alta (void)		//Já salta para o endereço onde tem mais espaço
{
	Trata_Alta ();			//Vou para rotina pois aqui não tem espaço
}
#pragma code				//para finalizar o pragma do ORG000h
#pragma interrupt Trata_Alta//para indicar ao compilador que a prioridade da interrupção é alta
///////////////////////////

///////////////////////////


void Trata_Alta (void)
{	
	if (INTCONbits.TMR0IF == 1)
	{
		Trata_Timer0();	
	}
	if (PIR1bits.TMR1IF == 1)
	{
		Trata_Timer1();	
	}	

}

//=====================================================================================
//					Tratamento das INTERRUPÇÕES
//=====================================================================================
void Trata_Timer0(void)
{
	WriteTimer0(CONST_T_TIMER0);
	INTCONbits.TMR0IF = 0;
	/*
	++cont_tempo_infra;
	*/
	
}

void Trata_Timer1(void)
{
	WriteTimer1(CONST_T_TIMER1);
	PIR1bits.TMR1IF = 0;
	
	//Escreva aqui sua interrupção
	
	++cont_tempo;
	
}


// -------------- FUNÇÕES --------------- //
void PosicionaServo (float Angle) {		// Função que posiciona o servo e toma o ângulo como parâmetro.
	CONTROL = ON;
	Delay100TCYx(Angle);
	CONTROL = OFF;
	Delay100TCYx(200 - Angle);
	}	



void CentavosParaReal() {		// Função que converte 100 centavos em 1 real.
    if (ContagemCent == 100) {
        ContagemReal = ContagemReal + 1;
        ContagemCent = 0.0;
        return;
    }
}

void MostraValorLCD() {		//Função que mostra no display LCD o valor que está foi inserido no moedeiro.
	LimpaLCD();
	StringLCD("INSERIDOS R$");
	PosicionaLCD(1, 13);
	EscreveLCD(ContagemReal + 0x30);
	PosicionaLCD(1, 14);
	StringLCD(",");
	PosicionaLCD(1, 15);
	if (ContagemCent == 0) {
		StringLCD("00");
	} else if (ContagemCent == 5) {
		StringLCD("05");
	} else {
		NumeroLCD(ContagemCent);
	}
	Delay1KTCYx(250);
	return;
}

// -------------------------------------- //

void conta_pulso (void)
{
		if(f_medindo==0)
		{
			if (MOEDEIRO_SINAL == 1)
			
			{
				WriteTimer1(CONST_T_TIMER1);
				T1CONbits.TMR1ON = 1;    //bit que liga e desliga o timer
				f_medindo=1;
				f_medindoH=1;
			}
			
		}
		if(f_medindoH==1)
		{
			if (MOEDEIRO_SINAL == 0)
			{
				T1CONbits.TMR1ON = 0;    //bit que liga e desliga o timer
				f_medindoH=0;
				if ((60<cont_tempo)&&(cont_tempo<80))
				{
					++ContadorPulsos;
					WriteTimer1(CONST_T_TIMER1);	
					T1CONbits.TMR1ON = 1;    //bit que liga e desliga o timer
					f_medindoL=1;
				}	
				else
				{
					f_medindo=0;
				}						
				cont_tempo=0;
			}
		}
		if(f_medindoL==1)
		{
			if (MOEDEIRO_SINAL == 1)
			{
				T1CONbits.TMR1ON = 0;    //bit que liga e desliga o timer
				f_medindoL=0;
				if ((90<cont_tempo)&&(cont_tempo<110))
				{
					WriteTimer1(CONST_T_TIMER1);	
					T1CONbits.TMR1ON = 1;    //bit que liga e desliga o timer
					f_medindoH=1;
				}	
				else
				{
					f_medindo=0;
				}						
				cont_tempo=0;
			}
			else if (300<cont_tempo)
			{	
				T1CONbits.TMR1ON = 0;    //bit que liga e desliga o timer	
				f_medindoL=0;		
				f_medindo=0;
				f_contagem_feita=1;
				cont_tempo=0;
				
			}	
					
		}		
			
}	
	
// ------- FUN��O MAIN --------- //
void main() {

    // ENTRADAS E SAÍDAS DO MICRO //
    //AD Essa configuração de AD é comum para todos os pinos de AD
	ADCON1 = 0b00001111;
	TRISB = 0b11111111;
	TRISC = 0b00000000;
	UCONbits.USBEN = 0;		//Configuração necessária para deixar os pinos RC4 e RC5
	UCFGbits.UTRDIS = 1;	//como entradas digitais, desabilitando a USB.
	TRISD = 0b00000000;
	TRISE = 0b00001111;
	PORTB = 0b00000000;
	PORTC = 0x00;
	PORTD = 0xFF;
	PORTA = 0x00;
	PORTE = 0b00000000;
	//T0CON = 0b11011001;
    // -------------------------- //
    
//********************************************************************
//Configuração dos Timers
//********************************************************************
//Tempo do estouro do timer = t cliclo de máquina * (carga do registrador)*prescaler
//no caso, (carga do registrador)=65536-500 pois é 16 bits

//Timer1//
OpenTimer1(TIMER_INT_ON&T1_16BIT_RW&T1_SOURCE_INT&T1_PS_1_2&T1_OSC1EN_OFF&T1_SYNC_EXT_OFF);
WriteTimer1(CONST_T_TIMER1);
T1CONbits.TMR1ON = 0;    //bit que liga e desliga o timer

    
//********************************************************************
//Configuração das Interrupções
//********************************************************************
    
    RCONbits.IPEN = 0;		//Definindo para o PIC que todas as interrupções são de alta prioridade
    INTCONbits.GIE = 1;		//habilita a interrupção global
    INTCONbits.PEIE = 1;	//habilita as interrupções de periférico
    
    
    
    f_medindo			=0;
	f_medindoH			=0;	
	f_medindoL			=0;
	f_contagem_feita	=0;
    
    
    
    
    
	LED_VERMELHO = ON;
	InicializaLCD();
	LimpaLCD();
	PosicionaLCD(1, 1);
	StringLCD("BEM VINDO!      ");
	PosicionaLCD(2, 1);
	StringLCD("VALOR: R$ ,00   ");
	PosicionaLCD(2, 10);
	EscreveLCD(ValorPago + 0x30);
	for (i = 0; i < 150; i = i + 1) {
	PosicionaServo (Ang_Neg30);
	}
	LED_VERMELHO = ON;
	LED_VERDE = OFF;	
	
	
	
	
	
//LOOP INFINITO	

	while (ON) 
	{
		if (f_contagem_feita==0)
		{
			conta_pulso();
		}
		
		
		if(f_contagem_feita==1)
		{
		
		
			switch (ContadorPulsos) {
			case 1: // CASO RECONHEÇA A MOEDA DE 1 REAL
				if (ContagemReal < ValorPago){
				ContagemReal += 1;
				MostraValorLCD();
				}    
				break;
			case 2: // CASO RECONHEÇA A MOEDA DE 50 CENTAVOS GROSSA
				if (ContagemReal < ValorPago) {
					for (i = 0; i < 50; i = i + 1) {
						ContagemCent = ContagemCent + 1;
						CentavosParaReal();
						}
						MostraValorLCD();
	            	}
				break;
			case 3: // CASO RECONHEÇA A MOEDA DE 50 CENTAVOS FINA
				if (ContagemReal < ValorPago) {
					for (i = 0; i < 50; i = i + 1) {
						ContagemCent = ContagemCent + 1;
						CentavosParaReal();
						}
						MostraValorLCD();
	                }
	            
				break;
			case 4: // CASO RECONHEÇA A MOEDA DE 25 CENTAVOS
					if (ContagemReal < ValorPago) {
						for (i = 0; i < 25; i = i + 1) {
							ContagemCent = ContagemCent + 1;
							CentavosParaReal();
						}
						MostraValorLCD();
					}
				
				break;
			case 5: // CASO RECONHEÇA A MOEDA DE 10 CENTAVOS
					if (ContagemReal < ValorPago) {
						for (i = 0; i < 10; i = i + 1) {
							ContagemCent = ContagemCent + 1;
							CentavosParaReal();
						}
						MostraValorLCD();
					}
				
				break;
			case 6: // CASO RECONHEÇA A MOEDA DE 5 CENTAVOS
					if (ContagemReal < ValorPago) {
						for (i = 0; i < 5; i = i + 1) {
							ContagemCent = ContagemCent + 1;
							CentavosParaReal();
						}
						MostraValorLCD();
				}
				break;
			}
		
			f_contagem_feita=0;
			ContadorPulsos=0;
		}	
		
		
		
		
		if (ContagemReal >= ValorPago) 
		{ // SE O VALOR INSERIDO FOR MAIOR OU IGUAL O VALOR NECESSÁRIO
			LimpaLCD();
			PosicionaLCD(1, 5);
			StringLCD("VALOR PAGO");
			PosicionaLCD(2, 5);
			StringLCD("BOA VIAGEM!");
			Delay1KTCYx(250);
			LED_VERDE = 1;
			LED_VERMELHO = 0;
			AcionaServo = 1;
			if (AcionaServo == 1)
			{
				AcionaServo = 0;
				ContagemReal=0;
				ContagemCent=0;
				
				for (i = 0; i < 250; i = i + 1) 
				{
					PosicionaServo (Ang_90);
				}
			
			if (SENSOR_SAIDA == 0){
				for (i = 0; i < 50; i = i + 1) 
				{
					PosicionaServo (Ang_Neg30);
				}	
					LED_VERMELHO = ON;
					LED_VERDE = OFF;
					InicializaLCD();
					LimpaLCD();
					PosicionaLCD(1, 1);
					StringLCD("BEM VINDO!      ");
					PosicionaLCD(2, 1);
					StringLCD("VALOR: R$ ,00   ");
					PosicionaLCD(2, 10);
					EscreveLCD(ValorPago + 0x30);	
				
		}
				
				
			
					
			}
		}
		
		
		
		
			
	}//FECHA WHILE
} // END MAIN 
    
