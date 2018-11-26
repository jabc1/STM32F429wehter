/**
  * @file    mpu6050.c 
  * @author  WB R&D Team - openmcu666
  * @version V0.1
  * @date    2015.6.24
  * @brief   Gyroscope Driver
  */
#include "stm32f4xx.h"                  // Device header
#include "IIC_MPU6050.h"
#include "delay.h"
#include "usart.h"
/**
  * @brief  ��ʼ��SDA��SCL
  * @param  None
  * @retval None
  */
void IIC_Bus_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;  //SCCB_SIC:SCCB_SID
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			      
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOH, &GPIO_InitStructure); 
	IIC_SID_H();                                           //����SDA��SCL
  delay_us(50);
  IIC_SIC_H();	                                         
  delay_us(50);
}

/**
  * @brief  ����SDAΪ���
  * @param  None
  * @retval None
  */
void IIC_Data_Out()
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOH, &GPIO_InitStructure);

}

/**
  * @brief  ����SDAΪ����
  * @param  None
  * @retval None
  */
void IIC_Data_In()
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;               
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;			
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOH, &GPIO_InitStructure);

}

/**
  * @brief  ��ʼ�ź�
  * @param  None
  * @retval None
  */
void IIC_Start(void)
{
    IIC_SID_H();              //�����߸ߵ�ƽ
    delay_us(5);
    IIC_SIC_H();	            //��ʱ���߸ߵ�ʱ���������ɸ�����
    delay_us(5);
    IIC_SID_L();
    delay_us(5);
    IIC_SIC_L();	            //�����߻ָ��͵�ƽ��������������Ҫ
    delay_us(5);

}

/**
  * @brief  ֹͣ�ź�
  * @param  None
  * @retval None
  */
void IIC_Stop()
{
   IIC_SID_L();
   delay_us(5);
   IIC_SIC_H();	
   delay_us(5);  
   IIC_SID_H();	
   delay_us(5);  

}

/**
  * @brief  ��Ӧ��
  * @param  None
  * @retval None
  */
void IIC_Send_NoAck()
{
  IIC_SID_H();	
	delay_us(5);	
	IIC_SIC_H();	
	delay_us(5);	
	IIC_SIC_L();	
	delay_us(5);	
	IIC_SID_L();	
	delay_us(5);
}

/**
  * @brief  ����һ��Ӧ���ź�
  * @param  None
  * @retval None
  */
void IIC_Send_Ack()
{
 	IIC_SID_L();	
	delay_us(5);	
	IIC_SIC_L();	
	delay_us(5);	
	IIC_SIC_H();	
	delay_us(5);	
	IIC_SIC_L();	
	delay_us(5);	
	IIC_SID_L();	
	delay_us(5);

}

/**
  * @brief  дһ���ֽ�
  * @param  Data:д�������
  * @retval 1:���ͳɹ�;0:����ʧ��
  */
uint8_t IIC_Bus_Write_Byte(uint8_t Data)
{
	uint32_t i;
	uint8_t tem;

	for(i = 0; i < 8; i++) //ѭ��8�η�������
	{
		if((Data<<i) & 0x80)
		{
			IIC_SID_H();
		}
		else 
		{
			IIC_SID_L();
		}
		delay_us(5);
		IIC_SIC_H();	
		delay_us(10);
		IIC_SIC_L();	
		delay_us(5);
	}
	delay_us(10);
	IIC_Data_In();
	delay_us(10);
	IIC_SIC_H();	
	delay_us(10);
	if(IIC_SID_STATE)
	{
		tem = 0;//SDA=1����ʧ��
	}
	else 
	{
		tem = 1;//SDA=0���ͳɹ�������1
	}

	IIC_SIC_L();	
	delay_us(5);	
	IIC_Data_Out();
	return tem;  
}

/**
  * @brief  ��һ���ֽ�
  * @param  ack:0:����Ӧ��;1:����Ӧ��
  * @retval read:��ȡ������
  */
uint8_t IIC_Bus_Read_Byte(unsigned char ack)
{	
	uint32_t i;
	uint8_t read = 0;
	
	IIC_Data_In();
	delay_us(5);
	for(i = 8; i > 0; i--) //ѭ��8�ν�������
	{		     
		delay_us(5);
		IIC_SIC_H();
		delay_us(5);
		read = read << 1;
		if(IIC_SID_STATE)
		{
			read += 1; 
		}
		IIC_SIC_L();
		delay_us(5);
	}	
    IIC_Data_Out();
	if(!ack)
	{
		IIC_Send_NoAck();
	}
	else
	{
	  IIC_Send_Ack();
	}
	return read;
}

