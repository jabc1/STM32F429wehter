/**
  * @file    W25Q16.c 
  * @author  WB R&D Team - openmcu666
  * @version V0.1
  * @date    2015.6.11
  * @brief   SPI Driver
  */
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_spi.h"
#include "W25Q16.h"

volatile uint32_t SPIFlashID;

/**
  * @brief  ��ʼ��SPI5����Ӧ�ܽ�
  * @param  None
  * @retval None
  */
void W25Qxx_GpioInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
	
  RCC_AHB1PeriphClockCmd(W25QXX_MISO_CLK | W25QXX_MOSI_CLK | W25QXX_SCK_CLK
                         | W25QXX_CS_CLK, ENABLE);
	
  RCC_APB2PeriphClockCmd(W25QXX_RCC_CLK, ENABLE);
						 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_PinAFConfig(W25QXX_MISO_GPIO, W25QXX_MISO_PINS, W25QXX_GPIO_AF);
  GPIO_InitStructure.GPIO_Pin = W25QXX_MISO_PIN;
  GPIO_Init(W25QXX_MISO_GPIO, &GPIO_InitStructure);

  GPIO_PinAFConfig(W25QXX_MOSI_GPIO, W25QXX_MOSI_PINS, W25QXX_GPIO_AF);
  GPIO_InitStructure.GPIO_Pin = W25QXX_MOSI_PIN;
  GPIO_Init(W25QXX_MOSI_GPIO, &GPIO_InitStructure);

  GPIO_PinAFConfig(W25QXX_SCK_GPIO, W25QXX_SCK_PINS, W25QXX_GPIO_AF);
  GPIO_InitStructure.GPIO_Pin = W25QXX_SCK_PIN;
  GPIO_Init(W25QXX_SCK_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin = W25QXX_CS_PIN;
  GPIO_Init(W25QXX_CS_GPIO, &GPIO_InitStructure);  
	
  
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(W25QXX_SPI, &SPI_InitStructure); 
  SPI_Cmd(W25QXX_SPI, ENABLE);	
}

/**
  * @brief  ��(��)W25Qxx��(д)һ��Byte
  * @param  Ҫд���data
  * @retval �����յ���data
  */
uint8_t W25Qxx_ReadWrite(uint8_t Byte)
{
 // uint8_t redata;	

	while (SPI_I2S_GetFlagStatus(W25QXX_SPI, SPI_I2S_FLAG_TXE) == RESET);
	
	SPI_I2S_SendData(W25QXX_SPI, Byte);
	
	while (SPI_I2S_GetFlagStatus(W25QXX_SPI, SPI_I2S_FLAG_RXNE) == RESET);
	
	return SPI_I2S_ReceiveData(W25QXX_SPI);                                //���ش�SPI���߶�ȡ���ֽ�
}
/**
  * @brief  ��ȡW25Qxx����ID
  * @param  None
  * @retval ID:W25Q16����ID
  */
uint32_t W25Qxx_ReadId(void)
{
  uint32_t ID = 0;
  uint8_t i;
  
  EN_SELECT();
  W25Qxx_ReadWrite(W25QXX_CMD_JEDEC_ID);
  for (i = 0; i < 3; i++)
  {
    ID <<= 8;
	ID |= W25Qxx_ReadWrite(0xFF);
  }  
  DS_SELECT();
  return ID;
}

/**
  * @brief  ��ʼ��W25Qxx
  * @param  None
  * @retval None
  */
void W25Qxx_Init(void)
{
  W25Qxx_GpioInit();
  
  SPIFlashID = W25Qxx_ReadId();
	//printf("\r\nSPI-Flash %d ID: \n\r", sizeof(buf));
}

/**
  * @brief  ��״̬�Ĵ���
  * @param  None
  * @retval ReadData:����״̬�Ĵ�����ֵ
  */
uint8_t W25Qxx_ReadStatus(void)
{
  u8 ReadData;	
  EN_SELECT();									
  W25Qxx_ReadWrite(0x05);							
  ReadData = W25Qxx_ReadWrite(0xFF);
  DS_SELECT();				
  return ReadData;	
}

