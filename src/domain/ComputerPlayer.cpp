#include "ComputerPlayer.h"
#include "GameRules.h"
#include <stdexcept>

namespace Domain {

ComputerPlayer::ComputerPlayer(const std::string& name) : Player(name) {}

// A simple AI: chooses the first valid card.
// The sophisticated logic from skat.c (e.g., make_best) will be ported later.
Card ComputerPlayer::chooseCard(const GameState& gameState) {
    for (const auto& card : hand) {
        if (GameRules::isMoveValid(card, hand, gameState)) {
            // In a real implementation, we would also remove the card from the hand here.
            // For now, we just return the chosen card.
            return card;
        }
    }

    // This should not happen in a valid game state.
    // If the player has cards, at least one should be playable.
    if (!hand.empty()) {
        return hand.front(); // Fallback to playing any card if logic fails.
    }

    throw std::runtime_error("ComputerPlayer has no cards to choose from.");
}

} // namespace Domain