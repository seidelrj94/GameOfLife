#include <ctime>

#include <QGuiApplication>
#include <QPushButton>

#include "version.h"
#include "board.hpp"
#include "gol_window.hpp"

int main(int argc, char* argv[])
{
    QGuiApplication app (argc, argv);

    // initialize the random number generator
    srand(time(0));

    // create and show window
    GOL_Window window;
    window.show();

    // run my window
    return app.exec();
}

