#include "mainwindow.h"
#include "gameboard.h"

#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow()
    : QWidget(nullptr)
{
    _gameBoard = new GameBoard;
    _newGame = new QPushButton("New Game");
    _debugDump = new QPushButton("Dump");

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(_newGame);
    buttonsLayout->addWidget(_debugDump);

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addLayout(buttonsLayout);
    centralLayout->addWidget(_gameBoard);

    setLayout(centralLayout);
    resize(750, 700);

    connect(_newGame, &QPushButton::clicked, _gameBoard, &GameBoard::newGame);
    connect(_debugDump, &QPushButton::clicked, _gameBoard, &GameBoard::debugDump);
}

MainWindow::~MainWindow()
{
    _gameBoard->deleteLater();
}
