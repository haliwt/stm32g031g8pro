#include "txdecode.h"
#include "gpio.h"
#include "singleled.h"
#include "usart.h"


uint8_t txdata;
uint8_t led_by_id;  //A? ?? B ?
uint8_t led_by_A;   //A
uint8_t led_by_B;  //

static uint8_t BCC(void);




void TxDecode(void)
{
    uint8_t cmdType_0   = aRxBuffer[0] ; //command order 0
	uint8_t cmdType_1 =   aRxBuffer[1] ; //command order 1
	uint8_t cmdType_2 =  aRxBuffer[2] ;  //group A led
	uint8_t cmdType_3 =  aRxBuffer[3];   //group B led
	uint8_t cmdType_6 =aRxBuffer[6] ; //check sum codes   
	  
	 switch(cmdType_0){
		
		  case 0x42:
				
			    if(cmdType_1 == 0x4c){
						if(cmdType_6 ==BCC()){
						 	   
							TurnOff_TheFirstLedA();	
							TurnOff_TheSecondLedB();
							
							led_by_id = cmdType_0;
							txdata =led_by_id;
							HAL_UART_Transmit(&huart1,&txdata, 1, 10);
							if(led_by_id == 0){
							   led_by_id = 2;
							   led_by_B = cmdType_3;

							}
							else{
								led_by_id =1;
                                led_by_A = cmdType_2;
                            }
							  
						}
				}
					else{
					
					  return ;
					}
				
			
			break;
			default:
				 
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
/*************************************************************************
 	*
	*Function Name: void CheckRun(void)
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
void CheckRun(void)
{
	switch(led_by_id){

		case 0:

		break;

		case 1 :  //A group
		       
			   TheFirstGroup_SingleLEDA(led_by_A);

		break;

		case 2:   //B group
               TheSecondGroup_SingleLEDB(led_by_B);
		break;

		default:

		break;
	}

}
/*************************************************************************
 	*
	*Function Name: void CheckRun(void)
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/