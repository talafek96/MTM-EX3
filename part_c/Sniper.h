#ifndef SNIPER_INC
#define SNIPER_INC
// Includes

#include "Character.h"
#include <map>
//---------

namespace mtm
{
    class Sniper : public Character
    {
    private:
        /*********************************/
        /*        Private Section        */
        /*********************************/
        /* Instance variables */
        int combo_attack_count;
        
        /* Const instance variables */
        static const char CPP_NAME = 'S';
        static const char PYTHON_NAME = 's';
        static const int MAX_MOVE_RANGE = 4;
        static const int MAX_COMBO = 2;
        static const units_t CRITICAL_MULTIPLIER = 2;
        static const units_t RELOAD_AMMOUNT = 2;
        static const units_t AMMO_COST = 1;
    public:
        /*
         * Constructor: Sniper
         * Usage: Sniper usopp(height, width);
         * ---------------------------------------
         * Initializes a new Sniper character.  
         * Creates a Sniper character with the inputted stats.
         */
        Sniper(Team team, units_t health, units_t ammo, units_t range, units_t power) noexcept;
        
        /*
         * Copy Constructor: Sniper
         * Usage: Sniper copied_sniper(other);
         * ---------------------------------------
         * Creates a new copy of the sniper other.
         * Copies each and every one of other's stats.
         */
        Sniper(const Sniper& other) = default;
        
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
         * Usage: sniper.reload();
         * -----------------------------------
         * Adds 2 ammo to the sniper. 
         */
        void reload() noexcept;

        /*
         * Method: isInAttackRange
         * Usage: sniper.isInAttackRange(src_coords, dst_coords);
         * -----------------------------------
         * Returns true if and only if the attack target is in attack range.
         */
        bool isInAttackRange(const GridPoint& src_coordinates , const GridPoint& dst_coordinates) const noexcept;

        /*
         * Method: isLegalMove
         * Usage: sniper.isLegalMove();
         * -----------------------------------
         * Returns true if and only if the desired movement is legal.
         */        
        bool isLegalMove(int distance) const noexcept;

        /*
         * Method: hasEnoughAmmo
         * Usage: sniper.hasEnoughAmmo();
         * -----------------------------------
         * Returns true if and only if the sniper has enough ammo to attack.
         */
        bool hasEnoughAmmo() const noexcept;

        /*
         * Method: attack
         * Usage: sniper.attack(board, src_coords, dst_coords);
         * -----------------------------------
         * ASSUMES: src_coords is legal and contains the corresponding character (*this).
         * 
         * Attempts to attack the enemy character at grid dst_coords.
         * 
         * Possible Exceptions:
         * mtm::OutOfAmmo, mtm::IllegalTarget.
         */
        void attack(Matrix<std::shared_ptr<Character>>board, const GridPoint& src_coordinates , const GridPoint& dst_coordinates);
    };
};
#endif