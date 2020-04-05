#ifndef HIGHLIGHTBUTTONGROUP_H
#define HIGHLIGHTBUTTONGROUP_H

#include <QWidget>
#include <QList>
#include <QPushButton>

#include <optional>

class HighlightButtonGroup : public QWidget
{
    Q_OBJECT
public:
    explicit HighlightButtonGroup(QWidget *parent = nullptr);

signals:
    void highlightRequest(std::optional<int>);

private slots:
    void onButtonClicked();

private:
    QList<QPushButton *> _buttons;
    QPushButton *_currentChecked;
};

#endif // HIGHLIGHTBUTTONGROUP_H
