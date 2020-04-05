#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QButtonGroup>

class GameBoard;
class QPushButton;
class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();

private:
    QButtonGroup *_highLightGroup;
    GameBoard *_gameBoard;
    QPushButton *_newGame;
    QPushButton *_debugDump;
};

#endif // MAINWINDOW_H
