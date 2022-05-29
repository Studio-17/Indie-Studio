/*
** EPITECH PROJECT, 2022
** B-CCP-400-PAR-4-1-indie-studio-martin.vanaud
** File description:
** Clock
*/

#ifndef CLOCK_HPP_
#define CLOCK_HPP_

#include <chrono>
#include <iostream>

using timePoint = std::chrono::time_point<std::chrono::system_clock>;

    class Clock
    {
    public:
        Clock() {};
        ~Clock() {};

        timePoint getClockStart()
        {
            return (_start);
        };
        timePoint getClockEnd()
        {
            return (_end);
        };

        void start()
        {
            _start = std::chrono::system_clock::now();
        };
        void restart()
        {
            _start = std::chrono::system_clock::now();
        };

        long long int getElapsedTime()
        {
            _end = std::chrono::system_clock::now();
            _elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start).count();

            return (_elapsedTime);
        };

    protected:
    private:
        timePoint _start;
        timePoint _end;
        long long int _elapsedTime;
    };

#endif /* !CLOCK_HPP_ */