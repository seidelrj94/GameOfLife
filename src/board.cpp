#include <iostream>

#include "board.hpp"

Board::Board(void)
{
    // set everything to not initialized
    rows = 0u;
    columns = 0u;
    round = 0u;
    initialized = false;
    pCells = new std::vector<Cell>();
}

Board::Board(uint32_t rows, uint32_t columns)
{
    // initialize data
    this->rows = rows;
    this->columns = columns;
    round = 0u;
    initialized = false;
    pCells = new std::vector<Cell>(rows*columns);

    // initialize cells with random states
    for (uint32_t idx = 0u; idx < pCells->size(); idx++)
    {
        Cell::state state = (((rand() % 2) == 0) ? Cell::ALIVE_E : Cell::DEAD_E);
        pCells->at(idx).setCurrentState(state);
    }

    initialized = true;
}

Board::~Board(void)
{
    delete pCells;
}

uint32_t Board::getRows(void)
{
    return rows;
}

uint32_t Board::getColumns(void)
{
    return columns;
}

uint32_t Board::getRound(void)
{
    return round;
}

std::vector<Cell>* Board::getCells(void)
{
    return pCells;
}

bool Board::isInitialized(void)
{
    return initialized;
}

void Board::init(uint32_t rows, uint32_t columns)
{
    // initialize data
    this->rows = rows;
    this->columns = columns;
    round = 0u;
    pCells->resize(rows*columns);

    // initialize cells with random states
    for (uint32_t idx = 0u; idx < pCells->size(); idx++)
    {
        Cell::state state = (((rand() % 2) == 0) ? Cell::ALIVE_E : Cell::DEAD_E);
        pCells->at(idx).setCurrentState(state);
    }

    initialized = true;
}

void Board::update(void)
{
    // for each cell, find its neighbors and calculate the next state
    for (uint32_t idx = 0u; idx < pCells->size(); idx++)
    {
        std::vector<Cell>* pNeighbors = findNeighbors(idx);
        pCells->at(idx).calculateNextState(pNeighbors);
        delete pNeighbors;
    }

    // for each cell, set the current state to the next state
    for (uint32_t idx = 0u; idx < pCells->size(); idx++)
    {
        pCells->at(idx).update();
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
            pCells->at(idx).print();
        }
        std::cout << std::endl;
    }
}

std::vector<Cell>* Board::findNeighbors(uint32_t idx)
{
    uint32_t rowIdx = idx / columns;
    uint32_t colIdx = idx % columns;
    uint32_t neighborIdx = 0u;
    std::vector<Cell>* pNeighbors = new std::vector<Cell>();

    // have 8 possible positions to check
    // upper left
    if ((rowIdx > 0u) && // not first row
        (colIdx > 0u))   // not first columnt
    {
        neighborIdx = (columns * (rowIdx - 1u)) + (colIdx - 1u);
        pNeighbors->push_back(pCells->at(neighborIdx));
    }

    // above
    if (rowIdx > 0u) // not first row
    {
        neighborIdx = (columns * (rowIdx - 1u)) + colIdx;
        pNeighbors->push_back(pCells->at(neighborIdx));
    }

    // upper right
    if ((rowIdx > 0u) &&           // not first row
        (colIdx < (columns - 1u))) // not last column
    {
        neighborIdx = (columns * (rowIdx - 1u)) + (colIdx + 1u);
        pNeighbors->push_back(pCells->at(neighborIdx));
    }

    // left
    if (colIdx > 0u) // not first column
    {
        neighborIdx = (columns * rowIdx) + (colIdx - 1u);
        pNeighbors->push_back(pCells->at(neighborIdx));
    }

    // right
    if (colIdx < (columns - 1u)) // not last column
    {
        neighborIdx = (columns * rowIdx) + (colIdx + 1u);
        pNeighbors->push_back(pCells->at(neighborIdx));
    }

    // lower left
    if ((rowIdx < (rows - 1u)) && // not last row
        (colIdx > 0u))            // not first columnt
    {
        neighborIdx = (columns * (rowIdx + 1u)) + (colIdx - 1u);
        pNeighbors->push_back(pCells->at(neighborIdx));
    }

    // below
    if (rowIdx < (rows - 1u)) // not last row
    {
        neighborIdx = (columns * (rowIdx + 1u)) + colIdx;
        pNeighbors->push_back(pCells->at(neighborIdx));
    }

    // lower right
    if ((rowIdx < (rows - 1u)) &&  // not last row
        (colIdx < (columns - 1u))) // not last column
    {
        neighborIdx = (columns * (rowIdx + 1u)) + (colIdx + 1u);
        pNeighbors->push_back(pCells->at(neighborIdx));
    }

    return pNeighbors;
}