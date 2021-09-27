#include "technolarp_buzzer.h"

M_buzzer::M_buzzer(int buzzerPinSet, Scheduler* aScheduler) : Task(TASK_MILLISECOND*1000, TASK_FOREVER, aScheduler, false)
{
	buzzerPin = buzzerPinSet;
	
	pinMode(buzzerPin, OUTPUT);
	digitalWrite(buzzerPin, LOW);

  activeBuzzer=false;
  frequency=1000;
  //unsigned long int startBeep = 0;
}

void M_buzzer::buzzerOn(uint16_t frequency)
{
  analogWrite(buzzerPin, frequency);
}

void M_buzzer::buzzerOff()
{
  analogWrite(buzzerPin, 0);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);
}

void M_buzzer::beep(uint16_t freq, uint16_t interval, uint16_t iterations)
{
  frequency=freq;
  setInterval(interval);
  setIterations(iterations);

  activeBuzzer=true;
    
  enable();
  forceNextIteration();
}

void M_buzzer::shortBeep()
{
  frequency=1000;
  setInterval(50);
  setIterations(2);

  activeBuzzer=true;
    
  enable();
  forceNextIteration();
}

void M_buzzer::doubleBeep()
{
  frequency=1000;
  setInterval(50);
  setIterations(4);

  activeBuzzer=true;
    
  enable();
  forceNextIteration();
}

void M_buzzer::tripleBeep()
{
  frequency=800;
  setInterval(100);
  setIterations(6);

  activeBuzzer=true;
    
  enable();
  forceNextIteration();
}

void M_buzzer::longBeep()
{
  frequency=500;
  setInterval(400);
  setIterations(2);

  activeBuzzer=true;
    
  enable();
  forceNextIteration();
}


bool M_buzzer::Callback()
{
  //Serial.print("callback beep: ");
  //Serial.println(activeBuzzer);

  if (activeBuzzer)
  {
    buzzerOn(frequency);
  }
  else
  {
    buzzerOff();
  }
  activeBuzzer=!activeBuzzer;
  return true;
}

bool M_buzzer::OnEnable()
{
  //Serial.println("shortbeep enable");
  return true;
}

void M_buzzer::OnDisable()
{
  //Serial.println("shortbeep disable: ");
  //Serial.println(millis()-startBeep);
}
