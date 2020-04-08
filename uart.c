/*
*
*   uart.c
*
*
*
*   @author
*   @date
*/

#include "uart.h"
#include <stdint.h>


void uart_init(void){

    uint16_t iBRD;
    uint16_t fBRD;
    SYSCTL_RCGCGPIO_R |= 0b000010;
    SYSCTL_RCGCUART_R |= 0b000010;
    GPIO_PORTB_AFSEL_R |= 0b000011;
    GPIO_PORTB_PCTL_R |= 0x00000011;
    GPIO_PORTB_DEN_R |= 0b11;
    GPIO_PORTB_DIR_R &= 0b00;
    GPIO_PORTB_DIR_R |= 0b10;
    iBRD = 8;
    fBRD = 44;
    UART1_CTL_R &= ~(UART_CTL_UARTEN);
    UART1_IBRD_R = iBRD;
    UART1_FBRD_R = fBRD;
    UART1_LCRH_R = UART_LCRH_WLEN_8;
    UART1_CC_R = UART_CC_CS_SYSCLK;
    UART1_CTL_R = (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);




//
//   // cyBot_uart_init_clean();
//    //TODO
//  //enable clock to GPIO port B
//  SYSCTL_RCGCGPIO_R |= 0b111010;
//
//  //enable clock to UART1
//  SYSCTL_RCGCUART_R |= 0b10;
//
//  //wait for GPIOB and UART1 peripherals to be ready
//  while (!(SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_R1) ) {};
//  while (!(SYSCTL_PRUART_R & 0b10) ) {};
//
//  //enable alternate functions on port B pins
//  GPIO_PORTB_AFSEL_R |= 0x63;
//
//  //enable digital functionality on port B pins
//  GPIO_PORTB_DEN_R |= 0x63;
//
//  //enable UART1 Rx and Tx on port B pins
//  GPIO_PORTB_PCTL_R = 0x11;
//
//  //calculate baud rate
//  uint16_t iBRD = 0x08; //use equations  //??????
//  uint16_t fBRD = 0x2C; // equations   //??????
//
//  //turn off UART1 while setting it up
//  UART1_CTL_R &= ~0b1;
//
//
//  GPIO_PORTB_DEN_R |= 0b01100011; //NOT FROM GIVEN FILE
//  GPIO_PORTB_DIR_R |= 0x41;     //NOT FROM GIVEN FILE
//
//  //set baud rate
//  //note: to take effect, there must be a write to LCRH after these assignments
//  UART1_IBRD_R = iBRD;
//  UART1_FBRD_R = fBRD;
//
//  //set frame, 8 data bits, 1 stop bit, no parity, no FIFO
//  //note: this write to LCRH must be after the BRD assignments
//  UART1_LCRH_R = 0X60;//UART_LCRH_WLEN_8
//
//  //use system clock as source
//  //note from the datasheet UARTCCC register description:
//  //field is 0 (system clock) by default on reset
//  //Good to be explicit in your code
//  UART1_CC_R = 0x0;
//
//  //re-enable UART1 and also enable RX, TX (three bits)
//  //note from the datasheet UARTCTL register description:
//  //RX and TX are enabled by default on reset
//  //Good to be explicit in your code
//  UART1_CTL_R = 0x301;

}



//
//
//
//void uart_init(void){
//
//
//
//    //cyBot_uart_init_PHJ_first_half();
//    //*
//    // Complete this code for configuring the GPIO PORTB part of UART1 initialization (your UART GPIO init code)
//
//
//    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;
//    SYSCTL_RCGCUART_R |= 0b10;
//    while ((SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_R4) == 0)
//    {};
//    while (!(SYSCTL_PRUART_R & 0b10 )) {};
//
//
//    GPIO_PORTB_AFSEL_R |= /*0x1;//*/0b11; // I think this is good N
//
//
//
//
//    GPIO_PORTB_PCTL_R &= ~0xFFFFFFFF;     // Force 0's in the desired locations
//    GPIO_PORTB_PCTL_R |= 0x11;     // Force 1's in the desired locations
//
//
//
//
//    // Or see the notes for a coding alternative to assign a value to the PCTL field
//
//
//
//
//    GPIO_PORTB_DEN_R |= 0b01100011; //I think this is good N
//    GPIO_PORTB_DIR_R &= ~0b00100010;   //I think this is good N
//
//
//
//    GPIO_PORTB_DIR_R |= 0x41;    //I think this is good N
//
//
//  //calculate baud rate
//  uint16_t iBRD = 0x08; //use equations  //??????
//  uint16_t fBRD = 0x2C; // equations   //??????
//
//  //turn off UART1 while setting it up
//  UART1_CTL_R &= ~0x1;  //??????
//
//
//
//
//  //good
//  //set baud rate
//  //note: to take effect, there must be a write to LCRH after these assignments
//  UART1_IBRD_R = iBRD;
//  UART1_FBRD_R = fBRD;
//
//  //set frame, 8 data bits, 1 stop bit, no parity, no FIFO
//  //note: this write to LCRH must be after the BRD assignments
//  UART1_LCRH_R = 0x60;       //GOOD
//
//
//
//  //use system clock as source
//  //note from the datasheet UARTCCC register description:
//  //field is 0 (system clock) by default on reset
//  //Good to be explicit in your code
//  UART1_CC_R = 0x0;//GOOD
//
//  //re-enable UART1 and also enable RX, TX (three bits)
//  //note from the datasheet UARTCTL register description:
//  //RX and TX are enabled by default on reset
//  //Good to be explicit in your code
//  UART1_CTL_R |= 0x301;//GOOD
//
//}

void uart_sendChar(char data){

    while(UART1_FR_R & 0x20){}

    UART1_DR_R = data;

}

char uart_receive(void){
    int data = 0;
    while(UART1_FR_R & UART_FR_RXFE);
    data = (int)(UART1_DR_R & 0xFF); //might have to mask as a char here?
    return data;
}

void uart_sendStr(const char *data){

    while(*data != '\0'){

        uart_sendChar(*data);
        data++;


    }







}


//TODO
// I want this to store the most recent char sent and controlled by interrupt
char getInturuptChar(){
    return 0;
}


char* receive_string(char str[], int size)
{
    int i = 0;
    while (i < size - 1)
    {
        str[i] = uart_receive();
        if (str[i] == '\n' || str[i] == '\r')
        {
            break;
        }
        i++;
    }
    str[i] = '\0';

    return str;

}
