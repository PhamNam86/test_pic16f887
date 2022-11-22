//#include "D:\Proteus 8.8\pic16f887\test\LM35.h"

//LCD module connections
#define LCD_RS_PIN PIN_D0
#define LCD_RW_PIN PIN_D1
#define LCD_ENABLE_PIN PIN_D2
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7

#define LOA PIN_C6
//End LCD module connections
 
#include <16F887.h>
#fuses NOMCLR NOBROWNOUT NOLVP INTRC_IO
#device ADC = 10
#use delay(clock = 8MHz)
#include <lcd.h>
//#include <LCD.C>
void Button1()
{
if(input(PIN_A3)==0)
{
   OUTPUT_B(0x44);
}
else{
   OUTPUT_B(0x00);
}
}
float temp;
float fahr;
void Celius()
{
  //lcd_putc('\f');// Clear LCD
   lcd_gotoxy(3,1);                              // Go to column 3 row 1
   lcd_putc("Temperature:");
   lcd_gotoxy(1,2);     
   printf(lcd_putc,"%f",temp);// Display LM35 temperature result
   lcd_putc(0xdf);               
   lcd_putc("C ");
  
  if(temp > 130)
  {
  OUTPUT_B(0xFF);
  OUTPUT_HIGH(LOA);
    lcd_gotoxy(1,2);     
    printf(lcd_putc,"%f in Celius",temp);
    delay_ms(2000);
    lcd_putc('\f');
    lcd_gotoxy(3,1);                              // Go to column 3 row 1
    lcd_putc("Temperature:");
    lcd_gotoxy(5,2);     
    lcd_putc("Overload");
    delay_ms(2000);
  }
  if(temp >= 100 && temp <= 130)
  {
  OUTPUT_B(0xFF);
  OUTPUT_HIGH(LOA);
  delay_ms(1000);
  OUTPUT_B(0x00);
  OUTPUT_LOW(LOA);
  DELAY_MS(1000);
  }
  if(temp >50 && temp < 100)
  {
  OUTPUT_B(0xAA);
  OUTPUT_HIGH(LOA);
  delay_ms(500);
  OUTPUT_B(0x00);
  OUTPUT_LOW(LOA); 
  delay_ms(500);
  }
  
  if(temp > 0 && temp <= 50)
  {
   OUTPUT_B(0x55);
   delay_ms(500);
   OUTPUT_B(0x00);
   delay_ms(500);
   OUTPUT_LOW(LOA);  
  }
  if(temp <= 0)
  {
  OUTPUT_B(0x00);
  OUTPUT_LOW(LOA);
  }
}
void Fahrenheit()
{
   fahr= (temp*1.8)+32;
  // lcd_putc('\f');                                // Clear LCD
   lcd_gotoxy(3,1);                              // Go to column 3 row 1
   lcd_putc("Fahrenheit");
   lcd_gotoxy(1,2);
   printf(lcd_putc,"%f in Fahrenheit",fahr);               // Display LM35 temperature result
  if(fahr > 50)
  {
  while(input(pin_a4)==0){
  OUTPUT_B(0xCC);
  delay_ms(1000);
  OUTPUT_B(0x00);
  delay_ms(1000);
  }
  }
  else
  {
  OUTPUT_B(0x00);
  }
}
void BUTTON_3()
{
while(input(pin_a5)==0){OUTPUT_HIGH(LOA);}
OUTPUT_B(0XFF);

delay_ms(200);

while(input(pin_a5)==1){OUTPUT_LOW(LOA);}
OUTPUT_B(0X00);

delay_ms(200);
}
void main(){
  set_tris_a(0x11);
  set_tris_b(0x00);
  set_tris_c(0x00);
  setup_oscillator(OSC_8MHZ);                    // Set the internal oscillator to 8MHz
  setup_adc(ADC_CLOCK_INTERNAL);                 // ADC Module uses its internal oscillator
  setup_adc_ports(sAN0);                         // Configure AN0 pin as analog
  set_adc_channel(0);                            // Select channel 0 (AN0)
  lcd_init(); 
  lcd_putc('\f'); 
  // Initialize LCD module
  output_b(0x00);
  
  while(TRUE){
   
   temp = read_adc() / 2.048;// Read analog voltage and convert it to degree Celsius (0.489 = 500/1023)
   
   Celius();

   delay_ms(20);

   if(INPUT(PIN_A3)==0){
    Button1();
    }
   while(input(pin_a4)==0)
   {
   if(input(pin_a4)==0)
   Fahrenheit();
   if(input(pin_a4)==1)
   lcd_putc('\f'); 
   Celius();
   }
    if(INPUT(PIN_A5)==0){
    BUTTON_3();
    }
  }
}
   

