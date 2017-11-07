#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include "AGraphic.h"
#include "PAS/GraphicCore/lodepng.h"


#define PNG01_PATH "/usr/bin/res/pdc_focus_warning.png"
//#define PNG02_PATH "apa_reverse_arrow_fill_16.png"
#define PNG02_PATH "/usr/bin/res/pdc_front_right_inside_0.png"
#define PNG03_PATH "/usr/bin/res/pdc_malfunction.png"
//#define PNG04_PATH "pdc_trailer.png"
#define PNG04_PATH "/usr/bin/res/pdc_front_right_inside_1.png"

#define PNG05_PATH "/usr/bin/res/apa_reverse_arrow_fill_16.png"
#define PNG06_PATH "/usr/bin/res/apa_stop.png"
#define PNG07_PATH "/usr/bin/res/apa_cancel.png"
//#define PNG08_PATH "apa_caution.png"
#define PNG08_PATH "/usr/bin/res/apa_forward_arrow_fill_16.png"


using namespace Harman::Adas::AFramework::AGraphic;

static CAdasGraphic *graphic1 = NULL;

unsigned char* LodePNGImage(std::string filename, unsigned int &width, unsigned int &height)
{
#if 0
	unsigned error;
	//unsigned char* image;
	char* image;
	unsigned w, h;

	error = lodepng_decode32_file(&image, w, h, filename);
	if (error) printf("error %u: %s\n", error, lodepng_error_text(error));

	/*use image here*/

	//free(image);

	return image;
#endif
	unsigned w, h;
	unsigned char *buffer = NULL;
	unsigned char *text = NULL;
	std::vector<unsigned char> image; //the raw pixels
	unsigned error = lodepng::decode(image, w, h, filename, LCT_RGBA, 8);
	printf("   [%s, %d] error = %d\n", __FUNCTION__, __LINE__, error);
	if (error != 0)
	{
		printf("   [%s, %d] open file fail\n", __FUNCTION__, __LINE__);
		return NULL;
	}

	buffer = new unsigned char[w*h*4];
	memset(buffer, 0, w*h*4);
	width = w;
	height = h;
    for (int i=0;i<height;i++)
    {
        for (int j=0;j<width;j++)
        {
            buffer[4 * i*width + 4 * j]     = (unsigned char)image[4 * i*width + 4 * j];
			buffer[4 * i*width + 4 * j + 1] = (unsigned char)image[4 * i*width + 4 * j + 1];
			buffer[4 * i*width + 4 * j + 2] = (unsigned char)image[4 * i*width + 4 * j + 2];
			buffer[4 * i*width + 4 * j + 3] = (unsigned char)image[4 * i*width + 4 * j + 3];
        }
    }

	//return buffer;

	/*std::vector<char> tex;
	int k = 0;
	while(k < width*height*4)
	{
		if(buffer[k+3]!=0)
		{
			tex.pushback(buffer[k]);
			tex.pushback(buffer[k+1]);
			tex.pushback(buffer[k+2]);
			tex.pushback(buffer[k+3]);
		}
		k = k+4;
	}*/
	int k = 0;
	/*unsigned int len = 0;
	while(k < width*height*4)
	{
		//if(buffer[k+3] != 0)
		{
			len += 4;
		}
		k += 4;
	}
	printf("   [%s, %d] len = %d\n", __FUNCTION__, __LINE__, len);*/

	text = new unsigned char[w*h*4];
	memset(text, 0, w*h*4);
	k = 0;
	int index = 0;
	while(k < width*height*4)
	{
		if(buffer[k+3] != 0)
		{
			text[k]   = buffer[k];
			text[k+1] = buffer[k+1];
			text[k+2] = buffer[k+2];
			text[k+3] = buffer[k+3];
			//index += 4;
		}
		else
		{
			//text[k]   = 0xFF;
			//text[k+1] = 0xFF;
			//text[k+2] = 0xFF;
			//text[k+3] = 0xFF;
			//text[k]   = buffer[k];
			//text[k+1] = buffer[k+1];
			//text[k+2] = buffer[k+2];
			//text[k+3] = buffer[k+3];
		}
		k += 4;
	}
	delete buffer;
	buffer = NULL;

	//printf("   [%s, %d] %x, %x, %x, %x\n", __FUNCTION__, __LINE__, text[0], text[1], text[2], text[3]);
	return text;
}

