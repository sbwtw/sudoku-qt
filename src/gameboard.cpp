#include "gameboard.h"
#include "cell.h"
#include "numpad.h"

#include <QGridLayout>
#include <QElapsedTimer>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QDebug>

extern "C" void update_callback(void *ptr, uint32_t row, uint32_t column)
{
    GameBoard *board = static_cast<GameBoard *>(ptr);
    if (board)
        QMetaObject::invokeMethod(board, "reloadCell", Qt::QueuedConnection, Q_ARG(uint32_t, row), Q_ARG(uint32_t, column));
}

GameBoard::GameBoard(QWidget *parent)
    : QWidget(parent)
{
    _hidedCell = nullptr;
    _sudokuBoard = sudoku_new();
    _numpad = new Numpad(this);
    _numpad->hide();

    sudoku_set_update_callback(_sudokuBoard, this, update_callback);

    for (int i(0); i != 81; ++i)
    {
        auto cell = new Cell(i, this);
        _cells.push_back(cell);

        connect(cell, &Cell::clicked, this, &GameBoard::onCellClicked);
    }

    _cellGridLayout = new QGridLayout;
    for (int i(0); i != 81; ++i)
        _cellGridLayout->addWidget(_cells[i], i / 9, i % 9);

    connect(_numpad, &Numpad::triggered, this, &GameBoard::onNumpadTriggered);

    setLayout(_cellGridLayout);
}

GameBoard::~GameBoard()
{
    sudoku_free(_sudokuBoard);
}

void GameBoard::newGame()
{
    QElapsedTimer timer;
    timer.start();
    qDebug() << "Generate start";
    sudoku_generate(_sudokuBoard);
    qDebug() << "Generate took" << timer.elapsed() << "ms";

    sudoku_dump(_sudokuBoard);
}

void GameBoard::debugDump()
{
    sudoku_dump(_sudokuBoard);
}

void GameBoard::reloadAllCell()
{
    for (int i(0); i != 9; ++i)
    {
        for (int j(0); j != 9; ++j) {
            reloadCell(i, j);
        }
    }
}

void GameBoard::reloadCell(uint32_t row, uint32_t column)
{
    auto n = sudoku_get_number(_sudokuBoard, row, column);
    auto s = sudoku_get_cell_state(_sudokuBoard, row, column);
    auto can = sudoku_get_candidate(_sudokuBoard, row, column);

    _cells[row * 9 + column]->setNumber(n);
    _cells[row * 9 + column]->setCellState(s);
    _cells[row * 9 + column]->setCandidate(can);
}

void GameBoard::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);

    const auto w = _cells[0]->width();
    const auto h = _cells[0]->height();

    QPainter p(this);
    auto top1 = (_cells[2]->pos() + _cells[3]->pos()) / 2 + QPoint(w / 2, 0);
    auto top2 = (_cells[5]->pos() + _cells[6]->pos()) / 2 + QPoint(w / 2, 0);
    auto bot1 = (_cells[74]->pos() + _cells[75]->pos()) / 2 + QPoint(w / 2, h);
    auto bot2 = (_cells[77]->pos() + _cells[78]->pos()) / 2 + QPoint(w / 2, h);
    auto left1 = (_cells[18]->pos() + _cells[27]->pos()) / 2 + QPoint(0, h / 2);
    auto left2 = (_cells[45]->pos() + _cells[54]->pos()) / 2 + QPoint(0, h / 2);
    auto right1 = (_cells[26]->pos() + _cells[35]->pos()) / 2 + QPoint(w, h / 2);
    auto right2 = (_cells[53]->pos() + _cells[62]->pos()) / 2 + QPoint(w, h / 2);

    auto pen = p.pen();
    pen.setColor(qRgb(72, 163, 219));
    pen.setWidth(2);
    p.setPen(pen);
    p.drawLine(top1, bot1);
    p.drawLine(top2, bot2);
    p.drawLine(left1, right1);
    p.drawLine(left2, right2);
}

void GameBoard::onCellClicked()
{
    auto cell = static_cast<Cell *>(sender());
    if (!cell || cell->pre_filled())
        return;

    if (_hidedCell != nullptr)
    {
        auto *item = _cellGridLayout->replaceWidget(_numpad, _hidedCell);
        delete item;

        _hidedCell->show();
    }

    auto *item = _cellGridLayout->replaceWidget(cell, _numpad);
    delete item;

    _hidedCell = cell;
    _hidedCell->hide();
    _numpad->show();
}

void GameBoard::onNumpadTriggered(const uint32_t num)
{
    auto *item = _cellGridLayout->replaceWidget(_numpad, _hidedCell);
    delete item;

    auto index = _cells.indexOf(_hidedCell);
    _numpad->hide();
    _hidedCell->show();
    _hidedCell = nullptr;

    if (index != -1)
        sudoku_set_cell(_sudokuBoard, index / 9, index % 9, num);
}
