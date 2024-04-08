/*
** EPITECH PROJECT, 2024
** snake game for sfml
** File description:
** snake sfml hpp
*/

#ifndef SNAKE_SFML_HPP_
#define SNAKE_SFML_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
// #include "../../Interface.hpp"

class SnakePart
{
public:
    sf::RectangleShape shape;
    SnakePart(const sf::Vector2f& position, const sf::Color& color) {
        shape.setSize(sf::Vector2f(20, 20));
        shape.setPosition(position);
        shape.setFillColor(color);
    }
};

class SnakeGame {
private:
    std::vector<SnakePart> snakeBody;
    sf::Vector2f direction_snake;
    bool gameOver;
    sf::SoundBuffer buffer1;
    sf::Sound eatingSound;
    sf::SoundBuffer buffer2;
    sf::Sound game_over;
    void createObjectList();


public:
    SnakeGame();
    sf::Vector2f generatepoint();
    void update(sf::Keyboard::Key OldKey, sf::Keyboard::Key NewKey);
    unsigned int getScore() const;
    bool isGameOver() const;
    void reset();
    sf::Vector2f getdirection_snake() const;
    const std::vector<SnakePart>& getObjectList() const;
    void move();
    void checkCollision(const sf::Vector2f& pointPosition, sf::CircleShape& apple);

};

class SFMLLibrary {
private:
    sf::RenderWindow window;
    float snakeSpeed;
    sf::RectangleShape border;
    sf::CircleShape apple;
    sf::Keyboard::Key lastKey;
    SnakeGame snakeGame;
    sf::Vector2f generatepoint();

public:
    SFMLLibrary();
    void createWindow(const std::pair<unsigned int, unsigned int>& WindowSize);
    void handleKeyPress(sf::Keyboard::Key key);
    void drawObject(sf::RenderWindow& window);

};

#endif /* SNAKE_SFML_HPP_ */
