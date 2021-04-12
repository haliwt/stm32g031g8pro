/**
  ******************************************************************************
  * @file    stm32g0xx_hal_uart.h
  * @author  MCD Application Team
  * @brief   Header file of UART HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32G0xx_HAL_UART_H
#define STM32G0xx_HAL_UART_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal_def.h"

/** @addtogroup STM32G0xx_HAL_Driver
  * @{
  */

/** @addtogroup UART
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup UART_Exported_Types UART Exported Types
  * @{
  */

/**
  * @brief UART Init Structure definition
  */
typedef struct
{
  uint32_t BaudRate;                  /*!< This member configures the UART communication baud rate.
                                           The baud rate register is computed using the following formula:
                                           LPUART:
                                           =======
                                           Baud Rate Register = ((256 * lpuart_ker_ckpres) / ((huart->Init.BaudRate)))
                                           where lpuart_ker_ck_pres is the UART input clock divided by a prescaler
                                           UART:
                                           =====
                                           - If oversampling is 16 or in LIN mode,
                                              Baud Rate Register = ((uart_ker_ckpres) / ((huart->Init.BaudRate)))
                                           - If oversampling is 8,
                                              Baud Rate Register[15:4] = ((2 * uart_ker_ckpres) /
                                              ((huart->Init.BaudRate)))[15:4]
                                              Baud Rate Register[3] =  0
                                              Baud Rate Register[2:0] =  (((2 * uart_ker_ckpres) /
                                              ((huart->Init.BaudRate)))[3:0]) >> 1
                                           where uart_ker_ck_pres is the UART input clock divided by a prescaler */

  uint32_t WordLength;                /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref UARTEx_Word_Length. */

  uint32_t StopBits;                  /*!< Specifies the number of stop bits transmitted.
                                           This parameter can be a value of @ref UART_Stop_Bits. */

  uint32_t Parity;                    /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref UART_Parity
                                           @note When parity is enabled, the computed parity is inserted
                                                 at the MSB position of the transmitted data (9th bit when
                                                 the word length is set to 9 data bits; 8th bit when the
                                                 word length is set to 8 data bits). */

  uint32_t Mode;                      /*!< Specifies whether the Receive or Transmit mode is enabled or disabled.
                                           This parameter can be a value of @ref UART_Mode. */

  uint32_t HwFlowCtl;                 /*!< Specifies whether the hardware flow control mode is enabled
                                           or disabled.
                                           This parameter can be a value of @ref UART_Hardware_Flow_Control. */

  uint32_t OverSampling;              /*!< Specifies whether the Over sampling 8 is enabled or disabled,
                                           to achieve higher speed (up to f_PCLK/8).
                                           This parameter can be a value of @ref UART_Over_Sampling. */

  uint32_t OneBitSampling;            /*!< Specifies whether a single sample or three samples' majority vote is selected.
                                           Selecting the single sample method increases the receiver tolerance to clock
                                           deviations. This parameter can be a value of @ref UART_OneBit_Sampling. */

  uint32_t ClockPrescaler;            /*!< Specifies the prescaler value used to divide the UART clock source.
                                           This parameter can be a value of @ref UART_ClockPrescaler. */

} UART_InitTypeDef;

/**
  * @brief  UART Advanced Features initialization structure definition
  */
typedef struct
{
  uint32_t AdvFeatureInit;        /*!< Specifies which advanced UART features is initialized. Several
                                       Advanced Features may be initialized at the same time .
                                       This parameter can be a value of
                                       @ref UART_Advanced_Features_Initialization_Type. */

  uint32_t TxPinLevelInvert;      /*!< Specifies whether the TX pin active level is inverted.
                                       This parameter can be a value of @ref UART_Tx_Inv. */

  uint32_t RxPinLevelInvert;      /*!< Specifies whether the RX pin active level is inverted.
                                       This parameter can be a value of @ref UART_Rx_Inv. */

  uint32_t DataInvert;            /*!< Specifies whether data are inverted (positive/direct logic
                                       vs negative/inverted logic).
                                       This parameter can be a value of @ref UART_Data_Inv. */

  uint32_t Swap;                  /*!< Specifies whether TX and RX pins are swapped.
                                       This parameter can be a value of @ref UART_Rx_Tx_Swap. */

  uint32_t OverrunDisable;        /*!< Specifies whether the reception overrun detection is disabled.
                                       This parameter can be a value of @ref UART_Overrun_Disable. */

  uint32_t DMADisableonRxError;   /*!< Specifies whether the DMA is disabled in case of reception error.
                                       This parameter can be a value of @ref UART_DMA_Disable_on_Rx_Error. */

  uint32_t AutoBaudRateEnable;    /*!< Specifies whether auto Baud rate detection is enabled.
                                       This parameter can be a value of @ref UART_AutoBaudRate_Enable. */

  uint32_t AutoBaudRateMode;      /*!< If auto Baud rate detection is enabled, specifies how the rate
                                       detection is carried out.
                                       This parameter can be a value of @ref UART_AutoBaud_Rate_Mode. */

  uint32_t MSBFirst;              /*!< Specifies whether MSB is sent first on UART line.
                                       This parameter can be a value of @ref UART_MSB_First. */
} UART_AdvFeatureInitTypeDef;

/**
  * @brief HAL UART State definition
  * @note  HAL UART State value is a combination of 2 different substates:
  *        gState and RxState (see @ref UART_State_Definition).
  *        - gState contains UART state information related to global Handle management
  *          and also information related to Tx operations.
  *          gState value coding follow below described bitmap :
  *          b7-b6  Error information
  *             00 : No Error
  *             01 : (Not Used)
  *             10 : Timeout
  *             11 : Error
  *          b5     Peripheral initialization status
  *             0  : Reset (Peripheral not initialized)
  *             1  : Init done (Peripheral not initialized. HAL UART Init function already called)
  *          b4-b3  (not used)
  *             xx : Should be set to 00
  *          b2     Intrinsic process state
  *             0  : Ready
  *             1  : Busy (Peripheral busy with some configuration or internal operations)
  *          b1     (not used)
  *             x  : Should be set to 0
  *          b0     Tx state
  *             0  : Ready (no Tx operation ongoing)
  *             1  : Busy (Tx operation ongoing)
  *        - RxState contains information related to Rx operations.
  *          RxState value coding follow below described bitmap :
  *          b7-b6  (not used)
  *             xx : Should be set to 00
  *          b5     Peripheral initialization status
  *             0  : Reset (Peripheral not initialized)
  *             1  : Init done (Peripheral not initialized)
  *          b4-b2  (not used)
  *            xxx : Should be set to 000
  *          b1     Rx state
  *             0  : Ready (no Rx operation ongoing)
  *             1  : Busy (Rx operation ongoing)
  *          b0     (not used)
  *             x  : Should be set to 0.
  */
typedef uint32_t HAL_UART_StateTypeDef;

/**
  * @brief UART clock sources definition
  */
typedef enum
{
  UART_CLOCKSOURCE_PCLK1      = 0x00U,    /*!< PCLK1 clock source  */
  UART_CLOCKSOURCE_HSI        = 0x02U,    /*!< HSI clock source    */
  UART_CLOCKSOURCE_SYSCLK     = 0x04U,    /*!< SYSCLK clock source */
  UART_CLOCKSOURCE_LSE        = 0x08U,    /*!< LSE clock source       */
  UART_CLOCKSOURCE_UNDEFINED  = 0x10U     /*!< Undefined clock source */
} UART_ClockSourceTypeDef;

/**
  * @brief HAL UART Reception type definition
  * @note  HAL UART Reception type value aims to identify which type of Reception is ongoing.
  *        It is expected to admit following values :
  *           HAL_UART_RECEPTION_STANDARD         = 0x00U,
  *           HAL_UART_RECEPTION_TOIDLE           = 0x01U,
  *           HAL_UART_RECEPTION_TORTO            = 0x02U,
  *           HAL_UART_RECEPTION_TOCHARMATCH      = 0x03U,
  */
typedef uint32_t HAL_UART_RxTypeTypeDef;

/**
  * @brief  UART handle Structure definition
  */
typedef struct __UART_HandleTypeDef
{
  USART_TypeDef            *Instance;                /*!< UART registers base address        */

  UART_InitTypeDef         Init;                     /*!< UART communication parameters      */

  UART_AdvFeatureInitTypeDef AdvancedInit;           /*!< UART Advanced Features initialization parameters */

  uint8_t                  *pTxBuffPtr;              /*!< Pointer to UART Tx transfer Buffer */

  uint16_t                 TxXferSize;               /*!< UART Tx Transfer size              */

  __IO uint16_t            TxXferCount;              /*!< UART Tx Transfer Counter           */

  uint8_t                  *pRxBuffPtr;              /*!< Pointer to UART Rx transfer Buffer */

  uint16_t                 RxXferSize;               /*!< UART Rx Transfer size              */

  __IO uint16_t            RxXferCount;              /*!< UART Rx Transfer Counter           */

  uint16_t                 Mask;                     /*!< UART Rx RDR register mask          */

  uint32_t                 FifoMode;                 /*!< Specifies if the FIFO mode is being used.
                                                          This parameter can be a value of @ref UARTEx_FIFO_mode. */

  uint16_t                 NbRxDataToProcess;        /*!< Number of data to process during RX ISR execution */

  uint16_t                 NbTxDataToProcess;        /*!< Number of data to process during TX ISR execution */

  __IO HAL_UART_RxTypeTypeDef ReceptionType;         /*!< Type of ongoing reception          */

  void (*RxISR)(struct __UART_HandleTypeDef *huart); /*!< Function pointer on Rx IRQ handler */

  void (*TxISR)(struct __UART_HandleTypeDef *huart); /*!< Function pointer on Tx IRQ handler */

  DMA_HandleTypeDef        *hdmatx;                  /*!< UART Tx DMA Handle parameters      */

  DMA_HandleTypeDef        *hdmarx;                  /*!< UART Rx DMA Handle parameters      */

  HAL_LockTypeDef           Lock;                    /*!< Locking object                     */

  __IO HAL_UART_StateTypeDef    gState;              /*!< UART state information related to global Handle management
                                                          and also related to Tx operations. This parameter
                                                          can be a value of @ref HAL_UART_StateTypeDef */

  __IO HAL_UART_StateTypeDef    RxState;             /*!< UART state information related to Rx operations. This
                                                          parameter can be a value of @ref HAL_UART_StateTypeDef */

  __IO uint32_t                 ErrorCode;           /*!< UART Error code                    */

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
  void (* TxHalfCpltCallback)(struct __UART_HandleTypeDef *huart);        /*!< UART Tx Half Complete Callback        */
  void (* TxCpltCallback)(struct __UART_HandleTypeDef *huart);            /*!< UART Tx Complete Callback             */
  void (* RxHalfCpltCallback)(struct __UART_HandleTypeDef *huart);        /*!< UART Rx Half Complete Callback        */
  void (* RxCpltCallback)(struct __UART_HandleTypeDef *huart);            /*!< UART Rx Complete Callback             */
  void (* ErrorCallback)(struct __UART_HandleTypeDef *huart);             /*!< UART Error Callback                   */
  void (* AbortCpltCallback)(struct __UART_HandleTypeDef *huart);         /*!< UART Abort Complete Callback          */
  void (* AbortTransmitCpltCallback)(struct __UART_HandleTypeDef *huart); /*!< UART Abort Transmit Complete Callback */
  void (* AbortReceiveCpltCallback)(struct __UART_HandleTypeDef *huart);  /*!< UART Abort Receive Complete Callback  */
  void (* WakeupCallback)(struct __UART_HandleTypeDef *huart);            /*!< UART Wakeup Callback                  */
  void (* RxFifoFullCallback)(struct __UART_HandleTypeDef *huart);        /*!< UART Rx Fifo Full Callback            */
  void (* TxFifoEmptyCallback)(struct __UART_HandleTypeDef *huart);       /*!< UART Tx Fifo Empty Callback           */
  void (* RxEventCallback)(struct __UART_HandleTypeDef *huart, uint16_t Pos); /*!< UART Reception Event Callback     */

  void (* MspInitCallback)(struct __UART_HandleTypeDef *huart);           /*!< UART Msp Init callback                */
  void (* MspDeInitCallback)(struct __UART_HandleTypeDef *huart);         /*!< UART Msp DeInit callback              */
#endif  /* USE_HAL_UART_REGISTER_CALLBACKS */

} UART_HandleTypeDef;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
/**
  * @brief  HAL UART Callback ID enumeration definition
  */
typedef enum
{
  HAL_UART_TX_HALFCOMPLETE_CB_ID         = 0x00U,    /*!< UART Tx Half Complete Callback ID        */
  HAL_UART_TX_COMPLETE_CB_ID             = 0x01U,    /*!< UART Tx Complete Callback ID             */
  HAL_UART_RX_HALFCOMPLETE_CB_ID         = 0x02U,    /*!< UART Rx Half Complete Callback ID        */
  HAL_UART_RX_COMPLETE_CB_ID             = 0x03U,    /*!< UART Rx Complete Callback ID             */
  HAL_UART_ERROR_CB_ID                   = 0x04U,    /*!< UART Error Callback ID                   */
  HAL_UART_ABORT_COMPLETE_CB_ID          = 0x05U,    /*!< UART Abort Complete Callback ID          */
  HAL_UART_ABORT_TRANSMIT_COMPLETE_CB_ID = 0x06U,    /*!< UART Abort Transmit Complete Callback ID */
  HAL_UART_ABORT_RECEIVE_COMPLETE_CB_ID  = 0x07U,    /*!< UART Abort Receive Complete Callback ID  */
  HAL_UART_WAKEUP_CB_ID                  = 0x08U,    /*!< UART Wakeup Callback ID                  */
  HAL_UART_RX_FIFO_FULL_CB_ID            = 0x09U,    /*!< UART Rx Fifo Full Callback ID            */
  HAL_UART_TX_FIFO_EMPTY_CB_ID           = 0x0AU,    /*!< UART Tx Fifo Empty Callback ID           */

  HAL_UART_MSPINIT_CB_ID                 = 0x0BU,    /*!< UART MspInit callback ID                 */
  HAL_UART_MSPDEINIT_CB_ID               = 0x0CU     /*!< UART MspDeInit callback ID               */

} HAL_UART_CallbackIDTypeDef;

/**
  * @brief  HAL UART Callback pointer definition
  */
typedef  void (*pUART_CallbackTypeDef)(UART_HandleTypeDef *huart);  /*!< pointer to an UART callback function */
typedef  void (*pUART_RxEventCallbackTypeDef)(struct __UART_HandleTypeDef *huart, uint16_t Pos);   /*!< pointer to a UART Rx Event specific callback function */

