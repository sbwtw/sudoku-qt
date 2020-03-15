#ifndef CELL_H
#define CELL_H

#include <sudoku.h>

#include <QAbstractButton>

class Cell : public QAbstractButton
{
    Q_OBJECT
public:
    Cell(QWidget *parent);

    inline bool filled() const
    { return bool(_cellStates & CellStates_FILLED); }

public slots:
    void setNumber(char number);
    void setCandidate(uint32_t candidate);
    void setCellState(CellStates state);

private:
    void paintEvent(QPaintEvent *) override;

    QString candidatesString() const;

private:
    char _number;
    uint32_t _candidate;
    CellStates _cellStates;
};

#endif // CELL_H
