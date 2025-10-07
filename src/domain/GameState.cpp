#include "GameState.h"

namespace Domain {

GameState::GameState(const std::vector<Player*>& players)
    : phase(GamePhase::Dealing),
      players(players),
      currentPlayerIndex(0),
      trumpSuit(Suit::Clubs), // Default initialization
      trumpSuitIsSet(false),
      trickStarterIndex(0) {}

GamePhase GameState::getPhase() const {
    return phase;
}

const std::vector<Player*>& GameState::getPlayers() const {
    return players;
}

void GameState::setPhase(GamePhase newPhase) {
    phase = newPhase;
}

int GameState::getCurrentPlayerIndex() const {
    return currentPlayerIndex;
}

void GameState::nextPlayer() {
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
}

void GameState::setTrumpSuit(Suit suit) {
    trumpSuit = suit;
    trumpSuitIsSet = true;
}

void GameState::clearTrumpSuit() {
    trumpSuitIsSet = false;
}

bool GameState::hasTrumpSuit() const {
    return trumpSuitIsSet;
}

Suit GameState::getTrumpSuit() const {
    // It's the caller's responsibility to check hasTrumpSuit() first.
    return trumpSuit;
}

const std::vector<Card>& GameState::getCurrentTrick() const {
    return currentTrick;
}

void GameState::playCard(const Card& card) {
    if (currentTrick.empty()) {
        trickStarterIndex = currentPlayerIndex;
    }
    currentTrick.push_back(card);
}

void GameState::clearTrick() {
    currentTrick.clear();
    currentPlayerIndex = trickStarterIndex;
}

} // namespace Domain