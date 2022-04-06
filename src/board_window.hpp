#ifndef __BOARD_WINDOW_H__
#define __BOARD_WINDOW_H__

#include <cstdint>

#include <QWidget>
#include <QTimer>

#include "board.hpp"

class BoardWindow : public QWidget
{
    Q_OBJECT
    public:
        explicit BoardWindow(QWidget *parent = 0);

        Board* getBoard(void);
        void init(uint32_t, uint32_t, uint32_t);
        void startTimer(void);
        void stopTimer(void);

    signals:
        void updated(uint32_t);

    private slots:

    protected:
        void paintEvent(QPaintEvent *) override;

    private:
        QTimer* pTimer;
        Board* pBoard;
        bool isFirstUpdate;
        uint32_t updateRateMS;
};

#endif // __BOARD_WINDOW_H__