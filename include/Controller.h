#pragma once

#include <QObject>
#include "GameField.h"

class Controller : public QObject
{
Q_OBJECT

  GameField field;
public:
  explicit Controller(QObject *parent = nullptr);

signals:

};