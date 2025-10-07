#include "Player.h"

namespace Domain {

Player::Player(const std::string& name) : name(name) {}

const std::string& Player::getName() const {
    return name;
}

void Player::addCardsToHand(const std::vector<Card>& cards) {
    hand.insert(hand.end(), cards.begin(), cards.end());
}

const std::vector<Card>& Player::getHand() const {
    return hand;
}

} // namespace Domain