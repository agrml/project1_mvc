#pragma once

#include <string>
#include <map>
#include <vector>
#include <QtCore>
#include <QtCore/QObject>
//#include "io.hpp"
#include "AppModel.hpp"

using OptionsType = std::map<std::string, std::string>;


// fixme: интерфейс -- это когда констуктор приватный?
// ==============================LEVEL 1===================================
/// Base class for all views. Other modules interact with View objects.
class View : public QObject
{
public:
    /**
     * View init
     *
     * A few words about singletone...
     * It would be nice to implement initalization in constructors. But init provides i/o.
     * So we can't do this. Actually we nead to implement singltone pattern but we will not. (So lazy)
     * So we implement `run` method.
     */
public:
    virtual ~View() {};
};

// ==============================LEVEL 2===================================
class ImageView : public View
{
public:
    virtual void run(std::shared_ptr<AppModel> model,
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
    /// getting input
    virtual OptionsType getOptions() const = 0;

    virtual void write(const std::string &msg) const = 0;
    virtual void log(const std::string &msg) const = 0;
    virtual std::string getLine(const std::string &msg) const = 0;
};

// ==============================LEVEL 3===================================
class CliImageView : public ImageView
{
    std::shared_ptr<AppModel> model_{};
    /// where to save image
    std::string save_path_ = "";
public:
    void run(std::shared_ptr<AppModel> model,
             const std::string &path) override;
    void updateImage() const override;
};

class CliTextView : public TextView
{
    std::shared_ptr<AppModel> model_{};
public:
    void run();
    void write(const std::string &msg) const override;
    void log(const std::string &msg) const override;
    /// wipes all space simbols before first non-space symbol
    std::string getLine(const std::string &msg) const override;
    OptionsType getOptions() const override;
};
