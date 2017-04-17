#ifndef CHESS_FIGURES_H_INCLUDED
#define CHESS_FIGURES_H_INCLUDED

#include<string>
#include<sstream>
#include<vector>
#include<array>

static const int BOARD_SIDE = 8;
static const int BOARD_SIZE = BOARD_SIDE * BOARD_SIDE;
typedef std::array<char, BOARD_SIZE> ChessBoard;

enum FIGURE_COLOR {WHITE, BLACK};
enum FIGURE_TYPE {PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING};

class ChessFigures
{
public:
    // Destructor
    virtual ~ChessFigures() {}

    // Constructor
    ChessFigures(const std::string & position, const bool & moved, const bool & is_white, const FIGURE_TYPE & type) :
        m_position(getPositionFromString(position)),
        m_moved(moved),
        m_is_white(is_white),
        m_type(type) {}

    virtual std::vector<std::string> getAvailableMoves(const ChessBoard & otherFigures) const = 0;

    bool move(const std::string & newPosition, const ChessBoard & otherFigures)
    {
        std::vector<std::string> valid_moves = getAvailableMoves(otherFigures);

        for (auto valid_move : valid_moves)
        {
            if(valid_move == newPosition)
            {
                this->m_position = getPositionFromString(newPosition);
                this->m_moved = true;
                return true;
            }
        }

        return false;
    }

    std::string getFigureDetails(const ChessBoard & otherFigures) const
    {
        std::stringstream ss;

        ss << getFigureColorName() << " "
            << getFigureTypeName() << " ("
            << getFigureSymbol() << ") at "
            << getPositionName(this->m_position)
            << std::endl << "  Valid moves: "
            << getValidMovesList(getAvailableMoves(otherFigures));

        return ss.str();
    }

    std::string getFigureDetailsCompact(const ChessBoard & otherFigures) const
    {
        std::stringstream ss;

        ss << getFigureTypeName() << " ("
            << getFigureSymbol() << ") at ["
            << getPositionName(this->m_position)
            << "] Valid moves: "
            << getValidMovesList(getAvailableMoves(otherFigures));

        return ss.str();
    }

    std::string getFigureDetailsShort() const
    {
        std::stringstream ss;

        ss << getFigureColorName() << " "
            << getFigureTypeName() << " ("
            << getFigureSymbol() << ") at ["
            << getPositionName(this->m_position)
            << "]";

        return ss.str();
    }

    static std::string getPositionName(const int & position)
    {
        if (!isPositionValid(position))
        {
            throw "Invalid figure position";
        }

        std::stringstream ss;

        ss << char(97 + position % 8) << 1 + position / 8;

        return ss.str();
    }

    static int getPositionFromString(const std::string & position_str)
    {
        if (position_str.length() != 2
            || position_str[0] < 'a' || position_str[0] >= 'a' + BOARD_SIDE
            || position_str[1] < '1' || position_str[1] > '0' + BOARD_SIDE)
        {
            throw "Invalid figure position on board";
        }

        return (position_str[0] - 'a') + (position_str[1] - '1') * 8;
    }

    bool isFigureWhite() const
    {
        return this->m_is_white;
    }

    int getPosition() const
    {
        return this->m_position;
    }

    char getFigureSymbol() const
    {
        int color_update = 0;

        if (!this->m_is_white)
        {
            color_update += 32; // Small letters for black figures
        }

        switch (this->m_type)
        {
            case PAWN:
                return 'P' + color_update;
            case KNIGHT:
                return 'N' + color_update;
            case BISHOP:
                return 'B' + color_update;
            case ROOK:
                return 'R' + color_update;
            case QUEEN:
                return 'Q' + color_update;
            case KING:
                return 'K' + color_update;
            default:
                throw "Invalid figure type";
        }
    }

    bool isEnemyFigureAtPosition(const int & position, const ChessBoard & otherFigures) const
    {
        if (!isPositionEmpty(position, otherFigures))
        {
            if (this->m_is_white != isupper(otherFigures[position]))
            {
                return true;
            }
        }

        return false;
    }

    FIGURE_TYPE getType() const
    {
        return this->m_type;
    }

protected:
    int m_position;
    bool m_moved;
    const bool m_is_white;
    const FIGURE_TYPE m_type;

    std::string getFigureTypeName() const
    {
        switch (this->m_type)
        {
            case PAWN:
                return "Pawn";
            case KNIGHT:
                return "Knight";
            case BISHOP:
                return "Bishop";
            case ROOK:
                return "Rook";
            case QUEEN:
                return "Queen";
            case KING:
                return "King";
            default:
                throw "Invalid figure type";
        }
    }

