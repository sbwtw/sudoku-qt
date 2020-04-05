#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "numpad.h"
#include <sudoku.h>
#include <vector>

#include <QWidget>
#include <QGridLayout>

class Cell;
class GameBoard : public QWidget
{
    Q_OBJECT
public:
    explicit GameBoard(QWidget *parent = nullptr);
    ~GameBoard();

public slots:
    void newGame();
    void debugDump();
    void reloadAllCell();
    void reloadCell(uint32_t row, uint32_t column);

private:
    void paintEvent(QPaintEvent *) override;

private slots:
    void onCellClicked();
    void onNumpadTriggered(const uint32_t num);

private:
    QList<Cell *> _cells;
    Board *_sudokuBoard;
    Numpad *_numpad;
    Cell *_hidedCell;
    QGridLayout *_cellGridLayout;
};

#endif // GAMEBOARD_H
