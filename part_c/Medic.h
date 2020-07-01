#ifndef MEDIC_INC
#define MEDIC_INC
// Includes
#include "Character.h"
//---------

namespace mtm
{
    class Medic : public Character
    {
    private:
        /*********************************/
        /*        Private Section        */
        /*********************************/
        /* Const instance variables */

        static const char CPP_NAME = 'M';
        static const char PYTHON_NAME = 'm';
        static const int MAX_MOVE_RANGE = 5;
        static const units_t RELOAD_AMMOUNT = 5;
        static const units_t AMMO_COST = 1;
    public:
        /*
         * Constructor: Medic
         * Usage: Medic choper(height, width);
         * ---------------------------------------
         * Initializes a new Medic character.  
         * Creates a Medic character with the inputted stats.
         */
        Medic(Team team, units_t health, units_t ammo, units_t range, units_t power) noexcept;
        
        /*
         * Copy Constructor: Medic
         * Usage: Medic copied_medic(other);
         * ---------------------------------------
         * Creates a new copy of the medic other.
         * Copies each and every one of other's stats.
         */
        Medic(const Medic& other) = default;
        
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
         * Usage: medic.reload();
         * -----------------------------------
         * Adds 5 ammo to the medic. 
         */
        void reload() noexcept;

        /*
         * Method: isInAttackRange
         * Usage: medic.isInAttackRange(src_coords, dst_coords);
         * -----------------------------------
         * Returns true if and only if the attack target is in attack range.
         */
        bool isInAttackRange(const GridPoint& src_coordinates , const GridPoint& dst_coordinates) const noexcept;

        /*
         * Method: isLegalMove
         * Usage: medic.isLegalMove();
         * -----------------------------------
         * Returns true if and only if the desired movement is legal.
         */        
        bool isLegalMove(int distance) const noexcept;

        /*
         * Method: hasEnoughAmmo
         * Usage: medic.hasEnoughAmmo();
         * -----------------------------------
         * Returns true if and only if the medic has enough ammo to attack.
         */
        bool hasEnoughAmmo() const noexcept;

        /*
         * Method: attack
         * Usage: medic.attack(board, src_coords, dst_coords);
         * -----------------------------------
         * ASSUMES: src_coords and dst_coords are legal and contain
         * the corresponding character(*this) and the target.
         * 
         * If the character in dst_coords is on the same team as *this, 
         * heal him for an amount equal to the power of *this.
         * Otherwise, deal damage equals to the power of *this.
         * 
         * Possible Exceptions:
         * mtm::OutOfAmmo, mtm::IllegalTarget.
         */
        void attack(Matrix<std::shared_ptr<Character>>board, const GridPoint& src_coordinates , const GridPoint& dst_coordinates);
    };
};
#endif