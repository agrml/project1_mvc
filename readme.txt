ФИО: Аграновский Михаил Леонидович
Группа: 321
Задание: Разделение логики и пользовательского интерфейса. Система плагинов.
Система программирования:
 - Intel core i5 3337u, 8Gb RAM
 - Ubuntu 15.10 x86-64, g++ 4.9.3, Qt, Google glog. Cmake, make.
   Логирование реализовано через Google log:
       sudo apt install libgoogle-glog-dev
   May require x86 libs for correct work (it is not one of dependencies)
 - JetBrains Clion (проект корректно собирается и работает из консоли).


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
Вообще, реализована полиморфная иерархия вьюшек: View -> [ImageView, TextView] -> [CliImageView, CliTextView;
                                                                                   GuiImageView*, GuiTextView*]
Реализация Gui не доведена до рабочего состояния (проблемы с вынесением Qt в отдельный поток), поэтому исключена.
Однако полиморфный каркас для ее "легкого" подключения новых вьюшек реализован.
Требование независимости model от view и controller реализовано через механизм Qt signals&slots.

Дальнейшие комментарии расположены в коде.
