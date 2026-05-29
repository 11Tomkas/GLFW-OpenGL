#ifndef DELTA_HPP
#define DELTA_HPP

class Delta
{
    public:
        Delta();
        Delta(const Delta&) = delete;
        Delta(Delta&&) = delete;
        ~Delta() = default;
        Delta& operator=(const Delta&) = delete;
        Delta& operator=(Delta&&) = delete;

        void update();
        float time() const;
    private:
        float m_time;
};

extern Delta delta;

#endif