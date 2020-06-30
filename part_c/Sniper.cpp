#include "Sniper.h"

namespace mtm
{
    Sniper::Sniper(Team team, units_t health, units_t ammo, units_t range, units_t power) noexcept :
    Character(team, health, ammo, range, power), combo_attack_count(0) { }

    char Sniper::getName() const noexcept
    {
        if(getTeam() == CPP)
        {
            return CPP_NAME;
        }
        return PYTHON_NAME;
    }

    void Sniper::reload() noexcept
    {           
        ammo += RELOAD_AMMOUNT;
    }

    bool Sniper::isInAttackRange(int distance) const noexcept
    {
        if(distance > getRange() || distance < static_cast<int>(std::ceil(static_cast<double>(getRange())/2)))
        {
            return false;
        }
        return true;
    }

    bool Sniper::isLegalMove(int distance) const noexcept
    {
        if (distance > MAX_MOVE_RANGE)
        {
            return false;
        }
        return true;
    }

    bool Sniper::hasEnoughAmmo() const noexcept
    {
        if (ammo < AMMO_COST)
        {
            return false;
        }
        return true;
    }

    void Sniper::attack(Matrix<std::shared_ptr<Character>>board, const GridPoint src_coordinates , const GridPoint dst_coordinates)
    {
        if(!board(src_coordinates.row, src_coordinates.col)->hasEnoughAmmo())
        {
            throw OutOfAmmo();
        }
        if(board(dst_coordinates.row, dst_coordinates.col)->getTeam() == getTeam())
        {
            throw IllegalTarget();
        }
        units_t damage = combo_attack_count++ ==(MAX_COMBO - 1)? getPower()*CRITICAL_MULTIPLIER : getPower();
        board(dst_coordinates.row, dst_coordinates.col)->setHealth(getHealth() - damage);
        combo_attack_count %= MAX_COMBO;
    }

    std::shared_ptr<Character> Sniper::clone() const 
    {
        std::shared_ptr<Character> copy(new Sniper(*this));
        return copy;
    }
};
