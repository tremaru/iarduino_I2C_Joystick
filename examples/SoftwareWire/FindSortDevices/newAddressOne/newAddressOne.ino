// ПРИМЕР СМЕНЫ АДРЕСА МОДУЛЯ I2C-FLASH:                     // * Строки со звёздочкой являются необязательными.
// Требуется установить библиотеку <iarduino_I2C_Software.h> //
// Требуется установить библиотеку <iarduino_I2C_Address.h>  //
                                                             //
uint8_t newAddress = 0x09;                                   //   Назначаемый модулю адрес (0x07 < адрес < 0x7F).
                                                             //
#include <iarduino_I2C_Software.h>                           //   Подключаем библиотеку для работы с программной шиной I2C, до подключения библиотеки iarduino_I2C_Address.
SoftTwoWire sWire(3,4);                                      //   Объявляем  объект программной шины I2C указав выводы которым будет назначена роль линий: SDA, SCL.
                                                             //
#include <iarduino_I2C_Address.h>                            //   Подключаем библиотеку для работы с адресами модулей линейки I2C-flash.
iarduino_I2C_Address j;                                      //   Объявляем объект j для работы с модулем I2C-flash. Адрес модуля будет определен автоматически.
                                                             //   Если адрес модуля известен, то его можно указать при создании объекта, например, iarduino_I2C_Address j(0xA0);
//   В данном примере объект j объявлен без указания адреса, //
//   значит адрес будет найден автоматически, следовательно, //
//   на шине I2C должен быть только один модуль.             //
                                                             //
void setup(){                                                //
     delay(500);                                             // * Ждём завершение переходных процессов связанных с подачей питания.
     Serial.begin(9600);                                     //
     while(!Serial){;}                                       // * Ждём завершения инициализации шины UART.
//   Начинаем работу с модулем:                              //
     j.begin(&sWire); // &Wire, &Wire1, &Wire2 ...           //   Функция begin() принимает ссылку на объект для работы с шиной I2C и проверяет существование модуля на этой шине.
//   Выводим сообщение о отсутствии модуля:                  //   Получить результат проверки можно сразу: if( j.begin(&sWire) ){...}, а можно так, как показано в этом примере.
     if(!j){                                                 //   После вызова j.begin(), результат обнаружения модуля остаётся доступным для чтения: if( j ){/*модуль был обнаружен*/;}else{/*нет*/;}
         Serial.print(F("Модуль не найден."));               //
         while(1){;}                                         // * Запрещаем дальнейшую работу если модуль не найден.
     }                                                       //
//   Выводим информацию о модуле:                            //
     Serial.print(F("Найден модуль 0x"));                    //
     Serial.print(j, HEX);                                   //   Выводим текущий адрес модуля.
//   Если модуль принадлежит линейке Flash I2C:              // *
     if( j.getDevice()==DEVICE_I2C_FLASH                     // * DEVICE_I2C_FLASH - модуль принадлежит линейке Flash I2C, DEVICE_I2C_FLASH_OLD - модуль принадлежит линейке Flash I2C но не поддерживает вывод названия и сортировку адреса.
     ||  j.getDevice()==DEVICE_I2C_FLASH_OLD ){              // * Иные значения: DEVICE_I2C_ABSENT - модуль не найден, DEVICE_I2C_UNKNOWN - неизвестный модуль, DEVICE_I2C_DOUBLE - несколько модулей на одном адресе.
         Serial.print(", ");                                 // *
         Serial.print(j.getName());                          // * Выводим название модуля.
         Serial.print(F(", идентификатор = 0x"));            // *
         Serial.print(j.getModel(), HEX);                    // * Выводим номер модели.
         Serial.print(F(", версия прошивки "));              // *
         Serial.print(j.getVersion());                       // * Выводим версию прошивки модуля.
         Serial.print(F(", подтяжка линий шины I2C "));      // *
         Serial.print(j.getPullI2C()? "в":"от");             // * Выводим состояние внутрисхемной подтяжки модуля.
         Serial.print(F("ключена"));                         // *
     }   Serial.println();                                   //
//   Меняем адрес модуля на newAddress:                      //   Менять адреса позволяют только модули линейки Flash I2C.
     j=newAddress;                                           //   Смену адреса можно выполнить с проверкой: if( j=newAddress ){/*успешно*/;}else{/*провал*/;}
//   Проверяем новый адрес модуля:                           //
     if( j==newAddress ){                                    // * Проверяем новый адрес модуля.
         Serial.println(F("Адрес модуля изменён"));          // * Успех записи нового адреса можно проверить по результату присвоения: if( j=newAddress ){/*успешно*/;}else{/*провал*/;}
     }                                                       // * 
//   Выводим новый адрес:                                    //
     Serial.print(F("Текущий адрес модуля 0x"));             //
     Serial.println(j, HEX);                                 //   Выводим текущий адрес модуля.
}                                                            //
                                                             //
void loop(){                                                 //
}                                                            //
                                                             //
//  ПРИМЕЧАНИЕ:                                              //
//  Данный скетч демонстрирует не только возможность смены   //
//  адреса на указанный в переменной newAddress, но и        //
//  обнаружение, и вывод текущего адреса модуля на шине I2C. //
//  Пример библиотеки "sortingAll" показывает как            //
//  автоматически отсортировать все адреса по порядку.       //
