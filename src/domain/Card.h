#ifndef CARD_H
#define CARD_H

namespace Domain {

enum class Suit {
    Clubs,
    Spades,
    Hearts,
    Diamonds
};

enum class Rank {
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace
};

class Card {
public:
    Card(Suit suit, Rank rank);

    Suit getSuit() const;
    Rank getRank() const;

private:
    Suit suit;
    Rank rank;
};

} // namespace Domain

#endif // CARD_H