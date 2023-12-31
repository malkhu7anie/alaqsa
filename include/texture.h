#ifndef TEXTURE_H
#define TEXTURE_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/glu.h>
#include <utils.h>

class Texture { 
public:
    Texture();
    Texture(const std::string& filename);
    void load(const std::string&, int = {}, int = {}, int = {});
    void bind();
    void unbind();

    unsigned int id;
};

#endif
