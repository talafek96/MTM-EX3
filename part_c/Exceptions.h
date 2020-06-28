#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <iostream>

namespace mtm
{
    class Exception : public std::exception { };
    class GameException : public Exception
    {
    protected:
        std::string game_error;
        std::string exception_name;
    public:
        GameException();
        GameException(const std::string error);
        virtual ~GameException();
    };

    class IllegalArgument : public GameException
    { 
        std::string message;
    public:
        IllegalArgument();
        ~IllegalArgument() = default;
        const char* what() const noexcept override;
    };

    class IllegalCell : public GameException 
    { 
        std::string message;
    public:
        IllegalCell();
        ~IllegalCell() = default;
        const char* what() const noexcept override;

    };

    class CellEmpty : public GameException 
    { 
        std::string message;
    public:
        CellEmpty();
        ~CellEmpty() = default; 
        const char* what() const noexcept override;
    };

    class MoveTooFar : public GameException 
    { 
        std::string message;
    public:
        MoveTooFar();
        ~MoveTooFar() = default;
        const char* what() const noexcept override;
    };

    class CellOccupied : public GameException 
    { 
        std::string message;
    public:
        CellOccupied();
        ~CellOccupied() = default;
        const char* what() const noexcept override;
    };

    class OutOfRange : public GameException 
    { 
        std::string message;
    public:
        OutOfRange();
        ~OutOfRange() = default;
        const char* what() const noexcept override;
    };

    class OutOfAmmo : public GameException 
    { 
        std::string message;
    public:
        OutOfAmmo();
        ~OutOfAmmo() = default;
        const char* what() const noexcept override;
    };

    class IllegalTarget : public GameException 
    { 
        std::string message;
    public:
        IllegalTarget();
        ~IllegalTarget() = default;
        const char* what() const noexcept override;
    };
};
#endif