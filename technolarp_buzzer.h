#include <Arduino.h>

#define _TASK_OO_CALLBACKS
#include <TaskSchedulerDeclarations.h>

class M_buzzer : public Task
{
  private:
  uint16_t buzzerPin;
  bool activeBuzzer;
  uint16_t frequency;
  //unsigned long int startBeep;

  
  
  public:  
  M_buzzer(int buzzerPinSet, Scheduler* aScheduler);
  
  void buzzerOn(uint16_t frequency);
  void buzzerOff();
  
  void shortBeep();
  void doubleBeep();
  void tripleBeep();
  void longBeep();
  
  bool Callback();
  bool OnEnable();
  void OnDisable();  
};