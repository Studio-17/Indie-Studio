/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** WindowError
*/

#ifndef WINDOWERROR_HPP_
    #define WINDOWERROR_HPP_

    #include "Errors.hpp"

namespace Error {
    class WindowError : public Errors {
        public:
            WindowError(std::string const &message) throw();
            virtual ~WindowError() throw();
    };
}

#endif /* !WINDOWERROR_HPP_ */
