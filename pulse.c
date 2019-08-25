//----BIBLIOTECAS ---- //
#include <p18f4550.h>
#include <delays.h>
#include "lcd.h"
//--------------------//

//----- CONFIGURAÇÕES MICRO CONTROLADOR ----//
#pragma config	FOSC	=	HS
#pragma config	PWRT	=	ON
#pragma config	PBADEN	=	OFF
#pragma config	WDT	=	OFF
#pragma config	LVP	=	OFF
//------------------------------------------//

//----- DEFINES ----//
#define LED_VERDE PORTCbits.RC1
#define LED_VERMELHO PORTCbits.RC2
#define CONTROL PORTCbits.RC0
#define ON 1
#define OFF 0
//------------------//

// DECLARAÇÃO DE VARIÁVEIS //
int i = 0;
int ContadorPulsos = 0;
int ParalisaLCD = 1;
int ParalisaLCDfinal = 0;
float ReaisInseridos = 0.0; 
float ValorPedagio = 4.00;
float ValorRestante = 0.00;
// ----------------------- //


// ------- MAIN --------- //
void main(){

// ENTRADAS E SAÍDAS DO MICRO //
	TRISB = 0xFF;
	TRISC = 0x00;
	TRISD = 0x40;
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0b11111111;
// -------------------------- //
	LED_VERMELHO = ON;
	InicializaLCD();
	LimpaLCD();
	PosicionaLCD(1,1);
	StringLCD("BEM VINDO!");
	PosicionaLCD(2,1);
	StringLCD("VALOR: R$4,00");
	Delay1KTCYx(250);
	while (ON){					//LOOP INFINITO
		if(PORTBbits.RB6 == OFF){   // VERIFICA SE O SENSOR DE SAÍDA FOI ATIVADO
			Delay1KTCYx(50);
			CONTROL = ON;
			Delay1KTCYx(185);
			CONTROL = OFF;
			Delay1KTCYx(15);
			LED_VERDE = 0;
			LED_VERMELHO = ON;
			if (ParalisaLCD == OFF){
			LimpaLCD();
			PosicionaLCD(1,1);
			StringLCD("BEM VINDO!");
			PosicionaLCD(2,1);
			StringLCD("VALOR: R$4,00");
			i = 0;
			ContadorPulsos = 0;
			ParalisaLCD = OFF;
			ParalisaLCDfinal = OFF;
			ReaisInseridos = 0.0;
			ValorPedagio = 4.00;
			ValorRestante = 0.00;
			}
		}	
			
		if(PORTBbits.RB0 == OFF){		//SE MOEDA DE 1 REAL FOR RECONHECIDA, ENVIAR 1 PULSO
			Delay1KTCYx(100);
			ParalisaLCD = OFF;
			ContadorPulsos = 1;
			PORTDbits.RD0 = OFF;
			Delay1KTCYx(10);
			PORTDbits.RD0 = ON;
			Delay1KTCYx(10);
			PORTDbits.RD0 = OFF;
							}

		if(PORTBbits.RB1 == OFF){		//SE MOEDA DE 50 CENTAVOS GROSSA FOR RECONHECIDA, ENVIAR 2 PULSOS
			Delay1KTCYx(100);
			ParalisaLCD = OFF;
			ContadorPulsos = 2;
			for(i=0; i<2; i=i+1){
				PORTDbits.RD0 = OFF;
				Delay1KTCYx(10);
				PORTDbits.RD0 = ON;
				Delay1KTCYx(100);
					}		
				}		

		if(PORTBbits.RB2 == OFF){		//SE MOEDA DE 50 CENTAVOS FINA FOR RECONHECIDA, ENVIAR 3 PULSOS
			Delay1KTCYx(100);
			ParalisaLCD = OFF;
			ContadorPulsos = 3;
			for(i=0; i<3; i=i+1){
				PORTDbits.RD0 = OFF;
				Delay1KTCYx(10);
				PORTDbits.RD0 = ON;
				Delay1KTCYx(100);
						}
								}

		if(PORTBbits.RB3 == OFF){		//SE MOEDA DE 25 CENTAVOS NOVA FOR RECONHECIDA, ENVIAR 4 PULSOS
			Delay1KTCYx(100);
			ParalisaLCD = OFF;
			ContadorPulsos = 4;
			for(i=0; i<4; i=i+1){
				PORTDbits.RD0 = OFF;
				Delay1KTCYx(10);
				PORTDbits.RD0 = ON;
				Delay1KTCYx(100);
			}			
								}						

		if(PORTBbits.RB4 == OFF){		//SE MOEDA DE 10 CENTAVOS FOR RECONHECIDA, ENVIAR 5 PULSOS
			Delay1KTCYx(100);
			ParalisaLCD = 0;
			ContadorPulsos = 5;
			for(i=0; i<5; i=i+1){
				PORTDbits.RD0 = OFF;
				Delay1KTCYx(10);
				PORTDbits.RD0 = ON;
				Delay1KTCYx(100);
			}		
								}

		if(PORTBbits.RB5 == OFF){		//SE MOEDA DE 5 CENTAVOS NOVA FOR RECONHECIDA, ENVIAR 6 PULSOS
			ParalisaLCD = 0;
			Delay1KTCYx(100);
			ContadorPulsos = 6;
			for(i=0; i<6; i=i+1){
				PORTDbits.RD0 = OFF;
				Delay1KTCYx(10);
				PORTDbits.RD0 = ON;
				Delay1KTCYx(100);
				}	
								}
		switch (ContadorPulsos){
			case 1:
				if (ParalisaLCD == OFF){
					if (ReaisInseridos < ValorPedagio){
					ReaisInseridos += 1.00;
					LimpaLCD();
					PosicionaLCD(1,1);
					StringLCD("R$1,00 INSERIDOS");
					PosicionaLCD(2,1);
					StringLCD("PEDAG. AUTOMAT.");
					Delay1KTCYx(250);
					ParalisaLCD = ON;
						}
					}
				break;
			case 2:
				if (ParalisaLCD == OFF){
					if (ReaisInseridos < ValorPedagio){
					LimpaLCD();
					PosicionaLCD(1,1);
					StringLCD("R$0,50 INSERIDOS");
					PosicionaLCD(2,1);
					StringLCD("PEDAG. AUTOMAT.");
					Delay1KTCYx(250);
					ReaisInseridos += 0.50;
					ParalisaLCD = ON;
						}
					}
				break;
			case 3:
				if (ParalisaLCD == OFF){
					if (ReaisInseridos < ValorPedagio){
					ReaisInseridos += 0.50;
					LimpaLCD();
					PosicionaLCD(1,1);
					StringLCD("R$0,50 INSERIDOS");
					PosicionaLCD(2,1);
					StringLCD("PEDAG. AUTOMAT.");
					Delay1KTCYx(250);
					ParalisaLCD = ON;
						}
					}
				break;
			case 4:
				if (ParalisaLCD == OFF){
					if (ReaisInseridos < ValorPedagio){
					ReaisInseridos += 0.25;
					LimpaLCD();
					PosicionaLCD(1,1);
					StringLCD("R$0,25 INSERIDOS");
					PosicionaLCD(2,1);
					StringLCD("PEDAG. AUTOMAT.");
					Delay1KTCYx(250);
					ParalisaLCD = ON;
						}
					}	
				break;
			case 5:
				if (ParalisaLCD == OFF){
					if (ReaisInseridos < ValorPedagio){
					ReaisInseridos += 0.10;
					LimpaLCD();
					PosicionaLCD(1,1);
					StringLCD("R$0,10 INSERIDOS");
					PosicionaLCD(2,1);
					StringLCD("PEDAG. AUTOMAT.");
					Delay1KTCYx(250);
					ParalisaLCD = ON;
						}
					}	
				break;
			case 6:
				if (ParalisaLCD == OFF){
					if (ReaisInseridos < ValorPedagio){
				ReaisInseridos += 0.05;
				LimpaLCD();
				PosicionaLCD(1,1);
				StringLCD("R$0,05 INSERIDOS");
				PosicionaLCD(2,1);
				StringLCD("PEDAG. AUTOMAT.");
				Delay1KTCYx(250);
				ParalisaLCD = ON;
					}
				}
				break;
			}
		if (ReaisInseridos >= ValorPedagio){
			if (ParalisaLCDfinal == OFF){
			LimpaLCD();
			PosicionaLCD(1,3);
			StringLCD("VALOR PAGO");
			PosicionaLCD(2,3);
			StringLCD("BOA VIAGEM!");
			Delay1KTCYx(250);
			ParalisaLCDfinal = ON;
			ParalisaLCD = OFF;
			CONTROL = ON;
			Delay1KTCYx(185);
			CONTROL = OFF;
			Delay1KTCYx(15);
			LED_VERDE = 1;
			LED_VERMELHO = 0;
			}
		}	
	}																									
}        

// ---------------------------------//
