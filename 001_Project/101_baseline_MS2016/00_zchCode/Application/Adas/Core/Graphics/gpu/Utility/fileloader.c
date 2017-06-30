#include "fileloader.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <img/img.h>

int LoadShaderFromFile(char* file_name, char** pString)
{
	int r = 0, length = 0;
	int fd = open(file_name, O_RDWR);
	if (fd < 0) {
		//__E("failed to open file [%s]: %s", fname, strerror(errno));
		return -1;
	}

	if((r = lseek(fd, 0, SEEK_END)) == -1) {
		//__E("seek to end of %s: %s", fname, strerror(errno));
		return -1;
	}
	lseek(fd, 0, SEEK_SET);
	length = r;
	*pString  = (char*)calloc(length+2, 1);

	if((r = read(fd, *pString, length)) < length) {
		//__E("read from %s: %s", fname, strerror(errno));
		return -1;
	}
	(*pString)[length] = 0;
	(*pString)[length+1] = 0;

	return 0;
}

static unsigned char* copyImageData(img_t* pImg,int& width, int& height)
{
	unsigned char* pData;
	unsigned char *pSrc,*pDst;
	int imgStride;
	unsigned char* pImgData = NULL;
	int i,tmpStride;
	pImgData = pImg->access.direct.data;
	if(pImgData == NULL)
		return NULL;
	imgStride = pImg->access.direct.stride;
	width = pImg->w;
	height = pImg->h;
	tmpStride = 4*width;
//	printf("width=%d,height=%d,stride=%d\n",width,height,imgStride);

	pData = (unsigned char*)malloc(tmpStride*height);
	if(imgStride == tmpStride)
	{
		memcpy(pData,pImgData,tmpStride*height);
	}
	else if(imgStride > tmpStride)
	{
		pSrc = pImgData;
		pDst = pData;
		for(i=0;i<height;i++)
		{
			memcpy(pDst,pSrc,tmpStride);
			pSrc += imgStride;
			pDst += tmpStride;
		}
	}
	else
	{
		free(pData);
		pData = NULL;
	}
	return pData;
}

unsigned char* LoadPNGImage(const char* filename,int& width, int& height)
{
	int rc;
	unsigned char* pData = NULL;
    img_t img;
    img_lib_t ilib = NULL;
    img_format_t img_format = IMG_FMT_PKHE_ABGR8888;

    if ((rc = img_lib_attach(&ilib)) != IMG_ERR_OK) {
        printf("img_lib_attach() failed: %d\n", rc);
        return NULL;
    }

    img.format = img_format;
    img.flags = IMG_FORMAT;
    if ((rc = img_load_file(ilib, filename, NULL, &img)) == IMG_ERR_OK)
    {
//            rc = copy_image( &screen_pbuf, &img);
    	pData = copyImageData(&img,width,height);
    }
    else
    {
        // just blank screen if bitmap not found
        printf("img_load_file(\"%s\") failed: %d\n", filename, rc);
        pData = NULL;
    }
    img_lib_detach(ilib);
    return pData;
}

/*
 * Windows BMP file functions for OpenGL.
 *
 * Written by Michael Sweet.
 */


#ifdef WIN32
/*
 * 'LoadDIBitmap()' - Load a DIB/BMP file from disk.
 *
 * Returns a pointer to the bitmap if successful, NULL otherwise...
 */

