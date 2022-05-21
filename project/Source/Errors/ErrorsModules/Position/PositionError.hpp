/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** PositionError
*/

#ifndef POSITIONERROR_HPP_
    #define POSITIONERROR_HPP_

    #include "../../Errors.hpp"

class PositionError : public Errors {
    public:
        PositionError(std::ostream &os, std::string const &message) throw();
        virtual ~PositionError() throw();

    protected:
    private:
};


namespace Error {
    class FilesystemError : public Errors {
        public:
            FilesystemError(std::ostream &os, std::string const &message) throw();
            virtual ~FilesystemError() throw();
    };
}

#endif /* !POSITIONERROR_HPP_ */
