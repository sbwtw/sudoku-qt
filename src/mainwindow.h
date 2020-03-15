#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class GameBoard;
class QPushButton;
class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();

private:
    GameBoard *_gameBoard;
    QPushButton *_newGame;
    QPushButton *_debugDump;
};

#endif // MAINWINDOW_H
