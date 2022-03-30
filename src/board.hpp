#ifndef __BOARD_H__
#define __BOARD_H__

#include <cstdint>
#include <vector>

#include "cell.hpp"

class Board
{
    public:
        Board(void);
        Board(uint32_t, uint32_t);
        ~Board(void);

        uint32_t getRound(void);

        void init(uint32_t, uint32_t);
        void update(void);
        void print(void);

    private:
        std::vector<Cell> findNeighbors(uint32_t);
        uint32_t rows;
        uint32_t columns;
        uint32_t round;
        std::vector<Cell> cells;
};

#endif // __BOARD_H__
