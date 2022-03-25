#ifndef __CELL_H__
#define __CELL_H__

#include <vector>

class Cell
{
    public:
        enum state
        {
            ALIVE_E,
            DEAD_E,
        };
        Cell(void);
        Cell(Cell::state);
        ~Cell(void);
        Cell::state getCurrentState(void);
        void setCurrentState(Cell::state);
        void calculateNextState(std::vector<Cell> &);
        void update(void);
        void print(void);

    private:
        void aliveNextState(std::vector<Cell> &);
        void deadNextState(std::vector<Cell> &);

        Cell::state currentState;
        Cell::state nextState;
};

#endif // __CELL_H__
