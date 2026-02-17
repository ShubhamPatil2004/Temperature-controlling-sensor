

// Segment pins
int segPins[7] = {2,3,4,5,6,7,8};

//Digit select pins
int digitTens  = 9;
int digitUnits = 10;

//Sensor 
#define LM35 A0


byte numbers[10] = {
  B11000000, //0
  B11111001, //1
  B10100100, //2
  B10110000, //3
  B10011001, //4
  B10010010, //5
  B10000010, //6
  B11111000, //7
  B10000000, //8
  B10010000  //9
};

//Display one digit 
void showDigit(int num)
{
  for(int i=0;i<7;i++)
    digitalWrite(segPins[i], bitRead(numbers[num],i));
}

//Multiplex display 
void displayNumber(int num)
{
  int tens  = num/10;
  int units = num%10;

  // Tens
  digitalWrite(digitTens, LOW);
  digitalWrite(digitUnits, HIGH);
  showDigit(tens);
  delay(4);

  // Units
  digitalWrite(digitTens, HIGH);
  digitalWrite(digitUnits, LOW);
  showDigit(units);
  delay(4);
}

//Read temperature (stable) 
int readTemperature()
{
  long sum = 0;

  // average 20 samples
  for(int i=0;i<20;i++)
  {
    sum += analogRead(LM35);
    delay(2);
  }

  float adc = sum / 20.0;
  float voltage = adc * (5.0/1023.0);
  int temp = voltage * 100.0;

  if(temp > 99) temp = 99;
  if(temp < 0) temp = 0;

  return temp;
}


void setup()
{
  for(int i=0;i<7;i++)
    pinMode(segPins[i], OUTPUT);

  pinMode(digitTens, OUTPUT);
  pinMode(digitUnits, OUTPUT);

  pinMode(LM35, INPUT);
}


void loop()
{
  int temperature = readTemperature();

  // continuously refresh display
  for(int i=0;i<120;i++)
    displayNumber(temperature);
}
