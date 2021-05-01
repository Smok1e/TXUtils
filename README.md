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
- [txu::Color](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucolor)
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
В классе содержатся публичные переменные r, g, b, a для хранения соответствующих каналов.

## Конструкторы:
- txu::Color (int r, int g, int b, int a)
- txu::Color (int r, int g, int b)
- txu::Color (const Color& that)
- txu::Color (RGBQUAD rgbquad)
- txu::Color (COLORREF colorref)
- txu::Color ()

## Функции-члены:
- [static Color Interpolate (Color a, Color b, double t)](https://github.com/Smok1e/TXUtils/blob/main/README.md#color-txucolorinterpolate-color-a-color-b-color-t)
- [operator RGBQUAD  ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucoloropreator-rgbquad-)
- [operator COLORREF ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucoloroperator-colorref-)
- [Color operator ! ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucoloroperator-colorref-)

##Функции для операций с цветом:
- txu::Color Blend (Color a, Color b)
- txu::Color operator <<= (Color a, Color b)

# Color txu::Color::Interpolate (Color a, Color b, Color t)
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

# txu::Color::opreator RGBQUAD ()
Оператор преобразования к RGBQUAD

# txu::Color::operator COLORREF ()
Оператор преобразования к COLORREF

# Color txu::Color::operator ! ()
Возвращает инвертированный цвет:
```
txu::Color black (0, 0, 0)
txu::Color white = !black //Белый цвет
```

# txu::Color Blend (Color a, Color b)
Функция смешивания цветов с учётом альфа-канала.
Например:
```
	int size_x = 400;
	int size_y = 400;

	txCreateWindow (size_x, size_y);
	
	txSetFillColor (txu::Color (24, 24, 24));
	txClear ();

	txSetFillColor (txu::Color::White);
	txRectangle (50, 75, 200, 150);

	for (int x = 100; x < 300; x++)
		for (int y = 100; y < 300; y++)
			txSetPixel (x, y, txu::Blend (txu::Color (0, 130, 255, 100), txGetPixel (x, y)));
```

Этот код нарисует полу-прозрачный синий квадрат:

![alt text](https://sun9-7.userapi.com/impg/MgASVpcQx8lKaYcHmaAdbrFjE7MybQO5l4EtWg/dQAGTt2ornE.jpg?size=421x456&quality=96&sign=9a47d95f45c3e79c92693e5e9c4b94a2&type=album)

Примечание: функция Blend учитывает альфа-канал только первого цвета!

# txu::Color operator <<= (Color a, Color b)
Делает то же, что и Blend, однако цвета повёрнуты местами. То есть:
```
txu::Color color = txu::Blend (a, b);
```
эквивалентно
```
txu::Color color = b <<= a;
```
