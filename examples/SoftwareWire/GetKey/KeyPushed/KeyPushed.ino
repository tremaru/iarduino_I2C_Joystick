// ДАННЫЙ ПРИМЕР ФИКСИРУЕТ НАЖАТИЕ КНОПКИ:                   //   При каждом нажатии кнопки, будет включаться светодиод на плате Arduino.
// (ТОЛЬКО ДЛЯ ВЕРСИИ ДЖОЙСТИКА С КНОПКОЙ)                   // * Строки со звёздочкой являются необязательными.
                                                             //
// Требуется установить библиотеку <iarduino_I2C_Software.h> //   https://iarduino.ru/file/627.html
                                                             //
// Джойстик, FLASH-I2C (Trema-модуль):                       //   https://iarduino.ru/shop/Expansion-payments/dzhoystik-i2c---flash-trema-modul.html
// Информация о подключении модулей к шине I2C:              //   https://wiki.iarduino.ru/page/i2c_connection/
// Информация о модуле и описание библиотеки:                //   https://wiki.iarduino.ru/page/joystick-i2c/
                                                             //
#include <iarduino_I2C_Software.h>                           //   Подключаем библиотеку для работы с программной шиной I2C, до подключения библиотеки iarduino_I2C_Joystick.
SoftTwoWire sWire(3,4);                                      //   Создаём объект программной шины I2C указав выводы которым будет назначена роль линий: SDA, SCL.
                                                             //
#include <iarduino_I2C_Joystick.h>                           //   Подключаем библиотеку для работы с джойстиком I2C-flash.
iarduino_I2C_Joystick joy(0x09);                             //   Объявляем объект joy для работы с функциями и методами библиотеки iarduino_I2C_Joystick, указывая адрес модуля на шине I2C.
                                                             //   Если объявить объект без указания адреса (iarduino_I2C_Joystick joy;), то адрес будет найден автоматически.
void setup(){                                                //
    delay(500);                                              // * Ждём завершение переходных процессов связанных с подачей питания.
    pinMode(LED_BUILTIN, OUTPUT);                            //   Конфигурируем вывод к которому подключён светодиод на плате Arduino в режим работы на выход.
    joy.begin(&sWire);                                       //   Инициируем работу с джойстиком, указав ссылку на объект для работы с шиной I2C на которой находится джойстик (по умолчанию &Wire).
}                                                            //
                                                             //
void loop(){                                                 //
//  Фиксируем событие нажатия кнопки:                        //
    if( joy.getButton(KEY_PUSHED) ){                         //   Если кнопка джойстика нажимается, то ...
        digitalWrite(LED_BUILTIN, HIGH);                     //   Включаем светодиод на плате Arduino.
        delay(100);                                          //   Даём светодиоду светиться 100 мс, чтоб мы его заметили.
    }                                                        //
    digitalWrite(LED_BUILTIN, LOW);                          //   Отключаем светодиод на плате Arduino.
}                                                            //