#ifndef CHARACTER_INC
#define CHARACTER_INC
// Includes
#include <iostream>
#include <memory>
#include "Matrix.h"
#include "Auxiliaries.h"
#include "Exceptions.h"
//---------

namespace mtm
{
    class Character
    {
    private:
        /*********************************/
        /*        Private Section        */
        /*********************************/
        /* Instance variables */
        units_t range;
        units_t power;
        Team team;
        Character& operator=(const Character& other) = delete;
    protected:
        /*********************************/
        /*       Protected Section       */
        /*********************************/
        units_t health;
        units_t ammo;

        units_t getRange() const;
        units_t getPower() const;
    public:
        /**************************************/
        /*     C'tors and D'tors section      */
        /**************************************/
        explicit Character(Team team, units_t health, units_t ammo, units_t range, units_t power) noexcept;
        Character(const Character& other) = default;
        virtual ~Character() = default;
        

        /****************************************/
        /*        Getter&Setter methods         */
        /****************************************/
        /*
         * Method: getName
         * Usage: char name = character.getName();
         * -----------------------------------
         * Returns the representation of the character on the game board as a char.
         */
        virtual char getName() const = 0;

        /*
         * Method: getTeam
         * Usage: Team team = character.getTeam();
         * -----------------------------------
         * Returns the team of the character.
         */
        Team getTeam() const noexcept;

        /*
         * Method: getHealth
         * Usage: units_t health = character.getHealth();
         * -----------------------------------
         * Returns the current health of the character.
         */
        units_t getHealth() const noexcept;

        /*
         * Method: setHealth
         * Usage: character.setHealth(new_health);
         * -----------------------------------
         * Sets the health of character to new_health.
         */
        void setHealth(units_t new_health);

        /**************************************/
        /*        Pure virtual section        */
        /**************************************/
        /*
         * Method: clone
         * Usage: shared_ptr<Character> copied_character = character.clone();
         * -----------------------------------
         * Returns a shared_ptr to a copy of a copied character.
         */
        virtual std::shared_ptr<Character> clone() const = 0;

        //To be explained in each character header file:
        virtual void reload() noexcept = 0;
        virtual bool isInAttackRange(int distance) const noexcept = 0;
        virtual bool isLegalMove(int distance) const noexcept = 0;
        virtual bool hasEnoughAmmo() const noexcept = 0;
        virtual void attack(Matrix<std::shared_ptr<Character>>board, const GridPoint src_coordinates , const GridPoint dst_coordinates) = 0;
    };
};
#endif