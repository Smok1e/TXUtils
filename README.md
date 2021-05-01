# TXUtils
TXUtils - это opensource библиотека, написанная мною для ~~себя~~ облегчения и удобства работы с графикой, используя [TXLib](http://storage.ded32.net.ru/Lib/TX/TXUpdate/Doc/HTML.ru/).



## Установка
Всё что вам потребуется, это скачать данный репозиторий и распаковать в любом удобном месте. Например в C:\Lib\TXUtils\.
Затем подключите файл TXU.h в вашей программе после подключения TXLIb:

```
#include <TXLib.h>
#include "C:\Lib\TXUtils\TXU.h"
```

Готово!

Примечание: я гарантирую работу библиотеки лишь с компилятором vusial studio и не отвечаю за совместимость с другими средами.

# Функции библиотеки:
- void txu::WasExitButtonPressed    ()
- int  txu::GetMouseWheel           ()
- void txu::SetConsoleOutputEnabled (bool enable)
- bool txu::IsConsoleOutputEnabled  ()

# Классы библиотеки:
- txu::Color
- txu::Font
- txu::Context


# txu::Color
Класс предназначеный для хранения и операций с цветом.
Вы можете пользоваться txu::Color так же как и COLORREF, поскольку класс содержит соответствующий оператор.
Например:
```
COLORREF colorref = txu::Color (0, 130, 255);
```
или
```
txSetFillColor (txu::Color (24, 24, 24));
```
В классе содержатся переменные r, g, b, a для хранения соответствующих каналов.

## Конструкторы класса:
- txu::Color (int r, int g, int b, int a)
- txu::Color (int r, int g, int b)
- txu::Color (const Color& that)
- txu::Color (RGBQUAD rgbquad)
- txu::Color (COLORREF colorref)
- txu::Color ()

## Функции-члены класса:
- [static Color Interpolate (Color a, Color b, double t)](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucolorinterpolate)
- operator RGBQUAD  ()
- operator COLORREF ()
- Color operator ! ()

## Color txu::Color::Interpolate (Color a, Color b, Color t)
Эта функция позволяет создавать поавный переход между цветами в зависимости от переменной t.
При t == 0 функция вернёт цвет A, при t == 1 функция вернёт цвет B, а при t == 0.5 функция вернёт средний цвет между A и B.
Нпример:
```
int size_x = 800;
int size_y = 100;

txCreateWindow (size_x, size_y);

for (int x = 0; x < size_x; x++)
{
  double t = (double) x / size_x;
  txSetColor (txu::Color::Interpolate (txu::Color::DarkCyan, txu::Color::DarkPink, t));
  txRectangle (x, 0, x+1, size_y);
}
```

Этот код нарисует на экране плавный градиент от синего к розовому:
![alt text](https://sun9-75.userapi.com/impg/asgxBLRJxiH55RZZrQ0tVBcCR6iWUAoKkrP6XA/uxpa4NcGZ88.jpg?size=817x146&quality=96&sign=7ec3e464ad7d033a6bc39a8d5a5ef7bc&type=album)

## txu::Color::opreator RGBQUAD ()
Оператор преобразования к RGBQUAD

## txu::Color::operator COLORREF ()
Оператор преобразования к COLORREF

## Color txu::Color::operator ! ()
Возвращает инвертированный цвет:
```
txu::Color black (0, 0, 0)
txu::Color white = !black //Белый цвет
```

