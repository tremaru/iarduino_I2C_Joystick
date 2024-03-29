// ДАННЫЙ ПРИМЕР ВЫПОЛНЯЕТ КАЛИБРОВКУ ДЖОЙСТИКА:                                  // * Строки со звёздочкой являются необязательными.
                                                                                  //
#include <Wire.h>                                                                 // * Подключаем библиотеку для работы с аппаратной шиной I2C.
#include <iarduino_I2C_Joystick.h>                                                //   Подключаем библиотеку для работы с джойстиком I2C-flash.
iarduino_I2C_Joystick joy(0x09);                                                  //   Объявляем объект joy для работы с функциями и методами библиотеки iarduino_I2C_Joystick, указывая адрес модуля на шине I2C.
                                                                                  //   Если объявить объект без указания адреса (iarduino_I2C_Joystick joy;), то адрес будет найден автоматически.
uint32_t tmrStop;                                                                 //
long x, adc_X_min=4096, adc_X_cen=0, adc_X_max=0;                                 //
long y, adc_Y_min=4096, adc_Y_cen=0, adc_Y_max=0;                                 //
                                                                                  //
void setup(){                                                                     //
    delay(500);                                                                   // * Ждём завершение переходных процессов связанных с подачей питания.
    Serial.begin(9600);                                                           //
    while(!Serial){;}                                                             // * Ждём завершения инициализации шины UART.
    joy.begin();                                                                  //   Инициируем работу с джойстиком.
    joy.setAveraging(2);                                                          //   Устанавливаем незначительное усреднение показаний АЦП.
    joy.setDeadZone(7.0);                                                         //   Устанавливаем мёртвую зону центрального положения в 7%.
//  Готовимся определить центральное положение джойстика:                         //
    Serial.println( F("\r\nКАЛИБРОВКА ДЖОЙСТИКА:\r\n")                         ); //
    Serial.println( F("Отпустите джойстик.")                                   ); //
    Serial.println( F("Он должен самостоятельно установиться")                 ); //
    Serial.println( F("в центральное положение.")                              ); //
    Serial.print  ( F("Ждём.")                                                 ); //
    for(int i=0; i<5; i++){ delay(1000); Serial.print("."); }                     //   Даём время пользователю отпустить джойстик.
//  Получаем значения АЦП соответствующие центральному положению:                 //
    for(int i=0; i<10; i++){                                                      //   Выполняем цикл чтения 10 раз.
        joy.getADC(x,y); Serial.print( (String) "\r\nАЦП = "+x+":"+y           ); //   Получаем текущие значения АЦП в указанные переменные.
        adc_X_cen += x;  adc_Y_cen += y; delay(200);                              //   Получаем АЦП центра, прибавляя его к предыдущему значению.
    }   adc_X_cen /= 10; adc_Y_cen /= 10;                                         //   Получаем среднее арифметическое значение АЦП центра.
//  Готовимся определить крайние положения джойстика:                             //
    Serial.println( F("\r\nГотово!") );                                           //
    Serial.println( F("------------------------------------------------")      ); //
    Serial.println( ""                                                         ); //
    Serial.println( F("Теперь медленно поворачивайте джойстик по кругу,")      ); //
    Serial.println( F("со скоростью 1 полный оборот за 2-3 секунды,")          ); //
    Serial.println( F("на максимальном удалении джойстика от центра.")         ); //
//  Получаем значения АЦП соответствующие крайним положениям:                     //
    tmrStop = millis() + 10000;                                                   //   Определяем время завершения снятия показаний.
    while(millis()<tmrStop){                                                      //   Выполняем цикл пока не достигнем времени tmrStop...
        joy.getADC(x,y);                                                          //   Получаем текущие значения АЦП в указанные переменные.
        if( x < adc_X_min ){ adc_X_min = x; }                                     //   Получаем минимальное  значение АЦП по оси X.
        if( y < adc_Y_min ){ adc_Y_min = y; }                                     //   Получаем минимальное  значение АЦП по оси Y.
        if( x > adc_X_max ){ adc_X_max = x; }                                     //   Получаем максимальное значение АЦП по оси X.
        if( y > adc_Y_max ){ adc_Y_max = y; }                                     //   Получаем максимальное значение АЦП по оси Y.
        if(millis()%1000<10){ delay(10); Serial.print("."); }                     //   Выводим точку в монитор, один раз в секунду.
    }                                                                             //
//  Выводим результат:                                                            //
    Serial.println( F("\r\nГотово!")                                           ); //
    Serial.println( F("------------------------------------------------")      ); //
    Serial.println( ""                                                         ); //
    Serial.println( (String) "АЦП по оси X меняется от "+adc_X_min+" до "+adc_X_max+", с центром в "+adc_X_cen);
    Serial.println( (String) "АЦП по оси Y меняется от "+adc_Y_min+" до "+adc_Y_max+", с центром в "+adc_Y_cen);
    Serial.println( F("================================================")      ); //
    Serial.println( ""                                                         ); //
//  Калибруем джойстик (данные сохранятся в его flash памяти):                    //
    joy.setCalibration_X(adc_X_min, adc_X_cen, adc_X_max);                        //  Калибруем координаты по оси X.
    joy.setCalibration_Y(adc_Y_min, adc_Y_cen, adc_Y_max);                        //  Калибруем координаты по оси Y.
//  Готовимся к выводу координат после калибровки:                                //
    delay(2000);                                                                  //
    Serial.println( F("Приготовтесь проверить результат калибровки.")          ); //
    Serial.println( F("Сейчас будут выводиться координаты джойстика...")       ); //
    Serial.println( F("При выводе координат можно изменить направление осей.") ); //
    Serial.println( F("- для смены направления оси X введите 1.")              ); //
    Serial.println( F("- для смены направления оси Y введите 2.")              ); //
    Serial.print  ( F("Ждём.")                                                 ); //
    for(int i=0; i<10; i++){ delay(1000); Serial.print("."); }                    //   Даём время пользователю прочитать результат, до начала вывода координат.
    Serial.println( F("\r\nВыводим координаты:")                               ); //
}                                                                                 //
                                                                                  //
