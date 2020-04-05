#include "numpad.h"

#include <QGridLayout>
#include <QDebug>
#include <QTimer>

Numpad::Numpad(QWidget *parent)
    : QWidget(parent)
    , _selected(0)
{
    QGridLayout *num_grid = new QGridLayout;
    num_grid->setSpacing(0);
    num_grid->setMargin(0);

    for (int i(0); i != 9; ++i)
    {
        QPushButton *b = new QPushButton(QString::number(i + 1));

        num_grid->addWidget(b, i / 3, i % 3);

        connect(b, &QPushButton::clicked, this, &Numpad::onSelected);

        _buttons.append(b);
    }

    setLayout(num_grid);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
}

void Numpad::onSelected()
{
    QPushButton *b = static_cast<QPushButton *>(sender());
    const auto num = _buttons.indexOf(b);

    if (num != -1)
    {
        _selected = num + 1;
        emit triggered(num + 1);
    }
}
