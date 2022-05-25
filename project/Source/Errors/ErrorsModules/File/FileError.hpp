/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** FileError
*/

#ifndef FILEERROR_HPP_
    #define FILEERROR_HPP_

    #include "Errors.hpp"
namespace Error {
    class FileError : public Errors {
        public:
            FileError(std::string const &message) throw();
            virtual ~FileError() throw();
    };
}

#endif /* !FILEERROR_HPP_ */