#endif /* USE_HAL_UART_REGISTER_CALLBACKS */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup UART_Exported_Constants UART Exported Constants
  * @{
  */

/** @defgroup UART_State_Definition UART State Code Definition
  * @{
  */
#define  HAL_UART_STATE_RESET         0x00000000U    /*!< Peripheral is not initialized
                                                          Value is allowed for gState and RxState */
#define  HAL_UART_STATE_READY         0x00000020U    /*!< Peripheral Initialized and ready for use
                                                          Value is allowed for gState and RxState */
#define  HAL_UART_STATE_BUSY          0x00000024U    /*!< an internal process is ongoing
                                                          Value is allowed for gState only */
#define  HAL_UART_STATE_BUSY_TX       0x00000021U    /*!< Data Transmission process is ongoing
                                                          Value is allowed for gState only */
#define  HAL_UART_STATE_BUSY_RX       0x00000022U    /*!< Data Reception process is ongoing
                                                          Value is allowed for RxState only */
#define  HAL_UART_STATE_BUSY_TX_RX    0x00000023U    /*!< Data Transmission and Reception process is ongoing
                                                          Not to be used for neither gState nor RxState.Value is result
                                                          of combination (Or) between gState and RxState values */
#define  HAL_UART_STATE_TIMEOUT       0x000000A0U    /*!< Timeout state
                                                          Value is allowed for gState only */
#define  HAL_UART_STATE_ERROR         0x000000E0U    /*!< Error
                                                          Value is allowed for gState only */
/**
  * @}
  */

/** @defgroup UART_Error_Definition   UART Error Definition
  * @{
  */
#define  HAL_UART_ERROR_NONE             ((uint32_t)0x00000000U)    /*!< No error                */
#define  HAL_UART_ERROR_PE               ((uint32_t)0x00000001U)    /*!< Parity error            */
#define  HAL_UART_ERROR_NE               ((uint32_t)0x00000002U)    /*!< Noise error             */
#define  HAL_UART_ERROR_FE               ((uint32_t)0x00000004U)    /*!< Frame error             */
#define  HAL_UART_ERROR_ORE              ((uint32_t)0x00000008U)    /*!< Overrun error           */
#define  HAL_UART_ERROR_DMA              ((uint32_t)0x00000010U)    /*!< DMA transfer error      */
#define  HAL_UART_ERROR_RTO              ((uint32_t)0x00000020U)    /*!< Receiver Timeout error  */

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
#define  HAL_UART_ERROR_INVALID_CALLBACK ((uint32_t)0x00000040U)    /*!< Invalid Callback error  */
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup UART_Stop_Bits   UART Number of Stop Bits
  * @{
  */
#define UART_STOPBITS_0_5                    USART_CR2_STOP_0                     /*!< UART frame with 0.5 stop bit  */
#define UART_STOPBITS_1                     0x00000000U                           /*!< UART frame with 1 stop bit    */
#define UART_STOPBITS_1_5                   (USART_CR2_STOP_0 | USART_CR2_STOP_1) /*!< UART frame with 1.5 stop bits */
#define UART_STOPBITS_2                      USART_CR2_STOP_1                     /*!< UART frame with 2 stop bits   */
/**
  * @}
  */

/** @defgroup UART_Parity  UART Parity
  * @{
  */
#define UART_PARITY_NONE                    0x00000000U                        /*!< No parity   */
#define UART_PARITY_EVEN                    USART_CR1_PCE                      /*!< Even parity */
#define UART_PARITY_ODD                     (USART_CR1_PCE | USART_CR1_PS)     /*!< Odd parity  */
/**
  * @}
  */

/** @defgroup UART_Hardware_Flow_Control UART Hardware Flow Control
  * @{
  */
#define UART_HWCONTROL_NONE                  0x00000000U                          /*!< No hardware control       */
#define UART_HWCONTROL_RTS                   USART_CR3_RTSE                       /*!< Request To Send           */
#define UART_HWCONTROL_CTS                   USART_CR3_CTSE                       /*!< Clear To Send             */
#define UART_HWCONTROL_RTS_CTS               (USART_CR3_RTSE | USART_CR3_CTSE)    /*!< Request and Clear To Send */
/**
  * @}
  */

/** @defgroup UART_Mode UART Transfer Mode
  * @{
  */
#define UART_MODE_RX                        USART_CR1_RE                    /*!< RX mode        */
#define UART_MODE_TX                        USART_CR1_TE                    /*!< TX mode        */
#define UART_MODE_TX_RX                     (USART_CR1_TE |USART_CR1_RE)    /*!< RX and TX mode */
/**
  * @}
  */

/** @defgroup UART_State  UART State
  * @{
  */
#define UART_STATE_DISABLE                  0x00000000U         /*!< UART disabled  */
#define UART_STATE_ENABLE                   USART_CR1_UE        /*!< UART enabled   */
/**
  * @}
  */

/** @defgroup UART_Over_Sampling UART Over Sampling
  * @{
  */
#define UART_OVERSAMPLING_16                0x00000000U         /*!< Oversampling by 16 */
#define UART_OVERSAMPLING_8                 USART_CR1_OVER8     /*!< Oversampling by 8  */
/**
  * @}
  */

/** @defgroup UART_OneBit_Sampling UART One Bit Sampling Method
  * @{
  */
#define UART_ONE_BIT_SAMPLE_DISABLE         0x00000000U         /*!< One-bit sampling disable */
#define UART_ONE_BIT_SAMPLE_ENABLE          USART_CR3_ONEBIT    /*!< One-bit sampling enable  */
/**
  * @}
  */

/** @defgroup UART_ClockPrescaler  UART Clock Prescaler
  * @{
  */
#define UART_PRESCALER_DIV1    0x00000000U  /*!< fclk_pres = fclk     */
#define UART_PRESCALER_DIV2    0x00000001U  /*!< fclk_pres = fclk/2   */
#define UART_PRESCALER_DIV4    0x00000002U  /*!< fclk_pres = fclk/4   */
#define UART_PRESCALER_DIV6    0x00000003U  /*!< fclk_pres = fclk/6   */
#define UART_PRESCALER_DIV8    0x00000004U  /*!< fclk_pres = fclk/8   */
#define UART_PRESCALER_DIV10   0x00000005U  /*!< fclk_pres = fclk/10  */
#define UART_PRESCALER_DIV12   0x00000006U  /*!< fclk_pres = fclk/12  */
#define UART_PRESCALER_DIV16   0x00000007U  /*!< fclk_pres = fclk/16  */
#define UART_PRESCALER_DIV32   0x00000008U  /*!< fclk_pres = fclk/32  */
#define UART_PRESCALER_DIV64   0x00000009U  /*!< fclk_pres = fclk/64  */
#define UART_PRESCALER_DIV128  0x0000000AU  /*!< fclk_pres = fclk/128 */
#define UART_PRESCALER_DIV256  0x0000000BU  /*!< fclk_pres = fclk/256 */
/**
  * @}
  */

/** @defgroup UART_AutoBaud_Rate_Mode    UART Advanced Feature AutoBaud Rate Mode
  * @{
  */
#define UART_ADVFEATURE_AUTOBAUDRATE_ONSTARTBIT    0x00000000U           /*!< Auto Baud rate detection
                                                                              on start bit              */
#define UART_ADVFEATURE_AUTOBAUDRATE_ONFALLINGEDGE USART_CR2_ABRMODE_0   /*!< Auto Baud rate detection
                                                                              on falling edge           */
#define UART_ADVFEATURE_AUTOBAUDRATE_ON0X7FFRAME   USART_CR2_ABRMODE_1   /*!< Auto Baud rate detection
                                                                              on 0x7F frame detection   */
#define UART_ADVFEATURE_AUTOBAUDRATE_ON0X55FRAME   USART_CR2_ABRMODE     /*!< Auto Baud rate detection
                                                                              on 0x55 frame detection   */
/**
  * @}
  */

/** @defgroup UART_Receiver_Timeout UART Receiver Timeout
  * @{
  */
#define UART_RECEIVER_TIMEOUT_DISABLE       0x00000000U                /*!< UART Receiver Timeout disable */
#define UART_RECEIVER_TIMEOUT_ENABLE        USART_CR2_RTOEN            /*!< UART Receiver Timeout enable  */
/**
  * @}
  */

/** @defgroup UART_LIN    UART Local Interconnection Network mode
  * @{
  */
#define UART_LIN_DISABLE                    0x00000000U                /*!< Local Interconnect Network disable */
#define UART_LIN_ENABLE                     USART_CR2_LINEN            /*!< Local Interconnect Network enable  */
/**
  * @}
  */

/** @defgroup UART_LIN_Break_Detection  UART LIN Break Detection
  * @{
  */
#define UART_LINBREAKDETECTLENGTH_10B       0x00000000U                /*!< LIN 10-bit break detection length */
#define UART_LINBREAKDETECTLENGTH_11B       USART_CR2_LBDL             /*!< LIN 11-bit break detection length  */
/**
  * @}
  */

/** @defgroup UART_DMA_Tx    UART DMA Tx
  * @{
  */
#define UART_DMA_TX_DISABLE                 0x00000000U                /*!< UART DMA TX disabled */
#define UART_DMA_TX_ENABLE                  USART_CR3_DMAT             /*!< UART DMA TX enabled  */
/**
  * @}
  */

/** @defgroup UART_DMA_Rx   UART DMA Rx
  * @{
  */
#define UART_DMA_RX_DISABLE                 0x00000000U                 /*!< UART DMA RX disabled */
#define UART_DMA_RX_ENABLE                  USART_CR3_DMAR              /*!< UART DMA RX enabled  */
/**
  * @}
  */

/** @defgroup UART_Half_Duplex_Selection  UART Half Duplex Selection
  * @{
  */
#define UART_HALF_DUPLEX_DISABLE            0x00000000U                 /*!< UART half-duplex disabled */
#define UART_HALF_DUPLEX_ENABLE             USART_CR3_HDSEL             /*!< UART half-duplex enabled  */
/**
  * @}
  */

/** @defgroup UART_WakeUp_Methods   UART WakeUp Methods
  * @{
  */
#define UART_WAKEUPMETHOD_IDLELINE          0x00000000U                 /*!< UART wake-up on idle line    */
#define UART_WAKEUPMETHOD_ADDRESSMARK       USART_CR1_WAKE              /*!< UART wake-up on address mark */
/**
  * @}
  */

/** @defgroup UART_Request_Parameters UART Request Parameters
  * @{
  */
#define UART_AUTOBAUD_REQUEST               USART_RQR_ABRRQ        /*!< Auto-Baud Rate Request      */
#define UART_SENDBREAK_REQUEST              USART_RQR_SBKRQ        /*!< Send Break Request          */
#define UART_MUTE_MODE_REQUEST              USART_RQR_MMRQ         /*!< Mute Mode Request           */
#define UART_RXDATA_FLUSH_REQUEST           USART_RQR_RXFRQ        /*!< Receive Data flush Request  */
#define UART_TXDATA_FLUSH_REQUEST           USART_RQR_TXFRQ        /*!< Transmit data flush Request */
/**
  * @}
  */

/** @defgroup UART_Advanced_Features_Initialization_Type  UART Advanced Feature Initialization Type
  * @{
  */
#define UART_ADVFEATURE_NO_INIT                 0x00000000U          /*!< No advanced feature initialization       */
#define UART_ADVFEATURE_TXINVERT_INIT           0x00000001U          /*!< TX pin active level inversion            */
#define UART_ADVFEATURE_RXINVERT_INIT           0x00000002U          /*!< RX pin active level inversion            */
#define UART_ADVFEATURE_DATAINVERT_INIT         0x00000004U          /*!< Binary data inversion                    */
#define UART_ADVFEATURE_SWAP_INIT               0x00000008U          /*!< TX/RX pins swap                          */
#define UART_ADVFEATURE_RXOVERRUNDISABLE_INIT   0x00000010U          /*!< RX overrun disable                       */
#define UART_ADVFEATURE_DMADISABLEONERROR_INIT  0x00000020U          /*!< DMA disable on Reception Error           */
#define UART_ADVFEATURE_AUTOBAUDRATE_INIT       0x00000040U          /*!< Auto Baud rate detection initialization  */
#define UART_ADVFEATURE_MSBFIRST_INIT           0x00000080U          /*!< Most significant bit sent/received first */
/**
  * @}
  */

/** @defgroup UART_Tx_Inv UART Advanced Feature TX Pin Active Level Inversion
  * @{
  */
#define UART_ADVFEATURE_TXINV_DISABLE       0x00000000U             /*!< TX pin active level inversion disable */
#define UART_ADVFEATURE_TXINV_ENABLE        USART_CR2_TXINV         /*!< TX pin active level inversion enable  */
/**
  * @}
  */

/** @defgroup UART_Rx_Inv UART Advanced Feature RX Pin Active Level Inversion
  * @{
  */
#define UART_ADVFEATURE_RXINV_DISABLE       0x00000000U             /*!< RX pin active level inversion disable */
#define UART_ADVFEATURE_RXINV_ENABLE        USART_CR2_RXINV         /*!< RX pin active level inversion enable  */
/**
  * @}
  */

/** @defgroup UART_Data_Inv  UART Advanced Feature Binary Data Inversion
  * @{
  */
#define UART_ADVFEATURE_DATAINV_DISABLE     0x00000000U             /*!< Binary data inversion disable */
#define UART_ADVFEATURE_DATAINV_ENABLE      USART_CR2_DATAINV       /*!< Binary data inversion enable  */
/**
  * @}
  */

/** @defgroup UART_Rx_Tx_Swap UART Advanced Feature RX TX Pins Swap
  * @{
  */
#define UART_ADVFEATURE_SWAP_DISABLE        0x00000000U             /*!< TX/RX pins swap disable */
#define UART_ADVFEATURE_SWAP_ENABLE         USART_CR2_SWAP          /*!< TX/RX pins swap enable  */
/**
  * @}
  */

/** @defgroup UART_Overrun_Disable  UART Advanced Feature Overrun Disable
  * @{
  */
#define UART_ADVFEATURE_OVERRUN_ENABLE      0x00000000U             /*!< RX overrun enable  */
#define UART_ADVFEATURE_OVERRUN_DISABLE     USART_CR3_OVRDIS        /*!< RX overrun disable */
/**
  * @}
  */

/** @defgroup UART_AutoBaudRate_Enable  UART Advanced Feature Auto BaudRate Enable
  * @{
  */
#define UART_ADVFEATURE_AUTOBAUDRATE_DISABLE   0x00000000U          /*!< RX Auto Baud rate detection enable  */
#define UART_ADVFEATURE_AUTOBAUDRATE_ENABLE    USART_CR2_ABREN      /*!< RX Auto Baud rate detection disable */
/**
  * @}
  */

/** @defgroup UART_DMA_Disable_on_Rx_Error   UART Advanced Feature DMA Disable On Rx Error
  * @{
  */
#define UART_ADVFEATURE_DMA_ENABLEONRXERROR    0x00000000U          /*!< DMA enable on Reception Error  */
#define UART_ADVFEATURE_DMA_DISABLEONRXERROR   USART_CR3_DDRE       /*!< DMA disable on Reception Error */
/**
  * @}
  */

/** @defgroup UART_MSB_First   UART Advanced Feature MSB First
  * @{
  */
#define UART_ADVFEATURE_MSBFIRST_DISABLE    0x00000000U             /*!< Most significant bit sent/received
                                                                         first disable                      */
#define UART_ADVFEATURE_MSBFIRST_ENABLE     USART_CR2_MSBFIRST      /*!< Most significant bit sent/received
                                                                         first enable                       */
/**
  * @}
  */

/** @defgroup UART_Stop_Mode_Enable   UART Advanced Feature Stop Mode Enable
  * @{
  */
#define UART_ADVFEATURE_STOPMODE_DISABLE    0x00000000U             /*!< UART stop mode disable */
#define UART_ADVFEATURE_STOPMODE_ENABLE     USART_CR1_UESM          /*!< UART stop mode enable  */
/**
  * @}
  */

/** @defgroup UART_Mute_Mode   UART Advanced Feature Mute Mode Enable
  * @{
  */
#define UART_ADVFEATURE_MUTEMODE_DISABLE    0x00000000U             /*!< UART mute mode disable */
#define UART_ADVFEATURE_MUTEMODE_ENABLE     USART_CR1_MME           /*!< UART mute mode enable  */
/**
  * @}
  */

/** @defgroup UART_CR2_ADDRESS_LSB_POS    UART Address-matching LSB Position In CR2 Register
  * @{
  */
#define UART_CR2_ADDRESS_LSB_POS             24U             /*!< UART address-matching LSB position in CR2 register */
/**
  * @}
  */

/** @defgroup UART_WakeUp_from_Stop_Selection   UART WakeUp From Stop Selection
  * @{
  */
#define UART_WAKEUP_ON_ADDRESS              0x00000000U             /*!< UART wake-up on address                     */
#define UART_WAKEUP_ON_STARTBIT             USART_CR3_WUS_1         /*!< UART wake-up on start bit                   */
#define UART_WAKEUP_ON_READDATA_NONEMPTY    USART_CR3_WUS           /*!< UART wake-up on receive data register
                                                                         not empty or RXFIFO is not empty            */
/**
  * @}
  */

/** @defgroup UART_DriverEnable_Polarity      UART DriverEnable Polarity
  * @{
  */
#define UART_DE_POLARITY_HIGH               0x00000000U             /*!< Driver enable signal is active high */
#define UART_DE_POLARITY_LOW                USART_CR3_DEP           /*!< Driver enable signal is active low  */
/**
  * @}
  */

/** @defgroup UART_CR1_DEAT_ADDRESS_LSB_POS    UART Driver Enable Assertion Time LSB Position In CR1 Register
  * @{
  */
#define UART_CR1_DEAT_ADDRESS_LSB_POS       21U      /*!< UART Driver Enable assertion time LSB
                                                          position in CR1 register */
/**
  * @}
  */

/** @defgroup UART_CR1_DEDT_ADDRESS_LSB_POS    UART Driver Enable DeAssertion Time LSB Position In CR1 Register
  * @{
  */
#define UART_CR1_DEDT_ADDRESS_LSB_POS       16U      /*!< UART Driver Enable de-assertion time LSB
                                                          position in CR1 register */
/**
  * @}
  */

/** @defgroup UART_Interruption_Mask    UART Interruptions Flag Mask
  * @{
  */
#define UART_IT_MASK                        0x001FU  /*!< UART interruptions flags mask */
/**
  * @}
  */

/** @defgroup UART_TimeOut_Value    UART polling-based communications time-out value
  * @{
  */
#define HAL_UART_TIMEOUT_VALUE              0x1FFFFFFU  /*!< UART polling-based communications time-out value */
/**
  * @}
  */

/** @defgroup UART_Flags     UART Status Flags
  *        Elements values convention: 0xXXXX
  *           - 0xXXXX  : Flag mask in the ISR register
  * @{
  */
#define UART_FLAG_TXFT                      USART_ISR_TXFT          /*!< UART TXFIFO threshold flag                */
#define UART_FLAG_RXFT                      USART_ISR_RXFT          /*!< UART RXFIFO threshold flag                */
#define UART_FLAG_RXFF                      USART_ISR_RXFF          /*!< UART RXFIFO Full flag                     */
#define UART_FLAG_TXFE                      USART_ISR_TXFE          /*!< UART TXFIFO Empty flag                    */
#define UART_FLAG_REACK                     USART_ISR_REACK         /*!< UART receive enable acknowledge flag      */
#define UART_FLAG_TEACK                     USART_ISR_TEACK         /*!< UART transmit enable acknowledge flag     */
#define UART_FLAG_WUF                       USART_ISR_WUF           /*!< UART wake-up from stop mode flag          */
#define UART_FLAG_RWU                       USART_ISR_RWU           /*!< UART receiver wake-up from mute mode flag */
#define UART_FLAG_SBKF                      USART_ISR_SBKF          /*!< UART send break flag                      */
#define UART_FLAG_CMF                       USART_ISR_CMF           /*!< UART character match flag                 */
#define UART_FLAG_BUSY                      USART_ISR_BUSY          /*!< UART busy flag                            */
#define UART_FLAG_ABRF                      USART_ISR_ABRF          /*!< UART auto Baud rate flag                  */
#define UART_FLAG_ABRE                      USART_ISR_ABRE          /*!< UART auto Baud rate error                 */
#define UART_FLAG_RTOF                      USART_ISR_RTOF          /*!< UART receiver timeout flag                */
#define UART_FLAG_CTS                       USART_ISR_CTS           /*!< UART clear to send flag                   */
#define UART_FLAG_CTSIF                     USART_ISR_CTSIF         /*!< UART clear to send interrupt flag         */
#define UART_FLAG_LBDF                      USART_ISR_LBDF          /*!< UART LIN break detection flag             */
#define UART_FLAG_TXE                       USART_ISR_TXE_TXFNF     /*!< UART transmit data register empty         */
#define UART_FLAG_TXFNF                     USART_ISR_TXE_TXFNF     /*!< UART TXFIFO not full                      */
#define UART_FLAG_TC                        USART_ISR_TC            /*!< UART transmission complete                */
#define UART_FLAG_RXNE                      USART_ISR_RXNE_RXFNE    /*!< UART read data register not empty         */
#define UART_FLAG_RXFNE                     USART_ISR_RXNE_RXFNE    /*!< UART RXFIFO not empty                     */
#define UART_FLAG_IDLE                      USART_ISR_IDLE          /*!< UART idle flag                            */
#define UART_FLAG_ORE                       USART_ISR_ORE           /*!< UART overrun error                        */
#define UART_FLAG_NE                        USART_ISR_NE            /*!< UART noise error                          */
#define UART_FLAG_FE                        USART_ISR_FE            /*!< UART frame error                          */
#define UART_FLAG_PE                        USART_ISR_PE            /*!< UART parity error                         */
/**
  * @}
  */

/** @defgroup UART_Interrupt_definition   UART Interrupts Definition
  *        Elements values convention: 000ZZZZZ0XXYYYYYb
  *           - YYYYY  : Interrupt source position in the XX register (5bits)
  *           - XX  : Interrupt source register (2bits)
  *                 - 01: CR1 register
  *                 - 10: CR2 register
  *                 - 11: CR3 register
  *           - ZZZZZ  : Flag position in the ISR register(5bits)
  *        Elements values convention: 000000000XXYYYYYb
  *           - YYYYY  : Interrupt source position in the XX register (5bits)
  *           - XX  : Interrupt source register (2bits)
  *                 - 01: CR1 register
  *                 - 10: CR2 register
  *                 - 11: CR3 register
  *        Elements values convention: 0000ZZZZ00000000b
  *           - ZZZZ  : Flag position in the ISR register(4bits)
  * @{
  */
#define UART_IT_PE                          0x0028U              /*!< UART parity error interruption                 */
#define UART_IT_TXE                         0x0727U              /*!< UART transmit data register empty interruption */
#define UART_IT_TXFNF                       0x0727U              /*!< UART TX FIFO not full interruption             */
#define UART_IT_TC                          0x0626U              /*!< UART transmission complete interruption        */
#define UART_IT_RXNE                        0x0525U              /*!< UART read data register not empty interruption */
#define UART_IT_RXFNE                       0x0525U              /*!< UART RXFIFO not empty interruption             */
#define UART_IT_IDLE                        0x0424U              /*!< UART idle interruption                         */
#define UART_IT_LBD                         0x0846U              /*!< UART LIN break detection interruption          */
#define UART_IT_CTS                         0x096AU              /*!< UART CTS interruption                          */
#define UART_IT_CM                          0x112EU              /*!< UART character match interruption              */
#define UART_IT_WUF                         0x1476U              /*!< UART wake-up from stop mode interruption       */
#define UART_IT_RXFF                        0x183FU              /*!< UART RXFIFO full interruption                  */
#define UART_IT_TXFE                        0x173EU              /*!< UART TXFIFO empty interruption                 */
#define UART_IT_RXFT                        0x1A7CU              /*!< UART RXFIFO threshold reached interruption     */
#define UART_IT_TXFT                        0x1B77U              /*!< UART TXFIFO threshold reached interruption     */
#define UART_IT_RTO                         0x0B3AU              /*!< UART receiver timeout interruption             */

#define UART_IT_ERR                         0x0060U              /*!< UART error interruption                        */

#define UART_IT_ORE                         0x0300U              /*!< UART overrun error interruption                */
#define UART_IT_NE                          0x0200U              /*!< UART noise error interruption                  */
#define UART_IT_FE                          0x0100U              /*!< UART frame error interruption                  */
/**
  * @}
  */

/** @defgroup UART_IT_CLEAR_Flags  UART Interruption Clear Flags
  * @{
  */
#define UART_CLEAR_PEF                       USART_ICR_PECF            /*!< Parity Error Clear Flag           */
#define UART_CLEAR_FEF                       USART_ICR_FECF            /*!< Framing Error Clear Flag          */
#define UART_CLEAR_NEF                       USART_ICR_NECF            /*!< Noise Error detected Clear Flag   */
#define UART_CLEAR_OREF                      USART_ICR_ORECF           /*!< Overrun Error Clear Flag          */
#define UART_CLEAR_IDLEF                     USART_ICR_IDLECF          /*!< IDLE line detected Clear Flag     */
#define UART_CLEAR_TXFECF                    USART_ICR_TXFECF          /*!< TXFIFO empty clear flag           */
#define UART_CLEAR_TCF                       USART_ICR_TCCF            /*!< Transmission Complete Clear Flag  */
#define UART_CLEAR_LBDF                      USART_ICR_LBDCF           /*!< LIN Break Detection Clear Flag    */
#define UART_CLEAR_CTSF                      USART_ICR_CTSCF           /*!< CTS Interrupt Clear Flag          */
#define UART_CLEAR_CMF                       USART_ICR_CMCF            /*!< Character Match Clear Flag        */
#define UART_CLEAR_WUF                       USART_ICR_WUCF            /*!< Wake Up from stop mode Clear Flag */
#define UART_CLEAR_RTOF                      USART_ICR_RTOCF           /*!< UART receiver timeout clear flag  */
/**
  * @}
  */

/** @defgroup UART_RECEPTION_TYPE_Values  UART Reception type values
  * @{
  */
#define HAL_UART_RECEPTION_STANDARD          (0x00000000U)             /*!< Standard reception                       */
#define HAL_UART_RECEPTION_TOIDLE            (0x00000001U)             /*!< Reception till completion or IDLE event  */
#define HAL_UART_RECEPTION_TORTO             (0x00000002U)             /*!< Reception till completion or RTO event   */
#define HAL_UART_RECEPTION_TOCHARMATCH       (0x00000003U)             /*!< Reception till completion or CM event    */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup UART_Exported_Macros UART Exported Macros
  * @{
  */

/** @brief  Reset UART handle states.
  * @param  __HANDLE__ UART handle.
  * @retval None
  */
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
#define __HAL_UART_RESET_HANDLE_STATE(__HANDLE__)  do{                                                   \
                                                       (__HANDLE__)->gState = HAL_UART_STATE_RESET;      \
                                                       (__HANDLE__)->RxState = HAL_UART_STATE_RESET;     \
                                                       (__HANDLE__)->MspInitCallback = NULL;             \
                                                       (__HANDLE__)->MspDeInitCallback = NULL;           \
                                                     } while(0U)
#else
#define __HAL_UART_RESET_HANDLE_STATE(__HANDLE__)  do{                                                   \
                                                       (__HANDLE__)->gState = HAL_UART_STATE_RESET;      \
                                                       (__HANDLE__)->RxState = HAL_UART_STATE_RESET;     \
                                                     } while(0U)
#endif /*USE_HAL_UART_REGISTER_CALLBACKS */

/** @brief  Flush the UART Data registers.
  * @param  __HANDLE__ specifies the UART Handle.
  * @retval None
  */
#define __HAL_UART_FLUSH_DRREGISTER(__HANDLE__)  \
  do{                \
    SET_BIT((__HANDLE__)->Instance->RQR, UART_RXDATA_FLUSH_REQUEST); \
    SET_BIT((__HANDLE__)->Instance->RQR, UART_TXDATA_FLUSH_REQUEST); \
  }  while(0U)

/** @brief  Clear the specified UART pending flag.
  * @param  __HANDLE__ specifies the UART Handle.
  * @param  __FLAG__ specifies the flag to check.
  *          This parameter can be any combination of the following values:
  *            @arg @ref UART_CLEAR_PEF      Parity Error Clear Flag
  *            @arg @ref UART_CLEAR_FEF      Framing Error Clear Flag
  *            @arg @ref UART_CLEAR_NEF      Noise detected Clear Flag
  *            @arg @ref UART_CLEAR_OREF     Overrun Error Clear Flag
  *            @arg @ref UART_CLEAR_IDLEF    IDLE line detected Clear Flag
  *            @arg @ref UART_CLEAR_TXFECF   TXFIFO empty clear Flag
  *            @arg @ref UART_CLEAR_TCF      Transmission Complete Clear Flag
  *            @arg @ref UART_CLEAR_RTOF     Receiver Timeout clear flag
  *            @arg @ref UART_CLEAR_LBDF     LIN Break Detection Clear Flag
  *            @arg @ref UART_CLEAR_CTSF     CTS Interrupt Clear Flag
  *            @arg @ref UART_CLEAR_CMF      Character Match Clear Flag
  *            @arg @ref UART_CLEAR_WUF      Wake Up from stop mode Clear Flag
  * @retval None
  */
#define __HAL_UART_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->ICR = (__FLAG__))

/** @brief  Clear the UART PE pending flag.
  * @param  __HANDLE__ specifies the UART Handle.
  * @retval None
  */
#define __HAL_UART_CLEAR_PEFLAG(__HANDLE__)   __HAL_UART_CLEAR_FLAG((__HANDLE__), UART_CLEAR_PEF)

/** @brief  Clear the UART FE pending flag.
  * @param  __HANDLE__ specifies the UART Handle.
  * @retval None
  */
#define __HAL_UART_CLEAR_FEFLAG(__HANDLE__)   __HAL_UART_CLEAR_FLAG((__HANDLE__), UART_CLEAR_FEF)

/** @brief  Clear the UART NE pending flag.
  * @param  __HANDLE__ specifies the UART Handle.
  * @retval None
  */
#define __HAL_UART_CLEAR_NEFLAG(__HANDLE__)  __HAL_UART_CLEAR_FLAG((__HANDLE__), UART_CLEAR_NEF)

/** @brief  Clear the UART ORE pending flag.
  * @param  __HANDLE__ specifies the UART Handle.
  * @retval None
  */
#define __HAL_UART_CLEAR_OREFLAG(__HANDLE__)   __HAL_UART_CLEAR_FLAG((__HANDLE__), UART_CLEAR_OREF)

/** @brief  Clear the UART IDLE pending flag.
  * @param  __HANDLE__ specifies the UART Handle.
  * @retval None
  */
#define __HAL_UART_CLEAR_IDLEFLAG(__HANDLE__)   __HAL_UART_CLEAR_FLAG((__HANDLE__), UART_CLEAR_IDLEF)

/** @brief  Clear the UART TX FIFO empty clear flag.
  * @param  __HANDLE__ specifies the UART Handle.
  * @retval None
  */
#define __HAL_UART_CLEAR_TXFECF(__HANDLE__)   __HAL_UART_CLEAR_FLAG((__HANDLE__), UART_CLEAR_TXFECF)

/** @brief  Check whether the specified UART flag is set or not.
  * @param  __HANDLE__ specifies the UART Handle.
  * @param  __FLAG__ specifies the flag to check.
  *        This parameter can be one of the following values:
  *            @arg @ref UART_FLAG_TXFT  TXFIFO threshold flag
  *            @arg @ref UART_FLAG_RXFT  RXFIFO threshold flag
  *            @arg @ref UART_FLAG_RXFF  RXFIFO Full flag
  *            @arg @ref UART_FLAG_TXFE  TXFIFO Empty flag
  *            @arg @ref UART_FLAG_REACK Receive enable acknowledge flag
  *            @arg @ref UART_FLAG_TEACK Transmit enable acknowledge flag
  *            @arg @ref UART_FLAG_WUF   Wake up from stop mode flag
  *            @arg @ref UART_FLAG_RWU   Receiver wake up flag (if the UART in mute mode)
  *            @arg @ref UART_FLAG_SBKF  Send Break flag
  *            @arg @ref UART_FLAG_CMF   Character match flag
  *            @arg @ref UART_FLAG_BUSY  Busy flag
  *            @arg @ref UART_FLAG_ABRF  Auto Baud rate detection flag
  *            @arg @ref UART_FLAG_ABRE  Auto Baud rate detection error flag
  *            @arg @ref UART_FLAG_CTS   CTS Change flag
  *            @arg @ref UART_FLAG_LBDF  LIN Break detection flag
  *            @arg @ref UART_FLAG_TXE   Transmit data register empty flag
  *            @arg @ref UART_FLAG_TXFNF UART TXFIFO not full flag
  *            @arg @ref UART_FLAG_TC    Transmission Complete flag
  *            @arg @ref UART_FLAG_RXNE  Receive data register not empty flag
  *            @arg @ref UART_FLAG_RXFNE UART RXFIFO not empty flag
  *            @arg @ref UART_FLAG_RTOF  Receiver Timeout flag
  *            @arg @ref UART_FLAG_IDLE  Idle Line detection flag
  *            @arg @ref UART_FLAG_ORE   Overrun Error flag
  *            @arg @ref UART_FLAG_NE    Noise Error flag
  *            @arg @ref UART_FLAG_FE    Framing Error flag
  *            @arg @ref UART_FLAG_PE    Parity Error flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_UART_GET_FLAG(__HANDLE__, __FLAG__) (((__HANDLE__)->Instance->ISR & (__FLAG__)) == (__FLAG__))

/** @brief  Enable the specified UART interrupt.
  * @param  __HANDLE__ specifies the UART Handle.
  * @param  __INTERRUPT__ specifies the UART interrupt source to enable.
  *          This parameter can be one of the following values:
  *            @arg @ref UART_IT_RXFF  RXFIFO Full interrupt
  *            @arg @ref UART_IT_TXFE  TXFIFO Empty interrupt
  *            @arg @ref UART_IT_RXFT  RXFIFO threshold interrupt
  *            @arg @ref UART_IT_TXFT  TXFIFO threshold interrupt
  *            @arg @ref UART_IT_WUF   Wakeup from stop mode interrupt
  *            @arg @ref UART_IT_CM    Character match interrupt
  *            @arg @ref UART_IT_CTS   CTS change interrupt
  *            @arg @ref UART_IT_LBD   LIN Break detection interrupt
  *            @arg @ref UART_IT_TXE   Transmit Data Register empty interrupt
  *            @arg @ref UART_IT_TXFNF TX FIFO not full interrupt
  *            @arg @ref UART_IT_TC    Transmission complete interrupt
  *            @arg @ref UART_IT_RXNE  Receive Data register not empty interrupt
  *            @arg @ref UART_IT_RXFNE RXFIFO not empty interrupt
  *            @arg @ref UART_IT_RTO   Receive Timeout interrupt
  *            @arg @ref UART_IT_IDLE  Idle line detection interrupt
  *            @arg @ref UART_IT_PE    Parity Error interrupt
  *            @arg @ref UART_IT_ERR   Error interrupt (frame error, noise error, overrun error)
  * @retval None
  */
#define __HAL_UART_ENABLE_IT(__HANDLE__, __INTERRUPT__)   (\
                                                           ((((uint8_t)(__INTERRUPT__)) >> 5U) == 1U)?\
                                                           ((__HANDLE__)->Instance->CR1 |= (1U <<\
                                                               ((__INTERRUPT__) & UART_IT_MASK))): \
                                                           ((((uint8_t)(__INTERRUPT__)) >> 5U) == 2U)?\
                                                           ((__HANDLE__)->Instance->CR2 |= (1U <<\
                                                               ((__INTERRUPT__) & UART_IT_MASK))): \
                                                           ((__HANDLE__)->Instance->CR3 |= (1U <<\
                                                               ((__INTERRUPT__) & UART_IT_MASK))))

/** @brief  Disable the specified UART interrupt.
  * @param  __HANDLE__ specifies the UART Handle.
  * @param  __INTERRUPT__ specifies the UART interrupt source to disable.
  *          This parameter can be one of the following values:
  *            @arg @ref UART_IT_RXFF  RXFIFO Full interrupt
  *            @arg @ref UART_IT_TXFE  TXFIFO Empty interrupt
  *            @arg @ref UART_IT_RXFT  RXFIFO threshold interrupt
  *            @arg @ref UART_IT_TXFT  TXFIFO threshold interrupt
  *            @arg @ref UART_IT_WUF   Wakeup from stop mode interrupt
  *            @arg @ref UART_IT_CM    Character match interrupt
  *            @arg @ref UART_IT_CTS   CTS change interrupt
  *            @arg @ref UART_IT_LBD   LIN Break detection interrupt
  *            @arg @ref UART_IT_TXE   Transmit Data Register empty interrupt
  *            @arg @ref UART_IT_TXFNF TX FIFO not full interrupt
  *            @arg @ref UART_IT_TC    Transmission complete interrupt
  *            @arg @ref UART_IT_RXNE  Receive Data register not empty interrupt
  *            @arg @ref UART_IT_RXFNE RXFIFO not empty interrupt
  *            @arg @ref UART_IT_RTO   Receive Timeout interrupt
  *            @arg @ref UART_IT_IDLE  Idle line detection interrupt
  *            @arg @ref UART_IT_PE    Parity Error interrupt
  *            @arg @ref UART_IT_ERR   Error interrupt (Frame error, noise error, overrun error)
  * @retval None
  */
#define __HAL_UART_DISABLE_IT(__HANDLE__, __INTERRUPT__)  (\
                                                           ((((uint8_t)(__INTERRUPT__)) >> 5U) == 1U)?\
                                                           ((__HANDLE__)->Instance->CR1 &= ~ (1U <<\
                                                               ((__INTERRUPT__) & UART_IT_MASK))): \
                                                           ((((uint8_t)(__INTERRUPT__)) >> 5U) == 2U)?\
                                                           ((__HANDLE__)->Instance->CR2 &= ~ (1U <<\
                                                               ((__INTERRUPT__) & UART_IT_MASK))): \
                                                           ((__HANDLE__)->Instance->CR3 &= ~ (1U <<\
                                                               ((__INTERRUPT__) & UART_IT_MASK))))

/** @brief  Check whether the specified UART interrupt has occurred or not.
  * @param  __HANDLE__ specifies the UART Handle.
  * @param  __INTERRUPT__ specifies the UART interrupt to check.
  *          This parameter can be one of the following values:
  *            @arg @ref UART_IT_RXFF  RXFIFO Full interrupt
  *            @arg @ref UART_IT_TXFE  TXFIFO Empty interrupt
  *            @arg @ref UART_IT_RXFT  RXFIFO threshold interrupt
  *            @arg @ref UART_IT_TXFT  TXFIFO threshold interrupt
  *            @arg @ref UART_IT_WUF   Wakeup from stop mode interrupt
  *            @arg @ref UART_IT_CM    Character match interrupt
  *            @arg @ref UART_IT_CTS   CTS change interrupt
  *            @arg @ref UART_IT_LBD   LIN Break detection interrupt
  *            @arg @ref UART_IT_TXE   Transmit Data Register empty interrupt
  *            @arg @ref UART_IT_TXFNF TX FIFO not full interrupt
  *            @arg @ref UART_IT_TC    Transmission complete interrupt
  *            @arg @ref UART_IT_RXNE  Receive Data register not empty interrupt
  *            @arg @ref UART_IT_RXFNE RXFIFO not empty interrupt
  *            @arg @ref UART_IT_RTO   Receive Timeout interrupt
  *            @arg @ref UART_IT_IDLE  Idle line detection interrupt
  *            @arg @ref UART_IT_PE    Parity Error interrupt
  *            @arg @ref UART_IT_ERR   Error interrupt (Frame error, noise error, overrun error)
  * @retval The new state of __INTERRUPT__ (SET or RESET).
  */
#define __HAL_UART_GET_IT(__HANDLE__, __INTERRUPT__) ((((__HANDLE__)->Instance->ISR\
                                                        & (1U << ((__INTERRUPT__)>> 8U))) != RESET) ? SET : RESET)

/** @brief  Check whether the specified UART interrupt source is enabled or not.
  * @param  __HANDLE__ specifies the UART Handle.
  * @param  __INTERRUPT__ specifies the UART interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg @ref UART_IT_RXFF  RXFIFO Full interrupt
  *            @arg @ref UART_IT_TXFE  TXFIFO Empty interrupt
  *            @arg @ref UART_IT_RXFT  RXFIFO threshold interrupt
  *            @arg @ref UART_IT_TXFT  TXFIFO threshold interrupt
  *            @arg @ref UART_IT_WUF   Wakeup from stop mode interrupt
  *            @arg @ref UART_IT_CM    Character match interrupt
  *            @arg @ref UART_IT_CTS   CTS change interrupt
  *            @arg @ref UART_IT_LBD   LIN Break detection interrupt
  *            @arg @ref UART_IT_TXE   Transmit Data Register empty interrupt
  *            @arg @ref UART_IT_TXFNF TX FIFO not full interrupt
  *            @arg @ref UART_IT_TC    Transmission complete interrupt
  *            @arg @ref UART_IT_RXNE  Receive Data register not empty interrupt
  *            @arg @ref UART_IT_RXFNE RXFIFO not empty interrupt
  *            @arg @ref UART_IT_RTO   Receive Timeout interrupt
  *            @arg @ref UART_IT_IDLE  Idle line detection interrupt
  *            @arg @ref UART_IT_PE    Parity Error interrupt
  *            @arg @ref UART_IT_ERR   Error interrupt (Frame error, noise error, overrun error)
  * @retval The new state of __INTERRUPT__ (SET or RESET).
  */
