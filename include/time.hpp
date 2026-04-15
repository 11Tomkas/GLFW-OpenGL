#ifndef TIME_HPP
#define TIME_HPP

class Time
{
    public:
        Time();
        Time(const Time&) = delete;
        Time(Time&&) = delete;
        ~Time() = default;
        Time& operator=(const Time&) = delete;
        Time& operator=(Time&&) = delete;

        void updateDelta();
        float delta();
    private:
        float m_delta;
};

extern Time gTime;

#endif