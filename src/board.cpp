#include <iostream>

#include "board.hpp"

Board::Board(void)
{
    rows = 0u;
    columns = 0u;
    round = 0u;
}

Board::Board(uint32_t rows, uint32_t columns)
{
    this->rows = rows;
    this->columns = columns;
    round = 0u;
    cells.resize(rows*columns);
}

Board::~Board(void)
{
    // nothing to do
}

uint32_t Board::getRound(void)
{
    return round;
}

void Board::init(uint32_t, uint32_t)
{
    // initialize data
    this->rows = rows;
    this->columns = columns;
    round = 0u;
    cells.resize(rows*columns);

    // initialize cells with random states
    for (uint32_t idx = 0u; idx < cells.size(); idx++)
    {
        Cell::state state = (((rand() % 2) == 0) ? Cell::ALIVE_E : Cell::DEAD_E);
        cells.at(idx).setCurrentState(state);
    }
}

void Board::update(void)
{
    // for each cell, find its neighbors and calculate the next state
    for (uint32_t idx = 0u; idx < cells.size(); idx++)
    {
        std::vector<Cell> neighbors = findNeighbors(idx);
        cells.at(idx).calculateNextState(neighbors);
    }

    // for each cell, set the current state to the next state
    for (uint32_t idx = 0u; idx < cells.size(); idx++)
    {
        cells.at(idx).update();
    }

    // increment round
    round++;
}

void Board::print(void)
{
    for (uint32_t rowIdx = 0u; rowIdx < rows; rowIdx++)
    {
        for (uint32_t columnIdx = 0u; columnIdx < columns; columnIdx++)
        {
            uint32_t idx = (columns * rowIdx) + columnIdx;
            cells.at(idx).print();
        }
        std::cout << std::endl;
    }
}

std::vector<Cell> Board::findNeighbors(uint32_t idx)
{
    uint32_t rowIdx = idx / columns;
    uint32_t colIdx = idx % columns;
    uint32_t neighborIdx = 0u;
    std::vector<Cell> neighbors;

    // have 8 possible positions to check
    // upper left
    if ((rowIdx > 0u) && // not first row
        (colIdx > 0u))   // not first columnt
    {
        neighborIdx = (columns * (rowIdx - 1u)) + (colIdx - 1u);
        neighbors.push_back(cells.at(neighborIdx));
    }

    // above
    if (rowIdx > 0u) // not first row
    {
        neighborIdx = (columns * (rowIdx - 1u)) + colIdx;
        neighbors.push_back(cells.at(neighborIdx));
    }

    // upper right
    if ((rowIdx > 0u) &&           // not first row
        (colIdx < (columns - 1u))) // not last column
    {
        neighborIdx = (columns * (rowIdx - 1u)) + (colIdx + 1u);
        neighbors.push_back(cells.at(neighborIdx));
    }

    // left
    if (colIdx > 0u) // not first column
    {
        neighborIdx = (columns * rowIdx) + (colIdx - 1u);
        neighbors.push_back(cells.at(neighborIdx));
    }

    // right
    if (colIdx < (columns - 1u)) // not last column
    {
        neighborIdx = (columns * rowIdx) + (colIdx + 1u);
        neighbors.push_back(cells.at(neighborIdx));
    }

    // lower left
    if ((rowIdx < (rows - 1u)) && // not last row
        (colIdx > 0u))            // not first columnt
    {
        neighborIdx = (columns * (rowIdx + 1u)) + (colIdx - 1u);
        neighbors.push_back(cells.at(neighborIdx));
    }

    // below
    if (rowIdx < (rows - 1u)) // not last row
    {
        neighborIdx = (columns * (rowIdx + 1u)) + colIdx;
        neighbors.push_back(cells.at(neighborIdx));
    }

    // lower right
    if ((rowIdx < (rows - 1u)) &&  // not last row
        (colIdx < (columns - 1u))) // not last column
    {
        neighborIdx = (columns * (rowIdx + 1u)) + (colIdx + 1u);
        neighbors.push_back(cells.at(neighborIdx));
    }

    return neighbors;
}