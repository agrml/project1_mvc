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

// our modules
#include "model.hpp"
#include "view.hpp"
#include "controller.hpp"
#include "Cli.hpp"

/// init third-party libraries
void init(char *argv[])
{
    google::InitGoogleLogging(argv[0]);
    google::InstallFailureSignalHandler();
}



/**
 * The main function :)
 *
// * Initialazes all that does not depends of user input
 */
int main(int argc, char *argv[])
{
    init(argv);

    // parse argv
    constexpr int MODE_ARGC = 1;
    if (argc != MODE_ARGC + 1) {
        throw std::string{"Expect 1 command line argument, "} + std::to_string(argc - 1) + "given.";
    }
    std::string param{argv[MODE_ARGC]};

// todo: place them all on the heap: there is no one function (stack frame) prioritized in use of them
    // init view
    ImageView *imageView;
    TextView *textView;
    /*if (param == "--gui") {
        imageView = new QtImageView{};
        logView = new QtLogView{};
    } else */if (param == "--cli") {
        imageView = new CliImageView{};
        textView = new CliTextView{};
    } else {
        throw std::string{"unknown mode"};
    }
    auto ui = new Cli{imageView, textView};

    // init model
    Model *model = new Model{};

    // init controller
    auto controller = new AppController{model, view};
    controller->run();

    delete model;
    delete view;
    delete controller;

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