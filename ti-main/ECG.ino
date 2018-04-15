volatile unsigned i = 0;

void timer_func()
{
  if(i < 150)
    {
      if(digitalRead(LOp) == 0 && digitalRead(LOn) == 0)
      {
        ECG::raw[i] = analogRead(A_pin);
        i++;
      }
    }
    else
    {
      i = 0;
      volatile unsigned *tmp = ECG::raw;
      ECG::raw = ECG::raw_swap;
      ECG::raw_swap = ECG::raw;
      EventOverload.send();
    }
}

Timer *analogT = new Timer();
volatile bool old_state = false;
volatile unsigned  old_fill_mks;

void setup_ECG()
{
  pinMode(LOp, INPUT);
  pinMode(LOn, INPUT);

  analogT->begin(timer_func, fill_mks, 1);
  analogT->start();
  old_fill_mks = fill_mks;
}

void loop_ECG()
{
  if(old_fill_mks != fill_mks)
  {
    delete analogT;
    analogT = new Timer();
    analogT->begin(timer_func, fill_mks, 1);
    old_fill_mks = fill_mks;
    ECG::enable = true;
    old_state   = true;
    analogT->start();
  }
  
  if(ECG::enable != old_state)
  {
    if(ECG::enable)
    {
      analogT->start();
    }
    else
    {
      analogT->stop();
    }
    old_state = ECG::enable;
  }
  else
  {
    sleep(1000);
  }
}

