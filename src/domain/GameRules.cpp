#include "GameRules.h"
#include <numeric>
#include <algorithm>

namespace Domain {

// Mapping card ranks to their point values, similar to cardw[] in skat.c
int GameRules::getCardValue(const Card& card) {
    switch (card.getRank()) {
        case Rank::Ace:   return 11;
        case Rank::Ten:   return 10;
        case Rank::King:  return 4;
        case Rank::Queen: return 3;
        case Rank::Jack:  return 2;
        case Rank::Nine:
        case Rank::Eight:
        case Rank::Seven:
        default:          return 0;
    }
}

// Determines if a card is higher than another in a given context (trick)
// This logic is adapted from the higher() function in skat.c
bool is_higher(const Card& c1, const Card& c2, Suit trumpSuit) {
    bool c1IsTrump = (c1.getRank() == Rank::Jack) || (c1.getSuit() == trumpSuit);
    bool c2IsTrump = (c2.getRank() == Rank::Jack) || (c2.getSuit() == trumpSuit);

    if (c1IsTrump && !c2IsTrump) return true;
    if (!c1IsTrump && c2IsTrump) return false;

    // Both are trump or both are not trump
    if (c1IsTrump) { // Both are trumps
        if (c1.getRank() == Rank::Jack && c2.getRank() == Rank::Jack) {
            // Compare Jacks: Clubs > Spades > Hearts > Diamonds
            return static_cast<int>(c1.getSuit()) < static_cast<int>(c2.getSuit());
        }
        if (c1.getRank() == Rank::Jack) return true;
        if (c2.getRank() == Rank::Jack) return false;
        // Both are trump suit, compare rank
        return static_cast<int>(c1.getRank()) > static_cast<int>(c2.getRank());
    } else { // Both are non-trump
        if (c1.getSuit() != c2.getSuit()) {
            return false; // Not the same suit, c1 cannot be higher unless it's the leading suit
        }
        // Same suit, compare rank
        return static_cast<int>(c1.getRank()) > static_cast<int>(c2.getRank());
    }
}

// Determines the winner of a trick based on the trump suit.
// The winner is the player who played the highest card.
// The index returned is relative to the start of the trick (0, 1, or 2).
int GameRules::determineTrickWinner(const std::vector<Card>& trick, Suit trumpSuit) {
    if (trick.empty()) {
        return -1; // No winner
    }

    int winnerIndex = 0;
    for (size_t i = 1; i < trick.size(); ++i) {
        if (is_higher(trick[i], trick[winnerIndex], trumpSuit)) {
            winnerIndex = i;
        }
    }
    return winnerIndex;
}


// A simplified version of move validation logic from calc_poss() in skat.c
bool GameRules::isMoveValid(const Card& card, const std::vector<Card>& playerHand, const GameState& state) {
    const auto& trick = state.getCurrentTrick();
    if (trick.empty()) {
        return true; // Any card can be played to start a trick
    }

    const Card& leadCard = trick.front();
    bool isTrumpGame = state.hasTrumpSuit();
    Suit trumpSuit = isTrumpGame ? state.getTrumpSuit() : Suit::Clubs; // Dummy suit for non-trump games

    bool cardIsTrump = (card.getRank() == Rank::Jack) || (isTrumpGame && card.getSuit() == trumpSuit);
    bool leadCardIsTrump = (leadCard.getRank() == Rank::Jack) || (isTrumpGame && leadCard.getSuit() == trumpSuit);

    // Must follow suit if possible
    if (leadCardIsTrump) {
        bool hasTrump = std::any_of(playerHand.begin(), playerHand.end(), [&](const Card& c) {
            return (c.getRank() == Rank::Jack) || (isTrumpGame && c.getSuit() == trumpSuit);
        });
        if (hasTrump) {
            return cardIsTrump;
        }
    } else { // Lead card is a plain suit
        Suit leadSuit = leadCard.getSuit();
        bool hasLeadSuit = std::any_of(playerHand.begin(), playerHand.end(), [&](const Card& c) {
            return c.getSuit() == leadSuit && c.getRank() != Rank::Jack;
        });
        if (hasLeadSuit) {
            return card.getSuit() == leadSuit && !cardIsTrump;
        }
    }

    return true; // If player cannot follow suit, any card is valid
}

// Dummy implementation for now. Real calculation is complex.
// Logic from calc_result() in skat.c needs to be ported here.
int GameRules::calculateGameValue(const GameState& state, const Player& player) {
    // This is a placeholder. The actual calculation is highly complex,
    // involving bids, Schneider, Schwarz, Ouvert, etc.
    return 61;
}


} // namespace Domain