GLubyte *                          /* O - Bitmap data */
LoadDIBitmap(const char *filename, /* I - File to load */
             BITMAPINFO **info)    /* O - Bitmap information */
    {
    FILE             *fp;          /* Open file pointer */
    GLubyte          *bits;        /* Bitmap pixel bits */
    int              bitsize;      /* Size of bitmap */
    int              infosize;     /* Size of header information */
    BITMAPFILEHEADER header;       /* File header */


    /* Try opening the file; use "rb" mode to read this *binary* file. */
    if ((fp = fopen(filename, "rb")) == NULL)
        return (NULL);

    /* Read the file header and any following bitmap information... */
    if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1)
        {
        /* Couldn't read the file header - return NULL... */
	fclose(fp);
        return (NULL);
        }

    if (header.bfType != 'MB')	/* Check for BM reversed... */
        {
        /* Not a bitmap file - return NULL... */
        fclose(fp);
        return (NULL);
        }

    infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
    if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL)
        {
        /* Couldn't allocate memory for bitmap info - return NULL... */
        fclose(fp);
        return (NULL);
        }

    if (fread(*info, 1, infosize, fp) < infosize)
        {
        /* Couldn't read the bitmap header - return NULL... */
        free(*info);
        fclose(fp);
        return (NULL);
        }

    /* Now that we have all the header info read in, allocate memory for *
     * the bitmap and read *it* in...                                    */
    if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
        bitsize = ((*info)->bmiHeader.biWidth *
                   (*info)->bmiHeader.biBitCount + 7) / 8 *
  	           abs((*info)->bmiHeader.biHeight);

    if ((bits = malloc(bitsize)) == NULL)
        {
        /* Couldn't allocate memory - return NULL! */
        free(*info);
        fclose(fp);
        return (NULL);
        }

    if (fread(bits, 1, bitsize, fp) < bitsize)
        {
        /* Couldn't read bitmap - free memory and return NULL! */
        free(*info);
        free(bits);
        fclose(fp);
        return (NULL);
        }

    /* OK, everything went fine - return the allocated bitmap... */
    fclose(fp);
    return (bits);
    }


/*
 * 'SaveDIBitmap()' - Save a DIB/BMP file to disk.
 *
 * Returns 0 on success or -1 on failure...
 */

int                                /* O - 0 = success, -1 = failure */
SaveDIBitmap(const char *filename, /* I - File to load */
             BITMAPINFO *info,     /* I - Bitmap information */
	     GLubyte    *bits)     /* I - Bitmap data */
    {
    FILE             *fp;          /* Open file pointer */
    int              size,         /* Size of file */
                     infosize,     /* Size of bitmap info */
                     bitsize;      /* Size of bitmap pixels */
    BITMAPFILEHEADER header;       /* File header */


    /* Try opening the file; use "wb" mode to write this *binary* file. */
    if ((fp = fopen(filename, "wb")) == NULL)
        return (-1);

    /* Figure out the bitmap size */
    if (info->bmiHeader.biSizeImage == 0)
	bitsize = (info->bmiHeader.biWidth *
        	   info->bmiHeader.biBitCount + 7) / 8 *
		  abs(info->bmiHeader.biHeight);
    else
	bitsize = info->bmiHeader.biSizeImage;

    /* Figure out the header size */
    infosize = sizeof(BITMAPINFOHEADER);
    switch (info->bmiHeader.biCompression)
	{
	case BI_BITFIELDS :
            infosize += 12; /* Add 3 RGB doubleword masks */
            if (info->bmiHeader.biClrUsed == 0)
	      break;
	case BI_RGB :
            if (info->bmiHeader.biBitCount > 8 &&
        	info->bmiHeader.biClrUsed == 0)
	      break;
	case BI_RLE8 :
	case BI_RLE4 :
            if (info->bmiHeader.biClrUsed == 0)
              infosize += (1 << info->bmiHeader.biBitCount) * 4;
	    else
              infosize += info->bmiHeader.biClrUsed * 4;
	    break;
	}

    size = sizeof(BITMAPFILEHEADER) + infosize + bitsize;

    /* Write the file header, bitmap information, and bitmap pixel data... */
    header.bfType      = 'MB'; /* Non-portable... sigh */
    header.bfSize      = size;
    header.bfReserved1 = 0;
    header.bfReserved2 = 0;
    header.bfOffBits   = sizeof(BITMAPFILEHEADER) + infosize;

    if (fwrite(&header, 1, sizeof(BITMAPFILEHEADER), fp) < sizeof(BITMAPFILEHEADER))
        {
        /* Couldn't write the file header - return... */
        fclose(fp);
        return (-1);
        }

    if (fwrite(info, 1, infosize, fp) < infosize)
        {
        /* Couldn't write the bitmap header - return... */
        fclose(fp);
        return (-1);
        }

    if (fwrite(bits, 1, bitsize, fp) < bitsize)
        {
        /* Couldn't write the bitmap - return... */
        fclose(fp);
        return (-1);
        }

    /* OK, everything went fine - return... */
    fclose(fp);
    return (0);
    }


