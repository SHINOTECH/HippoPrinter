#include "mainwindow.h"
#include "Console.h"
#include <QtWidgets/QApplication>
#include <QStyleFactory>
#include <iostream>

using namespace std;
int main(int argc, char *argv[])
{
	//CConsoleOutput::Instance();
	//QApplication::setStyle(QStyleFactory::create("cleanlooks"));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
