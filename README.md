README: 100kHz Closed-Loop Boost Converter Simulation

This project implements a digitally controlled *DC-DC Boost Converter* using an *ATmega328P* (Arduino Uno) in a Proteus simulation environment. The system uses high-frequency PWM and a PI control algorithm to maintain a stable output voltage based on user input.

Technical Specifications
* Microcontroller: ATmega328P (Arduino Uno)
* *Switching Frequency:* 100kHz (Custom Timer 2 implementation)
* *Input Voltage (V_in): 12V DC
* *Output Voltage Range (V_out):* Adjustable 12V to 35V
* *Control Method:* Proportional-Integral (PI) Feedback Loop
* *Efficiency Features:* High-speed switching to minimize inductor size and output ripple.

Component Configuration
| Component | Value/Model | Role |
| :--- | :--- | :--- |
| **Inductor (L1)** | 4.2mH | Energy storage during the "ON" cycle. |
| **MOSFET (Q1)** | IRFZ44N | High-speed switching element. |
| **Diode (D2)** | 6A10 | Prevents reverse current during the "OFF" cycle. |
| **Capacitor (C1)** | 47μF | Output smoothing/filtering. |
| **Voltage Divider** | 10k 1k | Scales V_out to 0-5V for ADC Pin A0. |


Simulation & Operation
1.  **Voltage Control:** Adjust the **Potentiometer (A1)** to set the desired target voltage.
2.  **Feedback Loop:** The Arduino reads the actual output via **A0**. If the voltage drops due to load, the PI algorithm increases the duty cycle on **Pin 3**.
3.  **Monitoring:** * **Virtual Terminal:** Displays real-time Target Voltage, Measured Voltage, and Duty Cycle percentage.
    * **Voltmeter:** Displays the steady-state DC output.

### ### Safety & Optimization Notes
* **Duty Cycle Limit:** The code clamps the PWM to a maximum of **85%** to prevent inductor saturation and MOSFET failure.
* **Gate Driving:** For physical implementation, a logic-level MOSFET or a gate driver (e.g., TC4427) is recommended to handle the 100kHz switching speed efficiently.
* **Soft Start:** The PI controller naturally ramps the voltage to prevent high inrush currents upon startup.