/**
  * @brief  ��MPU6050дһ���ֽ�����
  * @param  Reg:�Ĵ�����ַ
  * @param  Data:����
  * @retval 0:���ͳɹ�;1:����ʧ��
  */
u8 MPU_Write_Byte(u8 Reg,u8 Data) 				 
{ 
    IIC_Start(); 
	if(!IIC_Bus_Write_Byte((MPU_ADDR<<1)|0))                //����������ַ
	{
		IIC_Stop();		 
		return 1;		
	}
    IIC_Bus_Write_Byte(Reg);	                            //д�Ĵ�����ַ
  
	if(!IIC_Bus_Write_Byte(Data))                           //��������

	{
		IIC_Stop();	 
		return 1;		 
	}		 
    IIC_Stop();	 
	return 0;
}

/**
  * @brief  ��MPU6050��һ���ֽ�����
  * @param  Reg:�Ĵ�����ַ 
  * @retval Data:��ȡ������
  */
u8 MPU_Read_Byte(u8 reg)
{
	u8 Data;
  IIC_Start(); 
	IIC_Bus_Write_Byte((MPU_ADDR<<1)|0);         //����������ַ��д����	

  IIC_Bus_Write_Byte(reg);	                   //д�Ĵ�����ַ  
  IIC_Start();
	IIC_Bus_Write_Byte((MPU_ADDR<<1)|1);         //����������ַ�Ͷ�����	
	Data=IIC_Bus_Read_Byte(0);                   //��ȡ����,����Ӧ��
  IIC_Stop();			                            
	return Data;		
}

/**
  * @brief  ��MPU6050дָ�����ȵ�����
  * @param  Addr:������ַ 
  * @param  Reg:�Ĵ�����ַ
  * @param  Len:д�볤��
  * @param  Buf:������
  * @retval 0:д��ɹ�;1:д��ʧ��
  */
u8 MPU_Write_Len(u8 Addr,u8 Reg,u8 Len,u8 *Buf)
{
	u8 i; 
  IIC_Start(); 
	if(!IIC_Bus_Write_Byte((Addr<<1)|0))
	{
		IIC_Stop();		 
		return 1;		
	}
  IIC_Bus_Write_Byte(Reg);	

	for(i=0;i<Len;i++)
	{
		if(!IIC_Bus_Write_Byte(Buf[i]))	//��������

		{
			IIC_Stop();	 
			return 1;		 
		}		
	}    
  IIC_Stop();	 
	return 0;	
} 

/**
  * @brief  ��MPU6050��ָ�����ȵ�����
  * @param  Addr:������ַ 
  * @param  Reg:�Ĵ�����ַ
  * @param  Len:д�볤��
  * @param  Buf:��ȡ���ݻ�����
  * @retval 0:��ȡ�ɹ�;1:��ȡʧ��
  */
u8 MPU_Read_Len(u8 Addr,u8 Reg,u8 Len,u8 *Buf)
{ 
 	IIC_Start(); 
	if(!IIC_Bus_Write_Byte((Addr<<1)|0))
	{
		IIC_Stop();		 
		return 1;		
	}
  IIC_Bus_Write_Byte(Reg);	
  IIC_Start();
  IIC_Bus_Write_Byte((Addr<<1)|1);
  
	while(Len)
	{
		if(Len==1)*Buf=IIC_Bus_Read_Byte(0);          //������,����nACK 
		else *Buf=IIC_Bus_Read_Byte(1);		            //������,����ACK  
		Len--;
		Buf++; 
	}    
  IIC_Stop();	
	return 0;	
}

/**
  * @brief  ����MPU6050���ٶȴ����������̷�Χ
  * @param  Fsr:0,��2g;1,��4g;2,��8g;3,��16g
  * @retval 0:�ɹ�;1:ʧ��
  */
u8 MPU_Set_Accel_Fsr(u8 Fsr)
{
	return MPU_Write_Byte(MPU_ACCEL_CFG_REG,Fsr<<3);//���ü��ٶȴ����������̷�Χ  
}

/**
  * @brief  ����MPU6050�����Ǵ����������̷�Χ
  * @param  Fsr:0,��250dps;1,��500dps;2,��1000dps;3,��2000dps
  * @retval 0:�ɹ�;1:ʧ��
  */
u8 MPU_Set_Gyro_Fsr(u8 Fsr)
{
	return MPU_Write_Byte(MPU_GYRO_CFG_REG,Fsr<<3);
}

