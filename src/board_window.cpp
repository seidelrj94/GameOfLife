#include <QPainter>
#include <QPalette>
#include <QDebug>

#include "board_window.hpp"

BoardWindow::BoardWindow(QWidget *parent)
{
    // initialize the board
    pBoard = new Board();

    // initialize the window
    QPalette palette = QPalette();
    palette.setColor(QPalette::Window, Qt::black);
    setAutoFillBackground(true);
    setPalette(palette);

    // initialize timer
    pTimer = new QTimer(this);

    // connect the timer signal with board update slot
    connect(pTimer, SIGNAL(timeout()), this, SLOT(update()));
}

void BoardWindow::init(uint32_t rows, uint32_t columns, uint32_t updateRate)
{
    // stop the timer
    pTimer->stop();

    // initialize the board
    pBoard->init(rows, columns);

    // set the updateRate
    updateRateMS = updateRate;

    // draw the initial board
    isFirstUpdate = true;
    update();
}

void BoardWindow::startTimer(void)
{
    // start the timer at the update rate
    pTimer->start(updateRateMS);
}

void BoardWindow::stopTimer(void)
{
    // pause the timer
    pTimer->stop();
}

Board* BoardWindow::getBoard(void)
{
    // return the boards current round
    return pBoard;
}

void BoardWindow::paintEvent(QPaintEvent *event)
{
    if (pBoard->isInitialized())
    {
        uint32_t cols = pBoard->getColumns();
        uint32_t rows = pBoard->getRows();

        float cellWidth = ((float) width()) / cols;
        float cellHeight = ((float) height()) / rows;

        // first update the board (if not the first time the board has been drawed)
        if (!isFirstUpdate)
        {
            pBoard->update();
        }

        // create a rectangle to paint, and scale it based on the widets size
        QPainter painter(this);

        std::vector<Cell> *pCells = pBoard->getCells();

        for (uint32_t idx = 0; idx < pCells->size(); idx++)
        {
            // save the state before we translate
            painter.save();

            // translate
            painter.translate((idx % cols) * cellWidth, (idx / cols) * cellHeight);

            // draw
            if (pCells->at(idx).getCurrentState() == Cell::ALIVE_E)
            {
                painter.setPen(Qt::green);
                painter.setBrush(Qt::green);
            }
            else
            {
                painter.setPen(Qt::NoPen);
                painter.setBrush(Qt::NoBrush);
            }
            painter.drawRect(0, 0, cellWidth, cellHeight);

            painter.restore();
        }

        // set first update to false so board will update from now on
        isFirstUpdate = false;

        // emit board updated so other widgets can update
        emit updated(pBoard->getRound());
    }
}