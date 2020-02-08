#include "mainwindow.h"
#include <QApplication>
#include "Blp.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Blp filter;
    double data = 0.21;
    double y = 0;
    while(true)
    {
        std::cout << "======please input data =======" <<  std::endl;
        std::cout << " data = " << data << std::endl;
        //std::cin>>data;
        //std::cout << " data = " << std::endl;
        y = filter.smooth_averpara_filter(data);
        std::cout << " y = " << y << std::endl;
    }
    return a.exec();
}
