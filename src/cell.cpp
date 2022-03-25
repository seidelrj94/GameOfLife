#include <iostream>

#include "cell.hpp"

Cell::Cell()
{
    currentState = Cell::DEAD_E;
    nextState = Cell::DEAD_E;
}

Cell::Cell(Cell::state state)
{
    currentState =state;
    nextState = Cell::DEAD_E;
}

Cell::~Cell()
{
    // nothing to do here
}

void Cell::setCurrentState(Cell::state state)
{
    currentState = state;
}

void Cell::calculateNextState(std::vector<Cell> &neighbors)
{
    switch(currentState)
    {
        case Cell::ALIVE_E:
            aliveNextState(neighbors);
            break;
        case Cell::DEAD_E:
            deadNextState(neighbors);
            break;
        default:
            break;
    }
}

void Cell::update(void)
{
    currentState = nextState;
}

void Cell::print(void)
{
    switch(currentState)
    {
        case Cell::ALIVE_E:
            std::cout << "O";
            break;
        case Cell::DEAD_E:
            std::cout << ".";
            break;
        default:
            break;
    }
}

void Cell::aliveNextState(std::vector<Cell> &neighbors)
{
    // count the number of live neighbors
    uint32_t numAliveNeighbors = 0u;
    for (uint32_t idx = 0u; idx < neighbors.size(); idx++)
    {
        if (neighbors.at(idx).currentState == Cell::ALIVE_E)
        {
            numAliveNeighbors++;
        }
    }

    // fewer than 2 live neighbors, die of underpopulation
    if (numAliveNeighbors < 2u)
    {
        nextState = Cell::DEAD_E;
    }
    // 2 or 3 live neighbors, live
    else if (numAliveNeighbors < 4u)
    {
        nextState = Cell::ALIVE_E;
    }
    // more than 3 live neighbors, die of overpopulation
    else
    {
        nextState = Cell::DEAD_E;
    }
}

void Cell::deadNextState(std::vector<Cell> &neighbors)
{
    // count the number of live neighbors
    uint32_t numAliveNeighbors = 0u;
    for (uint32_t idx = 0u; idx < neighbors.size(); idx++)
    {
        if (neighbors.at(idx).currentState == Cell::ALIVE_E)
        {
            numAliveNeighbors++;
        }
    }

    // if exactly 3 live neighbors, become a new cell
    if (numAliveNeighbors == 3u)
    {
        nextState = Cell::ALIVE_E;
    }
    // stay dead
    else
    {
        nextState = Cell::DEAD_E;
    }
}