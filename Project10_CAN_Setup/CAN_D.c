#include "CAN_Drive.h"

/*
void CAN_init(unsigned short can)
{
    RCC->APB2ENR |= 1; // AFIO enabled for the GPIOs
    
    CAN_EnterInitializationMode(); // Enter Initialization Mode
    
    if(can == 1) // For CAN1
    { 
        RCC->APB1ENR |= 0x2000000; // Enabling CAN1
        init_GP(PA, 11, IN, IF); // PA11 - Rx
        init_GP(PA, 12, OUT50, O_AF_PP); // PA12 - Tx
        CAN1->MCR &= 0x00000000; // Reset MCR
        CAN1->MCR |= 0x20; // Only AWUM is HIGH
        
        CAN_ConfigureBitTiming();
        CAN_ExitInitializationMode();
        CAN_Start();
    }
    else if(can == 2)
    { 
        RCC->APB1ENR |= 0x4000000; // Enabling CAN2
        init_GP(PA, 11, IN, IF);
        init_GP(PA, 12, OUT50, O_AF_PP);
        CAN2->MCR &= 0x00000000; // Reset MCR
        CAN2->MCR |= 0x20; // Only AWUM is HIGH
        
        CAN_ConfigureBitTiming();
        CAN_ExitInitializationMode();
        CAN_Start();
    }
}

void CAN_EnterInitializationMode(void)
{
    // Set the INRQ bit in CAN_MCR to request entering initialization mode
    CAN1->MCR |= CAN_MCR_INRQ;

    // Wait until the initialization mode is confirmed by checking the INAK bit
    while ((CAN1->MSR & CAN_MSR_INAK) == 0);
}

void CAN_ExitInitializationMode(void)
{
    // Clear the INRQ bit in CAN_MCR to request exiting initialization mode
    CAN1->MCR &= ~CAN_MCR_INRQ;

    // Wait until the initialization mode is exited by checking the INAK bit
    while (CAN1->MSR & CAN_MSR_INAK);
}

void CAN_ConfigureBitTiming(void)
{
    // Example bit timing configuration for 500 kbps with a 36 MHz CAN clock
    CAN1->BTR = (4 << 24) | (2 << 20) | (13 << 16) | 2;
}

void CAN_Start(void)
{
    // Clear the sleep mode request and enable automatic retransmission
    CAN1->MCR &= ~CAN_MCR_SLEEP;
    CAN1->MCR |= CAN_MCR_TXFP | CAN_MCR_ABOM;

    // Wait for the CAN controller to leave initialization mode
    while (CAN1->MSR & CAN_MSR_INAK);
}

void CAN_SendMessage(CAN_TypeDef* CANx, uint32_t id, uint8_t* data, uint8_t length)
{
    uint8_t transmit_mailbox;
    
    // Select an empty transmit mailbox
    if (CANx->TSR & CAN_TSR_TME0)
    {
        transmit_mailbox = 0;
    }
    else if (CANx->TSR & CAN_TSR_TME1)
    {
        transmit_mailbox = 1;
    }
    else if (CANx->TSR & CAN_TSR_TME2)
    {
        transmit_mailbox = 2;
    }
    else
    {
        return; // No available transmit mailbox
    }

    // Set up the ID
    CANx->sTxMailBox[transmit_mailbox].TIR = (id << 21);
    // Set up the data length code
    CANx->sTxMailBox[transmit_mailbox].TDTR &= ~CAN_TDTxR_DLC;
    CANx->sTxMailBox[transmit_mailbox].TDTR |= length & CAN_TDTxR_DLC;
    // Set up the data bytes
    CANx->sTxMailBox[transmit_mailbox].TDLR = ((uint32_t)data[3] << 24) | ((uint32_t)data[2] << 16) | ((uint32_t)data[1] << 8) | data[0];
    CANx->sTxMailBox[transmit_mailbox].TDHR = ((uint32_t)data[7] << 24) | ((uint32_t)data[6] << 16) | ((uint32_t)data[5] << 8) | data[4];
    // Request transmission
    CANx->sTxMailBox[transmit_mailbox].TIR |= CAN_TI0R_TXRQ;
}

int CAN_ReceiveMessage(CAN_TypeDef* CANx, uint32_t* id, uint8_t* data, uint8_t* length)
{
    // Check if there is a new message in FIFO 0
    if (CANx->RF0R & CAN_RF0R_FMP0)
    {
        // Get the ID
        *id = (CANx->sFIFOMailBox[0].RIR >> 21);
        // Get the data length code
        *length = CANx->sFIFOMailBox[0].RDTR & CAN_RDTxR_DLC;
        // Get the data bytes
        data[0] = CANx->sFIFOMailBox[0].RDLR & 0xFF;
        data[1] = (CANx->sFIFOMailBox[0].RDLR >> 8) & 0xFF;
        data[2] = (CANx->sFIFOMailBox[0].RDLR >> 16) & 0xFF;
        data[3] = (CANx->sFIFOMailBox[0].RDLR >> 24) & 0xFF;
        data[4] = CANx->sFIFOMailBox[0].RDHR & 0xFF;
        data[5] = (CANx->sFIFOMailBox[0].RDHR >> 8) & 0xFF;
        data[6] = (CANx->sFIFOMailBox[0].RDHR >> 16) & 0xFF;
        data[7] = (CANx->sFIFOMailBox[0].RDHR >> 24) & 0xFF;
        // Release the FIFO
        CANx->RF0R |= CAN_RF0R_RFOM0;
        return 0;
    }
    else
    {
        return -1; // No message available
    }
}
*/