//roll no: 3847
//rachit thakur
#include<p18f4550.h>
#include "vector_relocate.h"

#include<stdlib.h>


#define RS PORTCbits.RC0
#define RW PORTCbits.RC2
#define E PORTCbits.RC1

unsigned char enkey[4];
unsigned char key[]="8792";


int i,k,sw=0,seed=0;
unsigned char ran[6];
unsigned char k0[]="U GET 2 ATTEMPTS";
unsigned char k3[]="1ATMP.REMAINING";
unsigned char k4[]="ALARM ON......";
unsigned char k7[]="OLD PASSWORD :";
unsigned char k8[]="NEW PASSWORD :";
unsigned char k9[]="PASSKEY CHANGED";
unsigned char sms[]="HEY";
unsigned char sms_report[]="SMS Sent..";
unsigned char sms_indication[]="AT+CNMI=1,2,0,0,0\r";
unsigned char sms_terminate=0X1A;
unsigned char enter=0X0D;


void ms_delay(unsigned int time);
void command(unsigned char cmd);
void LCD_datawrite(unsigned char data);

	      unsigned char rx_data(void)
	    {
		    while(PIR1bits.RCIF==0);
		    return RCREG;
		    }

		    void transmit(unsigned char *serial)
{
      for(i=0;serial[i]!='\0';i++)
	{
		while(PIR1bits.TXIF==0);
		TXREG=serial[i];
	}
}


void tx_data(unsigned char serial_data)
{
		TXREG=serial_data;
		while(PIR1bits.TXIF==0);

}


void display(unsigned char *array)
{
		for(i=0;array[i]!='\0';i++)
		{
		LCD_datawrite(array[i]);
		}
}
		



void check()
{
	command(0X01);//clear LCD
	command(0X0E);//cursor off
	command(0X80);//Address of 1st position

	for(i=0;i<4;i++)
	{
		LCD_datawrite(ran[i]); 
		ms_delay(200);
	}		
}
void motor()
{
			PORTEbits.RE2=1;	
			ms_delay(500);
			PORTEbits.RE2=0;
}
void open()
{
		PORTEbits.RE0=1;
		PORTEbits.RE1=0;
		motor();		
}

void close()
{
		PORTEbits.RE0=0;
		PORTEbits.RE1=1;
		motor();		
}

void keypad()
{
			int t=0;
			while(t<4)
			{
					seed++;
					seed=seed%30000;
					TRISB=0;
					PORTB=0XF0;
					TRISB=0XF0;
					if(PORTB!=0XF0)
				{
					ms_delay(110);
					if(PORTB!=0XF0)
					{
						PORTBbits.RB0=0;
						PORTBbits.RB1=1;
						PORTBbits.RB2=1;
						PORTBbits.RB3=1;
						if(PORTB==0XEE)
						{
							LCD_datawrite('*');
							enkey[t]='1';t++;
						}	
						else if(PORTB==0XDE)			
						{
							LCD_datawrite('*');
							enkey[t]='2';t++;
						}
						else if(PORTB==0XBE)			
						{
							LCD_datawrite('*');
							enkey[t]='3';t++;
						}
						/*else if(PORTB==0X7E)			
						{
							LCD_datawrite('*');
							enkey[t]='3';
						}*/
		
						PORTBbits.RB0=1;
						PORTBbits.RB1=0;
						PORTBbits.RB2=1;
						PORTBbits.RB3=1;
						if(PORTB==0XED)
						{
							LCD_datawrite('*');
							enkey[t]='4';t++;
						}
						else if(PORTB==0XDD)			
						{
							LCD_datawrite('*');
							enkey[t]='5';t++;
						}
						else if(PORTB==0XBD)			
						{
							LCD_datawrite('*');
							enkey[t]='6';t++;
						}
						/*else if(PORTB==0X7D)			
						{
							LCD_datawrite('*');
							enkey[t]='7';
						}*/
		
						PORTBbits.RB0=1;
						PORTBbits.RB1=1;
						PORTBbits.RB2=0;
						PORTBbits.RB3=1;
						if(PORTB==0XEB)
						{
							LCD_datawrite('*');
							enkey[t]='7';t++;
						}
						else if(PORTB==0XDB)			
						{
							LCD_datawrite('*');
							enkey[t]='8';t++;
						}
						else if(PORTB==0XBB)			
						{
							LCD_datawrite('*');
							enkey[t]='9';t++;
						}
						/*else if(PORTB==0X7B)			
						{
							LCD_datawrite('*');
							enkey[t]='B';
						}*/
		
						PORTBbits.RB0=1;
						PORTBbits.RB1=1;
						PORTBbits.RB2=1;
						PORTBbits.RB3=0;
						/*if(PORTB==0XE7)
						{
							LCD_datawrite('*');
							enkey[t]='C';
						}*/
						 if(PORTB==0XD7)			
						{
							LCD_datawrite('*');
							enkey[t]='0';
							t++;
						}
						/*else if(PORTB==0XB7)			
						{
							LCD_datawrite('*');
							enkey[t]='E';
								open();	
						}*/
						/*else if(PORTB==0X77)			
						{
							LCD_datawrite('*');
							enkey[t]='F';
							close();
						}*/
						
					}
				}	
			}
}

