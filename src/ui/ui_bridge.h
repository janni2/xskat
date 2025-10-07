#ifndef UI_BRIDGE_H
#define UI_BRIDGE_H

// This header provides a C-compatible interface to the C++ GameController.
// It will be included by the C files in the ui directory.

#ifdef __cplusplus
extern "C" {
#endif

// Opaque pointer to the GameController instance
typedef struct GameController GameController;

// Represents the state of a single card for the UI
typedef struct {
    int suit; // 0-3 for Clubs, Spades, Hearts, Diamonds
    int rank; // 0-7 for 7, 8, 9, 10, J, Q, K, A
    int raw_value; // The original integer value from skat.h for compatibility
} UICard;

// A C-compatible struct to hold the game state for rendering
typedef struct {
    char player_names[3][20];
    UICard player_hands[3][10];
    UICard skat[2];
    UICard current_trick[3];
    int trick_size;
    int current_player_index;
    int game_phase; // Corresponds to the GamePhase enum
} UIGameState;


// --- Bridge API Functions ---

// Initializes the game controller and returns an opaque pointer to it.
GameController* create_game_controller();

// Destroys the game controller instance.
void destroy_game_controller(GameController* controller);

// Starts a new game.
void controller_start_new_game(GameController* controller);

// Gets the current game state for the UI to render.
void controller_get_ui_state(GameController* controller, UIGameState* ui_state);

// Informs the controller that a player has chosen a card.
void controller_play_card(GameController* controller, int player_index, int card_index_in_hand);


#ifdef __cplusplus
}
#endif

#endif // UI_BRIDGE_H