#ifndef TEXTURE_H
#define TEXTURE_H
#include <stdlib.h>
#include <GL/gl.h>
#include <stdio.h>

class Texture
{
    public:
        Texture();
        virtual ~Texture();
        GLuint texture; //the array for our texture
        GLuint LoadTexture( const char * filename, int width, int height );
        void FreeTexture( GLuint texture );

    protected:

    private:
};

#endif // TEXTURE_H
