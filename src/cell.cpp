#include "cell.h"
#include "numpad.h"

#include <QPaintEvent>
#include <QPainter>
#include <QTimer>
#include <QDebug>

Cell::Cell(uint32_t index, QWidget *parent)
    : QAbstractButton(parent)
    , _number(0)
    , _index(index)
    , _candidate(0)
    , _cellStates(CellStates_NONE)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Cell::setNumber(char number)
{
    _number = number;
    update();
}

void Cell::setCandidate(uint32_t candidate)
{
    _candidate = candidate;
    update();
}

void Cell::setCellState(CellStates state)
{
    _cellStates = state;
    update();
}

void Cell::paintEvent(QPaintEvent *)
{
    const auto r = rect().marginsRemoved(QMargins(2, 2, 2, 2));

    QPainter p(this);
    p.setPen(Qt::NoPen);

    // draw background
    if (_cellStates & CellStates_HIGH_LIGHT)
        p.setBrush(QBrush(qRgb(255, 0, 0)));
    else
        p.setBrush(QBrush(qRgb(239, 231, 144)));
    p.drawRoundedRect(r, 5, 5);

    p.setPen(qRgb(24, 142, 101));
    // draw candidate
    p.drawText(r, Qt::AlignLeft | Qt::AlignTop, candidatesString());

#ifdef QT_DEBUG
    auto f = p.font();
    f.setPixelSize(8);
    p.setFont(f);
    const auto text = QString("%1: (%2, %3)").arg(_index).arg(_index / 9).arg(_index % 9);
    p.drawText(r, Qt::AlignRight | Qt::AlignBottom, text);
#endif

    if (_number)
    {
        // draw selected
        if ((_cellStates & CellStates_CONFLICT) == CellStates_CONFLICT)
            p.setPen(Qt::red);
        else if ((_cellStates & CellStates_PRE_FILLED) == CellStates_PRE_FILLED)
            p.setPen(Qt::black);

        auto f = p.font();
        f.setBold(true);
        f.setPixelSize(24);
        p.setFont(f);
        p.drawText(r, Qt::AlignCenter, QString::number(_number));
    }
}

QString Cell::candidatesString() const
{
    QString s;
    for (int i(1); i != 10; ++i)
    {
        if ((_candidate & (1 << i)) != 0)
        {
            s.append(i + '0');
        }
    }

    return s;
}