    std::string getValidMovesList(const std::vector<std::string> & valid_moves) const
    {
        std::stringstream ss;

        for (auto position : valid_moves)
        {
            ss << position << " ";
        }

        return ss.str();
    }

    std::string getFigureColorName() const
    {
        return this->m_is_white?"White":"Black";
    }

    bool isPositionEmpty(const int & position, const ChessBoard & otherFigures) const
    {
        return otherFigures[position] == '0';
    }

    static bool isPositionValid(const int & position)
    {
        if (position < 0 && position >= BOARD_SIZE)
        {
            return false;
        }

        return true;
    }

    void validateNewPosition(const int & position, const ChessBoard & otherFigures, bool & valid_locaion, bool & end_reached) const
    {
        valid_locaion = false;
        end_reached = false;
        if (!isPositionValid(position))
        {
            end_reached = true;
        }
        else if (isEnemyFigureAtPosition(position, otherFigures))
        {
            valid_locaion = true;
            end_reached = true;
        }
        else if (isPositionEmpty(position, otherFigures))
        {
            valid_locaion = true;
        }
        else
        {
            end_reached = true;
        }
    }

    bool validateNewPositionSimple(const int & position, const ChessBoard & otherFigures) const
    {
            return isPositionValid(position)
                && (isPositionEmpty(position, otherFigures)
                    || isEnemyFigureAtPosition(position, otherFigures));
    }
};

class Pawn : public ChessFigures
{
public:
    Pawn(const std::string & position, const FIGURE_COLOR color) :
        ChessFigures(position, false, (color == WHITE), PAWN) {}

    std::vector<std::string> getAvailableMoves(const ChessBoard & otherFigures) const
    {
        std::vector<std::string> valid_moves_list;

        int forward_direction = BOARD_SIDE;

        if (!this->m_is_white)
        {
            forward_direction = -BOARD_SIDE;
        }

        // Check position in front of the pawn
        if (isPositionEmpty(this->m_position + forward_direction, otherFigures))
        {
            valid_moves_list.push_back(getPositionName(this->m_position + forward_direction));
        }

        // Check position two spaces in front of the pawn when not moved so far in the game
        if (!this->m_moved
            && isPositionEmpty(this->m_position + forward_direction, otherFigures)
            && isPositionEmpty(this->m_position + forward_direction * 2, otherFigures))
        {
            valid_moves_list.push_back(getPositionName(this->m_position + forward_direction * 2));
        }

        // Check for possible attack on one of the sides
        if (this->m_position % 8 < 7 && isEnemyFigureAtPosition(this->m_position + forward_direction + 1, otherFigures))
        {
            valid_moves_list.push_back(getPositionName(this->m_position + forward_direction + 1));
        }

        // Check for possible attack on the other side
        if (this->m_position % 8 > 0  && isEnemyFigureAtPosition(this->m_position + forward_direction - 1, otherFigures))
        {
            valid_moves_list.push_back(getPositionName(this->m_position + forward_direction - 1));
        }

        return valid_moves_list;
    }
};

class Knight : public ChessFigures
{
public:
    Knight(const std::string & position, const FIGURE_COLOR color) :
        ChessFigures(position, false, (color == WHITE), KNIGHT) {}

