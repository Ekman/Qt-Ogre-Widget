#ifndef QT_OGRE_PREPROCESSOR_H
#define QT_OGRE_PREPROCESSOR_H

// stl
#include <stdexcept>

#pragma GCC diagnostic ignored "-Wall"
#include <Ogre.h>
#include <QtWidgets>
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
#include <QX11Info>
#endif
#pragma GCC diagnostic pop

typedef short int sint;
typedef unsigned short int usint;
typedef unsigned int uint;
typedef long int lint;
typedef unsigned long int ulint;
typedef unsigned char uchar;

#endif // PREPROCESSOR_H
