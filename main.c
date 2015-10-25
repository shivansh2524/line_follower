#include<avr/io.h>
#include<util/delay.h>
#define forward PORTD=0x50
#define backward PORTD=0xA0
#define slright PORTD=0x10
#define slleft PORTD=0x40
#define shright PORTD=0x90
#define shleft PORTD=0x60
#define forwardb PORTB=0x05
#define backwardb PORTB=0x0A
#define slrightb PORTB=0x01
#define slleftb PORTB=0x04
#define shrightb PORTB=0x09
#define shleftb PORTB=0x06
void check(unsigned char m);
void crave(unsigned char m);
void main()
{
	unsigned int adc[5];
	unsigned char m,k;
	DDRD=0xF0;
	PORTD=0x00;
	DDRB=0x0F;
	PORTB=0x00;
	ADCSRA|=(1<<ADEN)|(1<<ADFR)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS0);
	ADCSRA|=(1<<ADSC);
	while(1)
	{	m=0;
		for(k=0;k<6;k++)
		{
			ADMUX=k;
			_delay_ms(1);
			adc[k]=ADCW;
			if(adc[k]<307)
			{
				m|=1<<k;
			}
			else
			{
				m&=~(1<<k);
			}
		}//End of for loop
		check(m);
	}
}
void check(unsigned char m)
{
	PORTD=0x00;
	if((m & 0x1F)==0x0E)
	{
		forward;
		forwardb;
	}
	else if((m & 0x1F)==0x0F)
	{
		shright;shrightb;
	}
	else if((m & 0x1F)==0x1E)
	{
		shleft;shleftb;
	}
	else if((m & 0x1F)==0x07)
	{
		slright;slrightb;
	}
	else if((m & 0x1F)==0x1C)
	{
		slleft;slleftb;
	}
	else if((m & 0x1F)==0x01)
	{
		shright;shrightb;
	}
	else if((m & 0x1F)==0x10)
	{
		shleft;shleftb;
	}
	else if((m & 0x1F)==0x1F)
	{
		forward;forwardb;
	}
	else
	{
		crave(m);
	}
	return;
}
void crave(unsigned char m)
{
	unsigned int l,x,j,i,flag=0;
	unsigned char z;
	forward;forwardb;
	for(j=0;j<10;j++)
	{	flag=0;
		_delay_ms(1);
		z=0;
		for(i=0;i<6;i++)
		{
			ADMUX=i;
			_delay_ms(1);
			adc[i]=ADgCW;
			if(adc[i]<307)
			{
				z|=1<<i;
			}
			else
			{
				z&=~(1<<i);
			}
		}
		if(!(z==m))
		{
			flag=1;
			break;
		}
	}
	if(flag==1)
	{
		return;
	}
	shleft;shleftb;
	for(j=0;j<20;j++)
	{	flag=0;
		_delay_ms(1);
		z=0;
		for(i=0;i<6;i++)
		{
			ADMUX=i;
			_delay_ms(1);
			adc[i]=ADCW;
			if(adc[i]<307)
			{
				z|=1<<i;
			}
			else
			{
				z&=~(1<<i);
			}
		}
		if(!(z==m))
		{
			flag=1;
			break;
		}
	}
	if(flag==1)
	{
		return;
	}
	shright;shrightb;
	for(j=0;j<10;j++)
	{	flag=0;
		_delay_ms(1);
		z=0;
		for(i=0;i<6;i++)
		{
			ADMUX=i;
			_delay_ms(1);
			adc[i]=ADCW;
			if(adc[i]<307)
			{
				z|=1<<i;
			}
			else
			{
				z&=~(1<<i);
			}
		}
		if(!(m==z))
		{
			flag=1;
			break;
		}
	}
	return;
}
	
	
	
	