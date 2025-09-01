/*
  SerialPrintTime.ino
  Версия: 1.0.0
  Дата: 01.09.2025
  Автор: RootTool

  Пример работы с библиотекой RootDS1302.

  Что делает:
  - Инициализация модуля времени DS1302 на указанных пинах (CLK, DAT, RST)
  - Считывание текущего времени и даты с DS1302 каждую секунду
  - Вывод времени и даты в Serial в формате HH:MM:SS  DD.MM.YY

  Как работает:
  - DS1302.Setup() настраивает пины для работы с модулем
  - В loop() вызывается DS1302.GetTime() для получения текущего времени
  - Результат выводится в Serial
  - Используется задержка 1 секунда для удобного отображения времени
*/


#include <RootDS1302.h>

RootDS1302 DS1302(2, 3, 4); // CLK=2, DAT=3, RST = 4

void setup() 
{
  Serial.begin(9600);
  DS1302.Setup();
}

void loop() 
{
  RootDS1302Struct DS1302Struct = DS1302.GetTime();

  Serial.print(DS1302Struct.Hour);
  Serial.print(":");
  Serial.print(DS1302Struct.Min);
  Serial.print(":");
  Serial.print(DS1302Struct.Sec);
  Serial.print("  ");
  Serial.print(DS1302Struct.Day);
  Serial.print(".");
  Serial.print(DS1302Struct.Month);
  Serial.print(".");
  Serial.println(DS1302Struct.Year);

  delay(1000);
}
