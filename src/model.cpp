#include "io.hpp"
#include "model.hpp"


void Model::setImage(const Image &img)
{

    emit modelUpdated();
}
