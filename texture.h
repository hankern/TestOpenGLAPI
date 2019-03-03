#ifndef TEXTURE_H
#define	TEXTURE_H

#include <string>

#include <GL/glew.h>
#include <QImage>
//#include <ImageMagick/Magick++.h>
#include <Magick++.h>

class Texture
{
public:
    Texture(GLenum TextureTarget, const std::string& FileName);

    bool Load();

    void Bind(GLenum TextureUnit);

private:
    std::string m_fileName;
    GLenum m_textureTarget;
    GLuint m_textureObj;
    //QImage* m_pImage;
    Magick::Image* m_pImage;
    Magick::Blob m_blob;
};


#endif	/* TEXTURE_H */

