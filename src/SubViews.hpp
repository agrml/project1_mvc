#pragma once

#include <string>
#include <map>
#include <vector>
//#include "io.hpp"
#include "AppModel.hpp"

using OptionsType = std::map<std::string, std::string>;


// fixme: интерфейс -- это когда констуктор приватный?
// ==============================LEVEL 1===================================
/// Base class for all views. Other modules interact with View objects.
class View
{
protected:
    AppModel *model_ = nullptr;
public:
    /**
     * View init
     *
     * A few words about singletone...
     * It would be nice to implement initalization in constructors. But init provides i/o.
     * So we can't do this. Actually we nead to implement singltone pattern but we will not. (So lazy)
     * So we implement `run` method.
     */
//    virtual void run() = 0;

    virtual ~View() {};

//public slots:
//    void onUpdate();
};

// ==============================LEVEL 2===================================
class ImageView : public View
{
public:
    virtual void run(AppModel *model,
                     const std::string &path) = 0;
//    /// in qt-signal version, connection will be established here
//    ImageView(AppModel *model);
    /// updating view to the current state of the model.
    /// It will be a slot
    virtual void updateImage() const = 0;

//    virtual ~ImageView() {}
};

class TextView : public View
{
public:
    virtual void run() = 0;
//    /// in qt-signal version, connection will be established here
//    ImageView(AppModel *model);

//    // getting input
    virtual OptionsType getOptions() const = 0;

    virtual void write(const std::string &msg) const = 0;
    virtual void log(const std::string &msg) const = 0;
//    todo: operator<<;
    virtual std::string getLine(const std::string &msg) const = 0;

//    ~ ну вроде он автоматически виртуальный если в родительском виртуальный
};

// ==============================LEVEL 3===================================
class CliImageView : public ImageView
{
    /// where to save image
    std::string path_ = "";
public:
    // note: TextView is used to get the path
    void run(AppModel *model,
             const std::string &path) override;
//    void run() override;
    void updateImage() const override;

//    virtual ~CliImageView() {}
};

class CliTextView : public TextView
{
public:
    void run();
    void write(const std::string &msg) const override;
    void log(const std::string &msg) const override;
    /// wipes all space simbols before first non-space symbol
    std::string getLine(const std::string &msg) const override;
    OptionsType getOptions() const override;
};
