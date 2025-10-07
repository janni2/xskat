#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "Player.h"
#include "GameState.h"
#include <vector>

namespace Domain {

class ComputerPlayer : public Player {
public:
    ComputerPlayer(const std::string& name);

    // The core AI logic for choosing a card to play.
    // This will eventually encapsulate the logic from make_best() in skat.c
    Card chooseCard(const GameState& gameState);
};

} // namespace Domain

#endif // COMPUTERPLAYER_H