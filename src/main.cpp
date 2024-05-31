#include <csignal>
#include <mylibrary.h>
#include <QtWidgets/QApplication>

#include "mainwindow.h"

void handleSigterm(int)
{
    QApplication::quit();
}

int main(int argc, char *argv[])
{
    signal(SIGTERM, handleSigterm);
    signal(SIGINT, handleSigterm);

    QApplication app(argc, argv);

    MainWindow win;

    win.show();

    qDebug() << "QtApp";

    sayHello("Bro");

    return app.exec();
}