void loop(){                                                                      //
//  Выводим координаты:                                                           //
    joy.getPosition(x,y); Serial.print( (String) "X:Y="+x+":"+y+" "       );      //   Выводим координаты X:Y.
    joy.getADC(x,y);      Serial.print( (String) "(АЦП="+x+":"+y+").\r\n" );      //   Выводим значения АЦП.
//  Проверяем не желает ли пользователь сменить направление осей:                 //
    if(Serial.available()){                                                       //   Если из монитора последовательного порта получены данные, то ...
        switch(Serial.read()){                                                    //
            case '1': joy.getCalibration_X(adc_X_min, adc_X_cen, adc_X_max);      //   Читаем установленные  калибровочные значения для оси X.
                      joy.setCalibration_X(adc_X_max, adc_X_cen, adc_X_min);      //   Сохраняем прочитанные калибровочные значения для оси X, но меняем местами значения min и max.
                      Serial.println( F("Направление оси X изменено.")         ); //
                      delay(3000);                                                //
            break;                                                                //
            case '2': joy.getCalibration_Y(adc_Y_min, adc_Y_cen, adc_Y_max);      //   Читаем установленные  калибровочные значения для оси Y.
                      joy.setCalibration_Y(adc_Y_max, adc_Y_cen, adc_Y_min);      //   Сохраняем прочитанные калибровочные значения для оси Y, но меняем местами значения min и max.
                      Serial.println( F("Направление оси Y изменено.")         ); //
                      delay(3000);                                                //
            break;                                                                //
        }   while(Serial.available()){Serial.read(); delay(5);}                   //   Чистим буфер обмена UART.
    }                                                                             //
}                                                                                 //