// ДАННЫЙ ПРИМЕР МЕНЯЕТ НАПРАВЛЕНИЕ ОСЕЙ:                    // * Строки со звёздочкой являются необязательными.
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
int a, b, c;                                                 //
                                                             //
void setup(){                                                //
    delay(500);                                              // * Ждём завершение переходных процессов связанных с подачей питания.
    Serial.begin(9600);                                      //
    while(!Serial){;}                                        // * Ждём завершения инициализации шины UART.
    joy.begin(&sWire);                                       //   Инициируем работу с джойстиком, указав ссылку на объект для работы с шиной I2C на которой находится джойстик (по умолчанию &Wire).
//  Изменение направления оси X:                             //
    joy.getCalibration_X(a, b, c);                           //   Читаем установленные  калибровочные значения для оси X в переменные a,b,c.
    joy.setCalibration_X(c, b, a);                           //   Сохраняем прочитанные калибровочные значения для оси X, но указываем аргументы в обратном порядке: c,b,a.
//  Изменение направления оси Y:                             //
    joy.getCalibration_Y(a, b, c);                           //   Читаем установленные  калибровочные значения для оси Y в переменные a,b,c.
    joy.setCalibration_Y(c, b, a);                           //   Сохраняем прочитанные калибровочные значения для оси Y, но указываем аргументы в обратном порядке: c,b,a.
}                                                            //
                                                             //
void loop(){                                                 //
    joy.getPosition(a,b);                                    //   Получаем координаты в переменные a и b.
    Serial.println( (String)"X:Y="+a+":"+b );                //   Выводим  координаты джойстика.
}                                                            //