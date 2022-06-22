/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 9/22/2017
Author  : 
Company : 
Comments: 


Chip type               : ATmega8A
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega8.h>

#include <delay.h>
#include <delay.h>
#include <stdio.h>
#include <stdlib.h>
// Alphanumeric LCD functions
#include <alcd.h>

// Declare your global variables here
char lcd[20],str[20],pick[60]={0},press_vec[60]={0},n=0,hr;
char up=0,count=0,i,max_index,start=0;
int presure,old,new,systole,max_pick,maximum,diastole,time;
float thr=0,time_vec[60]={0},tsum;

 float tabdil(unsigned int input)
{
float p;
p=input*.3168-42.77;
return p;
}
// Voltage Reference: AVCC pin
#define ADC_VREF_TYPE ((0<<REFS1) | (1<<REFS0) | (0<<ADLAR))

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | ADC_VREF_TYPE;
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=(1<<ADSC);
// Wait for the AD conversion to complete
while ((ADCSRA & (1<<ADIF))==0);
ADCSRA|=(1<<ADIF);
return ADCW;
}
// External Interrupt 1 service routine
interrupt [EXT_INT1] void ext_int1_isr(void)
{
// Place your code here
          PORTD&=~(1<<PORTD6);
         PORTD|=(1<<PORTD7);
         lcd_clear(); 
         lcd_gotoxy(2,0);
         lcd_puts("RELAX!!!");
         presure=read_adc(0);
        presure=tabdil(presure);
          while(presure>0 )
        {
        presure=read_adc(0);
        presure=tabdil(presure);
        }  
        //delay_ms(3000);
        PORTD&=~(1<<PORTD7);
        WDTCR=0X18;
        WDTCR=0X08;
         
}

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
// Place your code here
 time=time+2; //2.048ms=intrrupt timer0
}

// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
{
// Place your code here
 start=1;
 for(i=0;i<200;i++)
{
press_vec[i]=0;
pick[i]=0;
}       
}



void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRC=(0<<DDC6) | (1<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
// State: Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTC=(0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=Out Bit6=Out Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(1<<DDD7) | (1<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=0 Bit6=0 Bit5=T Bit4=T Bit3=T Bit2=P Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (1<<PORTD3) | (1<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 125.000 kHz
TCCR0=(0<<CS02) | (1<<CS01) | (1<<CS00);
TCNT0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2 output: Disconnected
ASSR=0<<AS2;
TCCR2=(0<<PWM2) | (0<<COM21) | (0<<COM20) | (0<<CTC2) | (0<<CS22) | (0<<CS21) | (0<<CS20);
TCNT2=0x00;
OCR2=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (1<<TOIE0);

// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Falling Edge
// INT1: Off
GICR|=(1<<INT1) | (1<<INT0);
MCUCR=(1<<ISC11) | (0<<ISC10) | (1<<ISC01) | (0<<ISC00);
GIFR=(1<<INTF1) | (1<<INTF0);

// USART initialization
// USART disabled
UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (0<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);

// Analog Comparator initialization
// Analog Comparator: Off
// The Analog Comparator's positive input is
// connected to the AIN0 pin
// The Analog Comparator's negative input is
// connected to the AIN1 pin
ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);

// ADC initialization
// ADC Clock frequency: 1000.000 kHz
// ADC Voltage Reference: AVCC pin
ADMUX=ADC_VREF_TYPE;
ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADFR) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
SFIOR=(0<<ACME);

// SPI initialization
// SPI disabled
SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);

// TWI initialization
// TWI disabled
TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTB Bit 0
// RD - PORTB Bit 1
// EN - PORTB Bit 2
// D4 - PORTB Bit 4
// D5 - PORTB Bit 5
// D6 - PORTB Bit 6
// D7 - PORTB Bit 7
// Characters/line: 16
lcd_init(16);

// Global enable interrupts
#asm("sei")

lcd_clear();
lcd_gotoxy(4,0);
   lcd_puts("WELCOME!");
   lcd_gotoxy(1,1);
   lcd_puts("DESIGNER R.K.");
   delay_ms(2000);
   lcd_clear();
   lcd_gotoxy(2,0);
   lcd_puts("PUT THE CUFF");
   lcd_gotoxy(0,1);
   lcd_puts("THEN PRESS START");
   delay_ms(500);     

