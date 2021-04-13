#include "txdecode.h"
#include "gpio.h"

static uint8_t BCC(void);

void TxDecode(void)
{
     uint8_t cmdType_0 =aRxBuffer[0] ; //command order 0
	   uint8_t cmdType_1 =aRxBuffer[1] ; //command order 1
	   uint8_t cmdType_2 =aRxBuffer[2] ; //the first group   LEDAxx LED
	   uint8_t cmdType_3 =aRxBuffer[3] ; //the second group   LEDBxx
	   uint8_t cmdType_4 =aRxBuffer[4] ; //the third group    LEDCxx LED
	   uint8_t cmdType_5 =aRxBuffer[5] ; //the fourth group   LEDDxx  LED
	   uint8_t cmdType_6 =aRxBuffer[6] ; //check sum codes
	  switch(cmdType_0){
		
		  case 0x42:
				
			    if(cmdType_1 == 0x4c){
						 if(cmdType_6 ==BCC())
					    HAL_GPIO_WritePin(GPIOA,LEDA1_Pin, GPIO_PIN_SET);
					
					}
					else{
					
					  return ;
					}
				
			
			break;
		
		
		
		}

}

/*************************************************************************
 	*
	*Function Name: uint8_t BCC(uint8_t *sbytes,uint8_t width)
	*Function : BCC checksum code
	*Input Ref: 
	*Output Ref:No
	*
******************************************************************************/
static uint8_t BCC(void)
{
   uint8_t i;
	 
	 uint8_t tembyte =0xAA ^ aRxBuffer[2];
	
    for (i = 3; i <6; i++) {
        tembyte ^=aRxBuffer[i];
    }
    return tembyte;

}