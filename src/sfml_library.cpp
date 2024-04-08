/*
** EPITECH PROJECT, 2024
** snake game for sfml
** File description:
** arcade
*/

#include "snake_sfml.hpp"

SnakeGame::SnakeGame()
{
    if (!buffer1.loadFromFile("src/eating_apple.mp3")) {
        std::cerr << "Error: Fils don't exist" << std::endl;
    }
    if (!buffer2.loadFromFile("src/game_over.mp3")) {
        std::cerr << "Error: Fils don't exist" << std::endl;
    }
    createObjectList();
    direction_snake = sf::Vector2f(0, 0);
    gameOver = false;
    eatingSound.setBuffer(buffer1);
    game_over.setBuffer(buffer2);
}


void SnakeGame::update(sf::Keyboard::Key OldKey, sf::Keyboard::Key NewKey)
{
    if (OldKey == sf::Keyboard::Left && NewKey == sf::Keyboard::Right)
        return;
    if (OldKey == sf::Keyboard::Right && NewKey == sf::Keyboard::Left)
        return;
    if (OldKey == sf::Keyboard::Up && NewKey == sf::Keyboard::Down)
        return;
    if (OldKey == sf::Keyboard::Down && NewKey == sf::Keyboard::Up)
        return;
    if (NewKey == sf::Keyboard::Left && direction_snake != sf::Vector2f(1, 0))
        direction_snake = sf::Vector2f(-1, 0);
    else if (NewKey == sf::Keyboard::Right && direction_snake != sf::Vector2f(-1, 0))
        direction_snake = sf::Vector2f(1, 0);
    else if (NewKey == sf::Keyboard::Up && direction_snake != sf::Vector2f(0, 1))
        direction_snake = sf::Vector2f(0, -1);
    else if (NewKey == sf::Keyboard::Down && direction_snake != sf::Vector2f(0, -1))
        direction_snake = sf::Vector2f(0, 1);
}

unsigned int SnakeGame::getScore() const
{
}

bool SnakeGame::isGameOver() const
{
    return gameOver;
}

void SnakeGame::reset()
{
    gameOver = false;
    snakeBody.clear();
    direction_snake = sf::Vector2f(1, 0);
    createObjectList();
}

sf::Vector2f SnakeGame::getdirection_snake() const
{
    return direction_snake;
}

const std::vector<SnakePart>& SnakeGame::getObjectList() const
{
    return snakeBody;
}

void SnakeGame ::move()
{
    for (int i = snakeBody.size() - 1; i > 0; --i) {
        snakeBody[i].shape.setPosition(snakeBody[i - 1].shape.getPosition());
    }
    sf::Vector2f headPosition = snakeBody[0].shape.getPosition();
    sf::Vector2f newPosition = headPosition + direction_snake;
    snakeBody[0].shape.setPosition(newPosition);
}

void SnakeGame ::checkCollision(const sf::Vector2f& pointPosition, sf::CircleShape& apple)
{
    sf::Vector2f nextpos = snakeBody[0].shape.getPosition() + direction_snake;
    float collisionRadius = 15.0f;

    if (nextpos.x < 100 || nextpos.x > 700 || nextpos.y < 30 || nextpos.y > 530) {
        gameOver = true;
        std::cout << "You lose :(" << std::endl;
        return;
    }
    for (size_t i = 1; i < snakeBody.size(); ++i) {
        if (nextpos == snakeBody[i].shape.getPosition()) {
            gameOver = true;
            std::cout << "You lose :(" << std::endl;
            return;
        }
    }
    float distanceSquared = (nextpos.x - pointPosition.x) * (nextpos.x - pointPosition.x) + (nextpos.y - pointPosition.y) * (nextpos.y - pointPosition.y);
    float collision_point = collisionRadius * collisionRadius;
    if (distanceSquared <= collision_point) {
        sf::Vector2f postion_before = snakeBody.back().shape.getPosition();
        for (int i = 0; i < 25; ++i) {
            snakeBody.emplace_back(postion_before, sf::Color::Green);
        }
        eatingSound.play();
        sf::Vector2f newPosition = generatepoint();
        apple.setPosition(newPosition);
    }
}

void SnakeGame::createObjectList()
{
    sf::RectangleShape head;
    head.setSize(sf::Vector2f(20, 20));
    head.setPosition(400, 300);
    head.setFillColor(sf::Color::Green);
    snakeBody.emplace_back(head.getPosition(), sf::Color::Green);
}

SFMLLibrary::SFMLLibrary()
{
    lastKey = sf::Keyboard::Right;
    snakeSpeed = 0.01f;
}

void SFMLLibrary :: createWindow(const std::pair<unsigned int, unsigned int>& WindowSize)
{
    window.create(sf::VideoMode(WindowSize.first, WindowSize.second), "SFML ARCADE");
    border.setSize(sf::Vector2f(600, 500));
    border.setPosition(100, 30);
    border.setFillColor(sf::Color::White);
    border.setOutlineThickness(5);
    border.setOutlineColor(sf::Color::White);
    apple.setRadius(5);
    apple.setPosition(generatepoint());
    apple.setFillColor(sf::Color::Red);

    sf::Clock clock;

    while (window.isOpen() && !snakeGame.isGameOver()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
                else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape)
                        window.close();
                        else {
                            handleKeyPress(event.key.code);
                    }
                }
        }
        handleKeyPress(lastKey);

        if (!snakeGame.isGameOver()) {
            snakeGame.move();
            sf::Vector2f pointPosition = apple.getPosition();
            snakeGame.checkCollision(pointPosition, apple);
        }

        drawObject(window);
        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();
        if (deltaTime < snakeSpeed) {
            sf::sleep(sf::seconds(snakeSpeed - deltaTime));
        }
    }
}

void SFMLLibrary:: handleKeyPress(sf::Keyboard::Key key)
{
    sf::Keyboard::Key OldKey = lastKey;
    lastKey = key;
    if (OldKey != lastKey) {
        snakeGame.update(OldKey, lastKey);
    }
}

void  SFMLLibrary :: drawObject(sf::RenderWindow& window)
{
    window.clear();
    window.draw(border);
    window.draw(apple);
    for (const auto& part : snakeGame.getObjectList()) {
        window.draw(part.shape);
    }
    window.display();
}

sf::Vector2f SnakeGame :: generatepoint()
{
    float x = static_cast<float>(std::rand() % 601 + 100);
    float y = static_cast<float>(std::rand() % 501 + 30);
    return sf::Vector2f(x, y);
}

sf::Vector2f SFMLLibrary :: generatepoint()
{
    float x = static_cast<float>(std::rand() % 601 + 100);
    float y = static_cast<float>(std::rand() % 501 + 30);
    return sf::Vector2f(x, y);
}

extern "C" {
    void createWindow() {
        std::shared_ptr<SFMLLibrary> sfmlLibrary = std::make_shared<SFMLLibrary>();
        sfmlLibrary->createWindow(std::make_pair(800, 600));
    }
}
