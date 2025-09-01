/*
  SerialSetTime.ino
  Версия: 1.0.0
  Дата: 01.09.2025
  Автор: RootTool

  Пример работы с библиотекой RootDS1302.

  Что делает:
  - Инициализация модуля времени DS1302 на указанных пинах (CLK, DAT, RST)
  - Считывание текущего времени с DS1302 и вывод в Serial каждые 100 мс
  - Позволяет устанавливать время через Serial в формате:
    HH:MM:SS DD.MM.YY
    (Пример: 14:30:00 01.09.25)
  - Валидирует введённую строку и сообщает об ошибках формата

  Как работает:
  - DS1302.Setup() настраивает пины для работы с модулем
  - В loop() проверяется наличие данных в Serial и парсится строка
  - При корректном формате вызывается DS1302.SetTime()
  - Для вывода времени используется вспомогательная функция PrintTime(), которая получает данные через DS1302.GetTime()
*/


#include <RootDS1302.h>

RootDS1302 DS1302(2, 3, 4); // CLK=2, DAT=3, RST = 4

unsigned long LastUpdate = 0; // хранит время последнего вывода

void setup() 
{
  Serial.begin(9600);
  DS1302.Setup();
}

void loop() 
{
  if (Serial.available()) 
  {
    String line = Serial.readStringUntil('\n');
    line.trim();
    if(line.length() > 0) 
    {
      int h, m, s, day, month, year; 
      
      // Парсим строку формата HH:MM:SS DD.MM.YY
      if(sscanf(line.c_str(), "%d:%d:%d %d.%d.%d", &h, &m, &s, &day, &month, &year) == 6) 
      {
        RootDS1302Struct NewTime;
      	NewTime.Hour  = (uint8_t)h;
      	NewTime.Min   = (uint8_t)m;
      	NewTime.Sec   = (uint8_t)s;
      	NewTime.Day   = (uint8_t)day;
      	NewTime.Month = (uint8_t)month;
      	NewTime.Year  = (uint8_t)year;
      
      	DS1302.SetTime(NewTime);
      	Serial.println("Time updated!");
      } else Serial.println("Invalid format. Use HH:MM:SS DD.MM.YY");
    }
  }
  
  unsigned long Now = millis();
  if (Now - LastUpdate >= 100) 
  {
    LastUpdate = Now;
    PrintTime();
  }
}

void PrintTime()
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
}
