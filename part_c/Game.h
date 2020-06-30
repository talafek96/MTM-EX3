#ifndef GAME_INC
#define GAME_INC
// Includes
#include <iostream>
#include <memory>
#include "Matrix.h"
#include "Auxiliaries.h"
#include "Exceptions.h"
#include "Character.h"
#include "Sniper.h"
#include "Medic.h"
#include "Soldier.h"
//---------

namespace mtm
{
    class Game
    {
    private:
        /*********************************/
        /*        Private Section        */
        /*********************************/
        /* Instance variables */
        Matrix<std::shared_ptr<Character>> board;
        bool isInBounds(const GridPoint& coordinates) const;
        static const char EMPTY_CELL = ' ';
    public:
        /**************************************/
        /*     C'tors and D'tors section      */
        /**************************************/
        /*
         * Constructor: Game
         * Usage: Game game(height, width);
         * ---------------------------------------
         * Initializes a new Game.  
         * Creates a game board with the dimension of height x width.
         * Each cell in the board is initialized to be clear of characters.
         * 
         * Possible Exceptions:
         * mtm::IllegalArgument, std::bad_alloc
         */
        Game(int height, int width);
        
        /*
         * Copy Constructor: Game
         *            Usage: Game new_game(other);
         *                   Game new_game =other;
         * ---------------------------------------
         * Creates a game that is a copy of other.
         *
         * Possible exceptions:
         * std::bad_alloc
         */ 
        Game(const Game& other);
        ~Game() = default;

        /**************************************/
        /*     Method definition section      */
        /**************************************/
        /*
         * Method: addCharacter
         * Usage: game.addCharacter(coordinates, character);
         * -----------------------------------
         * Recieves a shared_ptr to character, and places him in the wanted coordinates.
         * 
         * Possible exceptions:
         * mtm::IllegalCell, mtm::CellOccupied.
         */
        void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);

        /*
         * Method: move
         * Usage: game.move(src_coordinates, dst_coordinates);
         * -----------------------------------
         * Moves a character from src_coordinates to dst_coordinates.
         * 
         * Possible exceptions:
         * mtm::IllegalCell, mtm::CellOccupied.
         */
        void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);

        /*
         * Method: addCharacter
         * Usage: int rows = matrix.height();
         * -----------------------------------
         * Makes a character in the cell src_coordinates send an attack to dst_coordinates.
         * 
         * Possible exceptions:
         * mtm::IllegalCell,mtm::CellEmpty, mtm::MoveTooFar, mtm::CellOccupied.
         */
        void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);

        /*
         * Method: reload
         * Usage: game.reload();
         * -----------------------------------
         * Gives ammo the the character in the chosen coordinates.
         * 
         * Possible exceptions:
         * mtm::IllegalCell, mtm::CellEmpty.
         */
        void reload(const GridPoint & coordinates);

        /*
         * Method: isOver
         * Usage: bool game_over = game.isOver();
         * -----------------------------------
         * Returns whether the game is in a winning state or not.
         * If returns true and winningTeam is not a NULL pointer,
         * update it with the winning team (enum).
         */
        bool isOver(Team* winningTeam=NULL) const noexcept;

        /**************************************/
        /*    Function definition section     */
        /**************************************/
        /*
         * Function: makeCharacter
         * Usage:  std::shared_ptr<Character> new_character = makeCharacter(type, team, health, ammo, range, power)
         * --------------------------------------
         * Creates a new character with the corresponding parameters, and 
         * returns a shared_ptr to his object.
         * 
         * Possible exceptions:
         * mtm::IllegalArgument, std::bad_alloc.
         */
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team, 
                                    units_t health, units_t ammo, units_t range, units_t power);

        /**************************************/
        /*    Operator definition section     */
        /**************************************/
        
        Game& operator=(const Game& other);
        /*
         * Operator: <<
         * Usage: std::ostream& out << game
         * ----------------------------------
         * Prints the game board in a formatted template to the output channel.
         */
        friend std::ostream& operator<<(std::ostream& out, Game& game) noexcept;
    };
    std::ostream& operator<<(std::ostream& out, Game& game) noexcept;
};
#endif