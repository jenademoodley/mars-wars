#ifndef READSOUNDFILENAMES_H
#define READSOUNDFILENAMES_H
#include "ReadSoundFileNames.h"
#include <Windows.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
using namespace std;

class ReadSoundFileNames
{
    public:
        ReadSoundFileNames(string folder);
        virtual ~ReadSoundFileNames();
        void shuffleNames();
        vector<string> getNames();
    protected:
    private:
        vector<string> names;
};
#endif // READSOUNDFILENAMES_H
