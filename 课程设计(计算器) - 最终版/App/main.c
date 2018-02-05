/*=================================================*/
/*��Ŀ����: 51��Ƭ��������
/*��������: F H X
/*�޸�ʱ��: 2017/12/20
/*��ϵ��ʽ: 374454765@qq.com
/*=================================================*/
#include "Config.h"

uchar T0RH = 0;                                  //��ʱ��0����ֵ
uchar T0RL = 0;

extern bit Buzz_flag;                            //���������ر�־
/*========================================================================*/
/*��������:void main()
/*��������:������
/*�������:��
/*�������:��
/*========================================================================*/
void main()
{
	EA=1;                                          //�������ж�
	Timer0Init(2);                                 //��ʱ��0��ʼ�� ��ʱ2ms
	InitLcd1602();                                 //LCD1602��ʼ��
	
	while(1)
	{	
		KeyDrive();                                  //�����������
		KeyDrive2();                                 //������������
	}
}
/*========================================================================*/
/*��������:void KeyDown(uchar keycode)
/*��������:ִ�а�������
/*�������:keycode
/*�������:��
/*========================================================================*/
void KeyDown(uchar keycode)
{
	if((keycode <= 0x39)&&(keycode >= 0x30))           //���ּ�0~9
	{
		BuzzerControl();
		NumAction(keycode - 0x30);
	}
	else if(keycode == 0x26)                           //"+"��
	{
		BuzzerControl();
		OprAction(0);
	}
	else if(keycode == 0x25)                           //"-"��
	{
		BuzzerControl();
		OprAction(1);
	}
	else if(keycode == 0x28)                           //"��"��
	{
		BuzzerControl();
		OprAction(2);
	}
	else if(keycode == 0x27)                           //"��"��
	{
		BuzzerControl();
		OprAction(3);
	}
	else if(keycode == 0x0D)                           //"="��
	{
		BuzzerControl();
		GetResult();
	}
	else if(keycode == 0x1B)                           //С���� '.'
	{
		BuzzerControl();
		DecimalAction();
	}
	else if(keycode == 0x01)                           //��λ��
	{
		BuzzerControl();
		Reset();
	}
	else if(keycode == 0x02)                           //�˷�����                   
	{
		BuzzerControl();
		OprAction(4);	
	}
	else if(keycode == 0x03)                           //��24c02��ȡ������
	{
		BuzzerControl();
		Read_Result();                               
	}
	else if(keycode == 0x04)                           //���ط���������
	{
		Buzz_flag = ~Buzz_flag;
	}
}
/*========================================================================*/
/*��������:void Timer0Init(uint ms)
/*��������:��ʱ��0��ʼ��
/*�������:ms
/*�������:��
/*========================================================================*/
void Timer0Init(uint ms)
{
	ulong tmp;                                //16λ�����ͱ���tmp
	tmp = MAIN_OSC/12;                        //�þ���Ƶ�ʳ���12�õ���ʱ������Ƶ��
	tmp = (tmp*ms)/1000;                      //�������Ҫ���ٸ���������
	tmp = 65536 - tmp;                        //��ʱ���ĳ�ʼֵ
	tmp = tmp + 18;                           //�����ж���ʱ��Ӧ��ɵ����
	T0RH = (uchar)(tmp>>8);                   //��tmp��8λ����8λ ��ֵ��T0RH
	T0RL = (uchar)tmp;                        //��tmp��8λ��ֵ��T0RL
	TMOD &= 0xF0;                             //TMOD��4λ���� ����λ����
	TMOD |= 0x01;                             //TMOD����λ���0001
	TH0 = T0RH;                               //װ�س�ֵ
	TL0 = T0RL;
	ET0 = 1;                                  //������ʱ��0�ж�          
	TR0 = 1;                                  //������ʱ��0
}
/*========================================================================*/
/*��������:void InterruptTimer0() interrupt 1
/*��������:��ʱ��0�жϷ���
/*�������:��
/*�������:��
/*========================================================================*/
void InterruptTimer0() interrupt 1
{
	TH0 = T0RH;                               //���س�ֵ
	TL0 = T0RL;
	KeyScan();                               //���󰴼�ɨ��
	KeyScan2();                              //��������ɨ��
}