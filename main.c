
#include "16F877A.h" //Mikrodenetleyici baþlýk dosyasý tanýtýlýr.
#use delay(clock=4000000) //delay komutlarý için osilatör hýzý 4Mhz
#fuses XT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD,PUT
#use rs232( baud = 9600,xmit=pin_c6,rcv=pin_c7,parity=N,stop=1) 
#use fast_io(a)
unsigned int counter=0;
char envia[30];
int8 last=0;

int16 i=0;
int16 k=0;
int8 a=0;
int8 gelenKarakter[4];
int16 b =0;

int16 sayac=0;
int16 sayac1=0;
int16 sayac2=0;
int16 sayac3=0;
int16 sayac4=0;
int16 say = 0;
int8 h=0;

unsigned long int bilgi;
float voltaj,sicaklik;
int8 derece[8]={

0X01,0X03,0X02,0X06,0X04,0x0C,0X08,0X09};

int8 derece1[8]={
0X09,0X08,0x0C,0X04,0X06,0X02,0X03,0X01

};

 #int_timer0 
 void timer0_kesme()
   {
      set_timer0(6);
      
      say++;
      
      if(say==1000){
       say=0;
       
     //  output_toggle(PIN_D7);
       printf("%f'c",sicaklik);
     
      }
     
    }
    


 #int_RDA
void veri_gedli(void)
{
  disable_interrupts(int_RDA);
       
        gelenKarakter[0]=getch();   //tft ekrandan gelen verileri chara ayýrma
        gelenKarakter[1]=getch();
        gelenKarakter[2]=getch();
        gelenKarakter[3]=getch();
       
        
        if( gelenKarakter[0]==100){
          b=1;
          output_toggle(PIN_D5);
        }
         if( gelenKarakter[0]==101){
          b=2;
           output_toggle(PIN_D6);
        }
         
        if(b==1)  {  //tft adres belirleme komutu(p)
                   output_toggle(PIN_D5);
                    if(  gelenKarakter[0]==97){    //girilen açý deðeri 0<Q<10
                        sayac=(gelenKarakter[1]-48);
                        sayac3=sayac;
                      }
                    if(  gelenKarakter[0]==98){    //girilen açý deðeri 9<Q<100
                         sayac=(gelenKarakter[1]-48);
                         sayac1=(gelenKarakter[2]-48);
                         sayac3=(sayac*10)+sayac1;
                     }
                   if(  gelenKarakter[0]==99){    //girilen açý deðeri 99<Q
                         sayac=(gelenKarakter[1]-48);
                         sayac1=(gelenKarakter[2]-48);
                         sayac2=(gelenKarakter[3]-48);
                         sayac3=(sayac*100)+(sayac1*10)+sayac2;
                     }
                     
                }
           
              
        if(b==2)  {  //tft adres belirleme komutu(p)
                   output_toggle(PIN_D6);
                    if(  gelenKarakter[0]==97){    //girilen açý deðeri 0<Q<10
                        sayac=(gelenKarakter[1]-48);
                        sayac4=sayac;
                      }
                    if(  gelenKarakter[0]==98){    //girilen açý deðeri 9<Q<100
                         sayac=(gelenKarakter[1]-48);
                         sayac1=(gelenKarakter[2]-48);
                         sayac4=(sayac*10)+sayac1;
                     }
                   if(  gelenKarakter[0]==99){    //girilen açý deðeri 99<Q
                         sayac=(gelenKarakter[1]-48);
                         sayac1=(gelenKarakter[2]-48);
                         sayac2=(gelenKarakter[3]-48);
                         sayac4=(sayac*100)+(sayac1*10)+sayac2;
                     }
                    
                }
                   
 enable_interrupts(int_RDA); 
}

#INT_RB  
 void kesme(void){
  
  if(last==0 && INPUT(PIN_B4)==1){
      output_toggle(PIN_B1);   //VERÝ KONTORL LAMBASI
         if(INPUT(PIN_B5)==1){
           counter--;
          }
          else{
          counter++;
          }
         sprintf(envia,"page1.n1.val=%d",(unsigned int)counter);
      printf(envia);
      printf("\xFF\xFF\xFF");
       }
       last=INPUT(PIN_B4);
     
 }


void main()
{
       set_tris_d(0x00);
       output_d(0x00);
    
       
   
      
       
    setup_adc(adc_clock_div_32);
    setup_adc_ports(AN0);
    set_adc_channel(0);
    
       
        setup_timer_0(RTCC_INTERNAL|RTCC_DIV_4|RTCC_8_bit);
        
        enable_interrupts(INT_timer0);
        enable_interrupts(INT_RDA); 
        enable_interrupts(INT_RB);
        enable_interrupts(GLOBAL);
       
        set_timer0(6);
       
   while(TRUE)
   {
   
    if(interrupt_active(INT_RB)){
    h++;
    printf("%d",h);
    
    }
  
    if(sayac3==i){
     enable_interrupts(INT_timer0);
     
     }
     else{
     
    disable_interrupts(INT_timer0);
     
     }
   
   bilgi=read_adc();
voltaj=(0.0048828125*bilgi)*1000;
sicaklik=(voltaj/10);


   
   
   
    if(b==1)  {
  if(sayac3>i){ //GÝRÝLEN DEÐER ÝLE KONUMUN KARÞILAÞTIRILMASI
       
           for(i;i<sayac3;i++){
         
             for(a;a<9;a++){
             output_d(derece[a]);
             delay_ms(3);
             }
           
             a=0;
           }
       
        }
        
        if(i>sayac3){
            for(i;i>sayac3;i--){
           
                for(a;a<9;a++){
                  output_d(derece1[a]);
                  delay_ms(3);
                }
               
                  a=0;
             }
              
         }
    }
    
    
    
      if(b==2)  {
  if(sayac4>k){ //GÝRÝLEN DEÐER ÝLE KONUMUN KARÞILAÞTIRILMASI
       
           for(k;k<sayac4;k++){
         
             for(a;a<9;a++){
             output_c(derece[a]);
             delay_ms(3);
             }
           
             a=0;
           }
       
        }
        
        if(k>sayac4){
            for(k;k>sayac4;k--){
           
                for(a;a<9;a++){
                  output_c(derece1[a]);
                  delay_ms(3);
                }
               
                  a=0;
             }
              
         }
    }
   }

}




