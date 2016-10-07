// parts of standard library
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <initializer_list>
#include <limits>
#include <ctime>

// parts of third-party libraries
#include <glog/logging.h>
#include <QtCore>

// our modules
#include "AppModel.hpp"
#include "SubViews.hpp"
#include "AppController.hpp"
#include "Ui.hpp"

/// init third-party libraries
void init(int argc, char *argv[])
{
    google::InitGoogleLogging(argv[0]);
    google::InstallFailureSignalHandler();

//    QCoreApplication app(argc, argv);
}


/**
 * The main function :)
 *
// * Initialazes all that does not depends of user input
 */
int main(int argc, char *argv[])
{
//    std::ifstream in("/Data/tmp/in.txt");
//    std::cin.rdbuf(in.rdbuf());

    init(argc, argv);

    // parse argv
    constexpr int MODE_ARGC = 1;
    if (argc != MODE_ARGC + 1) {
        throw std::string{"Expect 1 command line argument, "} + std::to_string(argc - 1) + "given.";
    }
    std::string param{argv[MODE_ARGC]};

// todo: place them all on the heap: there is no one function (stack frame) prioritized in use of them
    // init view
    std::shared_ptr<ImageView> imageView;
    std::shared_ptr<TextView> textView;
    /*if (param == "--gui") {
        imageView = std::make_shared<QtImageView>();
        logView = std::make_shared<QtLogView>();
    } else */if (param == "--cli") {
        imageView = std::make_shared<CliImageView>();
        textView = std::make_shared<CliTextView>();
    } else {
        throw std::string{"unknown mode"};
    }
    auto model = std::make_shared<AppModel>();
    auto ui = std::make_shared<Cli>(imageView, textView, model);
    auto controller = std::make_shared<AppController>(model, ui);
    controller->run();

    return 0;
}

/* Generel TODO:
 * -- shared ptr
 * */

/*Консольное приложение

Необходимо реализовать возможность задания списка применяемых алгоритмов постобработки в интерактивном режиме. Параметры запуска – ключ --manual или -m и имена входного и выходного файлов с изображениями. После запуска, поиска и регистрации всех доступных плагинов, программа должна предложить выбрать способы постобработки из созданного списка.

>> ./task -m input_image.bmp output_image.bmp
[0] Process image
Available postprocessing:
[1] Grey world
[2] Auto contrast
Please choose command to process.
 >> 2
[0] Process image
Available postprocessing:
[1] Gray world
[2] Auto contrast (1)
Please choose command to process
>> 0
A basic phase was finised.
A postprocessing phase is started:
1. Auto contrast
An image was successfully writed to output_image.bmp
>>*/