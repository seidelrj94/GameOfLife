#include <iostream>
#include <string>
#include <ctime>

#include "version.h"
#include "board.hpp"

int main(int argc, char* argv[])
{
    std::cout << argv[0] << " Version: " << VERSION_D << std::endl;
    int status = 0;

    if (argc != 3)
    {
        std::cout << "Usage: life rows columns" << std::endl;
        status = 1;
    }

    if (status == 0)
    {
        uint32_t rows = (uint32_t) std::stoi(argv[1]);
        uint32_t columns = (uint32_t) std::stoi(argv[2]);
        Board board(rows, columns);

        // initialize the random number generator
        srand(time(0));

        // initialize the board
        board.init();

        // print the initial state of the board
        board.print();
        std::cout << std::endl << std::endl;

        // back up stdout so we will overwrite it
        while (true)
        {
            // wait a few seconds then update the state
            time_t startTime = time(NULL);
            while (difftime(time(NULL), startTime) < 3.0)
            {
            }

            // update the state
            board.update();

            // print updated state
            board.print();
            std::cout << std::endl << std::endl;
        }
    }

    return status;
}

