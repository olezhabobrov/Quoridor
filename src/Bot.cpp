#include "Bot.h"

void Bot::play(Board &board) {
    Cell &cell = *board.players[1].currentPosition;
    cell.button->setText("");
    board.players[1].currentPosition = &board.cells[cell.y + 1][cell.x];
    board.players[1].currentPosition->setPlayerMark(true);
}