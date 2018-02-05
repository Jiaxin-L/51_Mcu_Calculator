#include "Calculate.h"


uchar oprt = 0;                         //���������
uchar step = 0;                         //�����������

uchar result_buf[12];                   //�����������Ļ�����
uchar result_len;                       //����������

float num1 = 0;                         //������1
float num2 = 0;                         //������2
float result = 0;                       //������

uchar num1_buf[10];                     //�����һ���������Ļ�����
uchar num2_buf[10];                     //����ڶ����������Ļ�����
uchar num1_index = 0;                   //������һ ��������
uchar num2_index = 0;                   //�������� ��������

bit dec_flag = 0;                       //С�����־

/*========================================================================*/
/*��������:void NumAction(uchar n)
/*��������:��������
/*�������:n
/*�������:��
/*========================================================================*/
void NumAction(uchar n)
{
	if(step>1)Reset();                      //���������λ
	
	if(step == 0)                           //�����һ��������
	{
		if(num1_index < 10)                 //���������Ȳ����� 10 λ
		{
			num1_buf[num1_index] = n + '0';
			num1_index ++;
			LcdShowNum(1,1);                //��LCD1602�ڶ�����ʾ������һ
		}
		else
			return;
	}
	else if(step == 1)                      //����ڶ���������
	{
		if(num2_index < 10)
		{
			num2_buf[num2_index] = n + '0';
			num2_index ++;
			LcdShowNum(1,2);                //��LCD1602�ڶ�����ʾ��������
		}
		else
			return;
	}
}

/*========================================================================*/
/*��������:void DecimalAction()
/*��������:С��������
/*�������:��
/*�������:��
/*========================================================================*/
void DecimalAction()
{	
	if(step == 0)                             //�ڵ�һ���������м���С����
	{
		if((num1_index < 10)&&(dec_flag == 0))
		{
			dec_flag = 1;                     //ÿ��������ֻ��һ��С����
			num1_buf[num1_index] = '.';
			num1_index ++;
			LcdShowNum(1,1);
		}
		else
			return;
	}
	
	else if(step == 1)                        //�ڵڶ����������м���С����
	{
		if((num2_index < 10)&&(dec_flag == 0))
		{
			dec_flag = 1;
			num2_buf[num2_index] = '.';
			num2_index ++;
			LcdShowNum(1,2);
		}
		else
			return;
	}
}

/*========================================================================*/
/*��������:void OprAction(uchar type)
/*��������:���������
/*�������:type
/*�������:��
/*========================================================================*/
void OprAction(uchar type)
{
	if(step==0)                              //�ڶ���������δ����ʱ��Ӧ
	{
		num1 = StringToFloat(num1_buf);      //�����������������ַ�ת��Ϊ������
		dec_flag = 0;                        //��־����
		LcdAreaClear(0,0,16-num1_index);     //�����һ����ߵ��ַ�
		LcdShowNum(0,1);                     //�ַ���ʾ�ڵ�һ���ұ�
		LcdShowOpr(0,1,type);                //�������ʾ�ڵڶ������
		LcdAreaClear(1,1,14);                //����ڶ����м���ַ�
		LcdShowStr(15,1,"0");
		oprt = type;                         //��¼��ǰ�����
		num1_index = 0;
		step = 1;
	}
	
	if(step == 2)                               //��������״̬
	{
		dec_flag = 0;
		num1 = result;                          //������һ Ϊ��һ��������
		LcdAreaClear(0,0,16);
		LcdShowStr(16-result_len,0,result_buf);	//��һ����������ʾ�ڵ�һ��
		LcdAreaClear(0,1,16);
		LcdShowOpr(0,1,type);                   //�������ʾ�ڵڶ������
		oprt = type;
		step = 1;
	}
}

