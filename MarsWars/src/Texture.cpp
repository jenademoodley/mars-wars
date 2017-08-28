#include "Texture.h"
#include <iostream>
#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <stdio.h>
Texture::Texture()
{
    //ctor
}

Texture::~Texture()
{
    //dtor
}


GLuint Texture::LoadTexture( const char * filename, int width, int height )
{
    GLuint texture;
    unsigned char * data;
    FILE * file;

    //The following code will read in our RAW file
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;
    data = (unsigned char *)malloc( width * height * 3 );
    fread( data, width * height * 1, 1, file );
    fclose( file );

    glGenTextures( 1, &texture ); //generate the texturewith the loaded data
    glBindTexture( GL_TEXTURE_2D, texture ); //bind thetexture to it’s array
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE ); //set texture environment parameters

    //here we are setting what textures to use and when. The MIN filter is which quality to show
    //when the texture is near the view, and the MAG filter iswhich quality to show when the texture
    //is far from the view.

    //The qualities are (in order from worst to best)
    //GL_NEAREST
    //GL_LINEAR
    //GL_LINEAR_MIPMAP_NEAREST
    //GL_LINEAR_MIPMAP_LINEAR

    //And if you go and use extensions, you can use Anisotropicfiltering textures which are of an
    //even better quality, but this will do for now.
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);

    //Generate the texture with mipmaps
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
    free( data ); //free the texture
    return texture; //return whether it was successfull
    }

    void Texture::FreeTexture( GLuint texture )
    {
    glDeleteTextures( 1, &texture );
    }
