/* Write a program which uses the figures from Task 4 and allows two players
 to play the game of chess on the console. Your program should do something like:

intialize board;
currentPlayer = white;
while(no winner) {
    print board;
    read player input to select figure
    //optional: show positions to which selected figure can go
    read player input to move figure //should check for validity
    update board; //move the figure, remove any destroyed figures, etc.
    change currentPlayer;
}
print end game board and winner;

Printing the board should just be printing a matrix of 8x8. Each position of the
matrix can be a single character (you can also add the column and row designations
if you like). You can distinguish between white and black figures by printing all
the black figures as lowercase symbols, while printing all the white figures as
uppercase symbols. If you want, you can play around with changing console color,
clearing the console after each move, etc. - but that will probably make your program
not run on every OS. So if you do that, you should submit it as a separate version and
also submit a version that doesn't have those additional features and works on every OS.
The structure of your program is up to you, but a good approach would be to have a
ChessRenderer which is inherited by a ChessConsoleVisualRenderer, which prints to the
console (so that your code easily be extended, for example, by adding a ChessConsoleTextRenderer
which just prints stuff like "White Knight at G3"), an InputParser which reads player
input from the console, a ChessEngine which manages all the figures, handles moves and
figure destruction, keeps track of the game state (did the King die?/does the king have
nowhere to move?/is the current player's king under threat, meaning that the current
player's valid moves are restricted to defending the king?), etc., and a Chess class
which uses all of the above in the correct order to play the game.*/

#include<iostream>
#include "5-chess-game.h"

int main()
{
    ChessGame * game = new ChessGame();

    ConsoleWriter console_writer;
    ConsoleReader console_reader;

    int turns_counter = 1;

    while (!game->gameEnded())
    {
        std::cout << std::endl << "Turn " << turns_counter++ << std::endl << std:: endl;

        console_writer.printChessBoard(game->getChessBoard());

        ChessFigures * selected_figure = nullptr;

        do
        {
            console_writer.printPlayerMoves(game->getFiguresList(), game->isWhiteTurn(), game->getChessBoard());
            selected_figure = game->getPlayerSelectedFigure(console_reader.getUserInput());
        }
        while (selected_figure == nullptr );

        std::string new_position;

        ChessFigures * enemy_figure = nullptr;

        do
        {
            console_writer.printFigureMoves(selected_figure, game->getChessBoard());

            new_position = console_reader.getUserInput();

            enemy_figure = nullptr;

            if (selected_figure->isEnemyFigureAtPosition(ChessFigures::getPositionFromString(new_position), game->getChessBoard()))
            {
                enemy_figure = game->getFigureAtPosition(new_position);
            }

        }
        while (!selected_figure->move(new_position, game->getChessBoard()));

        if (enemy_figure != nullptr)
        {
            std::cout << std::endl << enemy_figure->getFigureDetailsShort() << " removed from game" << std::endl;

            if (!game->deleteFigure(enemy_figure))
            {
                throw "Figure deletion failed";
            }
        }

        game->updateBoard();

        game->switchPlayer();
    }

    console_writer.printChessBoard(game->getChessBoard());

    std::cout << std::endl << "Checkmate - " << (game->isWhiteTurn()?"Black":"White") << " victory!" << std::endl;

    delete game;

    return 0;
}
