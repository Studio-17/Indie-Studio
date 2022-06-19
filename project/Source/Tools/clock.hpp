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
            _isPaused = false;
        };
        void restart()
        {
            _start = std::chrono::system_clock::now();
            _isPaused = false;
        };

        long long int getElapsedTime()
        {
            _end = std::chrono::system_clock::now();
            _elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start).count();

            return (!_isPaused ? _elapsedTime - _elapsedTimePause : _tmpElapsedTime);
        };

        void pause()
        {
            _tmpElapsedTime = getElapsedTime();
            _isPaused = true;
            _startPause = std::chrono::system_clock::now();
        }

        void unpause()
        {
            _endPause = std::chrono::system_clock::now();
            _elapsedTimePause += std::chrono::duration_cast<std::chrono::milliseconds>(_endPause - _startPause).count();
            _isPaused = false;
        }

        bool isPaused()
        {
            return _isPaused;
        }

        void reset()
        {
            _start = std::chrono::system_clock::now();
            _end = std::chrono::system_clock::now();
            _startPause = std::chrono::system_clock::now();
            _endPause = std::chrono::system_clock::now();
            _isPaused = false;
            _elapsedTime = 0;
            _elapsedTimePause = 0;
            _tmpElapsedTime = 0;
        }

    protected:
    private:
        timePoint _start;
        timePoint _end;
        timePoint _startPause;
        timePoint _endPause;
        long long int _elapsedTimePause = 0;
        long long int _elapsedTime = 0;
        long long int _tmpElapsedTime = 0;
        bool _isPaused = false;
    };

#endif /* !CLOCK_HPP_ */