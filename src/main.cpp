#include <ctime>

#include <QApplication>

#include "gol_window.hpp"

int main(int argc, char* argv[])
{
    QApplication app (argc, argv);

    // initialize the random number generator
    srand(time(0));

    // create and show window
    GOL_Window window;
    window.show();

    // run my window
    return app.exec();
}

