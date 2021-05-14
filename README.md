# TXUtils
TXUtils - это opensource библиотека, написанная мною для ~~себя~~ облегчения и удобства работы с графикой, используя [TXLib](http://storage.ded32.net.ru/Lib/TX/TXUpdate/Doc/HTML.ru/).

# Зависимости
Разумеется, для работы TXUtils необходим [TXLib](http://storage.ded32.net.ru/Lib/TX/TXUpdate/Doc/HTML.ru/). 
Так же, рекомендуется установить [libpng](http://www.libpng.org/pub/png/libpng.html), если у вас её нет. Библиотека может работать и без неё, но тогда вы не сможете работать с форматом png используя [txu::Context](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucontext).

# Установка
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
- [bool txu::SetWindowIcon (const char* filename)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txusetwindowicon-const-char-filename)

# Макросы
- [WS_NOFRAME](https://github.com/Smok1e/TXUtils/blob/main/README.md#ws_noframe)

# Классы библиотеки:
- [txu::Color](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucolor)
- [txu::Font](https://github.com/Smok1e/TXUtils/blob/main/README.md#txufont)
- [txu::Coord2D](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucoord2d)
- [txu::Context](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucontext)
- [txu::Time](https://github.com/Smok1e/TXUtils/blob/main/README.md#txutime)
- [txu::Timer]()

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

![WasExitButtonPressed_example](https://user-images.githubusercontent.com/33802666/117330931-e2ea3e00-ae9e-11eb-91c9-a5e5cf0ac772.gif)

## int txu::GetMouseWheel ()
Возвращает сторону, в которую повернулось колёсико мыши.
Если колёсико повернулось вниз, функция вернёт -1, если вверх, 1, а если колёсико не было повёрнуто - функция вернёт 0. 
Значение стороны в которую было повёрнуто колёсико хранится и не изменяется до тех пор, пока колёсико не повернётся снова или не будет вызвана эта функция.

## void txu::SetConsoleOutputEnabled (bool enable)
Разрешает или запрещает дублирование данных из консоли поверх окна txlib. В результатах теста было выяснено, что рисование данных консоли поверх окна снижает fps.

## bool txu::IsConsoleOutputEnabled ()
Возвращает true если рисование консоли поверх окна разрешено или false в обратном случае.

## bool txu::SetWindowIcon (const char* filename)
Вам не надоела иконка TXLib'а, которую [дед](http://ded32.net.ru/) нагло вставил в свою библиотеку? Мне да.
Поэтому я и сделал эту функцию.
Она устанавливает окну TXLib иконку, загруженную из файла, указанного в параметрах. Если картинка загружена успешно, функция вернёт true. В обратном случае - false.
Иконка должна быть в формате [.ico](https://ru.wikipedia.org/wiki/ICO_(%D1%84%D0%BE%D1%80%D0%BC%D0%B0%D1%82_%D1%84%D0%B0%D0%B9%D0%BB%D0%B0))

Я нарисовал такую иконку для своей программы:

![setwindowicon_example_1](https://user-images.githubusercontent.com/33802666/117330977-f0072d00-ae9e-11eb-8355-25fd6b65d703.png)

И вызвал функцию txu::SetWindowIcon:

```
txCreateWindow (800, 800);
txu::SetWindowIcon ("icon.ico");
```

Теперь в заголовке окна висит моя собственная иконка:

![setwindowicon_example_2](https://user-images.githubusercontent.com/33802666/117331032-001f0c80-ae9f-11eb-82e1-cf1503ff5560.png)

Так же, советую вам [плагин для фотошопа, позволяющий сохранять картинки в формате ico](https://rugraphics.ru/photoshop/plagin-format-ico-v-photoshop-cs6-i-cc).

И напоследок, если вам не нравится то, что TXLib устанавливает своё имя в заголовке окна, используйте функцию [SetWindowText](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowtexta) из WinApi.

## WS_NOFRAME
Стиль окна без заголовка и рамок.
```
_txWindowStyle = WS_NOFRAME;
txCreateWindow (800, 800);
```

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
- [Color& operator = (const Color& that)](https://github.com/Smok1e/TXUtils/blob/main/README.md#color-txucoloroperator--const-color-that)
- [static Color HSV (int h, int s, int v)](https://github.com/Smok1e/TXUtils/blob/main/README.md#static-color-txucolorhsv-int-h-int-s-int-)
- [int hue ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#int-txucolorhue-)
- [int saturation ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#int-txucolorsaturation-)
- [int value ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#int-txucolorvalue-)

## Функции для операций с цветом:
- [txu::Color Blend (Color a, Color b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucolor-blend-color-a-color-b)
- [txu::Color operator <<= (Color a, Color b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucolor-operator--color-a-color-b)
- [bool operator == (const Color& a, const Color& b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-operator--const-color-a-const-color-b)
- [bool operator != (const Color& a, const COlor& b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-operator--const-color-a-const-color-b-1)

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

![color_interpolate_example](https://user-images.githubusercontent.com/33802666/117331183-2d6bba80-ae9f-11eb-8345-622fd799f51a.png)

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

![color_interpolate_initializer_list_example](https://user-images.githubusercontent.com/33802666/117331231-39577c80-ae9f-11eb-961f-6b6fc0e6d246.png)

## txu::Color::opreator RGBQUAD ()
Оператор преобразования к RGBQUAD

## txu::Color::operator COLORREF ()
Оператор преобразования к COLORREF
Обратите внимание, что если альфа-канал цвета равен нулю, то оператор COLORREF вернёт TX_TRANSPARENT.
В остальных случаях альфа-канал не учитывается. К сожалению, хоть размер COLORREF и равен четырём байтам, в одном из которых в теории можно хранить альфа-канал, GDI windows не позволяет оперировать полу-прозрачными цветами нативно, а четвёртый байт COLORREF'a считается зарезервированным.

## Color txu::Color::operator ! ()
Возвращает инвертированный цвет:
```
txu::Color black (0, 0, 0)
txu::Color white = !black //Белый цвет
```

## Color& txu::Color::operator = (const Color& that)
Опиратор присваивания

## static Color txu::Color::HSV (int h, int s, int v)
Возвращает цвет, созданный на основе системы [HSV](https://ru.wikipedia.org/wiki/HSV_(%D1%86%D0%B2%D0%B5%D1%82%D0%BE%D0%B2%D0%B0%D1%8F_%D0%BC%D0%BE%D0%B4%D0%B5%D0%BB%D1%8C)).
Значения h, s и v должны быть в диапазоне от 0 до 255.
Эта функция является статической, то есть её можно вызвать не создавая экземпляра класса Color.
Например:

```
int size_x = 800;
int size_y = 100;

txCreateWindow (size_x, size_y);
for (int x = 0; x < size_x; x++)
{
	double t = (double) x / size_x;
	int hue = t * 255;

	txSetColor (txu::Color::HSV (hue, 255, 255));
	txRectangle (x, 0, x+1, size_y);
}
```

Этот код нарисует в окне плавный переход между всеми цветами радуги:

![color_hsv_example](https://user-images.githubusercontent.com/33802666/117331258-41afb780-ae9f-11eb-8684-9174395668c2.png)

## int txu::Color::hue ()
Переводит цвет в формат HSV, и возвращает значение hue (цветовой тон). См. [Цветовая модель HSV](https://ru.wikipedia.org/wiki/HSV_(%D1%86%D0%B2%D0%B5%D1%82%D0%BE%D0%B2%D0%B0%D1%8F_%D0%BC%D0%BE%D0%B4%D0%B5%D0%BB%D1%8C)).

## int txu::Color::saturation ()
Переводит цвет в формат HSV, и возвращает значение saturatuion (насыщеность). См. [Цветовая модель HSV](https://ru.wikipedia.org/wiki/HSV_(%D1%86%D0%B2%D0%B5%D1%82%D0%BE%D0%B2%D0%B0%D1%8F_%D0%BC%D0%BE%D0%B4%D0%B5%D0%BB%D1%8C)).

## int txu::Color::value ()
Переводит цвет в формат HSV, и возвращает значение value (яркость). См. [Цветовая модель HSV](https://ru.wikipedia.org/wiki/HSV_(%D1%86%D0%B2%D0%B5%D1%82%D0%BE%D0%B2%D0%B0%D1%8F_%D0%BC%D0%BE%D0%B4%D0%B5%D0%BB%D1%8C)).

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

![color_blend_example](https://user-images.githubusercontent.com/33802666/117331317-52602d80-ae9f-11eb-995e-f1391f8604f6.png)

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

## bool operator == (const Color& a, const Color& b)
Оператор сравнения двух цветов: возвращает true только если a.r == b.r, и a.g == b.g, и a.b == b.b. Альфа-канал не учтён.

## bool operator != (const Color& a, const Color& b)
Оператор сравнения двух цветов: возвращает true, если a.r != b.r, или a.g != b.g, или a.b != b.b. Альфа-канал не учтён.

# txu::Font
Класс, предназначенный для хранения информации о шрифте и установки шрифта в HDC. Класс txu::Font позволяет загружать шрифты непосредственно из файла.

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

![font_example](https://user-images.githubusercontent.com/33802666/117331362-5a1fd200-ae9f-11eb-88ce-51cbb778ea6f.png)

## Конструкторы:
- Font ()
- Font (const char* name, int size_x, int size_y, int weight = FW_DONTCARE, bool italic = false, bool underline = false, bool strikeout = false)
- Font (const Font& that)

## Функции-члены:
- [bool txu::Font::create ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txufontcreate-)
- [bool txu::Font::create (const char* name, int size_x, int size_y, int weight = FW_DONTCARE, bool italic = false, bool underline = false, bool strikeout = false)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txufontcreate-)
- [bool txu::Font::create (const Font& that)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txufontcreate-)
- [bool txu::Font::loadFromFile (const char* filename)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txufontloadfromfile-const-char-filename)
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

## bool txu::Font::loadFromFile (const char* filename)
Позволяет загрузить шрифт из файла. Вы не сможете загрузить шрифт, используя только TXLib или WinApi, поскольку эти библиотеки не предоставляют средств для чтения внутреннего имени шрифта, необходимого для его использования. Мне удалось решить эту проблему, написав собственную функцию чтения файла .ttf, однако, к сожалению, некоторые шрифты всё равно не загружаются, даже если loadFromFile вернёт true.

Я написал небольшой пример:

```
int size_x = 400;
int size_y = 400;

_txWindowStyle = WS_NOFRAME;
txCreateWindow (size_x, size_y);
txDisableAutoPause ();
txu::SetConsoleOutputEnabled (false);

txu::Context context (size_x, size_y);

txu::Font font;
font.loadFromFile ("font.ttf");	
font.setSize (25, 50);

const char* text = "Hello World!";
double hue = 0;

txBegin ();
while (!GetAsyncKeyState (VK_ESCAPE) && !txu::WasExitButtonPressed ())
{
	context.clear (txu::Color (24, 24, 24));

	txu::Color color = txu::Color::HSV (hue, 255, 255);

	context.setColor     (color);
	context.setFillColor (color);
	context.setFont      (font);

	int x = size_x/2 - strlen (text)*font.getSizeX () / 2;
	int y = size_y/2 -               font.getSizeY () / 2;

	txTextOut (x, y, text, context);

	hue += 0.02;
	if (hue > 255) hue = 0;

	context.render ();
	txSleep (0);
}
```

Этот код загружает шрифт из файла "font.ttf", а затем выводит надпись "Hello world!" переливающимся цветом. О том, что такое txu::Context сказанно чуть-чуть ниже.

![font_load_example](https://user-images.githubusercontent.com/33802666/117331419-686dee00-ae9f-11eb-909c-e2456a08367f.gif)

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



# txu::Coord2D
Скорее всего, вы уже сталкивались со структурой POINT из WinApi. Класс Coord2D представляет из себя тоже самое, но с некоторыми преимуществами.
Во первых, POINT способна хранить исключительно целые числа, в то время как Coord2D оперирует с double. А во вторых, для Coord2D определены всевозможные математические операторы. Кроме того, разумеется, вы сможете явно или неявно преобразовать POINT к Coord2D, и обратно.

Представьте ситуацию. У вас есть графический интерфейс и область рисования, которая смещена относительно этого интерфейса. Вам необходимо получить относительные координаты мыши этой области рисования. Это очень легко сделать при помощи Coord2D.

Я накодил такой пример:

```
int size_x = 800;
int size_y = 800;

txCreateWindow (size_x, size_y);
txDisableAutoPause ();

txu::Coord2D drawfield_offset (150, 0);
txu::Context drawfield (size_x - drawfield_offset.x, size_y - drawfield_offset.y);

drawfield.clear (txu::Color (24, 24, 24));

txBegin ();
while (!GetAsyncKeyState (VK_ESCAPE) && !txu::WasExitButtonPressed ())
{
	txSetFillColor (txu::Color (32, 32, 32));
	txClear ();

	txSetFillColor (txu::Color::White);
	txSelectFont ("consolas", 20, 10, FW_BOLD);
	txTextOut (0, size_y/2, "Some ui here!");

	if (txMouseButtons () == 1)
	{
		txu::Coord2D mouse = txMousePos ();
		mouse -= drawfield_offset;

		drawfield.setColor     (txu::Color::White);
		drawfield.setFillColor (txu::Color::White);
		txEllipse (txCoord (mouse - 5), txCoord (mouse + 5), drawfield);
	}

	drawfield.render (txDC (), txCoord (drawfield_offset));
	txSleep (0);
}
```

О том, что такое txu::Context я расскажу чуть позже. В этом примере слева находится абстрактное меню, а справа от него область рисования. 
Если нажать на поле рисования, на нём остаются белые кружки.

![Coord2D_example](https://user-images.githubusercontent.com/33802666/117331646-a2d78b00-ae9f-11eb-9863-cf26e28ed19e.gif)

## Конструкторы класса:
- txu::Coord2D (double x, double y)
- txu::Coord2D (const Coord2D& that)
- txu::Coord2D (POINT point)
- txu::Coord2D ()

## Функции-члены:
- [txu::Coord2D::operator POINT ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucoord2doperator-point-)
- [Coord2D txu::Coord2D::operator - ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#coord2d-txucoord2doperator----%D1%83%D0%BD%D0%B0%D1%80%D0%BD%D1%8B%D0%B9)
- [Coord2D& txu::Coord2D::operator += (const Coord2D& that)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [Coord2D& txu::Coord2D::operator -= (const Coord2D& that)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [Coord2D& txu::Coord2D::operator *= (const Coord2D& that)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [Coord2D& txu::Coord2D::operator /= (const Coord2D& that)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [Coord2D& txu::Coord2D::operator += (double scalar)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%81%D0%BA%D0%B0%D0%BB%D1%8F%D1%80%D0%BD%D1%8B%D0%B5-%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [Coord2D& txu::Coord2D::operator -= (double scalar)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%81%D0%BA%D0%B0%D0%BB%D1%8F%D1%80%D0%BD%D1%8B%D0%B5-%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [Coord2D& txu::Coord2D::operator *= (double scalar)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%81%D0%BA%D0%B0%D0%BB%D1%8F%D1%80%D0%BD%D1%8B%D0%B5-%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [Coord2D& txu::Coord2D::operator /= (double scalar)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%81%D0%BA%D0%B0%D0%BB%D1%8F%D1%80%D0%BD%D1%8B%D0%B5-%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)

## Функции для операций с Coord2D:
- [txu::Coord operator + (const Coord2D& a, const Coord2D& b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [txu::Coord operator - (const Coord2D& a, const Coord2D& b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [txu::Coord operator * (const Coord2D& a, const Coord2D& b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [txu::Coord operator / (const Coord2D& a, const Coord2D& b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [txu::Coord operator + (const Coord2D& coord, double scalar)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%81%D0%BA%D0%B0%D0%BB%D1%8F%D1%80%D0%BD%D1%8B%D0%B5-%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [txu::Coord operator - (const Coord2D& coord, double scalar)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%81%D0%BA%D0%B0%D0%BB%D1%8F%D1%80%D0%BD%D1%8B%D0%B5-%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [txu::Coord operator * (const Coord2D& coord, double scalar)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%81%D0%BA%D0%B0%D0%BB%D1%8F%D1%80%D0%BD%D1%8B%D0%B5-%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [txu::Coord operator / (const Coord2D& coord, double scalar)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%81%D0%BA%D0%B0%D0%BB%D1%8F%D1%80%D0%BD%D1%8B%D0%B5-%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [bool operator == (const Coord2D& a, const Coord2D& b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-operator--const-coord2d-a-const-coord2d-b)
- [bool operator != (const Coord2D& a, const Coord2D& b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-operator--const-coord2da-const-coord2d-b)
- [double Coord2Distance (const Coor2D& a, const Coord2D& b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#double-txucoord2distance-const-coord2d-a-const-coord2d-b)
- [double Coord2DSqrDistance (const Coord2D& a, const Coord2D& b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#double-txucoord2dsqrdistance-const-coord2d-a-const-coord2d-b)

## Макросы для операций с классом:
- txCoord(coord)

## txu::Coord2D::operator POINT ()
Оператор преобразования к POINT.

## Coord2D txu::Coord2D::operator - () (унарный)
Возвращает отрицательный Coord2D.
То есть 

```
Coord2D a (-5, -2); 
Coord2D b ( 5,  2); 
a == -b //true
```

## Математические операторы Coord2D
Делают то же, что и обычные операторы чисел, но применяются к каждмоу из чисел класса Coord2D.
То есть

```
Coord2D a (1, 5);
Coord2D b (2, 3);

Coord2D c = a + b; // c == {3, 8}
```

или

```
Coord2D a (1, 5);
Coord2D b (2, 3);

Coord2D c = a * b; // c == {2, 15}
```

## Скалярные математические операторы Coord2D
Далают то же, что и обычные операторы Coord2D, но скалярное число оперируется с каждым из чисел Coord2D.
То есть

```
Coord2D coord (1, 5);
double scalar = 5;

Coord2D result = coord + scalar; // result == {6, 10}
```

или

```
Coord2D coord (1, 5);
double scalar = 5;

Coord2D result = coord * scalar; // result == {5, 25}
```

## bool operator == (const Coord2D& a, const Coord2D& b)
Оператор сравнения для Coord2D. Возвращает true, если a.x == b.x и a.y == b.y, иначе false.

## bool operator != (const Coord2D&a, const Coord2D& b)
Оператор сравнения для Coord2D. Возвращает true, если a.x != b.x, или a.y != b.y, иначе false.

## double txu::Coord2Distance (const Coord2D& a, const Coord2D& b)
Очень полезная функция. Возвращает численное расстояние между точками a и b по теореме пифагора.

## double txu::Coord2DSqrDistance (const Coord2D& a, const Coord2D& b)
Возвращает численное расстояние между точками a и b, возведённое в квадрат.
Советую использовать это функцию вместо [txu::Coord2Distance](https://github.com/Smok1e/TXUtils/blob/main/README.md#double-txucoord2distance-const-coord2d-a-const-coord2d-b), если вам не нужно точное расстояние (например для сравнения расстояния a и расстояния b), поскольку последней приходится извлекать квадратный корень из расстояния, что является очень дорогой операцией.

## txCoord(coord)
Это макрос для удобства указания координат в функции, принимающие отдельно координату x и y.
Например:

```
txu::Coord2D position (100, 100);
txu::Coord2D size     (25,  50 );

txRectangle (position.x, position.y, position.x + size.x, position.y + size.y);
```

эквивалентно

```
txu::Coord2D position (100, 100);
txu::Coord2D size     (25,  50 );

txRectangle (txCoord (position), txCoord (position + size));
```

И ещё один пример:

```
txu::Coord2D position (100, 100);
double radius = 5;

txEllipse (position.x - 5, position.y - 5, position.x + 5, position.y + 5);
```

так же эквивалентно

```
txu::Coord2D position (100, 100);
double radius = 5;

txEllipse (txCoord (position-5), txCoord (position+5));
```

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

		int h = color.hue        ();
		int s = color.saturation ();
		int v = color.value      ();

		result.setPixel (x, y, txu::Color::HSV ((h + 140) % 255, s, v));
	}
}

txCreateWindow (size_x, size_y);
result.render ();
```

Этот код загрузит картинку из файла "image.bmp" в txu::Context, затем конвертирует цвет каждого пикселя в систему HSV, прибавит к hue 140 и конвертирует цвет обратно в RGB:

![context_example_1](https://user-images.githubusercontent.com/33802666/117331689-af5be380-ae9f-11eb-94c5-6d49013cf082.png)

Или вот пример посложнее:

```
void Blur (txu::Context* source, txu::Context* result, int radius)
{
	int size_x = source -> getSizeX ();
	int size_y = source -> getSizeY ();
	result -> resize (size_x, size_y);

	for (int x = 0; x < size_x; x++)
	{
		for (int y = 0; y < size_y; y++)
		{
			int r = 0, g = 0, b = 0;
			int n = 0;

			for (int _x = x-radius; _x < x+radius; _x++)
			{
				for (int _y = y-radius; _y < y+radius; _y++)
				{
					if (_x < 0 || _x >= size_x || _y < 0 || _y >= size_y) continue;

					txu::Color color = source -> getPixel (_x, _y);
					r += color.r, g += color.g, b += color.b;

					n++;
				}
			}

			if (n == 0)	continue;

			txu::Color color (r/n, g/n, b/n);
			result -> setPixel (x, y, color);
		}
	}
}
```

Эта функция размывает картинку. Вызовем её с радиусом в 5 пикселей:

```
txu::Context source ("image.bmp");
txu::Context result;

Blur (&source, &result, 5);

txCreateWindow (result.getSizeX (), result.getSizeY ());
result.render ();
```

И получим размытое изображение на экране:

![context_example_2](https://user-images.githubusercontent.com/33802666/117331765-bd116900-ae9f-11eb-8100-02d3fe9e0e81.png)

Экземпляром класса можно пользоваться так же, как и HDC. Для этого в нём есть соответствующий оператор.

## Конструкторы класса:
- txu::Context ()
- txu::Context (int size_x, int size_y)
- txu::Context (const Context& that)
- txu::Context (const HDC& dc)
- txu::Context (const char* filename)

## Функции-члены:
- [bool txu::Context::create ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txucontextcreate-)
- [bool txu::Context::create (int size_x, int size_y)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txucontextcreate-)
- [bool txu::Context::create (const Context& that)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txucontextcreate-)
- [bool txu::Context::create (const HDC& dc)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txucontextcreate-)
- [bool txu::Context::create (const char* filename)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txucontextcreate-)
- [bool txu::Context::loadFromFile (const char* filename)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txucontextloadfromfile-const-char-filename)
- [bool txu::Context::saveToFile (const char* filename)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txucontextsavetofile-const-char-filename)
- [int txu::Context::getSizeX ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#int-txucontextgetsizex-)
- [int txu::Context::getSizeY ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#int-txucontextgetsizey-)
- [void txu::Context::resize (int new_size_x, int new_size_y)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txucontextresize-int-new_size_x-int-new_size_y)
- [void txu::Context::render (HDC dc = txDC (), int x = 0, int y = 0, int width = 0, int height = 0)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txucontextrender-hdc-dc--txdc--int-x--0-int-y--0-int-width--0-int-height--0)
- [void txu::Context::clear (txu::Color color)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txucontextclear-txucolor-color)
- [void txu::Context::capture (HWND wnd = nullptr)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txucontextcapture-hwnd-wnd--nullptr)
- [txu::Context::operator HDC& ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucontextoperator-hdc-)
- [RGBQUAD* txu::Context::getBuffer ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#rgbquad-txucontextgetbuffer-)
- [size_t txu::Context::getBufferLength ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#size_t-txucontextgetbufferlength-)
- [RGBQUAD* txu::Context::access (size_t index)](https://github.com/Smok1e/TXUtils/blob/main/README.md#rgbquad-txucontextaccess-size_t-index)
- [RGBQUAD* txu::Context::access (int x, int y)](https://github.com/Smok1e/TXUtils/blob/main/README.md#rgbquad-txucontextaccess-int-x-int-y)
- [void txu::Context::setPixel (int x, int y, txu::Color color)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txucontextsetpixel-int-x-int-y-txucolor-color)
- [txu::Color txu::Context::getPixel (int x, int y)](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucolor-txucontextgetpixel-int-x-int-y)
- [void txu::Context::setColor (txu::Color color, int thikness = 0)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txucontextsetcolor-txucolor-color-int-thikness--0)
- [void txu::Context::setFillColor (txu::Color color)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txucontextsetfillcolor-txucolor-color)
- [void txu::Context::setFont (HFONT font)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txucontextsetfont-hfont-font)
- [void txu::Context::setFont (const char* name, int sx, int sy = -1, int bold = FW_DONTCARE, bool italic = false, bool underline = false, bool strikeout = false, double angle = 0)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txucontextsetfont-const-char-name-int-sx-int-sy---1-int-bold--fw_dontcare-bool-italic--false-bool-underline--false-bool-strikeout--false-double-angle--0)

## bool txu::Context::create (...)
Заново инициализирует изображение в соответствии с указанными параметрами. Возвращает true в случае успеха.

## bool txu::Context::loadFromFile (const char* filename)
Загружает изображение из файла, указанного в параметрах.
Помимо .bmp, я реализовал загрузку изображений формата png, посредством [libpng](http://www.libpng.org/pub/png/libpng.html).
Внимание! Для того, чтобы загрузить файл формата png, убедитесь, что у вас установлена библиотека libpng, а перед включением TXU.h вы объявили макрос TXU_USE_PNG. Возможно, библиотека libpng у вас уже установлена (по крайней мере у меня она уже была), а если нет, вы можете установить её при помощи [vcpkg](https://docs.microsoft.com/ru-ru/cpp/build/vcpkg?view=msvc-160)

Функция вернёт true если изображение загружено успешно, или false - в обратном случае.

Вот небольшой пример загрузки изображения из png-файла:

```
#define TXU_USE_PNG

//-------------------

#include <TXLib.h>
#include <TXU.h>

//-------------------

int main ()
{
	txu::Context image;
	image.loadFromFile ("image.png");
	int size_x = image.getSizeX ();
	int size_y = image.getSizeY ();
	
	_txWindowStyle = WS_NOFRAME;
	txCreateWindow (size_x, size_y);
	
	image.render ();
	
	return 0;
}
```

В результате, на экране кошка.

![context_load_from_file_example](https://user-images.githubusercontent.com/33802666/117331803-c6023a80-ae9f-11eb-82cc-ac27f3f68ebc.png)

## bool txu::Context::saveToFile (const char* filename)
Сохраняет изображение в файл, указанный в параметрах. По умолчанию сохраняет в формате .bmp, однако, если вы подключили использование libpng (см [bool txu::Context::loadFromFile (const char* filename)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txucontextloadfromfile-const-char-filename)), функция автоматически определит его расширение из строки имени. То есть, если в конце имени файла указано ".png", и при этом подключён libpng, то изображение сохранится в формате png. В любых других случаях, изображение будет сохранено в формате bmp.

## int txu::Context::getSizeX ()
Возвращает ширину изображения.

## int txu::Context::getSizeY ()
Возвращает высоту изображения.

## void txu::Context::resize (int new_size_x, int new_size_y)
Меняет размер изображения в соответствии с параметрами, при этом сохраняя исходное изображение. 

## void txu::Context::render (HDC dc = txDC (), int x = 0, int y = 0, int width = 0, int height = 0)
Копирует изображение в HDC, указанный в параметрах. Если HDC не указан, изображение копируется в окно TXLib.
В параметрах так же можно указать координаты и размер копируемого изображения.

## void txu::Context::clear (txu::Color color)
Очищает изображение указанным в параметрах цветом.

## void txu::Context::capture (HWND wnd = nullptr)
Захватывает изображения из окна, указанного в параметре. По умолчанию дексриптор окна равен nullptr, что означает, что захвачен будет весь экран. Изображение автоматически изменится до нужного размера.

## txu::Context::operator HDC& ()
Оператор преобразования к HDC. 

## RGBQUAD* txu::Context::getBuffer ()
Возвращает указатель на начало буффера изображения в формате RGBQUAD.

## size_t txu::Context::getBufferLength ()
Возвращает размер буффера изображения.

## RGBQUAD* txu::Context::access (size_t index)
Возвращает указатель на пиксель изорбажения под индексом, указанным в параметрах. Внутри функции существует проверка индекса, благодаря которой функция вернёт nullptr если индекс вышел за границы массива. Обратите внимание, что эта проверка работает только в debug сборке. Если выйти за границы в сборке release, может произойти исключение access violation. 

## RGBQUAD* txu::Context::access (int x, int y)
Делает то же, что и [txu::Context::access (size_t index)](https://github.com/Smok1e/TXUtils/blob/main/README.md#rgbquad-txucontextaccess-int-x-int-y), но вместа индекса принимает координаты пикселя.

## void txu::Context::setPixel (int x, int y, txu::Color color)
Устанавливает пиксель в точке, указанной параметрами x и y с учётом альфа-канала входного цвета.

## txu::Color txu::Context::getPixel (int x, int y)
Возвращает цвет пикселя по указанным координатам. Если координаты выходят за рамки изображения, функция вернёт txu::Color::Black.

## void txu::Context::setColor (txu::Color color, int thikness = 0)
Устанавливает цвет и толщину обводки для внутреннего HDC. Тоже самое, что и txSetColor.

## void txu::Context::setFillColor (txu::Color color)
Устанавливает цвет заливки для внутреннего HDC. Тоже самое, что и txSetFillColor.

## void txu::Context::setFont (HFONT font)
Устанавливает шрифт для внутреннего HDC, указанный в параметрах. В качестве параметра используйте txu::Font.

## void txu::Context::setFont (const char* name, int sx, int sy = -1, int bold = FW_DONTCARE, bool italic = false, bool underline = false, bool strikeout = false, double angle = 0)
Устанавливает шрифт для внутреннего HDC по указанным параметрам. Тоже самое, что и txSelectFont.

# txu::Time
Класс, предназначенный для представления единиц времени в удобном формате. Поначалу, может показаться, что эта вещь бесполезна. Ведь время это же просто величина, как расстояние и скорость? В простых случаях - так и есть. Программист заводит переменную, к примеру, int timeout и вызвает абстрактную функцию Sleep (timeout). Как правило, для представления времени в программировании используются милисекунды, а значит timeout - время (в милисекундах). Но что если надо представить время не в милисекундах, а, например, в секундах? Тогда значение придётся умножить на 1000, а значит вызов Sleep будет происходить как Sleep (timeout * 1000). Но любой человек, посмотревший на такой код может сказать: А что это за "магическое" число 1000? Магическими числами называют численные выражения, не пояснённые и не обозначенные никакой переменной, из за чего сложно понять для чего они предназначаются. Все эти проблемы и решает класс txu::Time. С его использованием, предыдущий пример будет выглядеть так:
```
txu::Time timeout = txu::Time::seconds (1);
Sleep (timeout);
```

Всё, теперь ничего пояснять не нужно. Вы можете инициализировать класс пятью разными способами из микросекунд, милисекунд, секунд, минут и часов. 

```
txu::Time::microseconds (1000000) == 
txu::Time::miliseconds  (1000)    == 
txu::Time::seconds      (1)       == 
txu::Time::minutes      (1/60)    == 
txu::Time::hours        (1/3600);
```

Все эти записи эквивалентны и равняются одной секунде.

Разумеется, после создания переменной типа Time, вы можете достать из неё значения в любом удобном формате с помощью Time::getMicroseconds, Time::getMilliseconds, и.т.д.

По умолчанию, время присваевается в милисекундах, то есть:

```
txu::Time time = 1000; // будет равна 1000 милисекундам
```

Ну и разумеется, в классе предусмотрен оператор приведения к double:
```
double time = txu::Time::seconds (1); // будет равна 1000 милисекундам
```

Оператор так же возвращает значение в милисекундах. Поэтому, вы можете использовать Time как обычное число в функциях, принимающих время в милисекундах.

# Внутренние типы
- [txu::Time::time_t](https://github.com/Smok1e/TXUtils/blob/main/README.md#txutimetime_t)

# Конструкторы:
- txu::Time::Time (Time::time_t time)
- txu::Time::Time (const Time& that)
- txu::Time::Time ()

# Функции-члены:
- [txu::Time::time_t txu::Time::getMicroseconds ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D0%B4%D0%BB%D1%8F-%D0%BF%D0%BE%D0%BB%D1%83%D1%87%D0%B5%D0%BD%D0%B8%D1%8F-%D0%B2%D1%80%D0%B5%D0%BC%D0%B5%D0%BD%D0%B8)
- [txu::Time::time_t txu::Time::getMilliseconds ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D0%B4%D0%BB%D1%8F-%D0%BF%D0%BE%D0%BB%D1%83%D1%87%D0%B5%D0%BD%D0%B8%D1%8F-%D0%B2%D1%80%D0%B5%D0%BC%D0%B5%D0%BD%D0%B8)
- [txu::Time::time_t txu::Time::getSeconds ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D0%B4%D0%BB%D1%8F-%D0%BF%D0%BE%D0%BB%D1%83%D1%87%D0%B5%D0%BD%D0%B8%D1%8F-%D0%B2%D1%80%D0%B5%D0%BC%D0%B5%D0%BD%D0%B8)
- [txu::Time::time_t txu::Time::getMinutes ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D0%B4%D0%BB%D1%8F-%D0%BF%D0%BE%D0%BB%D1%83%D1%87%D0%B5%D0%BD%D0%B8%D1%8F-%D0%B2%D1%80%D0%B5%D0%BC%D0%B5%D0%BD%D0%B8)
- [txu::Time::time_t txu::Time::getHours ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D0%B4%D0%BB%D1%8F-%D0%BF%D0%BE%D0%BB%D1%83%D1%87%D0%B5%D0%BD%D0%B8%D1%8F-%D0%B2%D1%80%D0%B5%D0%BC%D0%B5%D0%BD%D0%B8)
- [txu::Time operator double ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#txutimeoperator-double-)
- [txu::Time txu::Time::microseconds (Time::time_t microseconds)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%81%D1%82%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D0%B8%D0%BD%D0%B8%D1%86%D0%B8%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D0%B8)
- [txu::Time txu::Time::milliseconds (Time::time_t millisedonds)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%81%D1%82%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D0%B8%D0%BD%D0%B8%D1%86%D0%B8%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D0%B8)
- [txu::Time txu::Time::seconds (Time::time_t seconds)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%81%D1%82%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D0%B8%D0%BD%D0%B8%D1%86%D0%B8%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D0%B8)
- [txu::time txu::Time::minutes (Time::time_t minutes)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%81%D1%82%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D0%B8%D0%BD%D0%B8%D1%86%D0%B8%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D0%B8)
- [txu::Time txu::Time::hours (Time::time_t hours)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%81%D1%82%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D0%B8%D0%BD%D0%B8%D1%86%D0%B8%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D0%B8)

## txu::Time::time_t
Это тип абстрактной единицы времени. По сути представляет из себя знаковое число с плавающей точкой.

## Функции для получения времени
Возвращают время в указанных единицах. getMicroseconds вернёт микросекунды, getMilliseconds - милисекунды, и так далее.

## txu::Time::operator double ()
Возвращает время в милисекундах.

## Статические функции инициализации
Функции txu::Time::milliseconds, txu::Time::seconds и другие без префикса get - являются статическими (то есть их можно вызвать, не создавая переменную типа Time) и возвращают объект типа txu::Time, созданный в указанной еденице времени из числа, указанного в параметре.

# txu::Timer
Это сопутствующий txu::Time класс. Он выполняет функцию таймера, как несложно догадаться из названия. Класс очень простой, в нём всего 2 функции, но полезный. Он считает время не в милисекундах, как например примитывный GetTickCount (), а в микросекундах, используя для работы значения частоты и тиков процессора, так что он позволяет выявить даже самые незначительные различия во времени.

Его использование крайне простое, например, для измерения времени, которое занимает функция test, подойдёт следующий код:

```
txu::Timer timer;
timer.start ();

test ();

txu::Time elapsed = timer.getTime ();
printf ("Function call elapsed %lf microseconds\n", elapsed.getMicroseconds ());
```

Для начала отсчёта нужно вызвать функцию start. Дальше, для получения прошедшего времени на текущий момент - вызвовите функцию getTime (), которая вернёт объект типа txu::Time.

# Конструкторы класса:
- txu::Timer::Timer (const Timer& that) 
- txu::Timer::Timer ()

# Функции-члены:
- void txu::Timer::srart ()
- txu::Time txu::Timer::getTime ()

## void txu::Timer::start ()
Начинает отсчёт времени с текущего момента.

## txu::Timer txu::Timer::getTime ()
Возвращает прошедшее с момента вызва функции start время в виде объекта txu::Time.

# Спасибо за использование TXUtils!
Я буду рад ответить на ваши вопросы и предложения. В будущем я собираюсь добавить ещё множество удобных фич!
