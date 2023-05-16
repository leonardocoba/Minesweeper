
#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H
#include <SFML/Graphics.hpp>
using namespace std;
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
class Board {
private:
    vector<vector<int>> board;
    int numMines;
    int rows;
    int columns;
public:
    Board() {
        fstream inFile("../files/board_config.cfg", ios_base::in);
        if (!inFile.is_open()) {
            cout << "Error opening file" << endl;
        }
        int numRows, numColumns, numMines;
        inFile >> numColumns >> numRows >> numMines;

        this->numMines = numMines;
        this->rows = numRows;
        this->columns = numColumns;
        this->board = vector<vector<int>>(rows, vector<int>(columns));
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = 0;
            }
        }
        GenerateMines();
        GenerateNums();
    }
    void GenerateMines() {
        int numMinesPlaced = 0;
        while (numMinesPlaced < numMines) {
            int row = rand() % rows;
            int col = rand() % columns;
            if (board[row][col] != -1) {
                board[row][col] = -1;
                numMinesPlaced++;
            }
        }
    }
    void GenerateNums() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (board[i][j] == -1) {
                    continue;
                }
                int num_bombs = 0;
                for (int r = max(i-1, 0); r <= min(i+1, rows-1); r++) {
                    for (int c = max(j-1, 0); c <= min(j+1, columns-1); c++) {
                        if (board[r][c] == -1) {
                            num_bombs++;
                        }
                    }
                }
                board[i][j] = num_bombs;
            }
        }
    }
    void DisplayBoard() {
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                cout << this->board[i][j] << " ";
            }
            cout << endl;
        }
    }
    int ReturnInt(int x, int y){
        return board[x][y];
    }
    void ResetBoard(){
        this->board = vector<vector<int>>(this->rows, vector<int>(this->columns));
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = 0;
            }
        }
        GenerateMines();
        GenerateNums();

    }
    int ReturnNumMines(){
        return this->numMines;
    }

};
class BoardWindow {
public:
    BoardWindow(string name) {
        srand(time(NULL));
        Board myboard = Board();
        myboard.DisplayBoard();

        //===========================Board/Game Window Initializer ===================================//
        fstream inFile("../files/board_config.cfg", ios_base::in);
        if (!inFile.is_open()) {
            cout << "Error opening file" << endl;
        }
        int numColumns, numRows, numMines;
        inFile >> numColumns >> numRows >> numMines;
        int width = numColumns * 32;
        int height = (numRows * 32) + 100;
        sf::RenderWindow gameWindow(sf::VideoMode(width, height), "MineSweeper", sf::Style::Close);
        sf::RectangleShape rect;

        rect.setFillColor(sf::Color::White);
        rect.setSize(sf::Vector2f(width, 100));
        rect.setPosition(width, height);
        rect.setOrigin(width, 100);

        //=============================== HappyFace/LoseFace/WinFace =================================//
        sf::Texture happyFaceT;
        happyFaceT.loadFromFile("../files/images/face_happy.png");
        sf::Sprite happyFace;
        happyFace.setTexture(happyFaceT);
        happyFace.setPosition((numColumns / 2.0 * 32) - 32, 32 * (numRows + 0.5f));
        sf::FloatRect happyFaceBounds = happyFace.getGlobalBounds();
        int maxX = ((numColumns / 2.0 * 32) - 32);
        int maxY = 32 * (numRows + 0.5f);

        sf::Texture loseFaceT;
        loseFaceT.loadFromFile("../files/images/face_lose.png");
        sf::Sprite loseFace;
        loseFace.setTexture(loseFaceT);
        loseFace.setPosition((numColumns / 2.0 * 32) - 32, 32 * (numRows + 0.5f));

        sf::Texture winFaceT;
        winFaceT.loadFromFile("../files/images/face_win.png");
        sf::Sprite winFace;
        winFace.setTexture(winFaceT);
        winFace.setPosition((numColumns / 2.0 * 32) - 32, 32 * (numRows + 0.5f));


        //=============================== Debug/ Pause/ Play/ Leader buttons ==============================//
        sf::Texture debugButtonT;
        debugButtonT.loadFromFile("../files/images/debug.png");
        sf::Sprite debugButton;
        debugButton.setTexture(debugButtonT);
        debugButton.setPosition((numColumns * 32) - 304, 32 * (numRows + .5f));
        sf::FloatRect debugBounds = debugButton.getGlobalBounds();
        int maxX3 = (numColumns * 32) - 304;
        int maxY3 = 32 * (numRows + .5f);

        sf::Texture pauseButtonT;
        pauseButtonT.loadFromFile("../files/images/pause.png");
        sf::Sprite pauseButton;
        pauseButton.setTexture(pauseButtonT);
        pauseButton.setPosition((numColumns * 32) - 240, 32 * (numRows + .5f));
        sf::FloatRect pauseBounds = pauseButton.getGlobalBounds();
        int maxX4 = (numColumns * 32) - 240;
        int maxY4 = 32 * (numRows + .5f);

        sf::Texture playButtonT;
        playButtonT.loadFromFile("../files/images/play.png");
        sf::Sprite playButton;
        playButton.setTexture(playButtonT);
        playButton.setPosition((numColumns * 32) - 240, 32 * (numRows + .5f));


        sf::Texture leaderButtonT;
        leaderButtonT.loadFromFile("../files/images/leaderboard.png");
        sf::Sprite leaderButton;
        leaderButton.setTexture(leaderButtonT);
        leaderButton.setPosition((numColumns * 32) - 176, 32 * (numRows + .5f));
        sf::FloatRect leaderButtonBounds = leaderButton.getGlobalBounds();
        int maxX2 = (numColumns * 32) - 176;
        int maxY2 = 32 * (numRows + .5f);

        //====================================== Hidden Tiles/ Revealed Tiles / Mines /Revealed Nums/ Flag / Digits =====================//
        sf::Texture hiddenTile;
        hiddenTile.loadFromFile("../files/images/tile_hidden.png");
        vector<sf::Sprite> tiles(numRows * numColumns);
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numColumns; j++) {
                int index = i * numColumns + j;
                sf::Sprite &tileHidden = tiles[index];
                tileHidden.setTexture(hiddenTile);
                tileHidden.setPosition(j * 32, i * 32);
            }
        }
        sf::Texture revealedTile;
        revealedTile.loadFromFile("../files/images/tile_revealed.png");
        vector<sf::Sprite> revealedTiles;

        sf::Texture minesTexture;
        minesTexture.loadFromFile("../files/images/mine.png");
        vector<sf::Sprite> revealedMines;

        vector<sf::Sprite> revealedNums;
        sf::Texture numTexture;
        vector<sf::Texture> numTextures;
        for (int i = 1; i < 9; i++) {
            sf::Texture texture;
            texture.loadFromFile("../files/images/number_" + to_string(i) + ".png");
            numTextures.push_back(texture);
        }

        sf::Texture flagTexture;
        flagTexture.loadFromFile("../files/images/flag.png");
        vector<sf::Sprite> flags;

        sf::Texture digitsTexture;
        digitsTexture.loadFromFile("../files/images/digits.png");
        vector<sf::Texture> digitTextures;
        for (int i = 0; i < 11; i++) {
            sf::IntRect rect(21 * i, 0, 21, 32);
            sf::Texture texture;
            texture.loadFromImage(digitsTexture.copyToImage(), rect);
            digitTextures.push_back(texture);
        }


        // ========================= Timer and Counter =================================//
        vector<sf::Sprite> mineCounter;

        sf::Clock timer;
        sf::Time elapsedTime;
        sf::Time pausedTime = sf::Time::Zero;
        sf::Clock pausedTimer;
        vector<sf::Sprite> timerDigits;


        //========================Cords, Bools, and Etc. =========================//
        vector<sf::Sprite> tempRevealed;
        int totalNonMines = (numColumns * numRows) - myboard.ReturnNumMines();

        vector<pair<int, int>> revealedTilesCoords;
        bool gameLose = false;
        bool gameWin = false;
        bool debugPressed = false;
        bool gamePaused = false;
        int minutes;
        int seconds;


        while (gameWindow.isOpen()) {
            sf::Event event;
            while (gameWindow.pollEvent(event)) {
                switch (event.type) {

                    case sf::Event::Closed:
                        gameWindow.close();
                        break;
                    case sf::Event::MouseButtonPressed:
                        //==========================If its a left click=======================//
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            cout << "mouse x: " << event.mouseButton.x << endl;
                            cout << "mouse y: " << event.mouseButton.y << endl;
                            if (event.mouseButton.x <= width && event.mouseButton.y <= height - 100 &&
                            gamePaused !=true && gameLose != true && gameWin !=true  ) {
                                cout << width << " " << height << endl;
                                int row = floor(event.mouseButton.y / 32);
                                int col = floor(event.mouseButton.x / 32);
                                bool alreadyFlagged = false;
                                for (int i = 0; i < flags.size(); i++) {
                                    sf::Sprite &flag = flags[i];
                                    if (flag.getPosition() == sf::Vector2f(col * 32, row * 32)) {
                                        alreadyFlagged = true;
                                    }
                                }
                                //=========================== If its an empty cell================//
                                if (myboard.ReturnInt(row, col) == 0 && !alreadyFlagged) {
                                    revealAdjacentTiles(row, col, numRows, numColumns, revealedTile, revealedTiles,
                                                        revealedTilesCoords, myboard, revealedNums, numTextures, flags);

                                }
                                // ====================== If tile is a bomb======================//
                                else if (myboard.ReturnInt(row, col) == -1 && !alreadyFlagged) {
                                    for (int i = 0; i <numRows; i++) {
                                        for (int j = 0; j < numColumns; j++) {
                                            if (myboard.ReturnInt(i, j)== -1) {
                                                sf::Sprite newTileRevealed(revealedTile);
                                                newTileRevealed.setPosition(j * 32, i * 32);
                                                revealedTiles.push_back(newTileRevealed);

                                                sf::Sprite revealedMine(minesTexture);
                                                revealedMine.setPosition(j * 32, i * 32);
                                                revealedMines.push_back(revealedMine);
                                            }

                                        }
                                    }
                                    gameLose = true;
                                    gamePaused = true;
                                }
                                //=======================If tile is a number ====================//
                                else if (!alreadyFlagged){
                                    sf::Sprite newTileRevealed(revealedTile);
                                    newTileRevealed.setPosition(col * 32, row * 32);
                                    revealedTiles.push_back(newTileRevealed);
                                    revealedTilesCoords.push_back(make_pair(row, col));

                                    int x = myboard.ReturnInt(row, col);
                                    string num = to_string(x);
                                    sf::Sprite revealedNum(numTextures[x - 1]);
                                    revealedNum.setPosition(col * 32, row * 32);
                                    revealedNums.push_back(revealedNum);
                                }
                                //=========================Checking if all tiles have been revealed=============//
                                if ( revealedTilesCoords.size() == totalNonMines){
                                    gameWin = true;
                                    gamePaused = true;
                                    flags.clear();
                                    for (int i = 0; i < numRows; i++){
                                        for(int j = 0; j < numColumns; j++){
                                            if (myboard.ReturnInt(i, j) == -1){
                                                sf::Sprite flagSprite(flagTexture);
                                                flagSprite.setPosition(j * 32, i * 32);
                                                flags.push_back(flagSprite);
                                            }

                                        }

                                    }
                                    LeaderBoardUpdate(minutes, seconds, name);
                                    LeaderBoard(numColumns, numRows);

                                }
                                break;
                            }
//================================ If happy face is clicked =========================================================//
                            if (event.mouseButton.x >= maxX && event.mouseButton.x <= maxX + happyFaceBounds.width &&
                                event.mouseButton.y >= maxY && event.mouseButton.y <= maxY + happyFaceBounds.height) {
                                // reset the board
                                myboard.ResetBoard();

                                // remove all revealed tiles
                                revealedTiles.clear();
                                revealedTilesCoords.clear();
                                revealedMines.clear();
                                revealedNums.clear();
                                mineCounter.clear();
                                pausedTime = sf::Time::Zero;
                                pausedTimer.restart();
                                timer.restart();

                                // add all hidden tiles
                                for (int i = 0; i < numRows; i++) {
                                    for (int j = 0; j < numColumns; j++) {
                                        if (myboard.ReturnInt(i, j) != -1) {
                                            sf::Sprite hiddenTileSprite(hiddenTile);
                                            hiddenTileSprite.setPosition(j * 32, i * 32);
                                            tiles.push_back(hiddenTileSprite);
                                        }
                                    }
                                }
                                // remove all flags
                                flags.clear();
                                gameLose = false;

                                gameWin = false;
                                gamePaused =false;

                                break;
                            }
                            //=================If debug button has been pressed============================//
                            if (event.mouseButton.x >= maxX3 && event.mouseButton.x <= maxX3 + debugBounds.width &&
                                   event.mouseButton.y >= maxY3 && event.mouseButton.y <= maxY3 + debugBounds.height && gamePaused != true) {
                                    if (gameWin != true && gameLose != true && debugPressed != true) {
                                        for (int i = 0; i < numRows; i++) {
                                            for (int j = 0; j < numColumns; j++) {
                                                if (myboard.ReturnInt(i, j) == -1) {
                                                    sf::Sprite newTileRevealed(revealedTile);
                                                    newTileRevealed.setPosition(j * 32, i * 32);
                                                    revealedTiles.push_back(newTileRevealed);

                                                    sf::Sprite revealedMine(minesTexture);
                                                    revealedMine.setPosition(j * 32, i * 32);
                                                    revealedMines.push_back(revealedMine);

                                                }

                                            }
                                        }
                                        debugPressed = true;
                                    }
                                    else if (gameWin != true && gameLose != true && debugPressed == true ){
                                        revealedTiles.clear();
                                        revealedTilesCoords.clear();
                                        revealedMines.clear();
                                        revealedNums.clear();

                                        // add all hidden tiles
                                        for (int i = 0; i < numRows; i++) {
                                            for (int j = 0; j < numColumns; j++) {
                                                if (myboard.ReturnInt(i, j) != -1) {
                                                    sf::Sprite hiddenTileSprite(hiddenTile);
                                                    hiddenTileSprite.setPosition(j * 32, i * 32);
                                                    tiles.push_back(hiddenTileSprite);
                                                }
                                            }
                                        }
                                        debugPressed = false;
                                    }
                                break;
                            }
                            //=====================If leader board button is pressed==============================//
                            if (event.mouseButton.x >= maxX2 && event.mouseButton.x <= maxX2 + leaderButtonBounds.width &&
                                event.mouseButton.y >= maxY2 && event.mouseButton.y <= maxY2 + leaderButtonBounds.height) {

                                LeaderBoard(numColumns, numRows);
                                break;
                            }
                            //====================If paused button is pressed=======================================//
                            if (event.mouseButton.x >= maxX4 && event.mouseButton.x <= maxX4 + pauseBounds.width &&
                                event.mouseButton.y >= maxY4 && event.mouseButton.y <= maxY4 + pauseBounds.height
                                && gameWin != true && gameLose != true) {
                                if(gamePaused != true) {
                                    pausedTimer.restart();
                                    for (int i = 0; i < numRows; i++) {
                                        for (int j = 0; j < numColumns; j++) {
                                            sf::Sprite temp(revealedTile);
                                            temp.setPosition(j * 32, i * 32);
                                            tempRevealed.push_back(temp);
                                            gamePaused = true;
                                        }
                                    }
                                }

                                else{
                                    pausedTime += pausedTimer.getElapsedTime();
                                    tempRevealed.clear();
                                    gamePaused = false;
                                }
                                break;
                            }
                        }
                        //===========================If its a right click=======================//
                        if (event.mouseButton.button == sf::Mouse::Right) {
                            //========================== Placing a flag==========================//
                            if (event.mouseButton.x <= width && (event.mouseButton.y) <= height) {
                                int row = floor(event.mouseButton.y / 32);
                                int col = floor(event.mouseButton.x / 32);
                                bool alreadyRevealed = false;
                                for (const auto &coords: revealedTilesCoords) {
                                    if (coords.first == row && coords.second == col) {
                                        alreadyRevealed = true;
                                        break;
                                    }
                                }
                                if (!alreadyRevealed) {
                                    bool alreadyFlagged = false;
                                    int indexToRemove = -1;
                                    for (int i = 0; i < flags.size(); i++) {
                                        sf::Sprite &flag = flags[i];
                                        if (flag.getPosition() == sf::Vector2f(col * 32, row * 32)) {
                                            alreadyFlagged = true;
                                            indexToRemove = i;
                                            break;
                                        }
                                    }
                                    if (alreadyFlagged) {
                                        flags.erase(flags.begin() + indexToRemove);
                                    } else {
                                        sf::Sprite flagSprite(flagTexture);
                                        flagSprite.setPosition(col * 32, row * 32);
                                        flags.push_back(flagSprite);
                                    }

                                }
                            }
                            break;
                        }
                }
            }
