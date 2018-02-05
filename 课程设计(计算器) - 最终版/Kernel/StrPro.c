/*========================*/
/*  �����ַ���������    */
/*========================*/
#include "StrPro.h"

/*========================================================================*/
/*��������:uchar LongToString(uchar *str,float dat)
/*��������:������תΪ�ַ���
/*�������:�ַ���*str ��������dat
/*�������:�ַ�������len
/*========================================================================*/
uchar LongToString(uchar *str,float dat)
{
	uchar len;
	
	sprintf(str,"%10ld",(long int)dat);
	len = sprintf(str,"%10ld",(long int)dat);
	
	return len;     	                           //����len
}

/*========================================================================*/
/*��������:uchar FloatToString(uchar *str,float dat)
/*��������:������תΪ�ַ���
/*�������:�ַ���*str ��������dat
/*�������:�ַ�������len
/*========================================================================*/
uchar FloatToString(uchar *str,float dat)
{
	uchar len;
	
	sprintf(str,"%5.5f",dat);
	
	len = sprintf(str,"%5.5f",dat);
	
	while(len-- > 0)                              //ȥ��ĩβ����� 0
	{
		if(str[len] != '0')
		{
			break;
		}
	}
	
	len = len + 1;
	return len;
}

/*========================================================================*/
/*��������:float StringToFloat(uchar *buf)
/*��������:�ַ�תΪ������
/*�������:�ַ����� buf
/*�������:������ num
/*========================================================================*/
float StringToFloat(uchar *buf)
{	
	float num;
	
	num = atof(buf);
	
	return num;
}