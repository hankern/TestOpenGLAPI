QT += core
QT += gui

CONFIG += c++11

TARGET = HOpenGL
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    math_3d.cpp \
    ogldev_util.cpp \
    camera.cpp \
    pipeline.cpp \
    texture.cpp \
    lighting_technique.cpp \
    technique.cpp \
    glut_backend.cpp \
    mesh.cpp \
    shadow_map_fbo.cpp \
    shadow_map_technique.cpp \
    skybox.cpp \
    skybox_technique.cpp \
    cubemap_texture.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS+=-L"D:/FreeGlut_Glew/lib" -lfreeglut -lglew32
LIBS+=-L"D:\Program Files\ImageMagick-6.2.7-Q16\lib" -lCORE_RL_Magick++_
LIBS+=-L"D:/assimp" -lassimp-vc140-mtd


INCLUDEPATH+=D:\FreeGlut_Glew\include
INCLUDEPATH+=D:\assimp\include
INCLUDEPATH+="D:\Program Files\ImageMagick-6.2.7-Q16\include"

HEADERS += \
    ogldev_math_3d.h \
#    ogldev_util.h
    camera.h \
    pipeline.h \
    texture.h \
    vector3.h \
    math_3d.h \
    ogldev_util.h \
    util.h \
    lighting_technique.h \
    technique.h \
    glut_backend.h \
    mesh.h \
    shadow_map_fbo.h \
    shadow_map_technique.h \
    skybox.h \
    skybox_technique.h \
    cubemap_texture.h
