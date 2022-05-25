/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** PositionError
*/

#ifndef POSITIONERROR_HPP_
    #define POSITIONERROR_HPP_

    #include "Errors.hpp"

namespace Error {
    class FileError : public Errors {
        public:
            FileError(std::string const &message) throw();
            virtual ~FileError() throw();
    };
}

#endif /* !POSITIONERROR_HPP_ */
