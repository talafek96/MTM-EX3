#include "Game.h"

namespace mtm
{
    /***************************************/
    /*     Ctors implementation section    */
    /***************************************/
    Game::Game(int height, int width) :
    board((height <=0 || width <= 0)?
        throw IllegalArgument() : Matrix<std::shared_ptr<Character>>(Dimensions(height, width), nullptr))
    {
        
    }
    
    Game::Game(const Game& other) :
    board(other.board)
    {
        for(std::shared_ptr<Character>& character_ptr : board)
        {
            if(character_ptr != nullptr)
            {
                character_ptr = character_ptr->clone();
            }
        }
    }

    /****************************************/
    /*     Method implementation section    */
    /****************************************/
    void Game::addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character)
    {
        if ((coordinates.row < 0) || (coordinates.col < 0) 
            || (coordinates.row >= board.height()) || (coordinates.col >= board.width()))
        {
            throw IllegalCell();
        }
        if(board(coordinates.row, coordinates.col) != nullptr)
        {
            throw CellOccupied();
        }
        board(coordinates.row, coordinates.col) = character;
    }
    
    void Game::move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
    {
        if(!(isInBounds(src_coordinates)) || !(isInBounds(dst_coordinates)))
        {
            throw IllegalCell();
        }
        if (board(src_coordinates.row, src_coordinates.col) == nullptr)  
        {
            throw CellEmpty();
        }  
        if(!board(src_coordinates.row, src_coordinates.col)->
        isLegalMove(GridPoint::distance(src_coordinates, dst_coordinates)))
        {
            throw MoveTooFar();
        }
        if (board(dst_coordinates.row, dst_coordinates.col) != nullptr)
        {
            throw CellOccupied();
        }
        board(dst_coordinates.row, dst_coordinates.col) = board(src_coordinates.row, src_coordinates.col);
        board(src_coordinates.row, src_coordinates.col) = nullptr;
    }

    void Game::attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
    {
        if(!isInBounds(src_coordinates) || !isInBounds(dst_coordinates))
        {
            throw IllegalCell();
        }
        if (board(src_coordinates.row, src_coordinates.col) == nullptr)  
        {
            throw CellEmpty();
        }
        if(!board(src_coordinates.row, src_coordinates.col)->
        isInAttackRange(src_coordinates, dst_coordinates))
        {
            throw OutOfRange();
        }
        board(src_coordinates.row, src_coordinates.col)->attack(board, src_coordinates, dst_coordinates);
        clearDeadCharacters();
    };

    void Game::reload(const GridPoint & coordinates)
    {
        if ((coordinates.row < 0) || (coordinates.col < 0) 
            || (coordinates.row >= board.height()) || (coordinates.col >= board.width()))
        {
            throw IllegalCell();
        }
        if(board(coordinates.row, coordinates.col) == nullptr)
        {
            throw CellEmpty();
        }
        board(coordinates.row, coordinates.col)->reload();
    }
    
    bool Game::isOver(Team* winningTeam) const noexcept
    {
        bool cppFlag = false, pythonFlag = false; //false = none exist on the board, true = otherwise
        bool winnerFlag = false;
        Team whoWon;
        for (const std::shared_ptr<Character>& character_ptr : board)
        {
            if (character_ptr != nullptr)
            {
                if (character_ptr->getTeam() == CPP)
                {
                    cppFlag = true;
                }
                if (character_ptr->getTeam() == PYTHON)
                {
                    pythonFlag = true;
                }
            }
        }
        if(cppFlag && !pythonFlag)
        {
            whoWon = CPP;
            winnerFlag = true;
        }
        else if(!cppFlag && pythonFlag)
        {
            whoWon = PYTHON;
            winnerFlag = true;
        }
        if(winnerFlag && winningTeam != nullptr)
        {
            *winningTeam = whoWon;
        }
        return winnerFlag;
    }

    bool Game::isInBounds(const GridPoint& coordinates) const
    {
        if((coordinates.row < 0) || (coordinates.col < 0) 
        || (coordinates.row >= board.height()) || (coordinates.col >= board.width()) )
        {
            return false;
        }
        return true;
    }
    
    /* Private Methods */
    void Game::clearDeadCharacters() noexcept
    {
        for(std::shared_ptr<Character>& cell : board)
        {
            if(cell != nullptr)
            {
                if(cell->getHealth() <= 0)
                {
                    cell = nullptr;
                }
            }
        }
    }

    /**************************************/
    /*    Function definition section     */
    /**************************************/
    std::shared_ptr<Character> Game::makeCharacter(CharacterType type, Team team, 
                                units_t health, units_t ammo, units_t range, units_t power)
    {
        std::shared_ptr<Character> new_character;
        switch(type)
        {
            case SOLDIER:
            new_character = std::shared_ptr<Character>(new Soldier(team, health, ammo, range, power));
            break;

            case MEDIC:
            new_character = std::shared_ptr<Character>(new Medic(team, health, ammo, range, power));
            break;

            case SNIPER:
            new_character = std::shared_ptr<Character>(new Sniper(team, health, ammo, range, power));
            break;
        }
        return new_character;
    }

    std::ostream& operator<<(std::ostream& out, Game& game) noexcept
    {
        char container[game.board.size()];
        int i = 0;
        for (const std::shared_ptr<Character>& character_ptr : game.board)
        {
            if(character_ptr == nullptr)
            {
                container[i++] = Game::EMPTY_CELL;
            }
            else
            {
                container[i++] = character_ptr->getName();
            }
        }
        return printGameBoard(out, container, container + i, game.board.width());
    }
};