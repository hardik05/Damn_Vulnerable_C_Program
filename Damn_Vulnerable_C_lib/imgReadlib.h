#ifndef IMAGEREAD_H
#define IMAGEREAD_H

struct Image
{
    char header[4];
    int width;
    int height;
    char data[10];
};

int ProcessImage(char* filename);

#endif

