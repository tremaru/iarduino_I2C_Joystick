// ДАННЫЙ ПРИМЕР ФИКСИРУЕТ УДЕРЖАНИЕ КНОПКИ:      //   Светодиод на плате Arduino будет светиться, если кнопка удерживается дольше указанного времени.
// (ТОЛЬКО ДЛЯ ВЕРСИИ ДЖОЙСТИКА С КНОПКОЙ)        // * Строки со звёздочкой являются необязательными.
                                                  //
// Джойстик, FLASH-I2C (Trema-модуль):            //   https://iarduino.ru/shop/Expansion-payments/dzhoystik-i2c---flash-trema-modul.html
// Информация о подключении модулей к шине I2C:   //   https://wiki.iarduino.ru/page/i2c_connection/
// Информация о модуле и описание библиотеки:     //   https://wiki.iarduino.ru/page/joystick-i2c/
                                                  //
#include <Wire.h>                                 //   Подключаем библиотеку для работы с аппаратной шиной I2C, до подключения библиотеки iarduino_I2C_Joystick.
#include <iarduino_I2C_Joystick.h>                //   Подключаем библиотеку для работы с джойстиком I2C-flash.
iarduino_I2C_Joystick joy(0x09);                  //   Объявляем объект joy для работы с функциями и методами библиотеки iarduino_I2C_Joystick, указывая адрес модуля на шине I2C.
                                                  //   Если объявить объект без указания адреса (iarduino_I2C_Joystick joy;), то адрес будет найден автоматически.
void setup(){                                     //
    delay(500);                                   // * Ждём завершение переходных процессов связанных с подачей питания.
    pinMode(LED_BUILTIN, OUTPUT);                 //   Конфигурируем вывод к которому подключён светодиод на плате Arduino в режим работы на выход.
    joy.begin(&Wire); // &Wire1, &Wire2 ...       //   Инициируем работу с джойстиком, указав ссылку на объект для работы с шиной I2C на которой находится джойстик (по умолчанию &Wire).
}                                                 //
                                                  //
void loop(){                                      //
    int f=joy.getButton(KEY_TIME_PRESSED);        //   Считываем время удержания кнопки (в миллисекундах) в переменную f.
    digitalWrite(LED_BUILTIN, f>5000);            //   Включаем светодиод если кнопка удерживается дольше 5 секунд.
}                                                 //   Максимально фиксируемое время удержания: 25,5 секунд.