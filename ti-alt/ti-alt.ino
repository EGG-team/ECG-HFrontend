namespace ECG
{
  volatile unsigned *raw      = new unsigned[125];
  volatile unsigned *raw_swap = new unsigned[125];
  volatile bool     enable    = true;
  const int LOp   = P3_5;
  const int LOn   = P3_6;
  const int A_pin = A7;
  unsigned  fill_mks = 100;
};

void setup()
{
    Serial.begin(9600);
    pinMode(ECG::LOp, INPUT);
    pinMode(ECG::LOn, INPUT);

}

void sendSwap()
{
  Serial.println("ARR-START");
  for(int k = 0; k < 150; k++)
  {
    Serial.println(ECG::raw_swap[k]);
  }
  Serial.println("ARR-END");
}

volatile unsigned i = 0;

void timer_func()
{
  if(i < 150)
    {
      if(digitalRead(ECG::LOp) == 0 && digitalRead(ECG::LOn) == 0)
      {
        ECG::raw[i] = analogRead(ECG::A_pin);
        i++;
      }
    }
    else
    {
      i = 0;
      volatile unsigned *tmp = ECG::raw;
      ECG::raw = ECG::raw_swap;
      ECG::raw_swap = tmp;
      sendSwap();
    }
}

char last_sym = '\0';

void loop()
{
  if(Serial.available())
  {
    char tok = Serial.read();
    if(last_sym == 'F')
    {
      last_sym = '\0';
      ECG::fill_mks = (unsigned)tok;
    }
    switch(tok)
    {
      case 'E':
        last_sym = 'E';
        Serial.println("OK");
        break;
      case 'Y':
        if(last_sym == 'E')
        {
         last_sym == '\0';
         ECG::enable = true; 
         Serial.println("OK");
        }
        break;
      case 'N':
        if(last_sym == 'E')
        {
         last_sym == '\0';
         ECG::enable = false; 
         Serial.println("OK");
         break;
        }
      case 'F':
        if(last_sym == 'E')
         {
           last_sym == 'F';
           Serial.println("OK");
           break;
         }
      
        
    }
  }
  if(ECG::enable)
  {
    timer_func();
    delayMicroseconds(ECG::fill_mks);
  }
}