/**
  * @brief  ����MPU6050�����ֵ�ͨ�˲���
  * @param  Lpf:���ֵ�ͨ�˲�Ƶ��(Hz)
  * @retval 0:�ɹ�;1:ʧ��
  */
u8 MPU_Set_LPF(u16 Lpf)
{
	u8 Data=0;
	if(Lpf>=188)Data=1;
	else if(Lpf>=98)Data=2;
	else if(Lpf>=42)Data=3;
	else if(Lpf>=20)Data=4;
	else if(Lpf>=10)Data=5;
	else Data=6; 
	return MPU_Write_Byte(MPU_CFG_REG,Data);//�������ֵ�ͨ�˲���  
}

/**
  * @brief  ����MPU6050������
  * @param  Rate:4~1000(Hz)
  * @retval 0:�ɹ�;1:ʧ��
  */
u8 MPU_Set_Rate(u16 Rate)
{
	u8 data;
	if(Rate>1000)Rate=1000;
	if(Rate<4)Rate=4;
	data=1000/Rate-1;
	data=MPU_Write_Byte(MPU_SAMPLE_RATE_REG,data);	 
 	return MPU_Set_LPF(Rate/2);	                         //�Զ�����LPFΪ�����ʵ�һ��
}

/**
  * @brief  ��ʼ��6050
  * @param  None
  * @retval 0:�ɹ�;1:ʧ��
  */
u8 MPU6050_Init(void)
{
	u8 Res=0;
  IIC_Bus_Init();
  MPU_Write_Byte(MPU_PWR_MGMT1_REG,0x80);	          //��λMPU6050
	delay_ms(80);
  MPU_Write_Byte(MPU_PWR_MGMT1_REG,0x00);	          //����MPU6050 
	MPU_Set_Gyro_Fsr(3);					                   
	MPU_Set_Accel_Fsr(0);					                    
	MPU_Set_Rate(50);						                      //������50Hz
  MPU_Write_Byte(MPU_INT_EN_REG,0x00);	            //�ر������ж�
	MPU_Write_Byte(MPU_USER_CTRL_REG,0x00);        
	MPU_Write_Byte(MPU_FIFO_EN_REG,0x00);	           
	MPU_Write_Byte(MPU_INTBP_CFG_REG,0x80);	          
	Res=MPU_Read_Byte(MPU_DEVICE_ID_REG);
	if(Res==MPU_ADDR)                                 //����ID��ȷ
	{
		MPU_Write_Byte(MPU_PWR_MGMT1_REG,0x01);	         //����CLKSEL,PLL X��Ϊ�ο�
		MPU_Write_Byte(MPU_PWR_MGMT2_REG,0x00);	         //���ٶ��������Ƕ�����
		MPU_Set_Rate(50);						                     //���ò�����Ϊ50Hz
 	}else return 1;
	return 0;
}

/**
  * @brief  �õ��¶�ֵ
  * @param  None
  * @retval �¶�ֵ
  */
short MPU_Get_Temperature(void)
{
  u8 Buf[2]; 
  short Raw;
	float Temp;
	MPU_Read_Len(MPU_ADDR,MPU_TEMP_OUTH_REG,2,Buf); 
  Raw=((u16)Buf[0]<<8)|Buf[1];  
  Temp=36.53+((double)Raw)/340;  
  return Temp*100;;                                     //����100��
}

/**
  * @brief  �õ�ԭʼ���ٶ�ֵ
  * @param  gx,gy,gz:������x,y,z���ԭʼ����
  * @retval 0:�ɹ�;1:ʧ��
  */
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az)
{
  u8 Res,Buf[6];  
	Res=MPU_Read_Len(MPU_ADDR,MPU_ACCEL_XOUTH_REG,6,Buf);
	if(Res==0)
	{
		*ax=((u16)Buf[0]<<8)|Buf[1];  
		*ay=((u16)Buf[2]<<8)|Buf[3];  
		*az=((u16)Buf[4]<<8)|Buf[5];
	} 	
    return Res;;
}

/**
  * @brief  ��ȡ������ԭʼ����
  * @param  gx,gy,gz:������x,y,z���ԭʼ����
  * @retval 0:�ɹ�;1:ʧ��
  */
u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz)
{
    u8 Res,Buf[6];  
	Res=MPU_Read_Len(MPU_ADDR,MPU_GYRO_XOUTH_REG,6,Buf);
	if(Res==0)
	{
		*gx=((u16)Buf[0]<<8)|Buf[1];  
		*gy=((u16)Buf[2]<<8)|Buf[3];  
		*gz=((u16)Buf[4]<<8)|Buf[5];
	} 	
    return Res;
}

