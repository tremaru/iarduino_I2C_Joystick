// ДАННЫЙ ПРИМЕР УСТАНИВЛИВАЕТ СВЕТОДИОДНУЮ АНИМАЦИЮ НАЖАТИЙ КНОПОК:// * Строки со звёздочкой являются необязательными.
// (нажимайте удерживайте и отпускайте кнопки клавиатуры)           //
                                                                    //
// Клавиатура 4x2, FLASH-I2C:                                       //   https://iarduino.ru/shop/Expansion-payments/klaviatura-4x2-i2c-flash.html
// Клавиатура 5x2, FLASH-I2C:                                       //   https://iarduino.ru/shop/Expansion-payments/klaviatura-5x2-i2c-flash.html
// Информация о подключении модулей к шине I2C:                     //   https://wiki.iarduino.ru/page/i2c_connection/
// Информация о модуле и описание библиотеки:                       //   https://wiki.iarduino.ru/page/keyboard-i2c-flash/
                                                                    //
#include <Wire.h>                                                   //   Подключаем библиотеку для работы с аппаратной шиной I2C, до подключения библиотеки iarduino_I2C_Keyboard.
#include <iarduino_I2C_Keyboard.h>                                  //   Подключаем библиотеку для работы с клавиатурой I2C-flash.
iarduino_I2C_Keyboard kbd(0x09,5,2);                                //   Объявляем объект kbd для работы с функциями и методами библиотеки iarduino_I2C_Keyboard, указывая адрес модуля на шине I2C, количество кнопок в линии, количество линий с кнопками.
                                                                    //   Если объявить объект без указания адреса (iarduino_I2C_Keyboard kbd(false,5,2);), то адрес будет найден автоматически.
void setup(){                                                       //
    delay(500);                                                     // * Ждём завершение переходных процессов связанных с подачей питания.
    kbd.begin(&Wire); // &Wire1, &Wire2 ...                         //   Инициируем работу с клавиатурой, указав ссылку на объект для работы с шиной I2C на которой находится клавиатура (по умолчанию &Wire).
//  Включаем одну из представленных анимаций:                       //
//  kbd.setAnimation(1,200);                                        //   Анимация №1: Светодиод будет включаться на 200 мс после каждого нажатия на кнопку.
//  kbd.setAnimation(2,200);                                        //   Анимация №2: Светодиод будет включаться на 200 мс после каждого отпускания кнопки.
//  kbd.setAnimation(3,200);                                        //   Анимация №3: Светодиод будет включаться на 200 мс после каждого нажатия или отпускания кнопки.
//  kbd.setAnimation(4);                                            //   Анимация №4: Светодиод будет светиться пока кнопка нажата.
//  kbd.setAnimation(5);                                            //   Анимация №5: Светодиод работает как переключатель.
//  kbd.setAnimation(6);                                            //   Анимация №6: Светодиод будет светиться если кнопка удерживается (нажата дольше 0,5 с).
    kbd.setAnimation(7);                                            //   Анимация №7: Светодиод будет светиться при каждом пополнении буфера FIFO кодом символа своей кнопки.
//  kbd.setAnimation(0);                                            //   Отключить светодиодную анимацию.
}                                                                   //
                                                                    //
void loop(){                                                        //
}                                                                   //
                                                                    //
//  ПРИМЕЧАНИЕ:                                                     //
//  Светодиодная анимация выполняется модулем клавиатуры,           //
//  не используя ресурсов Arduino.                                  //
//  Для некоторых видов анимации можно (но не обязательно)          //
//  указывать время свечения светодиода (от 0 до 2550 мс).          //
