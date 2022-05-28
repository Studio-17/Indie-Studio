/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** IAudio
*/

#ifndef IAUDIO_HPP_
    #define IAUDIO_HPP_

class IAudio {
    public:
        virtual ~IAudio() = default;

        virtual void play() = 0;
        virtual void stop() = 0;
        virtual void pause() = 0;
        virtual void resume() = 0;

        virtual bool isPlaying() const = 0;
        virtual void setVolume(float volume) = 0;

    protected:
    private:
};

#endif /* !IAUDIO_HPP_ */
