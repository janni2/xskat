#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Card.h"
#include "Player.h"
#include <vector>

// Removed <optional> to fix build error

namespace Domain {

enum class GamePhase {
    Dealing,
    Bidding,
    TrickTaking,
    GameOver
};

class GameState {
public:
    GameState(const std::vector<Player*>& players);

    GamePhase getPhase() const;
    void setPhase(GamePhase newPhase);

    const std::vector<Player*>& getPlayers() const;
    int getCurrentPlayerIndex() const;
    void nextPlayer();

    void setTrumpSuit(Suit suit);
    void clearTrumpSuit();
    bool hasTrumpSuit() const;
    Suit getTrumpSuit() const;

    const std::vector<Card>& getCurrentTrick() const;
    void playCard(const Card& card);
    void clearTrick();

private:
    GamePhase phase;
    std::vector<Player*> players;
    int currentPlayerIndex;
    Suit trumpSuit;
    bool trumpSuitIsSet;
    std::vector<Card> currentTrick;
    int trickStarterIndex;
};

} // namespace Domain

#endif // GAMESTATE_H