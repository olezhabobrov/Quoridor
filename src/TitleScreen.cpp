#include "TitleScreen.h"
#include "Controller.h"
#include "ui_TitleScreen.h"
#include <QDesktopServices>
#include <QUrl>


TitleScreen::TitleScreen(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::TitleScreen) {
    ui->setupUi(this);
    setConnections();
}

TitleScreen::~TitleScreen() {
    delete ui;
}

void TitleScreen::setConnections() {
    connect(ui->Button1Player, &QPushButton::clicked, [=] { start_1player_game(); });
    connect(ui->Button2Players, &QPushButton::clicked, [=] { start_2players_game(); });
    connect(ui->info, &QPushButton::clicked, [=] {
        QString link = "https://github.com/olezhabobrov/Quoridor";
        QDesktopServices::openUrl(QUrl(link));
    });
    connect(ui->quit, &QPushButton::clicked, [=] { close(); });
}

void TitleScreen::start_2players_game() {
    this->hide();
    Controller controller;
    this->show();
}


void TitleScreen::start_1player_game() {
    this->hide();
    Controller controller(nullptr, true);
    this->show();
}
