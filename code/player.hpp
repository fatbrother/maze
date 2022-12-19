#include "context.hpp"

class Player
{
public:
    Player();
    int move(const std::vector<std::vector<char>> &map) const;
    void draw(sf::RenderWindow &window);
    void setPos(sf::Vector2i pos);
    sf::Vector2i getPos() const;

private:
    sf::Vector2i pos;
};

Player::Player()
{
    pos = sf::Vector2i(0, 0);
}

void Player::draw(sf::RenderWindow &window)
{
    sf::CircleShape player;
    player.setRadius(GRID_SIZE / 2);
    player.setFillColor(sf::Color::Green);
    player.setPosition(pos.x * GRID_SIZE, pos.y * GRID_SIZE);
    window.draw(player);
}

void Player::setPos(sf::Vector2i pos)
{
    this->pos = pos;
}

sf::Vector2i Player::getPos() const
{
    return pos;
}

int Player::move(const std::vector<std::vector<char>> &map) const
{
    // return UP, DOWN, LEFT, RIGHT or any other integer if no move
    // write a algorithm to determine the next move
    
    return -1;
}