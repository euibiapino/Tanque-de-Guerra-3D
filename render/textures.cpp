#include "textures.h"
#include <SOIL/SOIL.h>
#include <stdexcept>

static GLuint texturas[NUM_TEXTURES];

void configurarParametrosTextura(GLuint texturaID) {
    glBindTexture(GL_TEXTURE_2D, texturaID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


bool carregarTextura()
{
    try
    {

        texturas[TEXTURA_TERRENO] = SOIL_load_OGL_texture(
            "assets/grama.jpg",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
            configurarParametrosTextura(texturas[TEXTURA_TERRENO]);

        texturas[TEXTURA_CORPO] = SOIL_load_OGL_texture(
            "assets/militar.jpg",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
            configurarParametrosTextura(texturas[TEXTURA_CORPO]);


        texturas[TEXTURA_TORRETA] = SOIL_load_OGL_texture(
            "assets/militar.jpg",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
            configurarParametrosTextura(texturas[TEXTURA_TORRETA]);

        texturas[TEXTURA_CANO] = SOIL_load_OGL_texture(
            "assets/militar.jpg",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
            configurarParametrosTextura(texturas[TEXTURA_CANO]);

        texturas[TEXTURA_ESTEIRA] = SOIL_load_OGL_texture(
            "assets/esteira.jpg",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
            configurarParametrosTextura(texturas[TEXTURA_ESTEIRA]);

        for (int i = 0; i < NUM_TEXTURES; i++)
        {
            if (texturas[i] == 0)
            {
                throw std::runtime_error("Erro ao carregar textura");
            }
        }

        return true;
    }
    catch (...)
    {
        liberarTextura();
        return false;
    }
}

GLuint obterTextura(textureType tipo)
{
    if (tipo >= NUM_TEXTURES)
        return 0;
    return texturas[tipo];
}

void liberarTextura()
{
    for (int i = 0; i < NUM_TEXTURES; i++)
    {
        if (texturas[i])
        {
            glDeleteTextures(1, &texturas[i]);
            texturas[i] = 0;
        }
    }
}