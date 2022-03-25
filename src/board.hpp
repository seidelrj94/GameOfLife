#ifndef __BOARD_H__
#define __BOARD_H__

#include <cstdint>
#include <vector>

#include "cell.hpp"

class Board
{
    public:
        Board(uint32_t, uint32_t);
        ~Board(void);
        void init(void);
        void update(void);
        void print(void);

    private:
        std::vector<Cell> findNeighbors(uint32_t);
        uint32_t rows;
        uint32_t columns;
        std::vector<Cell> cells;
};

#endif // __BOARD_H__
