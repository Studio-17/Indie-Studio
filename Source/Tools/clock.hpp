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

using timePoint = std::chrono::time_point<std::chrono::system_clock>; ///< Time point type

    /**
     * @brief Clock class to handle time management throughout the game
     *
     */
    class Clock
    {
    public:
        /**
         * @brief Construct a new Clock object
         *
         */
        Clock() {};
        /**
         * @brief Destroy the Clock object
         *
         */
        ~Clock() {};

        /**
         * @brief Get the Clock Start object
         *
         * @return timePoint
         */
        timePoint getClockStart()
        {
            return (_start);
        };
        /**
         * @brief Get the Clock End object
         *
         * @return timePoint
         */
        timePoint getClockEnd()
        {
            return (_end);
        };

        /**
         * @brief Start the clock
         *
         */
        void start()
        {
            _start = std::chrono::system_clock::now();
            _isPaused = false;
        };
        /**
         * @brief Restart the clock
         *
         */
        void restart()
        {
            _start = std::chrono::system_clock::now();
            _isPaused = false;
        };

        /**
         * @brief Get the Elapsed Time object
         *
         * @return long long int
         */
        long long int getElapsedTime()
        {
            _end = std::chrono::system_clock::now();
            _elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start).count();

            return (!_isPaused ? _elapsedTime - _elapsedTimePause : _tmpElapsedTime);
        };

        /**
         * @brief Pause the clock
         *
         */
        void pause()
        {
            _tmpElapsedTime = getElapsedTime();
            _isPaused = true;
            _startPause = std::chrono::system_clock::now();
        }

        /**
         * @brief Resume the clock
         *
         */
        void unpause()
        {
            _endPause = std::chrono::system_clock::now();
            _elapsedTimePause += std::chrono::duration_cast<std::chrono::milliseconds>(_endPause - _startPause).count();
            _isPaused = false;
        }

        /**
         * @brief Get if the time is paused of not
         *
         * @return true
         * @return false
         */
        bool isPaused()
        {
            return _isPaused;
        }

        /**
         * @brief Reset the clock
         *
         */
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
        timePoint _start; ///< Start time point
        timePoint _end; ///< End time point
        timePoint _startPause; ///< Start pause time point
        timePoint _endPause; ///< End pause time point
        long long int _elapsedTimePause = 0; ///< Elapsed time pause
        long long int _elapsedTime = 0; ///< Elapsed time
        long long int _tmpElapsedTime = 0; ///< Temporary elapsed time
        bool _isPaused = false; ///< Is paused
};

#endif /* !CLOCK_HPP_ */