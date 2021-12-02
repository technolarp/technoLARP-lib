#include <Arduino.h>

class M_buzzer
{
  private:
  uint8_t buzzerPin;
  
  bool buzzerActif;
  bool statutBuzzer;
  uint16_t iterations;
  uint16_t frequency;
  
  uint16_t interval;
  uint32_t previousMillis;
  
  
  public:  
  M_buzzer(uint8_t buzzerPinSet);
  
  void update();
  
  void buzzerOn(uint16_t frequency);
  void buzzerOn();
  void buzzerOff();
  
  void shortBeep();
  void doubleBeep();
  void tripleBeep();
  void longBeep();
  //void beep(uint16_t freq, uint16_t interval, uint16_t iterations);
};