#else /* !WIN32 */
/*
 * Functions for reading and writing 16- and 32-bit little-endian integers.
 */

static unsigned short read_word(FILE *fp);
static unsigned int   read_dword(FILE *fp);
static int            read_long(FILE *fp);

static int            write_word(FILE *fp, unsigned short w);
static int            write_dword(FILE *fp, unsigned int dw);
static int            write_long(FILE *fp, int l);


/*
 * 'LoadDIBitmap()' - Load a DIB/BMP file from disk.
 *
 * Returns a pointer to the bitmap if successful, NULL otherwise...
 */

unsigned char *                          /* O - Bitmap data */
LoadDIBitmap(const char *filename, /* I - File to load */
             BITMAPINFO **info)    /* O - Bitmap information */
    {
    FILE             *fp;          /* Open file pointer */
    unsigned char          *bits;        /* Bitmap pixel bits */
    unsigned char          *ptr;         /* Pointer into bitmap */
    unsigned char          temp;         /* Temporary variable to swap red and blue */
    int              x, y;         /* X and Y position in image */
    int              length;       /* Line length */
    unsigned int              bitsize;      /* Size of bitmap */
    int              infosize;     /* Size of header information */
    BITMAPFILEHEADER header;       /* File header */


    /* Try opening the file; use "rb" mode to read this *binary* file. */
    if ((fp = fopen(filename, "rb")) == NULL)
        return (NULL);

    /* Read the file header and any following bitmap information... */
    header.bfType      = read_word(fp);
    header.bfSize      = read_dword(fp);
    header.bfReserved1 = read_word(fp);
    header.bfReserved2 = read_word(fp);
    header.bfOffBits   = read_dword(fp);

    if (header.bfType != BF_TYPE) /* Check for BM reversed... */
        {
        /* Not a bitmap file - return NULL... */
        fclose(fp);
        return (NULL);
        }

    infosize = header.bfOffBits - 18;
    if ((*info = (BITMAPINFO *)malloc(sizeof(BITMAPINFO))) == NULL)
        {
        /* Couldn't allocate memory for bitmap info - return NULL... */
        fclose(fp);
        return (NULL);
        }

    (*info)->bmiHeader.biSize          = read_dword(fp);
    (*info)->bmiHeader.biWidth         = read_long(fp);
    (*info)->bmiHeader.biHeight        = read_long(fp);
    (*info)->bmiHeader.biPlanes        = read_word(fp);
    (*info)->bmiHeader.biBitCount      = read_word(fp);
    (*info)->bmiHeader.biCompression   = read_dword(fp);
    (*info)->bmiHeader.biSizeImage     = read_dword(fp);
    (*info)->bmiHeader.biXPelsPerMeter = read_long(fp);
    (*info)->bmiHeader.biYPelsPerMeter = read_long(fp);
    (*info)->bmiHeader.biClrUsed       = read_dword(fp);
    (*info)->bmiHeader.biClrImportant  = read_dword(fp);

    if (infosize > 40)
	if (fread((*info)->bmiColors, infosize - 40, 1, fp) < 1)
            {
            /* Couldn't read the bitmap header - return NULL... */
            free(*info);
            fclose(fp);
            return (NULL);
            }

    /* Now that we have all the header info read in, allocate memory for *
     * the bitmap and read *it* in...                                    */
    if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
        bitsize = ((*info)->bmiHeader.biWidth *
                   (*info)->bmiHeader.biBitCount + 7) / 8 *
  	           abs((*info)->bmiHeader.biHeight);

    if ((bits = (unsigned char*)malloc(bitsize)) == NULL)
        {
        /* Couldn't allocate memory - return NULL! */
        free(*info);
        fclose(fp);
        return (NULL);
        }

    if (fread(bits, 1, bitsize, fp) < bitsize)
        {
        /* Couldn't read bitmap - free memory and return NULL! */
        free(*info);
        free(bits);
        fclose(fp);
        return (NULL);
        }

    /* Swap red and blue */
    if((*info)->bmiHeader.biBitCount == 24)
    {
        length = ((*info)->bmiHeader.biWidth * 3 + 3) & ~3;
        for (y = 0; y < (*info)->bmiHeader.biHeight; y ++)
            for (ptr = bits + y * length, x = (*info)->bmiHeader.biWidth;
                 x > 0;
    	     x --, ptr += 3)
    	    {
    	    temp   = ptr[0];
    	    ptr[0] = ptr[2];
    	    ptr[2] = temp;
    	    }
    }


    /* OK, everything went fine - return the allocated bitmap... */
    fclose(fp);
    return (bits);
    }


