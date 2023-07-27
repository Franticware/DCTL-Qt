#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSlider>
#include <QCheckBox>
#include <QImage>
#include <QPushButton>

#include "dctlq.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void on_actionSave_As_triggered();
    void on_actionAbout_triggered();
    void on_comboBoxZoom_currentTextChanged(const QString &arg1);
    void on_checkBoxCenterLines_stateChanged(int);
    void on_actionE_xit_triggered();

private:
    Ui::MainWindow *ui;

    void addParamWidget(int row, QPushButton* resetAll, void* param);
    void updateZoom(const QString& zoom);

    DCTL_checkBox* m_equirectCheckBoxValues = nullptr;

    QString m_filename;
    QImage m_image;
    int m_zoom;

    void openImage(QString newImageFilename);
};

#endif // MAINWINDOW_H