void * func1(void *arg)
{
    int num=*(int *)arg;
    printf("num is %d\n",num);

	tsurfaceInfo surfaceInfo;
	tsurfaceList surfaceArry;
	unsigned int width, height;
	trenderData renderData1;
	tbufInfo bufferInfo1;
	tbufInfo bufferInfo2;
	tbufInfo bufferInfo3;
	renderData1.surfaceID = 1;


	surfaceInfo.surfaceName = "Graphic_1";
	surfaceInfo.surfaceId = 1;
	surfaceInfo.moduleType = MODULE_PAS;
	surfaceInfo.bActiveEGL = TRUE;
	surfaceInfo.viewPos.width = 1024;//width;
	surfaceInfo.viewPos.height = 600;//height;
	surfaceInfo.viewPos.viewPos.x = 0;
	surfaceInfo.viewPos.viewPos.y = 0;
	surfaceArry.push_back(surfaceInfo);
	graphic1->createSurface(surfaceArry);

	unsigned char *buffer1 = LodePNGImage(PNG01_PATH, width, height);
	bufferInfo1.buffer = buffer1;
	bufferInfo1.width = width;
	bufferInfo1.heigth = height;
	bufferInfo1.bRender = TRUE;
	renderData1.bufferMap.insert(make_pair(ADAS_PAS_CAR_STATUS, bufferInfo1));
	unsigned char *buffer2 = LodePNGImage(PNG02_PATH, width, height);
	bufferInfo2.buffer = buffer2;
	bufferInfo2.width = width;
	bufferInfo2.heigth = height;
	bufferInfo2.bRender = TRUE;
	renderData1.bufferMap.insert(make_pair(ADAS_PAS_RADAR_STATUS, bufferInfo2));
	unsigned char *buffer3 = LodePNGImage(PNG03_PATH, width, height);
	bufferInfo3.buffer = buffer3;
	bufferInfo3.width = width;
	bufferInfo3.heigth = height;
	bufferInfo3.bRender = TRUE;
	renderData1.bufferMap.insert(make_pair(ADAS_PAS_WARNING_STATUS, bufferInfo3));

	unsigned int count = 1;
	unsigned char *buffer4;
	while(1)
	{
		//printf(" [%s, %d]  count = %d\n", __FUNCTION__, __LINE__, count);
	#if 1
		if(1 == count%2)
		{
			//printf(" [%s, %d]  count = %d\n", __FUNCTION__, __LINE__, count);
			buffer4 = LodePNGImage(PNG04_PATH, width, height);
			auto it1 = renderData1.bufferMap.find(ADAS_PAS_RADAR_STATUS);
			it1->second.buffer = buffer4;
			it1->second.width = width;
			it1->second.heigth = height;
		}
		else
		{
			//printf(" [%s, %d]  count = %d\n", __FUNCTION__, __LINE__, count);
			buffer4 = LodePNGImage(PNG02_PATH, width, height);
			auto it3 = renderData1.bufferMap.find(ADAS_PAS_RADAR_STATUS);
			it3->second.buffer = buffer4;
			it3->second.width = width;
			it3->second.heigth = height;

		}
	#endif

		count++;
		graphic1->Render(renderData1);
		sleep(1);
		delete buffer4;
	}
    return NULL;
}

