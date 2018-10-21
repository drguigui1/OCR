#include "Network.h"

#ifndef IMAGETRAINING_H
#define IMAGETRAINING_H

typedef enum ImageType{Train, Test}ImageType; 

StoreMatrix ImageParsing(ImageType type);

#endif