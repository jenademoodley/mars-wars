#ifndef SUNLIGHT_H
#define SUNLIGHT_H

class Sunlight
{
    public:
        Sunlight(float, float , float);
        Sunlight();
        void render(float, float , float);
        virtual ~Sunlight();
    protected:
    private:
};

#endif // SUNLIGHT_H
