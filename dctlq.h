#ifndef DCTLQ_H
#define DCTLQ_H

#include <QCheckBox>
#include <QObject>
#include <QLabel>
#include <QSlider>

#include "dctl_struct.h"

struct DCTL_QCheckBox : public QObject
{
    Q_OBJECT
public:
    DCTL_QCheckBox(QObject* parent) : QObject(parent) { }

    DCTL_checkBox* data = nullptr;
    QCheckBox* cb = nullptr;

public slots:
    void stateChanged(int state);
    void reset();
};

class DCTL_QSlider : public QObject
{
    Q_OBJECT
public:
    DCTL_QSlider(QObject* parent) : QObject(parent) { }

    DCTL_slider* data = nullptr;
    float udef = 0.f;
    QLabel* labelValue = nullptr;
    QSlider* sl = nullptr;

public slots:
    void valueChanged(int value);
    void reset();
    void openMenu();
    void saveDef();
    void revertDef();
};

#endif // DCTLQ_H
