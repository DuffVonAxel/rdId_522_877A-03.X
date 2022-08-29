/*
 * File:   rdId_522_877A-02.c
 * Author: Fred_Dell
 *
 * Created on 28 de Agosto de 2022, 14:39
 */
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>

#define _LCD_
#include "biblioteca_v18.h"
#include "spiSoft_v01.h"
#include "mfrc522_v01.h"

char key[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
//char writeData[]={"Duff Von Axel"};// 
char writeData[]={"_____________"};// 

/* Teste funcional */
//void main(void)
//{
//	char ddd[]={"________"};
//	char eee[]={"____________"};
//	char ggg[]={"______"};
//	char fff[]={"____"};
//
//	char tst,a=0,ttt;													// 
//	
//	char z;
//	
//#define LedVm1	PORTCbits.RC2	// 1a saida
//#define LedAm1	PORTCbits.RC6	// 2a saida
//#define LedVd1	PORTCbits.RC1	// 3a saida
//#define LedAz1	PORTCbits.RC7	// 4a saida
//	
//	TRISC=0x39;
//	PORTC=0x00;
////	LedVm1=1;
//	lcdIniciar(&PORTD,lcd20x4);													// LCD Iniciar.
//	
//	lcdTexto("MFRC522 -2",1,1);													// Mensagem no LCD.
//	lcdCaracter('>',2,1);
//	lcdCaracter('>',3,1);
////	LedVm1=0;
//	spiSoftIniciar();															// SPI Iniciar.
//	mfrc522Iniciar();															// RFID Iniciar.
//	
//	eepromLoad();
//	
//	while(1)
//	{
////		
//		/*Sequencia funcional*/					//+
//		tst = procura_tag(PICC_REQIDL, fff);	//|
//		lcdCaracter(tst+'0',1,16);				//|
//		ttt=mfrc522Uid(ggg);					//|
//		lcdCaracter(ttt+'0',1,18);				//|
//		if(ttt==0)								//|
//		{										//|
//			z=tagSearch(ggg);					//|
//			lcdCaracter(z+'0',1,19);			//|
//			nonSense(ggg,eee);					//|
//			lcdHex2(eee,2,3);					//|
//			nonSense2(fff,ddd);					//|
//			lcdHex3(ddd,3,3);					//|
//		}										//|
//		/* Fim Sequencia */						//+
////		
//		
//		/* Indicador modo 'Run' */
//		if(a)lcdCaracter(0x7E,1,9);
//		else lcdCaracter(0x7F,1,9);
//		a=~a;
//		__delay_ms(500);
//		/* Fim indicador */
//	}
//}
/* Fim teste funcional */

/* Sob teste 250822 */
// Tipo da TAG:
//0x0044 = Mifare_UltraLight
//0x0004 = Mifare_One (S50)
//0x0002 = Mifare_One (S70)
//0x0008 = Mifare_Pro (X)
//0x0344 = Mifare_DESFire
void main()
{
	char msg[]={"________________"};
	
	char TAG[]={"0000"};
	char tagAsc[]={"________"};
	
	char UID[]={"000000"};
	char uidAsc[]={"____________"};
	
	char VER[]={"__"};
	char verAsc[]={"____"};
	
	char TagType;
	char tagTypeAsc[]={"____"};

	char size;
	char sizeAsc[]={"____"};

	char i,h,j,k,a=0,b=0,c=0,d;

	//Inicializa display
	lcdIniciar(&PORTD, lcd20x4);
	
	spiSoftIniciar();
	mfrc522Iniciar();
	
	lcdTexto("Fred", 1, 1);
	__delay_ms(500);
	
	//inicializa o modulo RFID
//	MFRC522_Init();
	__delay_ms(1000);

	/* Inicia msg */
	lcdTexto(tagAsc, 3, 1);
	lcdTexto(uidAsc, 4, 1);
	lcdTexto(sizeAsc, 1, 10);
	lcdTexto(verAsc, 2, 1);
	lcdTexto(msg, 1, 1);
	/* Fim Inicia msg */
	
	while (1)
	{
		if(a)lcdCaracter(0x7E,1,20);
		else lcdCaracter(0x7F,1,20);
		a=~a;
		
		/**/
//		d=MFRC522_Request(VERSIONREG, VER);
		d=procura_tag(VERSIONREG, VER);
		lcdCaracter(d+'0',2,15);
		if(d==0)
		{
			hex2Ascii(VER,verAsc,2);	// 
			lcdTexto(verAsc, 2, 1);
		}

		c=procura_tag(PICC_REQIDL, TAG); // Tipo da TAG? ok
//		c=MFRC522_Request(PICC_REQIDL, TAG); //
		lcdCaracter(c+'0',3,15);
		if(c==0)
		{
			hex2Ascii(TAG,tagAsc,4);	// 
			lcdTexto(tagAsc, 3, 1);
		}

		/* Esse bloco funciona...*/
		b = MFRC522_AntiColl(UID);//ok
//		b=mfrc522Uid(UID); //ok
		lcdCaracter(b+'0',4,15);
		if(b==0) 
		{ 
			hex2Ascii(UID,uidAsc,6);	// 
			lcdTexto(uidAsc, 4, 1);
		}
		/**/
//		MFRC522_ReadCardSerial(UID);
//		hex2Ascii(UID,uidAsc,6);
//		lcdTexto(uidAsc, 4, 1);
		/**/
//		k=MFRC522_isCard(&TagType);
//		lcdCaracter(k+'0',2,17);
//		hex2Ascii(&TagType,tagTypeAsc,4);
//		lcdTexto(tagTypeAsc, 2, 1);
		/**/
//		if (MFRC522_isCard(&TagType))
//		{
//			//Exibe o tipo do cartao no display
//			//         ByteToHex( Lo(TagType), msg );
//			//         ByteToHex( Hi(TagType), msg+2 );
//			ByteToHex(TagType, msg);
//			//         Lcd_Out( 1, 1, "TAG TYPE: " );
//			lcdTexto("TAG TYPE: ", 2, 1);
//			lcdTexto(msg, 2, 11);
//
//			//Faz a leitura do numero de serie
//			if (MFRC522_ReadCardSerial(&UID))
//			{
//				//Posiciona o cursor 
//
//				for (i = 0; i < 5; i++)
//				{
//					ByteToHex(UID[i], msg);
//					lcdTexto(msg, 1, i + 1);
//				}
		/**/
				size = MFRC522_SelectTag(UID);
				hex2Ascii(&size,sizeAsc,2);	// 
				lcdTexto(sizeAsc, 2, 9);
				/**/
//			}
//			Tenta realizar a autenticaçao A do setor 1( blocos: 4 - 7 )
//			bloco de autenticaçao é o 7
				/**/
				h=MFRC522_Auth(PICC_AUTHENT1A, 7, key, UID);
				j=MFRC522_Auth(PICC_AUTHENT1B, 7, key, UID);
				lcdCaracter(h+'0',3,17);
				lcdCaracter(j+'0',3,18);
//			if (MFRC522_Auth(PICC_AUTHENT1A, 7, key, UID) == 0)
			if (h == 0)						// Se ==0 teste de gravacao Se ==10 testa leitura.
			{
				//Escreve algo no bloco 4
				i=MFRC522_Write(4, writeData);
				lcdCaracter(i+'0',4,17);
			} else if (j == 0)						//else if (MFRC522_Auth(PICC_AUTHENT1B, 7, key, UID) == 0)
			{
				//Escreve algo no bloco 4
				i=MFRC522_Write(4, writeData);
				lcdCaracter(i+'0',4,18);
			} else
			{
//				lcdTexto("Erro", 2, 1);
				lcdCaracter('?',4,19);
				continue;
			}
				/**/
			//Faz a leitura do bloco 4
			for(i=0;i<13;i++) writeData[i]=0x30; // Limpa mem p/ teste
			lcdTexto(writeData, 1, 1);
			
			i=MFRC522_Read(4, writeData);
			lcdCaracter(i+'0',4,20);
			if (i == 0) lcdTexto(writeData, 1, 1);

//			//Estado de hibernacao
//			MFRC522_Halt();
//			__delay_ms(50);
//		}
		__delay_ms(500);
	}
}
/* fim teste 250822 */