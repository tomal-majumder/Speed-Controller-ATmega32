# Automated Speed Control System with ATMEGA32 and IR sensor

A microcontroller-based system that measures RPM using external interrupts and displays the results on an LCD screen with analog voltage monitoring and motor control capabilities.

## Features

- **RPM Measurement**: Real-time revolution counting using external interrupts
- **LCD Display**: 16x2 character LCD showing voltage and RPM readings
- **Analog Input**: ADC-based voltage measurement (0-5V range)
- **Motor Control**: PWM-based motor speed control with automatic adjustment
- **Interrupt-driven**: Efficient processing using timer and external interrupts
- **Real-time Updates**: Continuous monitoring and display refresh

## Hardware Requirements

### Components List

- **Microcontroller**: ATMega32 or similar AVR microcontroller
- **Motor Driver**: I293D
- **LCD Display**: 16x2 character LCD
- **Sensors**:
  - IR sensor
  - Potentiometer
- **Motor**: DC motor for speed control demonstration
- **Power Supply**: 5V DC power supply
- **External Battery**: external LIPO battery to power motors.
- **Resistors**: 2 10kΩ pull-up resistors for interrupt pins
- **Breadboard/PCB**: For circuit assembly
- **Connecting Wires**: Jumper wires for connections

### Pin Configuration

| Function      | AVR Pin | Port   | Description                           |
| ------------- | ------- | ------ | ------------------------------------- |
| LCD D4        | PD4     | PORTD4 | LCD Data Line 4                       |
| LCD D5        | PD5     | PORTD5 | LCD Data Line 5                       |
| LCD D6        | PD6     | PORTD6 | LCD Data Line 6                       |
| LCD D7        | PD7     | PORTD7 | LCD Data Line 7                       |
| LCD RS        | PC6     | PORTC6 | LCD Register Select                   |
| LCD EN        | PC7     | PORTC7 | LCD Enable                            |
| IR Input      | PD2     | INT0   | External Interrupt 0 (IR sensor)      |
| Control Input | PD3     | INT1   | External Interrupt 1 (Control signal) |
| Analog Input  | PC0     | ADC0   | Analog voltage measurement            |
| PWM Output    | PB3     | OC0    | Motor control PWM                     |
| Status LEDs   | PB0-PB1 | PORTB  | Status indication                     |

## Circuit Diagram

```
                    ATmega32
                   ┌─────────────┐
    IR Sensor ────-┤PD2 (INT0)   │
   Control Sig ────┤PD3 (INT1)   │
                   │             │
    LCD D4-D7 ─────|PD4-PD7      │
    LCD RS ────────|PC6          │
    LCD EN ────────|PC7          │
                   │             │
    Analog In ─────|PC0 (ADC0)   │
                   │             │
    Motor PWM ─────|PB3 (OC0)    │
    Status LEDs ───|PB0-PB1      │
                   │             │
    16MHz Crystal ─|XTAL1/XTAL2  │
                   └─────────────┘
```

## Software Requirements

- **Atmel Studio** (or AVR-GCC toolchain)
- **AVR Programmer**: Arduino
- **avrdude** for hex file uploading

## Setup Instructions

### 1. Hardware Assembly

1. Connect the LCD display to the specified pins (4-bit mode)
2. Connect IR sensor to PD2 (INT0) with pull-up resistor
3. Connect control signal to PD3 (INT1) with pull-up resistor
4. Connect analog input to PC0 (ADC0)
5. Connect motor to PWM output (PB3) through appropriate driver circuit
6. Connect status LEDs to PB0 and PB1
7. Ensure proper power supply connections (VCC, GND)

### 2. Software Compilation

1. Open the project in Atmel Studio
2. Ensure the `lcd.h` library is included in your project
3. Set the target device to ATmega32 (or your specific AVR)
4. Build the project (Build → Build Solution)

### 3. Programming the Microcontroller

#### Using Atmel Studio:

1. Connect your programmer to the AVR
2. Go to Tools → Device Programming
3. Select your programmer and device
4. Load the generated hex file
5. Program the device

### Required LCD Library Header (lcd.h)

_Note: You'll need to create or obtain the `lcd.h` library file. Here's a basic template:_

```c
#ifndef LCD_H_
#define LCD_H_

#define eS_PORTD4 4
#define eS_PORTD5 5
#define eS_PORTD6 6
#define eS_PORTD7 7
#define eS_PORTC6 6
#define eS_PORTC7 7

// Function prototypes
void Lcd4_Init(void);
void Lcd4_Set_Cursor(char row, char col);
void Lcd4_Write_String(char *str);
void Lcd4_Write_Char(char data);
void Lcd4_Clear(void);

#endif /* LCD_H_ */
```

### Control Features

- **Automatic Speed Control**: When RPM exceeds 380, PWM duty cycle resets to maintain speed
- **Interrupt-based Counting**: External interrupt on INT0 counts each revolution
- **Timer-based Calculation**: Timer1 triggers RPM calculation every second

## Troubleshooting

### Common Issues

1. **No Display**: Check LCD connections and power supply
2. **Incorrect RPM Reading**: Verify RPM sensor wiring and pull-up resistor
3. **No PWM Output**: Check Timer0 configuration and pin connections
4. **ADC Not Working**: Verify AVCC connection and ADC pin wiring

### Debug Tips

- Use multimeter to verify power supply voltages
- Verify interrupt pin states with LED indicators
- Monitor PWM output with oscilloscope

## Demo

You can find the demonstration in this link:
https://www.youtube.com/watch?v=2P7i6D3QxLc
