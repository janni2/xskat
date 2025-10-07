#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../domain/GameState.h"
#include "../domain/Deck.h"
#include "../domain/Player.h"
#include <vector>
#include <memory>

namespace Application {

class GameController {
public:
    GameController();
    ~GameController();

    void initializeGame();
    void startGame();

    // Methods to be called by the UI
    void onCardPlayed(int playerIndex, const Domain::Card& card);
    const Domain::GameState& getGameState() const;

private:
    std::unique_ptr<Domain::GameState> gameState;
    std::unique_ptr<Domain::Deck> deck;
    std::vector<Domain::Player*> players; // Using raw pointers for now, will manage lifetime
};

} // namespace Application

#endif // GAMECONTROLLER_H