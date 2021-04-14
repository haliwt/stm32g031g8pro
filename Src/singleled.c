#include "singleled.h"
#include "gpio.h"





void SingleLed_Test(void)
{

    uint8_t cmdType_0 = aRxBuffer[0]; //command order 0
    uint8_t cmdType_1 = aRxBuffer[1]; //command order 1
	uint8_t cmdType_2 = aRxBuffer[2]; //command order 1
    uint8_t cmdType_3 = aRxBuffer[3]; //check sum codes
    if(cmdType_3 == 0xAA){
        
        TheFirstGroup_SingleLEDA(cmdType_0);
        TheSecondGroup_SingleLEDB(cmdType_1);
		FanControl(cmdType_2);
    }
}
  
/*************************************************************************
 	*
	*Function Name: void TheFirstGroup_SingleLEDA(uint8_t ledvala)
	*Function : Turn On LEDAxx LED
	*Input Ref: receive UART of data
	*Output Ref:No
	*
******************************************************************************/
void TheFirstGroup_SingleLEDA(uint8_t ledvala)
{
        if (ledvala > 8)
        {
          TurnOff_TheFirstLedA();
		  TurnOff_TheSecondLedB();
		}
        else
        {
            switch (ledvala)
            {

			case 0:
					TurnOff_TheFirstLedA();
					TurnOff_TheSecondLedB();
			break;
			
			case 1:
				TurnOff_TheSecondLedB();
				HAL_Delay(100);
                TurnOff_TheFirstLedA();
				HAL_Delay(100);
				//1.turn on LEDA1 =1
			   HAL_GPIO_WritePin(LEDA1_GPIO_Port, LEDA1_Pin, GPIO_PIN_SET);
			   //2.EN on
                HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_SET);
                
                break;

            case 2:
				TurnOff_TheSecondLedB();
				HAL_Delay(100);
	
				TurnOff_TheFirstLedA();
								HAL_Delay(100);
                //turn on LEDA2  
                HAL_GPIO_WritePin(LEDA2_GPIO_Port, LEDA2_Pin, GPIO_PIN_SET);
								HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_SET);
                break;

            case 3:
				TurnOff_TheSecondLedB();
				HAL_Delay(100);
				TurnOff_TheFirstLedA();
				HAL_Delay(100);
                //turn on LEDA3
                HAL_GPIO_WritePin(LEDA3_GPIO_Port, LEDA3_Pin, GPIO_PIN_SET);
						    //2. enable
						    HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_SET);
                break;

            case 4:
				TurnOff_TheSecondLedB();
				HAL_Delay(100);
				TurnOff_TheFirstLedA();
				HAL_Delay(100);
                //turn on LEDA4
                HAL_GPIO_WritePin(LEDA4_GPIO_Port, LEDA4_Pin, GPIO_PIN_SET);
						    HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_SET);
                break;

            case 5:
				TurnOff_TheSecondLedB();
				HAL_Delay(100);
				TurnOff_TheFirstLedA();
				HAL_Delay(100);
                //turn on LEDA5
                HAL_GPIO_WritePin(LEDA5_GPIO_Port, LEDA5_Pin, GPIO_PIN_SET);      //1.the first turn on LED
						    HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_SET);  //2.the second turn on Enable
                break;

            case 6:
				TurnOff_TheSecondLedB();
				HAL_Delay(100);
				TurnOff_TheFirstLedA();
				HAL_Delay(100);
                //turn on LEDA6
                HAL_GPIO_WritePin(LEDA6_GPIO_Port, LEDA6_Pin, GPIO_PIN_SET);
						    HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_SET);  //2.the second turn on Enable
                break;

            case 7:
				TurnOff_TheSecondLedB();
				HAL_Delay(100);
				TurnOff_TheFirstLedA();
				HAL_Delay(100);
                //turn on LEDA7
                HAL_GPIO_WritePin(LEDA7_GPIO_Port, LEDA7_Pin, GPIO_PIN_SET);
						    HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_SET);  //2.the second turn on Enable
                break;

            case 8:
				TurnOff_TheSecondLedB();
				HAL_Delay(100);
				TurnOff_TheFirstLedA();
				HAL_Delay(100);
                //turn on LEDA8
                HAL_GPIO_WritePin(LEDA8_GPIO_Port, LEDA8_Pin, GPIO_PIN_SET);
						    HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_SET);  //2.the second turn on Enable
                break;
            }
        }
}