/*
 * 'SaveDIBitmap()' - Save a DIB/BMP file to disk.
 *
 * Returns 0 on success or -1 on failure...
 */

int                                /* O - 0 = success, -1 = failure */
SaveDIBitmap(const char *filename, /* I - File to load */
             BITMAPINFO *info,     /* I - Bitmap information */
             unsigned char    *bits)     /* I - Bitmap data */
    {
    FILE *fp;                      /* Open file pointer */
    int  size,                     /* Size of file */
         infosize;                 /* Size of bitmap info */
    unsigned int     bitsize;                  /* Size of bitmap pixels */


    /* Try opening the file; use "wb" mode to write this *binary* file. */
    if ((fp = fopen(filename, "wb")) == NULL)
        return (-1);

    /* Figure out the bitmap size */
    if (info->bmiHeader.biSizeImage == 0)
	bitsize = (info->bmiHeader.biWidth *
        	   info->bmiHeader.biBitCount + 7) / 8 *
		  abs(info->bmiHeader.biHeight);
    else
	bitsize = info->bmiHeader.biSizeImage;

    /* Figure out the header size */
    infosize = sizeof(BITMAPINFOHEADER);
    switch (info->bmiHeader.biCompression)
	{
	case BI_BITFIELDS :
            infosize += 12; /* Add 3 RGB doubleword masks */
            if (info->bmiHeader.biClrUsed == 0)
	      break;
	case BI_RGB :
            if (info->bmiHeader.biBitCount > 8 &&
        	info->bmiHeader.biClrUsed == 0)
	      break;
	case BI_RLE8 :
	case BI_RLE4 :
            if (info->bmiHeader.biClrUsed == 0)
              infosize += (1 << info->bmiHeader.biBitCount) * 4;
	    else
              infosize += info->bmiHeader.biClrUsed * 4;
	    break;
	}

    size = sizeof(BITMAPFILEHEADER) + infosize + bitsize;

    /* Write the file header*/
    write_word(fp, BF_TYPE);        /* bfType */
    write_dword(fp, size);          /* bfSize */
    write_word(fp, 0);              /* bfReserved1 */
    write_word(fp, 0);              /* bfReserved2 */
    //write_dword(fp, 18 + infosize); /* bfOffBits */
    //write_dword(fp, sizeof(BITMAPFILEHEADER) + infosize);
    write_dword(fp, 54);
    //BITMAPFILEHEADER=16
    //BITMAPINFOHEADER=40
    fprintf(stderr," info->bmiHeader.biWidth= %d\n", info->bmiHeader.biWidth);
    fprintf(stderr,"info->bmiHeader.biHeight= %d\n",info->bmiHeader.biHeight);
    fprintf(stderr," info->bmiHeader.biBitCount= %d\n", info->bmiHeader.biBitCount);
    fprintf(stderr," info->bmiHeader.biCompression= %d\n", info->bmiHeader.biCompression); 

//bitmap information
    write_dword(fp, info->bmiHeader.biSize);
    write_long(fp, info->bmiHeader.biWidth);
    write_long(fp, info->bmiHeader.biHeight);
    write_word(fp, info->bmiHeader.biPlanes);
    write_word(fp, info->bmiHeader.biBitCount);
    write_dword(fp, info->bmiHeader.biCompression);
    write_dword(fp, info->bmiHeader.biSizeImage);
    write_long(fp, info->bmiHeader.biXPelsPerMeter);
    write_long(fp, info->bmiHeader.biYPelsPerMeter);
    write_dword(fp, info->bmiHeader.biClrUsed);
    write_dword(fp, info->bmiHeader.biClrImportant);

//if RGBQUAD exists, write RGBQUAD data
    if (infosize > 40)
	if (fwrite(info->bmiColors, infosize - 40, 1, fp) < 1)
            {
            /* Couldn't write the bitmap header - return... */
            fclose(fp);
            return (-1);
            }

//and bitmap pixel data
    if (fwrite(bits, 1, bitsize, fp) < bitsize)
        {
        /* Couldn't write the bitmap - return... */
        fclose(fp);
        return (-1);
        }

    /* OK, everything went fine - return... */
    fclose(fp);
    return (0);
    }


