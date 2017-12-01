
#include <assert.h>
#include <iostream>
#include "lodepng.h"

#include <string>
#include <vector>
#include <map>
#include <queue>
#include <utility>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

typedef struct _data
{
    unsigned int width;
    unsigned int hight;
    unsigned int beginIndex;
    unsigned int endIndex;
} AREA;

int SaveAsBinaryFile(const string& inputFile, unsigned char* databuffer, const unsigned int width, const unsigned int hight, const unsigned int beginIndex, const unsigned int endIndex)
{
    assert(databuffer != NULL);
    assert(width != 0);
    assert(hight != 0);
    assert(endIndex != 0);

    const char* path = inputFile.c_str();

    AREA aera = {width, hight, beginIndex, endIndex};

    FILE* stream = fopen(path, "wb");
    if(stream == NULL) {
        printf("open file : %s failed ! \n", path);
        return -1;
    }

    if(-1 == fwrite(&aera,  sizeof(AREA), 1, stream)){
        printf("fwrite file : %s failed ! \n", path);
        if(-1 == fclose(stream)){
            printf("fclose file : %s failed ! \n", path);
            return -1;
        }
        return -1;
    }
    if(-1 == fwrite(databuffer+beginIndex,  endIndex-beginIndex+4, 1, stream)){
    //if(-1 == fwrite(databuffer,  width*hight*4, 1, stream)){
        printf("fwrite file : %s failed ! \n", path);
        if(-1 == fclose(stream)){
            printf("fclose file : %s failed ! \n", path);
            return -1;
        }
        return -1;
    }

    if(-1 == fclose(stream)){
        printf("fclose file : %s failed ! \n", path);
        return -1;
    }

    return 0;
}

int LodePNGImage(const string& inputFile, const string& outputFile)
{

    unsigned int l_width = 0;
    unsigned int l_height = 0;

    unsigned int beginIndex = 0;
    unsigned int endIndex = 0;

    std::vector<unsigned char> image;
    if(lodepng::decode(/* out */image, /* out */l_width, /* out */l_height, inputFile, LCT_RGBA, 8) != 0){
        printf(" open file : %s fail\n", inputFile.c_str());
        return -1;
    }

    beginIndex = l_height*l_width*4;

    //printf(" inputFile : %s, l_width = %u, l_height = %u image.size() = %d\n", inputFile.c_str(), l_width, l_height, image.size());

    if(!image.empty()){
        unsigned char* buffer = (unsigned char*)malloc(l_width * l_height * 4);   // free by class : ColorBlock
        if(NULL == buffer) {
            printf(" malloc failed !\n");
            return -1;
        }

        memcpy(buffer, &image[0], image.size()*sizeof(unsigned char)); //dangerous but safe

        //printf(" open file1 : %s fail\n", inputFile.c_str());

        if(inputFile.find("_0") != std::string::npos){
            for(int i = 0; i < l_width * l_height * 4;){
                if(buffer[i+3] != 0) {
                    buffer[i] = 87;
                    buffer[i+1] = 87;
                    buffer[i+2] = 87;
                    buffer[i+3] = 255;
                }
                i += 4;
            }
        } else if(inputFile.find("_front_") != std::string::npos || inputFile.find("_rear_") != std::string::npos){
            for(int i = 0; i < l_width * l_height * 4;){
                if(buffer[i] == 255 && buffer[i+1] == 255 && buffer[i+2] == 255){
                    buffer[i] = 0;
                    buffer[i+1] = 0;
                    buffer[i+2] = 0;
                    buffer[i+3] = 0;
                }
                i += 4;
            }
        }


        for(int index = 0; index < l_width * l_height * 4;)
        {
            if(buffer[index+3]!=0)
            {
                beginIndex = index;
                break;
            }
            index += 4;
        }
        for(int index = l_width * l_height * 4 - 1; index > 0;)
        {
            if(buffer[index]!=0)
            {
                endIndex = index - 3;
                break;
            }
            index -= 4;
        }



        //printf("ValidErea : %s,  beginIndex = %u, endIndex = %u\n", inputFile.c_str(), beginIndex, endIndex);

        SaveAsBinaryFile(outputFile, buffer, l_width, l_height, beginIndex, endIndex);

        free(buffer);

        return 0;
    }else{
        return -1;
    }

    return -1;
}

int main(int argc, char* args[])
{
    //arg[1] *.png
    //arg[2] *.PngRes
    return LodePNGImage(args[1], args[2]);
}