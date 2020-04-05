#ifndef CELL_H
#define CELL_H

#include <sudoku.h>

#include <QAbstractButton>

class Cell : public QAbstractButton
{
    Q_OBJECT
public:
    Cell(uint32_t index, QWidget *parent);

    inline bool filled() const
    { return (_cellStates & CellStates_FILLED) == CellStates_FILLED; }

    inline bool pre_filled() const
    { return (_cellStates & CellStates_PRE_FILLED) == CellStates_PRE_FILLED; }

public slots:
    void setNumber(char number);
    void setCandidate(uint32_t candidate);
    void setCellState(CellStates state);

private:
    void paintEvent(QPaintEvent *) override;

    QString candidatesString() const;

private:
    char _number;
    uint32_t _index;
    uint32_t _candidate;
    CellStates _cellStates;
};

#endif // CELL_H
