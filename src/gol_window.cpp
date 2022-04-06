#include <QFormLayout>
#include <QGridLayout>
#include <QApplication>

#include "version.h"
#include "gol_window.hpp"

GOL_Window::GOL_Window(QWidget *parent)
{
    // initialize the group boxes
    initBoardGroup();
    initControlGroup();
    initStatusGroup();

    // connect signals to slots
    connect(pStartButton, SIGNAL (clicked()), this, SLOT (startButtonClicked(void)));
    connect(pInitButton, SIGNAL (clicked()), this, SLOT (initButtonClicked(void)));
    connect(pBoardWindow, SIGNAL (updated(uint32_t)), this, SLOT (boardUpdated(uint32_t)));

    // finalize layout
    QGridLayout* pMainLayout = new QGridLayout();
    setLayout(pMainLayout);
    pMainLayout->addWidget(pBoardGroup, 0, 0, 4, 4);
    pMainLayout->addWidget(pControlGroup, 0, 4, 1, 1);
    pMainLayout->addWidget(pStatusGroup, 4, 0, 1, 4);

    for(uint32_t idx = 0u; idx < 5u; idx++)
    {
        pMainLayout->setRowStretch(idx, 5);
        pMainLayout->setColumnStretch(idx, 1);
    }
    pMainLayout->setRowStretch(4, 1);

    setWindowTitle(tr("Game of Life - v")+tr(VERSION_D));
    

    setFixedSize(1000, 1000);

    isRunning = false;
}

void GOL_Window::initButtonClicked(void)
{
    // reset the start button
    pBoardWindow->stopTimer();
    pStartButton->setText("Start");
    isRunning = false;

    // initalize the button with the values in the spin box
    pBoardWindow->init(pRowsBox->value(), pColsBox->value(), pRateLine->text().toUInt());
}

void GOL_Window::startButtonClicked(void)
{
    // if the button is checked, start the simulation
    if (isRunning)
    {
        pBoardWindow->stopTimer();
        pStartButton->setText("Start");
        isRunning = false;
    }
    else
    {
        if(pBoardWindow->getBoard()->isInitialized())
        {
            pBoardWindow->startTimer();
            pStartButton->setText("Stop");
            isRunning = true;
        }
    }
}

void GOL_Window::boardUpdated(uint32_t newRound)
{
    pRoundLine->setText(QString::number(newRound));
}

void GOL_Window::initBoardGroup(void)
{
    // initialize group box
    pBoardGroup = new QGroupBox(tr("Board"), this);

    // initialize the board window
    pBoardWindow = new BoardWindow();

    QHBoxLayout* pLayout = new QHBoxLayout();
    pLayout->addWidget(pBoardWindow);

    pBoardGroup->setLayout(pLayout);
}


void GOL_Window::initControlGroup(void)
{
    // initialize group box
    pControlGroup = new QGroupBox(tr("Controller"), this);

    // initialize Spin boxes and labels
    pRowsBox = new QSpinBox();
    pRowsBox->setRange(1,100);
    pRowsBox->setSingleStep(1);

    pColsBox = new QSpinBox();
    pColsBox->setRange(1,100);
    pColsBox->setSingleStep(1);

    pRateLine = new QLineEdit("0");

    pRowsLabel = new QLabel(tr("Rows:"));
    pRowsLabel->setBuddy(pRowsBox);

    pColsLabel = new QLabel(tr("Columns:"));
    pColsLabel->setBuddy(pColsLabel);

    pRateLabel = new QLabel(tr("Update Rate (ms):"));
    pRateLabel->setBuddy(pRateLine);

    // initialize buttons
    pStartButton = new QPushButton("Start");
    pInitButton = new QPushButton("Init");

    // set layout of group box
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(pRowsLabel, 0, 0, Qt::AlignRight);
    layout->addWidget(pRowsBox, 0, 1);
    layout->addWidget(pColsLabel, 1, 0, Qt::AlignRight);
    layout->addWidget(pColsBox, 1, 1);
    layout->addWidget(pRateLabel, 2, 0, Qt::AlignRight);
    layout->addWidget(pRateLine, 2, 1);
    layout->addWidget(pInitButton, 3, 0);
    layout->addWidget(pStartButton, 3, 1);

    layout->setRowStretch(0, 1);
    layout->setRowStretch(1, 1);
    layout->setRowStretch(2, 1);
    layout->setRowStretch(3, 1);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(0, 1);


    pControlGroup->setLayout(layout);
}

void GOL_Window::initStatusGroup(void)
{
    // initialize group box
    pStatusGroup = new QGroupBox(tr("Status"), this);
    
    pRoundLine = new QLineEdit("0");
    pRoundLine->setReadOnly(true);
    
    pRoundLabel = new QLabel(tr("Round:"));
    pRoundLabel->setBuddy(pRoundLine);

    QFormLayout* layout = new QFormLayout();
    layout->addRow(pRoundLabel, pRoundLine);

    pStatusGroup->setLayout(layout);
}