#include "highlightbuttongroup.h"

#include <QHBoxLayout>
#include <QDebug>

HighlightButtonGroup::HighlightButtonGroup(QWidget *parent)
    : QWidget(parent)
    , _currentChecked(nullptr)
{
    QHBoxLayout *layout = new QHBoxLayout;
    for (int i(1); i != 10; ++i) {
        QPushButton *b = new QPushButton(QString::number(i));
        b->setCheckable(true);
        b->setFixedSize(24, 24);
        _buttons.append(b);
        layout->addWidget(b);

        connect(b, &QPushButton::clicked, this, &HighlightButtonGroup::onButtonClicked);
    }

    setLayout(layout);
}

void HighlightButtonGroup::onButtonClicked()
{
    QPushButton *b = qobject_cast<QPushButton *>(sender());
    assert(b);

    if (_currentChecked)
    {
        _currentChecked->blockSignals(true);
        _currentChecked->setChecked(false);
        _currentChecked->blockSignals(false);
    }

    if (b == _currentChecked)
    {
        _currentChecked = nullptr;
        emit highlightRequest(std::optional<int>());
    } else {
        assert(b->isChecked());
        _currentChecked = b;
        auto idx = _buttons.indexOf(b);
        assert(idx != -1);

        emit highlightRequest(std::optional<int>(idx + 1));
    }
}