#define __HAL_UART_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((((((((uint8_t)(__INTERRUPT__)) >> 5U) == 1U) ?\
                                                                (__HANDLE__)->Instance->CR1 : \
                                                                (((((uint8_t)(__INTERRUPT__)) >> 5U) == 2U) ?\
                                                                 (__HANDLE__)->Instance->CR2 : \
                                                                 (__HANDLE__)->Instance->CR3)) & (1U <<\
                                                                     (((uint16_t)(__INTERRUPT__)) &\
                                                                      UART_IT_MASK)))  != RESET) ? SET : RESET)

/** @brief  Clear the specified UART ISR flag, in setting the proper ICR register flag.
  * @param  __HANDLE__ specifies the UART Handle.
  * @param  __IT_CLEAR__ specifies the interrupt clear register flag that needs to be set
  *                       to clear the corresponding interrupt
  *          This parameter can be one of the following values:
  *            @arg @ref UART_CLEAR_PEF    Parity Error Clear Flag
  *            @arg @ref UART_CLEAR_FEF    Framing Error Clear Flag
  *            @arg @ref UART_CLEAR_NEF    Noise detected Clear Flag
  *            @arg @ref UART_CLEAR_OREF   Overrun Error Clear Flag
  *            @arg @ref UART_CLEAR_IDLEF  IDLE line detected Clear Flag
  *            @arg @ref UART_CLEAR_RTOF   Receiver timeout clear flag
  *            @arg @ref UART_CLEAR_TXFECF TXFIFO empty Clear Flag
  *            @arg @ref UART_CLEAR_TCF    Transmission Complete Clear Flag
  *            @arg @ref UART_CLEAR_LBDF   LIN Break Detection Clear Flag
  *            @arg @ref UART_CLEAR_CTSF   CTS Interrupt Clear Flag
  *            @arg @ref UART_CLEAR_CMF    Character Match Clear Flag
  *            @arg @ref UART_CLEAR_WUF    Wake Up from stop mode Clear Flag
  * @retval None
  */
#define __HAL_UART_CLEAR_IT(__HANDLE__, __IT_CLEAR__) ((__HANDLE__)->Instance->ICR = (uint32_t)(__IT_CLEAR__))

/** @brief  Set a specific UART request flag.
  * @param  __HANDLE__ specifies the UART Handle.
  * @param  __REQ__ specifies the request flag to set
  *          This parameter can be one of the following values:
  *            @arg @ref UART_AUTOBAUD_REQUEST Auto-Baud Rate Request
  *            @arg @ref UART_SENDBREAK_REQUEST Send Break Request
  *            @arg @ref UART_MUTE_MODE_REQUEST Mute Mode Request
  *            @arg @ref UART_RXDATA_FLUSH_REQUEST Receive Data flush Request
  *            @arg @ref UART_TXDATA_FLUSH_REQUEST Transmit data flush Request
  * @retval None
  */
#define __HAL_UART_SEND_REQ(__HANDLE__, __REQ__) ((__HANDLE__)->Instance->RQR |= (uint16_t)(__REQ__))

/** @brief  Enable the UART one bit sample method.
  * @param  __HANDLE__ specifies the UART Handle.
  * @retval None
  */
#define __HAL_UART_ONE_BIT_SAMPLE_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->CR3|= USART_CR3_ONEBIT)

/** @brief  Disable the UART one bit sample method.
  * @param  __HANDLE__ specifies the UART Handle.
  * @retval None
  */
#define __HAL_UART_ONE_BIT_SAMPLE_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->CR3 &= ~USART_CR3_ONEBIT)

/** @brief  Enable UART.
  * @param  __HANDLE__ specifies the UART Handle.
  * @retval None
  */
#define __HAL_UART_ENABLE(__HANDLE__)                   ((__HANDLE__)->Instance->CR1 |= USART_CR1_UE)

/** @brief  Disable UART.
  * @param  __HANDLE__ specifies the UART Handle.
  * @retval None
  */
#define __HAL_UART_DISABLE(__HANDLE__)                  ((__HANDLE__)->Instance->CR1 &= ~USART_CR1_UE)

/** @brief  Enable CTS flow control.
  * @note   This macro allows to enable CTS hardware flow control for a given UART instance,
  *         without need to call HAL_UART_Init() function.
  *         As involving direct access to UART registers, usage of this macro should be fully endorsed by user.
  * @note   As macro is expected to be used for modifying CTS Hw flow control feature activation, without need
  *         for USART instance Deinit/Init, following conditions for macro call should be fulfilled :
  *           - UART instance should have already been initialised (through call of HAL_UART_Init() )
  *           - macro could only be called when corresponding UART instance is disabled
  *             (i.e. __HAL_UART_DISABLE(__HANDLE__)) and should be followed by an Enable
  *              macro (i.e. __HAL_UART_ENABLE(__HANDLE__)).
  * @param  __HANDLE__ specifies the UART Handle.
  * @retval None
  */
#define __HAL_UART_HWCONTROL_CTS_ENABLE(__HANDLE__)        \
  do{                                                      \
    SET_BIT((__HANDLE__)->Instance->CR3, USART_CR3_CTSE);  \
    (__HANDLE__)->Init.HwFlowCtl |= USART_CR3_CTSE;        \
  } while(0U)

/** @brief  Disable CTS flow control.
  * @note   This macro allows to disable CTS hardware flow control for a given UART instance,
  *         without need to call HAL_UART_Init() function.
  *         As involving direct access to UART registers, usage of this macro should be fully endorsed by user.
  * @note   As macro is expected to be used for modifying CTS Hw flow control feature activation, without need
  *         for USART instance Deinit/Init, following conditions for macro call should be fulfilled :
  *           - UART instance should have already been initialised (through call of HAL_UART_Init() )
  *           - macro could only be called when corresponding UART instance is disabled
  *             (i.e. __HAL_UART_DISABLE(__HANDLE__)) and should be followed by an Enable
  *              macro (i.e. __HAL_UART_ENABLE(__HANDLE__)).
  * @param  __HANDLE__ specifies the UART Handle.
  * @retval None
  */
#define __HAL_UART_HWCONTROL_CTS_DISABLE(__HANDLE__)        \
  do{                                                       \
    CLEAR_BIT((__HANDLE__)->Instance->CR3, USART_CR3_CTSE); \
    (__HANDLE__)->Init.HwFlowCtl &= ~(USART_CR3_CTSE);      \
  } while(0U)

/** @brief  Enable RTS flow control.
  * @note   This macro allows to enable RTS hardware flow control for a given UART instance,
  *         without need to call HAL_UART_Init() function.
  *         As involving direct access to UART registers, usage of this macro should be fully endorsed by user.
  * @note   As macro is expected to be used for modifying RTS Hw flow control feature activation, without need
  *         for USART instance Deinit/Init, following conditions for macro call should be fulfilled :
  *           - UART instance should have already been initialised (through call of HAL_UART_Init() )
  *           - macro could only be called when corresponding UART instance is disabled
  *             (i.e. __HAL_UART_DISABLE(__HANDLE__)) and should be followed by an Enable
  *              macro (i.e. __HAL_UART_ENABLE(__HANDLE__)).
  * @param  __HANDLE__ specifies the UART Handle.
  * @retval None
  */
#define __HAL_UART_HWCONTROL_RTS_ENABLE(__HANDLE__)       \
  do{                                                     \
    SET_BIT((__HANDLE__)->Instance->CR3, USART_CR3_RTSE); \
    (__HANDLE__)->Init.HwFlowCtl |= USART_CR3_RTSE;       \
  } while(0U)

/** @brief  Disable RTS flow control.
  * @note   This macro allows to disable RTS hardware flow control for a given UART instance,
  *         without need to call HAL_UART_Init() function.
  *         As involving direct access to UART registers, usage of this macro should be fully endorsed by user.
  * @note   As macro is expected to be used for modifying RTS Hw flow control feature activation, without need
  *         for USART instance Deinit/Init, following conditions for macro call should be fulfilled :
  *           - UART instance should have already been initialised (through call of HAL_UART_Init() )
  *           - macro could only be called when corresponding UART instance is disabled
  *             (i.e. __HAL_UART_DISABLE(__HANDLE__)) and should be followed by an Enable
  *              macro (i.e. __HAL_UART_ENABLE(__HANDLE__)).
  * @param  __HANDLE__ specifies the UART Handle.
  * @retval None
  */
#define __HAL_UART_HWCONTROL_RTS_DISABLE(__HANDLE__)       \
  do{                                                      \
    CLEAR_BIT((__HANDLE__)->Instance->CR3, USART_CR3_RTSE);\
    (__HANDLE__)->Init.HwFlowCtl &= ~(USART_CR3_RTSE);     \
  } while(0U)
/**
  * @}
  */

/* Private macros --------------------------------------------------------*/
/** @defgroup UART_Private_Macros   UART Private Macros
  * @{
  */
/** @brief  Get UART clok division factor from clock prescaler value.
  * @param  __CLOCKPRESCALER__ UART prescaler value.
  * @retval UART clock division factor
  */
#define UART_GET_DIV_FACTOR(__CLOCKPRESCALER__) \
  (((__CLOCKPRESCALER__) == UART_PRESCALER_DIV1)   ? 1U :       \
   ((__CLOCKPRESCALER__) == UART_PRESCALER_DIV2)   ? 2U :       \
   ((__CLOCKPRESCALER__) == UART_PRESCALER_DIV4)   ? 4U :       \
   ((__CLOCKPRESCALER__) == UART_PRESCALER_DIV6)   ? 6U :       \
   ((__CLOCKPRESCALER__) == UART_PRESCALER_DIV8)   ? 8U :       \
   ((__CLOCKPRESCALER__) == UART_PRESCALER_DIV10)  ? 10U :      \
   ((__CLOCKPRESCALER__) == UART_PRESCALER_DIV12)  ? 12U :      \
   ((__CLOCKPRESCALER__) == UART_PRESCALER_DIV16)  ? 16U :      \
   ((__CLOCKPRESCALER__) == UART_PRESCALER_DIV32)  ? 32U :      \
   ((__CLOCKPRESCALER__) == UART_PRESCALER_DIV64)  ? 64U :      \
   ((__CLOCKPRESCALER__) == UART_PRESCALER_DIV128) ? 128U :     \
   ((__CLOCKPRESCALER__) == UART_PRESCALER_DIV256) ? 256U : 1U)

/** @brief  BRR division operation to set BRR register with LPUART.
  * @param  __PCLK__ LPUART clock.
  * @param  __BAUD__ Baud rate set by the user.
  * @param  __CLOCKPRESCALER__ UART prescaler value.
  * @retval Division result
  */
#define UART_DIV_LPUART(__PCLK__, __BAUD__, __CLOCKPRESCALER__)                        \
  ((uint32_t)((((((uint64_t)(__PCLK__))/(UARTPrescTable[(__CLOCKPRESCALER__)]))*256U)+ \
               (uint32_t)((__BAUD__)/2U)) / (__BAUD__))                                \
  )

/** @brief  BRR division operation to set BRR register in 8-bit oversampling mode.
  * @param  __PCLK__ UART clock.
  * @param  __BAUD__ Baud rate set by the user.
  * @param  __CLOCKPRESCALER__ UART prescaler value.
  * @retval Division result
  */
#define UART_DIV_SAMPLING8(__PCLK__, __BAUD__, __CLOCKPRESCALER__)                        \
  (((((__PCLK__)/UARTPrescTable[(__CLOCKPRESCALER__)])*2U) + ((__BAUD__)/2U)) / (__BAUD__))

/** @brief  BRR division operation to set BRR register in 16-bit oversampling mode.
  * @param  __PCLK__ UART clock.
  * @param  __BAUD__ Baud rate set by the user.
  * @param  __CLOCKPRESCALER__ UART prescaler value.
  * @retval Division result
  */
#define UART_DIV_SAMPLING16(__PCLK__, __BAUD__, __CLOCKPRESCALER__)                       \
  ((((__PCLK__)/UARTPrescTable[(__CLOCKPRESCALER__)]) + ((__BAUD__)/2U)) / (__BAUD__))

/** @brief  Check whether or not UART instance is Low Power UART.
  * @param  __HANDLE__ specifies the UART Handle.
  * @retval SET (instance is LPUART) or RESET (instance isn't LPUART)
  */
#define UART_INSTANCE_LOWPOWER(__HANDLE__) (IS_LPUART_INSTANCE((__HANDLE__)->Instance))

/** @brief  Check UART Baud rate.
  * @param  __BAUDRATE__ Baudrate specified by the user.
  *         The maximum Baud Rate is derived from the maximum clock on G0 (i.e. 64 MHz)
  *         divided by the smallest oversampling used on the USART (i.e. 8)
  * @retval SET (__BAUDRATE__ is valid) or RESET (__BAUDRATE__ is invalid)
  */
#define IS_UART_BAUDRATE(__BAUDRATE__) ((__BAUDRATE__) < 8000001U)

/** @brief  Check UART assertion time.
  * @param  __TIME__ 5-bit value assertion time.
  * @retval Test result (TRUE or FALSE).
  */
#define IS_UART_ASSERTIONTIME(__TIME__)    ((__TIME__) <= 0x1FU)

/** @brief  Check UART deassertion time.
  * @param  __TIME__ 5-bit value deassertion time.
  * @retval Test result (TRUE or FALSE).
  */
#define IS_UART_DEASSERTIONTIME(__TIME__) ((__TIME__) <= 0x1FU)

/**
  * @brief Ensure that UART frame number of stop bits is valid.
  * @param __STOPBITS__ UART frame number of stop bits.
  * @retval SET (__STOPBITS__ is valid) or RESET (__STOPBITS__ is invalid)
  */
#define IS_UART_STOPBITS(__STOPBITS__) (((__STOPBITS__) == UART_STOPBITS_0_5) || \
                                        ((__STOPBITS__) == UART_STOPBITS_1)   || \
                                        ((__STOPBITS__) == UART_STOPBITS_1_5) || \
                                        ((__STOPBITS__) == UART_STOPBITS_2))

/**
  * @brief Ensure that LPUART frame number of stop bits is valid.
  * @param __STOPBITS__ LPUART frame number of stop bits.
  * @retval SET (__STOPBITS__ is valid) or RESET (__STOPBITS__ is invalid)
  */
#define IS_LPUART_STOPBITS(__STOPBITS__) (((__STOPBITS__) == UART_STOPBITS_1) || \
                                          ((__STOPBITS__) == UART_STOPBITS_2))

/**
  * @brief Ensure that UART frame parity is valid.
  * @param __PARITY__ UART frame parity.
  * @retval SET (__PARITY__ is valid) or RESET (__PARITY__ is invalid)
  */
#define IS_UART_PARITY(__PARITY__) (((__PARITY__) == UART_PARITY_NONE) || \
                                    ((__PARITY__) == UART_PARITY_EVEN) || \
                                    ((__PARITY__) == UART_PARITY_ODD))

/**
  * @brief Ensure that UART hardware flow control is valid.
  * @param __CONTROL__ UART hardware flow control.
  * @retval SET (__CONTROL__ is valid) or RESET (__CONTROL__ is invalid)
  */
#define IS_UART_HARDWARE_FLOW_CONTROL(__CONTROL__)\
  (((__CONTROL__) == UART_HWCONTROL_NONE) || \
   ((__CONTROL__) == UART_HWCONTROL_RTS)  || \
   ((__CONTROL__) == UART_HWCONTROL_CTS)  || \
   ((__CONTROL__) == UART_HWCONTROL_RTS_CTS))

/**
  * @brief Ensure that UART communication mode is valid.
  * @param __MODE__ UART communication mode.
  * @retval SET (__MODE__ is valid) or RESET (__MODE__ is invalid)
  */
#define IS_UART_MODE(__MODE__) ((((__MODE__) & (~((uint32_t)(UART_MODE_TX_RX)))) == 0x00U) && ((__MODE__) != 0x00U))

/**
  * @brief Ensure that UART state is valid.
  * @param __STATE__ UART state.
  * @retval SET (__STATE__ is valid) or RESET (__STATE__ is invalid)
  */
#define IS_UART_STATE(__STATE__) (((__STATE__) == UART_STATE_DISABLE) || \
                                  ((__STATE__) == UART_STATE_ENABLE))

/**
  * @brief Ensure that UART oversampling is valid.
  * @param __SAMPLING__ UART oversampling.
  * @retval SET (__SAMPLING__ is valid) or RESET (__SAMPLING__ is invalid)
  */
#define IS_UART_OVERSAMPLING(__SAMPLING__) (((__SAMPLING__) == UART_OVERSAMPLING_16) || \
                                            ((__SAMPLING__) == UART_OVERSAMPLING_8))

/**
  * @brief Ensure that UART frame sampling is valid.
  * @param __ONEBIT__ UART frame sampling.
  * @retval SET (__ONEBIT__ is valid) or RESET (__ONEBIT__ is invalid)
  */
#define IS_UART_ONE_BIT_SAMPLE(__ONEBIT__) (((__ONEBIT__) == UART_ONE_BIT_SAMPLE_DISABLE) || \
                                            ((__ONEBIT__) == UART_ONE_BIT_SAMPLE_ENABLE))

/**
  * @brief Ensure that UART auto Baud rate detection mode is valid.
  * @param __MODE__ UART auto Baud rate detection mode.
  * @retval SET (__MODE__ is valid) or RESET (__MODE__ is invalid)
  */
#define IS_UART_ADVFEATURE_AUTOBAUDRATEMODE(__MODE__)  (((__MODE__) == UART_ADVFEATURE_AUTOBAUDRATE_ONSTARTBIT)    || \
                                                        ((__MODE__) == UART_ADVFEATURE_AUTOBAUDRATE_ONFALLINGEDGE) || \
                                                        ((__MODE__) == UART_ADVFEATURE_AUTOBAUDRATE_ON0X7FFRAME)   || \
                                                        ((__MODE__) == UART_ADVFEATURE_AUTOBAUDRATE_ON0X55FRAME))

/**
  * @brief Ensure that UART receiver timeout setting is valid.
  * @param __TIMEOUT__ UART receiver timeout setting.
  * @retval SET (__TIMEOUT__ is valid) or RESET (__TIMEOUT__ is invalid)
  */
#define IS_UART_RECEIVER_TIMEOUT(__TIMEOUT__)  (((__TIMEOUT__) == UART_RECEIVER_TIMEOUT_DISABLE) || \
                                                ((__TIMEOUT__) == UART_RECEIVER_TIMEOUT_ENABLE))

/** @brief  Check the receiver timeout value.
  * @note   The maximum UART receiver timeout value is 0xFFFFFF.
  * @param  __TIMEOUTVALUE__ receiver timeout value.
  * @retval Test result (TRUE or FALSE)
  */
#define IS_UART_RECEIVER_TIMEOUT_VALUE(__TIMEOUTVALUE__)  ((__TIMEOUTVALUE__) <= 0xFFFFFFU)

/**
  * @brief Ensure that UART LIN state is valid.
  * @param __LIN__ UART LIN state.
  * @retval SET (__LIN__ is valid) or RESET (__LIN__ is invalid)
  */
#define IS_UART_LIN(__LIN__)        (((__LIN__) == UART_LIN_DISABLE) || \
                                     ((__LIN__) == UART_LIN_ENABLE))

/**
  * @brief Ensure that UART LIN break detection length is valid.
  * @param __LENGTH__ UART LIN break detection length.
  * @retval SET (__LENGTH__ is valid) or RESET (__LENGTH__ is invalid)
  */
#define IS_UART_LIN_BREAK_DETECT_LENGTH(__LENGTH__) (((__LENGTH__) == UART_LINBREAKDETECTLENGTH_10B) || \
                                                     ((__LENGTH__) == UART_LINBREAKDETECTLENGTH_11B))

/**
  * @brief Ensure that UART DMA TX state is valid.
  * @param __DMATX__ UART DMA TX state.
  * @retval SET (__DMATX__ is valid) or RESET (__DMATX__ is invalid)
  */
#define IS_UART_DMA_TX(__DMATX__)     (((__DMATX__) == UART_DMA_TX_DISABLE) || \
                                       ((__DMATX__) == UART_DMA_TX_ENABLE))

/**
  * @brief Ensure that UART DMA RX state is valid.
  * @param __DMARX__ UART DMA RX state.
  * @retval SET (__DMARX__ is valid) or RESET (__DMARX__ is invalid)
  */
#define IS_UART_DMA_RX(__DMARX__)     (((__DMARX__) == UART_DMA_RX_DISABLE) || \
                                       ((__DMARX__) == UART_DMA_RX_ENABLE))

/**
  * @brief Ensure that UART half-duplex state is valid.
  * @param __HDSEL__ UART half-duplex state.
  * @retval SET (__HDSEL__ is valid) or RESET (__HDSEL__ is invalid)
  */
#define IS_UART_HALF_DUPLEX(__HDSEL__)     (((__HDSEL__) == UART_HALF_DUPLEX_DISABLE) || \
                                            ((__HDSEL__) == UART_HALF_DUPLEX_ENABLE))

/**
  * @brief Ensure that UART wake-up method is valid.
  * @param __WAKEUP__ UART wake-up method .
  * @retval SET (__WAKEUP__ is valid) or RESET (__WAKEUP__ is invalid)
  */
#define IS_UART_WAKEUPMETHOD(__WAKEUP__) (((__WAKEUP__) == UART_WAKEUPMETHOD_IDLELINE) || \
                                          ((__WAKEUP__) == UART_WAKEUPMETHOD_ADDRESSMARK))

/**
  * @brief Ensure that UART request parameter is valid.
  * @param __PARAM__ UART request parameter.
  * @retval SET (__PARAM__ is valid) or RESET (__PARAM__ is invalid)
  */
#define IS_UART_REQUEST_PARAMETER(__PARAM__) (((__PARAM__) == UART_AUTOBAUD_REQUEST)     || \
                                              ((__PARAM__) == UART_SENDBREAK_REQUEST)    || \
                                              ((__PARAM__) == UART_MUTE_MODE_REQUEST)    || \
                                              ((__PARAM__) == UART_RXDATA_FLUSH_REQUEST) || \
                                              ((__PARAM__) == UART_TXDATA_FLUSH_REQUEST))

/**
  * @brief Ensure that UART advanced features initialization is valid.
  * @param __INIT__ UART advanced features initialization.
  * @retval SET (__INIT__ is valid) or RESET (__INIT__ is invalid)
  */
#define IS_UART_ADVFEATURE_INIT(__INIT__)   ((__INIT__) <= (UART_ADVFEATURE_NO_INIT                | \
                                                            UART_ADVFEATURE_TXINVERT_INIT          | \
                                                            UART_ADVFEATURE_RXINVERT_INIT          | \
                                                            UART_ADVFEATURE_DATAINVERT_INIT        | \
                                                            UART_ADVFEATURE_SWAP_INIT              | \
                                                            UART_ADVFEATURE_RXOVERRUNDISABLE_INIT  | \
                                                            UART_ADVFEATURE_DMADISABLEONERROR_INIT | \
                                                            UART_ADVFEATURE_AUTOBAUDRATE_INIT      | \
                                                            UART_ADVFEATURE_MSBFIRST_INIT))

/**
  * @brief Ensure that UART frame TX inversion setting is valid.
  * @param __TXINV__ UART frame TX inversion setting.
  * @retval SET (__TXINV__ is valid) or RESET (__TXINV__ is invalid)
  */
#define IS_UART_ADVFEATURE_TXINV(__TXINV__) (((__TXINV__) == UART_ADVFEATURE_TXINV_DISABLE) || \
                                             ((__TXINV__) == UART_ADVFEATURE_TXINV_ENABLE))

/**
  * @brief Ensure that UART frame RX inversion setting is valid.
  * @param __RXINV__ UART frame RX inversion setting.
  * @retval SET (__RXINV__ is valid) or RESET (__RXINV__ is invalid)
  */
#define IS_UART_ADVFEATURE_RXINV(__RXINV__) (((__RXINV__) == UART_ADVFEATURE_RXINV_DISABLE) || \
                                             ((__RXINV__) == UART_ADVFEATURE_RXINV_ENABLE))

/**
  * @brief Ensure that UART frame data inversion setting is valid.
  * @param __DATAINV__ UART frame data inversion setting.
  * @retval SET (__DATAINV__ is valid) or RESET (__DATAINV__ is invalid)
  */
#define IS_UART_ADVFEATURE_DATAINV(__DATAINV__) (((__DATAINV__) == UART_ADVFEATURE_DATAINV_DISABLE) || \
                                                 ((__DATAINV__) == UART_ADVFEATURE_DATAINV_ENABLE))

/**
  * @brief Ensure that UART frame RX/TX pins swap setting is valid.
  * @param __SWAP__ UART frame RX/TX pins swap setting.
  * @retval SET (__SWAP__ is valid) or RESET (__SWAP__ is invalid)
  */
#define IS_UART_ADVFEATURE_SWAP(__SWAP__) (((__SWAP__) == UART_ADVFEATURE_SWAP_DISABLE) || \
                                           ((__SWAP__) == UART_ADVFEATURE_SWAP_ENABLE))

/**
  * @brief Ensure that UART frame overrun setting is valid.
  * @param __OVERRUN__ UART frame overrun setting.
  * @retval SET (__OVERRUN__ is valid) or RESET (__OVERRUN__ is invalid)
  */
#define IS_UART_OVERRUN(__OVERRUN__)     (((__OVERRUN__) == UART_ADVFEATURE_OVERRUN_ENABLE) || \
                                          ((__OVERRUN__) == UART_ADVFEATURE_OVERRUN_DISABLE))

/**
  * @brief Ensure that UART auto Baud rate state is valid.
  * @param __AUTOBAUDRATE__ UART auto Baud rate state.
  * @retval SET (__AUTOBAUDRATE__ is valid) or RESET (__AUTOBAUDRATE__ is invalid)
  */
#define IS_UART_ADVFEATURE_AUTOBAUDRATE(__AUTOBAUDRATE__) (((__AUTOBAUDRATE__) == \
                                                            UART_ADVFEATURE_AUTOBAUDRATE_DISABLE) || \
                                                           ((__AUTOBAUDRATE__) == UART_ADVFEATURE_AUTOBAUDRATE_ENABLE))

/**
  * @brief Ensure that UART DMA enabling or disabling on error setting is valid.
  * @param __DMA__ UART DMA enabling or disabling on error setting.
  * @retval SET (__DMA__ is valid) or RESET (__DMA__ is invalid)
  */
#define IS_UART_ADVFEATURE_DMAONRXERROR(__DMA__)  (((__DMA__) == UART_ADVFEATURE_DMA_ENABLEONRXERROR) || \
                                                   ((__DMA__) == UART_ADVFEATURE_DMA_DISABLEONRXERROR))

/**
  * @brief Ensure that UART frame MSB first setting is valid.
  * @param __MSBFIRST__ UART frame MSB first setting.
  * @retval SET (__MSBFIRST__ is valid) or RESET (__MSBFIRST__ is invalid)
  */
#define IS_UART_ADVFEATURE_MSBFIRST(__MSBFIRST__) (((__MSBFIRST__) == UART_ADVFEATURE_MSBFIRST_DISABLE) || \
                                                   ((__MSBFIRST__) == UART_ADVFEATURE_MSBFIRST_ENABLE))

/**
  * @brief Ensure that UART stop mode state is valid.
  * @param __STOPMODE__ UART stop mode state.
  * @retval SET (__STOPMODE__ is valid) or RESET (__STOPMODE__ is invalid)
  */
#define IS_UART_ADVFEATURE_STOPMODE(__STOPMODE__) (((__STOPMODE__) == UART_ADVFEATURE_STOPMODE_DISABLE) || \
                                                   ((__STOPMODE__) == UART_ADVFEATURE_STOPMODE_ENABLE))

