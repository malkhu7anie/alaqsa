#include <GL/glu.h>
#include <utils.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

class Texture { 
public:
    Texture(const std::string& filename);
    void load(const std::string& filename, 
            int width = {}, int height = {}, int n = {});
    void bind();
    void unbind();

    unsigned int id;
};