void intializelcd()
{
	
	command(0X38);//initialisation of LCD
	command(0X01);//clear LCD
	command(0X0E);//cursor on
	command(0X80);//Address of 1st position


}
void password()
{
	unsigned char k[]="ENTER THE KEY:";
	intializelcd();
	for(i=0;i<14;i++)
	{
		LCD_datawrite(k[i]); 
	//	ms_delay(20);
	}
	command(0XC0);//next line	
	keypad();
}
void keypad3()
{
			int t=0;
			while(t<1)
			{
					seed++;
					seed=seed%30000;
					TRISB=0;
					PORTB=0XF0;
					TRISB=0XF0;
					if(PORTB!=0XF0)
				{
					ms_delay(110);
					if(PORTB!=0XF0)
					{
					
		
						PORTBbits.RB0=1;
						PORTBbits.RB1=1;
						PORTBbits.RB2=1;
						PORTBbits.RB3=0;


						if(PORTB==0X77)			
						{
							t++;
							close();
							
						}
						
					}
				}	
			}
}

int compare2()
{
	int flag=0;
	unsigned char k1[]="WRONG KEY!!!!";
	unsigned char k2[]="CORRECT KEY!!!!";
	for(i=0;i<4;i++)
	{
		if(enkey[i]!=ran[i])
		{
			flag=1;
			break;
		}
	}
	intializelcd();
	if(flag==1)
	{
		for(i=0;i<13;i++)
		{
			LCD_datawrite(k1[i]); 
		//	ms_delay(10);
		}
		
	}
	else
	{
		for(i=0;i<15;i++)
		{
			LCD_datawrite(k2[i]); 
		//	ms_delay(10);
		}
		
	}
	ms_delay(1000);
	return(flag);
}


void gsm()
{

unsigned char sms_format[]="AT+CMGF=1\r";
unsigned char char_set[]="AT+CSCS=\"GSM\"\r";
unsigned char sms_write[]="AT+CMGS=\"9960525487\"\r";

        transmit(sms_format);
        ms_delay(10);
        transmit(char_set);
        ms_delay(10);
        transmit(sms_write);


}
void gsmwarning()
{
		unsigned char data4[]="SOMEONE ENTERED WRONG PASSWORD ON THE LOCKER.CHECK LOCKER FOR SAFETY.\r";
		gsm();
        ms_delay(10);
        transmit(data4); 
        ms_delay(10);
        tx_data(sms_terminate);
        ms_delay(10);
        tx_data(enter);
}

void gsmpasschange()
{
			
			unsigned char data5[]="PASSWORD CHANGED SUCCESSFULLY!!!\r";
			gsm();
        ms_delay(10);
        transmit(data5); 
        ms_delay(10);
        tx_data(sms_terminate);
        ms_delay(10);
        tx_data(enter);

}
void gsmalarm()
{
			
			unsigned char data5[]="ALARM ON!!!!\r";
			gsm();
        ms_delay(10);
        transmit(data5); 
        ms_delay(10);
        tx_data(sms_terminate);
        ms_delay(10);
        tx_data(enter);

}

void gsmpart()
{
		int z;
		unsigned char otp[]="ENTER THE OTP:";
		unsigned char lockopen[]="THE LOCK IS OPEN";
		gsm();
		srand(seed);
		for(i=0;i<4;i++)
		{
				ran[i]=(rand()%10)+48;
		}
		ran[4]='\r';
		ran[5]='\0';
        ms_delay(10);
        transmit(ran); 
        ms_delay(10);
        tx_data(sms_terminate);
        ms_delay(10);
        tx_data(enter);
	    ms_delay(9000);
		intializelcd();
		for(i=0;i<14;i++)
		{
			LCD_datawrite(otp[i]); 
		//	ms_delay(10);
		}
		command(0XC0);//next line	
		keypad();

			ms_delay(200);
			z=compare2();
			
			if(z==1)
			{
					command(0XC0);//next line							
					for(i=0;i<14;i++)
					{
					LCD_datawrite(k4[i]); 
					//	ms_delay(20);
					}
					PORTAbits.RA0=1;

					gsmwarning();
					ms_delay(9000);
					gsmalarm();	
								
					ms_delay(12000);
					PORTAbits.RA0=0;
					PORTAbits.RA1=0;	
			}
			else
			{
					intializelcd();
					for(i=0;i<16;i++)
					{
						LCD_datawrite(lockopen[i]); 
					//	ms_delay(10);
					}
					PORTAbits.RA1=0;
					open();
					command(0XC0);//next line	
					keypad3();		
			}
}

int compare()
{
	int flag=0;
	unsigned char k1[]="WRONG KEY!!!!";
	unsigned char k2[]="CORRECT KEY!!!!";
	for(i=0;i<4;i++)
	{
		if(enkey[i]!=key[i])
		{
			flag=1;
			break;
		}
	}
	intializelcd();
	if(flag==1)
	{
		for(i=0;i<13;i++)
		{
			LCD_datawrite(k1[i]); 
		//	ms_delay(10);
		}
		ms_delay(2000);
	}
	else
	{
		for(i=0;i<15;i++)
		{
			LCD_datawrite(k2[i]); 
		//	ms_delay(10);
		}
		ms_delay(2000);
	}
	return(flag);
}