/**
  * @brief Ensure that UART mute mode state is valid.
  * @param __MUTE__ UART mute mode state.
  * @retval SET (__MUTE__ is valid) or RESET (__MUTE__ is invalid)
  */
#define IS_UART_MUTE_MODE(__MUTE__)       (((__MUTE__) == UART_ADVFEATURE_MUTEMODE_DISABLE) || \
                                           ((__MUTE__) == UART_ADVFEATURE_MUTEMODE_ENABLE))

/**
  * @brief Ensure that UART wake-up selection is valid.
  * @param __WAKE__ UART wake-up selection.
  * @retval SET (__WAKE__ is valid) or RESET (__WAKE__ is invalid)
  */
#define IS_UART_WAKEUP_SELECTION(__WAKE__) (((__WAKE__) == UART_WAKEUP_ON_ADDRESS)           || \
                                            ((__WAKE__) == UART_WAKEUP_ON_STARTBIT)          || \
                                            ((__WAKE__) == UART_WAKEUP_ON_READDATA_NONEMPTY))

/**
  * @brief Ensure that UART driver enable polarity is valid.
  * @param __POLARITY__ UART driver enable polarity.
  * @retval SET (__POLARITY__ is valid) or RESET (__POLARITY__ is invalid)
  */
#define IS_UART_DE_POLARITY(__POLARITY__)    (((__POLARITY__) == UART_DE_POLARITY_HIGH) || \
                                              ((__POLARITY__) == UART_DE_POLARITY_LOW))

/**
  * @brief Ensure that UART Prescaler is valid.
  * @param __CLOCKPRESCALER__ UART Prescaler value.
  * @retval SET (__CLOCKPRESCALER__ is valid) or RESET (__CLOCKPRESCALER__ is invalid)
  */
#define IS_UART_PRESCALER(__CLOCKPRESCALER__) (((__CLOCKPRESCALER__) == UART_PRESCALER_DIV1)   || \
                                               ((__CLOCKPRESCALER__) == UART_PRESCALER_DIV2)   || \
                                               ((__CLOCKPRESCALER__) == UART_PRESCALER_DIV4)   || \
                                               ((__CLOCKPRESCALER__) == UART_PRESCALER_DIV6)   || \
                                               ((__CLOCKPRESCALER__) == UART_PRESCALER_DIV8)   || \
                                               ((__CLOCKPRESCALER__) == UART_PRESCALER_DIV10)  || \
                                               ((__CLOCKPRESCALER__) == UART_PRESCALER_DIV12)  || \
                                               ((__CLOCKPRESCALER__) == UART_PRESCALER_DIV16)  || \
                                               ((__CLOCKPRESCALER__) == UART_PRESCALER_DIV32)  || \
                                               ((__CLOCKPRESCALER__) == UART_PRESCALER_DIV64)  || \
                                               ((__CLOCKPRESCALER__) == UART_PRESCALER_DIV128) || \
                                               ((__CLOCKPRESCALER__) == UART_PRESCALER_DIV256))

/**
  * @}
  */

/* Include UART HAL Extended module */
#include "stm32g0xx_hal_uart_ex.h"


/* Prescaler Table used in BRR computation macros.
   Declared as extern here to allow use of private UART macros, outside of HAL UART functions */
extern const uint16_t UARTPrescTable[12];


/* Exported functions --------------------------------------------------------*/
/** @addtogroup UART_Exported_Functions UART Exported Functions
  * @{
  */

/** @addtogroup UART_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */

/* Initialization and de-initialization functions  ****************************/
HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_HalfDuplex_Init(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_LIN_Init(UART_HandleTypeDef *huart, uint32_t BreakDetectLength);
HAL_StatusTypeDef HAL_MultiProcessor_Init(UART_HandleTypeDef *huart, uint8_t Address, uint32_t WakeUpMethod);
HAL_StatusTypeDef HAL_UART_DeInit(UART_HandleTypeDef *huart);
void HAL_UART_MspInit(UART_HandleTypeDef *huart);
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart);

