# TXUtils
TXUtils - это opensource библиотека, написанная мною для ~~себя~~ облегчения и удобства работы с графикой, используя [TXLib](http://storage.ded32.net.ru/Lib/TX/TXUpdate/Doc/HTML.ru/).



## Установка
Всё, что вам потребуется - это скачать данный репозиторий и распаковать в любом удобном месте. Например в C:\Lib\TXUtils\.
Затем подключите файл TXU.h в вашей программе после подключения TXLIb:

```
#include <TXLib.h>
#include "C:\Lib\TXUtils\TXU.h"
```

Готово!

Примечание: я гарантирую работу библиотеки лишь с компилятором vusial studio и не отвечаю за совместимость с другими средами.

# Функции библиотеки:
- [void txu::WasExitButtonPressed    ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txuwasexitbuttonpressed-)
- [int  txu::GetMouseWheel           ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#int-txugetmousewheel-)
- [void txu::SetConsoleOutputEnabled (bool enable)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txusetconsoleoutputenabled-bool-enable)
- [bool txu::IsConsoleOutputEnabled  ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txuisconsoleoutputenabled-)

# Классы библиотеки:
- [txu::Color](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucolor)
- [txu::Font](https://github.com/Smok1e/TXUtils/blob/main/README.md#txufont)
- txu::Context



## bool txu::WasExitButtonPressed ()
Возвращает true, если был нажат крестик в меню окна, иначе false, для того чтобы программист сам мог отреагировать на нажатие крестика. Например так:

```
txCreateWindow (800, 800);

while (!GetAsyncKeyState (VK_ESCAPE))
{
	if (txu::WasExitButtonPressed ())
		MessageBox (txWindow (), "THERE IS NO EXIT!", "NO!", MB_OK | MB_ICONERROR);

	txSleep (10);
}
```

![alt text](https://psv4.userapi.com/c534536/u402150900/docs/d10/93c60311fe0b/TXUtils_Github_WasExitButtonPressed_Example.gif?extra=HscRkmZLtfDWHeatsbDqzKfNDiJEaz7j2fUhOc1vagEy7Kh78LJ0LmSZiPwHBWvcNg58IEa6vbL3WyEOyeJsAO7QXS-UXk0kD3DWqojBk1I7nu7P4QPh8mxfPGdyhLO5I2OjkU52zyWM3tBkgK-J4_-d)

## int txu::GetMouseWheel ()
Возвращает сторону, в которую повернулось колёсико мыши.
Если колёсико повернулось вниз, функция вернёт -1, если вверх, 1, а если колёсико не было повёрнуто - функция вернёт 0. 
Значение стороны в которую было повёрнуто колёсико хранится и не изменяется до тех пор, пока колёсико не повернётся снова или не будет вызвана эта функция.

## void txu::SetConsoleOutputEnabled (bool enable)
Разрешает или запрещает дублирование данных из консоли поверх окна txlib. В результатах теста было выяснено, что рисование данных консоли поверх окна снижает fps.

## bool txu::IsConsoleOutputEnabled ()
Возвращает true если рисование консоли поверх окна разрешено или false в обратном случае.

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
- [static Color Interpolate (const std::initializer_list& list, double t)](https://github.com/Smok1e/TXUtils/blob/main/README.md#color-txucolorinterpolate-const-stdinitializer_list-list-double-t)
- [operator RGBQUAD  ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucoloropreator-rgbquad-)
- [operator COLORREF ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucoloroperator-colorref-)
- [Color operator ! ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#color-txucoloroperator--)

## Функции для операций с цветом:
- [txu::Color Blend (Color a, Color b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucolor-blend-color-a-color-b)
- [txu::Color operator <<= (Color a, Color b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucolor-operator--color-a-color-b)

## Color txu::Color::Interpolate (Color a, Color b, Color t)
Эта статическая функция позволяет создавать плавный переход между цветами в зависимости от переменной t.
При t == 0 функция вернёт цвет A, при t == 1 функция вернёт цвет B, а при t == 0.5 функция вернёт средний цвет между A и B.
Например:
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

## Color txu::Color::Interpolate (const std::initializer_list& list, double t)
Тоже самое что и txu::Color::Interpolate (Color a, Color b, double t), но может принять произвольное количество цветов. Например:

```
int size_x = 800;
int size_y = 100;

txCreateWindow (size_x, size_y);
for (int x = 0; x < size_x; x++)
{
	double t = (double) x / size_x;
	txu::Color color = txu::Color::Interpolate ({txu::Color::DarkCyan, txu::Color::DarkPink, txu::Color::Green}, t);
	txSetColor (color);
	txRectangle (x, 0, x+1, size_y);
}
```

Этот код нарисует плавный переход от синего к розовому, а от розового к зелёному:

![alt text](https://sun9-39.userapi.com/impg/6LALpjU6cjeGZguiOl8qeR6_S4VijVP8udaG2A/XAC-U1xZ2V8.jpg?size=810x145&quality=96&sign=8f84690a620e0dc3d376eadcc180524e&type=album)

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

## txu::Color Blend (Color a, Color b)
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

## txu::Color operator <<= (Color a, Color b)
Делает то же, что и Blend, однако цвета повёрнуты местами. То есть:
```
txu::Color color = txu::Blend (a, b);
```
эквивалентно
```
txu::Color color = b <<= a;
```

# txu::Font
Класс, предназначенный для хранения информации о шрифте и установки шрифта в HDC. В будущем постараюсь добавить функцию загрузки шрифта непосредственно из файла.

Пример использования:
```
int size_x = 400;
int size_y = 400;

const char* text = "Hello World!";

txCreateWindow (size_x, size_y);

txSetFillColor (txu::Color (24, 24, 24));
txClear ();

txu::Font font ("consolas", 25, 50, FW_BOLD);
font.setItalicEnabled    (true);
font.setUnderlineEnabled (true);
font.select ();

txSetColor (txu::Color::White);
txTextOut (size_x/2 - txGetTextExtentX (text)/2, size_y/2 - txGetTextExtentY (text)/2, text);
```

Этот код выведет на экран надпись:

![alt text](https://sun9-59.userapi.com/impg/qfrFKRTi7VuiTp7OF1oYxszDmWuSGkT_mn_nsw/nB9r8XHmdcA.jpg?size=415x443&quality=96&sign=75688fd0129e537d00c34d96e983f1de&type=album)

## Конструкторы:
- Font ()
- Font (const char* name, int size_x, int size_y, int weight = FW_DONTCARE, bool italic = false, bool underline = false, bool strikeout = false)
- Font (const Font& that)

## Функции-члены:
- [bool txu::Font::create ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txufontcreate-)
- [bool txu::Font::create (const char* name, int size_x, int size_y, int weight = FW_DONTCARE, bool italic = false, bool underline = false, bool strikeout = false)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txufontcreate-)
- [bool txu::Font::create (const Font& that)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txufontcreate-)
- [void txu::Font::setSize (int size_x, int size_y)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txufontsetsize-int-size_x-int-size_y)
- [int txu::Font::getSizeX ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#int-txufontgetsizex-)
- [int txu::Font::getSizeY ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#int-txufontgetsizey-)
- [void txu::Font::setWeight (int weight)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txufontsetweight-int-weight)
- [int txu::Font::getWeight ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#int-txufontgetweight-)
- [void txu::Font::setItalicEnabled (bool enable)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txufontsetitalicenabled-bool-enabled)
- [bool txu::Font::getItalicEnabled ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txufontgetitalicenabled-)
- [void txu::Font::setUnderlineEnabled (bool enable)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txufontsetunderlineenabled-bool-enable)
- [bool txu::Font::getUnderlineEnabled ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txufontgetunderlineenabled-)
- [void txu::Font::setStrikeoutEnabled (bool enable)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txufontsetstrikeoutenabled-bool-enable)
- [bool txu::Font::getStrikeoutEnabled ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txufontgetstrikeoutenabled-)
- [void setName (const char* name)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txufontsetname-const-char-name)
- [const char* getName ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#const-char-txufontgetname-)
- [HFONT getSystemHandle ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#hfont-txufontgetsystemhandle-)
- [operator HFONT ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#txufontoperator-hfont-)
- [void select (HDC dc = txDC ())](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txufontselect-hdc-dc--txdc-)


## bool txu::Font::create (...)
Заново инициализирует шрифт с указанными параметрами. Возвращает true в случае успеха, иначе false.

## void txu::Font::setSize (int size_x, int size_y)
Устанавливает размер шрифта.

## int txu::Font::getSizeX ()
Возвращает ширину шрифта.

## int txu::Font::getSizeY ()
Возвращает высоту шрифта.

## void txu::Font::setWeight (int weight)
Устанавливает толщину шрифта. См. [CreateFont](https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createfonta#parameters)

## int txu::Font::getWeight ()
Возвращает толщину шрифта.

## void txu::Font::setItalicEnabled (bool enabled)
Включает или отключает прописной шрифт.

## bool txu::Font::getItalicEnabled ()
Возвращает true если прописной шрифт включён, false в обратном случае.

## void txu::Font::setUnderlineEnabled (bool enable)
Включает или отключает подчёркивание текста.

## bool txu::Font::getUnderlineEnabled ()
Возвращает true если подчёркивание текста включено, в обратном случае false.

## void txu::Font::setStrikeoutEnabled (bool enable)
Включает или отключает зачёркивание текста.

## bool txu::Font::getStrikeoutEnabled ()
Возвращает true если зачёркивание текста включено, в обратном случае false.

## void txu::Font::setName (const char* name)
Устанавливает имя шрифта.

## const char* txu::Font::getName ()
Возвращает имя шрифта.

## HFONT txu::Font::getSystemHandle ()
Возвращает дескриптор шрифта winapi.

## txu::Font::operator HFONT ()
Оператор преобразования к HFONT.

## void txu::Font::select (HDC dc = txDC ())
Устанавливает шрифт к HDC указанному в параметре. По умолчанию это txDC ().


# txu::Context
Это, пожалуй, основной инструмент библиотеки. Забудьте о ~~ежедневном геморрое с~~ HDC!
Context обеспечивает удобную и надёжную работу с изображениями. Его не надо освобождать с помощью txDeleteDC, за вас это сделает деструктор.
Давайте начнём.

```
txu::Context source ("image.bmp");
int size_x = source.getSizeX ();
int size_y = source.getSizeY ();

txu::Context result (size_x, size_y);
for (int x = 0; x < size_x; x++)
{
	for (int y = 0; y < size_y; y++)
	{
		txu::Color color = source.getPixel (x, y);
		color.r = 0;
		result.setPixel (x, y, color);
	}
}

txCreateWindow (size_x, size_y);
result.render ();
```

Этот код загрузит картинку из файла "image.bmp" в txu::Context, а затем уберёт красный канал с фотографии:

![alt text](https://sun9-55.userapi.com/impg/xpZhX5tJg1XnkjYSRZJbHlfdA5nRIMqL2PQ9dg/q55WyNvV-hY.jpg?size=257x551&quality=96&sign=0075640318e1216b517c650ec61a4b4d&type=album)
