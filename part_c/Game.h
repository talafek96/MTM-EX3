#ifndef GAME_INC
#define GAME_INC
// Includes
#include <iostream>
#include "Matrix.h"
#include "Auxiliaries.h"
#include "Exceptions.h"
#include <memory>
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
        Matrix<std::shared_ptr<Character>> board;
    public:
        /**************************************/
        /*     C'tors amd D'tors section      */
        /**************************************/
        Game(int height, int width);
        Game(const Game& other);
        ~Game();

        /**************************************/
        /*     Method definition section      */
        /**************************************/
        void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);
        void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
        void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
        void reload(const GridPoint & coordinates);
        bool isOver(Team* winningTeam=NULL) const;

        /**************************************/
        /*    Function definition section     */
        /**************************************/
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team, 
                                    units_t health, units_t ammo, units_t range, units_t power);

        /**************************************/
        /*    Operator definition section     */
        /**************************************/
        Game& operator=(const Game& other);

    };
    std::ostream& operator<<(std::ostream& out, Game board);
};
#endif