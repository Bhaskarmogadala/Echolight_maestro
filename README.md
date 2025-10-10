# EcoLight Maestro – Time & Intensity Adaptive Street Light Automation

# Overview :
EcoLight Maestro is an embedded system designed to automatically control streetlights based on both **time** and **ambient light intensity**.  
It ensures efficient power management by turning lights **ON/OFF** according to real-time conditions, reducing energy waste in urban areas.

## Objective :
The main objective of this project is to **automate streetlight operation** using:
  1.**Fixed time schedules** (through the on-chip RTC)
  2.**Real-time light intensity measurement** (via LDR and ADC)
  
## System Workflow
1. The system initializes peripherals such as:
   - **LCD Display**
   - **LEDs**
   - **Keypad**
   - **RTC (Real-Time Clock)**
   - **ADC (for LDR input)**
   - **External Interrupts**
2. The RTC continuously provides the **current time and date** on the LCD.
3. Between **6 PM and 6 AM**, the system monitors the **ambient light intensity**:
   - If light level < threshold → LEDs (streetlights) **turn ON**
   - If light level ≥ threshold → LEDs **remain OFF**
4. At other times, the system only displays time/date info.

##  User Interaction :
If the RTC time becomes inaccurate, the user can:
- Press a switch to generate an **interrupt**
- Access a menu on the LCD:
  1. **Edit RTC Info**
  2. **Exit**
- When editing:
  - Modify hours, minutes, seconds, date, month, year
  - Validation checks ensure all inputs are within valid ranges
  - Invalid entries show an error and prompt retry
- After successful update, the system returns to main operation.

##  Hardware Requirements :
- **LPC2148 (ARM7 microcontroller)**
- **LCD Display**
- **Keypad**
- **LEDs (Streetlights)**
- **LDR Sensor**
- **Buzzer**
- 
## Software Requirements :
- **Embedded C programming**
- **Keil µVision (C compiler)**
- **Flash Magic (for microcontroller flashing)**

##  Features :
- Real-time light intensity sensing  
- Time-based automatic switching  
- RTC editing via keypad interface  
- LCD status display  
- Efficient power-saving operation  

## Tools and Technologies
- Language: **Embedded C**
- Compiler: **Keil µVision**
- Hardware Platform: **LPC2148 (ARM7)**
- Flashing Tool: **Flash Magic**

## Future Enhancements :
- Integrate IoT module for remote monitoring  
- Add motion sensor for smart dimming  
- Implement cloud-based data logging  

## Author :
**Bhaskara Rao Mogadala**  
Embedded Systems Developer  