/**
  * @brief  �������ݸ�����������λ�����
  * @param  Fun:������. 0xA0~0xAF
  * @param  Data:���ݻ�����
  * @param  Len:��Ч���ݸ���
  * @retval None
  */
void USART1_Report(u8 Fun,u8*Data,u8 Len)
{
//	u8 Send_Buf[32];
//	u8 i;
//	Send_Buf[Len+3]=0;	                        //У��������
//	Send_Buf[0]=0x88;	                          //֡ͷ
//	Send_Buf[1]=Fun;	                           //������
//	Send_Buf[2]=Len;	                            //���ݳ���
//	for(i=0;i<Len;i++)Send_Buf[3+i]=Data[i];			//��������
//	for(i=0;i<Len+3;i++)Send_Buf[Len+3]+=Send_Buf[i];	//����У���	
//	for(i=0;i<Len+4;i++) USART1_SendChar(Send_Buf[i]);	//�������ݵ�����1 
	
	u8 Send_Buf[32];
	u8 i;
	Send_Buf[Len+4]=0;	                        //У��������
	Send_Buf[0]=0xAA;	                          //֡ͷ
	Send_Buf[1]=0xAA;	                          //֡ͷ
	Send_Buf[2]=Fun;	                           //������
	Send_Buf[3]=Len;	                            //���ݳ���
	for(i=0;i<Len;i++)Send_Buf[4+i]=Data[i];			//��������
	for(i=0;i<Len+4;i++)Send_Buf[Len+4]+=Send_Buf[i];	//����У���	
	for(i=0;i<Len+5;i++) USART1_SendChar(Send_Buf[i]);	//�������ݵ�����1 
	
}

/**
  * @brief  ���ͼ��ٶȴ������������ǵ�����
  * @param  aacx,aacy,aacz:x,y,z������������ļ��ٶ�ֵ
  * @param  gyrox,gyroy,gyroz:x,y,z�������������������ֵ
  * @retval None
  */
void MPU6050_SendData(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz)
{
	u8 tbuf[12]; 
	tbuf[0]=(aacx>>8)&0xFF;
	tbuf[1]=aacx&0xFF;
	tbuf[2]=(aacy>>8)&0xFF;
	tbuf[3]=aacy&0xFF;
	tbuf[4]=(aacz>>8)&0xFF;
	tbuf[5]=aacz&0xFF; 
	tbuf[6]=(gyrox>>8)&0xFF;
	tbuf[7]=gyrox&0xFF;
	tbuf[8]=(gyroy>>8)&0xFF;
	tbuf[9]=gyroy&0xFF;
	tbuf[10]=(gyroz>>8)&0xFF;
	tbuf[11]=gyroz&0xFF;
//	USART1_Report(0xA1,tbuf,12);                          //�Զ���֡,0xA1
	USART1_Report(0xF2,tbuf,12);                          //�Զ���֡,0xF1
}	

/**
  * @brief  ���ͽ�������̬���ݸ�����
  * @param  aacx,aacy,aacz:x,y,z������������ļ��ٶ�ֵ
  * @param  gyrox,gyroy,gyroz:x,y,z�������������������ֵ
  * @param  roll:�����.
  * @param  pitch:������.
  * @param  yaw:�����.
  * @retval None
  */
void Report_imu(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz,short roll,short pitch,short yaw)
{
	u8 tbuf[28]; 
	u8 i;
	for(i=0;i<28;i++)tbuf[i]=0;
	tbuf[0]=(aacx>>8)&0xFF;
	tbuf[1]=aacx&0xFF;
	tbuf[2]=(aacy>>8)&0xFF;
	tbuf[3]=aacy&0xFF;
	tbuf[4]=(aacz>>8)&0xFF;
	tbuf[5]=aacz&0xFF; 
	tbuf[6]=(gyrox>>8)&0xFF;
	tbuf[7]=gyrox&0xFF;
	tbuf[8]=(gyroy>>8)&0xFF;
	tbuf[9]=gyroy&0xFF;
	tbuf[10]=(gyroz>>8)&0xFF;
	tbuf[11]=gyroz&0xFF;	
	tbuf[18]=(roll>>8)&0xFF;
	tbuf[19]=roll&0xFF;
	tbuf[20]=(pitch>>8)&0xFF;
	tbuf[21]=pitch&0xFF;
	tbuf[22]=(yaw>>8)&0xFF;
	tbuf[23]=yaw&0xFF;
	USART1_Report(0xFF,tbuf,28);//�ɿ���ʾ֡,0xAF
} 
