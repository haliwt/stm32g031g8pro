#include "txdecode.h"
#include "gpio.h"


void TxDecode(void)
{
     uint8_t cmdType_0 =aRxBuffer[0] ;
	   uint8_t cmdType_1 =aRxBuffer[1] ;
	 
	  switch(cmdType_0){
		
		  case 0x42:
				
			    if(cmdType_1 == 0x4c){
					   HAL_GPIO_WritePin(GPIOA,LEDA1_Pin, GPIO_PIN_SET);
					
					}
					else{
					
					  return ;
					}
				
			
			break;
		
		
		
		}

}