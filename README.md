# RootDS1302

_(v1.0.0)_

Библиотека для Arduino для работы с модулем времени DS1302: установка, чтение и обновление даты и времени.

---

## Возможности

* Установка текущего времени и даты
* Чтение текущего времени и даты
* Работа с секундами, минутами, часами, днями, месяцами и годами
* Простой интерфейс через структуру `RootDS1302Struct`
* Полностью совместимо с Arduino, лёгкая интеграция

---

## Установка

1. Скачайте или клонируйте репозиторий:

```bash
git clone https://github.com/RootTool0/RootDS1302.git
```

2. Скопируйте папку `RootDS1302` в папку `libraries` Arduino.
3. Перезапустите Arduino IDE.

---

## Использование библиотеки

### Создание объекта

```cpp
RootDS1302 RTC(uint8_t PinCLK, uint8_t PinDAT, uint8_t PinRST);
```

* `PinCLK` - Пин подключения CLK модуля DS1302
* `PinDAT` - Пин подключения DIO модуля DS1302
* `PinRST` - Пин подключения RST модуля DS1302

---

### Инициализация

```cpp
void Setup();
```

* Инициализирует модуль DS1302
* Должно вызываться в `setup()`

---

### Структура RootDS1302Struct

```cpp
struct RootDS1302Struct {
    uint8_t Sec;
    uint8_t Min;
    uint8_t Hour;
    uint8_t Day;
    uint8_t Month;
    uint8_t Year;
};
```

---

### Установка времени

```cpp
void SetTime(const RootDS1302Struct& Time);
```

* Устанавливает дату и время из структуры в модуль DS1302

---

### Чтение времени

```cpp
RootDS1302Struct GetTime();
```

* Читает текущее время и дату с модуля DS1302
* Результат возвращается в структуре `RootDS1302Struct`

---

## Примеры

* [SerialPrintTime.ino](examples%2FSerialPrintTime%2FSerialPrintTime.ino) - Пример вывода времени с модуля DS1302 в Serial.
* [SerialSetTime.ino](examples%2FSerialSetTime%2FSerialSetTime.ino) - Пример установки времени через Serial.

---

## Лицензия

MIT License

См. файл [LICENSE](LICENSE)

---

## Обратная связь

Если у вас есть вопросы, предложения или баги, то можете связаться со мной:

* **Telegram (канал/блог)**: [RootTool Blog](https://t.me/RootToolBlog)
* **Telegram (ЛС)**: [@RootTool28](https://t.me/RootTool28)
* **Discord**: `.roottool` (или `RootTool#5776`)
* **YouTube**: [RootTool](https://www.youtube.com/@RTEdits0)

*(прошу не беспокоить меня без причины)*
