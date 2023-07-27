#include "dctlq.h"

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
        sl->setValue(std::floor((data->def - data->lo)/data->step));
    }
}
