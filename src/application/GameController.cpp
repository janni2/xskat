#include "GameController.h"
#include "../domain/ComputerPlayer.h"
#include <stdexcept>

namespace Application {

GameController::GameController() {
    // Player creation and memory management will be handled here.
    // For now, create the players for a standard game.
    players.push_back(new Domain::Player("Player 1")); // Human
    players.push_back(new Domain::ComputerPlayer("Player 2 (PC)"));
    players.push_back(new Domain::ComputerPlayer("Player 3 (PC)"));
}

GameController::~GameController() {
    // Clean up dynamically allocated players
    for (auto p : players) {
        delete p;
    }
    players.clear();
}

void GameController::initializeGame() {
    deck = std::make_unique<Domain::Deck>();
    deck->shuffle();

    // Deal cards to players
    for (auto& player : players) {
        player->addCardsToHand(deck->deal(10));
    }
    // Two cards go to the skat
    auto skat = deck->deal(2);

    gameState = std::make_unique<Domain::GameState>(players);
}

void GameController::startGame() {
    if (!gameState) {
        initializeGame();
    }
    gameState->setPhase(Domain::GamePhase::Bidding);
}

void GameController::onCardPlayed(int playerIndex, const Domain::Card& card) {
    if (!gameState || gameState->getPhase() != Domain::GamePhase::TrickTaking) {
        // Not in the right phase to play a card
        return;
    }
    if (playerIndex != gameState->getCurrentPlayerIndex()) {
        // Not this player's turn
        return;
    }

    // TODO: Validate move using GameRules

    gameState->playCard(card);

    // Check if the trick is over
    if (gameState->getCurrentTrick().size() == players.size()) {
        // TODO: Determine trick winner using GameRules, update scores, etc.
        gameState->clearTrick();
    } else {
        gameState->nextPlayer();
    }
}

const Domain::GameState& GameController::getGameState() const {
    if (!gameState) {
        throw std::runtime_error("Game state is not initialized.");
    }
    return *gameState;
}

} // namespace Application