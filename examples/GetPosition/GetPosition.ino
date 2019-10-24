// ДАННЫЙ ПРИМЕР ВЫВОДИТ КООРДИНАТЫ ДЖОЙСТИКА:    // * Строки со звёздочкой являются необязательными.
                                                  //
#include <Wire.h>                                 // * Подключаем библиотеку для работы с аппаратной шиной I2C.
#include <iarduino_I2C_Joystick.h>                //   Подключаем библиотеку для работы с джойстиком I2C-flash.
iarduino_I2C_Joystick joy(0x09);                  //   Объявляем объект joy для работы с функциями и методами библиотеки iarduino_I2C_Joystick, указывая адрес модуля на шине I2C.
                                                  //   Если объявить объект без указания адреса (iarduino_I2C_Joystick joy;), то адрес будет найден автоматически.
void setup(){                                     //
    delay(500);                                   // * Ждём завершение переходных процессов связанных с подачей питания.
    Serial.begin(9600);                           //
    while(!Serial){;}                             // * Ждём завершения инициализации шины UART.
    joy.begin();                                  //   Инициируем работу с джойстиком.
}                                                 //
                                                  //
void loop(){                                      //
//  Получаем и выводим координаты по отдельности: //
    Serial.print( "X=" );                         //
    Serial.print( joy.getPosition_X() );          //   Выводим координату по оси X, значение от -100 до 100.
    Serial.print( ", Y=" );                       //
    Serial.print( joy.getPosition_Y() );          //   Выводим координату по оси Y, значение от -100 до 100.
//  Получаем сразу обе координаты:                //
    int x,y;                                      //   Объявляем переменные для получения координат.
    joy.getPosition(x,y);                         //   Получаем координаты в указанные переменные.
    Serial.print( ", X:Y=" );                     //
    Serial.print( x );                            //   Выводим координату по оси X, значение от -100 до 100.
    Serial.print( ":" );                          //
    Serial.print( y );                            //   Выводим координату по оси X, значение от -100 до 100.
    Serial.println( "." );                        //
}                                                 //