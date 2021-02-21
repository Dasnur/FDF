# "FDF" This project is about created a simplified 3D graphic representation of a relief landscape
* [Как запустить](#Старт)
* [Как запустить Windows](#Старт_Windows)

**Задача:**
Визуализировать описанную поверхность

**Функционал**
* Изменение проекции с параллельной на изометрическую и обратно
* Приближение и отдаление повержности
* Возможность поворачивать поверхность
* Градиетная раскраска цветом в зависимости от удаленности точки от нулевой координаты поверхности

**Входные данные:**
Набор точек в формате:
* x - строка точки
* y - столбец точки
* z - значение точки
* через запятую с точкой может быть указан цвет точки в формате 0x"код цвета RGB"

**Выходные данные:**
* Графчиеское 3D пердставление плоскости

**Управление**
* w/s - x rot
* q/e - y rot
* a/d - z rot
* i - iso
* p - parallel
* arrows - move proj
* +/- - zoom proj
* Колечико мышки - zoom
* Зажатие ЛКМ - вращение проекции
* esc - завершение программы
_____

![421_fdf](https://user-images.githubusercontent.com/45533581/108629335-6aafd700-7470-11eb-9f19-64d77360691c.gif)

Карта Марса
![mars1_fsf](https://user-images.githubusercontent.com/45533581/108629529-5d471c80-7471-11eb-84fc-7d95d7089324.gif)

Изменение вида проекции на примере пирамиды
![pyra_fdf](https://user-images.githubusercontent.com/45533581/108629705-43f2a000-7472-11eb-9ccb-67393f2fc442.gif)
__________
<a name="Старт"></a>
**Старт**
* Выполните make в папке FDF_linux/FDF
* Имя исполняемого файла fdf
* Запуск просиходит в виде ./fdf  "../maps/*fdf"

<a name="Старт_Windows"></a>
**Старт Windows**
* Для запуска на Windows из подсистемы WSL необходимо использовать Xming server
* Перед запускам использовать "export DISPLAY=:0"
