/**
 * Auteur 
 * Maxime Champagne
 * 3 mars 2022
 * 
 * Modifié par
 * Jeff Truong
 * Date : 25 mars 2025
 * Desc:Générateur de formes d?onde (sinusoïdale, carrée, triangulaire)
 * 
 * SPI/main.c
 * 
*/
#include <stdio.h>
#include "mcc_generated_files/mcc.h"
#include "ecran.h"

#define MAX 60
#define BTN_PLUS PORTBbits.RB0  // Bouton "+"
#define BTN_MOINS PORTBbits.RB1 // Bouton "-"
uint8_t const sin[MAX] ={
              254,254,252,249,244,238,231,222,213,202,
              191,179,167,154,141,127,114,101,88,76,
              64,53,42,33,24,17,11,6,3,1,
              0,1,3,6,11,17,24,33,42,53,
              64,76,88,101,114,128,141,154,167,179,
              191,202,213,222,231,238,244,249,252,254};

uint8_t const car[MAX] ={
             0,0,0,0,0,0,0,0,0,0,
			  0,0,0,0,0,0,0,0,0,0,
			  0,0,0,0,0,0,0,0,0,0,
			  255,255,255,255,255,255,255,255,255,255,
			  255,255,255,255,255,255,255,255,255,255,
			  255,255,255,255,255,255,255,255,255,255};

uint8_t const tri[MAX] ={
            9,17,26,34,43,51,60,68,77,85,
			 94,102,111,119,128,136,145,153,162,170,
			 179,187,196,204,213,221,230,238,247,255,
			 247,238,230,221,213,204,196,187,179,170,
			 162,153,145,136,128,119,111,102,94,86,
			 77,68,60,51,43,34,26,17,9,0};

// ----------------------------------------------------------------------------
// Variables Globales
// ----------------------------------------------------------------------------
uint16_t Freq_actuelle = 0xEFB9 ; // Valeur initiale pour 20 Hz
uint8_t i = 0;
uint8_t E = 0; // Flag
char onde = 's';         // Forme d'onde actuelle ('s', 'c', 't')

// ----------------------------------------------------------------------------
// Prototypes
// ----------------------------------------------------------------------------
void out_dig(uint8_t x);
void myTimer1_ISR(void);
void sinus(void);
void Square_Pants(void);
void Doritos(void);

//void sinus_60(void);
//void Square_Pants_60(void);
//void Doritos_60(void);

/*
                         Main application
*/
void main(void)
{
    
    SYSTEM_Initialize();
    
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
    TMR1_SetInterruptHandler(myTimer1_ISR);

    SSPCON1bits.SSPEN = 1; // Activer SPI
    IO_RA5_SetHigh();

    uint8_t Read;
    uint8_t Frequence = 0;
    
    // Initialisation de l'écran
    videEcran();
    curseurPosition(0x00);
    printf("Press s,c,t :");
    curseurPosition(0x40);
    printf("Freq:");
    curseurPosition(0x54);
    printf("Onde:");
    
    while (1)
    {

        // Lire entrée UART
        if (EUSART1_is_rx_ready())
        {
            Read = EUSART1_Read();
            if (Read == '+')
            {
                if (Frequence < 4) Frequence++;
            }
            else if (Read == '-')
            {
                if (Frequence > 0) Frequence--;
            }
            else if (Read == 's' || Read == 'c' || Read == 't')
            {
                onde = Read;

                // Mise à jour de l'affichage de la forme d'onde
                curseurPosition(0x59);

                switch (onde)
                {
                    case 's':
                        printf("S"); // Sinus
                        break;
                    case 'c':
                        printf("C"); // Carré
                        break;
                    case 't':
                        printf("T"); // Triangle
                        break;
                }
            }
            // Ajuster fréquence.
            curseurPosition(0x45);
            switch (Frequence)
            {
                case 0: 
                    Freq_actuelle = 0xEFBB;
                    printf(" 20Hz"); 
                    break;
                case 1: 
                    Freq_actuelle = 0xF7DB; 
                    printf(" 40Hz"); 
                    break;
                case 2: 
                    Freq_actuelle = 0xFA92; 
                    printf(" 60Hz"); 
                    break;
                case 3: 
                    Freq_actuelle = 0xFBF0; 
                    printf(" 80Hz"); 
                    break;
                case 4: 
                    Freq_actuelle = 0xFCBD; 
                    printf("100Hz"); 
                    break;
            }
        }
        
        // Réagie à une interruption Timer1
        if (E == 1) 
        {
            E = 0;
            switch (onde)
            {
                case 's': 
                    sinus(); 
                    break;
                case 'c': 
                    Square_Pants(); 
                    break;
                case 't': 
                    Doritos(); 
                    break;
            }

        }
    }        
}

//---------------------------------------------------------------
// Routine d'interruption du Timer1
//---------------------------------------------------------------
void myTimer1_ISR(void)
{
    TMR1_WriteTimer(Freq_actuelle); // Recharge timer
    
    E = 1;                          // Flag d'exécution
    i++;
    if (i==MAX){
        i=0;
    }
}
    
//----------------------------------------------------------------
// Transmission au pot. d'une onde comprenant 60 points par cycle.
//----------------------------------------------------------------
//void sinus_60(void) {
//    uint8_t i;
//    for (i=0;i<MAX;i++) 
//    {
//        out_dig(sin[i]);
//        __delay_ms(1);
//    }
//}
//
//
//void Square_Pants_60(void) {
//    uint8_t i;  
//    for (i=0;i<MAX;i++) 
//    {
//        out_dig(car[i]);
//        __delay_ms(1);
//    }     
//}
//
//
//void Doritos_60(void) {
//    uint8_t i;
//    for (i=0;i<MAX;i++) 
//    {
//        out_dig(tri[i]);
//        __delay_ms(1);
//    }
//}

void sinus(void)
{
    out_dig(sin[i]);
}
void Square_Pants(void)
{
    out_dig(car[i]);
}
void Doritos(void) 
{
    out_dig(tri[i]);

}

//----------------------------------------------------------------
//  Transmission d'une donnee a la sortie du pot. numerique
//----------------------------------------------------------------
void out_dig(uint8_t x)
{
	IO_RA5_SetLow();   // selection du potentiometre
	SPI_ExchangeByte(0x11);  // ecriture, pot. 0
	SPI_ExchangeByte(x);
	IO_RA5_SetHigh();
	//__delay_ms(1);
}
