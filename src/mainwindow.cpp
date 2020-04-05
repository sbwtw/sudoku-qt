#include "mainwindow.h"
#include "gameboard.h"
#include "highlightbuttongroup.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>

MainWindow::MainWindow()
    : QWidget(nullptr)
{

    _gameBoard = new GameBoard;
    _newGame = new QPushButton("New Game");
    _debugDump = new QPushButton("Dump");

    HighlightButtonGroup *highlightGroup = new HighlightButtonGroup;
    connect(highlightGroup, &HighlightButtonGroup::highlightRequest, _gameBoard, &GameBoard::setHighlight);

    QHBoxLayout *controlsLayout = new QHBoxLayout;
    controlsLayout->addWidget(highlightGroup);
    controlsLayout->addStretch();
    controlsLayout->addWidget(_newGame);
    controlsLayout->addWidget(_debugDump);

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addLayout(controlsLayout);
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
