#ifndef GRWIDGET_H
#define GRWIDGET_H

#include <QWidget>
#include <QSpinBox>

#include "dctl.h"

namespace Ui {
class GrWidget;
}

class GrWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GrWidget(QWidget *parent = nullptr);
    ~GrWidget();

    void paintEvent(QPaintEvent *event);
    void setParams(const QImage* img, int* zoom, QSpinBox* thr, QCheckBox* checkBoxCenterLines)
    {
        m_image = img;
        m_zoom = zoom;
        m_spinBoxThreads = thr;
        m_checkBoxCenterLines = checkBoxCenterLines;
    }

    void processImage(QImage& result, int z, int thr);

public slots:
    void updateResultImage();

private:
    Ui::GrWidget *ui;

    const QImage* m_image;
    int* m_zoom;
    QSpinBox* m_spinBoxThreads;
    QCheckBox* m_checkBoxCenterLines;
    QImage m_resultImage;

    std::vector<uint8_t> pixbuf;
};

#endif // GRWIDGET_H
