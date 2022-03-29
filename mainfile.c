# include "config.h"
int count=0;

int timer0_limit=390;
int pwm=0;
char segment[5]={0x01,0x02,0x04,0x08};
void __interrupt() my_isr(void)
{
    if(INTCONbits.TMR0IF == 1)
    {
        //INTCONbits.TMR0IF=0;
        count++;
        if(count <= pwm)
        {
            PORTD=0xFF;
        }
        else
        {
            PORTD=0x00;
        }
        
        if(count >= timer0_limit)   
        {
            //PORTD=~PORTD;
            count=0;
        }
        
        //PORTD=~PORTD;
        //PORTDbits.RD4=~PORTDbits.RD4;
        /*
        PORTD=segment[count];
        count++;
        if(count>3)  
            count=0;
        */
        INTCONbits.TMR0IF=0; 
    }
   /* if(INTCONbits.INTF == 1)
    {
        timer0_limit++;
        INTCONbits.INTF == 0;
    }
    */
    
}

void main()
{
    TRISD=0x00;
    PORTD=0x00;
    INTCONbits.GIE=1; //enable global interrupt
    INTCONbits.PEIE=1;//enable peripheral interrupa
    INTCONbits.TMR0IE=1;//enable timer one interrupt
    INTCONbits.TMR0IF=0;//clear the interrupt flag
    //INTCONbits.INTE=1; //enable external interuuptu
    ei();
    //configuret the timer 1 with option resgister
   // OPTION_REGbits.nRBPU=0;//internal instruction cycle clock
   // OPTION_REGbits.INTEDG=0;//internal instruction cycle clock
    
    OPTION_REGbits.T0CS=0;//internal instruction cycle clock
    OPTION_REGbits.T0SE=0;//edege selsect 
    OPTION_REGbits.PSA=1;//prescalar assigned to timer 0
    //select the prescalar as 1:256
    OPTION_REGbits.PS0=0;
    OPTION_REGbits.PS1=0;
    OPTION_REGbits.PS2=0;
    
    while(1)
    {
        pwm=pwm+1;
        if(pwm >= timer0_limit/10)
            pwm=timer0_limit/20;
        __delay_ms(1000);
    }
    
            
}
