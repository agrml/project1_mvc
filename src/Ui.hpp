#pragma once

#include "SubViews.hpp"
#include <QtWidgets>


/// The app view (AppView) -- the `view` controlled by the `controller` (AppController class)
/// and represents the `model` -- the state of the app (no the state of the image. it is meaningfull to note that.)

class Ui : public View
{
    Q_OBJECT
public:
    virtual void run(std::shared_ptr<AppModel> appModel) = 0;
    virtual void runImageView() = 0;
protected slots:
    virtual void onModelUpdate() = 0;
//public:
//    virtual void write(const std::string &msg) = 0;
public slots:
    virtual void log(const std::string &msg) = 0;
public:
    virtual std::string getLine(const std::string &msg) = 0;
    virtual OptionsType getOptions() = 0;
};

/// Implements programmer side of UI (api?) and uses console io and system viewer as user side of UI.
class Cli : public Ui
{
    Q_OBJECT
    std::shared_ptr<CliImageView> imageView_;
    std::shared_ptr<CliTextView> textView_;
    std::shared_ptr<AppModel> appModel_{};
public:
    Cli(std::shared_ptr<CliImageView> imageView,
        std::shared_ptr<CliTextView> textView);

    void run(std::shared_ptr<AppModel> appModel) override;
    void runImageView() override;
protected slots:
    void onModelUpdate() override;
public slots:
    void log(const std::string &msg) override;
public:
    std::string getLine(const std::string &msg) override;
    OptionsType getOptions() override;
};

/// Implements programmer side of UI and user side (Qt GUI application) too. Uses it as user side of UI.
//class Gui : public Ui
//{
//Q_OBJECT
//    std::shared_ptr<GuiImageView> imageView_;
//    std::shared_ptr<GuiTextView> textView_;
//    std::shared_ptr<AppModel> appModel_{};
//
//    // main window widget
//    std::shared_ptr<QMainWindow> window_{};
//    std::shared_ptr<QHBoxLayout> layout_{};
//
//    // other widgets{}
//
//public:
//    Gui(std::shared_ptr<GuiImageView> imageView,
//        std::shared_ptr<GuiTextView> textView);
//
//    void run(std::shared_ptr<AppModel> appModel) override;
//    void runImageView() override;
//protected slots:
//    void onModelUpdate() override;
//public slots:
//    void log(const std::string &msg) override;
//public:
//    std::string getLine(const std::string &msg) override;
//    OptionsType getOptions() override;
//};
