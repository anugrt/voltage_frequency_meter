# voltage_frequency_meter

OBJECTIVE
• To design a digital voltmeter by using Arduino.
• To measure the input voltage range between 0 to 10VPP by using voltage divider.
• To measure the frequency of a signal.
• To implement switching between channels with the help of Demux.
• Know how Arduino works and how easy it is to use it.

DESIGN AND IMPLEMENTATION

Following are the functionalities of our device:
 Firstly it could generate a PWM signal when the 00 is entered to the serial monitor. This is done by making the digital pin 9 of Arduino Uno high. The baud rate is always kept 9600. The below figure represents the output that we get by generating the PWM waveform. ThemArduino can generate a PWM waveform ranging from 0 to 5V. In this case we have made the duty cycle 12% , and the values that we see as output from the serial monitor holds precision. We have used digital pin 9 to generate PWM wave form.The Arduino's programming
language makes PWM easy to use; simply call analogWrite(pin, dutyCycle), where dutyCycle is a value from 0 to 255, and pin is one of the PWM pins (3, 5, 6, 9, 10, or 11). The analogWrite() function provides a simple interface to the hardware PWM, but doesn't provide any control over frequency.

Secondly, it could read the voltage of an analog signal which is in the range of 10 Vpp when 01 is entered. This is made possible by analog read function of arduino where the analog pins reads the voltage by 10 bit ADC converter. In general case the Arduino analogRead () can only read voltages between 0 and 5 V. But here we have used a three resisitor styled voltage divider in the ratio 1:2:2. This maps the -10V to 0V and +10V to 5V respectively.

Thirdly, this device of ours also measures the frequency, this is enabled by inputting 10
to the serial monitor. The frequency is measured at the digital pin 2 of arduino . So the input to
Analog pin 2 and digital pin 2 are interconnected. Meanwhile we have made the digital pin 9
LOW since both the frequencies of PWM (pin 9) and the measuring frequency is connected to
it. 
Apart from all these the selection process is done with the help of a demux. We have used
a 16 channeled demux but has only made use of three channels. Selection lines S0 and S1 are
connected to respective digital pins and the rest two selection pins are grounded. Our options
like 00, 01, 10 are the three channels C0, C1, C2 of demux respectively. In the figure below we
have basically switched between the channels of the demux to glow the led corresponding to
channel 00.


