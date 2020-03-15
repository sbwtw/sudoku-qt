#ifndef NUMPAD_H
#define NUMPAD_H

#include <QWidget>
#include <QPushButton>
#include <QList>

class Numpad : public QWidget
{
    Q_OBJECT
public:
    explicit Numpad(QWidget *parent);

    uint32_t selected() const
    { return _selected; }

private slots:
    void onSelected();

private:
    uint32_t _selected;
    QList<QPushButton *> _buttons;
};

#endif // NUMPAD_H
