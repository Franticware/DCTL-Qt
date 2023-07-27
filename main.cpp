#include "mainwindow.h"

#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <errno.h>
#include <dlfcn.h>

#include "dctl_plugin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFileDialog dialog;
    dialog.setWindowTitle("Select plugin");
    dialog.setNameFilter("Plugins (*.plugin);;All files (*)");
    if (dialog.exec())
    {
        if (dialog.selectedFiles().size() == 1)
        {
            if (!DCTL_loadPlugin(dialog.selectedFiles()[0].toStdString().c_str()))
            {
                QMessageBox::critical(nullptr, "Error", "Could not load plugin", QMessageBox::Ok);
                return 1;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }

    MainWindow w;
    w.show();
    return a.exec();
}