while (1)
{
      // Place your code here
      if(start==1)
      {
          lcd_clear(); 
          lcd_gotoxy(2,0);
          lcd_puts("DON'T MOVE!!");
          delay_ms(70);      
          PORTD|=(1<<PORTD6);   //pump
          presure=read_adc(0); 
          presure=tabdil(presure);
          while(presure<160)
          {    
              
               presure=read_adc(0);
               presure=tabdil(presure);
                if(presure>0)     
                {
                 ftoa(presure,0,str);
                    sprintf(lcd,"PRESSURE IS:%4s",str);
                    //lcd_clear();
                    lcd_gotoxy(0,1);
                    lcd_puts(lcd);
                    }
          }
          PORTD&=~(1<<PORTD6);
          delay_ms(500);
          
        
          // Timer(s)/Counter(s) Interrupt(s) initialization on
          
          max_pick=0;
          count=0;   
          time=0;   
          while(presure>70)
          {
               old=read_adc(1);
               presure=read_adc(0);
               presure=tabdil(presure);
               delay_ms(50);//           inc/dec
               new=read_adc(1);
                  
               
                      ftoa(presure,0,str);
                    sprintf(lcd,"PRESSURE IS:%4s",str);
                    //lcd_clear();
                    lcd_gotoxy(0,1);
                    lcd_puts(lcd);
                
               // presure1=tabdil(presure);
     
               //delay_ms(50);
                 if (new>160) 
                 {
               if(new+2>old)
               {
                    up=1;
               } 
               else if(new<old+2)
               {
                    if(up)
                    {    
                         if(count==0)
                         { 
                         time=0;
                         //TCCR0=(0<<CS02) | (1<<CS01) | (1<<CS00); 
                         //TCNT0=0x00;
                         //TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (1<<TOIE0);  
                         }
                        /* lcd_clear();
                          ftoa(count,0,str);
                          sprintf(lcd,"pick:%3s",str);
                         //lcd_clear();
                         lcd_gotoxy(0,0);
                          lcd_puts(lcd); */
                         
                         
                         pick[count]=new;
                         press_vec[count]=presure;
                         time_vec[count]=time;
                         if(pick[count]>max_pick)
                         {    
                              
                              max_pick=pick[count];
                              max_index=count; 
                              
                         }
                         count++;  
                      
                 
                    }
               up=0;
               }
               }
          } 
        
          TCCR0&=0x00;
         if(count>0){ n=count-1;}
           lcd_clear();
           if (n>2)
           {
          count=0;
          tsum=0;
            for(i=0;i<n;i++)
          {    
               thr=time_vec[i+1]-time_vec[i];
               if(thr<1000 & thr>600)
               {
                   tsum=thr+tsum;
                   count++;
               }
          }
         
          
          maximum=press_vec[max_index];
          systole=press_vec[1];  
          diastole=(3*maximum-systole)/2.2;
          
        
          ftoa(systole,0,str);
          sprintf(lcd,"SYS:%3s",str);
          //lcd_clear();
          lcd_gotoxy(0,0);
          lcd_puts(lcd);
          lcd_puts("  ");
          //delay_ms(50);
          ftoa(diastole,0,str);
          sprintf(lcd,"DIA:%3s",str);
          //lcd_clear();
          //lcd_gotoxy(0,1);
          lcd_puts(lcd);
          
           if(count>0) {
          thr=tsum/count;
          hr = 60000/thr;
          ftoa(hr,0,str);
          sprintf(lcd,"H.RATE:%3s",str);
          lcd_gotoxy(2,1);
          lcd_puts(lcd); 
          }        
          delay_ms(100);
          }
          else
          {
            lcd_clear();
            lcd_gotoxy(2,0);
            lcd_puts("Cuff is not");
            lcd_gotoxy(1,1);
            lcd_puts("put correctly");
          }
          start=0;   
          
         PORTD&=~(1<<PORTD6);
         PORTD|=(1<<PORTD7);
        // delay_ms(9000);
        presure=read_adc(0);
        presure=tabdil(presure);
          while(presure>0)
        {
        presure=read_adc(0);
        presure=tabdil(presure);
        }   
        PORTD&=~(1<<PORTD7);
      }
      
}
}
