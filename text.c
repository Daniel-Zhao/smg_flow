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
		switch(i)	 //位选，选择点亮的数码管，
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//显示第0位
			case(1):
				LSA=1;LSB=0;LSC=0; break;//显示第1位
			case(2):
				LSA=0;LSB=1;LSC=0; break;//显示第2位
			case(3):
				LSA=1;LSB=1;LSC=0; break;//显示第3位
			case(4):
				LSA=0;LSB=0;LSC=1; break;//显示第4位
			case(5):
				LSA=1;LSB=0;LSC=1; break;//显示第5位
			case(6):
				LSA=0;LSB=1;LSC=1; break;//显示第6位
			case(7):
				LSA=1;LSB=1;LSC=1; break;//显示第7位	
		}
		//P0=smgduan[i];//发送段码
		temp[i] = smgduan[i];
		P0 = temp[i];
		temp[i+1] = temp[i] << 1;
		delay(10000); //间隔一段时间扫描	
		P0=0x00;//消隐
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
				//delay(100000);、
				P0=smgduan[k+i-2];//发送段码
				switch(i)//位选，选择点亮的数码管，
				{
					case(0):
						LSA=0;LSB=0;LSC=0; break;//显示第0位
					case(1):
						LSA=1;LSB=0;LSC=0; break;//显示第1位
					case(2):
						LSA=0;LSB=1;LSC=0; break;//显示第2位
					case(3):
						LSA=1;LSB=1;LSC=0; break;//显示第3位
					case(4):
						LSA=0;LSB=0;LSC=1; break;//显示第4位
					case(5):
						LSA=1;LSB=0;LSC=1; break;//显示第5位
					case(6):
						LSA=0;LSB=1;LSC=1; break;//显示第6位
					case(7):
						LSA=1;LSB=1;LSC=1; break;//显示第7位	
				}
				
				delay(100); //间隔一段时间扫描	
				P0=0x00;//消隐
			}
		}
	}
}

void main()
{	
	TMOD=0X01;//选择工作方式1
	TH0=0xd8;
	TL0=0xf0;
	ET0=1;//打开定时器0中断允许
	EA=1;//打开总中断
	TR0=1;//打开定时器		
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
