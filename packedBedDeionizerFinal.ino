
//Add the MegunoLink library for real time data collection
#include "MegunoLink.h"

//Create plots for salinity and pressure differential
TimePlot Salinity;
TimePlot PressureDifferential;

// Define variable names for the Arduino pins
//int freshPump = 4;
//int brackishPump = 5;
int gaugePower = 7;
int salinityPower = 6;
int salinityProbe = A0;
int pressureGaugeTop = A1;
int pressureGaugeBottom = A2;

//salinity variables
int cycleCount = 0;
float maxADC = 1023.0;
float probeValue = 0.0;
float salinityVoltage;
float salinityThreshold = 3.8;

//pressure variables
float psi0MV = 500.0;
float psi30MV = 4500.0;
float rangeADCMV = 5000.0;
float pressureGaugeTopValue = 0.0;
float pressureGaugeBottomValue = 0.0;
float pressureGaugeTopVoltage = 0.0;
float pressureGaugeBottomVoltage = 0.0;
float pressureDifferential = 0.0;
float pressureConversionPSI = 0.0;
float pressureConversionKPA = 0.0;

//pump variables
//boolean switchPump = false;


void setup() {
  // Set the pump pins as output pins
  //pinMode(freshPump, OUTPUT);
  //pinMode(brackishPump, OUTPUT);
  pinMode(salinityPower, OUTPUT);
  pinMode(gaugePower, OUTPUT);
  // Begin serial connection at 9600 baud
  Serial.begin(9600);
}

void loop() {
  // Write a logic high to the salinity probes power pin
  if(cycleCount > 100){
    digitalWrite(salinityPower, LOW);
    cycleCount = 0;
  }
  else
   digitalWrite(salinityPower, HIGH);

   
  // Read in salinity value
  probeValue = analogRead(salinityProbe);
  salinityVoltage = probeValue * (5.0 / maxADC);

  
  // Read in pressure gauge values
  digitalWrite(gaugePower, HIGH);
  pressureGaugeTopValue = analogRead(pressureGaugeTop);
  pressureGaugeBottomValue = analogRead(pressureGaugeBottom);
  pressureGaugeTopVoltage = pressureGaugeTopValue * (4.0 / maxADC);
  pressureGaugeBottomVoltage = pressureGaugeBottomValue * (4.0 / maxADC);
  pressureDifferential = abs(pressureGaugeBottomVoltage) - abs(pressureGaugeTopVoltage);
  pressureConversionPSI = pressureDifferential * 0.0075;
  pressureConversionKPA = pressureConversionPSI * 6.895;
  


  // Checks to see if the salinity threshold has been reached
  //if (salinityVoltage < salinityThreshold) {
    //switchPump = true;
  //}
  //else
    //switchPump = false;

  // Checks to see if the pumps need to be switched
  //if (switchPump == true) {
    //digitalWrite(brackishPump, LOW);
    //digitalWrite(freshPump, HIGH);
  //}
  //else
    //digitalWrite(freshPump, LOW);
    //digitalWrite(brackishPump, HIGH);

  // Send values through serial connection to computer
  //delay(1000);
  //if (switchPump == true) {
    //Serial.print("The freshwater pump is in use");
    //Serial.print('\n');
  //}
  //else
    //Serial.print("The brackish pump is in use");
    //Serial.print('\n');
    delay(1000);
    Serial.print("The salinity voltage is ");
    Serial.print(salinityVoltage);
    Serial.print('\n');

    Serial.print("The pressure differential is ");
    Serial.print(pressureDifferential);
    Serial.print('\n');
   
  // Increase cycle count for salinity probe power  
    cycleCount ++;
  //Send values to MegunoLink timeplots  
    PressureDifferential.SendData("Pressure Differential", pressureDifferential);
    Salinity.SendData("Salinity Voltage", salinityVoltage);

}
