#include "Soldier.h"

namespace mtm
{
    Soldier::Soldier(Team team, units_t health, units_t ammo, units_t range, units_t power) noexcept :
    Character(team, health, ammo, range, power) { }

    char Soldier::getName() const noexcept
    {
        if(getTeam() == CPP)
        {
            return CPP_NAME;
        }
        return PYTHON_NAME;
    }

    void Soldier::reload() noexcept
    {
        ammo += RELOAD_AMMOUNT;
    }

    bool Soldier::isInAttackRange(const GridPoint& src_coordinates , const GridPoint& dst_coordinates) const noexcept
    {
        int distance = GridPoint::distance(src_coordinates, dst_coordinates);
        if(distance > getRange())
        {
            return false;
        }
        return true;
    }

    bool Soldier::isLegalMove(int distance) const noexcept
    {
        if(distance > MAX_MOVE_RANGE)
        {
            return false;
        }
        return true;
    }

    bool Soldier::hasEnoughAmmo() const noexcept
    {
        if (ammo < AMMO_COST)
        {
            return false;
        }
        return true;
    }

    void Soldier::attack(Matrix<std::shared_ptr<Character>>board, const GridPoint& src_coordinates , const GridPoint& dst_coordinates)
    {
        if(!board(src_coordinates.row, src_coordinates.col)->hasEnoughAmmo())
        {
            throw OutOfAmmo();
        }
        if((src_coordinates.col != dst_coordinates.col) && (src_coordinates.row != dst_coordinates.row))
        {
            throw IllegalTarget();
        }
        int distance;
        std::shared_ptr<Character> cell;
        int area_of_effect = std::ceil(static_cast<double>(getRange())/COLATERAL_RANGE);
        units_t area_of_effect_damage = std::ceil(static_cast<double>(getPower())/COLATERAL_DAMAGE);
        for(int row = 0; row < board.height(); row++)
        {
            for(int col = 0; col < board.width(); col++)
            {
                cell = board(row, col);
                distance = GridPoint::distance(GridPoint(row, col), dst_coordinates);
                if(distance <= area_of_effect) //Checks to see if the cell is in the area of effect
                {
                    if(cell != nullptr && cell->getTeam() != getTeam()) //Makes sure that the target is an enemy
                    {
                        switch(distance)
                        {
                            case 0: //Means that the target is exactly in the dst_coordinates
                            cell->setHealth(cell->getHealth() - getPower());
                            break;

                            default: //Means that the target is in the area of effect, but not center
                            cell->setHealth(cell->getHealth() - area_of_effect_damage);
                            break;
                        }
                    }
                }
            }
        }
        ammo -= AMMO_COST; //Reduce ammo
    }

    std::shared_ptr<Character> Soldier::clone() const 
    {
        std::shared_ptr<Character> copy(new Soldier(*this));
        return copy;
    }
}
