int16_t ADCvalue;

void setup(){
  Serial.begin(9600);
}

void loop() {
  ADCvalue = analogRead(A0);
  Thermistor(ADCvalue);
}
void Thermistor(int16_t ADCvalue)
{
  double T, Temp;
  double T0 = 301.15;  // 273.15 + 28 (room temperature) 室溫換成絕對溫度
  double lnR;
  int16_t R;          // Thermistor resistence 
  int16_t R0 = 8805;  // calibrated by reading R at room temperature (=28 degree Celsius )
  int16_t B  = 3950;
  int16_t Pullup = 9930;
  //double V;
  double ReadVoltage(byte pin){
  double Reading = analogRead(pin); // Reference voltage is 3v3 so maximum reading is 3v3 = 4095 in range 0 to 4095
  if(Reading < 1 || Reading > 4095) return 0;
  return -0.000000000000016 * pow(Reading,4) + 0.000000000118171 * pow(Reading,3)- 0.000000301211691 * pow(Reading,2)+ 0.001109019271794 * Reading + 0.034143524634089;
  }
  V = ReadVoltage(A0); // ADC accuracy improved for ESP32
  R = (Pullup * ADCvalue) / (4096 - ADCvalue);

  V = ReadVoltage(A0);
  R = 9990 * V / (5 - V); // assuming 9990 is the measured resistance of 10K resistor by a multi-meter.
  T = 1 / (1/T0 + (log(R)-log(R0)) / B ); // R0=8805 measured in room tempature at 28 celsius degree.
  Temp = T - 273.15;

Serial.println(Temp);
}
