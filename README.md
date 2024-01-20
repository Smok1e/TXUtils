# TXUtils
TXUtils - это библиотека с открытым исходным кодом, написанная мною для ~~себя~~ облегчения и удобства работы с графикой, используя [TXLib](http://storage.ded32.net.ru/Lib/TX/TXUpdate/Doc/HTML.ru/).
Библиотека совместима с MSVC (Microsoft Visual Studio) и с MinGW (Скорее всего, установлена вами вместе с CodeBlocks).
Я очень постарался, чтобы моя библиотека как можно меньше влияла на TXLib: на данный момент, включение TXUtils в программу никак не скажется её работе. Вы можете использовать TXLib как обычно.

# Зависимости
Вообще я за здоровый образ жизни. Однако, разумеется, для работы TXUtils необходим [TXLib](http://storage.ded32.net.ru/Lib/TX/TXUpdate/Doc/HTML.ru/). 
Так же, рекомендуется установить [libpng](http://www.libpng.org/pub/png/libpng.html), если у вас её нет. Библиотека может работать и без неё, но тогда вы не сможете работать с форматом png используя [txu::Context](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucontext).

# Установка
Достаточно скачать репозиторий
`git clone https://github.com/Smok1e/TXUtils`

А затем подключить файл TXU.h к вашей программе после подключения TXLIb:

```c++
#include <TXLib.h>
#include "C:\path\to\txutils\TXU.h"
```

Готово!

Примечание: я гарантирую работу библиотеки только с компилятороми MSVC и MinGW. Я не отвечаю за совместимость с другими компиляторами.

# Функции библиотеки:
- [void txu::WasExitButtonPressed()](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txuwasexitbuttonpressed-)
- [int  txu::GetMouseWheel()](https://github.com/Smok1e/TXUtils/blob/main/README.md#int-txugetmousewheel-)
- [void txu::SetConsoleOutputEnabled(bool enable)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txusetconsoleoutputenabled-bool-enable)
- [bool txu::IsConsoleOutputEnabled()](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txuisconsoleoutputenabled-)
- [bool txu::SetWindowIcon(const char* filename)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txusetwindowicon-const-char-filename)
- [void txu::SetWindowCursor(HCURSOR cursor)](https://github.com/Smok1e/TXUtils#void-txusetwindowcursor-hcursor-cursor)
- [void txu::SetCursorVisible(bool visible)](https://github.com/Smok1e/TXUtils#void-txusetcursorvisible-bool-visible)
- [void txu::IsCursorVisible()](https://github.com/Smok1e/TXUtils#bool-txuiscursorvisible-)
- [void txu::SetWindowResizingEnabled](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txusetwindowresizingenabled-bool-enable-hwnd-wnd--txwindow-)
- [bool txu::IsWindowResizingEnabled](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txuiswindowresizingenabled-hwnd-wnd--txwindow-)
- [bool txu::WasWindowResized](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txuwaswindowresized-)
- [bool txu::GetNewWindowSize(POINT* size)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txugetnewwindowsize-point-size)

# Макросы
- [WS_NOFRAME](https://github.com/Smok1e/TXUtils/blob/main/README.md#ws_noframe)

# Классы библиотеки:
- [txu::Color](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucolor)
- [txu::Font](https://github.com/Smok1e/TXUtils/blob/main/README.md#txufont)
- [txu::Coord2D](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucoord2d)
- [txu::Context](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucontext)
- [txu::Time](https://github.com/Smok1e/TXUtils/blob/main/README.md#txutime)
- [txu::Timer](https://github.com/Smok1e/TXUtils/blob/main/README.md#txutimer)
- [txu::Sound](https://github.com/Smok1e/TXUtils/blob/main/README.md#txusound)

## bool txu::WasExitButtonPressed()
Возвращает true, если был нажат крестик в меню окна, иначе false, для того чтобы программист сам мог отреагировать на нажатие крестика. Например так:

```c++
txCreateWindow(800, 800);

while (!GetAsyncKeyState(VK_ESCAPE))
{
	if (txu::WasExitButtonPressed())
		MessageBox(txWindow(), "THERE IS NO EXIT!", "NO!", MB_OK | MB_ICONERROR);

	txSleep(10);
}
```

![WasExitButtonPressed_example](https://user-images.githubusercontent.com/33802666/117330931-e2ea3e00-ae9e-11eb-91c9-a5e5cf0ac772.gif)

## int txu::GetMouseWheel()
Возвращает сторону, в которую повернулось колесо мыши.
Если колесо повернулось вниз, функция вернёт -1, если вверх, 1, а если колесо не было повёрнуто - функция вернёт 0. 
Значение стороны, в которую было повёрнуто колёсико, хранится и не изменяется до тех пор, пока оно не повернётся снова или не будет вызвана эта функция.

## void txu::SetConsoleOutputEnabled(bool enable)
Разрешает или запрещает дублирование вывода stdout поверх окна txlib. В результате тестов я выясненио, что рисование вывода поверх окна снижает производительность программы.

## bool txu::IsConsoleOutputEnabled()
Возвращает true, если рисование консоли поверх окна разрешено.

## bool txu::SetWindowIcon(const char* filename)
Вам не надоела иконка TXLib'а, которую [дед](http://ded32.net.ru/) повесил на все ваши окна? Мне да, поэтому я и сделал эту функцию.
Она устанавливает окну TXLib иконку, загруженную из файла, указанного в параметрах. Если картинка загружена успешно, функция вернёт true. В обратном случае - false.
Иконка должна быть в формате [.ico](https://ru.wikipedia.org/wiki/ICO_(%D1%84%D0%BE%D1%80%D0%BC%D0%B0%D1%82_%D1%84%D0%B0%D0%B9%D0%BB%D0%B0))

Я нарисовал такую иконку для своей программы:

![setwindowicon_example_1](https://user-images.githubusercontent.com/33802666/117330977-f0072d00-ae9e-11eb-8355-25fd6b65d703.png)

И вызвал функцию txu::SetWindowIcon:

```c++
txCreateWindow (800, 800);
txu::SetWindowIcon ("icon.ico");
```

Теперь в заголовке окна висит моя собственная иконка:

![setwindowicon_example_2](https://user-images.githubusercontent.com/33802666/117331032-001f0c80-ae9f-11eb-82e1-cf1503ff5560.png)

Так же, советую вам [плагин для фотошопа, позволяющий сохранять картинки в формате ico](https://rugraphics.ru/photoshop/plagin-format-ico-v-photoshop-cs6-i-cc).

И напоследок, если вам не нравится то, что TXLib устанавливает своё имя в заголовке окна, используйте функцию [SetWindowText](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowtexta) из WinApi.

## void txu::SetWindowCursor(HCURSOR cursor)
Устанавливает курсор, переданный в качестве параметра, в окно TXLib.
Если в качестве параметра передать нулевой указатель, обработка курсора прекратится, то есть установится стандартный курсор, определённый системой.

## void txu::SetCursorVisible(bool visible)
Устанавливает видимость курсора внутри окна TXLib. false - курсор не будет видно, true - курсор будет видно.

## bool txu::IsCursorVisible()
Возвращает состояние видимости курсора.

## void txu::SetWindowResizingEnabled(bool enable, HWND wnd = txWindow())
Разрешает или запрещает пользователю изменять размер окна.

## bool txu::IsWindowResizingEnabled(HWND wnd = txWindow())
Возвращает true, если изменение размера окна разрешено.

## bool txu::WasWindowResized()
Возвращает true, если размер окна TXLib был изменён пользователем, но функция GetNewWindowSize или WasWindowResized ещё не была вызвана.

## bool txu::GetNewWindowSize(POINT* size)
Переменная, на которую ссылается указатель size получает последний изменённый пользователем размер окна. 
Возвращает true, если пользователь изменил размер окна, но функция GetNewWindowSize или WasWindowResized ещё не была вызвана.
TXUtils автоматически изменяет размер нужных буферов окна, когда его размер меняется. Вот небольшой пример обработки изменения размера окна: 

```c++
txCreateWindow(800, 800);
txu::SetWindowResizingEnabled (true);

while (!txu::WasExitButtonPressed())
{
	POINT size = {};
	if (txu::GetNewWindowSize(&size))
	{
		printf("New window size: {%d, %d}\n", size.x, size.y);
		// ...
	}
}
```

## WS_NOFRAME
Стиль окна без заголовка и рамок.
```c++
_txWindowStyle = WS_NOFRAME;
txCreateWindow (800, 800);
```

# txu::Color
Класс, предназначеный для хранения цвета и операций с ним.
Вы можете пользоваться txu::Color так же, как и COLORREF, поскольку класс содержит соответствующий оператор.
Например:
```c++
COLORREF colorref = txu::Color(0, 130, 255);
```
или
```c++
txSetFillColor(txu::Color (24, 24, 24));
```
Класс содержит публичные поля `r`, `g`, `b` и `a` для хранения значений красного, зелёного, синего и калфа-канала соответственно.

Класс содержит 24 предопределённых статических цвета, которые можно получить, подобно `txu::Color::White`. Ниже представлен список названий и соответствующих им цветов всех статических экземпляров:

![txu_color_list](https://user-images.githubusercontent.com/33802666/125601749-b474bf78-ab9b-4c28-8fd5-e1cbc715a602.png)

## Конструкторы:
- txu::Color(int r, int g, int b, int a)
- txu::Color(int r, int g, int b)
- txu::Color(const Color& that)
- txu::Color(RGBQUAD rgbquad)
- txu::Color(COLORREF colorref)
- txu::Color()

## Функции-члены:
- [static Color Interpolate(Color a, Color b, double t)](https://github.com/Smok1e/TXUtils/blob/main/README.md#color-txucolorinterpolate-color-a-color-b-color-t)
- [static Color Interpolate(const std::initializer_list \<Color\>& list, double t)](https://github.com/Smok1e/TXUtils/blob/main/README.md#color-txucolorinterpolate-const-stdinitializer_list-color-list-double-t)
- [static Color Random()](https://github.com/Smok1e/TXUtils/blob/main/README.md#color-txucolorrandom-)
- [static Color Choose(Color def = Black)](https://github.com/Smok1e/TXUtils/blob/main/README.md#color-txucolorchoose-color-def--black)
- [operator RGBQUAD()](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucoloropreator-rgbquad-)
- [operator COLORREF()](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucoloroperator-colorref-)
- [Color operator!()](https://github.com/Smok1e/TXUtils/blob/main/README.md#color-txucoloroperator--)
- [Color& operator=(const Color& that)](https://github.com/Smok1e/TXUtils/blob/main/README.md#color-txucoloroperator--const-color-that)
- [static Color HSV(int h, int s, int v)](https://github.com/Smok1e/TXUtils/blob/main/README.md#static-color-txucolorhsv-int-h-int-s-int-)
- [int hue()](https://github.com/Smok1e/TXUtils/blob/main/README.md#int-txucolorhue-)
- [int saturation()](https://github.com/Smok1e/TXUtils/blob/main/README.md#int-txucolorsaturation-)
- [int value()](https://github.com/Smok1e/TXUtils/blob/main/README.md#int-txucolorvalue-)
- [int average()](https://github.com/Smok1e/TXUtils/blob/main/README.md#int-txucoloraverage-)

## Функции для операций с цветом:
- [txu::Color Blend(Color a, Color b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucolor-blend-color-a-color-b)
- [txu::Color operator<<=(Color a, Color b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucolor-operator--color-a-color-b)
- [bool operator==(const Color& a, const Color& b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-operator--const-color-a-const-color-b)
- [bool operator!=(const Color& a, const COlor& b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-operator--const-color-a-const-color-b-1)

## Color txu::Color::Interpolate (Color a, Color b, Color t)
Эта статическая функция позволяет создавать плавный переход между цветами в зависимости от параметра t.
При t == 0 функция вернёт цвет A, при t == 1 функция вернёт цвет B, а при t == 0.5 функция вернёт средний цвет между A и B.
Например:
```c++
int size_x = 800;
int size_y = 100;

txCreateWindow(size_x, size_y);
for (int x = 0; x < size_x; x++)
{
	double t = static_cast<double>(x) / size_x;
	txSetColor(txu::Color::Interpolate(txu::Color::DarkCyan, txu::Color::DarkPink, t));
	txRectangle(x, 0, x+1, size_y);
}
```

нарисует на экране плавный градиент от синего к розовому:

![color_interpolate_example](https://user-images.githubusercontent.com/33802666/117331183-2d6bba80-ae9f-11eb-8345-622fd799f51a.png)

## Color txu::Color::Interpolate (const std::initializer_list \<Color\>& list, double t)
Тоже самое что и txu::Color::Interpolate (Color a, Color b, double t), но может принять произвольное количество цветов. Например:

```c++
int size_x = 800;
int size_y = 100;

txCreateWindow(size_x, size_y);
for (int x = 0; x < size_x; x++)
{
	double t = static_cast<double>(x) / size_x;
	txu::Color color = txu::Color::Interpolate({txu::Color::DarkCyan, txu::Color::DarkPink, txu::Color::Green}, t);
	txSetColor(color);
	txRectangle(x, 0, x+1, size_y);
}
```

нарисует плавный переход от синего к розовому, а от розового к зелёному:

![color_interpolate_initializer_list_example](https://user-images.githubusercontent.com/33802666/117331231-39577c80-ae9f-11eb-961f-6b6fc0e6d246.png)

## Color txu::Color::Random()
Статическая функция. Возвращает случайный цвет.

## Color txu::Color::Choose(Color def = Black)
Статическая функция. Вызывает стандартное диалоговое окно выбора цвета windows и возвращает выбранный пользователем цвет, если была нажата кнопка ОК.
Если пользователь отменил выбор цвета, функция вернёт цвет, переданный в опциональном параметре (по умолчанию - чёрный).

![color_choose_example](https://user-images.githubusercontent.com/33802666/120930771-5fb74480-c6f7-11eb-9744-77f37f612365.png)

## txu::Color::opreator RGBQUAD()
Оператор преобразования к RGBQUAD

## txu::Color::operator COLORREF()
Оператор преобразования к COLORREF.
Обратите внимание, что если альфа-канал цвета равен нулю, то оператор COLORREF вернёт TX_TRANSPARENT.
В остальных же случаях альфа-канал не учитывается. К сожалению, хоть размер COLORREF и равен четырём байтам, в одном из которых, в теории, можно быль бы хранить значение альфа-канала, GDI windows не позволяет оперировать полу-прозрачными цветами нативно, а младший байт COLORREF'a считается зарезервированным.

## Color txu::Color::operator!()
Возвращает инвертированный цвет:
```c++
txu::Color black (0, 0, 0)
txu::Color white = !black //Белый цвет
```

## Color& txu::Color::operator=(const Color& that)
Оператор присваивания

## static Color txu::Color::HSV(int h, int s, int v)
Возвращает цвет, созданный на основе системы [HSV](https://ru.wikipedia.org/wiki/HSV_(%D1%86%D0%B2%D0%B5%D1%82%D0%BE%D0%B2%D0%B0%D1%8F_%D0%BC%D0%BE%D0%B4%D0%B5%D0%BB%D1%8C)).
Значения h, s и v должны быть в диапазоне от 0 до 255.
Эта функция является статической, то есть её можно вызвать не создавая экземпляра класса Color.
Например:

```c++
int size_x = 800;
int size_y = 100;

txCreateWindow(size_x, size_y);
for (int x = 0; x < size_x; x++)
{
	double t = static_cast<double>(x) / size_x;
	int hue = t * 255;

	txSetColor(txu::Color::HSV(hue, 255, 255));
	txRectangle(x, 0, x+1, size_y);
}
```

нарисует в окне плавный переход между всеми цветами радуги:

![color_hsv_example](https://user-images.githubusercontent.com/33802666/117331258-41afb780-ae9f-11eb-8684-9174395668c2.png)

## int txu::Color::hue()
Преобразует цвет в формат HSV и возвращает значение hue (цветовой тон). См. [Цветовая модель HSV](https://ru.wikipedia.org/wiki/HSV_(%D1%86%D0%B2%D0%B5%D1%82%D0%BE%D0%B2%D0%B0%D1%8F_%D0%BC%D0%BE%D0%B4%D0%B5%D0%BB%D1%8C)).

## int txu::Color::saturation()
Преобразует цвет в формат HSV и возвращает значение saturatuion (насыщеность). См. [Цветовая модель HSV](https://ru.wikipedia.org/wiki/HSV_(%D1%86%D0%B2%D0%B5%D1%82%D0%BE%D0%B2%D0%B0%D1%8F_%D0%BC%D0%BE%D0%B4%D0%B5%D0%BB%D1%8C)).

## int txu::Color::value()
Преобразует цвет в формат HSV и возвращает значение value (яркость). См. [Цветовая модель HSV](https://ru.wikipedia.org/wiki/HSV_(%D1%86%D0%B2%D0%B5%D1%82%D0%BE%D0%B2%D0%B0%D1%8F_%D0%BC%D0%BE%D0%B4%D0%B5%D0%BB%D1%8C)).

## int txu::Color::average()
Возвращает среднее значение каналов r, g и b. Альфа-канал не учитывается.

## txu::Color Blend(Color a, Color b)
Функция смешивания цветов с учётом альфа-канала.
Например:
```c++
int size_x = 400;
int size_y = 400;

txCreateWindow(size_x, size_y);

txSetFillColor(txu::Color(24, 24, 24));
txClear();

txSetFillColor(txu::Color::White);
txRectangle(50, 75, 200, 150);

for (int x = 100; x < 300; x++)
	for (int y = 100; y < 300; y++)
		txSetPixel(x, y, txu::Blend(txu::Color (0, 130, 255, 100), txGetPixel(x, y)));
```

нарисует полу-прозрачный синий квадрат:

![color_blend_example](https://user-images.githubusercontent.com/33802666/117331317-52602d80-ae9f-11eb-995e-f1391f8604f6.png)

Примечание: функция Blend учитывает альфа-канал только первого цвета.

## txu::Color operator<<=(Color a, Color b)
Делает то же, что и Blend, однако цвета повёрнуты местами. То есть:
```c++
txu::Color color = txu::Blend(a, b);
```
эквивалентно
```c++
txu::Color color = b <<= a;
```

## bool operator==(const Color& a, const Color& b)
Оператор сравнения двух цветов: возвращает true только если a.r == b.r, и a.g == b.g, и a.b == b.b. Альфа-канал не учтён.

## bool operator!=(const Color& a, const Color& b)
Оператор сравнения двух цветов: возвращает true, если a.r != b.r, или a.g != b.g, или a.b != b.b. Альфа-канал не учтён.

# txu::Font
Класс, предназначенный для хранения информации о шрифте и установки шрифта в HDC. Класс txu::Font позволяет загружать шрифты непосредственно из файла.

Пример использования:
```
int size_x = 400;
int size_y = 400;

const char* text = "Hello World!";

txCreateWindow(size_x, size_y);

txSetFillColor(txu::Color(24, 24, 24));
txClear();

txu::Font font("consolas", 25, 50, FW_BOLD);
font.setItalicEnabled   (true);
font.setUnderlineEnabled(true);
font.select();

txSetColor(txu::Color::White);
txTextOut(size_x/2 - txGetTextExtentX(text)/2, size_y/2 - txGetTextExtentY(text)/2, text);
```

выведет на экран надпись:

![font_example](https://user-images.githubusercontent.com/33802666/117331362-5a1fd200-ae9f-11eb-88ce-51cbb778ea6f.png)

## Конструкторы:
- Font()
- Font(const char* name, int size_x, int size_y, int weight = FW_DONTCARE, bool italic = false, bool underline = false, bool strikeout = false)
- Font(const Font& that)

## Функции-члены:
- [bool txu::Font::create()](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txufontcreate-)
- [bool txu::Font::create(const char* name, int size_x, int size_y, int weight = FW_DONTCARE, bool italic = false, bool underline = false, bool strikeout = false)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txufontcreate-)
- [bool txu::Font::create(const Font& that)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txufontcreate-)
- [bool txu::Font::loadFromFile(const char* filename)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txufontloadfromfile-const-char-filename)
- [void txu::Font::setSize(Coord2D size)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txufontsetsize-coord2d-size)
- [void txu::Font::setSize(int size_x, int size_y)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txufontsetsize-int-size_x-int-size_y)
- [Coord2D txu::Font::getSize()](https://github.com/Smok1e/TXUtils/blob/main/README.md#coord2d-txufontgetsize-)
- [int txu::Font::getSizeX()](https://github.com/Smok1e/TXUtils/blob/main/README.md#int-txufontgetsizex-)
- [int txu::Font::getSizeY()](https://github.com/Smok1e/TXUtils/blob/main/README.md#int-txufontgetsizey-)
- [void txu::Font::setWeight(int weight)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txufontsetweight-int-weight)
- [int txu::Font::getWeight()](https://github.com/Smok1e/TXUtils/blob/main/README.md#int-txufontgetweight-)
- [void txu::Font::setItalicEnabled(bool enable)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txufontsetitalicenabled-bool-enabled)
- [bool txu::Font::getItalicEnabled()](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txufontgetitalicenabled-)
- [void txu::Font::setUnderlineEnabled(bool enable)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txufontsetunderlineenabled-bool-enable)
- [bool txu::Font::getUnderlineEnabled()](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txufontgetunderlineenabled-)
- [void txu::Font::setStrikeoutEnabled(bool enable)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txufontsetstrikeoutenabled-bool-enable)
- [bool txu::Font::getStrikeoutEnabled()](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txufontgetstrikeoutenabled-)
- [void setName (const char* name)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txufontsetname-const-char-name)
- [const char* getName()](https://github.com/Smok1e/TXUtils/blob/main/README.md#const-char-txufontgetname-)
- [HFONT getSystemHandle()](https://github.com/Smok1e/TXUtils/blob/main/README.md#hfont-txufontgetsystemhandle-)
- [operator HFONT()](https://github.com/Smok1e/TXUtils/blob/main/README.md#txufontoperator-hfont-)
- [void select(HDC dc = txDC())](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txufontselect-hdc-dc--txdc-)


## bool txu::Font::create(...)
Заново инициализирует шрифт с указанными параметрами. Возвращает true в случае успеха, иначе false.

## bool txu::Font::loadFromFile(const char* filename)
Позволяет загрузить шрифт из файла. Вы не сможете загрузить шрифт, используя только TXLib или WinApi, поскольку эти библиотеки не предоставляют средств для чтения внутреннего имени шрифта, необходимого для его использования. Мне удалось решить эту проблему, написав собственную функцию чтения файла .ttf, однако, к сожалению, некоторые шрифты всё равно не загружаются, даже если loadFromFile вернёт true.

Я написал небольшой пример:

```c++
int size_x = 400;
int size_y = 400;

_txWindowStyle = WS_NOFRAME;
txCreateWindow(size_x, size_y);
txDisableAutoPause();
txu::SetConsoleOutputEnabled(false);

txu::Context context(size_x, size_y);

txu::Font font;
font.loadFromFile("font.ttf");	
font.setSize(25, 50);

const char* text = "Hello World!";
double hue = 0;

txBegin();
while (!GetAsyncKeyState(VK_ESCAPE) && !txu::WasExitButtonPressed())
{
	context.clear(txu::Color(24, 24, 24));

	txu::Color color = txu::Color::HSV(hue, 255, 255);

	context.setColor    (color);
	context.setFillColor(color);
	context.setFont     (font);

	int x = size_x/2 - strlen(text)*font.getSizeX() / 2;
	int y = size_y/2 -              font.getSizeY() / 2;

	txTextOut(x, y, text, context);

	hue += 0.02;
	if (hue > 255) hue = 0;

	context.render();
	txSleep(0);
}
```

Этот код загружает шрифт из файла "font.ttf", а затем выводит надпись "Hello world!" переливающимся цветом. О том, что такое txu::Context сказанно чуть-чуть ниже.

![font_load_example](https://user-images.githubusercontent.com/33802666/117331419-686dee00-ae9f-11eb-909c-e2456a08367f.gif)

## void txu::Font::setSize(Coord2D size)
Устанавливает размер шрифта.

## void txu::Font::setSize(int size_x, int size_y)
Устанавливает размер шрифта.

## Coord2D txu::Font::getSize()
Возвращает размер шрифта.

## int txu::Font::getSizeX()
Возвращает ширину шрифта.

## int txu::Font::getSizeY()
Возвращает высоту шрифта.

## void txu::Font::setWeight(int weight)
Устанавливает толщину шрифта. См. [CreateFont](https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createfonta#parameters)

## int txu::Font::getWeight()
Возвращает толщину шрифта.

## void txu::Font::setItalicEnabled(bool enabled)
Включает или отключает прописной шрифт.

## bool txu::Font::getItalicEnabled()
Возвращает true если прописной шрифт включён, false в обратном случае.

## void txu::Font::setUnderlineEnabled(bool enable)
Включает или отключает подчёркивание текста.

## bool txu::Font::getUnderlineEnabled()
Возвращает true если подчёркивание текста включено, в обратном случае false.

## void txu::Font::setStrikeoutEnabled(bool enable)
Включает или отключает зачёркивание текста.

## bool txu::Font::getStrikeoutEnabled()
Возвращает true если зачёркивание текста включено, в обратном случае false.

## void txu::Font::setName(const char* name)
Устанавливает имя шрифта.

## const char* txu::Font::getName()
Возвращает имя шрифта.

## HFONT txu::Font::getSystemHandle()
Возвращает дескриптор шрифта winapi.

## txu::Font::operator HFONT()
Оператор преобразования к HFONT.

## void txu::Font::select(HDC dc = txDC())
Устанавливает шрифт к HDC указанному в параметре. По умолчанию это txDC ().

# txu::Coord2D
Скорее всего, вы уже сталкивались со структурой POINT из WinApi. Класс Coord2D представляет из себя тоже самое, но с некоторыми преимуществами.
Во первых, POINT способна хранить исключительно целые числа, в то время как Coord2D оперирует с double. А во вторых, для Coord2D определены всевозможные математические операторы. Кроме того, разумеется, вы можете преобразовать POINT к Coord2D, и обратно.

Представьте ситуацию. У вас есть графический интерфейс и область рисования, которая смещена относительно этого интерфейса. Вам необходимо получить относительные координаты мыши этой области рисования. Это очень легко сделать при помощи Coord2D.

Я накодил такой пример:

```c++
int size_x = 800;
int size_y = 800;

txCreateWindow(size_x, size_y);
txDisableAutoPause();

txu::Coord2D drawfield_offset(150, 0);
txu::Context drawfield(size_x - drawfield_offset.x, size_y - drawfield_offset.y);

drawfield.clear(txu::Color (24, 24, 24));

txBegin();
while (!GetAsyncKeyState(VK_ESCAPE) && !txu::WasExitButtonPressed())
{
	txSetFillColor(txu::Color (32, 32, 32));
	txClear();

	txSetFillColor(txu::Color::White);
	txSelectFont("consolas", 20, 10, FW_BOLD);
	txTextOut(0, size_y/2, "Some ui here!");

	if (txMouseButtons() == 1)
	{
		txu::Coord2D mouse = txMousePos();
		mouse -= drawfield_offset;

		drawfield.setColor    (txu::Color::White);
		drawfield.setFillColor(txu::Color::White);
		txEllipse(txCoord(mouse - 5), txCoord(mouse + 5), drawfield);
	}

	drawfield.render(txDC(), txCoord(drawfield_offset));
	txSleep(0);
}
```

О том, что такое txu::Context, я расскажу чуть позже. В этом примере слева находится меню, а справа от него область рисования. 
Если нажать на поле рисования, на нём остаются белые кружки.

![Coord2D_example](https://user-images.githubusercontent.com/33802666/117331646-a2d78b00-ae9f-11eb-9863-cf26e28ed19e.gif)

## Конструкторы класса:
- txu::Coord2D(double x, double y)
- txu::Coord2D(const Coord2D& that)
- txu::Coord2D(POINT point)
- txu::Coord2D()

## Функции-члены:
- [static txu::Coord2D txu::Coord2D::Screen()](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucoord2d-txucoord2dscreen-)
- [txu::Coord2D::operator POINT()](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucoord2doperator-point-)
- [Coord2D txu::Coord2D::operator-()](https://github.com/Smok1e/TXUtils/blob/main/README.md#coord2d-txucoord2doperator----%D1%83%D0%BD%D0%B0%D1%80%D0%BD%D1%8B%D0%B9)
- [Coord2D& txu::Coord2D::operator+=(const Coord2D& that)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [Coord2D& txu::Coord2D::operator-=(const Coord2D& that)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [Coord2D& txu::Coord2D::operator*=(const Coord2D& that)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [Coord2D& txu::Coord2D::operator/=(const Coord2D& that)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [Coord2D& txu::Coord2D::operator+=(double scalar)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%81%D0%BA%D0%B0%D0%BB%D1%8F%D1%80%D0%BD%D1%8B%D0%B5-%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [Coord2D& txu::Coord2D::operator-=(double scalar)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%81%D0%BA%D0%B0%D0%BB%D1%8F%D1%80%D0%BD%D1%8B%D0%B5-%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [Coord2D& txu::Coord2D::operator*=(double scalar)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%81%D0%BA%D0%B0%D0%BB%D1%8F%D1%80%D0%BD%D1%8B%D0%B5-%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [Coord2D& txu::Coord2D::operator/=(double scalar)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%81%D0%BA%D0%B0%D0%BB%D1%8F%D1%80%D0%BD%D1%8B%D0%B5-%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)

## Функции для операций с Coord2D:
- [txu::Coord operator+(const Coord2D& a, const Coord2D& b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [txu::Coord operator-(const Coord2D& a, const Coord2D& b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [txu::Coord operator*(const Coord2D& a, const Coord2D& b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [txu::Coord operator/(const Coord2D& a, const Coord2D& b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [txu::Coord operator+(const Coord2D& coord, double scalar)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%81%D0%BA%D0%B0%D0%BB%D1%8F%D1%80%D0%BD%D1%8B%D0%B5-%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [txu::Coord operator-(const Coord2D& coord, double scalar)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%81%D0%BA%D0%B0%D0%BB%D1%8F%D1%80%D0%BD%D1%8B%D0%B5-%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [txu::Coord operator*(const Coord2D& coord, double scalar)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%81%D0%BA%D0%B0%D0%BB%D1%8F%D1%80%D0%BD%D1%8B%D0%B5-%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [txu::Coord operator/(const Coord2D& coord, double scalar)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%81%D0%BA%D0%B0%D0%BB%D1%8F%D1%80%D0%BD%D1%8B%D0%B5-%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-coord2d)
- [bool operator==(const Coord2D& a, const Coord2D& b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-operator--const-coord2d-a-const-coord2d-b)
- [bool operator!=(const Coord2D& a, const Coord2D& b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-operator--const-coord2da-const-coord2d-b)
- [double Coord2Distance(const Coor2D& a, const Coord2D& b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#double-txucoord2distance-const-coord2d-a-const-coord2d-b)
- [double Coord2DSqrDistance(const Coord2D& a, const Coord2D& b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#double-txucoord2dsqrdistance-const-coord2d-a-const-coord2d-b)

## Макросы для операций с классом:
- [txCoord(coord)](https://github.com/Smok1e/TXUtils/blob/main/README.md#txcoordcoord)

## txu::Coord2D txu::Coord2D::Screen()
Статическая функция. Возвращает экземпляр класса Coord2D с размерами основного экрана.
Вот небольшой пример использования:
```c++
txu::Coord2D screen = txu::Coord2D::Screen();

_txWindowStyle = WS_NOFRAME;
txCreateWindow(txCoord(screen));
```
В результате откроется полноэкранное окно.

## txu::Coord2D::operator POINT()
Оператор преобразования к POINT.

## Coord2D txu::Coord2D::operator-()
Возвращает отрицательный Coord2D.
То есть 

```c++
Coord2D a(-5, -2); 
Coord2D b( 5,  2); 
a == -b //true
```

## Математические операторы Coord2D
Позволяют производить над каждой координатой экземпляра класса стандартные арифметические операции.
При этом операции производятся над x левого и x правого операнда и над y левого и y правого операнда по отдельности.
То есть

```c++
Coord2D a(1, 5);
Coord2D b(2, 3);

Coord2D c = a + b; // c == {3, 8}
```

или

```c++
Coord2D a(1, 5);
Coord2D b(2, 3);

Coord2D c = a * b; // c == {2, 15}
```

## Скалярные математические операторы Coord2D
Позволяют производить над каждой координатой экземпляра класса стандартные арифметические операции со скалярным значеним.
Операция производится с каждой координатой по отдельности.
То есть

```c++
Coord2D coord(1, 5);
double scalar = 5;

Coord2D result = coord + scalar; // result == {6, 10}
```

или

```c++
Coord2D coord(1, 5);
double scalar = 5;

Coord2D result = coord * scalar; // result == {5, 25}
```

## bool operator==(const Coord2D& a, const Coord2D& b)
Оператор сравнения для Coord2D. Возвращает true, если a.x == b.x и a.y == b.y, иначе false.

## bool operator!=(const Coord2D&a, const Coord2D& b)
Оператор сравнения для Coord2D. Возвращает true, если a.x != b.x, или a.y != b.y, иначе false.

## double txu::Coord2Distance(const Coord2D& a, const Coord2D& b)
Возвращает численное расстояние между точками a и b согласно теореме Пифагора (или длине вектора, если угодно).

## double txu::Coord2DSqrDistance(const Coord2D& a, const Coord2D& b)
Возвращает численное расстояние между точками a и b, возведённое в квадрат.
Советую использовать это функцию вместо [txu::Coord2Distance](https://github.com/Smok1e/TXUtils/blob/main/README.md#double-txucoord2distance-const-coord2d-a-const-coord2d-b), если вам не нужно точное расстояние (например для сравнения расстояния a и расстояния b), поскольку последней приходится извлекать квадратный корень, что может снижать производительность программы.

## txCoord(coord)
Это макрос для удобства указания координат в функции, принимающие отдельно координату x и y.
Например:

```c++
txu::Coord2D position(100, 100);
txu::Coord2D size    (25,  50 );

txRectangle(position.x, position.y, position.x + size.x, position.y + size.y);
```

эквивалентно

```c++
txu::Coord2D position(100, 100);
txu::Coord2D size    (25,  50 );

txRectangle(txCoord(position), txCoord(position + size));
```

И ещё один пример:

```c++
txu::Coord2D position(100, 100);
double radius = 5;

txEllipse(position.x - radius, position.y - radius, position.x + radius, position.y + radius);
```

эквивалентно

```c++
txu::Coord2D position(100, 100);
double radius = 5;

txEllipse(txCoord(position-radius), txCoord(position+radius));
```

# txu::Context
Основной инструмент библиотеки. Забудьте о ~~ежедневном геморрое с~~ HDC!
Context обеспечивает удобную и надёжную работу с изображениями. Его не надо освобождать с помощью txDeleteDC, за вас это сделает деструктор.

Пример:

```c++
txu::Context source("image.bmp");
int size_x = source.getSizeX();
int size_y = source.getSizeY();

txu::Context result(size_x, size_y);
for (int x = 0; x < size_x; x++)
{
	for (int y = 0; y < size_y; y++)
	{
		txu::Color color = source.getPixel (x, y);

		int h = color.hue       ();
		int s = color.saturation();
		int v = color.value     ();

		result.setPixel(x, y, txu::Color::HSV((h + 140) % 255, s, v));
	}
}

txCreateWindow(size_x, size_y);
result.render();
```

загрузит картинку из файла "image.bmp" в txu::Context, затем конвертирует цвет каждого пикселя в систему HSV, прибавит к hue 140 и конвертирует цвет обратно в RGB:

![context_example_1](https://user-images.githubusercontent.com/33802666/117331689-af5be380-ae9f-11eb-94c5-6d49013cf082.png)

Или вот пример посложнее:

```c++
void Blur(txu::Context* source, txu::Context* result, int radius)
{
	int size_x = source->getSizeX();
	int size_y = source->getSizeY();
	result -> resize(size_x, size_y);

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

					txu::Color color = source->getPixel(_x, _y);
					r += color.r, g += color.g, b += color.b;

					n++;
				}
			}

			if (n == 0)
				continue;

			txu::Color color(r/n, g/n, b/n);
			result->setPixel(x, y, color);
		}
	}
}
```

Эта функция размывает картинку. Вызовем её с радиусом в 5 пикселей:

```c++
txu::Context source("image.bmp");
txu::Context result;

Blur(&source, &result, 5);

txCreateWindow(result.getSizeX(), result.getSizeY());
result.render();
```

И получим размытое изображение на экране:

![context_example_2](https://user-images.githubusercontent.com/33802666/117331765-bd116900-ae9f-11eb-8100-02d3fe9e0e81.png)

Экземпляром класса можно пользоваться так же, как и HDC. Для этого в нём есть соответствующий оператор.

## Конструкторы класса:
- txu::Context()
- txu::Context(int size_x, int size_y)
- txu::Context(const Context& that)
- txu::Context(const HDC& dc)
- txu::Context(const char* filename)

## Функции-члены:
- [bool txu::Context::create()](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txucontextcreate-)
- [bool txu::Context::create(int size_x, int size_y)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txucontextcreate-)
- [bool txu::Context::create(const Context& that)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txucontextcreate-)
- [bool txu::Context::create(const HDC& dc)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txucontextcreate-)
- [bool txu::Context::create(const char* filename)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txucontextcreate-)
- [bool txu::Context::loadFromFile(const char* filename)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txucontextloadfromfile-const-char-filename)
- [bool txu::Context::saveToFile(const char* filename)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txucontextsavetofile-const-char-filename)
- [Coord2D txu::Context::getSize()](https://github.com/Smok1e/TXUtils/blob/main/README.md#coord2d-txucontextgetsize-)
- [int txu::Context::getSizeX()](https://github.com/Smok1e/TXUtils/blob/main/README.md#int-txucontextgetsizex-)
- [int txu::Context::getSizeY()](https://github.com/Smok1e/TXUtils/blob/main/README.md#int-txucontextgetsizey-)
- [void txu::Context::resize(int new_size_x, int new_size_y)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txucontextresize-int-new_size_x-int-new_size_y)
- [void txu::Context::render(HDC dc = txDC (), int x = 0, int y = 0, int width = 0, int height = 0)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txucontextrender-hdc-dc--txdc--int-x--0-int-y--0-int-width--0-int-height--0)
- [void txu::Context::clear(txu::Color color)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txucontextclear-txucolor-color)
- [void txu::Context::capture(HWND wnd = nullptr)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txucontextcapture-hwnd-wnd--nullptr)
- [txu::Context::operator HDC&()](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucontextoperator-hdc-)
- [RGBQUAD* txu::Context::getBuffer()](https://github.com/Smok1e/TXUtils/blob/main/README.md#rgbquad-txucontextgetbuffer-)
- [size_t txu::Context::getBufferLength()](https://github.com/Smok1e/TXUtils/blob/main/README.md#size_t-txucontextgetbufferlength-)
- [RGBQUAD* txu::Context::access(size_t index)](https://github.com/Smok1e/TXUtils/blob/main/README.md#rgbquad-txucontextaccess-size_t-index)
- [RGBQUAD* txu::Context::access(int x, int y)](https://github.com/Smok1e/TXUtils/blob/main/README.md#rgbquad-txucontextaccess-int-x-int-y)
- [void txu::Context::setPixel(int x, int y, txu::Color color, bool blend = false)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txucontextsetpixel-int-x-int-y-txucolor-color)
- [txu::Color txu::Context::getPixel(int x, int y)](https://github.com/Smok1e/TXUtils/blob/main/README.md#txucolor-txucontextgetpixel-int-x-int-y)
- [void txu::Context::setColor(txu::Color color, int thikness = 0)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txucontextsetcolor-txucolor-color-int-thikness--0)
- [void txu::Context::setFillColor(txu::Color color)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txucontextsetfillcolor-txucolor-color)
- [void txu::Context::setFont(HFONT font)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txucontextsetfont-hfont-font)
- [void txu::Context::setFont(const char* name, int sy, int sx = -1, int bold = FW_DONTCARE, bool italic = false, bool underline = false, bool strikeout = false, double angle = 0)](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txucontextsetfont-const-char-name-int-sy-int-sx---1-int-bold--fw_dontcare-bool-italic--false-bool-underline--false-bool-strikeout--false-double-angle--0)

## bool txu::Context::create(...)
Заново инициализирует изображение в соответствии с указанными параметрами. Возвращает true в случае успеха.

## bool txu::Context::loadFromFile (const char* filename)
Загружает изображение из файла, указанного в параметрах.
Помимо .bmp я реализовал загрузку изображений формата png посредством [libpng](http://www.libpng.org/pub/png/libpng.html).

> Для того, чтобы загрузить файл формата png, убедитесь, что у вас установлена библиотека libpng, а перед включением TXU.h вы объявили макрос TXU_USE_PNG. Возможно, библиотека libpng у вас уже установлена (по крайней мере у меня она уже была), а если нет, вы можете установить > её при помощи [vcpkg](https://docs.microsoft.com/ru-ru/cpp/build/vcpkg?view=msvc-160)

Функция вернёт true если изображение загружено успешно, или false - в обратном случае.

Вот небольшой пример загрузки изображения из png-файла:

```c++
#define TXU_USE_PNG

//-------------------

#include <TXLib.h>
#include <TXU.h>

//-------------------

int main ()
{
	txu::Context image;
	image.loadFromFile("image.png");
	int size_x = image.getSizeX();
	int size_y = image.getSizeY();
	
	_txWindowStyle = WS_NOFRAME;
	txCreateWindow(size_x, size_y);
	
	image.render();
	
	return 0;
}
```

В результате на экране кошка.

![context_load_from_file_example](https://user-images.githubusercontent.com/33802666/117331803-c6023a80-ae9f-11eb-82cc-ac27f3f68ebc.png)

## bool txu::Context::saveToFile(const char* filename)
Сохраняет изображение в файл, указанный в параметрах. По умолчанию сохраняет в формате .bmp, однако, если вы подключили использование libpng (см [bool txu::Context::loadFromFile (const char* filename)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txucontextloadfromfile-const-char-filename)), функция автоматически определит его расширение по строке имени файла. То есть, если в конце имени файла указано ".png", и при этом подключён libpng, то изображение сохранится в формате png. В любых других случаях, изображение будет сохранено в формате bmp.

## Coord2D txu::Context::getSize()
Возвращает размер изображения.

## int txu::Context::getSizeX()
Возвращает ширину изображения.

## int txu::Context::getSizeY()
Возвращает высоту изображения.

## void txu::Context::resize(int new_size_x, int new_size_y)
Меняет размер изображения в соответствии с параметрами, при этом сохраняя исходное изображение. 

## void txu::Context::render(HDC dc = txDC (), int x = 0, int y = 0, int width = 0, int height = 0)
Копирует изображение в HDC, указанный в параметрах. Если HDC не указан, изображение копируется в окно TXLib.
В параметрах также можно указать позицию и размер копируемого изображения.

## void txu::Context::clear(txu::Color color)
Очищает изображение указанным в параметрах цветом.

## void txu::Context::capture(HWND wnd = nullptr)
Захватывает изображения окна. По умолчанию дексриптор окна равен nullptr, что означает, что захвачен будет весь экран.

## txu::Context::operator HDC&()
Оператор преобразования к HDC.

## RGBQUAD* txu::Context::getBuffer()
Возвращает указатель на начало буфера изображения в формате RGBQUAD.

## size_t txu::Context::getBufferLength()
Возвращает размер буфера изображения.

## RGBQUAD* txu::Context::access(size_t index)
Возвращает указатель на пиксель изорбажения под индексом, указанным в параметрах. Внутри функции существует проверка индекса, благодаря которой функция вернёт nullptr если индекс вышел за границы массива. Обратите внимание, что эта проверка работает только в debug сборке. Если выйти за границы в сборке release, может произойти исключение access violation. 

## RGBQUAD* txu::Context::access(int x, int y)
Делает то же, что и [txu::Context::access (size_t index)](https://github.com/Smok1e/TXUtils/blob/main/README.md#rgbquad-txucontextaccess-int-x-int-y), но вместа индекса принимает координаты пикселя.

## void txu::Context::setPixel(int x, int y, txu::Color color, bool blend = true)
Устанавливает пиксель в точке, указанной параметрами x и y с учётом альфа-канала входного цвета. Если в качестве последнего параметра передан false, альфа-канал не будет учтён, то есть в буфер изображения передастся цвет без изменений.

## txu::Color txu::Context::getPixel (int x, int y)
Возвращает цвет пикселя по указанным координатам. Если координаты выходят за рамки изображения, функция вернёт txu::Color::Black.

## void txu::Context::setColor(txu::Color color, int thikness = 0)
Устанавливает цвет и толщину обводки для внутреннего HDC. Тоже самое, что и txSetColor.

## void txu::Context::setFillColor(txu::Color color)
Устанавливает цвет заливки для внутреннего HDC. Тоже самое, что и txSetFillColor.

## void txu::Context::setFont(HFONT font)
Устанавливает шрифт для внутреннего HDC, указанный в параметрах. В качестве параметра используйте txu::Font.

## void txu::Context::setFont(const char* name, int sy, int sx = -1, int bold = FW_DONTCARE, bool italic = false, bool underline = false, bool strikeout = false, double angle = 0)
Устанавливает шрифт для внутреннего HDC по указанным параметрам. То же самое, что и txSelectFont.

# txu::Time
Класс, предназначенный для представления единиц времени в удобном формате. Поначалу, может показаться, что эта вещь бесполезна. Ведь время это же просто величина, как расстояние и скорость? В простых случаях - так и есть. Программист заводит переменную, к примеру, int timeout и вызвает абстрактную функцию Sleep (timeout). Как правило, для представления времени в программировании используются милисекунды, а значит timeout - время (в милисекундах). Но что если надо представить время не в милисекундах, а, например, в секундах? Тогда значение придётся умножить на 1000, а значит вызов Sleep будет происходить как Sleep (timeout * 1000). Но любой человек, посмотревший на такой код может сказать: А что это за "магическое" число 1000? Магическими числами называют численные выражения, не пояснённые и не обозначенные никакой переменной, из за чего сложно понять для чего они предназначаются. Все эти проблемы и решает класс txu::Time. С его использованием, предыдущий пример будет выглядеть так:
```c++
txu::Time timeout = txu::Time::seconds (1);
Sleep (timeout);
```

Всё, теперь ничего пояснять не нужно. Вы можете инициализировать класс пятью разными способами из микросекунд, милисекунд, секунд, минут и часов. 

```c++
txu::Time::microseconds (1000000) == 
txu::Time::milliseconds (1000)    == 
txu::Time::seconds      (1)       == 
txu::Time::minutes      (1/60)    == 
txu::Time::hours        (1/3600);
```

Все эти записи эквивалентны и равняются одной секунде.

Но даже это не предел удобства! Помните эти буквы после чисел, обозначающие тип числа? 10u 10f 10l и.т.д. Эти постификсы называются литеральными операторами. И разумеется, c++ был бы не ++, если бы в нём нельзя было определить пользовательские литеральные операторы. И в классе Time они тоже есть.
Хотите вызвать txSleep на 8 часов? ~зачем...~ Да без проблем!

```c++
txSleep (8_hours);
```

Для класса определены следующие литеральные операторы:
- \_mcsec | время из микросекунд
- \_msec  | время из миллисекунд
- \_sec   | время из секунд
- \_min   | время из минут
- \_hours | время из часов

Все они возвращают объект типа txu::Time, с которым вы уже можете делать всё что душе угодно.

Разумеется, после создания переменной типа Time, вы можете достать из неё значения в любом удобном формате с помощью Time::getMicroseconds, Time::getMilliseconds, и.т.д.

По умолчанию, время присваевается в милисекундах, то есть:

```c++
txu::Time time = 1000; // переменная time будет равна 1000 милисекундам
```

Ну и разумеется, в классе предусмотрен оператор приведения к double:
```c++
double milliseconds = 1_sec; // переменная milliseconds будет равна 1000
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
- [txu::Time txu::Time::microseconds (Time::time_t microseconds)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%81%D1%82%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D0%B8%D0%BD%D0%B8%D1%86%D0%B8%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D0%B8)
- [txu::Time txu::Time::milliseconds (Time::time_t millisedonds)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%81%D1%82%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D0%B8%D0%BD%D0%B8%D1%86%D0%B8%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D0%B8)
- [txu::Time txu::Time::seconds (Time::time_t seconds)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%81%D1%82%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D0%B8%D0%BD%D0%B8%D1%86%D0%B8%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D0%B8)
- [txu::time txu::Time::minutes (Time::time_t minutes)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%81%D1%82%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D0%B8%D0%BD%D0%B8%D1%86%D0%B8%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D0%B8)
- [txu::Time txu::Time::hours (Time::time_t hours)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%81%D1%82%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D0%B8%D0%BD%D0%B8%D1%86%D0%B8%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D0%B8)
- [txu::Time operator double ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#txutimeoperator-double-)
- [txu::Time operator = (const Time& that)](https://github.com/Smok1e/TXUtils/blob/main/README.md#txutime-txutimeoperator--const-time-that)
- [txu::Time::operator - ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#txutime-txutimeoperator--const-time-that)
- [txu::Time::operator += (const Time& that)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%83%D0%BD%D0%B0%D1%80%D0%BD%D1%8B%D0%B5-%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B)
- [txu::Time::operator -= (const Time& that)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D1%83%D0%BD%D0%B0%D1%80%D0%BD%D1%8B%D0%B5-%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B)

# Функции для операций с классом:
- [bool operator == (const txu::Time& a, const txu::Time& b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-operator--const-txutime-a-const-txutime-b)
- [bool operator != (const txu::Time& a, const txu::Time& b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-operator--const-txutime-a-const-txutime-b-1)
- [txu::Time operator + (const txu::Time& a, const txu::Time& b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%B1%D0%B8%D0%BD%D0%B0%D1%80%D0%BD%D1%8B%D0%B5-%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B)
- [txu::Time operator - (const txu::Time& b, const txu::Time& b)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%B1%D0%B8%D0%BD%D0%B0%D1%80%D0%BD%D1%8B%D0%B5-%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B)
- [txu::Time operator "" \_mcsec (long long unsigned microseconds)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%BB%D0%B8%D1%82%D0%B5%D1%80%D0%B0%D0%BB%D1%8C%D0%BD%D1%8B%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-time)
- [txu::Time operator "" \_msec (long long unsigned milliseconds)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%BB%D0%B8%D1%82%D0%B5%D1%80%D0%B0%D0%BB%D1%8C%D0%BD%D1%8B%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-time)
- [txu::Time operator "" \_sec (long long unsigned seconds)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%BB%D0%B8%D1%82%D0%B5%D1%80%D0%B0%D0%BB%D1%8C%D0%BD%D1%8B%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-time)
- [txu::Time operator "" \_min (long long unsigned minutes)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%BB%D0%B8%D1%82%D0%B5%D1%80%D0%B0%D0%BB%D1%8C%D0%BD%D1%8B%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-time)
- [txu::Time operator "" \_hours (long long unsigned hours)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%BB%D0%B8%D1%82%D0%B5%D1%80%D0%B0%D0%BB%D1%8C%D0%BD%D1%8B%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-time)
- [txu::Time operator "" \_mcsec (long double microseconds)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%BB%D0%B8%D1%82%D0%B5%D1%80%D0%B0%D0%BB%D1%8C%D0%BD%D1%8B%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-time)
- [txu::Time operator "" \_msec (long double milliseconds)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%BB%D0%B8%D1%82%D0%B5%D1%80%D0%B0%D0%BB%D1%8C%D0%BD%D1%8B%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-time)
- [txu::Time operator "" \_sec (long double seconds)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%BB%D0%B8%D1%82%D0%B5%D1%80%D0%B0%D0%BB%D1%8C%D0%BD%D1%8B%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-time)
- [txu::Time operator "" \_min (long double minutes)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%BB%D0%B8%D1%82%D0%B5%D1%80%D0%B0%D0%BB%D1%8C%D0%BD%D1%8B%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-time)
- [txu::Time operator "" \_hours (long double hours)](https://github.com/Smok1e/TXUtils/blob/main/README.md#%D0%BB%D0%B8%D1%82%D0%B5%D1%80%D0%B0%D0%BB%D1%8C%D0%BD%D1%8B%D0%B5-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D1%8B-time)

## txu::Time::time_t
Это тип абстрактной единицы времени. По сути представляет из себя знаковое число с плавающей точкой.

## Функции для получения времени
Возвращают время в указанных единицах. getMicroseconds вернёт микросекунды, getMilliseconds - милисекунды, и так далее.

## txu::Time::operator double ()
Возвращает время в милисекундах.

## Статические функции инициализации
Функции txu::Time::milliseconds, txu::Time::seconds и другие без префикса get - являются статическими (то есть их можно вызвать, не создавая переменную типа Time) и возвращают объект типа txu::Time, созданный в указанной еденице времени из числа, указанного в параметре.

## txu::Time& txu::Time::operator = (const Time& that)
Оператор присваивания.

## txu::Time txu::Time::operator - ()
Возвращает объект класса с отрицательным значением времени.

## Унарные математические операторы 
Операторы, такие как += и -= - выполняют то же, что и математические += и -=.

## bool operator == (const txu::Time& a, const txu::Time& b)
Возвращает true, если значение времени левого операнда равно значению правого.

## bool operator != (const txu::Time& a, const txu::Time& b)
Возвращает true, если значения операндов не равны.

## Бинарные математические операторы
Операторы, такие как + и - - выполняют то же, что и математические + и -.

## Литеральные операторы Time
Возвращают объект типа txu::Time, в зависимости от оператора.
\_mcsec возвращает микросекунды, \_msec - миллисекунды, \_sec - секунды, \_min - минуты, и \_hours - часы.
Литеральный оператор нужно писать сразу после числа, без пробелов. Синтаксис выглядит так:
```c++
txu::Time time = 1400_msec;
```
Тогда time будер равна 1400 миллисекундам.

# txu::Timer
Это сопутствующий txu::Time класс. Он выполняет функцию таймера, как несложно догадаться из названия. Класс очень простой, в нём всего 2 функции, но полезный. Он считает время не в милисекундах, как например примитывный GetTickCount (), а в микросекундах, используя для работы значения частоты и тиков процессора, так что он позволяет выявить даже самые незначительные различия во времени.

Его использование крайне простое, например, для измерения времени, которое занимает функция test, подойдёт следующий код:

```c++
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
- [void txu::Timer::start ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txutimerstart-)
- [txu::Time txu::Timer::getTime](https://github.com/Smok1e/TXUtils/blob/main/README.md#txutime-txutimergettime-)

## void txu::Timer::start ()
Начинает отсчёт времени с текущего момента.

## txu::Time txu::Timer::getTime ()
Возвращает прошедшее с момента вызва функции start время в виде объекта txu::Time.

# txu::Sound
Простой класс, предназначенный для хранения и воспроизведения звуков формата wav. С его помощью нельзя редактировать или записывать звуки, он предназначен только для хранения данных wav-файла и их воспроизведения. Это нужно для того чтобы не подгружать один и тот же файл каждый раз при его проигрывании, что довольно сильно экономит ресурсы, если звук проигрывается часто. В целом, воспроизводить звуки из буффера сэмплов сам winapi позволяет, а загрузку и сохранение вполне реально реализовать самостоятельно. Но задача эта не самая простая, так что скорее всего я реализую бóльшие возможности позже, когда возникнет необходимость.

Обращаться с классом очень просто. Вот пример кода, который загружает и проигрывает звук из файла "sound.wav":

```c++
txu::Sound sound ("sound.wav");
sound.play ();
```

# Конструкторы класса:
- txu::Sound::Sound ()
- txu::Sound::Sound (const char* filename)
- txu::Sound::Sound (Sound&  copy)
- txu::Sound::Sound (Sound&& copy)

# Функции-члены:
- [bool txu::Sound::loadFromFile (const char* filename)](https://github.com/Smok1e/TXUtils/blob/main/README.md#bool-txusoundloadfromfile-const-char-filename)
- [void txu::Sound::play ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txusoundplay-)
- [void txu::Sound::playAsync ()](https://github.com/Smok1e/TXUtils/blob/main/README.md#void-txusoundplayasync-)

## bool txu::Sound::loadFromFile (const char* filename)
Загружает звук из файла. В случае, если формат файла не соответствует wav, функция вернёт false и не станет его загружать. Если файл загрузится успешно, возвращает true.

## void txu::Sound::play ()
Проигрывает звук, останавливая программу на время воспроизведения.

## void txu::Sound::playAsync ()
Проигрывает звук параллельно с работой программы.

# Спасибо за использование TXUtils!
Я буду рад ответить на ваши вопросы и предложения. В будущем я собираюсь добавить ещё множество удобных фич!