void * func2(void *arg)
{
    int num=*(int *)arg;
    printf("num is %d\n",num);

	tsurfaceInfo surfaceInfo;
	tsurfaceList surfaceArry;

	unsigned int widthex, heightex;
	trenderData renderData2;
	tbufInfo bufferInfo1;
	tbufInfo bufferInfo2;
	tbufInfo bufferInfo3;
	renderData2.surfaceID = 2;

	surfaceInfo.surfaceName = "Graphic_2";
	surfaceInfo.surfaceId = 2;
	surfaceInfo.moduleType = MODULE_PAS;
	surfaceInfo.bActiveEGL = TRUE;
	surfaceInfo.viewPos.width = 1024;//widthex;
	surfaceInfo.viewPos.height = 600;//heightex;
	surfaceInfo.viewPos.viewPos.x = 0;//152;
	surfaceInfo.viewPos.viewPos.y = 0;//228;
	surfaceArry.push_back(surfaceInfo);

	graphic1->createSurface(surfaceArry);

	unsigned char *buffer1 = LodePNGImage(PNG05_PATH, widthex, heightex);
	bufferInfo1.buffer = buffer1;
	bufferInfo1.width = widthex;
	bufferInfo1.heigth = heightex;
	bufferInfo1.bRender = TRUE;
	renderData2.bufferMap.insert(make_pair(ADAS_PAS_CAR_STATUS, bufferInfo1));
	unsigned char *buffer2 = LodePNGImage(PNG06_PATH, widthex, heightex);
	bufferInfo2.buffer = buffer2;
	bufferInfo2.width = widthex;
	bufferInfo2.heigth = heightex;
	bufferInfo2.bRender = TRUE;
	renderData2.bufferMap.insert(make_pair(ADAS_PAS_RADAR_STATUS, bufferInfo2));
	unsigned char *buffer3 = LodePNGImage(PNG07_PATH, widthex, heightex);
	bufferInfo3.buffer = buffer3;
	bufferInfo3.width = widthex;
	bufferInfo3.heigth = heightex;
	bufferInfo3.bRender = TRUE;
	renderData2.bufferMap.insert(make_pair(ADAS_PAS_WARNING_STATUS, bufferInfo3));

	unsigned int count = 1;
	unsigned char *buffer4;
	//ilmErrorTypes callResult;
	while(1)
	{
		//printf(" [%s, %d]  count = %d\n", __FUNCTION__, __LINE__, count);
	#if 1
		if(1 == count%2)
		{
			//printf(" [%s, %d]  count = %d\n", __FUNCTION__, __LINE__, count);
			buffer4 = LodePNGImage(PNG08_PATH, widthex, heightex);
			auto it2 = renderData2.bufferMap.find(ADAS_PAS_CAR_STATUS);
			it2->second.buffer = buffer4;
			it2->second.width = widthex;
			it2->second.heigth = heightex;
		}
		else
		{
			//printf(" [%s, %d]  count = %d\n", __FUNCTION__, __LINE__, count);
			buffer4 = LodePNGImage(PNG05_PATH, widthex, heightex);
			auto it4 = renderData2.bufferMap.find(ADAS_PAS_CAR_STATUS);
			it4->second.buffer = buffer4;
			it4->second.width = widthex;
			it4->second.heigth = heightex;
		}
	#endif

		count++;
		graphic1->Render(renderData2);
		sleep(1);
		delete buffer4;
	}
    return NULL;
}

int createThread()
{
	pthread_t thr1,thr2;
	int a=1,b=2;
    if(pthread_create(&thr1,NULL,func1,&a)!=0)
    {
        printf("create thread failed!\n");
        return -1;
    }
    // if(pthread_create(&thr2,NULL,func2,&b)!=0)
    // {
    //     printf("create thread failed!\n");
    //     return -1;
    // }
}

int main(int argc, char *argv[])
{
	tsurfaceList surfaceArry;
	tsurfaceList surfaceArry1;
	tsurfaceInfo surfaceInfo;
	int a=1,b=2;

	graphic1 = new CAdasGraphic();
	/*surfaceInfo.surfaceName = "Graphic_1";
	surfaceInfo.surfaceId = 1;
	surfaceInfo.moduleType = MODULE_PAS;
	surfaceInfo.bActiveEGL = TRUE;
	surfaceInfo.viewPos.width = 1024;//width;
	surfaceInfo.viewPos.height = 600;//height;
	surfaceInfo.viewPos.viewPos.x = 0;
	surfaceInfo.viewPos.viewPos.y = 0;
	surfaceArry.push_back(surfaceInfo);

	surfaceInfo.surfaceName = "Graphic_2";
	surfaceInfo.surfaceId = 2;
	surfaceInfo.moduleType = MODULE_PAS;
	surfaceInfo.bActiveEGL = TRUE;
	surfaceInfo.viewPos.width = 1024;//widthex;
	surfaceInfo.viewPos.height = 600;//heightex;
	surfaceInfo.viewPos.viewPos.x = 0;//152;
	surfaceInfo.viewPos.viewPos.y = 0;//228;
	surfaceArry.push_back(surfaceInfo);

	graphic1->createSurface(surfaceArry);*/

	createThread();
	//func1(&a);
	while(1)
	{
		sleep(2);
	}
	return 0;

}


