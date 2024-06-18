#include "gp_drive.h"
#include "stm32f10x.h"                  // Device header
/*
void CAN_EnterInitializationMode(void);
void CAN_ExitInitializationMode(void);
void CAN_init(unsigned short can);
*/

/*
void CAN_Config(void);
void CAN_EnterInitializationMode(void);
void CAN_ExitInitializationMode(void);
void CAN_EnableDebugFreeze(void);
void CAN_DisableDebugFreeze(void);
void CAN_SoftwareMasterReset(void);
void CAN_TransmitMessage(void);
void CAN_ReceiveMessage(void);
*/

#define CAN_TDTxR_DLC 0x0000000F
#define CAN_RDTxR_DLC 0x0000000F

// Function prototypes
void CAN_EnterInitializationMode(void);
void CAN_ExitInitializationMode(void);
void CAN_ConfigureBitTiming(void);
void CAN_Start(void);
void CAN_SendMessage(CAN_TypeDef* CANx, uint32_t id, uint8_t* data, uint8_t length);
int CAN_ReceiveMessage(CAN_TypeDef* CANx, uint32_t* id, uint8_t* data, uint8_t* length);
void CAN_init(unsigned short can);