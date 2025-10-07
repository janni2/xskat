#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include <vector>
#include <string>

namespace Domain {

class Player {
public:
    Player(const std::string& name);

    const std::string& getName() const;
    void addCardsToHand(const std::vector<Card>& cards);
    const std::vector<Card>& getHand() const;

protected:
    std::string name;
    std::vector<Card> hand;
};

} // namespace Domain

#endif // PLAYER_H