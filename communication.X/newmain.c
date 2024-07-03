#include <xc.h>
#include <stdint.h>

// Configuration bits
#pragma config FOSC = INTRC_NOCLKOUT  // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF             // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF            // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON             // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF               // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF              // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON             // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON              // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON             // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF              // Low Voltage Programming Enable bit (RB3/PGM pin has RB3 function, low voltage programming disabled)

// EEPROM data manipulation functions
#include "lib_usart_pic16_v1.0/usart_pic16.h"

// Define crystal frequency
#define _XTAL_FREQ 8000000

// Function prototypes
void USARTInit(uint16_t baud_rate);
char UART_Read();
void Test();
void USARTWriteChar(char ch);
void writeEEPROM(unsigned char address, unsigned char data);
unsigned char readEEPROM(unsigned char address);

// Main function
void main(void) {
    OSCCONbits.IRCF = 0b111;  // Set internal oscillator frequency to 8MHz

    // Configure ports
    TRISB = 0x00;   // PORTB as output
    TRISD = 0x00;   // PORTD as output
    PORTD = 0x00;   // Initialize PORTD to 0
    PORTB = 0x00;   // Initialize PORTB to 0
    TRISA = 0x00;   // PORTA as output
    PORTA = 0x00;   // Initialize PORTA to 0

    Test();         // Perform test function (assuming it blinks a LED)

    USARTInit(9600); // Initialize UART with baud rate 9600

    // Password for validation
    char password[] = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46};
    int count = 0;
    int count1 = 0;

    while (1) {
        // Check if EEPROM location 0x8E is 0xFF (indicating first run)
        if (readEEPROM(0x8E) == 0xFF) {
            int validate = 0;
            while (validate == 0) {
                int success = 0;
                for (int i = 0; i <= 5; i++) {
                    PORTAbits.RA1 = 1;
                    __delay_ms(100);
                    PORTAbits.RA1 = 0;
                    
                    // Validate password sent via UART
                    if (password[i] == UART_Read()) {
                        success++;
                    } else {
                        i = 5;
                        USARTWriteChar(0x40);
                    }
                }
                // If password validated successfully
                if (success == 6) {
                    USARTWriteChar(0x3F);

                    // Write data to EEPROM starting from address 0x00
                    char addressW = 0x00;
                    char addressW1 = 0x34;
                    int flag = 0;
                    char temp = 0x00;

                    // Write data block 1
                    while (flag == 0) {
                        temp = UART_Read();
                        writeEEPROM(addressW, temp);
                        addressW++;
                        count++;
                        if (UART_Read() == 0x3F) {
                            flag = 1;
                        }
                    }

                    // Read back and send data block 1 via UART
                    for (int j = 0; j < count; j++) {
                        USARTWriteChar(readEEPROM(j));
                        PORTAbits.RA1 = 1;
                        __delay_ms(100);
                        PORTAbits.RA1 = 0;
                    }

                    // Write data block 2
                    flag = 0;
                    while (flag == 0) {
                        temp = UART_Read();
                        writeEEPROM(addressW1, temp);
                        addressW1++;
                        count1++;
                        if (UART_Read() == 0x3F) {
                            flag = 1;
                        }
                    }

                    // Read back and send data block 2 via UART
                    for (int k = 52; k < 59; k++) {
                        USARTWriteChar(readEEPROM(k));
                        PORTAbits.RA1 = 1;
                        __delay_ms(100);
                        PORTAbits.RA1 = 0;
                    }

                    validate = 1;  // Exit validation loop
                }
            }
            
            // Mark initialization as complete in EEPROM
            writeEEPROM(0x8E, 0x77);
            writeEEPROM(0x8F, count);  // Write count of data block 1 to EEPROM
        }

        USARTWriteChar(0x20);  // Send space character via UART

        // Check if termination character received via UART
        if (UART_Read() == 0x3F) {
            // Send and blink data block 1 via UART and LEDs
            for (int u = 0; u < readEEPROM(0x8F); u++) {
                USARTWriteChar(readEEPROM(u));
                PORTAbits.RA1 = 1;
                __delay_ms(100);
                PORTAbits.RA1 = 0;
            }

            USARTWriteChar(0x20);  // Send space character via UART

            // Send and blink data block 2 via UART and LEDs
            for (int w = 52; w < 59; w++) {
                USARTWriteChar(readEEPROM(w));
                PORTAbits.RA1 = 1;
                __delay_ms(100);
                PORTAbits.RA1 = 0;
            }
        }
    }
}

// Function to initialize UART
void USARTInit(uint16_t baud_rate) {
    // Setup queue
    UQFront = UQEnd = -1;

    // Set baud rate
    switch (baud_rate) {
        case 9600:
            SPBRG = 0x33;  // Set baud rate to 9600
            break;
    }

    // Configure TXSTA register
    TXSTAbits.TX9 = 0;   // 8-bit transmission
    TXSTAbits.TXEN = 1;  // Transmit enable
    TXSTAbits.SYNC = 0;  // Asynchronous mode
    TXSTAbits.BRGH = 1;  // High speed baud rate

    // Configure RCSTA register
    RCSTAbits.SPEN = 1;  // Serial port enable
    RCSTAbits.RX9 = 0;   // 8-bit mode
    RCSTAbits.CREN = 1;  // Enable receive
    RCSTAbits.ADDEN = 0; // Disable address detection

    BAUDCTLbits.BRG16 = 0;  // 8-bit baud rate generator

    // Enable receive interrupt
    PIE1bits.RCIE = 1;
    INTCONbits.PEIE = 1;

    ei();  // Enable global interrupts
}

// Function to read from UART
char UART_Read() {
    PIE1bits.RCIE = 1;  // Enable UART receive interrupt
    while (!RCIF);      // Wait until data is received
    PIE1bits.RCIE = 0;  // Disable UART receive interrupt
    return RCREG;       // Return received data
}

// Test function (assuming it blinks LED connected to RA1)
void Test() {
    int d = 0;
    while (d != 5) {
        PORTAbits.RA1 = 1;
        __delay_ms(100);
        PORTAbits.RA1 = 0;
        __delay_ms(100);
        d++;
    }
}

// Function to write to EEPROM
void writeEEPROM(unsigned char address, unsigned char data) {
    unsigned char INTCON_SAVE;

    EEADR = address;    // Address to write
    EEDATA = data;      // Data to write
    EECON1bits.EEPGD = 0; // Selecting EEPROM Data Memory
    EECON1bits.WREN = 1;  // Enable writing of EEPROM

    INTCON_SAVE = INTCON; // Backup INTCON interrupt register
    INTCON = 0;           // Disable interrupts
    EECON2 = 0x55;        // Required sequence for write to internal EEPROM
    EECON2 = 0xAA;        // Required sequence for write to internal EEPROM
    EECON1bits.WR = 1;    // Initialize write cycle
    INTCON = INTCON_SAVE; // Enable interrupts
    EECON1bits.WREN = 0;  // Disable write

    while (PIR2bits.EEIF == 0); // Wait for write operation completion
    PIR2bits.EEIF = 0;    // Clear EEIF bit
}

// Function to read from EEPROM
unsigned char readEEPROM(unsigned char address) {
    EEADR = address;     // Address to read
    EECON1bits.EEPGD = 0; // Selecting EEPROM Data Memory
    EECON1bits.RD = 1;   // Initialize read cycle
    return EEDATA;       // Return data
}

// Function to write a character to UART
void USARTWriteChar(char ch) {
    while (!PIR1bits.TXIF);  // Wait for transmit buffer empty
    TXREG = ch;              // Load character to transmit
}
