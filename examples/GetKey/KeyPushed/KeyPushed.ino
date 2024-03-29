// ДАННЫЙ ПРИМЕР ФИКСИРУЕТ НАЖАТИЕ КНОПКИ:        //   При каждом нажатии кнопки, будет включаться светодиод на плате Arduino.
// (ТОЛЬКО ДЛЯ ВЕРСИИ ДЖОЙСТИКА С КНОПКОЙ)        // * Строки со звёздочкой являются необязательными.
                                                  //
#include <Wire.h>                                 // * Подключаем библиотеку для работы с аппаратной шиной I2C.
#include <iarduino_I2C_Joystick.h>                //   Подключаем библиотеку для работы с джойстиком I2C-flash.
iarduino_I2C_Joystick joy(0x09);                  //   Объявляем объект joy для работы с функциями и методами библиотеки iarduino_I2C_Joystick, указывая адрес модуля на шине I2C.
                                                  //   Если объявить объект без указания адреса (iarduino_I2C_Joystick joy;), то адрес будет найден автоматически.
void setup(){                                     //
    delay(500);                                   // * Ждём завершение переходных процессов связанных с подачей питания.
    pinMode(LED_BUILTIN, OUTPUT);                 //   Конфигурируем вывод к которому подключён светодиод на плате Arduino в режим работы на выход.
    joy.begin();                                  //   Инициируем работу с джойстиком.
}                                                 //
                                                  //
void loop(){                                      //
//  Фиксируем событие нажатия кнопки:             //
    if( joy.getButton(KEY_PUSHED) ){              //   Если кнопка джойстика нажимается, то ...
        digitalWrite(LED_BUILTIN, HIGH);          //   Включаем светодиод на плате Arduino.
        delay(100);                               //   Даём светодиоду светиться 100 мс, чтоб мы его заметили.
    }                                             //
    digitalWrite(LED_BUILTIN, LOW);               //   Отключаем светодиод на плате Arduino.
}                                                 //