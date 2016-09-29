#pragma once


#include <string>
#include <map>
#include <vector>
#include "io.hpp"

using OptionsType = std::map<std::string, std::string>;

/// Base class for all views. Other modules interact with View objects.
class View
{
public:
    /// start interaction
    virtual void run() = 0;
    virtual std::string getPath(const std::string &msg) = 0;
    virtual OptionsType getOptions() = 0;
    /// the final point of interaction: getting the result
    virtual void output(const Image &res) = 0;
    virtual ~View() {};

//public slots:
//    void onUpdate();
};

class CliView : public View
{
public:
    void run() override;
    virtual std::string getPath(const std::string &msg) override;
    /// note: check for bad input is not implemented
    OptionsType getOptions() override;
    // todo: rewrite
    void output(const Image &res) override;
    virtual ~CliView() {};
};

//class GuiView : public View
//{
//
//};

// todo: void?