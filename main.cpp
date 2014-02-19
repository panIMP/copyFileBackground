#include <QApplication>
#include "copy.h"

int main(int argc, char* argv[]){
    QApplication app(argc,argv);
    Copy win;
    win.show();
    return app.exec();
}

