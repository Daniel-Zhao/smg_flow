#include <reg52.h>
typedef unsigned int u16;	 
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

u8 count;
u8 k = 0;
u8 code temp;
//u8 code smgduan[]={0x3f,0x06,0x5b,0x4f,
//									 0x66,0x6d,0x7d,0x07};
									 //0x7f,0x6f,0x77,0x7c,
									 //0x39,0x5e,0x79,0x71};		
u8 code smgduan[] = {0x06,0x4f,0x06,0x3f,0x06,0x5b,0x7f,0x06,0x3f,0x5b};
//u8 code smgduan[] = {0x5b,0x3f,0x06,0x7f,0x5b,0x06,0x3f,0x06,0x4f,0x06};//2018210131
void delay(u16 i)
{
	while(i--);	
}

/*void DigDisplay()
{
	u8 i;
	for(i=0;i<8;i++)
	{
		switch(i)	 //λѡ��ѡ�����������ܣ�
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//��ʾ��0λ
			case(1):
				LSA=1;LSB=0;LSC=0; break;//��ʾ��1λ
			case(2):
				LSA=0;LSB=1;LSC=0; break;//��ʾ��2λ
			case(3):
				LSA=1;LSB=1;LSC=0; break;//��ʾ��3λ
			case(4):
				LSA=0;LSB=0;LSC=1; break;//��ʾ��4λ
			case(5):
				LSA=1;LSB=0;LSC=1; break;//��ʾ��5λ
			case(6):
				LSA=0;LSB=1;LSC=1; break;//��ʾ��6λ
			case(7):
				LSA=1;LSB=1;LSC=1; break;//��ʾ��7λ	
		}
		//P0=smgduan[i];//���Ͷ���
		temp[i] = smgduan[i];
		P0 = temp[i];
		temp[i+1] = temp[i] << 1;
		delay(10000); //���һ��ʱ��ɨ��	
		P0=0x00;//����
	}
}*/

void DigDisplay()
{
	u8 i = 0,j = 0, k;
	for(k = 11; k > 0; k--)
	{
		//delay(100);
		for(j = 0; j < 50; j++)
		{
			for(i = 0; i < 11; i++)
			{
				//delay(100000);��
				P0=smgduan[k+i-2];//���Ͷ���
				switch(i)//λѡ��ѡ�����������ܣ�
				{
					case(0):
						LSA=0;LSB=0;LSC=0; break;//��ʾ��0λ
					case(1):
						LSA=1;LSB=0;LSC=0; break;//��ʾ��1λ
					case(2):
						LSA=0;LSB=1;LSC=0; break;//��ʾ��2λ
					case(3):
						LSA=1;LSB=1;LSC=0; break;//��ʾ��3λ
					case(4):
						LSA=0;LSB=0;LSC=1; break;//��ʾ��4λ
					case(5):
						LSA=1;LSB=0;LSC=1; break;//��ʾ��5λ
					case(6):
						LSA=0;LSB=1;LSC=1; break;//��ʾ��6λ
					case(7):
						LSA=1;LSB=1;LSC=1; break;//��ʾ��7λ	
				}
				
				delay(100); //���һ��ʱ��ɨ��	
				P0=0x00;//����
			}
		}
	}
}

void main()
{	
	TMOD=0X01;//ѡ������ʽ1
	TH0=0xd8;
	TL0=0xf0;
	ET0=1;//�򿪶�ʱ��0�ж�����
	EA=1;//�����ж�
	TR0=1;//�򿪶�ʱ��		
	while(1)
	{
		DigDisplay();
	}
}
void timer0() interrupt 1 
{
	TH0 = 0xd8;
	TL0 = 0xf0;
	count++;
	DigDisplay();
	if(count == 200)
	{
		count = 0;
		k = k + 1;
		if(k > 5)
		{
			k = 0;
		}
	}
}
