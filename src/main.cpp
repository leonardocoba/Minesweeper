#include "board.h"
int main(){
    //========================================Creating Window===============================//
    sf::RenderWindow window(sf::VideoMode(800, 600), "MineSweaper", sf::Style::Close);
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::Blue);
    rect.setSize(sf::Vector2f(800,600));
    rect.setPosition(400,300);
    rect.setOrigin(400,300);

    //======================================= Font set====================================//
    sf::Font font;
    font.loadFromFile("../files/font.ttf");
    sf::Text welcomeText("WELCOME TO MINESWEEPER!", font, 24);
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    sf::FloatRect textBounds = welcomeText.getLocalBounds();
    float welcomeX =  800/ 2.0f - textBounds.width / 2.0f;
    float welcomeY = 600/ 2.0f - textBounds.height / 2.0f -150 ;
    welcomeText.setPosition(welcomeX, welcomeY);

    sf::Text enterNameText("Enter your name", font, 20);
    enterNameText.setStyle(sf::Text::Bold);
    sf::FloatRect textBounds2 =enterNameText.getLocalBounds();
    float enterX =  800/ 2.0f - textBounds2.width / 2.0f;
    float enterY = 600/ 2.0f - textBounds2.height / 2.0f -75 ;
    enterNameText.setPosition(enterX, enterY);

    sf::Text inputText("|", font, 18);
    inputText.setFillColor(sf::Color::Yellow);
    sf::FloatRect textBounds3 = welcomeText.getLocalBounds();
    float inputX =  800/ 2.0f;
    float inputY = 600/ 2.0f - textBounds3.height / 2.0f -45 ;
    inputText.setPosition(inputX,inputY);

    sf::Event event;
    string name;


    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Enter && name.size() >0) {
                        window.close();
                    }
                    break;

                case sf::Event::Closed:
                    window.close();
                    return 0;
                    break;

                case sf::Event::TextEntered:
                    if (event.text.unicode < 128 && isalpha(event.text.unicode)) {
                        if (name.size() < 10) {
                            if (name.empty()) {
                                // Make the first character uppercase
                                name += toupper(static_cast<char>(event.text.unicode));
                            } else {
                                // Make the rest lowercase
                                name += tolower(static_cast<char>(event.text.unicode));
                            }
                            inputText.setString(name + "|");
                            sf::FloatRect textBounds3 = inputText.getLocalBounds();
                            float newInputX =  800/ 2.0f - textBounds3.width / 2.0f;
                            inputText.setPosition(newInputX,inputY);

                        }
                    }
                    else if (event.text.unicode == 8 && name.size() > 0) {
                        name.pop_back();
                        inputText.setString(name + "|");
                        sf::FloatRect textBounds3 = inputText.getLocalBounds();
                        float newInputX =  800/ 2.0f - textBounds3.width / 2.0f;
                        inputText.setPosition(newInputX,inputY);

                    }
                    break;

            }

        }
        window.clear();
        window.draw(rect);
        window.draw(welcomeText);
        window.draw(enterNameText);
        window.draw(inputText);
        window.display();
    }
    cout << name << endl;
    (BoardWindow(name));


        return 0;
    }