//================Second clock for checking paused time===========================//
            if (!gamePaused) {
                elapsedTime = timer.getElapsedTime() - pausedTime;

            }
//==========================Timer sprites===================================//
            int totalSeconds = elapsedTime.asSeconds();
            minutes = totalSeconds / 60;
            seconds = totalSeconds % 60;
            int minutesFirst = minutes / 10;
            int minutesSecond = minutes % 10;
            int secondsFirst = seconds / 10;
            int secondsSecond = seconds % 10;

            timerDigits.clear();

            sf::Sprite minuteFirst(digitTextures[minutesFirst]);
            minuteFirst.setPosition((numColumns * 32) - 97, 32 * ((numRows) + 0.5f) + 16);
            timerDigits.push_back(minuteFirst);

            sf::Sprite minuteSecond(digitTextures[minutesSecond]);
            minuteSecond.setPosition((numColumns * 32) - 76, 32 * ((numRows) + 0.5f) + 16);
            timerDigits.push_back(minuteSecond);

            sf::Sprite secondFirst(digitTextures[secondsFirst]);
            secondFirst.setPosition((numColumns * 32) - 54, 32 * ((numRows) + 0.5f) + 16);
            timerDigits.push_back(secondFirst);

            sf::Sprite secondSecond(digitTextures[secondsSecond]);
            secondSecond.setPosition((numColumns * 32) - 33, 32 * ((numRows) + 0.5f) + 16);
            timerDigits.push_back(secondSecond);



