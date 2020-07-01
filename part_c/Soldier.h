#ifndef SOLDIER_INC
#define SOLDIER_INC
// Includes
#include "Character.h"
//---------

namespace mtm
{
    class Soldier : public Character
    {
    private:
        /*********************************/
        /*        Private Section        */
        /*********************************/
        /* Const instance variables */
        static const char CPP_NAME = 'S';
        static const char PYTHON_NAME = 's';
        static const units_t COLATERAL_RANGE = 3;
        static const units_t COLATERAL_DAMAGE = 2;
        static const int MAX_MOVE_RANGE = 3;
        static const units_t RELOAD_AMMOUNT = 3;
        static const units_t AMMO_COST = 1;
    public:
        /*
         * Constructor: Soldier
         * Usage: Soldier zoro(height, width);
         * ---------------------------------------
         * Initializes a new Soldier character.  
         * Creates a Soldier character with the inputted stats.
         */
        Soldier(Team team, units_t health, units_t ammo, units_t range, units_t power) noexcept;
        
        /*
         * Copy Constructor: Soldier
         * Usage: Soldier copied_soldier(other);
         * ---------------------------------------
         * Creates a new copy of the soldier other.
         * Copies each and every one of other's stats.
         */
        Soldier(const Soldier& other) = default;
        
        /*
         * Method: getName
         * Usage: char name = character.getName();
         * -----------------------------------
         * Returns the representation of the character on the game board as a char.
         */
        char getName() const noexcept;

        /*
         * Method: clone
         * Usage: shared_ptr<Character> copied_character = character.clone();
         * -----------------------------------
         * Returns a shared_ptr to a copy of a copied character.
         * 
         * Possible Exceptions:
         * std::bad_alloc.
         */
         std::shared_ptr<Character> clone() const;
        
        /*
         * Method: reload
         * Usage: soldier.reload();
         * -----------------------------------
         * Adds 2 ammo to the Soldier. 
         */
        void reload() noexcept;

        /*
         * Method: isInAttackRange
         * Usage: soldier.isInAttackRange(src_coords, dst_coords);
         * -----------------------------------
         * Returns true if and only if the attack target is in attack range.
         */
        bool isInAttackRange(const GridPoint& src_coordinates , const GridPoint& dst_coordinates) const noexcept;

        /*
         * Method: isLegalMove
         * Usage: soldier.isLegalMove();
         * -----------------------------------
         * Returns true if and only if the desired movement is legal.
         */        
        bool isLegalMove(int distance) const noexcept;

        /*
         * Method: hasEnoughAmmo
         * Usage: soldier.hasEnoughAmmo();
         * -----------------------------------
         * Returns true if and only if the soldier has enough ammo to attack.
         */
        bool hasEnoughAmmo() const noexcept;

        /*
         * Method: attack
         * Usage: soldier.attack(board, src_coords, dst_coords);
         * -----------------------------------
         * ASSUMES: src_coords is legal and contains the corresponding character(*this),
         * and dst_coordinates is in range.
         * 
         * Attempts to attack the area around grid dst_coords.
         * 
         * Possible Exceptions:
         * mtm::OutOfAmmo.
         */
        void attack(Matrix<std::shared_ptr<Character>>board, const GridPoint& src_coordinates , const GridPoint& dst_coordinates);
    };
};
#endif