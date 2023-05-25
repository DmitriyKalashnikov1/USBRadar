#include <Servo.h>
#include <Ultrasonic.h>
// используем библиотеку сервы и библиотеку для ультразвукового датчика

uint8_t exo_pin = 5;   //  пин приемника УЗ датчика
uint8_t trig_pin = 6;  // пинговый пин УЗ датчика

uint8_t servo_pin = 4;  // пин сервы

int app_delay = 500;  // задержка необходимая для работы настольной программы-визулизотра (обнулить при отсутствии таковой)

Ultrasonic sensor(trig_pin, exo_pin);  // объект управляющий датчиком
Servo servo;                           // объект сервы

uint8_t max_angle = 180;  // максимальный угол поворота сервы

void setup() {
  Serial.begin(9600);       // открываем serial-port
  servo.attach(servo_pin);  // настраиваем серву
  servo.write(0);           // сброс в ноль положения сервы после включения
}

void loop() {
  /* алгоритм работы:
  вращаем серву в прямом и обратном направлении на max_angle, 
  при каждом угле снимаем расстояние в см и отправляем в serial вместе с углом
  */
  for (int angle = 0; angle <= max_angle; angle++) {
    servo.write(angle);
    Serial.print(angle);
    Serial.print(",");
    Serial.println(sensor.read());
    delay(app_delay);
  }
  for (int angle = max_angle; angle > 0; angle--) {
    servo.write(angle);
    Serial.print(angle);
    Serial.print(",");
    Serial.println(sensor.read());
    delay(app_delay);
  }
}
