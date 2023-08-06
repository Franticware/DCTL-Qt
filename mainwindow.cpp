#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QSpacerItem>
#include <QFileDialog>
#include <QMessageBox>

#include "dctl_plugin.h"
#include "wrapsettings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->labelParamsTitle->setText("Parameters of " + g_wrapSettings.getLensName());
    {
        QImage imgTmp(1, 1, QImage::Format_ARGB32);
        imgTmp.fill(Qt::black);
        m_image.swap(imgTmp);
    }
    ui->widget->setParams(&m_image, &m_zoom, ui->spinBoxThreads, ui->checkBoxCenterLines, &m_equirectCheckBoxValues);

    updateZoom(ui->comboBoxZoom->currentText());

    auto resetAll = new QPushButton("⟲", this);
    resetAll->setMaximumWidth(resetButtonMaxWidth);
    resetAll->setToolTip("Reset all parameters");
    QGridLayout* gl = dynamic_cast<QGridLayout*>(ui->scrollArea->widget()->layout());
    gl->addWidget(resetAll, 0, 3);

    ui->comboBoxZoom->setFocus();

    void* param = nullptr;
    int row = 0;
    while ((param = DCTL_getParam(row)))
    {
        DCTL_generic* paramGen = (DCTL_generic*)param;
        if (paramGen->type == DCTL_CHECKBOX && strcmp(paramGen->name, "EQUIRECT") == 0)
        {
            m_equirectCheckBoxValues = (DCTL_checkBox*)paramGen;
        }
        addParamWidget(row + 1, resetAll, param);
        ++row;
    }

    gl->addItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding), row + 1, 0);
}

void MainWindow::addParamWidget(int row, QPushButton* resetAll, void* param)
{
    DCTL_generic* paramGeneric = (DCTL_generic*)param;
    if (paramGeneric->type == DCTL_CHECKBOX)
    {
        DCTL_checkBox* paramCheckbox = (DCTL_checkBox*)param;
        DCTL_QCheckBox& cbData = *new DCTL_QCheckBox(this);
        cbData.data = paramCheckbox;

        cbData.data->val = cbData.data->def;

        QGridLayout* gl = dynamic_cast<QGridLayout*>(ui->scrollArea->widget()->layout());

        auto w = new QCheckBox(cbData.data->label);
        cbData.cb = w;

        w->setChecked(cbData.data->def);

        connect(w, &QCheckBox::stateChanged, &cbData, &DCTL_QCheckBox::stateChanged);
        connect(w, &QCheckBox::stateChanged, ui->widget, qOverload<>(&GrWidget::updateResultImage));
        cbData.stateChanged(w->checkState());

        gl->addWidget(w, row, 1);

        auto rb = new QPushButton("⟲");
        rb->setMaximumWidth(resetButtonMaxWidth);
        gl->addWidget(rb, row, 3);
        connect(rb, &QPushButton::clicked, &cbData, &DCTL_QCheckBox::reset);
        connect(resetAll, &QPushButton::clicked, &cbData, &DCTL_QCheckBox::reset);
    }
    else if (paramGeneric->type == DCTL_SLIDER)
    {
        DCTL_slider* paramSlider = (DCTL_slider*)param;
        DCTL_QSlider& sliderData = *new DCTL_QSlider(this);
        sliderData.data = paramSlider;

        sliderData.udef = sliderData.data->def;
        g_wrapSettings.loadDefault(sliderData.data->name, sliderData.udef);
        sliderData.data->val = sliderData.udef;

        QGridLayout* gl = dynamic_cast<QGridLayout*>(ui->scrollArea->widget()->layout());

        auto l = new QLabel(sliderData.data->label);
        auto w = new QSlider(Qt::Horizontal);
        sliderData.sl = w;

        w->setMinimum(0);
        w->setMaximum((sliderData.data->hi - sliderData.data->lo)/sliderData.data->step);
        w->setValue(std::floor((sliderData.data->val - sliderData.data->lo)/sliderData.data->step));
        w->setPageStep(1);

        connect(w, &QSlider::valueChanged, &sliderData, &DCTL_QSlider::valueChanged);
        connect(w, &QSlider::valueChanged, ui->widget, qOverload<>(&GrWidget::updateResultImage));

        auto v = new QLabel();
        sliderData.labelValue = v;
        sliderData.valueChanged(w->value());

        gl->addWidget(l, row, 0);
        gl->addWidget(w, row, 1);
        gl->addWidget(v, row, 2);

        auto rb = new QPushButton("⟲");
        rb->setMaximumWidth(resetButtonMaxWidth);
        gl->addWidget(rb, row, 3);
        connect(rb, &QPushButton::clicked, &sliderData, &DCTL_QSlider::reset);
        connect(resetAll, &QPushButton::clicked, &sliderData, &DCTL_QSlider::reset);

        auto mb = new QPushButton("...");
        mb->setMaximumWidth(resetButtonMaxWidth);
        gl->addWidget(mb, row, 4);
        connect(mb, &QPushButton::clicked, &sliderData, &DCTL_QSlider::openMenu);
    }
}

void MainWindow::updateZoom(const QString& zoom)
{
    QString z = zoom;
    z.replace('%', ' ');
    m_zoom = z.trimmed().toInt();
    m_zoom = std::clamp(m_zoom, 1, 100);

    ui->widget->updateResultImage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openImage(QString newImageFilename)
{
    m_filename = newImageFilename;
    ui->statusbar->showMessage("Opening...");
    QApplication::processEvents();
    if (m_image.load(m_filename))
    {
        m_image = m_image.convertToFormat(QImage::Format_ARGB32);
        ui->statusbar->showMessage("Image opened, " + QString::number(m_image.width()) + "x" + QString::number(m_image.height()));
        ui->widget->updateResultImage();
    }
    else
    {
        ui->statusbar->showMessage("Error loading " + m_filename);
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QFileDialog dialog(this);
    dialog.setNameFilter("Images (*.png *.jpg);;All files (*)");
    if (dialog.exec())
    {
        if (dialog.selectedFiles().size() == 1)
        {
            openImage(dialog.selectedFiles()[0]);
        }
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QFileDialog dialog(this);
    QString saveFileName = QFileDialog::getSaveFileName(this, QString(),
                                                        m_filename + "_dfe.png",
                                                        tr("PNG image (*.png)"));
    if (!saveFileName.isEmpty())
    {
        ui->statusbar->showMessage("Saving...");
        QApplication::processEvents();

        QImage proc;
        ui->widget->processImage(proc, 100, 1);

        proc.save(saveFileName);

        ui->statusbar->showMessage("Saved " + saveFileName);
    }
}

void MainWindow::on_comboBoxZoom_currentTextChanged(const QString &arg1)
{
    updateZoom(arg1);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, "About DeFisheye",
                             "© 2023 Franticware\n"
                             "github.com/Franticware/DCTL-Qt\n\n"
                             "DCTL plugin by roukou3\n"
                             "github.com/roukou3/DCTL\n\n"
                             "MIT License"
                             ,
                             QMessageBox::Ok);

}


void MainWindow::on_checkBoxCenterLines_stateChanged(int)
{
    ui->widget->update();
}


void MainWindow::on_actionE_xit_triggered()
{
    close();
}