    std::vector<std::string> getAvailableMoves(const ChessBoard & otherFigures) const
    {
        std::vector<std::string> valid_moves_list;

        if (this->m_position % BOARD_SIDE - 2 >= 0)
        {
            if (this->m_position / BOARD_SIDE - 1 >= 0 &&
                validateNewPositionSimple(this->m_position - BOARD_SIDE - 2, otherFigures))
            {
                valid_moves_list.push_back(getPositionName(this->m_position - BOARD_SIDE - 2));
            }

            if (this->m_position / BOARD_SIDE + 1 < BOARD_SIDE &&
                validateNewPositionSimple(this->m_position + BOARD_SIDE - 2, otherFigures))
            {
                valid_moves_list.push_back(getPositionName(this->m_position + BOARD_SIDE - 2));
            }
        }

        if (this->m_position % BOARD_SIDE + 2 < BOARD_SIDE)
        {
            if (this->m_position / BOARD_SIDE - 1 >= 0 &&
                validateNewPositionSimple(this->m_position - BOARD_SIDE + 2, otherFigures))
            {
                valid_moves_list.push_back(getPositionName(this->m_position - BOARD_SIDE + 2));
            }

            if (this->m_position / BOARD_SIDE + 1 < BOARD_SIDE &&
                validateNewPositionSimple(this->m_position + BOARD_SIDE + 2, otherFigures))
            {
                valid_moves_list.push_back(getPositionName(this->m_position + BOARD_SIDE + 2));
            }
        }

        if (this->m_position / BOARD_SIDE - 2 >= 0)
        {
            if (this->m_position % BOARD_SIDE - 1 >= 0 &&
                validateNewPositionSimple(this->m_position - 2 * BOARD_SIDE - 1, otherFigures))
            {
                valid_moves_list.push_back(getPositionName(this->m_position - 2 * BOARD_SIDE - 1));
            }

            if (this->m_position % BOARD_SIDE + 1 < BOARD_SIDE &&
                validateNewPositionSimple(this->m_position - 2 * BOARD_SIDE + 1, otherFigures))
            {
                valid_moves_list.push_back(getPositionName(this->m_position - 2 * BOARD_SIDE + 1));
            }
        }

        if (this->m_position / BOARD_SIDE + 2 < BOARD_SIDE)
        {
            if (this->m_position % BOARD_SIDE - 1 >= 0 &&
                validateNewPositionSimple(this->m_position + 2 * BOARD_SIDE - 1, otherFigures))
            {
                valid_moves_list.push_back(getPositionName(this->m_position + 2 * BOARD_SIDE - 1));
            }

            if (this->m_position % BOARD_SIDE + 1 < BOARD_SIDE &&
                validateNewPositionSimple(this->m_position + 2 * BOARD_SIDE + 1, otherFigures))
            {
                valid_moves_list.push_back(getPositionName(this->m_position + 2 * BOARD_SIDE + 1));
            }
        }

        return valid_moves_list;
    }
};

class Bishop : public ChessFigures
{
public:
    Bishop(const std::string & position, const FIGURE_COLOR color) :
        ChessFigures(position, false, (color == WHITE), BISHOP) {}

    std::vector<std::string> getAvailableMoves(const ChessBoard & otherFigures) const
    {
        std::vector<std::string> valid_moves_list;
        bool end_reached, valid_locaion;

        int curr_position = this->m_position;
        while (curr_position / BOARD_SIDE + 1 < BOARD_SIDE && curr_position % BOARD_SIDE + 1 < BOARD_SIDE)
        {
            curr_position += BOARD_SIDE + 1;

            validateNewPosition(curr_position, otherFigures, valid_locaion, end_reached);

            if (valid_locaion)
            {
                valid_moves_list.push_back(getPositionName(curr_position));
            }

            if (end_reached)
            {
                break;
            }
        }

        curr_position = this->m_position;
        while (curr_position / BOARD_SIDE + 1 < BOARD_SIDE && curr_position % BOARD_SIDE - 1 >= 0)
        {
            curr_position += BOARD_SIDE - 1;

            validateNewPosition(curr_position, otherFigures, valid_locaion, end_reached);

            if (valid_locaion)
            {
                valid_moves_list.push_back(getPositionName(curr_position));
            }

            if (end_reached)
            {
                break;
            }
        }

        curr_position = this->m_position;
        while (curr_position / BOARD_SIDE - 1 >= 0 && curr_position % BOARD_SIDE + 1 < BOARD_SIDE)
        {
            curr_position += -BOARD_SIDE + 1;

            validateNewPosition(curr_position, otherFigures, valid_locaion, end_reached);

            if (valid_locaion)
            {
                valid_moves_list.push_back(getPositionName(curr_position));
            }

            if (end_reached)
            {
                break;
            }
        }

        curr_position = this->m_position;
        while (curr_position / BOARD_SIDE - 1 >= 0 && curr_position % BOARD_SIDE - 1 >= 0)
        {
            curr_position += -BOARD_SIDE - 1;

            validateNewPosition(curr_position, otherFigures, valid_locaion, end_reached);

            if (valid_locaion)
            {
                valid_moves_list.push_back(getPositionName(curr_position));
            }

            if (end_reached)
            {
                break;
            }
        }

        return valid_moves_list;
    }
};

class Rook : public ChessFigures
{
public:
    Rook(const std::string & position, const FIGURE_COLOR color) :
        ChessFigures(position, false, (color == WHITE), ROOK) {}

