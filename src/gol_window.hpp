#ifndef __GOL_WINDOW_H__
#define __GOL_WINDOW_H__

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QSpinBox>
#include <QLineEdit>

#include "board_window.hpp"

class GOL_Window : public QWidget
{
    Q_OBJECT
    
    public:
        explicit GOL_Window(QWidget *parent = 0);
    
    signals:

    private slots:
        void initButtonClicked(void);
        void startButtonClicked(void);
        void boardUpdated(uint32_t);
    
    private:
        void initBoardGroup(void);
        void initControlGroup(void);
        void initStatusGroup(void);

        QGroupBox* pBoardGroup;
        BoardWindow* pBoardWindow;

        QGroupBox* pControlGroup;
        QSpinBox* pRowsBox;
        QSpinBox* pColsBox;
        QLineEdit* pRateLine;
        QLabel* pRowsLabel;
        QLabel* pColsLabel;
        QLabel* pRateLabel;
        QPushButton* pStartButton;
        QPushButton* pInitButton;

        QGroupBox* pStatusGroup;
        QLabel* pRoundLabel;
        QLineEdit* pRoundLine;

        bool isRunning;
};

#endif // __GOL_WINDOW_H__