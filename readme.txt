ФИО: Аграновский Михаил Леонидович
Группа: 321
Задание: Разделение логики и пользовательского интерфейса. Система плагинов.
Система программирования: Ubuntu 15.10 x64, g++ 4.9.3, Qt, Google glog. [Intel core i5 3337u, 8Gb RAM]
    Логирование реализовано через Google log:
        sudo apt install libgoogle-glog-dev
    May require x86 libs for correct work (it is not one of dependencies)

Запуск программы:
    Setup environment variables (run once per shell session):
        # Run it INSIDE build directory
        cd build && source ../glog_env.sh && cd ..
    Run:
        build/src/align_project --cli
    Пример дальнейшего ввода:
        pictures/src/ship.bmp
        gray-world
    Результат сохраняется в корне проекта и отображается средствами системного просмотрщика изображений (команда xdg-open).
Компиляция:
    cd build && rm -rf * && cmake .. && make


Комментарий:
На основе задания машграфа реализован паттерн MVC с легким контроллером. Соответсвенно,
 class AppModel -- model,
 class Ui -- view [опирается в реализации на классы ImageView, TextView -- расположены в модуле SubView],
 class AppController -- controller.
Вообще, реалихована полиморфная иерархия вьюшек: View -> [ImageView, TextView] -> [CliImageView, CliTextView;
                                                                                   GuiImageView*, GuiTextView*]
Реализация Gui не доведена до рабочего состояния, поэтому исключена.
Требование независимости model от view и controller реализовано через Qt signals&slots.
Дальнейшие комментарии расположены в коде.
