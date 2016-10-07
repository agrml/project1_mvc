#pragma once

#include <QObject>
#include "io.hpp"
#include "matrix.hpp"

class AppModel : public QObject
{
    Q_OBJECT
    std::shared_ptr<Image> img_ = std::make_shared<Image>();
public:
    Image getImg() const;
    void setImg(const Image &img);
signals:
    void modelUpdated();
    void log(const std::string &msg);
public:
    ~AppModel() {}

    // from align.cpp:
    void align(bool isPostprocessing,
               const std::string &postprocessingType,
               bool isMirror);
};
