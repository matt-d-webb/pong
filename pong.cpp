#include <SFML/Graphics.hpp>
#include <iostream>

const int windowWidth = 800;
const int windowHeight = 600;
const float paddleWidth = 15.f;
const float paddleHeight = 80.f;
const float ballSize = 15.f;
const float paddleSpeed = 300.f;
const float ballSpeed = 200.f;

void resetGame(sf::RectangleShape &leftPaddle, sf::RectangleShape &rightPaddle, sf::CircleShape &ball, sf::Vector2f &ballVelocity)
{
    leftPaddle.setPosition(10, windowHeight / 2 - paddleHeight / 2);
    rightPaddle.setPosition(windowWidth - 10 - paddleWidth, windowHeight / 2 - paddleHeight / 2);
    ball.setPosition(windowWidth / 2 - ballSize / 2, windowHeight / 2 - ballSize / 2);
    ballVelocity = sf::Vector2f(-ballSpeed, ballSpeed);
}

int main()
{

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Pong Game");
    window.setVerticalSyncEnabled(true);

    sf::RectangleShape leftPaddle(sf::Vector2f(paddleWidth, paddleHeight));
    sf::RectangleShape rightPaddle(sf::Vector2f(paddleWidth, paddleHeight));
    sf::CircleShape ball(ballSize);

    sf::Vector2f ballVelocity(-ballSpeed, ballSpeed);

    resetGame(leftPaddle, rightPaddle, ball, ballVelocity);

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
            {
                resetGame(leftPaddle, rightPaddle, ball, ballVelocity);
            }
        }

        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && leftPaddle.getPosition().y > 0)
        {
            leftPaddle.move(0, -paddleSpeed * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && leftPaddle.getPosition().y + paddleHeight < windowHeight)
        {
            leftPaddle.move(0, paddleSpeed * deltaTime);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rightPaddle.getPosition().y > 0)
        {
            rightPaddle.move(0, -paddleSpeed * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rightPaddle.getPosition().y + paddleHeight < windowHeight)
        {
            rightPaddle.move(0, paddleSpeed * deltaTime);
        }

        ball.move(ballVelocity * deltaTime);

        if (ball.getPosition().y <= 0 || ball.getPosition().y + ballSize >= windowHeight)
        {
            ballVelocity.y = -ballVelocity.y;
        }
        if (ball.getGlobalBounds().intersects(leftPaddle.getGlobalBounds()) || ball.getGlobalBounds().intersects(rightPaddle.getGlobalBounds()))
        {
            ballVelocity.x = -ballVelocity.x;
        }

        window.clear();
        window.draw(leftPaddle);
        window.draw(rightPaddle);
        window.draw(ball);
        window.display();
    }

    return 0;
}