/**
  * @brief  W25Qxxæ�ȴ�
  * @param  None
  * @retval None
  */
void W25Qxx_WaitBusy(void)
{
    while( W25Qxx_ReadStatus() & (0x01));
}

/**
  * @brief  ʹ��дW25Qxx
  * @param  None
  * @retval None
  */
void W25Qxx_WriteEnable(void)
{
  EN_SELECT();
  W25Qxx_ReadWrite(W25QXX_CMD_WREN);
  DS_SELECT();
  while (!(W25Qxx_ReadStatus() & 0x02));
}

/**
  * @brief  ʧ��дW25Qxx
  * @param  None
  * @retval None
  */
void W25Qxx_WriteDisable(void)
{
  EN_SELECT();
  W25Qxx_ReadWrite(W25QXX_CMD_WRDI);
  DS_SELECT();
  while (W25Qxx_ReadStatus() & 0x02);
}

/**
  * @brief  ��������
  * @param  Addr:Ҫ�����ĵ�ַ
  * @retval None
  */
void W25Qxx_SectorErase(uint32_t Addr)
{
//  add = add / W25QXX_SECTOR_SIZE;
  W25Qxx_WriteEnable();								
  EN_SELECT();						
  W25Qxx_ReadWrite(W25QXX_CMD_ERASE_4K);						
  W25Qxx_ReadWrite((uint8_t)(Addr >> 16));					
  W25Qxx_ReadWrite((uint8_t)(Addr >> 8));	
  W25Qxx_ReadWrite(0x00);						
  DS_SELECT();
  W25Qxx_WaitBusy();						
  W25Qxx_WriteDisable();
			
}

/**
  * @brief  ��W25Qxx��ȡָ�����ȵ�����
  * @param  Addr:��ȡ�ĵ�ַ
  * @param  Buf:ָ����ջ�����
  * @param  Len:Ҫ��ȡ�ĳ���
  * @retval None
  */
void W25Qxx_Read(uint32_t Addr, uint8_t *Buf, uint32_t Len)
{
  if (Len == 0)return;
   
  EN_SELECT();
  W25Qxx_ReadWrite(W25QXX_CMD_READ);						
  W25Qxx_ReadWrite((uint8_t)(Addr >> 16));					
  W25Qxx_ReadWrite((uint8_t)(Addr >> 8));	
  W25Qxx_ReadWrite((uint8_t)(Addr & 0xFF));	
  while (Len)
  {
    Len--;
    *Buf++ = W25Qxx_ReadWrite(0x00);	
  }  
  DS_SELECT();  
}

/**
  * @brief  ��W25Qxxд��ָ�����ȵ�����
  * @param  Addr:д���ַ
  * @param  Buf:ָ���ͻ�����
  * @param  Len:Ҫ���͵ĳ���
  * @retval None
  */
void W25Qxx_Write(uint32_t Addr, uint8_t *Buf, uint32_t Len)
{
  uint32_t num;
  if (Len == 0)return;
  while(Len)
  {
    num = W25QXX_PAGE_SIZE;
    if ((Addr % W25QXX_SECTOR_SIZE) == 0)
    {
      W25Qxx_SectorErase(Addr);
    }
    W25Qxx_WriteEnable();
    if (Addr & 0xFF) num = Addr % W25QXX_PAGE_SIZE;
    if (num > Len) num = Len;
    Len -= num;
    EN_SELECT();
    W25Qxx_ReadWrite(W25QXX_CMD_PP);						
    W25Qxx_ReadWrite((uint8_t)(Addr >> 16));					
    W25Qxx_ReadWrite((uint8_t)(Addr >> 8));	
    W25Qxx_ReadWrite((uint8_t)(Addr & 0xFF));
    Addr += num;
    while (num--)
    {
	    W25Qxx_ReadWrite(*Buf++);
    }	
    DS_SELECT();
    W25Qxx_WaitBusy();
    W25Qxx_WriteDisable();
  }
}

