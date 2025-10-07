#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>
#include <memory>

namespace Domain {

class Deck {
public:
    Deck();

    void shuffle();
    std::vector<Card> deal(int numCards);

private:
    void initialize();
    std::vector<Card> cards;
};

} // namespace Domain

#endif // DECK_H