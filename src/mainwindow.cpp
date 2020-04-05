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
    _highLightGroup = new QButtonGroup(this);
    _highLightGroup->setExclusive(true);

    QHBoxLayout *highLightButtonsLayout = new QHBoxLayout;
    for (int i(1); i != 10; ++i)
    {
        QPushButton *b = new QPushButton(QString::number(i));
        b->setFixedSize(25, 25);
        b->setCheckable(true);

        _highLightGroup->addButton(b);
        highLightButtonsLayout->addWidget(b);
    }

    QHBoxLayout *controlsLayout = new QHBoxLayout;
    controlsLayout->addLayout(highLightButtonsLayout);
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