//============================= Mine Counter sprites=============================//
            int numMines = myboard.ReturnNumMines() - flags.size();
            if (numMines < -99) {
                numMines = -99;
            }
            else if (numMines > 999) {
                numMines = 999;
            }

            if (numMines < 0) {
                sf::Sprite negative(digitTextures[10]);
                negative.setPosition(12, 32 * ((numRows)+0.5f) + 16);
                mineCounter.push_back(negative);
                numMines = abs(numMines);
            }

            sf::Sprite firstDigit(digitTextures[numMines / 100]);
            firstDigit.setPosition(33, 32 * ((numRows)+0.5f) + 16);
            mineCounter.push_back(firstDigit);

            sf::Sprite secondDigit(digitTextures[(numMines / 10) % 10]);
            secondDigit.setPosition(33+21, 32 * ((numRows)+0.5f) + 16);
            mineCounter.push_back(secondDigit);

            sf::Sprite thirdDigit(digitTextures[numMines % 10]);
            thirdDigit.setPosition(33+42, 32 * ((numRows)+0.5f) + 16);
            mineCounter.push_back(thirdDigit);

            //========================Drawing all sprites=========================//
            gameWindow.clear();
            for (const auto &tile: tiles) {
                gameWindow.draw(tile);
            }
            gameWindow.draw(rect);
            gameWindow.draw(happyFace);
            if (gameLose == true){
                gameWindow.draw(loseFace);
            }
            if (gameWin == true){
                gameWindow.draw(winFace);
            }


            for (const auto &tile: revealedTiles) {
                gameWindow.draw(tile);
            }
            for (const auto &mine: revealedMines) {
                gameWindow.draw(mine);
            }
            for (const auto &num: revealedNums) {
                gameWindow.draw(num);
            }
            for (const auto &flag: flags) {
                gameWindow.draw(flag);
            }
            for (const auto &digit: mineCounter) {
                gameWindow.draw(digit);
            }
            for (const auto &digit : timerDigits){
                gameWindow.draw(digit);
            }
            if(gamePaused == false){
                gameWindow.draw(pauseButton);
            }
            if (gamePaused == true){
                gameWindow.draw(playButton);
                for(const auto &tile : tempRevealed){
                    gameWindow.draw(tile);
                }
            }
            gameWindow.draw(debugButton);
            gameWindow.draw(leaderButton);
            gameWindow.display();
        }
    }
    //============================= Recursive function for revealing all adjacent tiles===================================//
    void revealAdjacentTiles(int row, int col, const int &numRows, const int &numColumns, const sf::Texture& revealedTile,
                             vector<sf::Sprite>& revealedTiles, vector<pair<int, int>>& revealedTilesCoords, Board& myboard, vector<sf::Sprite>& revealedNums,
                             vector<sf::Texture>& numTextures, vector<sf::Sprite> &flags) {
        if (row < 0 || col < 0 || row >= numRows || col >= numColumns) {
            return;
        }
        if (myboard.ReturnInt(row, col) == -1) {
            return;
        }
        bool alreadyFlagged = false;
        for (int i = 0; i < flags.size(); i++) {
            sf::Sprite &flag = flags[i];
            if (flag.getPosition() == sf::Vector2f(col * 32, row * 32)) {
                alreadyFlagged = true;
                return;
            }
            
        }
        for (const auto& coords : revealedTilesCoords) {
            if (coords == make_pair(row, col)) {
                return;
            }
        }
        sf::Sprite newTileRevealed(revealedTile);
        newTileRevealed.setPosition(col * 32, row * 32);
        revealedTiles.push_back(newTileRevealed);
        revealedTilesCoords.push_back(make_pair(            row, col));
        if (myboard.ReturnInt(row, col) != 0) {
            int x = myboard.ReturnInt(row, col);
            string num = to_string(x);
            sf::Sprite revealedNum(numTextures[x - 1]);
            revealedNum.setPosition(col * 32, row * 32);
            revealedNums.push_back(revealedNum);
            return;
        }
        revealAdjacentTiles(row - 1, col - 1, numRows, numColumns, revealedTile, revealedTiles, revealedTilesCoords, myboard, revealedNums, numTextures, flags);
        revealAdjacentTiles(row - 1, col, numRows, numColumns, revealedTile, revealedTiles, revealedTilesCoords, myboard, revealedNums, numTextures, flags);
        revealAdjacentTiles(row - 1, col + 1, numRows, numColumns, revealedTile, revealedTiles, revealedTilesCoords, myboard, revealedNums, numTextures, flags);
        revealAdjacentTiles(row, col - 1, numRows, numColumns, revealedTile, revealedTiles, revealedTilesCoords, myboard, revealedNums, numTextures, flags);
        revealAdjacentTiles(row, col + 1, numRows, numColumns, revealedTile, revealedTiles, revealedTilesCoords, myboard, revealedNums, numTextures, flags);
        revealAdjacentTiles(row + 1, col - 1, numRows, numColumns, revealedTile, revealedTiles, revealedTilesCoords, myboard, revealedNums, numTextures, flags);
        revealAdjacentTiles(row + 1, col, numRows, numColumns, revealedTile, revealedTiles, revealedTilesCoords, myboard, revealedNums, numTextures, flags);
        revealAdjacentTiles(row + 1, col + 1, numRows, numColumns, revealedTile, revealedTiles, revealedTilesCoords, myboard, revealedNums, numTextures, flags);
    }
    //============================================Leader window ==========================================//
        void LeaderBoard(int cols, int rows) {
            int width = cols*16;
            int height = rows*16 + 50;
            sf::RenderWindow leaderWindow(sf::VideoMode(width, height), "MineSweeper", sf::Style::Close);
            sf::RectangleShape rect;

            rect.setFillColor(sf::Color::Blue);
            rect.setSize(sf::Vector2f(width, height));
            rect.setPosition(0, 0);

            sf::Font font;
            font.loadFromFile("../files/font.ttf");
            sf::Text leaderTxt("LEADERBOARD", font, 20);
            leaderTxt.setStyle(sf::Text::Bold | sf::Text::Underlined);
            leaderTxt.setPosition(sf::Vector2f(width/2.0f , height / 2.0f -120));
            sf::FloatRect leaderBounds = leaderTxt.getGlobalBounds();
            leaderTxt.setOrigin(leaderBounds.width/2, leaderBounds.height/2);

            fstream inFile("../files/leaderboard.txt", ios_base::in);
            if (!inFile.is_open()) {
                cout << "Error opening file" << endl;
            }
            //==================================Reading all the inputs in text file=====================//
            string line;
            vector<pair<string, string>> entries;
            while(getline(inFile, line)) {
                stringstream ss(line);
                string time, name;
                getline(ss, time, ',');
                getline(ss, name);
                entries.push_back(make_pair(time, name));
            }

            sf::Text firstTxt("1.\t" + entries[0].first + "\t" + entries[0].second, font, 18);
            firstTxt.setPosition(width /4.0f, height/3.0f +20);
            sf::FloatRect firstBounds = firstTxt.getGlobalBounds();
            firstTxt.setStyle(sf::Text::Bold);

            sf::Text secondTxt("2.\t" + entries[1].first + "\t" + entries[1].second, font, 18);
            secondTxt.setPosition(width /4.0f, height/3.0f +40);
            leaderTxt.setStyle(sf::Text::Bold);
            sf::FloatRect secondBounds = secondTxt.getGlobalBounds();
            secondTxt.setStyle(sf::Text::Bold);


            sf::Text thirdTxt("3.\t" + entries[3].first + "\t" + entries[3].second, font, 18);
            thirdTxt.setPosition(width /4.0f, height/3.0f +60);
            sf::FloatRect thirdBounds = thirdTxt.getGlobalBounds();
            thirdTxt.setStyle(sf::Text::Bold);

            sf::Text fourthTxt("4.\t" + entries[3].first + "\t" + entries[3].second, font, 18);
            fourthTxt.setPosition(width /4.0f, height/3.0f +80);
            sf::FloatRect fourthBounds = fourthTxt.getGlobalBounds();
            fourthTxt.setStyle(sf::Text::Bold);

            sf::Text fifthTxt("5.\t" + entries[4].first + "\t" + entries[4].second, font, 18);
            fifthTxt.setPosition(width /4.0, height/3.0f +100);
            sf::FloatRect fifthBounds = fifthTxt.getGlobalBounds();
            fifthTxt.setStyle(sf::Text::Bold);

            // =============================Leaderboard window====================//
            while (leaderWindow.isOpen()) {
                sf::Event event;
                while (leaderWindow.pollEvent(event)) {
                    switch (event.type) {
                        case sf::Event::Closed:
                            leaderWindow.close();
                            break;
                    }
                }
                leaderWindow.clear();
                leaderWindow.draw(rect);
                leaderWindow.draw(leaderTxt);
                leaderWindow.draw(firstTxt);
                leaderWindow.draw(secondTxt);
                leaderWindow.draw(thirdTxt);
                leaderWindow.draw(fourthTxt);
                leaderWindow.draw(fifthTxt);
                leaderWindow.display();
            }

        }
        //============================Updating window if time is better than the ones in text======================//
    void LeaderBoardUpdate(int minutes, int seconds, string name){
        fstream inFile("../files/leaderboard.txt", ios_base::in);
        if (!inFile.is_open()) {
            cout << "Error opening file" << endl;
            return;
        }
        string line;
        vector<pair<string, string>> entries;
        while(getline(inFile, line)) {
            stringstream ss(line);
            string time, name;
            getline(ss, time, ',');
            getline(ss, name);
            entries.push_back(make_pair(time, name));
        }
        inFile.close();

        string newTime;
        if (minutes < 10) {
            newTime += "0";
        }
        newTime += to_string(minutes);
        newTime += ":";
        if (seconds < 10) {
            newTime += "0";
        }
        newTime += to_string(seconds);
        pair<string, string> newEntry = make_pair(newTime, name+"*");

        int insertIndex = 0;
        bool insertNewEntry = false;
        for (int i = 0; i < entries.size(); i++){
            if (entries[i].first > newTime){
                insertIndex = i;
                insertNewEntry = true;
                break;
            }
        }

        if (insertNewEntry || entries.size() < 5){
            entries.insert(entries.begin() + insertIndex, newEntry);
            if (entries.size() > 5){
                entries.pop_back();
            }
        }

        fstream outFile("../files/leaderboard.txt", ios_base::out | ios_base::trunc);
        if (!outFile.is_open()){
            cout << "Error opening file" << endl;
            return;
        }
        for (int i = 0; i < entries.size(); i++){
            outFile << entries[i].first << "," << entries[i].second << endl;
        }
        outFile.close();
        //====================Text default for leaderboard.txt===============//
//07:01,Alex
//09:04,Bruce
//10:03,Carl
//11:24,Dan
//12:15,Eve
    }
    };

#endif //MINESWEEPER_BOARD_H