#if 0
int main(int argc, char *argv[])
{
	unsigned char *buffer;
	unsigned int width, height;
	unsigned char *bufferex;
	unsigned int widthex, heightex;
	Int32 error = -1;
	tsurfaceList surfaceArry;
	tsurfaceList surfaceArry1;
	tsurfaceInfo surfaceInfo;
	surfaceInfo.bActiveEGL = TRUE;
	trenderData renderData1;
	trenderData renderData2;
	tbufInfo bufferInfo1;
	tbufInfo bufferInfo2;
	tbufInfo bufferInfo3;
	tbufInfo bufferInfo4;
	tbufInfo bufferInfo5;
	tbufInfo bufferInfo6;
	tbufInfo bufferInfo7;
	tbufInfo bufferInfo8;
	tbufInfo bufferInfo9;
	tbufInfo bufferInfo10;
	renderData1.surfaceID = 1;
	renderData2.surfaceID = 2;
	//printf(" [%s, %d]  error = %d\n", __FUNCTION__, __LINE__, error);

	unsigned char *buffer1 = LodePNGImage(PNG01_PATH, width, height);
	bufferInfo1.buffer = buffer1;
	bufferInfo1.width = width;
	bufferInfo1.heigth = height;
	bufferInfo1.bRender = TRUE;
	renderData1.bufferMap.insert(make_pair(ADAS_PAS_CAR_STATUS, bufferInfo1));
	unsigned char *buffer2 = LodePNGImage(PNG02_PATH, width, height);
	bufferInfo2.buffer = buffer2;
	bufferInfo2.width = width;
	bufferInfo2.heigth = height;
	bufferInfo2.bRender = TRUE;
	renderData1.bufferMap.insert(make_pair(ADAS_PAS_RADAR_STATUS, bufferInfo2));
	unsigned char *buffer3 = LodePNGImage(PNG03_PATH, width, height);
	bufferInfo3.buffer = buffer3;
	bufferInfo3.width = width;
	bufferInfo3.heigth = height;
	bufferInfo3.bRender = TRUE;
	renderData1.bufferMap.insert(make_pair(ADAS_PAS_WARNING_STATUS, bufferInfo3));
	//printf(" [%s, %d]  buffer = %x %x\n", __FUNCTION__, __LINE__, buffer[0], buffer[1]);
	//printf(" [%s, %d]  buffer = %d, %d\n", __FUNCTION__, __LINE__, width, height);

	/*buffer = new unsigned char[width*height*4*3];
	memcpy(buffer, buffer1, width*height*4);
	memcpy(buffer+width*height*4, buffer2, width*height*4);
	memcpy(buffer+width*height*4*2, buffer3, width*height*4);
	delete buffer1;
	delete buffer2;
	delete buffer3;*/

	unsigned char *buffer4 = LodePNGImage(PNG05_PATH, widthex, heightex);
	bufferInfo4.buffer = buffer4;
	bufferInfo4.width = widthex;
	bufferInfo4.heigth = heightex;
	bufferInfo4.bRender = TRUE;
	renderData2.bufferMap.insert(make_pair(ADAS_PAS_CAR_STATUS, bufferInfo4));
	unsigned char *buffer5 = LodePNGImage(PNG06_PATH, widthex, heightex);
	bufferInfo5.buffer = buffer5;
	bufferInfo5.width = widthex;
	bufferInfo5.heigth = heightex;
	bufferInfo5.bRender = TRUE;
	renderData2.bufferMap.insert(make_pair(ADAS_PAS_RADAR_STATUS, bufferInfo5));
	unsigned char *buffer6 = LodePNGImage(PNG07_PATH, widthex, heightex);
	bufferInfo6.buffer = buffer6;
	bufferInfo6.width = widthex;
	bufferInfo6.heigth = heightex;
	bufferInfo6.bRender = TRUE;
	renderData2.bufferMap.insert(make_pair(ADAS_PAS_WARNING_STATUS, bufferInfo6));
	/*bufferex = new unsigned char[widthex*heightex*4*3];
	memcpy(bufferex, buffer4, widthex*heightex*4);
	memcpy(bufferex+widthex*heightex*4, buffer5, widthex*heightex*4);
	memcpy(bufferex+widthex*heightex*4*2, buffer6, widthex*heightex*4);
	delete buffer4;
	delete buffer5;
	delete buffer6;*/

#if 0
	for(unsigned int i = 0; i < width*height*4*3; i++)
	{
		if(50 == i)
			cout << std::endl;
		//printf("%2.2X, %2.2X, %2.2X, %2.2X, %2.2X, %2.2X, %2.2X, %2.2X, %2.2X, %2.2X, %2.2X\n", buffer[i], buffer[i+1], buffer[i+2], buffer[i+3], buffer[i+4], buffer[i+5],
						 //buffer[i+6], buffer[i+7], buffer[i+8], buffer[i+9], buffer[i+10]);
		printf("%2.2X, ", buffer[i]);
	}
	cout << std::endl;
#endif

	CAdasGraphic *graphic1 = new CAdasGraphic();
	surfaceInfo.surfaceName = "Graphic_1";
	surfaceInfo.surfaceId = 1;
	surfaceInfo.moduleType = MODULE_PAS;
	surfaceInfo.bActiveEGL = TRUE;
	surfaceInfo.viewPos.width = 1024;//width;
	surfaceInfo.viewPos.height = 600;//height;
	surfaceInfo.viewPos.viewPos.x = 0;
	surfaceInfo.viewPos.viewPos.y = 0;
	surfaceArry.push_back(surfaceInfo);

	surfaceInfo.surfaceName = "Graphic_2";
	surfaceInfo.surfaceId = 2;
	surfaceInfo.moduleType = MODULE_PAS;
	surfaceInfo.bActiveEGL = TRUE;
	surfaceInfo.viewPos.width = 1024;//widthex;
	surfaceInfo.viewPos.height = 600;//heightex;
	surfaceInfo.viewPos.viewPos.x = 0;//152;
	surfaceInfo.viewPos.viewPos.y = 0;//228;
	surfaceArry.push_back(surfaceInfo);

	/*surfaceInfo.surfaceName = "Graphic_3";
	surfaceInfo.surfaceId = 2;
	surfaceInfo.viewPos.width = 10;
	surfaceInfo.viewPos.height = 10;
	surfaceInfo.viewPos.viewPos.x = 20;
	surfaceInfo.viewPos.viewPos.y = 20;
	surfaceArry.push_back(surfaceInfo);*/

	graphic1->createSurface(surfaceArry);
	//sleep(1);
	//graphic1->createSurface(surfaceArry1);

	unsigned int count = 1;
	unsigned char *buffer7;
	unsigned char *buffer8;
	//ilmErrorTypes callResult;
	while(1)
	{
		//callResult = ilm_surfaceSetDestinationRectangle(1, 0, 0, width, height);
		//printf(" [%s, %d]  callResult = %d\n", __FUNCTION__, __LINE__, callResult);
		//callResult = ilm_surfaceSetDestinationRectangle(2, width, height, widthex, heightex);
		//callResult = ilm_layerSetDestinationRectangle(1000, 50, 50, 1024, 600);
		//printf(" [%s, %d]  callResult = %d\n", __FUNCTION__, __LINE__, callResult);
		//ilm_commitChanges();

		//printf(" [%s, %d]  count = %d\n", __FUNCTION__, __LINE__, count);
	#if 1
		if(1 == count%2)
		{
			//printf(" [%s, %d]  count = %d\n", __FUNCTION__, __LINE__, count);
			buffer7 = LodePNGImage(PNG04_PATH, width, height);
			auto it1 = renderData1.bufferMap.find(ADAS_PAS_RADAR_STATUS);
			it1->second.buffer = buffer7;
			it1->second.width = width;
			it1->second.heigth = height;

			buffer8 = LodePNGImage(PNG08_PATH, widthex, heightex);
			auto it2 = renderData2.bufferMap.find(ADAS_PAS_CAR_STATUS);
			it2->second.buffer = buffer8;
			it2->second.width = widthex;
			it2->second.heigth = heightex;
		}
		else
		{
			//printf(" [%s, %d]  count = %d\n", __FUNCTION__, __LINE__, count);
			buffer7 = LodePNGImage(PNG02_PATH, width, height);
			auto it3 = renderData1.bufferMap.find(ADAS_PAS_RADAR_STATUS);
			it3->second.buffer = buffer7;
			it3->second.width = width;
			it3->second.heigth = height;

			buffer8 = LodePNGImage(PNG05_PATH, widthex, heightex);
			auto it4 = renderData2.bufferMap.find(ADAS_PAS_CAR_STATUS);
			it4->second.buffer = buffer8;
			it4->second.width = widthex;
			it4->second.heigth = heightex;
		}
	#endif

		count++;
		graphic1->Render(renderData1);
		sleep(1);
		graphic1->Render(renderData2);
		sleep(1);
		delete buffer7;
		delete buffer8;
	}

	return 0;
}
#endif

