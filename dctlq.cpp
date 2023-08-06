#include "dctlq.h"
#include "wrapsettings.h"

#include <QMenu>

void DCTL_QCheckBox::stateChanged(int state)
{
    if (data)
    {
        data->val = state == Qt::Checked;
    }
}

void DCTL_QCheckBox::reset()
{
    if (data)
    {
        cb->setCheckState(data->def ? Qt::Checked : Qt::Unchecked);
    }
}

void DCTL_QSlider::valueChanged(int val)
{
    if (data)
    {
        data->val = data->lo + val * data->step;
        if (labelValue)
        {
            labelValue->setText(QString::number(data->val, 'g', 4));
        }
    }
}

void DCTL_QSlider::reset()
{
    if (data)
    {
        sl->setValue(std::floor((udef - data->lo)/data->step));
    }
}

void DCTL_QSlider::openMenu()
{
    QMenu contextMenu;
    QAction action1("Save as default", this);
    connect(&action1, SIGNAL(triggered()), this, SLOT(saveDef()));
    contextMenu.addAction(&action1);

    QAction action2("Revert to factory", this);
    action2.setEnabled(g_wrapSettings.exists(data->name));
    connect(&action2, SIGNAL(triggered()), this, SLOT(revertDef()));
    contextMenu.addAction(&action2);

    contextMenu.exec(QCursor::pos());
}

void DCTL_QSlider::saveDef()
{
    g_wrapSettings.saveDefault(data->name, data->val);
    udef = data->val;
}

void DCTL_QSlider::revertDef()
{
    g_wrapSettings.factoryReset(data->name);
    udef = data->def;
}