/* Callbacks Register/UnRegister functions  ***********************************/
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
HAL_StatusTypeDef HAL_UART_RegisterCallback(UART_HandleTypeDef *huart, HAL_UART_CallbackIDTypeDef CallbackID,
                                            pUART_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_UART_UnRegisterCallback(UART_HandleTypeDef *huart, HAL_UART_CallbackIDTypeDef CallbackID);

HAL_StatusTypeDef HAL_UART_RegisterRxEventCallback(UART_HandleTypeDef *huart, pUART_RxEventCallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_UART_UnRegisterRxEventCallback(UART_HandleTypeDef *huart);
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @addtogroup UART_Exported_Functions_Group2 IO operation functions
  * @{
  */

/* IO operation functions *****************************************************/
HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_DMAPause(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DMAResume(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DMAStop(UART_HandleTypeDef *huart);
/* Transfer Abort functions */
HAL_StatusTypeDef HAL_UART_Abort(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortTransmit(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortReceive(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_Abort_IT(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortTransmit_IT(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortReceive_IT(UART_HandleTypeDef *huart);

void HAL_UART_IRQHandler(UART_HandleTypeDef *huart);
void HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart);
void HAL_UART_AbortCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_AbortTransmitCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_AbortReceiveCpltCallback(UART_HandleTypeDef *huart);

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);

/**
  * @}
  */

/** @addtogroup UART_Exported_Functions_Group3 Peripheral Control functions
  * @{
  */

/* Peripheral Control functions  ************************************************/
void HAL_UART_ReceiverTimeout_Config(UART_HandleTypeDef *huart, uint32_t TimeoutValue);
HAL_StatusTypeDef HAL_UART_EnableReceiverTimeout(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DisableReceiverTimeout(UART_HandleTypeDef *huart);

HAL_StatusTypeDef HAL_LIN_SendBreak(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_MultiProcessor_EnableMuteMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_MultiProcessor_DisableMuteMode(UART_HandleTypeDef *huart);
void HAL_MultiProcessor_EnterMuteMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_HalfDuplex_EnableTransmitter(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_HalfDuplex_EnableReceiver(UART_HandleTypeDef *huart);

/**
  * @}
  */

/** @addtogroup UART_Exported_Functions_Group4 Peripheral State and Error functions
  * @{
  */

/* Peripheral State and Errors functions  **************************************************/
HAL_UART_StateTypeDef HAL_UART_GetState(UART_HandleTypeDef *huart);
uint32_t              HAL_UART_GetError(UART_HandleTypeDef *huart);

/**
  * @}
  */

/**
  * @}
  */

/* Private functions -----------------------------------------------------------*/
/** @addtogroup UART_Private_Functions UART Private Functions
  * @{
  */
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
void              UART_InitCallbacksToDefault(UART_HandleTypeDef *huart);
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
HAL_StatusTypeDef UART_SetConfig(UART_HandleTypeDef *huart);
HAL_StatusTypeDef UART_CheckIdleState(UART_HandleTypeDef *huart);
HAL_StatusTypeDef UART_WaitOnFlagUntilTimeout(UART_HandleTypeDef *huart, uint32_t Flag, FlagStatus Status,
                                              uint32_t Tickstart, uint32_t Timeout);
void              UART_AdvFeatureConfig(UART_HandleTypeDef *huart);
HAL_StatusTypeDef UART_Start_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef UART_Start_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);

/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32g0xx_hal_usart.c
  * @author  MCD Application Team
  * @brief   USART HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Universal Synchronous/Asynchronous Receiver Transmitter
  *          Peripheral (USART).
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State and Error functions
  *
  @verbatim
 ===============================================================================
                        ##### How to use this driver #####
 ===============================================================================
    [..]
      The USART HAL driver can be used as follows:

      (#) Declare a USART_HandleTypeDef handle structure (eg. USART_HandleTypeDef husart).
      (#) Initialize the USART low level resources by implementing the HAL_USART_MspInit() API:
          (++) Enable the USARTx interface clock.
          (++) USART pins configuration:
            (+++) Enable the clock for the USART GPIOs.
            (+++) Configure these USART pins as alternate function pull-up.
          (++) NVIC configuration if you need to use interrupt process (HAL_USART_Transmit_IT(),
                HAL_USART_Receive_IT() and HAL_USART_TransmitReceive_IT() APIs):
            (+++) Configure the USARTx interrupt priority.
            (+++) Enable the NVIC USART IRQ handle.
            (++) USART interrupts handling:
              -@@-   The specific USART interrupts (Transmission complete interrupt,
                  RXNE interrupt and Error Interrupts) will be managed using the macros
                  __HAL_USART_ENABLE_IT() and __HAL_USART_DISABLE_IT() inside the transmit and receive process.
          (++) DMA Configuration if you need to use DMA process (HAL_USART_Transmit_DMA()
               HAL_USART_Receive_DMA() and HAL_USART_TransmitReceive_DMA() APIs):
            (+++) Declare a DMA handle structure for the Tx/Rx channel.
            (+++) Enable the DMAx interface clock.
            (+++) Configure the declared DMA handle structure with the required Tx/Rx parameters.
            (+++) Configure the DMA Tx/Rx channel.
            (+++) Associate the initialized DMA handle to the USART DMA Tx/Rx handle.
            (+++) Configure the priority and enable the NVIC for the transfer complete interrupt on the DMA Tx/Rx channel.

      (#) Program the Baud Rate, Word Length, Stop Bit, Parity, and Mode
          (Receiver/Transmitter) in the husart handle Init structure.

      (#) Initialize the USART registers by calling the HAL_USART_Init() API:
          (++) This API configures also the low level Hardware GPIO, CLOCK, CORTEX...etc)
               by calling the customized HAL_USART_MspInit(&husart) API.

    [..]
     (@) To configure and enable/disable the USART to wake up the MCU from stop mode, resort to UART API's
        HAL_UARTEx_StopModeWakeUpSourceConfig(), HAL_UARTEx_EnableStopMode() and
        HAL_UARTEx_DisableStopMode() in casting the USART handle to UART type UART_HandleTypeDef.

    ##### Callback registration #####
    ==================================

    [..]
    The compilation define USE_HAL_USART_REGISTER_CALLBACKS when set to 1
    allows the user to configure dynamically the driver callbacks.

    [..]
    Use Function @ref HAL_USART_RegisterCallback() to register a user callback.
    Function @ref HAL_USART_RegisterCallback() allows to register following callbacks:
    (+) TxHalfCpltCallback        : Tx Half Complete Callback.
    (+) TxCpltCallback            : Tx Complete Callback.
    (+) RxHalfCpltCallback        : Rx Half Complete Callback.
    (+) RxCpltCallback            : Rx Complete Callback.
    (+) TxRxCpltCallback          : Tx Rx Complete Callback.
    (+) ErrorCallback             : Error Callback.
    (+) AbortCpltCallback         : Abort Complete Callback.
    (+) RxFifoFullCallback        : Rx Fifo Full Callback.
    (+) TxFifoEmptyCallback       : Tx Fifo Empty Callback.
    (+) MspInitCallback           : USART MspInit.
    (+) MspDeInitCallback         : USART MspDeInit.
    This function takes as parameters the HAL peripheral handle, the Callback ID
    and a pointer to the user callback function.

    [..]
    Use function @ref HAL_USART_UnRegisterCallback() to reset a callback to the default
    weak (surcharged) function.
    @ref HAL_USART_UnRegisterCallback() takes as parameters the HAL peripheral handle,
    and the Callback ID.
    This function allows to reset following callbacks:
    (+) TxHalfCpltCallback        : Tx Half Complete Callback.
    (+) TxCpltCallback            : Tx Complete Callback.
    (+) RxHalfCpltCallback        : Rx Half Complete Callback.
    (+) RxCpltCallback            : Rx Complete Callback.
    (+) TxRxCpltCallback          : Tx Rx Complete Callback.
    (+) ErrorCallback             : Error Callback.
    (+) AbortCpltCallback         : Abort Complete Callback.
    (+) RxFifoFullCallback        : Rx Fifo Full Callback.
    (+) TxFifoEmptyCallback       : Tx Fifo Empty Callback.
    (+) MspInitCallback           : USART MspInit.
    (+) MspDeInitCallback         : USART MspDeInit.

    [..]
    By default, after the @ref HAL_USART_Init() and when the state is HAL_USART_STATE_RESET
    all callbacks are set to the corresponding weak (surcharged) functions:
    examples @ref HAL_USART_TxCpltCallback(), @ref HAL_USART_RxHalfCpltCallback().
    Exception done for MspInit and MspDeInit functions that are respectively
    reset to the legacy weak (surcharged) functions in the @ref HAL_USART_Init()
    and @ref HAL_USART_DeInit() only when these callbacks are null (not registered beforehand).
    If not, MspInit or MspDeInit are not null, the @ref HAL_USART_Init() and @ref HAL_USART_DeInit()
    keep and use the user MspInit/MspDeInit callbacks (registered beforehand).

    [..]
    Callbacks can be registered/unregistered in HAL_USART_STATE_READY state only.
    Exception done MspInit/MspDeInit that can be registered/unregistered
    in HAL_USART_STATE_READY or HAL_USART_STATE_RESET state, thus registered (user)
    MspInit/DeInit callbacks can be used during the Init/DeInit.
    In that case first register the MspInit/MspDeInit user callbacks
    using @ref HAL_USART_RegisterCallback() before calling @ref HAL_USART_DeInit()
    or @ref HAL_USART_Init() function.

    [..]
    When The compilation define USE_HAL_USART_REGISTER_CALLBACKS is set to 0 or
    not defined, the callback registration feature is not available
    and weak (surcharged) callbacks are used.


  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"
#include "stm32g0xx_hal_uart.h"

/** @addtogroup STM32G0xx_HAL_Driver
  * @{
  */

/** @defgroup USART USART
  * @brief HAL USART Synchronous module driver
  * @{
  */

#ifdef HAL_USART_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup USART_Private_Constants USART Private Constants
  * @{
  */
#define USART_DUMMY_DATA          ((uint16_t) 0xFFFF)           /*!< USART transmitted dummy data                     */
#define USART_TEACK_REACK_TIMEOUT             1000U             /*!< USART TX or RX enable acknowledge time-out value */
#define USART_CR1_FIELDS          ((uint32_t)(USART_CR1_M |  USART_CR1_PCE | USART_CR1_PS    | \
                                              USART_CR1_TE | USART_CR1_RE  | USART_CR1_OVER8 | \
                                              USART_CR1_FIFOEN ))                                  /*!< USART CR1 fields of parameters set by USART_SetConfig API */

#define USART_CR2_FIELDS          ((uint32_t)(USART_CR2_CPHA | USART_CR2_CPOL | USART_CR2_CLKEN | \
                                              USART_CR2_LBCL | USART_CR2_STOP | USART_CR2_SLVEN | \
                                              USART_CR2_DIS_NSS))                                  /*!< USART CR2 fields of parameters set by USART_SetConfig API */

#define USART_CR3_FIELDS          ((uint32_t)(USART_CR3_TXFTCFG | USART_CR3_RXFTCFG ))             /*!< USART or USART CR3 fields of parameters set by USART_SetConfig API */

#define USART_BRR_MIN    0x10U        /* USART BRR minimum authorized value */
#define USART_BRR_MAX    0xFFFFU      /* USART BRR maximum authorized value */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @addtogroup USART_Private_Functions
  * @{
  */
#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
void USART_InitCallbacksToDefault(USART_HandleTypeDef *husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
static void USART_EndTransfer(USART_HandleTypeDef *husart);
static void USART_DMATransmitCplt(DMA_HandleTypeDef *hdma);
static void USART_DMAReceiveCplt(DMA_HandleTypeDef *hdma);
static void USART_DMATxHalfCplt(DMA_HandleTypeDef *hdma);
static void USART_DMARxHalfCplt(DMA_HandleTypeDef *hdma);
static void USART_DMAError(DMA_HandleTypeDef *hdma);
static void USART_DMAAbortOnError(DMA_HandleTypeDef *hdma);
static void USART_DMATxAbortCallback(DMA_HandleTypeDef *hdma);
static void USART_DMARxAbortCallback(DMA_HandleTypeDef *hdma);
static HAL_StatusTypeDef USART_WaitOnFlagUntilTimeout(USART_HandleTypeDef *husart, uint32_t Flag, FlagStatus Status,
                                                      uint32_t Tickstart, uint32_t Timeout);
static HAL_StatusTypeDef USART_SetConfig(USART_HandleTypeDef *husart);
static HAL_StatusTypeDef USART_CheckIdleState(USART_HandleTypeDef *husart);
static void USART_TxISR_8BIT(USART_HandleTypeDef *husart);
static void USART_TxISR_16BIT(USART_HandleTypeDef *husart);
static void USART_TxISR_8BIT_FIFOEN(USART_HandleTypeDef *husart);
static void USART_TxISR_16BIT_FIFOEN(USART_HandleTypeDef *husart);
static void USART_EndTransmit_IT(USART_HandleTypeDef *husart);
static void USART_RxISR_8BIT(USART_HandleTypeDef *husart);
static void USART_RxISR_16BIT(USART_HandleTypeDef *husart);
static void USART_RxISR_8BIT_FIFOEN(USART_HandleTypeDef *husart);
static void USART_RxISR_16BIT_FIFOEN(USART_HandleTypeDef *husart);


/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup USART_Exported_Functions USART Exported Functions
  * @{
  */

/** @defgroup USART_Exported_Functions_Group1 Initialization and de-initialization functions
  * @brief    Initialization and Configuration functions
  *
@verbatim
 ===============================================================================
            ##### Initialization and Configuration functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to initialize the USART
    in asynchronous and in synchronous modes.
      (+) For the asynchronous mode only these parameters can be configured:
        (++) Baud Rate
        (++) Word Length
        (++) Stop Bit
        (++) Parity: If the parity is enabled, then the MSB bit of the data written
             in the data register is transmitted but is changed by the parity bit.
        (++) USART polarity
        (++) USART phase
        (++) USART LastBit
        (++) Receiver/transmitter modes

    [..]
    The HAL_USART_Init() function follows the USART  synchronous configuration
    procedure (details for the procedure are available in reference manual).

@endverbatim

  Depending on the frame length defined by the M1 and M0 bits (7-bit,
  8-bit or 9-bit), the possible USART formats are listed in the
  following table.

    Table 1. USART frame format.
    +-----------------------------------------------------------------------+
    |  M1 bit |  M0 bit |  PCE bit  |            USART frame                |
    |---------|---------|-----------|---------------------------------------|
    |    0    |    0    |    0      |    | SB |    8 bit data   | STB |     |
    |---------|---------|-----------|---------------------------------------|
    |    0    |    0    |    1      |    | SB | 7 bit data | PB | STB |     |
    |---------|---------|-----------|---------------------------------------|
    |    0    |    1    |    0      |    | SB |    9 bit data   | STB |     |
    |---------|---------|-----------|---------------------------------------|
    |    0    |    1    |    1      |    | SB | 8 bit data | PB | STB |     |
    |---------|---------|-----------|---------------------------------------|
    |    1    |    0    |    0      |    | SB |    7 bit data   | STB |     |
    |---------|---------|-----------|---------------------------------------|
    |    1    |    0    |    1      |    | SB | 6 bit data | PB | STB |     |
    +-----------------------------------------------------------------------+

  * @{
  */

/**
  * @brief  Initialize the USART mode according to the specified
  *         parameters in the USART_InitTypeDef and initialize the associated handle.
  * @param  husart USART handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_Init(USART_HandleTypeDef *husart)
{
  /* Check the USART handle allocation */
  if (husart == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_USART_INSTANCE(husart->Instance));

  if (husart->State == HAL_USART_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    husart->Lock = HAL_UNLOCKED;

#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
    USART_InitCallbacksToDefault(husart);

    if (husart->MspInitCallback == NULL)
    {
      husart->MspInitCallback = HAL_USART_MspInit;
    }

    /* Init the low level hardware */
    husart->MspInitCallback(husart);
#else
    /* Init the low level hardware : GPIO, CLOCK */
    HAL_USART_MspInit(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
  }

  husart->State = HAL_USART_STATE_BUSY;

  /* Disable the Peripheral */
  __HAL_USART_DISABLE(husart);

  /* Set the Usart Communication parameters */
  if (USART_SetConfig(husart) == HAL_ERROR)
  {
    return HAL_ERROR;
  }

  /* In Synchronous mode, the following bits must be kept cleared:
  - LINEN bit in the USART_CR2 register
  - HDSEL, SCEN and IREN bits in the USART_CR3 register.*/
  husart->Instance->CR2 &= ~USART_CR2_LINEN;
  husart->Instance->CR3 &= ~(USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN);

  /* Enable the Peripheral */
  __HAL_USART_ENABLE(husart);

  /* TEACK and/or REACK to check before moving husart->State to Ready */
  return (USART_CheckIdleState(husart));
}

/**
  * @brief DeInitialize the USART peripheral.
  * @param  husart USART handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_DeInit(USART_HandleTypeDef *husart)
{
  /* Check the USART handle allocation */
  if (husart == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_USART_INSTANCE(husart->Instance));

  husart->State = HAL_USART_STATE_BUSY;

  husart->Instance->CR1 = 0x0U;
  husart->Instance->CR2 = 0x0U;
  husart->Instance->CR3 = 0x0U;

#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
  if (husart->MspDeInitCallback == NULL)
  {
    husart->MspDeInitCallback = HAL_USART_MspDeInit;
  }
  /* DeInit the low level hardware */
  husart->MspDeInitCallback(husart);
#else
  /* DeInit the low level hardware */
  HAL_USART_MspDeInit(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */

  husart->ErrorCode = HAL_USART_ERROR_NONE;
  husart->State = HAL_USART_STATE_RESET;

  /* Process Unlock */
  __HAL_UNLOCK(husart);

  return HAL_OK;
}

/**
  * @brief Initialize the USART MSP.
  * @param husart USART handle.
  * @retval None
  */
__weak void HAL_USART_MspInit(USART_HandleTypeDef *husart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(husart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_USART_MspInit can be implemented in the user file
   */
}

/**
  * @brief DeInitialize the USART MSP.
  * @param husart USART handle.
  * @retval None
  */
__weak void HAL_USART_MspDeInit(USART_HandleTypeDef *husart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(husart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_USART_MspDeInit can be implemented in the user file
   */
}

#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a User USART Callback
  *         To be used instead of the weak predefined callback
  * @param  husart usart handle
  * @param  CallbackID ID of the callback to be registered
  *         This parameter can be one of the following values:
  *           @arg @ref HAL_USART_TX_HALFCOMPLETE_CB_ID Tx Half Complete Callback ID
  *           @arg @ref HAL_USART_TX_COMPLETE_CB_ID Tx Complete Callback ID
  *           @arg @ref HAL_USART_RX_HALFCOMPLETE_CB_ID Rx Half Complete Callback ID
  *           @arg @ref HAL_USART_RX_COMPLETE_CB_ID Rx Complete Callback ID
  *           @arg @ref HAL_USART_TX_RX_COMPLETE_CB_ID Rx Complete Callback ID
  *           @arg @ref HAL_USART_ERROR_CB_ID Error Callback ID
  *           @arg @ref HAL_USART_ABORT_COMPLETE_CB_ID Abort Complete Callback ID
  *           @arg @ref HAL_USART_RX_FIFO_FULL_CB_ID Rx Fifo Full Callback ID
  *           @arg @ref HAL_USART_TX_FIFO_EMPTY_CB_ID Tx Fifo Empty Callback ID
  *           @arg @ref HAL_USART_MSPINIT_CB_ID MspInit Callback ID
  *           @arg @ref HAL_USART_MSPDEINIT_CB_ID MspDeInit Callback ID
  * @param  pCallback pointer to the Callback function
  * @retval HAL status
+  */
HAL_StatusTypeDef HAL_USART_RegisterCallback(USART_HandleTypeDef *husart, HAL_USART_CallbackIDTypeDef CallbackID,
                                             pUSART_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    /* Update the error code */
    husart->ErrorCode |= HAL_USART_ERROR_INVALID_CALLBACK;

    return HAL_ERROR;
  }
  /* Process locked */
  __HAL_LOCK(husart);

  if (husart->State == HAL_USART_STATE_READY)
  {
    switch (CallbackID)
    {
      case HAL_USART_TX_HALFCOMPLETE_CB_ID :
        husart->TxHalfCpltCallback = pCallback;
        break;

      case HAL_USART_TX_COMPLETE_CB_ID :
        husart->TxCpltCallback = pCallback;
        break;

      case HAL_USART_RX_HALFCOMPLETE_CB_ID :
        husart->RxHalfCpltCallback = pCallback;
        break;

      case HAL_USART_RX_COMPLETE_CB_ID :
        husart->RxCpltCallback = pCallback;
        break;

      case HAL_USART_TX_RX_COMPLETE_CB_ID :
        husart->TxRxCpltCallback = pCallback;
        break;

      case HAL_USART_ERROR_CB_ID :
        husart->ErrorCallback = pCallback;
        break;

      case HAL_USART_ABORT_COMPLETE_CB_ID :
        husart->AbortCpltCallback = pCallback;
        break;

      case HAL_USART_RX_FIFO_FULL_CB_ID :
        husart->RxFifoFullCallback = pCallback;
        break;

      case HAL_USART_TX_FIFO_EMPTY_CB_ID :
        husart->TxFifoEmptyCallback = pCallback;
        break;

      case HAL_USART_MSPINIT_CB_ID :
        husart->MspInitCallback = pCallback;
        break;

      case HAL_USART_MSPDEINIT_CB_ID :
        husart->MspDeInitCallback = pCallback;
        break;

      default :
        /* Update the error code */
        husart->ErrorCode |= HAL_USART_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if (husart->State == HAL_USART_STATE_RESET)
  {
    switch (CallbackID)
    {
      case HAL_USART_MSPINIT_CB_ID :
        husart->MspInitCallback = pCallback;
        break;

      case HAL_USART_MSPDEINIT_CB_ID :
        husart->MspDeInitCallback = pCallback;
        break;

      default :
        /* Update the error code */
        husart->ErrorCode |= HAL_USART_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    husart->ErrorCode |= HAL_USART_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(husart);

  return status;
}

/**
  * @brief  Unregister an USART Callback
  *         USART callback is redirected to the weak predefined callback
  * @param  husart usart handle
  * @param  CallbackID ID of the callback to be unregistered
  *         This parameter can be one of the following values:
  *           @arg @ref HAL_USART_TX_HALFCOMPLETE_CB_ID Tx Half Complete Callback ID
  *           @arg @ref HAL_USART_TX_COMPLETE_CB_ID Tx Complete Callback ID
  *           @arg @ref HAL_USART_RX_HALFCOMPLETE_CB_ID Rx Half Complete Callback ID
  *           @arg @ref HAL_USART_RX_COMPLETE_CB_ID Rx Complete Callback ID
  *           @arg @ref HAL_USART_TX_RX_COMPLETE_CB_ID Rx Complete Callback ID
  *           @arg @ref HAL_USART_ERROR_CB_ID Error Callback ID
  *           @arg @ref HAL_USART_ABORT_COMPLETE_CB_ID Abort Complete Callback ID
  *           @arg @ref HAL_USART_RX_FIFO_FULL_CB_ID Rx Fifo Full Callback ID
  *           @arg @ref HAL_USART_TX_FIFO_EMPTY_CB_ID Tx Fifo Empty Callback ID
  *           @arg @ref HAL_USART_MSPINIT_CB_ID MspInit Callback ID
  *           @arg @ref HAL_USART_MSPDEINIT_CB_ID MspDeInit Callback ID
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_UnRegisterCallback(USART_HandleTypeDef *husart, HAL_USART_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process locked */
  __HAL_LOCK(husart);

  if (HAL_USART_STATE_READY == husart->State)
  {
    switch (CallbackID)
    {
      case HAL_USART_TX_HALFCOMPLETE_CB_ID :
        husart->TxHalfCpltCallback = HAL_USART_TxHalfCpltCallback;               /* Legacy weak  TxHalfCpltCallback       */
        break;

      case HAL_USART_TX_COMPLETE_CB_ID :
        husart->TxCpltCallback = HAL_USART_TxCpltCallback;                       /* Legacy weak TxCpltCallback            */
        break;

      case HAL_USART_RX_HALFCOMPLETE_CB_ID :
        husart->RxHalfCpltCallback = HAL_USART_RxHalfCpltCallback;               /* Legacy weak RxHalfCpltCallback        */
        break;

      case HAL_USART_RX_COMPLETE_CB_ID :
        husart->RxCpltCallback = HAL_USART_RxCpltCallback;                       /* Legacy weak RxCpltCallback            */
        break;

      case HAL_USART_TX_RX_COMPLETE_CB_ID :
        husart->TxRxCpltCallback = HAL_USART_TxRxCpltCallback;                   /* Legacy weak TxRxCpltCallback            */
        break;

      case HAL_USART_ERROR_CB_ID :
        husart->ErrorCallback = HAL_USART_ErrorCallback;                         /* Legacy weak ErrorCallback             */
        break;

      case HAL_USART_ABORT_COMPLETE_CB_ID :
        husart->AbortCpltCallback = HAL_USART_AbortCpltCallback;                 /* Legacy weak AbortCpltCallback         */
        break;

      case HAL_USART_RX_FIFO_FULL_CB_ID :
        husart->RxFifoFullCallback = HAL_USARTEx_RxFifoFullCallback;             /* Legacy weak RxFifoFullCallback        */
        break;

      case HAL_USART_TX_FIFO_EMPTY_CB_ID :
        husart->TxFifoEmptyCallback = HAL_USARTEx_TxFifoEmptyCallback;           /* Legacy weak TxFifoEmptyCallback       */
        break;

      case HAL_USART_MSPINIT_CB_ID :
        husart->MspInitCallback = HAL_USART_MspInit;                             /* Legacy weak MspInitCallback           */
        break;

      case HAL_USART_MSPDEINIT_CB_ID :
        husart->MspDeInitCallback = HAL_USART_MspDeInit;                         /* Legacy weak MspDeInitCallback         */
        break;

      default :
        /* Update the error code */
        husart->ErrorCode |= HAL_USART_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if (HAL_USART_STATE_RESET == husart->State)
  {
    switch (CallbackID)
    {
      case HAL_USART_MSPINIT_CB_ID :
        husart->MspInitCallback = HAL_USART_MspInit;
        break;

      case HAL_USART_MSPDEINIT_CB_ID :
        husart->MspDeInitCallback = HAL_USART_MspDeInit;
        break;

      default :
        /* Update the error code */
        husart->ErrorCode |= HAL_USART_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    husart->ErrorCode |= HAL_USART_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(husart);

  return status;
}
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */


/**
  * @}
  */

/** @defgroup USART_Exported_Functions_Group2 IO operation functions
  * @brief   USART Transmit and Receive functions
  *
@verbatim
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage the USART synchronous
    data transfers.

    [..] The USART supports master mode only: it cannot receive or send data related to an input
         clock (SCLK is always an output).

    [..]

    (#) There are two modes of transfer:
        (++) Blocking mode: The communication is performed in polling mode.
             The HAL status of all data processing is returned by the same function
             after finishing transfer.
        (++) No-Blocking mode: The communication is performed using Interrupts
             or DMA, These API's return the HAL status.
             The end of the data processing will be indicated through the
             dedicated USART IRQ when using Interrupt mode or the DMA IRQ when
             using DMA mode.
             The HAL_USART_TxCpltCallback(), HAL_USART_RxCpltCallback() and HAL_USART_TxRxCpltCallback() user callbacks
             will be executed respectively at the end of the transmit or Receive process
             The HAL_USART_ErrorCallback()user callback will be executed when a communication error is detected

    (#) Blocking mode API's are :
        (++) HAL_USART_Transmit() in simplex mode
        (++) HAL_USART_Receive() in full duplex receive only
        (++) HAL_USART_TransmitReceive() in full duplex mode

    (#) Non-Blocking mode API's with Interrupt are :
        (++) HAL_USART_Transmit_IT() in simplex mode
        (++) HAL_USART_Receive_IT() in full duplex receive only
        (++) HAL_USART_TransmitReceive_IT() in full duplex mode
        (++) HAL_USART_IRQHandler()

    (#) No-Blocking mode API's  with DMA are :
        (++) HAL_USART_Transmit_DMA() in simplex mode
        (++) HAL_USART_Receive_DMA() in full duplex receive only
        (++) HAL_USART_TransmitReceive_DMA() in full duplex mode
        (++) HAL_USART_DMAPause()
        (++) HAL_USART_DMAResume()
        (++) HAL_USART_DMAStop()

    (#) A set of Transfer Complete Callbacks are provided in Non_Blocking mode:
        (++) HAL_USART_TxCpltCallback()
        (++) HAL_USART_RxCpltCallback()
        (++) HAL_USART_TxHalfCpltCallback()
        (++) HAL_USART_RxHalfCpltCallback()
        (++) HAL_USART_ErrorCallback()
        (++) HAL_USART_TxRxCpltCallback()

    (#) Non-Blocking mode transfers could be aborted using Abort API's :
        (++) HAL_USART_Abort()
        (++) HAL_USART_Abort_IT()

    (#) For Abort services based on interrupts (HAL_USART_Abort_IT), a Abort Complete Callbacks is provided:
        (++) HAL_USART_AbortCpltCallback()

    (#) In Non-Blocking mode transfers, possible errors are split into 2 categories.
        Errors are handled as follows :
        (++) Error is considered as Recoverable and non blocking : Transfer could go till end, but error severity is
             to be evaluated by user : this concerns Frame Error, Parity Error or Noise Error in Interrupt mode reception .
             Received character is then retrieved and stored in Rx buffer, Error code is set to allow user to identify error type,
             and HAL_USART_ErrorCallback() user callback is executed. Transfer is kept ongoing on USART side.
             If user wants to abort it, Abort services should be called by user.
        (++) Error is considered as Blocking : Transfer could not be completed properly and is aborted.
             This concerns Overrun Error In Interrupt mode reception and all errors in DMA mode.
             Error code is set to allow user to identify error type, and HAL_USART_ErrorCallback() user callback is executed.

@endverbatim
  * @{
  */

/**
  * @brief  Simplex send an amount of data in blocking mode.
  * @note   When USART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
  *         the sent data is handled as a set of u16. In this case, Size must indicate the number
  *         of u16 provided through pTxData.
  * @note   When USART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
  *         address of user data buffer containing data to be sent, should be aligned on a half word frontier (16 bits)
  *         (as sent data will be handled using u16 pointer cast). Depending on compilation chain,
  *         use of specific alignment compilation directives or pragmas might be required to ensure proper alignment for pTxData.
  * @param  husart USART handle.
  * @param  pTxData Pointer to data buffer (u8 or u16 data elements).
  * @param  Size Amount of data elements (u8 or u16) to be sent.
  * @param  Timeout Timeout duration.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_Transmit(USART_HandleTypeDef *husart, uint8_t *pTxData, uint16_t Size, uint32_t Timeout)
{
  uint8_t  *ptxdata8bits;
  uint16_t *ptxdata16bits;
  uint32_t tickstart;

  if (husart->State == HAL_USART_STATE_READY)
  {
    if ((pTxData == NULL) || (Size == 0U))
    {
      return  HAL_ERROR;
    }

    /* In case of 9bits/No Parity transfer, pTxData buffer provided as input parameter
       should be aligned on a u16 frontier, as data to be filled into TDR will be
       handled through a u16 cast. */
    if ((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
    {
      if ((((uint32_t)pTxData) & 1U) != 0U)
      {
        return  HAL_ERROR;
      }
    }

    /* Process Locked */
    __HAL_LOCK(husart);

    husart->ErrorCode = HAL_USART_ERROR_NONE;
    husart->State = HAL_USART_STATE_BUSY_TX;

    /* Init tickstart for timeout management */
    tickstart = HAL_GetTick();

    husart->TxXferSize = Size;
    husart->TxXferCount = Size;

    /* In case of 9bits/No Parity transfer, pTxData needs to be handled as a uint16_t pointer */
    if ((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
    {
      ptxdata8bits  = NULL;
      ptxdata16bits = (uint16_t *) pTxData;
    }
    else
    {
      ptxdata8bits  = pTxData;
      ptxdata16bits = NULL;
    }

    /* Check the remaining data to be sent */
    while (husart->TxXferCount > 0U)
    {
      if (USART_WaitOnFlagUntilTimeout(husart, USART_FLAG_TXE, RESET, tickstart, Timeout) != HAL_OK)
      {
        return HAL_TIMEOUT;
      }
      if (ptxdata8bits == NULL)
      {
        husart->Instance->TDR = (uint16_t)(*ptxdata16bits & 0x01FFU);
        ptxdata16bits++;
      }
      else
      {
        husart->Instance->TDR = (uint8_t)(*ptxdata8bits & 0xFFU);
        ptxdata8bits++;
      }

      husart->TxXferCount--;
    }

    if (USART_WaitOnFlagUntilTimeout(husart, USART_FLAG_TC, RESET, tickstart, Timeout) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }

    /* Clear Transmission Complete Flag */
    __HAL_USART_CLEAR_FLAG(husart, USART_CLEAR_TCF);

    /* Clear overrun flag and discard the received data */
    __HAL_USART_CLEAR_OREFLAG(husart);
    __HAL_USART_SEND_REQ(husart, USART_RXDATA_FLUSH_REQUEST);
    __HAL_USART_SEND_REQ(husart, USART_TXDATA_FLUSH_REQUEST);

    /* At end of Tx process, restore husart->State to Ready */
    husart->State = HAL_USART_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(husart);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief Receive an amount of data in blocking mode.
  * @note   To receive synchronous data, dummy data are simultaneously transmitted.
  * @note   When USART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
  *         the received data is handled as a set of u16. In this case, Size must indicate the number
  *         of u16 available through pRxData.
  * @note   When USART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
  *         address of user data buffer for storing data to be received, should be aligned on a half word frontier (16 bits)
  *         (as received data will be handled using u16 pointer cast). Depending on compilation chain,
  *         use of specific alignment compilation directives or pragmas might be required to ensure proper alignment for pRxData.
  * @param husart USART handle.
  * @param pRxData Pointer to data buffer (u8 or u16 data elements).
  * @param Size Amount of data elements (u8 or u16) to be received.
  * @param Timeout Timeout duration.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_Receive(USART_HandleTypeDef *husart, uint8_t *pRxData, uint16_t Size, uint32_t Timeout)
{
  uint8_t  *prxdata8bits;
  uint16_t *prxdata16bits;
  uint16_t uhMask;
  uint32_t tickstart;

  if (husart->State == HAL_USART_STATE_READY)
  {
    if ((pRxData == NULL) || (Size == 0U))
    {
      return  HAL_ERROR;
    }

    /* In case of 9bits/No Parity transfer, pRxData buffer provided as input parameter
       should be aligned on a u16 frontier, as data to be received from RDR will be
       handled through a u16 cast. */
    if ((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
    {
      if ((((uint32_t)pRxData) & 1U) != 0U)
      {
        return  HAL_ERROR;
      }
    }

    /* Process Locked */
    __HAL_LOCK(husart);

    husart->ErrorCode = HAL_USART_ERROR_NONE;
    husart->State = HAL_USART_STATE_BUSY_RX;

    /* Init tickstart for timeout management */
    tickstart = HAL_GetTick();

    husart->RxXferSize = Size;
    husart->RxXferCount = Size;

    /* Computation of USART mask to apply to RDR register */
    USART_MASK_COMPUTATION(husart);
    uhMask = husart->Mask;

    /* In case of 9bits/No Parity transfer, pRxData needs to be handled as a uint16_t pointer */
    if ((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
    {
      prxdata8bits  = NULL;
      prxdata16bits = (uint16_t *) pRxData;
    }
    else
    {
      prxdata8bits  = pRxData;
      prxdata16bits = NULL;
    }

    /* as long as data have to be received */
    while (husart->RxXferCount > 0U)
    {
      if (husart->SlaveMode == USART_SLAVEMODE_DISABLE)
      {
        /* Wait until TXE flag is set to send dummy byte in order to generate the
        * clock for the slave to send data.
        * Whatever the frame length (7, 8 or 9-bit long), the same dummy value
        * can be written for all the cases. */
        if (USART_WaitOnFlagUntilTimeout(husart, USART_FLAG_TXE, RESET, tickstart, Timeout) != HAL_OK)
        {
          return HAL_TIMEOUT;
        }
        husart->Instance->TDR = (USART_DUMMY_DATA & (uint16_t)0x0FF);
      }

      /* Wait for RXNE Flag */
      if (USART_WaitOnFlagUntilTimeout(husart, USART_FLAG_RXNE, RESET, tickstart, Timeout) != HAL_OK)
      {
        return HAL_TIMEOUT;
      }

      if (prxdata8bits == NULL)
      {
        *prxdata16bits = (uint16_t)(husart->Instance->RDR & uhMask);
        prxdata16bits++;
      }
      else
      {
        *prxdata8bits = (uint8_t)(husart->Instance->RDR & (uint8_t)(uhMask & 0xFFU));
        prxdata8bits++;
      }

      husart->RxXferCount--;

    }

    /* Clear SPI slave underrun flag and discard transmit data */
    if (husart->SlaveMode == USART_SLAVEMODE_ENABLE)
    {
      __HAL_USART_CLEAR_UDRFLAG(husart);
      __HAL_USART_SEND_REQ(husart, USART_TXDATA_FLUSH_REQUEST);
    }

    /* At end of Rx process, restore husart->State to Ready */
    husart->State = HAL_USART_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(husart);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief Full-Duplex Send and Receive an amount of data in blocking mode.
  * @note   When USART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
  *         the sent data and the received data are handled as sets of u16. In this case, Size must indicate the number
  *         of u16 available through pTxData and through pRxData.
  * @note   When USART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
  *         address of user data buffers containing data to be sent/received, should be aligned on a half word frontier (16 bits)
  *         (as sent/received data will be handled using u16 pointer cast). Depending on compilation chain,
  *         use of specific alignment compilation directives or pragmas might be required to ensure proper alignment for pTxData and pRxData.
  * @param  husart USART handle.
  * @param  pTxData pointer to TX data buffer (u8 or u16 data elements).
  * @param  pRxData pointer to RX data buffer (u8 or u16 data elements).
  * @param  Size amount of data elements (u8 or u16) to be sent (same amount to be received).
  * @param  Timeout Timeout duration.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_TransmitReceive(USART_HandleTypeDef *husart, uint8_t *pTxData, uint8_t *pRxData,
                                            uint16_t Size, uint32_t Timeout)
{
  uint8_t  *prxdata8bits;
  uint16_t *prxdata16bits;
  uint8_t  *ptxdata8bits;
  uint16_t *ptxdata16bits;
  uint16_t uhMask;
  uint16_t rxdatacount;
  uint32_t tickstart;

  if (husart->State == HAL_USART_STATE_READY)
  {
    if ((pTxData == NULL) || (pRxData == NULL) || (Size == 0U))
    {
      return  HAL_ERROR;
    }

    /* In case of 9bits/No Parity transfer, pTxData and pRxData buffers provided as input parameter
       should be aligned on a u16 frontier, as data to be filled into TDR/retrieved from RDR will be
       handled through a u16 cast. */
    if ((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
    {
      if (((((uint32_t)pTxData) & 1U) != 0U) || ((((uint32_t)pRxData) & 1U) != 0U))
      {
        return  HAL_ERROR;
      }
    }

    /* Process Locked */
    __HAL_LOCK(husart);

    husart->ErrorCode = HAL_USART_ERROR_NONE;
    husart->State = HAL_USART_STATE_BUSY_RX;

    /* Init tickstart for timeout management */
    tickstart = HAL_GetTick();

    husart->RxXferSize = Size;
    husart->TxXferSize = Size;
    husart->TxXferCount = Size;
    husart->RxXferCount = Size;

    /* Computation of USART mask to apply to RDR register */
    USART_MASK_COMPUTATION(husart);
    uhMask = husart->Mask;

    /* In case of 9bits/No Parity transfer, pRxData needs to be handled as a uint16_t pointer */
    if ((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
    {
      prxdata8bits  = NULL;
      ptxdata8bits  = NULL;
      ptxdata16bits = (uint16_t *) pTxData;
      prxdata16bits = (uint16_t *) pRxData;
    }
    else
    {
      prxdata8bits  = pRxData;
      ptxdata8bits  = pTxData;
      ptxdata16bits = NULL;
      prxdata16bits = NULL;
    }

    if ((husart->TxXferCount == 0x01U) || (husart->SlaveMode == USART_SLAVEMODE_ENABLE))
    {
      /* Wait until TXE flag is set to send data */
      if (USART_WaitOnFlagUntilTimeout(husart, USART_FLAG_TXE, RESET, tickstart, Timeout) != HAL_OK)
      {
        return HAL_TIMEOUT;
      }
      if (ptxdata8bits == NULL)
      {
        husart->Instance->TDR = (uint16_t)(*ptxdata16bits & uhMask);
        ptxdata16bits++;
      }
      else
      {
        husart->Instance->TDR = (uint8_t)(*ptxdata8bits & (uint8_t)(uhMask & 0xFFU));
        ptxdata8bits++;
      }

      husart->TxXferCount--;
    }

    /* Check the remain data to be sent */
    /* rxdatacount is a temporary variable for MISRAC2012-Rule-13.5 */
    rxdatacount = husart->RxXferCount;
    while ((husart->TxXferCount > 0U) || (rxdatacount > 0U))
    {
      if (husart->TxXferCount > 0U)
      {
        /* Wait until TXE flag is set to send data */
        if (USART_WaitOnFlagUntilTimeout(husart, USART_FLAG_TXE, RESET, tickstart, Timeout) != HAL_OK)
        {
          return HAL_TIMEOUT;
        }
        if (ptxdata8bits == NULL)
        {
          husart->Instance->TDR = (uint16_t)(*ptxdata16bits & uhMask);
          ptxdata16bits++;
        }
        else
        {
          husart->Instance->TDR = (uint8_t)(*ptxdata8bits & (uint8_t)(uhMask & 0xFFU));
          ptxdata8bits++;
        }

        husart->TxXferCount--;
      }

      if (husart->RxXferCount > 0U)
      {
        /* Wait for RXNE Flag */
        if (USART_WaitOnFlagUntilTimeout(husart, USART_FLAG_RXNE, RESET, tickstart, Timeout) != HAL_OK)
        {
          return HAL_TIMEOUT;
        }

        if (prxdata8bits == NULL)
        {
          *prxdata16bits = (uint16_t)(husart->Instance->RDR & uhMask);
          prxdata16bits++;
        }
        else
        {
          *prxdata8bits = (uint8_t)(husart->Instance->RDR & (uint8_t)(uhMask & 0xFFU));
          prxdata8bits++;
        }

        husart->RxXferCount--;
      }
      rxdatacount = husart->RxXferCount;
    }

    /* At end of TxRx process, restore husart->State to Ready */
    husart->State = HAL_USART_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(husart);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief  Send an amount of data in interrupt mode.
  * @note   When USART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
  *         the sent data is handled as a set of u16. In this case, Size must indicate the number
  *         of u16 provided through pTxData.
  * @note   When USART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
  *         address of user data buffer containing data to be sent, should be aligned on a half word frontier (16 bits)
  *         (as sent data will be handled using u16 pointer cast). Depending on compilation chain,
  *         use of specific alignment compilation directives or pragmas might be required to ensure proper alignment for pTxData.
  * @param  husart USART handle.
  * @param  pTxData pointer to data buffer (u8 or u16 data elements).
  * @param  Size amount of data elements (u8 or u16) to be sent.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_Transmit_IT(USART_HandleTypeDef *husart, uint8_t *pTxData, uint16_t Size)
{
  if (husart->State == HAL_USART_STATE_READY)
  {
    if ((pTxData == NULL) || (Size == 0U))
    {
      return HAL_ERROR;
    }

    /* In case of 9bits/No Parity transfer, pTxData buffer provided as input parameter
       should be aligned on a u16 frontier, as data to be filled into TDR will be
       handled through a u16 cast. */
    if ((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
    {
      if ((((uint32_t)pTxData) & 1U) != 0U)
      {
        return  HAL_ERROR;
      }
    }

    /* Process Locked */
    __HAL_LOCK(husart);

    husart->pTxBuffPtr  = pTxData;
    husart->TxXferSize  = Size;
    husart->TxXferCount = Size;
    husart->TxISR       = NULL;

    husart->ErrorCode = HAL_USART_ERROR_NONE;
    husart->State     = HAL_USART_STATE_BUSY_TX;

    /* The USART Error Interrupts: (Frame error, noise error, overrun error)
    are not managed by the USART Transmit Process to avoid the overrun interrupt
    when the usart mode is configured for transmit and receive "USART_MODE_TX_RX"
    to benefit for the frame error and noise interrupts the usart mode should be
    configured only for transmit "USART_MODE_TX" */

    /* Configure Tx interrupt processing */
    if (husart->FifoMode == USART_FIFOMODE_ENABLE)
    {
      /* Set the Tx ISR function pointer according to the data word length */
      if ((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
      {
        husart->TxISR = USART_TxISR_16BIT_FIFOEN;
      }
      else
      {
        husart->TxISR = USART_TxISR_8BIT_FIFOEN;
      }

      /* Process Unlocked */
      __HAL_UNLOCK(husart);

      /* Enable the TX FIFO threshold interrupt */
      __HAL_USART_ENABLE_IT(husart, USART_IT_TXFT);
    }
    else
    {
      /* Set the Tx ISR function pointer according to the data word length */
      if ((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
      {
        husart->TxISR = USART_TxISR_16BIT;
      }
      else
      {
        husart->TxISR = USART_TxISR_8BIT;
      }

      /* Process Unlocked */
      __HAL_UNLOCK(husart);

      /* Enable the USART Transmit Data Register Empty Interrupt */
      __HAL_USART_ENABLE_IT(husart, USART_IT_TXE);
    }

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief Receive an amount of data in interrupt mode.
  * @note   To receive synchronous data, dummy data are simultaneously transmitted.
  * @note   When USART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
  *         the received data is handled as a set of u16. In this case, Size must indicate the number
  *         of u16 available through pRxData.
  * @note   When USART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
  *         address of user data buffer for storing data to be received, should be aligned on a half word frontier (16 bits)
  *         (as received data will be handled using u16 pointer cast). Depending on compilation chain,
  *         use of specific alignment compilation directives or pragmas might be required to ensure proper alignment for pRxData.
  * @param  husart USART handle.
  * @param  pRxData pointer to data buffer (u8 or u16 data elements).
  * @param  Size amount of data elements (u8 or u16) to be received.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_Receive_IT(USART_HandleTypeDef *husart, uint8_t *pRxData, uint16_t Size)
{
  uint16_t nb_dummy_data;

  if (husart->State == HAL_USART_STATE_READY)
  {
    if ((pRxData == NULL) || (Size == 0U))
    {
      return HAL_ERROR;
    }

    /* In case of 9bits/No Parity transfer, pRxData buffer provided as input parameter
       should be aligned on a u16 frontier, as data to be received from RDR will be
       handled through a u16 cast. */
    if ((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
    {
      if ((((uint32_t)pRxData) & 1U) != 0U)
      {
        return  HAL_ERROR;
      }
    }

    /* Process Locked */
    __HAL_LOCK(husart);

    husart->pRxBuffPtr  = pRxData;
    husart->RxXferSize  = Size;
    husart->RxXferCount = Size;
    husart->RxISR       = NULL;

    USART_MASK_COMPUTATION(husart);

    husart->ErrorCode = HAL_USART_ERROR_NONE;
    husart->State = HAL_USART_STATE_BUSY_RX;

    /* Enable the USART Error Interrupt: (Frame error, noise error, overrun error) */
    SET_BIT(husart->Instance->CR3, USART_CR3_EIE);

    /* Configure Rx interrupt processing */
    if ((husart->FifoMode == USART_FIFOMODE_ENABLE) && (Size >= husart->NbRxDataToProcess))
    {
      /* Set the Rx ISR function pointer according to the data word length */
      if ((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
      {
        husart->RxISR = USART_RxISR_16BIT_FIFOEN;
      }
      else
      {
        husart->RxISR = USART_RxISR_8BIT_FIFOEN;
      }

      /* Process Unlocked */
      __HAL_UNLOCK(husart);

      /* Enable the USART Parity Error interrupt and RX FIFO Threshold interrupt */
      SET_BIT(husart->Instance->CR1, USART_CR1_PEIE);
      SET_BIT(husart->Instance->CR3, USART_CR3_RXFTIE);
    }
    else
    {
      /* Set the Rx ISR function pointer according to the data word length */
      if ((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
      {
        husart->RxISR = USART_RxISR_16BIT;
      }
      else
      {
        husart->RxISR = USART_RxISR_8BIT;
      }

      /* Process Unlocked */
      __HAL_UNLOCK(husart);

      /* Enable the USART Parity Error and Data Register not empty Interrupts */
      SET_BIT(husart->Instance->CR1, USART_CR1_PEIE | USART_CR1_RXNEIE_RXFNEIE);
    }

    if (husart->SlaveMode == USART_SLAVEMODE_DISABLE)
    {
      /* Send dummy data in order to generate the clock for the Slave to send the next data.
         When FIFO mode is disabled only one data must be transferred.
         When FIFO mode is enabled data must be transmitted until the RX FIFO reaches its threshold.
      */
      if ((husart->FifoMode == USART_FIFOMODE_ENABLE) && (Size >= husart->NbRxDataToProcess))
      {
        for (nb_dummy_data = husart->NbRxDataToProcess ; nb_dummy_data > 0U ; nb_dummy_data--)
        {
          husart->Instance->TDR = (USART_DUMMY_DATA & (uint16_t)0x00FF);
        }
      }
      else
      {
        husart->Instance->TDR = (USART_DUMMY_DATA & (uint16_t)0x00FF);
      }
    }

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief Full-Duplex Send and Receive an amount of data in interrupt mode.
  * @note   When USART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
  *         the sent data and the received data are handled as sets of u16. In this case, Size must indicate the number
  *         of u16 available through pTxData and through pRxData.
  * @note   When USART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
  *         address of user data buffers containing data to be sent/received, should be aligned on a half word frontier (16 bits)
  *         (as sent/received data will be handled using u16 pointer cast). Depending on compilation chain,
  *         use of specific alignment compilation directives or pragmas might be required to ensure proper alignment for pTxData and pRxData.
  * @param  husart USART handle.
  * @param  pTxData pointer to TX data buffer (u8 or u16 data elements).
  * @param  pRxData pointer to RX data buffer (u8 or u16 data elements).
  * @param  Size amount of data elements (u8 or u16) to be sent (same amount to be received).
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_TransmitReceive_IT(USART_HandleTypeDef *husart, uint8_t *pTxData, uint8_t *pRxData,
                                               uint16_t Size)
{

  if (husart->State == HAL_USART_STATE_READY)
  {
    if ((pTxData == NULL) || (pRxData == NULL) || (Size == 0U))
    {
      return HAL_ERROR;
    }

    /* In case of 9bits/No Parity transfer, pTxData and pRxData buffers provided as input parameter
       should be aligned on a u16 frontier, as data to be filled into TDR/retrieved from RDR will be
       handled through a u16 cast. */
    if ((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
    {
      if (((((uint32_t)pTxData) & 1U) != 0U) || ((((uint32_t)pRxData) & 1U) != 0U))
      {
        return  HAL_ERROR;
      }
    }

    /* Process Locked */
    __HAL_LOCK(husart);

    husart->pRxBuffPtr = pRxData;
    husart->RxXferSize = Size;
    husart->RxXferCount = Size;
    husart->pTxBuffPtr = pTxData;
    husart->TxXferSize = Size;
    husart->TxXferCount = Size;

    /* Computation of USART mask to apply to RDR register */
    USART_MASK_COMPUTATION(husart);

    husart->ErrorCode = HAL_USART_ERROR_NONE;
    husart->State = HAL_USART_STATE_BUSY_TX_RX;

    /* Configure TxRx interrupt processing */
    if ((husart->FifoMode == USART_FIFOMODE_ENABLE) && (Size >= husart->NbRxDataToProcess))
    {
      /* Set the Rx ISR function pointer according to the data word length */
      if ((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
      {
        husart->TxISR = USART_TxISR_16BIT_FIFOEN;
        husart->RxISR = USART_RxISR_16BIT_FIFOEN;
      }
      else
      {
        husart->TxISR = USART_TxISR_8BIT_FIFOEN;
        husart->RxISR = USART_RxISR_8BIT_FIFOEN;
      }

      /* Process Locked */
      __HAL_UNLOCK(husart);

      /* Enable the USART Error Interrupt: (Frame error, noise error, overrun error) */
      SET_BIT(husart->Instance->CR3, USART_CR3_EIE);

      /* Enable the USART Parity Error interrupt  */
      SET_BIT(husart->Instance->CR1, USART_CR1_PEIE);

      /* Enable the TX and  RX FIFO Threshold interrupts */
      SET_BIT(husart->Instance->CR3, (USART_CR3_TXFTIE | USART_CR3_RXFTIE));
    }
    else
    {
      if ((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
      {
        husart->TxISR = USART_TxISR_16BIT;
        husart->RxISR = USART_RxISR_16BIT;
      }
      else
      {
        husart->TxISR = USART_TxISR_8BIT;
        husart->RxISR = USART_RxISR_8BIT;
      }

      /* Process Locked */
      __HAL_UNLOCK(husart);

      /* Enable the USART Error Interrupt: (Frame error, noise error, overrun error) */
      SET_BIT(husart->Instance->CR3, USART_CR3_EIE);

      /* Enable the USART Parity Error and USART Data Register not empty Interrupts */
      SET_BIT(husart->Instance->CR1, USART_CR1_PEIE | USART_CR1_RXNEIE_RXFNEIE);

      /* Enable the USART Transmit Data Register Empty Interrupt */
      SET_BIT(husart->Instance->CR1, USART_CR1_TXEIE_TXFNFIE);
    }

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief Send an amount of data in DMA mode.
  * @note   When USART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
  *         the sent data is handled as a set of u16. In this case, Size must indicate the number
  *         of u16 provided through pTxData.
  * @note   When USART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
  *         address of user data buffer containing data to be sent, should be aligned on a half word frontier (16 bits)
  *         (as sent data will be handled by DMA from halfword frontier). Depending on compilation chain,
  *         use of specific alignment compilation directives or pragmas might be required to ensure proper alignment for pTxData.
  * @param  husart USART handle.
  * @param  pTxData pointer to data buffer (u8 or u16 data elements).
  * @param  Size amount of data elements (u8 or u16) to be sent.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_Transmit_DMA(USART_HandleTypeDef *husart, uint8_t *pTxData, uint16_t Size)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t *tmp;

  if (husart->State == HAL_USART_STATE_READY)
  {
    if ((pTxData == NULL) || (Size == 0U))
    {
      return HAL_ERROR;
    }

    /* In case of 9bits/No Parity transfer, pTxData buffer provided as input parameter
       should be aligned on a u16 frontier, as data copy into TDR will be
       handled by DMA from a u16 frontier. */
    if ((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
    {
      if ((((uint32_t)pTxData) & 1U) != 0U)
      {
        return  HAL_ERROR;
      }
    }

    /* Process Locked */
    __HAL_LOCK(husart);

    husart->pTxBuffPtr = pTxData;
    husart->TxXferSize = Size;
    husart->TxXferCount = Size;

    husart->ErrorCode = HAL_USART_ERROR_NONE;
    husart->State = HAL_USART_STATE_BUSY_TX;

    if (husart->hdmatx != NULL)
    {
      /* Set the USART DMA transfer complete callback */
      husart->hdmatx->XferCpltCallback = USART_DMATransmitCplt;

      /* Set the USART DMA Half transfer complete callback */
      husart->hdmatx->XferHalfCpltCallback = USART_DMATxHalfCplt;

      /* Set the DMA error callback */
      husart->hdmatx->XferErrorCallback = USART_DMAError;

      /* Enable the USART transmit DMA channel */
      tmp = (uint32_t *)&pTxData;
      status = HAL_DMA_Start_IT(husart->hdmatx, *(uint32_t *)tmp, (uint32_t)&husart->Instance->TDR, Size);
    }

    if (status == HAL_OK)
    {
      /* Clear the TC flag in the ICR register */
      __HAL_USART_CLEAR_FLAG(husart, USART_CLEAR_TCF);

      /* Process Unlocked */
      __HAL_UNLOCK(husart);

      /* Enable the DMA transfer for transmit request by setting the DMAT bit
         in the USART CR3 register */
      SET_BIT(husart->Instance->CR3, USART_CR3_DMAT);

      return HAL_OK;
    }
    else
    {
      /* Set error code to DMA */
      husart->ErrorCode = HAL_USART_ERROR_DMA;

      /* Process Unlocked */
      __HAL_UNLOCK(husart);

      /* Restore husart->State to ready */
      husart->State = HAL_USART_STATE_READY;

      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief Receive an amount of data in DMA mode.
  * @note   When the USART parity is enabled (PCE = 1), the received data contain
  *         the parity bit (MSB position).
  * @note   The USART DMA transmit channel must be configured in order to generate the clock for the slave.
  * @note   When USART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
  *         the received data is handled as a set of u16. In this case, Size must indicate the number
  *         of u16 available through pRxData.
  * @note   When USART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
  *         address of user data buffer for storing data to be received, should be aligned on a half word frontier (16 bits)
  *         (as received data will be handled by DMA from halfword frontier). Depending on compilation chain,
  *         use of specific alignment compilation directives or pragmas might be required to ensure proper alignment for pRxData.
  * @param  husart USART handle.
  * @param  pRxData pointer to data buffer (u8 or u16 data elements).
  * @param  Size amount of data elements (u8 or u16) to be received.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_Receive_DMA(USART_HandleTypeDef *husart, uint8_t *pRxData, uint16_t Size)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t *tmp = (uint32_t *)&pRxData;

  /* Check that a Rx process is not already ongoing */
  if (husart->State == HAL_USART_STATE_READY)
  {
    if ((pRxData == NULL) || (Size == 0U))
    {
      return HAL_ERROR;
    }

    /* In case of 9bits/No Parity transfer, pRxData buffer provided as input parameter
       should be aligned on a u16 frontier, as data copy from RDR will be
       handled by DMA from a u16 frontier. */
    if ((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
    {
      if ((((uint32_t)pRxData) & 1U) != 0U)
      {
        return  HAL_ERROR;
      }
    }

    /* Process Locked */
    __HAL_LOCK(husart);

    husart->pRxBuffPtr = pRxData;
    husart->RxXferSize = Size;
    husart->pTxBuffPtr = pRxData;
    husart->TxXferSize = Size;

    husart->ErrorCode = HAL_USART_ERROR_NONE;
    husart->State = HAL_USART_STATE_BUSY_RX;

    if (husart->hdmarx != NULL)
    {
      /* Set the USART DMA Rx transfer complete callback */
      husart->hdmarx->XferCpltCallback = USART_DMAReceiveCplt;

      /* Set the USART DMA Half transfer complete callback */
      husart->hdmarx->XferHalfCpltCallback = USART_DMARxHalfCplt;

      /* Set the USART DMA Rx transfer error callback */
      husart->hdmarx->XferErrorCallback = USART_DMAError;

      /* Enable the USART receive DMA channel */
      status = HAL_DMA_Start_IT(husart->hdmarx, (uint32_t)&husart->Instance->RDR, *(uint32_t *)tmp, Size);
    }

    if ((status == HAL_OK) &&
        (husart->SlaveMode == USART_SLAVEMODE_DISABLE))
    {
      /* Enable the USART transmit DMA channel: the transmit channel is used in order
         to generate in the non-blocking mode the clock to the slave device,
         this mode isn't a simplex receive mode but a full-duplex receive mode */

      /* Set the USART DMA Tx Complete and Error callback to Null */
      if (husart->hdmatx != NULL)
      {
        husart->hdmatx->XferErrorCallback = NULL;
        husart->hdmatx->XferHalfCpltCallback = NULL;
        husart->hdmatx->XferCpltCallback = NULL;
        status = HAL_DMA_Start_IT(husart->hdmatx, *(uint32_t *)tmp, (uint32_t)&husart->Instance->TDR, Size);
      }
    }

    if (status == HAL_OK)
    {
      /* Process Unlocked */
      __HAL_UNLOCK(husart);

      /* Enable the USART Parity Error Interrupt */
      SET_BIT(husart->Instance->CR1, USART_CR1_PEIE);

      /* Enable the USART Error Interrupt: (Frame error, noise error, overrun error) */
      SET_BIT(husart->Instance->CR3, USART_CR3_EIE);

      /* Enable the DMA transfer for the receiver request by setting the DMAR bit
         in the USART CR3 register */
      SET_BIT(husart->Instance->CR3, USART_CR3_DMAR);

      /* Enable the DMA transfer for transmit request by setting the DMAT bit
         in the USART CR3 register */
      SET_BIT(husart->Instance->CR3, USART_CR3_DMAT);

      return HAL_OK;
    }
    else
    {
      if (husart->hdmarx != NULL)
      {
        status = HAL_DMA_Abort(husart->hdmarx);
      }

      /* No need to check on error code */
      UNUSED(status);

      /* Set error code to DMA */
      husart->ErrorCode = HAL_USART_ERROR_DMA;

      /* Process Unlocked */
      __HAL_UNLOCK(husart);

      /* Restore husart->State to ready */
      husart->State = HAL_USART_STATE_READY;

      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief Full-Duplex Transmit Receive an amount of data in non-blocking mode.
  * @note   When the USART parity is enabled (PCE = 1) the data received contain the parity bit.
  * @note   When USART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
  *         the sent data and the received data are handled as sets of u16. In this case, Size must indicate the number
  *         of u16 available through pTxData and through pRxData.
  * @note   When USART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
  *         address of user data buffers containing data to be sent/received, should be aligned on a half word frontier (16 bits)
  *         (as sent/received data will be handled by DMA from halfword frontier). Depending on compilation chain,
  *         use of specific alignment compilation directives or pragmas might be required to ensure proper alignment for pTxData and pRxData.
  * @param  husart USART handle.
  * @param  pTxData pointer to TX data buffer (u8 or u16 data elements).
  * @param  pRxData pointer to RX data buffer (u8 or u16 data elements).
  * @param  Size amount of data elements (u8 or u16) to be received/sent.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_TransmitReceive_DMA(USART_HandleTypeDef *husart, uint8_t *pTxData, uint8_t *pRxData,
                                                uint16_t Size)
{
  HAL_StatusTypeDef status;
  uint32_t *tmp;

  if (husart->State == HAL_USART_STATE_READY)
  {
    if ((pTxData == NULL) || (pRxData == NULL) || (Size == 0U))
    {
      return HAL_ERROR;
    }

    /* In case of 9bits/No Parity transfer, pTxData and pRxData buffers provided as input parameter
       should be aligned on a u16 frontier, as data copy to/from TDR/RDR will be
       handled by DMA from a u16 frontier. */
    if ((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
    {
      if (((((uint32_t)pTxData) & 1U) != 0U) || ((((uint32_t)pRxData) & 1U) != 0U))
      {
        return  HAL_ERROR;
      }
    }

    /* Process Locked */
    __HAL_LOCK(husart);

    husart->pRxBuffPtr = pRxData;
    husart->RxXferSize = Size;
    husart->pTxBuffPtr = pTxData;
    husart->TxXferSize = Size;

    husart->ErrorCode = HAL_USART_ERROR_NONE;
    husart->State = HAL_USART_STATE_BUSY_TX_RX;

    if ((husart->hdmarx != NULL) && (husart->hdmatx != NULL))
    {
      /* Set the USART DMA Rx transfer complete callback */
      husart->hdmarx->XferCpltCallback = USART_DMAReceiveCplt;

      /* Set the USART DMA Half transfer complete callback */
      husart->hdmarx->XferHalfCpltCallback = USART_DMARxHalfCplt;

      /* Set the USART DMA Tx transfer complete callback */
      husart->hdmatx->XferCpltCallback = USART_DMATransmitCplt;

      /* Set the USART DMA Half transfer complete callback */
      husart->hdmatx->XferHalfCpltCallback = USART_DMATxHalfCplt;

      /* Set the USART DMA Tx transfer error callback */
      husart->hdmatx->XferErrorCallback = USART_DMAError;

      /* Set the USART DMA Rx transfer error callback */
      husart->hdmarx->XferErrorCallback = USART_DMAError;

      /* Enable the USART receive DMA channel */
      tmp = (uint32_t *)&pRxData;
      status = HAL_DMA_Start_IT(husart->hdmarx, (uint32_t)&husart->Instance->RDR, *(uint32_t *)tmp, Size);

      /* Enable the USART transmit DMA channel */
      if (status == HAL_OK)
      {
        tmp = (uint32_t *)&pTxData;
        status = HAL_DMA_Start_IT(husart->hdmatx, *(uint32_t *)tmp, (uint32_t)&husart->Instance->TDR, Size);
      }
    }
    else
    {
      status = HAL_ERROR;
    }

    if (status == HAL_OK)
    {
      /* Process Unlocked */
      __HAL_UNLOCK(husart);

      /* Enable the USART Parity Error Interrupt */
      SET_BIT(husart->Instance->CR1, USART_CR1_PEIE);

      /* Enable the USART Error Interrupt: (Frame error, noise error, overrun error) */
      SET_BIT(husart->Instance->CR3, USART_CR3_EIE);

      /* Clear the TC flag in the ICR register */
      __HAL_USART_CLEAR_FLAG(husart, USART_CLEAR_TCF);

      /* Enable the DMA transfer for the receiver request by setting the DMAR bit
         in the USART CR3 register */
      SET_BIT(husart->Instance->CR3, USART_CR3_DMAR);

      /* Enable the DMA transfer for transmit request by setting the DMAT bit
         in the USART CR3 register */
      SET_BIT(husart->Instance->CR3, USART_CR3_DMAT);

      return HAL_OK;
    }
    else
    {
      if (husart->hdmarx != NULL)
      {
        status = HAL_DMA_Abort(husart->hdmarx);
      }

      /* No need to check on error code */
      UNUSED(status);

      /* Set error code to DMA */
      husart->ErrorCode = HAL_USART_ERROR_DMA;

      /* Process Unlocked */
      __HAL_UNLOCK(husart);

      /* Restore husart->State to ready */
      husart->State = HAL_USART_STATE_READY;

      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief Pause the DMA Transfer.
  * @param  husart USART handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_DMAPause(USART_HandleTypeDef *husart)
{
  const HAL_USART_StateTypeDef state = husart->State;

  /* Process Locked */
  __HAL_LOCK(husart);

  if ((HAL_IS_BIT_SET(husart->Instance->CR3, USART_CR3_DMAT)) &&
      (state == HAL_USART_STATE_BUSY_TX))
  {
    /* Disable the USART DMA Tx request */
    CLEAR_BIT(husart->Instance->CR3, USART_CR3_DMAT);
  }
  else if ((state == HAL_USART_STATE_BUSY_RX) ||
           (state == HAL_USART_STATE_BUSY_TX_RX))
  {
    if (HAL_IS_BIT_SET(husart->Instance->CR3, USART_CR3_DMAT))
    {
      /* Disable the USART DMA Tx request */
      CLEAR_BIT(husart->Instance->CR3, USART_CR3_DMAT);
    }
    if (HAL_IS_BIT_SET(husart->Instance->CR3, USART_CR3_DMAR))
    {
      /* Disable PE and ERR (Frame error, noise error, overrun error) interrupts */
      CLEAR_BIT(husart->Instance->CR1, USART_CR1_PEIE);
      CLEAR_BIT(husart->Instance->CR3, USART_CR3_EIE);

      /* Disable the USART DMA Rx request */
      CLEAR_BIT(husart->Instance->CR3, USART_CR3_DMAR);
    }
  }
  else
  {
    /* Nothing to do */
  }

  /* Process Unlocked */
  __HAL_UNLOCK(husart);

  return HAL_OK;
}

/**
  * @brief Resume the DMA Transfer.
  * @param  husart USART handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_DMAResume(USART_HandleTypeDef *husart)
{
  const HAL_USART_StateTypeDef state = husart->State;

  /* Process Locked */
  __HAL_LOCK(husart);

  if (state == HAL_USART_STATE_BUSY_TX)
  {
    /* Enable the USART DMA Tx request */
    SET_BIT(husart->Instance->CR3, USART_CR3_DMAT);
  }
  else if ((state == HAL_USART_STATE_BUSY_RX) ||
           (state == HAL_USART_STATE_BUSY_TX_RX))
  {
    /* Clear the Overrun flag before resuming the Rx transfer*/
    __HAL_USART_CLEAR_FLAG(husart, USART_CLEAR_OREF);

    /* Re-enable PE and ERR (Frame error, noise error, overrun error) interrupts */
    SET_BIT(husart->Instance->CR1, USART_CR1_PEIE);
    SET_BIT(husart->Instance->CR3, USART_CR3_EIE);

    /* Enable the USART DMA Rx request  before the DMA Tx request */
    SET_BIT(husart->Instance->CR3, USART_CR3_DMAR);

    /* Enable the USART DMA Tx request */
    SET_BIT(husart->Instance->CR3, USART_CR3_DMAT);
  }
  else
  {
    /* Nothing to do */
  }

  /* Process Unlocked */
  __HAL_UNLOCK(husart);

  return HAL_OK;
}

/**
  * @brief Stop the DMA Transfer.
  * @param  husart USART handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_DMAStop(USART_HandleTypeDef *husart)
{
  /* The Lock is not implemented on this API to allow the user application
     to call the HAL USART API under callbacks HAL_USART_TxCpltCallback() / HAL_USART_RxCpltCallback() /
     HAL_USART_TxHalfCpltCallback / HAL_USART_RxHalfCpltCallback:
     indeed, when HAL_DMA_Abort() API is called, the DMA TX/RX Transfer or Half Transfer complete
     interrupt is generated if the DMA transfer interruption occurs at the middle or at the end of
     the stream and the corresponding call back is executed. */

  /* Disable the USART Tx/Rx DMA requests */
  CLEAR_BIT(husart->Instance->CR3, USART_CR3_DMAT);
  CLEAR_BIT(husart->Instance->CR3, USART_CR3_DMAR);

  /* Abort the USART DMA tx channel */
  if (husart->hdmatx != NULL)
  {
    if (HAL_DMA_Abort(husart->hdmatx) != HAL_OK)
    {
      if (HAL_DMA_GetError(husart->hdmatx) == HAL_DMA_ERROR_TIMEOUT)
      {
        /* Set error code to DMA */
        husart->ErrorCode = HAL_USART_ERROR_DMA;

        return HAL_TIMEOUT;
      }
    }
  }
  /* Abort the USART DMA rx channel */
  if (husart->hdmarx != NULL)
  {
    if (HAL_DMA_Abort(husart->hdmarx) != HAL_OK)
    {
      if (HAL_DMA_GetError(husart->hdmarx) == HAL_DMA_ERROR_TIMEOUT)
      {
        /* Set error code to DMA */
        husart->ErrorCode = HAL_USART_ERROR_DMA;

        return HAL_TIMEOUT;
      }
    }
  }

  USART_EndTransfer(husart);
  husart->State = HAL_USART_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  Abort ongoing transfers (blocking mode).
  * @param  husart USART handle.
  * @note   This procedure could be used for aborting any ongoing transfer started in Interrupt or DMA mode.
  *         This procedure performs following operations :
  *           - Disable USART Interrupts (Tx and Rx)
  *           - Disable the DMA transfer in the peripheral register (if enabled)
  *           - Abort DMA transfer by calling HAL_DMA_Abort (in case of transfer in DMA mode)
  *           - Set handle State to READY
  * @note   This procedure is executed in blocking mode : when exiting function, Abort is considered as completed.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_Abort(USART_HandleTypeDef *husart)
{
  /* Disable TXEIE, TCIE, RXNE, RXFT, TXFT, PE and ERR (Frame error, noise error, overrun error) interrupts */
  CLEAR_BIT(husart->Instance->CR1, (USART_CR1_RXNEIE_RXFNEIE | USART_CR1_PEIE | USART_CR1_TXEIE_TXFNFIE |
                                    USART_CR1_TCIE));
  CLEAR_BIT(husart->Instance->CR3, (USART_CR3_EIE | USART_CR3_RXFTIE | USART_CR3_TXFTIE));

  /* Disable the USART DMA Tx request if enabled */
  if (HAL_IS_BIT_SET(husart->Instance->CR3, USART_CR3_DMAT))
  {
    CLEAR_BIT(husart->Instance->CR3, USART_CR3_DMAT);

    /* Abort the USART DMA Tx channel : use blocking DMA Abort API (no callback) */
    if (husart->hdmatx != NULL)
    {
      /* Set the USART DMA Abort callback to Null.
         No call back execution at end of DMA abort procedure */
      husart->hdmatx->XferAbortCallback = NULL;

      if (HAL_DMA_Abort(husart->hdmatx) != HAL_OK)
      {
        if (HAL_DMA_GetError(husart->hdmatx) == HAL_DMA_ERROR_TIMEOUT)
        {
          /* Set error code to DMA */
          husart->ErrorCode = HAL_USART_ERROR_DMA;

          return HAL_TIMEOUT;
        }
      }
    }
  }

  /* Disable the USART DMA Rx request if enabled */
  if (HAL_IS_BIT_SET(husart->Instance->CR3, USART_CR3_DMAR))
  {
    CLEAR_BIT(husart->Instance->CR3, USART_CR3_DMAR);

    /* Abort the USART DMA Rx channel : use blocking DMA Abort API (no callback) */
    if (husart->hdmarx != NULL)
    {
      /* Set the USART DMA Abort callback to Null.
         No call back execution at end of DMA abort procedure */
      husart->hdmarx->XferAbortCallback = NULL;

      if (HAL_DMA_Abort(husart->hdmarx) != HAL_OK)
      {
        if (HAL_DMA_GetError(husart->hdmarx) == HAL_DMA_ERROR_TIMEOUT)
        {
          /* Set error code to DMA */
          husart->ErrorCode = HAL_USART_ERROR_DMA;

          return HAL_TIMEOUT;
        }
      }
    }
  }

  /* Reset Tx and Rx transfer counters */
  husart->TxXferCount = 0U;
  husart->RxXferCount = 0U;

  /* Clear the Error flags in the ICR register */
  __HAL_USART_CLEAR_FLAG(husart, USART_CLEAR_OREF | USART_CLEAR_NEF | USART_CLEAR_PEF | USART_CLEAR_FEF);

  /* Flush the whole TX FIFO (if needed) */
  if (husart->FifoMode == USART_FIFOMODE_ENABLE)
  {
    __HAL_USART_SEND_REQ(husart, USART_TXDATA_FLUSH_REQUEST);
  }

  /* Discard the received data */
  __HAL_USART_SEND_REQ(husart, USART_RXDATA_FLUSH_REQUEST);

  /* Restore husart->State to Ready */
  husart->State  = HAL_USART_STATE_READY;

  /* Reset Handle ErrorCode to No Error */
  husart->ErrorCode = HAL_USART_ERROR_NONE;

  return HAL_OK;
}

/**
  * @brief  Abort ongoing transfers (Interrupt mode).
  * @param  husart USART handle.
  * @note   This procedure could be used for aborting any ongoing transfer started in Interrupt or DMA mode.
  *         This procedure performs following operations :
  *           - Disable USART Interrupts (Tx and Rx)
  *           - Disable the DMA transfer in the peripheral register (if enabled)
  *           - Abort DMA transfer by calling HAL_DMA_Abort_IT (in case of transfer in DMA mode)
  *           - Set handle State to READY
  *           - At abort completion, call user abort complete callback
  * @note   This procedure is executed in Interrupt mode, meaning that abort procedure could be
  *         considered as completed only when user abort complete callback is executed (not when exiting function).
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_Abort_IT(USART_HandleTypeDef *husart)
{
  uint32_t abortcplt = 1U;

  /* Disable TXEIE, TCIE, RXNE, RXFT, TXFT, PE and ERR (Frame error, noise error, overrun error) interrupts */
  CLEAR_BIT(husart->Instance->CR1, (USART_CR1_RXNEIE_RXFNEIE | USART_CR1_PEIE | USART_CR1_TXEIE_TXFNFIE |
                                    USART_CR1_TCIE));
  CLEAR_BIT(husart->Instance->CR3, (USART_CR3_EIE | USART_CR3_RXFTIE | USART_CR3_TXFTIE));

  /* If DMA Tx and/or DMA Rx Handles are associated to USART Handle, DMA Abort complete callbacks should be initialised
     before any call to DMA Abort functions */
  /* DMA Tx Handle is valid */
  if (husart->hdmatx != NULL)
  {
    /* Set DMA Abort Complete callback if USART DMA Tx request if enabled.
       Otherwise, set it to NULL */
    if (HAL_IS_BIT_SET(husart->Instance->CR3, USART_CR3_DMAT))
    {
      husart->hdmatx->XferAbortCallback = USART_DMATxAbortCallback;
    }
    else
    {
      husart->hdmatx->XferAbortCallback = NULL;
    }
  }
  /* DMA Rx Handle is valid */
  if (husart->hdmarx != NULL)
  {
    /* Set DMA Abort Complete callback if USART DMA Rx request if enabled.
       Otherwise, set it to NULL */
    if (HAL_IS_BIT_SET(husart->Instance->CR3, USART_CR3_DMAR))
    {
      husart->hdmarx->XferAbortCallback = USART_DMARxAbortCallback;
    }
    else
    {
      husart->hdmarx->XferAbortCallback = NULL;
    }
  }

  /* Disable the USART DMA Tx request if enabled */
  if (HAL_IS_BIT_SET(husart->Instance->CR3, USART_CR3_DMAT))
  {
    /* Disable DMA Tx at USART level */
    CLEAR_BIT(husart->Instance->CR3, USART_CR3_DMAT);

    /* Abort the USART DMA Tx channel : use non blocking DMA Abort API (callback) */
    if (husart->hdmatx != NULL)
    {
      /* USART Tx DMA Abort callback has already been initialised :
         will lead to call HAL_USART_AbortCpltCallback() at end of DMA abort procedure */

      /* Abort DMA TX */
      if (HAL_DMA_Abort_IT(husart->hdmatx) != HAL_OK)
      {
        husart->hdmatx->XferAbortCallback = NULL;
      }
      else
      {
        abortcplt = 0U;
      }
    }
  }

  /* Disable the USART DMA Rx request if enabled */
  if (HAL_IS_BIT_SET(husart->Instance->CR3, USART_CR3_DMAR))
  {
    CLEAR_BIT(husart->Instance->CR3, USART_CR3_DMAR);

    /* Abort the USART DMA Rx channel : use non blocking DMA Abort API (callback) */
    if (husart->hdmarx != NULL)
    {
      /* USART Rx DMA Abort callback has already been initialised :
         will lead to call HAL_USART_AbortCpltCallback() at end of DMA abort procedure */

      /* Abort DMA RX */
      if (HAL_DMA_Abort_IT(husart->hdmarx) != HAL_OK)
      {
        husart->hdmarx->XferAbortCallback = NULL;
        abortcplt = 1U;
      }
      else
      {
        abortcplt = 0U;
      }
    }
  }

  /* if no DMA abort complete callback execution is required => call user Abort Complete callback */
  if (abortcplt == 1U)
  {
    /* Reset Tx and Rx transfer counters */
    husart->TxXferCount = 0U;
    husart->RxXferCount = 0U;

    /* Reset errorCode */
    husart->ErrorCode = HAL_USART_ERROR_NONE;

    /* Clear the Error flags in the ICR register */
    __HAL_USART_CLEAR_FLAG(husart, USART_CLEAR_OREF | USART_CLEAR_NEF | USART_CLEAR_PEF | USART_CLEAR_FEF);

    /* Flush the whole TX FIFO (if needed) */
    if (husart->FifoMode == USART_FIFOMODE_ENABLE)
    {
      __HAL_USART_SEND_REQ(husart, USART_TXDATA_FLUSH_REQUEST);
    }

    /* Discard the received data */
    __HAL_USART_SEND_REQ(husart, USART_RXDATA_FLUSH_REQUEST);

    /* Restore husart->State to Ready */
    husart->State  = HAL_USART_STATE_READY;

    /* As no DMA to be aborted, call directly user Abort complete callback */
#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
    /* Call registered Abort Complete Callback */
    husart->AbortCpltCallback(husart);
#else
    /* Call legacy weak Abort Complete Callback */
    HAL_USART_AbortCpltCallback(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
  }

  return HAL_OK;
}

/**
  * @brief  Handle USART interrupt request.
  * @param  husart USART handle.
  * @retval None
  */
void HAL_USART_IRQHandler(USART_HandleTypeDef *husart)
{
  uint32_t isrflags   = READ_REG(husart->Instance->ISR);
  uint32_t cr1its     = READ_REG(husart->Instance->CR1);
  uint32_t cr3its     = READ_REG(husart->Instance->CR3);

  uint32_t errorflags;
  uint32_t errorcode;

  /* If no error occurs */
  errorflags = (isrflags & (uint32_t)(USART_ISR_PE | USART_ISR_FE | USART_ISR_ORE | USART_ISR_NE | USART_ISR_UDR));
  if (errorflags == 0U)
  {
    /* USART in mode Receiver ---------------------------------------------------*/
    if (((isrflags & USART_ISR_RXNE_RXFNE) != 0U)
        && (((cr1its & USART_CR1_RXNEIE_RXFNEIE) != 0U)
            || ((cr3its & USART_CR3_RXFTIE) != 0U)))
    {
      if (husart->RxISR != NULL)
      {
        husart->RxISR(husart);
      }
      return;
    }
  }

  /* If some errors occur */
  if ((errorflags != 0U)
      && (((cr3its & (USART_CR3_RXFTIE | USART_CR3_EIE)) != 0U)
          || ((cr1its & (USART_CR1_RXNEIE_RXFNEIE | USART_CR1_PEIE)) != 0U)))
  {
    /* USART parity error interrupt occurred -------------------------------------*/
    if (((isrflags & USART_ISR_PE) != 0U) && ((cr1its & USART_CR1_PEIE) != 0U))
    {
      __HAL_USART_CLEAR_IT(husart, USART_CLEAR_PEF);

      husart->ErrorCode |= HAL_USART_ERROR_PE;
    }

    /* USART frame error interrupt occurred --------------------------------------*/
    if (((isrflags & USART_ISR_FE) != 0U) && ((cr3its & USART_CR3_EIE) != 0U))
    {
      __HAL_USART_CLEAR_IT(husart, USART_CLEAR_FEF);

      husart->ErrorCode |= HAL_USART_ERROR_FE;
    }

    /* USART noise error interrupt occurred --------------------------------------*/
    if (((isrflags & USART_ISR_NE) != 0U) && ((cr3its & USART_CR3_EIE) != 0U))
    {
      __HAL_USART_CLEAR_IT(husart, USART_CLEAR_NEF);

      husart->ErrorCode |= HAL_USART_ERROR_NE;
    }

    /* USART Over-Run interrupt occurred -----------------------------------------*/
    if (((isrflags & USART_ISR_ORE) != 0U)
        && (((cr1its & USART_CR1_RXNEIE_RXFNEIE) != 0U) ||
            ((cr3its & (USART_CR3_RXFTIE | USART_CR3_EIE)) != 0U)))
    {
      __HAL_USART_CLEAR_IT(husart, USART_CLEAR_OREF);

      husart->ErrorCode |= HAL_USART_ERROR_ORE;
    }

    /* USART SPI slave underrun error interrupt occurred -------------------------*/
    if (((isrflags & USART_ISR_UDR) != 0U) && ((cr3its & USART_CR3_EIE) != 0U))
    {
      /* Ignore SPI slave underrun errors when reception is going on */
      if (husart->State == HAL_USART_STATE_BUSY_RX)
      {
        __HAL_USART_CLEAR_UDRFLAG(husart);
        return;
      }
      else
      {
        __HAL_USART_CLEAR_UDRFLAG(husart);
        husart->ErrorCode |= HAL_USART_ERROR_UDR;
      }
    }

    /* Call USART Error Call back function if need be --------------------------*/
    if (husart->ErrorCode != HAL_USART_ERROR_NONE)
    {
      /* USART in mode Receiver ---------------------------------------------------*/
      if (((isrflags & USART_ISR_RXNE_RXFNE) != 0U)
          && (((cr1its & USART_CR1_RXNEIE_RXFNEIE) != 0U)
              || ((cr3its & USART_CR3_RXFTIE) != 0U)))
      {
        if (husart->RxISR != NULL)
        {
          husart->RxISR(husart);
        }
      }

      /* If Overrun error occurs, or if any error occurs in DMA mode reception,
         consider error as blocking */
      errorcode = husart->ErrorCode & HAL_USART_ERROR_ORE;
      if ((HAL_IS_BIT_SET(husart->Instance->CR3, USART_CR3_DMAR)) ||
          (errorcode != 0U))
      {
        /* Blocking error : transfer is aborted
           Set the USART state ready to be able to start again the process,
           Disable Interrupts, and disable DMA requests, if ongoing */
        USART_EndTransfer(husart);

        /* Disable the USART DMA Rx request if enabled */
        if (HAL_IS_BIT_SET(husart->Instance->CR3, USART_CR3_DMAR))
        {
          CLEAR_BIT(husart->Instance->CR3, USART_CR3_DMAR | USART_CR3_DMAR);

          /* Abort the USART DMA Tx channel */
          if (husart->hdmatx != NULL)
          {
            /* Set the USART Tx DMA Abort callback to NULL : no callback
               executed at end of DMA abort procedure */
            husart->hdmatx->XferAbortCallback = NULL;

            /* Abort DMA TX */
            (void)HAL_DMA_Abort_IT(husart->hdmatx);
          }

          /* Abort the USART DMA Rx channel */
          if (husart->hdmarx != NULL)
          {
            /* Set the USART Rx DMA Abort callback :
               will lead to call HAL_USART_ErrorCallback() at end of DMA abort procedure */
            husart->hdmarx->XferAbortCallback = USART_DMAAbortOnError;

            /* Abort DMA RX */
            if (HAL_DMA_Abort_IT(husart->hdmarx) != HAL_OK)
            {
              /* Call Directly husart->hdmarx->XferAbortCallback function in case of error */
              husart->hdmarx->XferAbortCallback(husart->hdmarx);
            }
          }
          else
          {
            /* Call user error callback */
#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
            /* Call registered Error Callback */
            husart->ErrorCallback(husart);
#else
            /* Call legacy weak Error Callback */
            HAL_USART_ErrorCallback(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
          }
        }
        else
        {
          /* Call user error callback */
#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
          /* Call registered Error Callback */
          husart->ErrorCallback(husart);
#else
          /* Call legacy weak Error Callback */
          HAL_USART_ErrorCallback(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
        }
      }
      else
      {
        /* Non Blocking error : transfer could go on.
           Error is notified to user through user error callback */
#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
        /* Call registered Error Callback */
        husart->ErrorCallback(husart);
#else
        /* Call legacy weak Error Callback */
        HAL_USART_ErrorCallback(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
        husart->ErrorCode = HAL_USART_ERROR_NONE;
      }
    }
    return;

  } /* End if some error occurs */


  /* USART in mode Transmitter ------------------------------------------------*/
  if (((isrflags & USART_ISR_TXE_TXFNF) != 0U)
      && (((cr1its & USART_CR1_TXEIE_TXFNFIE) != 0U)
          || ((cr3its & USART_CR3_TXFTIE) != 0U)))
  {
    if (husart->TxISR != NULL)
    {
      husart->TxISR(husart);
    }
    return;
  }

  /* USART in mode Transmitter (transmission end) -----------------------------*/
  if (((isrflags & USART_ISR_TC) != 0U) && ((cr1its & USART_CR1_TCIE) != 0U))
  {
    USART_EndTransmit_IT(husart);
    return;
  }

  /* USART TX Fifo Empty occurred ----------------------------------------------*/
  if (((isrflags & USART_ISR_TXFE) != 0U) && ((cr1its & USART_CR1_TXFEIE) != 0U))
  {
#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
    /* Call registered Tx Fifo Empty Callback */
    husart->TxFifoEmptyCallback(husart);
#else
    /* Call legacy weak Tx Fifo Empty Callback */
    HAL_USARTEx_TxFifoEmptyCallback(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
    return;
  }

  /* USART RX Fifo Full occurred ----------------------------------------------*/
  if (((isrflags & USART_ISR_RXFF) != 0U) && ((cr1its & USART_CR1_RXFFIE) != 0U))
  {
#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
    /* Call registered Rx Fifo Full Callback */
    husart->RxFifoFullCallback(husart);
#else
    /* Call legacy weak Rx Fifo Full Callback */
    HAL_USARTEx_RxFifoFullCallback(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
    return;
  }
}

/**
  * @brief Tx Transfer completed callback.
  * @param husart USART handle.
  * @retval None
  */
__weak void HAL_USART_TxCpltCallback(USART_HandleTypeDef *husart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(husart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_USART_TxCpltCallback can be implemented in the user file.
   */
}

/**
  * @brief  Tx Half Transfer completed callback.
  * @param husart USART handle.
  * @retval None
  */
__weak void HAL_USART_TxHalfCpltCallback(USART_HandleTypeDef *husart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(husart);

  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_USART_TxHalfCpltCallback can be implemented in the user file.
   */
}

/**
  * @brief  Rx Transfer completed callback.
  * @param husart USART handle.
  * @retval None
  */
__weak void HAL_USART_RxCpltCallback(USART_HandleTypeDef *husart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(husart);

  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_USART_RxCpltCallback can be implemented in the user file.
   */
}

/**
  * @brief Rx Half Transfer completed callback.
  * @param husart USART handle.
  * @retval None
  */
__weak void HAL_USART_RxHalfCpltCallback(USART_HandleTypeDef *husart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(husart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_USART_RxHalfCpltCallback can be implemented in the user file
   */
}

/**
  * @brief Tx/Rx Transfers completed callback for the non-blocking process.
  * @param husart USART handle.
  * @retval None
  */
__weak void HAL_USART_TxRxCpltCallback(USART_HandleTypeDef *husart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(husart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_USART_TxRxCpltCallback can be implemented in the user file
   */
}

/**
  * @brief USART error callback.
  * @param husart USART handle.
  * @retval None
  */
__weak void HAL_USART_ErrorCallback(USART_HandleTypeDef *husart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(husart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_USART_ErrorCallback can be implemented in the user file.
   */
}

/**
  * @brief  USART Abort Complete callback.
  * @param  husart USART handle.
  * @retval None
  */
__weak void HAL_USART_AbortCpltCallback(USART_HandleTypeDef *husart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(husart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_USART_AbortCpltCallback can be implemented in the user file.
   */
}

/**
  * @}
  */

/** @defgroup USART_Exported_Functions_Group4 Peripheral State and Error functions
  *  @brief   USART Peripheral State and Error functions
  *
@verbatim
  ==============================================================================
            ##### Peripheral State and Error functions #####
  ==============================================================================
    [..]
    This subsection provides functions allowing to :
      (+) Return the USART handle state
      (+) Return the USART handle error code

@endverbatim
  * @{
  */


/**
  * @brief Return the USART handle state.
  * @param husart pointer to a USART_HandleTypeDef structure that contains
  *              the configuration information for the specified USART.
  * @retval USART handle state
  */
HAL_USART_StateTypeDef HAL_USART_GetState(USART_HandleTypeDef *husart)
{
  return husart->State;
}

/**
  * @brief Return the USART error code.
  * @param husart pointer to a USART_HandleTypeDef structure that contains
  *              the configuration information for the specified USART.
  * @retval USART handle Error Code
  */
uint32_t HAL_USART_GetError(USART_HandleTypeDef *husart)
{
  return husart->ErrorCode;
}

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup USART_Private_Functions USART Private Functions
  * @{
  */

/**
  * @brief  Initialize the callbacks to their default values.
  * @param  husart USART handle.
  * @retval none
  */
#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
void USART_InitCallbacksToDefault(USART_HandleTypeDef *husart)
{
  /* Init the USART Callback settings */
  husart->TxHalfCpltCallback        = HAL_USART_TxHalfCpltCallback;        /* Legacy weak TxHalfCpltCallback        */
  husart->TxCpltCallback            = HAL_USART_TxCpltCallback;            /* Legacy weak TxCpltCallback            */
  husart->RxHalfCpltCallback        = HAL_USART_RxHalfCpltCallback;        /* Legacy weak RxHalfCpltCallback        */
  husart->RxCpltCallback            = HAL_USART_RxCpltCallback;            /* Legacy weak RxCpltCallback            */
  husart->TxRxCpltCallback          = HAL_USART_TxRxCpltCallback;          /* Legacy weak TxRxCpltCallback          */
  husart->ErrorCallback             = HAL_USART_ErrorCallback;             /* Legacy weak ErrorCallback             */
  husart->AbortCpltCallback         = HAL_USART_AbortCpltCallback;         /* Legacy weak AbortCpltCallback         */
  husart->RxFifoFullCallback        = HAL_USARTEx_RxFifoFullCallback;      /* Legacy weak RxFifoFullCallback        */
  husart->TxFifoEmptyCallback       = HAL_USARTEx_TxFifoEmptyCallback;     /* Legacy weak TxFifoEmptyCallback       */
}
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */

/**
  * @brief  End ongoing transfer on USART peripheral (following error detection or Transfer completion).
  * @param  husart USART handle.
  * @retval None
  */
static void USART_EndTransfer(USART_HandleTypeDef *husart)
{
  /* Disable TXEIE, TCIE, RXNE, RXFT, TXFT, PE and ERR (Frame error, noise error, overrun error) interrupts */
  CLEAR_BIT(husart->Instance->CR1, (USART_CR1_RXNEIE_RXFNEIE | USART_CR1_PEIE | USART_CR1_TXEIE_TXFNFIE |
                                    USART_CR1_TCIE));
  CLEAR_BIT(husart->Instance->CR3, (USART_CR3_EIE | USART_CR3_RXFTIE | USART_CR3_TXFTIE));

  /* At end of process, restore husart->State to Ready */
  husart->State = HAL_USART_STATE_READY;
}

/**
  * @brief DMA USART transmit process complete callback.
  * @param  hdma DMA handle.
  * @retval None
  */
static void USART_DMATransmitCplt(DMA_HandleTypeDef *hdma)
{
  USART_HandleTypeDef *husart = (USART_HandleTypeDef *)(hdma->Parent);

  /* DMA Normal mode */
  if (HAL_IS_BIT_CLR(hdma->Instance->CCR, DMA_CCR_CIRC))
  {
    husart->TxXferCount = 0U;

    if (husart->State == HAL_USART_STATE_BUSY_TX)
    {
      /* Disable the DMA transfer for transmit request by resetting the DMAT bit
         in the USART CR3 register */
      CLEAR_BIT(husart->Instance->CR3, USART_CR3_DMAT);

      /* Enable the USART Transmit Complete Interrupt */
      __HAL_USART_ENABLE_IT(husart, USART_IT_TC);
    }
  }
  /* DMA Circular mode */
  else
  {
    if (husart->State == HAL_USART_STATE_BUSY_TX)
    {
#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
      /* Call registered Tx Complete Callback */
      husart->TxCpltCallback(husart);
#else
      /* Call legacy weak Tx Complete Callback */
      HAL_USART_TxCpltCallback(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
    }
  }
}

/**
  * @brief DMA USART transmit process half complete callback.
  * @param  hdma DMA handle.
  * @retval None
  */
static void USART_DMATxHalfCplt(DMA_HandleTypeDef *hdma)
{
  USART_HandleTypeDef *husart = (USART_HandleTypeDef *)(hdma->Parent);

#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
  /* Call registered Tx Half Complete Callback */
  husart->TxHalfCpltCallback(husart);
#else
  /* Call legacy weak Tx Half Complete Callback */
  HAL_USART_TxHalfCpltCallback(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
}

/**
  * @brief DMA USART receive process complete callback.
  * @param  hdma DMA handle.
  * @retval None
  */
static void USART_DMAReceiveCplt(DMA_HandleTypeDef *hdma)
{
  USART_HandleTypeDef *husart = (USART_HandleTypeDef *)(hdma->Parent);

  /* DMA Normal mode */
  if (HAL_IS_BIT_CLR(hdma->Instance->CCR, DMA_CCR_CIRC))
  {
    husart->RxXferCount = 0U;

    /* Disable PE and ERR (Frame error, noise error, overrun error) interrupts */
    CLEAR_BIT(husart->Instance->CR1, USART_CR1_PEIE);
    CLEAR_BIT(husart->Instance->CR3, USART_CR3_EIE);

    /* Disable the DMA RX transfer for the receiver request by resetting the DMAR bit
       in USART CR3 register */
    CLEAR_BIT(husart->Instance->CR3, USART_CR3_DMAR);
    /* similarly, disable the DMA TX transfer that was started to provide the
       clock to the slave device */
    CLEAR_BIT(husart->Instance->CR3, USART_CR3_DMAT);

    if (husart->State == HAL_USART_STATE_BUSY_RX)
    {
#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
      /* Call registered Rx Complete Callback */
      husart->RxCpltCallback(husart);
#else
      /* Call legacy weak Rx Complete Callback */
      HAL_USART_RxCpltCallback(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
    }
    /* The USART state is HAL_USART_STATE_BUSY_TX_RX */
    else
    {
#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
      /* Call registered Tx Rx Complete Callback */
      husart->TxRxCpltCallback(husart);
#else
      /* Call legacy weak Tx Rx Complete Callback */
      HAL_USART_TxRxCpltCallback(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
    }
    husart->State = HAL_USART_STATE_READY;
  }
  /* DMA circular mode */
  else
  {
    if (husart->State == HAL_USART_STATE_BUSY_RX)
    {
#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
      /* Call registered Rx Complete Callback */
      husart->RxCpltCallback(husart);
#else
      /* Call legacy weak Rx Complete Callback */
      HAL_USART_RxCpltCallback(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
    }
    /* The USART state is HAL_USART_STATE_BUSY_TX_RX */
    else
    {
#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
      /* Call registered Tx Rx Complete Callback */
      husart->TxRxCpltCallback(husart);
#else
      /* Call legacy weak Tx Rx Complete Callback */
      HAL_USART_TxRxCpltCallback(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
    }
  }
}

/**
  * @brief DMA USART receive process half complete callback.
  * @param  hdma DMA handle.
  * @retval None
  */
static void USART_DMARxHalfCplt(DMA_HandleTypeDef *hdma)
{
  USART_HandleTypeDef *husart = (USART_HandleTypeDef *)(hdma->Parent);

#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
  /* Call registered Rx Half Complete Callback */
  husart->RxHalfCpltCallback(husart);
#else
  /* Call legacy weak Rx Half Complete Callback */
  HAL_USART_RxHalfCpltCallback(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
}

/**
  * @brief DMA USART communication error callback.
  * @param  hdma DMA handle.
  * @retval None
  */
static void USART_DMAError(DMA_HandleTypeDef *hdma)
{
  USART_HandleTypeDef *husart = (USART_HandleTypeDef *)(hdma->Parent);

  husart->RxXferCount = 0U;
  husart->TxXferCount = 0U;
  USART_EndTransfer(husart);

  husart->ErrorCode |= HAL_USART_ERROR_DMA;
  husart->State = HAL_USART_STATE_READY;

#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
  /* Call registered Error Callback */
  husart->ErrorCallback(husart);
#else
  /* Call legacy weak Error Callback */
  HAL_USART_ErrorCallback(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA USART communication abort callback, when initiated by HAL services on Error
  *         (To be called at end of DMA Abort procedure following error occurrence).
  * @param  hdma DMA handle.
  * @retval None
  */
static void USART_DMAAbortOnError(DMA_HandleTypeDef *hdma)
{
  USART_HandleTypeDef *husart = (USART_HandleTypeDef *)(hdma->Parent);
  husart->RxXferCount = 0U;
  husart->TxXferCount = 0U;

#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
  /* Call registered Error Callback */
  husart->ErrorCallback(husart);
#else
  /* Call legacy weak Error Callback */
  HAL_USART_ErrorCallback(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA USART Tx communication abort callback, when initiated by user
  *         (To be called at end of DMA Tx Abort procedure following user abort request).
  * @note   When this callback is executed, User Abort complete call back is called only if no
  *         Abort still ongoing for Rx DMA Handle.
  * @param  hdma DMA handle.
  * @retval None
  */
static void USART_DMATxAbortCallback(DMA_HandleTypeDef *hdma)
{
  USART_HandleTypeDef *husart = (USART_HandleTypeDef *)(hdma->Parent);

  husart->hdmatx->XferAbortCallback = NULL;

  /* Check if an Abort process is still ongoing */
  if (husart->hdmarx != NULL)
  {
    if (husart->hdmarx->XferAbortCallback != NULL)
    {
      return;
    }
  }

  /* No Abort process still ongoing : All DMA channels are aborted, call user Abort Complete callback */
  husart->TxXferCount = 0U;
  husart->RxXferCount = 0U;

  /* Reset errorCode */
  husart->ErrorCode = HAL_USART_ERROR_NONE;

  /* Clear the Error flags in the ICR register */
  __HAL_USART_CLEAR_FLAG(husart, USART_CLEAR_OREF | USART_CLEAR_NEF | USART_CLEAR_PEF | USART_CLEAR_FEF);

  /* Restore husart->State to Ready */
  husart->State = HAL_USART_STATE_READY;

  /* Call user Abort complete callback */
#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
  /* Call registered Abort Complete Callback */
  husart->AbortCpltCallback(husart);
#else
  /* Call legacy weak Abort Complete Callback */
  HAL_USART_AbortCpltCallback(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */

}


/**
  * @brief  DMA USART Rx communication abort callback, when initiated by user
  *         (To be called at end of DMA Rx Abort procedure following user abort request).
  * @note   When this callback is executed, User Abort complete call back is called only if no
  *         Abort still ongoing for Tx DMA Handle.
  * @param  hdma DMA handle.
  * @retval None
  */
static void USART_DMARxAbortCallback(DMA_HandleTypeDef *hdma)
{
  USART_HandleTypeDef *husart = (USART_HandleTypeDef *)(hdma->Parent);

  husart->hdmarx->XferAbortCallback = NULL;

  /* Check if an Abort process is still ongoing */
  if (husart->hdmatx != NULL)
  {
    if (husart->hdmatx->XferAbortCallback != NULL)
    {
      return;
    }
  }

  /* No Abort process still ongoing : All DMA channels are aborted, call user Abort Complete callback */
  husart->TxXferCount = 0U;
  husart->RxXferCount = 0U;

  /* Reset errorCode */
  husart->ErrorCode = HAL_USART_ERROR_NONE;

  /* Clear the Error flags in the ICR register */
  __HAL_USART_CLEAR_FLAG(husart, USART_CLEAR_OREF | USART_CLEAR_NEF | USART_CLEAR_PEF | USART_CLEAR_FEF);

  /* Restore husart->State to Ready */
  husart->State  = HAL_USART_STATE_READY;

  /* Call user Abort complete callback */
#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
  /* Call registered Abort Complete Callback */
  husart->AbortCpltCallback(husart);
#else
  /* Call legacy weak Abort Complete Callback */
  HAL_USART_AbortCpltCallback(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
}


/**
  * @brief  Handle USART Communication Timeout.
  * @param  husart USART handle.
  * @param  Flag Specifies the USART flag to check.
  * @param  Status the Flag status (SET or RESET).
  * @param  Tickstart Tick start value
  * @param  Timeout timeout duration.
  * @retval HAL status
  */
static HAL_StatusTypeDef USART_WaitOnFlagUntilTimeout(USART_HandleTypeDef *husart, uint32_t Flag, FlagStatus Status,
                                                      uint32_t Tickstart, uint32_t Timeout)
{
  /* Wait until flag is set */
  while ((__HAL_USART_GET_FLAG(husart, Flag) ? SET : RESET) == Status)
  {
    /* Check for the Timeout */
    if (Timeout != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - Tickstart) > Timeout) || (Timeout == 0U))
      {
        husart->State = HAL_USART_STATE_READY;

        /* Process Unlocked */
        __HAL_UNLOCK(husart);

        return HAL_TIMEOUT;
      }
    }
  }
  return HAL_OK;
}

/**
  * @brief Configure the USART peripheral.
  * @param husart USART handle.
  * @retval HAL status
  */
static HAL_StatusTypeDef USART_SetConfig(USART_HandleTypeDef *husart)
{
  uint32_t tmpreg;
  USART_ClockSourceTypeDef clocksource;
  HAL_StatusTypeDef ret                = HAL_OK;
  uint16_t brrtemp;
  uint32_t usartdiv                    = 0x00000000;
  uint32_t pclk;

  /* Check the parameters */
  assert_param(IS_USART_POLARITY(husart->Init.CLKPolarity));
  assert_param(IS_USART_PHASE(husart->Init.CLKPhase));
  assert_param(IS_USART_LASTBIT(husart->Init.CLKLastBit));
  assert_param(IS_USART_BAUDRATE(husart->Init.BaudRate));
  assert_param(IS_USART_WORD_LENGTH(husart->Init.WordLength));
  assert_param(IS_USART_STOPBITS(husart->Init.StopBits));
  assert_param(IS_USART_PARITY(husart->Init.Parity));
  assert_param(IS_USART_MODE(husart->Init.Mode));
  assert_param(IS_USART_PRESCALER(husart->Init.ClockPrescaler));

  /*-------------------------- USART CR1 Configuration -----------------------*/
  /* Clear M, PCE, PS, TE and RE bits and configure
  *  the USART Word Length, Parity and Mode:
  *  set the M bits according to husart->Init.WordLength value
  *  set PCE and PS bits according to husart->Init.Parity value
  *  set TE and RE bits according to husart->Init.Mode value
  *  force OVER8 to 1 to allow to reach the maximum speed (Fclock/8) */
  tmpreg = (uint32_t)husart->Init.WordLength | husart->Init.Parity | husart->Init.Mode | USART_CR1_OVER8;
  MODIFY_REG(husart->Instance->CR1, USART_CR1_FIELDS, tmpreg);

  /*---------------------------- USART CR2 Configuration ---------------------*/
  /* Clear and configure the USART Clock, CPOL, CPHA, LBCL STOP and SLVEN bits:
   * set CPOL bit according to husart->Init.CLKPolarity value
   * set CPHA bit according to husart->Init.CLKPhase value
   * set LBCL bit according to husart->Init.CLKLastBit value (used in SPI master mode only)
   * set STOP[13:12] bits according to husart->Init.StopBits value */
  tmpreg = (uint32_t)(USART_CLOCK_ENABLE);
  tmpreg |= (uint32_t)husart->Init.CLKLastBit;
  tmpreg |= ((uint32_t)husart->Init.CLKPolarity | (uint32_t)husart->Init.CLKPhase);
  tmpreg |= (uint32_t)husart->Init.StopBits;
  MODIFY_REG(husart->Instance->CR2, USART_CR2_FIELDS, tmpreg);

  /*-------------------------- USART PRESC Configuration -----------------------*/
  /* Configure
   * - USART Clock Prescaler : set PRESCALER according to husart->Init.ClockPrescaler value */
  MODIFY_REG(husart->Instance->PRESC, USART_PRESC_PRESCALER, husart->Init.ClockPrescaler);

  /*-------------------------- USART BRR Configuration -----------------------*/
  /* BRR is filled-up according to OVER8 bit setting which is forced to 1     */
  USART_GETCLOCKSOURCE(husart, clocksource);

  switch (clocksource)
  {
    case USART_CLOCKSOURCE_PCLK1:
      pclk = HAL_RCC_GetPCLK1Freq();
      usartdiv = (uint32_t)(USART_DIV_SAMPLING8(pclk, husart->Init.BaudRate, husart->Init.ClockPrescaler));
      break;
    case USART_CLOCKSOURCE_HSI:
      usartdiv = (uint32_t)(USART_DIV_SAMPLING8(HSI_VALUE, husart->Init.BaudRate, husart->Init.ClockPrescaler));
      break;
    case USART_CLOCKSOURCE_SYSCLK:
      pclk = HAL_RCC_GetSysClockFreq();
      usartdiv = (uint32_t)(USART_DIV_SAMPLING8(pclk, husart->Init.BaudRate, husart->Init.ClockPrescaler));
      break;
    case USART_CLOCKSOURCE_LSE:
      usartdiv = (uint32_t)(USART_DIV_SAMPLING8((uint32_t)LSE_VALUE, husart->Init.BaudRate, husart->Init.ClockPrescaler));
      break;
    default:
      ret = HAL_ERROR;
      break;
  }

  /* USARTDIV must be greater than or equal to 0d16 and smaller than or equal to ffff */
  if ((usartdiv >= USART_BRR_MIN) && (usartdiv <= USART_BRR_MAX))
  {
    brrtemp = (uint16_t)(usartdiv & 0xFFF0U);
    brrtemp |= (uint16_t)((usartdiv & (uint16_t)0x000FU) >> 1U);
    husart->Instance->BRR = brrtemp;
  }
  else
  {
    ret = HAL_ERROR;
  }

  /* Initialize the number of data to process during RX/TX ISR execution */
  husart->NbTxDataToProcess = 1U;
  husart->NbRxDataToProcess = 1U;

  /* Clear ISR function pointers */
  husart->RxISR   = NULL;
  husart->TxISR   = NULL;

  return ret;
}

/**
  * @brief Check the USART Idle State.
  * @param husart USART handle.
  * @retval HAL status
  */
static HAL_StatusTypeDef USART_CheckIdleState(USART_HandleTypeDef *husart)
{
  uint32_t tickstart;

  /* Initialize the USART ErrorCode */
  husart->ErrorCode = HAL_USART_ERROR_NONE;

  /* Init tickstart for timeout management */
  tickstart = HAL_GetTick();

  /* Check if the Transmitter is enabled */
  if ((husart->Instance->CR1 & USART_CR1_TE) == USART_CR1_TE)
  {
    /* Wait until TEACK flag is set */
    if (USART_WaitOnFlagUntilTimeout(husart, USART_ISR_TEACK, RESET, tickstart, USART_TEACK_REACK_TIMEOUT) != HAL_OK)
    {
      /* Timeout occurred */
      return HAL_TIMEOUT;
    }
  }
  /* Check if the Receiver is enabled */
  if ((husart->Instance->CR1 & USART_CR1_RE) == USART_CR1_RE)
  {
    /* Wait until REACK flag is set */
    if (USART_WaitOnFlagUntilTimeout(husart, USART_ISR_REACK, RESET, tickstart, USART_TEACK_REACK_TIMEOUT) != HAL_OK)
    {
      /* Timeout occurred */
      return HAL_TIMEOUT;
    }
  }

  /* Initialize the USART state*/
  husart->State = HAL_USART_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(husart);

  return HAL_OK;
}

/**
  * @brief  Simplex send an amount of data in non-blocking mode.
  * @note   Function called under interruption only, once
  *         interruptions have been enabled by HAL_USART_Transmit_IT().
  * @note   The USART errors are not managed to avoid the overrun error.
  * @note   ISR function executed when FIFO mode is disabled and when the
  *         data word length is less than 9 bits long.
  * @param  husart USART handle.
  * @retval None
  */
static void USART_TxISR_8BIT(USART_HandleTypeDef *husart)
{
  const HAL_USART_StateTypeDef state = husart->State;

  /* Check that a Tx process is ongoing */
  if ((state == HAL_USART_STATE_BUSY_TX) ||
      (state == HAL_USART_STATE_BUSY_TX_RX))
  {
    if (husart->TxXferCount == 0U)
    {
      /* Disable the USART Transmit data register empty interrupt */
      __HAL_USART_DISABLE_IT(husart, USART_IT_TXE);

      /* Enable the USART Transmit Complete Interrupt */
      __HAL_USART_ENABLE_IT(husart, USART_IT_TC);
    }
    else
    {
      husart->Instance->TDR = (uint8_t)(*husart->pTxBuffPtr & (uint8_t)0xFF);
      husart->pTxBuffPtr++;
      husart->TxXferCount--;
    }
  }
}

/**
  * @brief  Simplex send an amount of data in non-blocking mode.
  * @note   Function called under interruption only, once
  *         interruptions have been enabled by HAL_USART_Transmit_IT().
  * @note   The USART errors are not managed to avoid the overrun error.
  * @note   ISR function executed when FIFO mode is disabled and when the
  *         data word length is 9 bits long.
  * @param  husart USART handle.
  * @retval None
  */
static void USART_TxISR_16BIT(USART_HandleTypeDef *husart)
{
  const HAL_USART_StateTypeDef state = husart->State;
  uint16_t *tmp;

  if ((state == HAL_USART_STATE_BUSY_TX) ||
      (state == HAL_USART_STATE_BUSY_TX_RX))
  {
    if (husart->TxXferCount == 0U)
    {
      /* Disable the USART Transmit data register empty interrupt */
      __HAL_USART_DISABLE_IT(husart, USART_IT_TXE);

      /* Enable the USART Transmit Complete Interrupt */
      __HAL_USART_ENABLE_IT(husart, USART_IT_TC);
    }
    else
    {
      tmp = (uint16_t *) husart->pTxBuffPtr;
      husart->Instance->TDR = (uint16_t)(*tmp & 0x01FFU);
      husart->pTxBuffPtr += 2U;
      husart->TxXferCount--;
    }
  }
}

/**
  * @brief  Simplex send an amount of data in non-blocking mode.
  * @note   Function called under interruption only, once
  *         interruptions have been enabled by HAL_USART_Transmit_IT().
  * @note   The USART errors are not managed to avoid the overrun error.
  * @note   ISR function executed when FIFO mode is enabled and when the
  *         data word length is less than 9 bits long.
  * @param  husart USART handle.
  * @retval None
  */
static void USART_TxISR_8BIT_FIFOEN(USART_HandleTypeDef *husart)
{
  const HAL_USART_StateTypeDef state = husart->State;
  uint16_t  nb_tx_data;

  /* Check that a Tx process is ongoing */
  if ((state == HAL_USART_STATE_BUSY_TX) ||
      (state == HAL_USART_STATE_BUSY_TX_RX))
  {
    for (nb_tx_data = husart->NbTxDataToProcess ; nb_tx_data > 0U ; nb_tx_data--)
    {
      if (husart->TxXferCount == 0U)
      {
        /* Disable the TX FIFO threshold interrupt */
        __HAL_USART_DISABLE_IT(husart, USART_IT_TXFT);

        /* Enable the USART Transmit Complete Interrupt */
        __HAL_USART_ENABLE_IT(husart, USART_IT_TC);

        break; /* force exit loop */
      }
      else if (__HAL_USART_GET_FLAG(husart, USART_FLAG_TXFNF) == SET)
      {
        husart->Instance->TDR = (uint8_t)(*husart->pTxBuffPtr & (uint8_t)0xFF);
        husart->pTxBuffPtr++;
        husart->TxXferCount--;
      }
      else
      {
        /* Nothing to do */
      }
    }
  }
}

/**
  * @brief  Simplex send an amount of data in non-blocking mode.
  * @note   Function called under interruption only, once
  *         interruptions have been enabled by HAL_USART_Transmit_IT().
  * @note   The USART errors are not managed to avoid the overrun error.
  * @note   ISR function executed when FIFO mode is enabled and when the
  *         data word length is 9 bits long.
  * @param  husart USART handle.
  * @retval None
  */
static void USART_TxISR_16BIT_FIFOEN(USART_HandleTypeDef *husart)
{
  const HAL_USART_StateTypeDef state = husart->State;
  uint16_t *tmp;
  uint16_t  nb_tx_data;

  /* Check that a Tx process is ongoing */
  if ((state == HAL_USART_STATE_BUSY_TX) ||
      (state == HAL_USART_STATE_BUSY_TX_RX))
  {
    for (nb_tx_data = husart->NbTxDataToProcess ; nb_tx_data > 0U ; nb_tx_data--)
    {
      if (husart->TxXferCount == 0U)
      {
        /* Disable the TX FIFO threshold interrupt */
        __HAL_USART_DISABLE_IT(husart, USART_IT_TXFT);

        /* Enable the USART Transmit Complete Interrupt */
        __HAL_USART_ENABLE_IT(husart, USART_IT_TC);

        break; /* force exit loop */
      }
      else if (__HAL_USART_GET_FLAG(husart, USART_FLAG_TXFNF) == SET)
      {
        tmp = (uint16_t *) husart->pTxBuffPtr;
        husart->Instance->TDR = (uint16_t)(*tmp & 0x01FFU);
        husart->pTxBuffPtr += 2U;
        husart->TxXferCount--;
      }
      else
      {
        /* Nothing to do */
      }
    }
  }
}

/**
  * @brief  Wraps up transmission in non-blocking mode.
  * @param  husart Pointer to a USART_HandleTypeDef structure that contains
  *                the configuration information for the specified USART module.
  * @retval None
  */
static void USART_EndTransmit_IT(USART_HandleTypeDef *husart)
{
  /* Disable the USART Transmit Complete Interrupt */
  __HAL_USART_DISABLE_IT(husart, USART_IT_TC);

  /* Disable the USART Error Interrupt: (Frame error, noise error, overrun error) */
  __HAL_USART_DISABLE_IT(husart, USART_IT_ERR);

  /* Clear TxISR function pointer */
  husart->TxISR = NULL;

  if (husart->State == HAL_USART_STATE_BUSY_TX)
  {
    /* Clear overrun flag and discard the received data */
    __HAL_USART_CLEAR_OREFLAG(husart);
    __HAL_USART_SEND_REQ(husart, USART_RXDATA_FLUSH_REQUEST);

    /* Tx process is completed, restore husart->State to Ready */
    husart->State = HAL_USART_STATE_READY;

#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
    /* Call registered Tx Complete Callback */
    husart->TxCpltCallback(husart);
#else
    /* Call legacy weak Tx Complete Callback */
    HAL_USART_TxCpltCallback(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
  }
  else if (husart->RxXferCount == 0U)
  {
    /* TxRx process is completed, restore husart->State to Ready */
    husart->State = HAL_USART_STATE_READY;

#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
    /* Call registered Tx Rx Complete Callback */
    husart->TxRxCpltCallback(husart);
#else
    /* Call legacy weak Tx Rx Complete Callback */
    HAL_USART_TxRxCpltCallback(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
  }
  else
  {
    /* Nothing to do */
  }
}


/**
  * @brief  Simplex receive an amount of data in non-blocking mode.
  * @note   Function called under interruption only, once
  *         interruptions have been enabled by HAL_USART_Receive_IT().
  * @note   ISR function executed when FIFO mode is disabled and when the
  *         data word length is less than 9 bits long.
  * @param  husart USART handle
  * @retval None
  */
static void USART_RxISR_8BIT(USART_HandleTypeDef *husart)
{
  const HAL_USART_StateTypeDef state = husart->State;
  uint16_t txdatacount;
  uint16_t uhMask = husart->Mask;
  uint32_t txftie;

  if ((state == HAL_USART_STATE_BUSY_RX) ||
      (state == HAL_USART_STATE_BUSY_TX_RX))
  {
    *husart->pRxBuffPtr = (uint8_t)(husart->Instance->RDR & (uint8_t)uhMask);
    husart->pRxBuffPtr++;
    husart->RxXferCount--;

    if (husart->RxXferCount == 0U)
    {
      /* Disable the USART Parity Error Interrupt and RXNE interrupt*/
      CLEAR_BIT(husart->Instance->CR1, (USART_CR1_RXNEIE_RXFNEIE | USART_CR1_PEIE));

      /* Disable the USART Error Interrupt: (Frame error, noise error, overrun error) */
      CLEAR_BIT(husart->Instance->CR3, USART_CR3_EIE);

      /* Clear RxISR function pointer */
      husart->RxISR = NULL;

      /* txftie and txdatacount are temporary variables for MISRAC2012-Rule-13.5 */
      txftie = READ_BIT(husart->Instance->CR3, USART_CR3_TXFTIE);
      txdatacount = husart->TxXferCount;

      if (state == HAL_USART_STATE_BUSY_RX)
      {
        /* Clear SPI slave underrun flag and discard transmit data */
        if (husart->SlaveMode == USART_SLAVEMODE_ENABLE)
        {
          __HAL_USART_CLEAR_UDRFLAG(husart);
          __HAL_USART_SEND_REQ(husart, USART_TXDATA_FLUSH_REQUEST);
        }

        /* Rx process is completed, restore husart->State to Ready */
        husart->State = HAL_USART_STATE_READY;

#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
        /* Call registered Rx Complete Callback */
        husart->RxCpltCallback(husart);
#else
        /* Call legacy weak Rx Complete Callback */
        HAL_USART_RxCpltCallback(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
      }
      else if ((READ_BIT(husart->Instance->CR1, USART_CR1_TCIE) != USART_CR1_TCIE) &&
               (txftie != USART_CR3_TXFTIE) &&
               (txdatacount == 0U))
      {
        /* TxRx process is completed, restore husart->State to Ready */
        husart->State = HAL_USART_STATE_READY;

#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
        /* Call registered Tx Rx Complete Callback */
        husart->TxRxCpltCallback(husart);
#else
        /* Call legacy weak Tx Rx Complete Callback */
        HAL_USART_TxRxCpltCallback(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
      }
      else
      {
        /* Nothing to do */
      }
    }
    else if ((state == HAL_USART_STATE_BUSY_RX) &&
             (husart->SlaveMode == USART_SLAVEMODE_DISABLE))
    {
      /* Send dummy byte in order to generate the clock for the Slave to Send the next data */
      husart->Instance->TDR = (USART_DUMMY_DATA & (uint16_t)0x00FF);
    }
    else
    {
      /* Nothing to do */
    }
  }
}

/**
  * @brief  Simplex receive an amount of data in non-blocking mode.
  * @note   Function called under interruption only, once
  *         interruptions have been enabled by HAL_USART_Receive_IT().
  * @note   ISR function executed when FIFO mode is disabled and when the
  *         data word length is 9 bits long.
  * @param  husart USART handle
  * @retval None
  */
static void USART_RxISR_16BIT(USART_HandleTypeDef *husart)
{
  const HAL_USART_StateTypeDef state = husart->State;
  uint16_t txdatacount;
  uint16_t *tmp;
  uint16_t uhMask = husart->Mask;
  uint32_t txftie;

  if ((state == HAL_USART_STATE_BUSY_RX) ||
      (state == HAL_USART_STATE_BUSY_TX_RX))
  {
    tmp = (uint16_t *) husart->pRxBuffPtr;
    *tmp = (uint16_t)(husart->Instance->RDR & uhMask);
    husart->pRxBuffPtr += 2U;
    husart->RxXferCount--;

    if (husart->RxXferCount == 0U)
    {
      /* Disable the USART Parity Error Interrupt and RXNE interrupt*/
      CLEAR_BIT(husart->Instance->CR1, (USART_CR1_RXNEIE_RXFNEIE | USART_CR1_PEIE));

      /* Disable the USART Error Interrupt: (Frame error, noise error, overrun error) */
      CLEAR_BIT(husart->Instance->CR3, USART_CR3_EIE);

      /* Clear RxISR function pointer */
      husart->RxISR = NULL;

      /* txftie and txdatacount are temporary variables for MISRAC2012-Rule-13.5 */
      txftie = READ_BIT(husart->Instance->CR3, USART_CR3_TXFTIE);
      txdatacount = husart->TxXferCount;

      if (state == HAL_USART_STATE_BUSY_RX)
      {
        /* Clear SPI slave underrun flag and discard transmit data */
        if (husart->SlaveMode == USART_SLAVEMODE_ENABLE)
        {
          __HAL_USART_CLEAR_UDRFLAG(husart);
          __HAL_USART_SEND_REQ(husart, USART_TXDATA_FLUSH_REQUEST);
        }

        /* Rx process is completed, restore husart->State to Ready */
        husart->State = HAL_USART_STATE_READY;

#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
        /* Call registered Rx Complete Callback */
        husart->RxCpltCallback(husart);
#else
        /* Call legacy weak Rx Complete Callback */
        HAL_USART_RxCpltCallback(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
      }
      else if ((READ_BIT(husart->Instance->CR1, USART_CR1_TCIE) != USART_CR1_TCIE) &&
               (txftie != USART_CR3_TXFTIE) &&
               (txdatacount == 0U))
      {
        /* TxRx process is completed, restore husart->State to Ready */
        husart->State = HAL_USART_STATE_READY;

#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
        /* Call registered Tx Rx Complete Callback */
        husart->TxRxCpltCallback(husart);
#else
        /* Call legacy weak Tx Rx Complete Callback */
        HAL_USART_TxRxCpltCallback(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
      }
      else
      {
        /* Nothing to do */
      }
    }
    else if ((state == HAL_USART_STATE_BUSY_RX) &&
             (husart->SlaveMode == USART_SLAVEMODE_DISABLE))
    {
      /* Send dummy byte in order to generate the clock for the Slave to Send the next data */
      husart->Instance->TDR = (USART_DUMMY_DATA & (uint16_t)0x00FF);
    }
    else
    {
      /* Nothing to do */
    }
  }
}

/**
  * @brief  Simplex receive an amount of data in non-blocking mode.
  * @note   Function called under interruption only, once
  *         interruptions have been enabled by HAL_USART_Receive_IT().
  * @note   ISR function executed when FIFO mode is enabled and when the
  *         data word length is less than 9 bits long.
  * @param  husart USART handle
  * @retval None
  */
static void USART_RxISR_8BIT_FIFOEN(USART_HandleTypeDef *husart)
{
  HAL_USART_StateTypeDef state = husart->State;
  uint16_t txdatacount;
  uint16_t rxdatacount;
  uint16_t uhMask = husart->Mask;
  uint16_t nb_rx_data;
  uint32_t txftie;

  /* Check that a Rx process is ongoing */
  if ((state == HAL_USART_STATE_BUSY_RX) ||
      (state == HAL_USART_STATE_BUSY_TX_RX))
  {
    for (nb_rx_data = husart->NbRxDataToProcess ; nb_rx_data > 0U ; nb_rx_data--)
    {
      if (__HAL_USART_GET_FLAG(husart, USART_FLAG_RXFNE) == SET)
      {
        *husart->pRxBuffPtr = (uint8_t)(husart->Instance->RDR & (uint8_t)(uhMask & 0xFFU));
        husart->pRxBuffPtr++;
        husart->RxXferCount--;

        if (husart->RxXferCount == 0U)
        {
          /* Disable the USART Parity Error Interrupt */
          CLEAR_BIT(husart->Instance->CR1, USART_CR1_PEIE);

          /* Disable the USART Error Interrupt: (Frame error, noise error, overrun error) and RX FIFO Threshold interrupt */
          CLEAR_BIT(husart->Instance->CR3, (USART_CR3_EIE | USART_CR3_RXFTIE));

          /* Clear RxISR function pointer */
          husart->RxISR = NULL;

          /* txftie and txdatacount are temporary variables for MISRAC2012-Rule-13.5 */
          txftie = READ_BIT(husart->Instance->CR3, USART_CR3_TXFTIE);
          txdatacount = husart->TxXferCount;

          if (state == HAL_USART_STATE_BUSY_RX)
          {
            /* Clear SPI slave underrun flag and discard transmit data */
            if (husart->SlaveMode == USART_SLAVEMODE_ENABLE)
            {
              __HAL_USART_CLEAR_UDRFLAG(husart);
              __HAL_USART_SEND_REQ(husart, USART_TXDATA_FLUSH_REQUEST);
            }

            /* Rx process is completed, restore husart->State to Ready */
            husart->State = HAL_USART_STATE_READY;
            state = HAL_USART_STATE_READY;

#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
            /* Call registered Rx Complete Callback */
            husart->RxCpltCallback(husart);
#else
            /* Call legacy weak Rx Complete Callback */
            HAL_USART_RxCpltCallback(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
          }
          else if ((READ_BIT(husart->Instance->CR1, USART_CR1_TCIE) != USART_CR1_TCIE) &&
                   (txftie != USART_CR3_TXFTIE) &&
                   (txdatacount == 0U))
          {
            /* TxRx process is completed, restore husart->State to Ready */
            husart->State = HAL_USART_STATE_READY;
            state = HAL_USART_STATE_READY;

#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
            /* Call registered Tx Rx Complete Callback */
            husart->TxRxCpltCallback(husart);
#else
            /* Call legacy weak Tx Rx Complete Callback */
            HAL_USART_TxRxCpltCallback(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
          }
          else
          {
            /* Nothing to do */
          }
        }
        else if ((state == HAL_USART_STATE_BUSY_RX) &&
                 (husart->SlaveMode == USART_SLAVEMODE_DISABLE))
        {
          /* Send dummy byte in order to generate the clock for the Slave to Send the next data */
          husart->Instance->TDR = (USART_DUMMY_DATA & (uint16_t)0x00FF);
        }
        else
        {
          /* Nothing to do */
        }
      }
    }

    /* When remaining number of bytes to receive is less than the RX FIFO
    threshold, next incoming frames are processed as if FIFO mode was
    disabled (i.e. one interrupt per received frame).
    */
    rxdatacount = husart->RxXferCount;
    if (((rxdatacount != 0U)) && (rxdatacount < husart->NbRxDataToProcess))
    {
      /* Disable the USART RXFT interrupt*/
      CLEAR_BIT(husart->Instance->CR3, USART_CR3_RXFTIE);

      /* Update the RxISR function pointer */
      husart->RxISR = USART_RxISR_8BIT;

      /* Enable the USART Data Register Not Empty interrupt */
      SET_BIT(husart->Instance->CR1, USART_CR1_RXNEIE_RXFNEIE);

      if ((husart->TxXferCount == 0U) &&
          (state == HAL_USART_STATE_BUSY_TX_RX) &&
          (husart->SlaveMode == USART_SLAVEMODE_DISABLE))
      {
        /* Send dummy byte in order to generate the clock for the Slave to Send the next data */
        husart->Instance->TDR = (USART_DUMMY_DATA & (uint16_t)0x00FF);
      }
    }
  }
  else
  {
    /* Clear RXNE interrupt flag */
    __HAL_USART_SEND_REQ(husart, USART_RXDATA_FLUSH_REQUEST);
  }
}

/**
  * @brief  Simplex receive an amount of data in non-blocking mode.
  * @note   Function called under interruption only, once
  *         interruptions have been enabled by HAL_USART_Receive_IT().
  * @note   ISR function executed when FIFO mode is enabled and when the
  *         data word length is 9 bits long.
  * @param  husart USART handle
  * @retval None
  */
static void USART_RxISR_16BIT_FIFOEN(USART_HandleTypeDef *husart)
{
  HAL_USART_StateTypeDef state = husart->State;
  uint16_t txdatacount;
  uint16_t rxdatacount;
  uint16_t *tmp;
  uint16_t uhMask = husart->Mask;
  uint16_t nb_rx_data;
  uint32_t txftie;

  /* Check that a Tx process is ongoing */
  if ((state == HAL_USART_STATE_BUSY_RX) ||
      (state == HAL_USART_STATE_BUSY_TX_RX))
  {
    for (nb_rx_data = husart->NbRxDataToProcess ; nb_rx_data > 0U ; nb_rx_data--)
    {
      if (__HAL_USART_GET_FLAG(husart, USART_FLAG_RXFNE) == SET)
      {
        tmp = (uint16_t *) husart->pRxBuffPtr;
        *tmp = (uint16_t)(husart->Instance->RDR & uhMask);
        husart->pRxBuffPtr += 2U;
        husart->RxXferCount--;

        if (husart->RxXferCount == 0U)
        {
          /* Disable the USART Parity Error Interrupt */
          CLEAR_BIT(husart->Instance->CR1, USART_CR1_PEIE);

          /* Disable the USART Error Interrupt: (Frame error, noise error, overrun error) and RX FIFO Threshold interrupt */
          CLEAR_BIT(husart->Instance->CR3, (USART_CR3_EIE | USART_CR3_RXFTIE));

          /* Clear RxISR function pointer */
          husart->RxISR = NULL;

          /* txftie and txdatacount are temporary variables for MISRAC2012-Rule-13.5 */
          txftie = READ_BIT(husart->Instance->CR3, USART_CR3_TXFTIE);
          txdatacount = husart->TxXferCount;

          if (state == HAL_USART_STATE_BUSY_RX)
          {
            /* Clear SPI slave underrun flag and discard transmit data */
            if (husart->SlaveMode == USART_SLAVEMODE_ENABLE)
            {
              __HAL_USART_CLEAR_UDRFLAG(husart);
              __HAL_USART_SEND_REQ(husart, USART_TXDATA_FLUSH_REQUEST);
            }

            /* Rx process is completed, restore husart->State to Ready */
            husart->State = HAL_USART_STATE_READY;
            state = HAL_USART_STATE_READY;

#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
            /* Call registered Rx Complete Callback */
            husart->RxCpltCallback(husart);
#else
            /* Call legacy weak Rx Complete Callback */
            HAL_USART_RxCpltCallback(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
          }
          else if ((READ_BIT(husart->Instance->CR1, USART_CR1_TCIE) != USART_CR1_TCIE) &&
                   (txftie != USART_CR3_TXFTIE) &&
                   (txdatacount == 0U))
          {
            /* TxRx process is completed, restore husart->State to Ready */
            husart->State = HAL_USART_STATE_READY;
            state = HAL_USART_STATE_READY;

#if (USE_HAL_USART_REGISTER_CALLBACKS == 1)
            /* Call registered Tx Rx Complete Callback */
            husart->TxRxCpltCallback(husart);
#else
            /* Call legacy weak Tx Rx Complete Callback */
            HAL_USART_TxRxCpltCallback(husart);
#endif /* USE_HAL_USART_REGISTER_CALLBACKS */
          }
          else
          {
            /* Nothing to do */
          }
        }
        else if ((state == HAL_USART_STATE_BUSY_RX) &&
                 (husart->SlaveMode == USART_SLAVEMODE_DISABLE))
        {
          /* Send dummy byte in order to generate the clock for the Slave to Send the next data */
          husart->Instance->TDR = (USART_DUMMY_DATA & (uint16_t)0x00FF);
        }
        else
        {
          /* Nothing to do */
        }
      }
    }

    /* When remaining number of bytes to receive is less than the RX FIFO
    threshold, next incoming frames are processed as if FIFO mode was
    disabled (i.e. one interrupt per received frame).
    */
    rxdatacount = husart->RxXferCount;
    if (((rxdatacount != 0U)) && (rxdatacount < husart->NbRxDataToProcess))
    {
      /* Disable the USART RXFT interrupt*/
      CLEAR_BIT(husart->Instance->CR3, USART_CR3_RXFTIE);

      /* Update the RxISR function pointer */
      husart->RxISR = USART_RxISR_16BIT;

      /* Enable the USART Data Register Not Empty interrupt */
      SET_BIT(husart->Instance->CR1, USART_CR1_RXNEIE_RXFNEIE);

      if ((husart->TxXferCount == 0U) &&
          (state == HAL_USART_STATE_BUSY_TX_RX) &&
          (husart->SlaveMode == USART_SLAVEMODE_DISABLE))
      {
        /* Send dummy byte in order to generate the clock for the Slave to Send the next data */
        husart->Instance->TDR = (USART_DUMMY_DATA & (uint16_t)0x00FF);
      }
    }
  }
  else
  {
    /* Clear RXNE interrupt flag */
    __HAL_USART_SEND_REQ(husart, USART_RXDATA_FLUSH_REQUEST);
  }
}

/**
  * @}
  */

#endif /* HAL_USART_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32G0xx_HAL_UART_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
