#include "ui_bridge.h"
#include "../application/GameController.h"
#include "../domain/Card.h"
#include "../domain/Player.h"
#include "../domain/GameState.h"
#include <cstring>

// Define the opaque struct to be a wrapper around the C++ class
struct GameController {
    Application::GameController* cpp_controller;
};

// Helper function to convert from domain Card to UI Card
static void to_ui_card(const Domain::Card& domain_card, UICard* ui_card) {
    ui_card->suit = static_cast<int>(domain_card.getSuit());
    ui_card->rank = static_cast<int>(domain_card.getRank());
    // The raw_value can be reconstructed if needed, e.g., (suit << 3) | rank
    // For now, we'll just use suit and rank.
    ui_card->raw_value = (ui_card->suit << 3) | ui_card->rank;
}

extern "C" {

GameController* create_game_controller() {
    GameController* c_controller = new GameController;
    c_controller->cpp_controller = new Application::GameController();
    return c_controller;
}

void destroy_game_controller(GameController* controller) {
    if (controller) {
        delete controller->cpp_controller;
        delete controller;
    }
}

void controller_start_new_game(GameController* controller) {
    if (controller && controller->cpp_controller) {
        controller->cpp_controller->initializeGame();
        controller->cpp_controller->startGame();
    }
}

void controller_get_ui_state(GameController* controller, UIGameState* ui_state) {
    if (!controller || !controller->cpp_controller || !ui_state) {
        return;
    }

    const auto& game_state = controller->cpp_controller->getGameState();

    // Copy player names and hands
    const auto& players = game_state.getPlayers(); // Assuming GameState has getPlayers()
    for (size_t i = 0; i < 3; ++i) {
        strncpy(ui_state->player_names[i], players[i]->getName().c_str(), 19);
        ui_state->player_names[i][19] = '\0';

        const auto& hand = players[i]->getHand();
        for (size_t j = 0; j < hand.size() && j < 10; ++j) {
            to_ui_card(hand[j], &ui_state->player_hands[i][j]);
        }
    }

    // Copy current trick
    const auto& trick = game_state.getCurrentTrick();
    ui_state->trick_size = trick.size();
    for(size_t i = 0; i < trick.size() && i < 3; ++i) {
        to_ui_card(trick[i], &ui_state->current_trick[i]);
    }

    // Copy game phase and current player
    ui_state->game_phase = static_cast<int>(game_state.getPhase());
    ui_state->current_player_index = game_state.getCurrentPlayerIndex();

    // Skat is not yet handled in the new domain, so we leave it empty
    // to_ui_card(skat_card_1, &ui_state->skat[0]);
    // to_ui_card(skat_card_2, &ui_state->skat[1]);
}

void controller_play_card(GameController* controller, int player_index, int card_index_in_hand) {
    if (!controller || !controller->cpp_controller) {
        return;
    }

    const auto& game_state = controller->cpp_controller->getGameState();
    const auto& players = game_state.getPlayers();

    if (player_index < 0 || player_index >= players.size()) return;

    const auto& hand = players[player_index]->getHand();
    if (card_index_in_hand < 0 || card_index_in_hand >= hand.size()) return;

    const Domain::Card& card_to_play = hand[card_index_in_hand];

    controller->cpp_controller->onCardPlayed(player_index, card_to_play);
}

} // extern "C"