void keypad2()
{
	int t=0;
			while(t<1)
			{
					seed++;
					seed=seed%30000;
					TRISB=0;
					PORTB=0XF0;
					TRISB=0XF0;
					if(PORTB!=0XF0)
				{
					ms_delay(110);
					if(PORTB!=0XF0)
					{
						PORTBbits.RB0=0;
						PORTBbits.RB1=1;
						PORTBbits.RB2=1;
						PORTBbits.RB3=1;
						if(PORTB==0XEE)
						{
							sw=1;t++;
						}	
						else if(PORTB==0XDE)			
						{
							sw=2;t++;
						}

					}
				}	
			}
}

void swtch()
{
	unsigned char k5[]="1.OPEN LOCK";
	unsigned char k6[]="2.CHANGE PASSKEY";
	intializelcd();
	for(i=0;i<11;i++)
	{
		LCD_datawrite(k5[i]); 
	//	ms_delay(20);
	}
	command(0XC0);//next line	
	for(i=0;i<16;i++)
	{
		LCD_datawrite(k6[i]); 
	//	ms_delay(20);
	}
	keypad2();
}


void main()
{
	int z,z1;

	TRISE=0X00;
	PORTE=0X00;
	TRISD=0X00;

	ADCON1=0X0F;//portA,B and E as digital i/o port
	INTCON2bits.RBPU=0;
	TRISB=0XF0;//this means last 4 as output 
	PORTB=0XF0;


	TRISA=0X00;
	PORTA=0X00;

	TRISC=0x80;
	E=0;
	SPBRG=0x4D;
	TXSTA=0x20;
	RCSTA=0x90;

	a:

	swtch();
	
	if(sw==1)
	{
				intializelcd();
				
				for(i=0;i<16;i++)
				{
						LCD_datawrite(k0[i]); 
						//	ms_delay(20);
				}
				ms_delay(2000);
				
				password();
				
				ms_delay(200);
				z=compare();
				
				if(z==1)
				{
							
							gsmwarning();
							ms_delay(5000);
							intializelcd();
							
							for(i=0;i<15;i++)
							{
									LCD_datawrite(k3[i]); 
									//	ms_delay(20);
							}
							ms_delay(6000);
							
							
							password();
							ms_delay(200);
							z1=compare();
							if(z1==1)
							{
									ms_delay(1000);
									gsmalarm();
									command(0XC0);//next line							
									for(i=0;i<14;i++)
									{
										LCD_datawrite(k4[i]); 
										//	ms_delay(20);
									}

									PORTAbits.RA0=1;
									ms_delay(20000);
									PORTAbits.RA0=0;
									goto a;	
							}
							else
							{
									z=z1;
							}
				
				
				}
				if(z==0)
				{
							
							PORTAbits.RA1=1;
							gsmpart();
							goto a;	
				}

	}
	else
	{
			intializelcd();
		
			for(i=0;i<14;i++)
			{
				LCD_datawrite(k7[i]); 
			//	ms_delay(20);
			}
			command(0XC0);//next line	
			keypad();

			ms_delay(200);
			z=compare();
			
			if(z==1)
			{	
					command(0XC0);//next line							
					for(i=0;i<14;i++)
					{
					LCD_datawrite(k4[i]); 
					//	ms_delay(20);
					}
					PORTAbits.RA0=1;

					gsmwarning();
					ms_delay(9000);
					gsmalarm();

					ms_delay(12000);
					PORTAbits.RA0=0;
					goto a;	
			}
			else
			{
					ms_delay(1500);
					intializelcd();
				
					for(i=0;i<14;i++)
					{
						LCD_datawrite(k8[i]); 
					//	ms_delay(20);
					}
					command(0XC0);//next line	
					keypad();
					ms_delay(100);
					for(i=0;i<4;i++)
					{
						key[i]=enkey[i]; 
					//	ms_delay(20);
					}
					
					gsmpasschange();
					
					intializelcd();
					for(i=0;i<15;i++)
					{
						LCD_datawrite(k9[i]); 
					//	ms_delay(20);
					}
					ms_delay(9000);					
					goto a;

			}
			

								
	}


	while(1);
} 

void ms_delay(unsigned int time)
{
		unsigned int i,j;
		for(i=0;i<time;i++)
		{
		   for(j=0;j<710;j++)//fosc=48MHz
		      {
		      }
		}
}
void command(unsigned char cmd)
{
		PORTD=cmd; //for giving command to lcd register D is used
		RS=0;
		RW=0;
		E=1;//used for giving high to low pulse to input data to LCD
		ms_delay(10);
		E=0;
}
 void LCD_datawrite(unsigned char data)
{
		PORTD=data;
		RS=1;
		RW=0;//used for displaying data,read/write=o/p
		E=1;//used for giving high to low pulse 
		ms_delay(10);
		E=0;
}