/*************************************************************************
 	*
	*Function Name: void TheSecondGroup_SingleLEDB(uint_8 ledvalb)
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
void TheSecondGroup_SingleLEDB(uint8_t ledvalb)
{
      
       if (ledvalb > 8)
       {
			TurnOff_TheSecondLedB();
        }
        else
        {
            switch (ledvalb)
            {
			case 0:
				 TurnOff_TheSecondLedB();
			break;

            case 1:
				 TurnOff_TheSecondLedB();
				  HAL_Delay(100);
			   //1.turn on LEDB1 =1
                HAL_GPIO_WritePin(LEDB1_GPIO_Port, LEDB1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(LEDBPWM_GPIO_Port, LEDBPWM_Pin, GPIO_PIN_SET);
                break;

            case 2:
				 TurnOff_TheSecondLedB();
				  HAL_Delay(100);
						 
						   //turn on LEDB1
                HAL_GPIO_WritePin(LEDB2_GPIO_Port, LEDB2_Pin, GPIO_PIN_SET);
								HAL_GPIO_WritePin(LEDBPWM_GPIO_Port, LEDBPWM_Pin, GPIO_PIN_SET);
                break;

            case 3:
							  TurnOff_TheSecondLedB();
								HAL_Delay(100);
							  //turn on LEDB3=1
                HAL_GPIO_WritePin(LEDB3_GPIO_Port, LEDB3_Pin, GPIO_PIN_SET);
								HAL_GPIO_WritePin(LEDBPWM_GPIO_Port, LEDBPWM_Pin, GPIO_PIN_SET);
                break;

            case 4:
                TurnOff_TheSecondLedB();
								HAL_Delay(100);
							  //turn on LEDB4=1
                HAL_GPIO_WritePin(LEDB4_GPIO_Port, LEDB4_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(LEDBPWM_GPIO_Port, LEDBPWM_Pin, GPIO_PIN_SET);
						break;

            case 5:
						  TurnOff_TheSecondLedB();
								HAL_Delay(100);
							  //turn on LEDB5=1
                HAL_GPIO_WritePin(LEDB5_GPIO_Port, LEDB5_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(LEDBPWM_GPIO_Port, LEDBPWM_Pin, GPIO_PIN_SET);
						break;

            case 6:
                // HAL_GPIO_WritePin(LEDB6_GPIO_Port,LEDB6_Pin, GPIO_PIN_SET);
                break;

            case 7:
						   TurnOff_TheSecondLedB();
								HAL_Delay(100);
							  //turn on LEDB7 =1
                HAL_GPIO_WritePin(LEDB7_GPIO_Port, LEDB7_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(LEDBPWM_GPIO_Port, LEDBPWM_Pin, GPIO_PIN_SET);
						break;

            case 8:

								TurnOff_TheSecondLedB();
								HAL_Delay(100);
						    //turn on LEDB8 =1
                HAL_GPIO_WritePin(LEDB8_GPIO_Port, LEDB8_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(LEDBPWM_GPIO_Port, LEDBPWM_Pin, GPIO_PIN_SET);
						break;
            }
        }
 }

/*************************************************************************
 	*
	*Function Name:static void FanControl(void)
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
void FanControl(uint8_t fanval)
{
    switch(fanval){
		   
			case 0:  
				HAL_GPIO_WritePin( FAN_GPIO_Port,FAN_Pin,GPIO_PIN_SET);
			break;
			
			case 1:
				HAL_GPIO_WritePin( FAN_GPIO_Port,FAN_Pin,GPIO_PIN_RESET);
			
			break;
			case 2:
				HAL_GPIO_WritePin( FAN_GPIO_Port,FAN_Pin,GPIO_PIN_SET);
			break;
			default :
					HAL_GPIO_WritePin( FAN_GPIO_Port,FAN_Pin,GPIO_PIN_SET);
			break;
		
	  }

}
/*************************************************************************
 	*
	*Function Name:void TurnOff_TheFirstLedA(void)
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
void TurnOff_TheFirstLedA(void)
{
     //turn off LEDA LED
	   HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_RESET);
	   HAL_Delay(200);
	   HAL_GPIO_WritePin(LEDA1_GPIO_Port, LEDA1_Pin | LEDA2_Pin | LEDA3_Pin | LEDA4_Pin | LEDA5_Pin | LEDA6_Pin, GPIO_PIN_RESET);
       HAL_GPIO_WritePin(LEDA7_GPIO_Port, LEDA7_Pin | LEDA8_Pin, GPIO_PIN_RESET);

}
/*************************************************************************
 	*
	*Function Name:void TurnOff_TheSecondLedB(void)
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
void TurnOff_TheSecondLedB(void)
{
		 //turn off LEDB LED
		 HAL_GPIO_WritePin(LEDBPWM_GPIO_Port, LEDBPWM_Pin, GPIO_PIN_RESET);
		 HAL_Delay(200);
		 HAL_GPIO_WritePin(LEDB1_GPIO_Port, LEDB1_Pin | LEDB2_Pin | LEDB3_Pin, GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(LEDB4_GPIO_Port, LEDB4_Pin | LEDB5_Pin | LEDB7_Pin, GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(LEDB8_GPIO_Port, LEDB8_Pin, GPIO_PIN_RESET);
}