## README: 100kHz Closed-Loop Boost Converter Simulation

This project implements a digitally controlled **DC-DC Boost Converter** using an **ATmega328P** (Arduino Uno) in a Proteus simulation environment. The system uses high-frequency PWM and a PI control algorithm to maintain a stable output voltage based on user input.

---

### ### Technical Specifications
* **Microcontroller:** ATmega328P (Arduino Uno)
* **Switching Frequency:** $100\text{kHz}$ (Custom Timer 2 implementation)
* **Input Voltage ($V_{in}$):** $12\text{V}$ DC
* **Output Voltage Range ($V_{out}$):** Adjustable $12\text{V}$ to $35\text{V}$
* **Control Method:** Proportional-Integral (PI) Feedback Loop
* **Efficiency Features:** High-speed switching to minimize inductor size and output ripple.

---

### ### Component Configuration
| Component | Value/Model | Role |
| :--- | :--- | :--- |
| **Inductor (L1)** | $4.2\text{mH}$ | Energy storage during the "ON" cycle. |
| **MOSFET (Q1)** | IRFZ44N | High-speed switching element. |
| **Diode (D2)** | 6A10 | Prevents reverse current during the "OFF" cycle. |
| **Capacitor (C1)** | $47\mu\text{F}$ | Output smoothing/filtering. |
| **Voltage Divider** | $10\text{k}\Omega$ / $1\text{k}\Omega$ | Scales $V_{out}$ to $0-5\text{V}$ for ADC Pin A0. |

---

### ### Simulation & Operation
1.  **Voltage Control:** Adjust the **Potentiometer (A1)** to set the desired target voltage.
2.  **Feedback Loop:** The Arduino reads the actual output via **A0**. If the voltage drops due to load, the PI algorithm increases the duty cycle on **Pin 3**.
3.  **Monitoring:** * **Virtual Terminal:** Displays real-time Target Voltage, Measured Voltage, and Duty Cycle percentage.
    * **Voltmeter:** Displays the steady-state DC output.

---

### ### Safety & Optimization Notes
* **Duty Cycle Limit:** The code clamps the PWM to a maximum of **85%** to prevent inductor saturation and MOSFET failure.
* **Gate Driving:** For physical implementation, a logic-level MOSFET or a gate driver (e.g., TC4427) is recommended to handle the $100\text{kHz}$ switching speed efficiently.
* **Soft Start:** The PI controller naturally ramps the voltage to prevent high inrush currents upon startup.

---

Would you like me to generate a **Bill of Materials (BOM)** for this circuit so you can estimate the cost of building it physically?
