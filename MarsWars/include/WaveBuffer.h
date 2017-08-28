#ifndef WAVEBUFFER_H
#define WAVEBUFFER_H
#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <fstream>
#include <conio.h>

class WaveBuffer
{
    public:
        WaveBuffer(char * filename);
        ~WaveBuffer();
        void play(bool async=true);
        bool isok();

    private:
        char * buffer;
        bool ok;
        HINSTANCE HInstance;
};
#endif // WAVE_H

