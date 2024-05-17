// ДАННЫЙ ПРИМЕР РЕАГИРУЕТ НА ИЗМЕНИНИЕ СОСТОЯНИЯ КЛАВИШ КЛАВИАТУРЫ:// * Строки со звёздочкой являются необязательными.
// (нажимайте или удерживайте кнопки клавиатуры)                    //
                                                                    //
// Клавиатура 4x2, FLASH-I2C:                                       //   https://iarduino.ru/shop/Expansion-payments/klaviatura-4x2-i2c-flash.html
// Клавиатура 5x2, FLASH-I2C:                                       //   https://iarduino.ru/shop/Expansion-payments/klaviatura-5x2-i2c-flash.html
// Информация о подключении модулей к шине I2C:                     //   https://wiki.iarduino.ru/page/i2c_connection/
// Информация о модуле и описание библиотеки:                       //   https://wiki.iarduino.ru/page/keyboard-i2c-flash/
                                                                    //
#include <Wire.h>                                                   //   Подключаем библиотеку для работы с аппаратной шиной I2C, до подключения библиотеки iarduino_I2C_Keyboard.
#include <iarduino_I2C_Keyboard.h>                                  //   Подключаем библиотеку для работы с клавиатурой I2C-flash.
iarduino_I2C_Keyboard kbd(0x09,4,2);                                //   Объявляем объект kbd для работы с функциями и методами библиотеки iarduino_I2C_Keyboard, указывая адрес модуля на шине I2C, количество кнопок в линии, количество линий с кнопками.
                                                                    //   Если объявить объект без указания адреса (iarduino_I2C_Keyboard kbd(false,4,2);), то адрес будет найден автоматически.
void setup(){                                                       //
    delay(500);                                                     // * Ждём завершение переходных процессов связанных с подачей питания.
    Serial.begin(9600);                                             //   Инициируем передачу данных по шине UART на скорости 9600 бит/сек.
    while(!Serial){;}                                               // * Ждём завершения инициализации шины UART.
    kbd.begin(&Wire); // &Wire1, &Wire2 ...                         //   Инициируем работу с клавиатурой, указав ссылку на объект для работы с шиной I2C на которой находится клавиатура (по умолчанию &Wire).
}                                                                   //
                                                                    //
void loop(){                                                        //
    uint16_t i;                                                     //   Объявляем переменную для получения флагов.
//  Выполняем действия по изменению состояния любой клавиши:        //
    if( kbd.getKey(KEY_ALL, KEY_CHANGED) ){                         //   Если изменилось состояние хотя бы одной кнопки, то ...
    i = kbd.getKey(KEY_ALL, KEY_STATE  );                           //   Получаем флаги текущего состояния кнопок.
        if(i         ){Serial.print("Нажаты кнопки: "     );}       //   Выводим текст если установлен хотя бы 1 флаг.
        else          {Serial.print("Все кнопки отпущены.");}       //   Выводим текст если все флаги сброшены.
        if(i & bit(0)){Serial.print("1,");}                         //   Если установлен 0 бит (флаг состояния 1 кнопки 1 ряда), то выводим текст.
        if(i & bit(1)){Serial.print("2,");}                         //   Если установлен 1 бит (флаг состояния 2 кнопки 1 ряда), то выводим текст.
        if(i & bit(2)){Serial.print("3,");}                         //   Если установлен 2 бит (флаг состояния 3 кнопки 1 ряда), то выводим текст.
        if(i & bit(3)){Serial.print("4,");}                         //   Если установлен 3 бит (флаг состояния 4 кнопки 1 ряда), то выводим текст.
        if(i & bit(4)){Serial.print("5,");}                         //   Если установлен 4 бит (флаг состояния 1 кнопки 2 ряда), то выводим текст.
        if(i & bit(5)){Serial.print("6,");}                         //   Если установлен 5 бит (флаг состояния 2 кнопки 2 ряда), то выводим текст.
        if(i & bit(6)){Serial.print("7,");}                         //   Если установлен 6 бит (флаг состояния 3 кнопки 2 ряда), то выводим текст.
        if(i & bit(7)){Serial.print("8,");}                         //   Если установлен 7 бит (флаг состояния 4 кнопки 2 ряда), то выводим текст.
        Serial.print("\r\n");                                       //
    }                                                               //
}                                                                   //
                                                                    //
//  ПРИМЕЧАНИЕ:                                                     //
//  Данный пример реагирует на событие KEY_CHANGED - изменилось     //
//  состояние любой клавиши клавиатуры.                             //
//  После чего считывает флаги состояния всех клавиш KEY_STATE в i. //
//  В примере не раскрыты следующие типы получаемых событий:        //
//  KEY_PUSHED   - реагировать только на «нажатие» клавиш.          //
//  KEY_RELEASED - реагировать только на «отпускание» клавиш.       //
//  KEY_TRIGGER  - вернуть состояние переключателя кнопки.          //
//  Попробуйте изменить KEY_STATE на любой из 3 перечисленных типов.//
//  В примере getKeyState показано как реагировать на состояния     //
//  не всех, а только указанных клавиш клавиатуры.                  //
