#ifndef HUD_H
#define HUD_H

class HUD
{
    public:
        HUD();
        bool shot ;
        void render(bool);
        void enable2D();
        void disable2D();
        void drawHUD();
        virtual ~HUD();
    protected:
    private:
};
#endif // HUD_H
