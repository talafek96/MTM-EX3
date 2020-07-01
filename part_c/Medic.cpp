#include "Medic.h"

namespace mtm
{
    Medic::Medic(Team team, units_t health, units_t ammo, units_t range, units_t power) noexcept :
    Character(team, health, ammo, range, power) { }

    char Medic::getName() const noexcept
    {
        if(getTeam() == CPP)
        {
            return CPP_NAME;
        }
        return PYTHON_NAME;
    }

    void Medic::reload() noexcept
    {           
        ammo += RELOAD_AMMOUNT;
    }

    bool Medic::isInAttackRange(const GridPoint& src_coordinates , const GridPoint& dst_coordinates) const noexcept
    {
        int distance = GridPoint::distance(src_coordinates, dst_coordinates);
        if(distance > getRange())
        {
            return false;
        }
        return true;
    }

    bool Medic::isLegalMove(int distance) const noexcept
    {
        if (distance > MAX_MOVE_RANGE)
        {
            return false;
        }
        return true;
    }

    bool Medic::hasEnoughAmmo() const noexcept
    {
        if (ammo < AMMO_COST)
        {
            return false;
        }
        return true;
    }
 
    void Medic::attack(Matrix<std::shared_ptr<Character>>board, const GridPoint& src_coordinates , const GridPoint& dst_coordinates)
    {
        std::shared_ptr<Character> target_ptr = board(dst_coordinates.row, dst_coordinates.col);
        if(target_ptr != nullptr)
        {
            if((target_ptr->getTeam() != getTeam()) &&
            (!board(src_coordinates.row, src_coordinates.col)->hasEnoughAmmo()))
            {
                throw OutOfAmmo();
            }
        }
        else if(!board(src_coordinates.row, src_coordinates.col)->hasEnoughAmmo())
        {
            throw OutOfAmmo();
        }
        if(target_ptr == nullptr || 
        GridPoint::distance(src_coordinates, dst_coordinates) == 0)
        {
            throw IllegalTarget();
        }
        if(target_ptr->getTeam() != getTeam())
        {
            target_ptr->setHealth(target_ptr->getHealth() - getPower());
            ammo -= AMMO_COST;
        }
        else
        {
            target_ptr->setHealth(target_ptr->getHealth() + getPower());
        }
    }

    std::shared_ptr<Character> Medic::clone() const 
    {
        std::shared_ptr<Character> copy(new Medic(*this));
        return copy;
    }
};