    std::vector<std::string> getAvailableMoves(const ChessBoard & otherFigures) const
    {
        std::vector<std::string> valid_moves_list;
        bool end_reached, valid_locaion;

        int curr_position = this->m_position;
        while (curr_position / BOARD_SIDE + 1 < BOARD_SIDE)
        {
            curr_position += BOARD_SIDE;

            validateNewPosition(curr_position, otherFigures, valid_locaion, end_reached);

            if (valid_locaion)
            {
                valid_moves_list.push_back(getPositionName(curr_position));
            }

            if (end_reached)
            {
                break;
            }
        }

        curr_position = this->m_position;
        while (curr_position / BOARD_SIDE - 1 >= 0)
        {
            curr_position -= BOARD_SIDE;

            validateNewPosition(curr_position, otherFigures, valid_locaion, end_reached);

            if (valid_locaion)
            {
                valid_moves_list.push_back(getPositionName(curr_position));
            }

            if (end_reached)
            {
                break;
            }
        }

        curr_position = this->m_position;
        while (curr_position % BOARD_SIDE - 1 >= 0)
        {
            curr_position -= 1;

            validateNewPosition(curr_position, otherFigures, valid_locaion, end_reached);

            if (valid_locaion)
            {
                valid_moves_list.push_back(getPositionName(curr_position));
            }

            if (end_reached)
            {
                break;
            }
        }

        curr_position = this->m_position;
        while (curr_position % BOARD_SIDE + 1 < BOARD_SIDE)
        {
            curr_position += 1;

            validateNewPosition(curr_position, otherFigures, valid_locaion, end_reached);

            if (valid_locaion)
            {
                valid_moves_list.push_back(getPositionName(curr_position));
            }

            if (end_reached)
            {
                break;
            }
        }

        return valid_moves_list;
    }
private:

};

class Queen : public ChessFigures
{
public:
    Queen(const std::string & position, const FIGURE_COLOR color) :
        ChessFigures(position, false, (color == WHITE), QUEEN) {}

    std::vector<std::string> getAvailableMoves(const ChessBoard & otherFigures) const
    {
        std::vector<std::string> valid_moves_list, valid_moves_list2;

        Rook rock(getPositionName(this->m_position), this->m_is_white?WHITE:BLACK);
        valid_moves_list = rock.getAvailableMoves(otherFigures);

        Bishop bishop(getPositionName(this->m_position), this->m_is_white?WHITE:BLACK);
        valid_moves_list2 = bishop.getAvailableMoves(otherFigures);

        valid_moves_list.insert(valid_moves_list.end(), valid_moves_list2.begin(), valid_moves_list2.end());

        return valid_moves_list;
    }
};

class King : public ChessFigures
{
public:
    King(const std::string & position, const FIGURE_COLOR color) :
        ChessFigures(position, false, (color == WHITE), KING) {}

    std::vector<std::string> getAvailableMoves(const ChessBoard & otherFigures) const
    {
        std::vector<std::string> valid_moves_list;

        if (this->m_position / BOARD_SIDE + 1 < BOARD_SIDE)
        {
            if (validateNewPositionSimple(this->m_position + BOARD_SIDE, otherFigures))
            {
                valid_moves_list.push_back(getPositionName(this->m_position + BOARD_SIDE));
            }

            if (this->m_position % BOARD_SIDE - 1 >= 0
                && validateNewPositionSimple(this->m_position + BOARD_SIDE - 1, otherFigures))
            {
                valid_moves_list.push_back(getPositionName(this->m_position + BOARD_SIDE - 1));
            }

            if (this->m_position % BOARD_SIDE + 1 < BOARD_SIDE
                && validateNewPositionSimple(this->m_position + BOARD_SIDE + 1, otherFigures))
            {
                valid_moves_list.push_back(getPositionName(this->m_position + BOARD_SIDE + 1));
            }
        }

        if (this->m_position / BOARD_SIDE - 1 >= 0)
        {
            if (validateNewPositionSimple(this->m_position - BOARD_SIDE, otherFigures))
            {
                valid_moves_list.push_back(getPositionName(this->m_position - BOARD_SIDE));
            }

            if (this->m_position % BOARD_SIDE - 1 >= 0
                && validateNewPositionSimple(this->m_position - BOARD_SIDE - 1, otherFigures))
            {
                valid_moves_list.push_back(getPositionName(this->m_position - BOARD_SIDE - 1));
            }

            if (this->m_position % BOARD_SIDE + 1 < BOARD_SIDE
                && validateNewPositionSimple(this->m_position - BOARD_SIDE + 1, otherFigures))
            {
                valid_moves_list.push_back(getPositionName(this->m_position - BOARD_SIDE + 1));
            }
        }

        if (this->m_position % BOARD_SIDE - 1 >= 0
            && validateNewPositionSimple(this->m_position - 1, otherFigures))
        {
            valid_moves_list.push_back(getPositionName(this->m_position - 1));
        }

        if (this->m_position % BOARD_SIDE + 1 < BOARD_SIDE
            && validateNewPositionSimple(this->m_position + 1, otherFigures))
        {
            valid_moves_list.push_back(getPositionName(this->m_position + 1));
        }

        return valid_moves_list;
    }
};
#endif // CHESS_FIGURES_H_INCLUDED
