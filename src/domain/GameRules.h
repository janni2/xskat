#ifndef GAMERULES_H
#define GAMERULES_H

#include "Card.h"
#include "GameState.h"
#include <vector>

namespace Domain {

class GameRules {
public:
    static int getCardValue(const Card& card);
    static bool isMoveValid(const Card& card, const std::vector<Card>& playerHand, const GameState& state);
    static int determineTrickWinner(const std::vector<Card>& trick, Suit trumpSuit);
    static int calculateGameValue(const GameState& state, const Player& player);
};

} // namespace Domain

#endif // GAMERULES_H