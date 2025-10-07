#include "Deck.h"
#include <algorithm>
#include <random>
#include <stdexcept>

namespace Domain {

Deck::Deck() {
    initialize();
}

void Deck::initialize() {
    cards.clear();
    for (int s = 0; s < 4; ++s) {
        for (int r = 0; r < 8; ++r) {
            cards.emplace_back(static_cast<Suit>(s), static_cast<Rank>(r));
        }
    }
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

std::vector<Card> Deck::deal(int numCards) {
    if (numCards > cards.size()) {
        throw std::out_of_range("Not enough cards in the deck to deal.");
    }
    std::vector<Card> dealtCards;
    for (int i = 0; i < numCards; ++i) {
        dealtCards.push_back(cards.back());
        cards.pop_back();
    }
    return dealtCards;
}

} // namespace Domain