/*========================================================================*/
/*��������:void GetResult()
/*��������:������
/*�������:��
/*�������:��
/*========================================================================*/
void GetResult()
{
	num2 = StringToFloat(num2_buf);
	
	if(step==1)                                        //�ڶ������������ż���
	{
		step=2;
		dec_flag = 0;                                  //С�����־����
		switch(oprt)
		{
			case 0:result=(float)(num1+num2);break;
			case 1:result=(float)(num1-num2);break;
			case 2:result=(float)(num1*num2);break;
			case 3:result=(float)(num1/num2);break;
			case 4:result=(float)pow(num1,num2);break;
			default:break;
		}
		LcdShowOpr(0,0,oprt);                               //��һ����ʾ�����
		LcdAreaClear(1,0,16-num2_index);                    //���������������ʾ     
		LcdShowNum(0,2);                                    //����������ʾ����һ��
		LcdShowStr(0,1,"=");                                //�ڶ�����ʾ ���ں� =
		num2_index = 0;
		
		if((result < 99999999)&&(result > -99999999))       //�������ڷ�Χ��
		{
			if(result == (signed long)result)                 //������������
			{
				result_len = LongToString(result_buf,result); //תΪ�ַ���
				Save_Result();					              //������
				LcdAreaClear(1,1,16);
				LcdShowStr(16-result_len,1,result_buf);		  //��ʾ���
			}
			else                                              //��������Ϊ����
			{ 
				if((result >=0)&&(result < 0.0001))result = 0;
				if((result <=1)&&(result > 0.9999))result = 1;
				result_len = FloatToString(result_buf,result);
				Save_Result();
				LcdAreaClear(1,1,16);
				LcdShowStr(16-result_len,1,result_buf);			
			}
		}
		else                                                  //������������Χ�򾯸�
			Warning();
	}
	memset(num1_buf,0,sizeof(num1_buf));                      //ÿ�μ�����ɺ󽫻���������
	memset(num2_buf,0,sizeof(num2_buf));
}

/*========================================================================*/
/*��������:void Save_Result()
/*��������:����������
/*�������:��
/*�������:��
/*========================================================================*/
void Save_Result()
{
	E2P_Write(0x00,0x40,20);                     //���������һ�����
	E2P_Write(result_buf,0x40,result_len);       //����������������24c02
}

/*========================================================================*/
/*��������:void Read_Result()
/*��������:��ȡ������
/*�������:��
/*�������:��
/*========================================================================*/
void Read_Result()
{
	uchar j;
	uchar tmp[12];
	
	LcdClearAll();
	E2P_Read(tmp,0x40,sizeof(result_buf));      //��24c02��ȡ������
	
	for(j = 0;j < result_len;j ++)
	{
			LcdShowDat(j,0,tmp[j]);             //��ʾ��ȡ�Ľ��
	}
}

/*========================================================================*/
/*��������:void LcdShowOpr(uchar x,uchar y,uchar type)
/*��������:lcd��ʾ������
/*�������:����(x,y) ����������type
/*�������:��
/*========================================================================*/
void LcdShowOpr(uchar x,uchar y,uchar type)
{
	switch(type)
	{
		case 0:LcdShowStr(x,y,"+");break;         // �Ӻ�
		case 1:LcdShowStr(x,y,"-");break;         // ����
		case 2:LcdShowDat(x,y,0x78);break;        // �˺�
		case 3:LcdShowDat(x,y,0xFD);break;        // ����
		case 4:LcdShowStr(x,y,"^");break;         // �˷�
		default:break;
	}
}

/*========================================================================*/
/*��������:void LcdShowNum(uchar y,uchar type)
/*��������:lcd1602��ʾ������
/*�������:����y ,����������type
/*�������:��
/*========================================================================*/
void LcdShowNum(uchar y,uchar type)
{
	if(y == 0)                                       //��LCD1602��һ����ʾ
	{
		if(type == 1)
			LcdShowStr(16-num1_index,0,num1_buf);    //��ʾ������һ
		else if(type == 2)
			LcdShowStr(16-num2_index,0,num2_buf);    //��ʾ��������
	}
	
	else if(y == 1)                                  //��LCD1602�ڶ�����ʾ
	{
		if(type == 1)
			LcdShowStr(16-num1_index,1,num1_buf);
		else if(type == 2)
			LcdShowStr(16-num2_index,1,num2_buf);
	}
}

/*========================================================================*/
/*��������:void Reset()
/*��������:��������λ
/*�������:��
/*�������:��
/*========================================================================*/
void Reset()
{
	num1 = 0;                                //�������� ��־λ ���� ������ ����
	num2 = 0;
	dec_flag = 0;
	memset(num1_buf,0,sizeof(num1_buf));
	memset(num2_buf,0,sizeof(num2_buf));
	num1_index = 0;
	num2_index = 0;
	step = 0;
	LcdClearAll();
	LcdShowStr(15,1,"0");
}

/*========================================================================*/
/*��������:void Warning()
/*��������:�������
/*�������:��
/*�������:��
/*========================================================================*/
void Warning()
{
	uint i = 10000;
	
	Reset();
	
	if(Buzz_flag == 1)
	{
		while(i--)
		{
			Buzz = ~Buzz;
		}		
	}
	
	LcdShowStr(0,0,"    ERROR!");
	Delay100ms();
	Reset();
	LcdShowStr(15,1,"0");
}