/*
 * 'read_word()' - Read a 16-bit unsigned integer.
 */

static unsigned short     /* O - 16-bit unsigned integer */
read_word(FILE *fp)       /* I - File to read from */
    {
    unsigned char b0, b1; /* Bytes from file */

    b0 = getc(fp);
    b1 = getc(fp);

    return ((b1 << 8) | b0);
    }


/*
 * 'read_dword()' - Read a 32-bit unsigned integer.
 */

static unsigned int               /* O - 32-bit unsigned integer */
read_dword(FILE *fp)              /* I - File to read from */
    {
    unsigned char b0, b1, b2, b3; /* Bytes from file */

    b0 = getc(fp);
    b1 = getc(fp);
    b2 = getc(fp);
    b3 = getc(fp);

    return ((((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
    }


/*
 * 'read_long()' - Read a 32-bit signed integer.
 */

static int                        /* O - 32-bit signed integer */
read_long(FILE *fp)               /* I - File to read from */
    {
    unsigned char b0, b1, b2, b3; /* Bytes from file */

    b0 = getc(fp);
    b1 = getc(fp);
    b2 = getc(fp);
    b3 = getc(fp);

    return ((int)(((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
    }


/*
 * 'write_word()' - Write a 16-bit unsigned integer.
 */

static int                     /* O - 0 on success, -1 on error */
write_word(FILE           *fp, /* I - File to write to */
           unsigned short w)   /* I - Integer to write */
    {
    putc(w, fp);
    return (putc(w >> 8, fp));
    }


/*
 * 'write_dword()' - Write a 32-bit unsigned integer.
 */

static int                    /* O - 0 on success, -1 on error */
write_dword(FILE         *fp, /* I - File to write to */
            unsigned int dw)  /* I - Integer to write */
    {
    putc(dw, fp);
    putc(dw >> 8, fp);
    putc(dw >> 16, fp);
    return (putc(dw >> 24, fp));
    }


/*
 * 'write_long()' - Write a 32-bit signed integer.
 */

static int           /* O - 0 on success, -1 on error */
write_long(FILE *fp, /* I - File to write to */
           int  l)   /* I - Integer to write */
    {
    putc(l, fp);
    putc(l >> 8, fp);
    putc(l >> 16, fp);
    return (putc(l >> 24, fp));
    }
#endif /* WIN32 */

