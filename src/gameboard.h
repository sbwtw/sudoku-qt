#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <sudoku.h>

#include <QWidget>

#include <vector>

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

private:
    std::vector<Cell *> _cells;
    Board *_sudokuBoard;
};

#endif // GAMEBOARD_H
