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
        uint32_t getRound(void);
    
    signals:

    private slots:

    protected:
        void paintEvent(QPaintEvent *) override;

    private:
        QTimer* timer;
        Board board;
};

#endif // __BOARD_WINDOW_H__