/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** AUDIOERROR
*/

#ifndef AUDIOERROR_HPP_
    #define AUDIOERROR_HPP_

    #include "Errors.hpp"

namespace Error {
    class AudioError : public Errors {
        public:
            AudioError(std::string const &message) throw();
            virtual ~AudioError() throw();
    };
}

#endif /* !AUDIOERROR_HPP_ */
