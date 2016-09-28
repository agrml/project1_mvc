#include "view.hpp"

OptionsType CliView::getOptions()
{
    std::map<std::string, std::vector<std::string>> options;
    std::string opt;
    std::cout << "What would you like to do? [align|gray-world|median]" << std::endl;
    std::cin >> opt1;
    options.emplace({"option", {opt}});
    if (opt == "align") {
        std::cout << "Postprocessing? [gray-world|median|n -- for stop]";
        std::vector<std::string> vect;
        while (std::cin >> opt && opt != "n") {
            vect.emplace_back(opt);
        }
        options.emplace({"postprocessing", ...});
    }
}

void CliView::run()
{
    std::cout << "Align Project: Prac Edition. Mikhail Agranovskiy, 321 group" << std::endl << std::endl;
    std::cout << "Welcome to CLI. We have pleasure that you prefer us to GUI." << std::endl;
    std::cout << "We will ask you for futher interactions soon." << std::endl;
}
