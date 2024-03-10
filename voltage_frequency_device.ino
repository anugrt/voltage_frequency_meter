#define s0 3
#define s1 4
const int pwmPin = 9;  
const int inputPin = 2; // The pin to measure the PWM signal(00)  &   Digital pin connected to the function generator(11)

const int pwmReadPin = A0;
unsigned long startTime = 0; // Variable to store the start time of the cycle
unsigned long timePeriod = 0;
int tONtime;
int tOFFtime;
float period;
float frequency;
float dutycycle;
float readVal;
volatile unsigned long pulseStartTime = 0; // Global variable to store the pulse start time
volatile unsigned long pulseEndTime = 0; // Global variable to store the start time
//volatile unsigned long endTime = 0;
volatile bool pulseStarted = false;
const int analogPin1 = A1;   // Analog pin connected to the FG output
const int analogPin2 = A2;   // Analog pin connected to the range of 20vpp
//const int analogPin3 = A3;   // Analog pin connected to the FG output to find the frequency







void pwmfunctions(){
  tONtime=pulseIn(pwmPin,HIGH);
  tOFFtime=pulseIn(pwmPin,LOW);
  period=tONtime+tOFFtime;
  frequency=1000000.0/period;
  dutycycle=(tONtime/period)*100;

  int pwmValue = analogRead(pwmReadPin);
  float voltage = pwmValue*(5.0 / 1023.0);
   Serial.print("PWM Voltage: ");
      Serial.print(voltage,2);
      Serial.println("V");
      Serial.print("Time Period: ");
      Serial.print(period,6);
      Serial.println("micro seconds");
    
    // Print the frequency to the Serial Monitor
    Serial.print("Frequency: ");
    Serial.print(frequency);
    Serial.println(" Hz");

    Serial.print("T ON: ");
    Serial.print(tONtime,6);
    Serial.println("micro seconds");
    Serial.print("T OFF: ");
    Serial.print(tOFFtime,6);
    Serial.println("micro seconds");

    Serial.print("Duty Cycle:");
    Serial.print(dutycycle);
    Serial.print("%");

  }


void tenvppfunctions(){

  int rawValue = analogRead(analogPin1);  // Read raw analog value
  float volt_ten_age = (rawValue / 1023.0) * 5.0;  // Convert raw value to voltage (assuming 5V reference)
      Serial.print("Voltage (values within 10 Vpp): ");
      Serial.println(volt_ten_age,2);
      Serial.println("V");
  delay(100);  // Delay for 100 milliseconds
}





//void twenty_vppfunctions(){

  //int raWValue = analogRead(analogPin2);  // Read raw analog value
  //float volt_twen_age = (raWValue / 1023.0) * 5.0;  // Convert raw value to voltage (assuming 5V reference)
      //Serial.print("Voltage (values within 20 Vpp): ");
      //Serial.println(volt_twen_age,2);
      //Serial.println("V");
  //delay(100);  // Delay for 100 milliseconds
//}




void fg_frequency(){
  int count = 0;
  unsigned long startTIme = micros();  // Get the starting time
  int rawValUe = analogRead(analogPin2);  // Read raw analog value
  float voltaGe = (rawValUe / 1023.0) * 5.0;  // Convert raw value to voltage (assuming 5V reference)

  //Serial.print(rawValue);
  //Serial.print(",");
   Serial.print("VOLTAGE: ");
  Serial.println(voltaGe);
  Serial.println(" V");

  while (micros() - startTime < 1000000) {  // Measure the signal for 1 second
    if (digitalRead(inputPin) == HIGH) {
      count++;
      while (digitalRead(inputPin) == HIGH) {
        // Wait until the signal goes low again
      }
    }
  }

  float frequency = count / 1.0;  // Calculate the frequency
  Serial.print("Frequency: ");
  Serial.print(frequency);
  Serial.println(" Hz");
  delay(1000);  // Delay for 1 second before measuring again


}


void setup() {
  Serial.begin(9600);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);

   pinMode(pwmPin, OUTPUT);//pin 9
   pinMode(pwmReadPin, INPUT); //A0 pin
   analogWrite(pwmPin, 64);//generate pwm with 25% dutycycle
   pinMode(inputPin, INPUT);//pin 2
   pinMode(analogPin1, INPUT);//A1 pin
   pinMode(analogPin2, INPUT);//A2 pin

   Serial.print("Select your options :");
   Serial.print("Press 00 to generate PWM");
   Serial.print("Press 01 to measure voltage  the range of 10VPP");
   //Serial.print("Press 10 to measure voltage the range of 20VPP");
   Serial.print("Press 10 to measure the frequency(Ensure that the voltage range is b/w 10 Vpp) ");

  delay(500);

}



void loop() {

int laststate1 = LOW;
int laststate2 = LOW;

int b = 1;
while(b!=0){
//digitalWrite(s0,LOW);
//digitalWrite(s1,LOW);
  Serial.print("please enter your option:");
  while (Serial.available()==0){
  }
    
    String num = Serial.readString();
    if (num.equals("00")){
    digitalWrite (s0,LOW);
    digitalWrite (s1,LOW);
     laststate1 = LOW;
    laststate2 = LOW;
    Serial.println("Generate PWM");

  pwmfunctions();

    delay(500);
    //while(1){}
    }
     else if(num.equals("01")){
    digitalWrite (s0,HIGH);
    digitalWrite (s1,LOW);
    laststate1 = HIGH;
    laststate2 = LOW;
    digitalWrite(9, LOW);
    Serial.println(" To find Voltage of signal in range of 10Vpp");
    tenvppfunctions();
    delay(500);
    // while(1){}
    }
    else if (num.equals("10")){
    digitalWrite (s0,LOW);
    digitalWrite (s1,HIGH);
    laststate1 = LOW;
    laststate2 = HIGH;
    digitalWrite(9, LOW);
    Serial.println("Frequency ");
    fg_frequency();
    delay(500);
     //while(1){}

    }
     //else if (num.equals("11")){
    //digitalWrite (s0,HIGH);
    //digitalWrite (s1,HIGH);
    //laststate1 = HIGH;
    //laststate2 = HIGH;
    //digitalWrite(9, LOW);
    //Serial.println("Frequency");
    //fg_frequency(); //b/w 10vpp
    //delay(500);
    

     //while(1){}
    //}
    else
    Serial.println("Please specify the correct option");
    delay(500); 


}
}

