#include <iostream>
#include "Exceptions.h"

namespace mtm
{
    /*********************************/
    /*         GameException         */
    /*********************************/
    GameException::GameException() :
    game_error("A game related error has occurred: "), exception_name("Unknown Error") { }
    GameException::GameException(const std::string error) :
    game_error("A game related error has occurred: "), exception_name(error) { }
    
    /*********************************/
    /*        IllegalArgument        */
    /*********************************/
    IllegalArgument::IllegalArgument() :
    GameException("IllegalArgument"), message(game_error += exception_name) { }
    const char* IllegalArgument::what() const noexcept
    {
        return message.c_str();
    }

    /*********************************/
    /*          IllegalCell          */
    /*********************************/
    IllegalCell::IllegalCell() :
    GameException("IllegalCell"), message(game_error += exception_name) { }
    const char* IllegalCell::what() const noexcept 
    {
       return message.c_str();
    }  

    /*********************************/
    /*           CellEmpty           */
    /*********************************/
    CellEmpty::CellEmpty() :
    GameException("CellEmpty"), message(game_error += exception_name) { }
    const char* CellEmpty::what() const noexcept 
    {
        return message.c_str();
    }    
    
    /*********************************/
    /*           MoveTooFar          */
    /*********************************/
    MoveTooFar::MoveTooFar() :
    GameException("MoveTooFar"), message(game_error += exception_name) { }
    const char* MoveTooFar::what() const noexcept
    {
        return message.c_str();
    }    
    
    /*********************************/
    /*         CellOccupied          */
    /*********************************/
    CellOccupied::CellOccupied() :
    GameException("CellOccupied"), message(game_error += exception_name) { }
    const char* CellOccupied::what() const noexcept
    {
        return message.c_str();
    }

    /*********************************/
    /*           OutOfRange          */
    /*********************************/
    OutOfRange::OutOfRange() :
    GameException("OutOfRange"), message(game_error += exception_name) { }
    const char* OutOfRange::what() const noexcept 
    {
        return message.c_str();
    }
    
    /*********************************/
    /*           OutOfAmmo           */
    /*********************************/
    OutOfAmmo::OutOfAmmo() :
    GameException("OutOfAmmo"), message(game_error += exception_name) { }
    const char* OutOfAmmo::what() const noexcept
    {
        return message.c_str();
    }
    
    /*********************************/
    /*         IllegalTarget         */
    /*********************************/
    IllegalTarget::IllegalTarget() :
    GameException("IllegalTarget"), message(game_error += exception_name) { }
    const char* IllegalTarget::what() const noexcept
    {
        return message.c_str();
    }
}