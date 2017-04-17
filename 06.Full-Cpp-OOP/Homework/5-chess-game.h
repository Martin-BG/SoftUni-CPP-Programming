#ifndef CHESS_GAME_H_INCLUDED
#define CHESS_GAME_H_INCLUDED

#include "4-chess-figures.h"
#include<list>

class ChessGame
{
public:
    // Destructor
    virtual ~ChessGame()
    {
        for (auto &it : this->m_figures)
        {
            delete it;
        }

        this->m_figures.clear();
    }

    // Constructor
    ChessGame() :
        m_chess_board(ChessBoard{
        // a    b    c    d    e    f    g    h
          'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R', // 1 White
          'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', // 2 figures
          '0', '0', '0', '0', '0', '0', '0', '0', // 3
          '0', '0', '0', '0', '0', '0', '0', '0', // 4
          '0', '0', '0', '0', '0', '0', '0', '0', // 5
          '0', '0', '0', '0', '0', '0', '0', '0', // 6
          'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', // 7 Black
          'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}),// 8 figures
        m_figures(),
        m_game_ended(false),
        m_white_turn(true)
    {
        createObjectsFromBoard();
    }

    std::list<ChessFigures*> & getFiguresList()
    {
        return this->m_figures;
    }

    ChessBoard & getChessBoard()
    {
        return this->m_chess_board;
    }

    ChessFigures * getPlayerSelectedFigure(const std::string & position_str) const
    {
        ChessFigures * figure = getFigureAtPosition(position_str);
        if (figure != nullptr
            && figure->isFigureWhite() == this->m_white_turn
            && figure->getAvailableMoves(this->m_chess_board).size() > 0)
        {
            return figure;
        }

        return nullptr;
    }

    ChessFigures * getFigureAtPosition(const std::string & position_str) const
    {
        int position = ChessFigures::getPositionFromString(position_str);

        for (auto figure : this->m_figures)
        {
            if (figure->getPosition() == position)
            {
                return figure;
            }
        }

        return nullptr;
    }

    void updateBoard()
    {
        std::fill(std::begin(this->m_chess_board), std::end(this->m_chess_board), '0');

        for (auto figure : this->m_figures)
        {
            this->m_chess_board[figure->getPosition()] = figure->getFigureSymbol();
        }
    }

    void switchPlayer()
    {
        this->m_white_turn = !this->m_white_turn;
    }

    bool gameEnded() const
    {
        return this->m_game_ended;
    }

    bool isWhiteTurn() const
    {
        return this->m_white_turn;
    }

    bool deleteFigure(ChessFigures * delete_figure)
    {
        for (auto i = this->m_figures.begin(); i != this->m_figures.end();)
        {
            if ((*i) == delete_figure)
            {
                if (delete_figure->getType() == KING)
                {
                    this->m_game_ended = true;
                }

                this->m_figures.erase(i);
                delete delete_figure;
                return true;
            }
            else
            {
                ++i;
            }
        }

        return false;
    }
protected:
    ChessBoard m_chess_board;
    std::list<ChessFigures*> m_figures;
    bool m_game_ended;
    bool m_white_turn;

private:
    void createObjectsFromBoard()
    {
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            if (this->m_chess_board[i] != '0')
            {
                FIGURE_COLOR color = isupper(this->m_chess_board[i])?WHITE:BLACK;

                switch (tolower(this->m_chess_board[i]))
                {
                    case 'p' : m_figures.push_back(new Pawn(ChessFigures::getPositionName(i), color)); break;
                    case 'n' : m_figures.push_back(new Knight(ChessFigures::getPositionName(i), color)); break;
                    case 'b' : m_figures.push_back(new Bishop(ChessFigures::getPositionName(i), color)); break;
                    case 'r' : m_figures.push_back(new Rook(ChessFigures::getPositionName(i), color)); break;
                    case 'q' : m_figures.push_back(new Queen(ChessFigures::getPositionName(i), color)); break;
                    case 'k' : m_figures.push_back(new King(ChessFigures::getPositionName(i), color)); break;
                    default : throw "Invalid figure type"; break;
                }
            }
        }
    }
};

class ChessRender
{
public:
    std::string getChessBoardString(const ChessBoard & chess_board) const
    {
        std::stringstream ss;

        ss << "  a b c d e f g h" << std::endl;
        for (int i = 0; i < BOARD_SIDE; i++)
        {
            ss << i + 1 << " ";

            for (int j = 0; j < BOARD_SIDE; j++)
            {
                ss << chess_board[i * BOARD_SIDE + j] <<  " ";
            }

            ss << i + 1 << std::endl;
        }
        ss << "  a b c d e f g h" << std::endl;

        return ss.str();
    }

    std::string getPlayerMovesString(const std::list<ChessFigures*> & figures, const bool white_turn, const ChessBoard & chess_board) const
    {
        std::stringstream ss;

        for (auto figure : figures)
        {
            if(figure->isFigureWhite() == white_turn
               && figure->getAvailableMoves(chess_board).size() > 0)
            {
                ss << figure->getFigureDetailsCompact(chess_board) << std::endl;
            }
        }

        return ss.str();
    }

    std::string getFigureMovesString(const ChessFigures * figure, const ChessBoard & chess_board) const
    {
        std::stringstream ss;

        ss << figure->getFigureDetailsCompact(chess_board)
            << std::endl << "Enter new position of the figure: ";

        return ss.str();
    }
};

class ConsoleWriter : public ChessRender
{
public:
    void printChessBoard(const ChessBoard & chess_board) const
    {
        std::cout << getChessBoardString(chess_board) << std::endl;
    }

    void printPlayerMoves(const std::list<ChessFigures*> & figures, const bool white_turn, const ChessBoard & chess_board) const
    {
        std::cout << "It's "
            << (white_turn?"White":"Black")
            << "'s turn" << std::endl << std::endl
            << getPlayerMovesString(figures, white_turn, chess_board) << std::endl
            << "Enter position of figure you want to move: ";
    }

    void printFigureMoves(const ChessFigures * figure, const ChessBoard & chess_board) const
    {
        std::cout << getFigureMovesString(figure, chess_board);
    }
};

class ConsoleReader
{
public:
    std::string getUserInput() const
    {
        std::string input;

        do
        {
            std::cin >> input;
        }
        while (input.length() != 2
                || input[0] < 'a' || input[0] >= 'a' + BOARD_SIDE
                || input[1] < '1' || input[1] > '0' + BOARD_SIDE);

        return input;
    }
};

#endif // CHESS_GAME_H_INCLUDED
