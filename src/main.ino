#include <Arduino.h>
#include <GyverPower.h>

#define MOTOR 2          // PIN мотора
#define DETECTOR_EN 3    // Сигнал на включение детектора
#define DETECTOR_SIG 4   // Сигнал с детектора рук
#define SPRAY_TIME 400   // 700ms
#define SLEEP_DELAY 2500 // Время сна МК

int empty;

void setup()
{
  pinMode(MOTOR, OUTPUT);
  pinMode(DETECTOR_EN, OUTPUT);
  pinMode(DETECTOR_SIG, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  power.autoCalibrate();
  power.hardwareDisable(PWR_ADC | PWR_I2C | PWR_SPI);

  power.setSystemPrescaler(PRESCALER_2);
  power.setSleepMode(POWERDOWN_SLEEP);
}

void loop()
{
  digitalWrite(DETECTOR_EN, HIGH);
  delay(50); // задержка, т.к. сразу после просыпания идентифицирует "руки"
  empty = digitalRead(DETECTOR_SIG);
  digitalWrite(DETECTOR_EN, LOW);
  if (empty == 1)
  {
    power.sleepDelay(SLEEP_DELAY);
    return;
  }

  if (empty == 0)
  {
    runDispancer();
  }
}

void runDispancer()
{
  digitalWrite(MOTOR, HIGH);
  delay(SPRAY_TIME);
  digitalWrite(MOTOR, LOW);
  delay(SLEEP_DELAY);
}