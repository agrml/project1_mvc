#pragma once


#include <string>
#include <map>
#include <vector>

using OptionsType = std::map<std::string, std::vector<std::string>>;

/// Base class for all views. Other modules interact with View objects.
class View
{
public:
    /// start interaction
    virtual void run() = 0;
    virtual OptionsType getOptions() = 0;
    virtual void translateInput() = 0;
    /// the final point of interaction: getting the result
    virtual void output() = 0;

public slots:
    void onUpdate();
};

class CliView : public View
{
public:
    void run() override;
    OptionsType getOptions() override;

};

class GuiView : public View
{

};

// todo: void?