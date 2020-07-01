#include "Character.h"

namespace mtm
{
    Character::Character(Team team, units_t health, units_t ammo, units_t range, units_t power) noexcept :
    range(range), power(power), team(team), health(health), ammo(ammo) { }

    units_t Character::getHealth() const noexcept
    {
        return health;
    }

    void Character::setHealth(units_t new_health)
    {
        health = new_health;
    }

    Team Character::getTeam() const noexcept
    {
        return team;
    }

    units_t Character::getRange() const
    {
        return range;
    }
    
    units_t Character::getPower() const
    {
        return power;
    }
}
