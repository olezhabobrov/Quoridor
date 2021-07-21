#include "Controller.h"

Controller::Controller(QObject *parent) : QObject(parent), field()
{
    field.showFullScreen();
    field.exec();

}
