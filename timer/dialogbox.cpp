#include "dialogbox.h"

class DialogboxData : public QSharedData
{
public:

};

Dialogbox::Dialogbox() : data(new DialogboxData)
{

}

Dialogbox::Dialogbox(const Dialogbox &rhs) : data(rhs.data)
{

}

Dialogbox &Dialogbox::operator=(const Dialogbox &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

Dialogbox::~Dialogbox()
{

}

