/*
 * File:   12f1840_1.c
 * Author: hugues
 *
 * Created on 6 janvier 2016, 14:39
 */

#include <xc.h>
#include <pic12f1840.h>
#include <String.h>
/*
 *
 */
// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

#define _XTAL_FREQ 32000000


#define taille_max 15
char chaine_a_emettre[taille_max+2];
char car;
int i=0;
char  command[20];
char reception[10];




int compare(const char* chaine1, const char* chaine2);

void bouilloire_mode(char val);

void COM_Puts(char *s);
void interrupt liaison_serie(void);

int main() {
    OSCCON = 0x70;          // switch to 8MHz system clock
    APFCON = 0x00;
    ADCON0 = 0x00;
    ANSELA = 0x00;          // digital IO
    PORTA = 0x00;

                            //   I/O    //
  TRISA0 = 0;
  TRISA1 = 1;
  TRISA2 = 1;
  TRISA3 = 1;
  TRISA4 = 0;
  TRISA5 = 0;
                            //   pull up    //
 // WPUA1 = 1;
  WPUA2 = 1;
  WPUA3 = 1;
  nWPUEN=0;

                            //   liaison serie    // p 270
    SYNC = 0;               // SYNC=0, BRGH=0, BRG16=0 => 9600 bits/s
    BRGH = 0;
    BRG16 = 0;
    SPBRG = 51;             // 51 -> 9600

    SPEN = 1;               // Serial Enable (config. broches pour serie)
    TXEN = 1;               // Transmission valide
    CREN = 1;               // Reception valide

    GIE = 1;                // Autorisation des interruptions au plan global
    PEIE = 1;               // Autorisation des interruptions des peripheriques
    RCIE = 1;               // Autorisation des ITs en reception

    RA4=1;
    RA5=1;

  while(1)
    {

    }
}
void interrupt liaison_serie(void)
{
    if (RCIF==1)                // identification de la source IT = reception
    {
        car = RCREG;             // lecture du registre de reception de l'EUSART

        if(car=='e' || car=='a' || car=='u' || car=='o' || car=='n' || car=='0' || car=='6' || car=='7' || car=='8' || car=='9' || car=='|'){
            reception[i]=car;
            i++;
             
            if(compare( &reception, "eau60")){
                bouilloire_mode(1);
                COM_Puts("ok60|");
                i=10;
            }else if(compare( &reception, "eau70")){
                bouilloire_mode(2);
                COM_Puts("ok70|");
                i=10;
            }else if(compare( &reception, "eau80")){
                bouilloire_mode(3);
                COM_Puts("ok80|");
                i=10;
            }else if(compare( &reception, "eau90")){
                bouilloire_mode(4);
                COM_Puts("ok90|");
                i=10;
            }else if(compare( &reception, "eauon")){
                COM_Puts("okon|");
                RA4=0;
                __delay_ms(100);
                RA4=1;
                i=10;
            }

            if(car=='|' || i>9){
              for(i=0;i<10;i++)
                   reception[i]="";
               i=0;
            }
        }
    }
    if (TXIF && TXIE)                       // identification de la source IT = transmission
    {
         i=0;
        car = chaine_a_emettre[i];          // recuperation du caractere depuis chaine_a_emettre
        while(car!='\0'){

            TXREG = car;                    // copie caractere dans registre de transmission
            __delay_ms(1);                  // contre les erreurs d'envoie
            i ++;                           // incrementation du comteur de caractere
            car = chaine_a_emettre[i];      // recuperation du caractere depuis chaine_a_emettre
        }
    TXIE = 0;
    }
}

void COM_Puts(char *s)
{
    i=0;
    while((car = s[i]) != '\0')             // tant que pas fin de chaine
    {
        chaine_a_emettre[i] = car;          // copie de car dans chaine_a_emettre
        i++ ;                               // incrementation de l'indice
    }
    chaine_a_emettre[i] = '\r';             // ajout le saut de ligne dans chaine_a_emettre
    chaine_a_emettre[i] = '\0';             // ajout caractere 'fin de chaine' dans chaine_a_emettre
    TXIE = 1;                               // validation interruption emission
}

int compare(const char* chaine1, const char* chaine2)
{   int e=0;
    for(e=0;e<strlen(chaine2);e++)
        if( chaine1[e] != chaine2[e])
            return 0;
    return 1;
}

void bouilloire_mode(char val){

    for(int e=0; e<val; e++){
        RA5=!RA5;
        __delay_ms(100);
        RA5=1;
        __delay_ms(500);
    }
}