
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _data
{
    unsigned int width;
    unsigned int hight;
    unsigned int beginIndex;
    unsigned int endIndex;
} AREA;

//argv[1] is the read file, argv[2] is write file
int main(int argc, char *argv[])
{
    int ch, total=0;
    int len;
    FILE *fRfile, *fWfile;

    fRfile = fopen(argv[1], "rb");
    if(!fRfile) {
        fprintf(stderr, "fopen %s failed!\n", argv[1]);
        return 0;
    }

    fWfile = fopen(argv[2], "wb+");
    if(!fWfile) {
        fprintf(stderr, "fopen %s failed!\n", argv[2]);
        fclose(fRfile);
        return 0;
    }

    fseek(fRfile, 0, SEEK_END);
    len=ftell(fRfile);
    len -= sizeof(AREA);
    if (len <= 0) {
        fprintf(stderr, "%s length should not be 0!\n", argv[1]);
        fclose(fRfile);
        fclose(fWfile);
        return 0;
    }

    fseek(fRfile, 0, SEEK_SET);

    fprintf(fWfile, "\n");

    fprintf(fWfile, "#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_%s_H__\n", argv[3]);
    fprintf(fWfile, "#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_%s_H__\n", argv[3]);

    fprintf(fWfile, "\n");

    fprintf(fWfile, "namespace Harman {\n");
    fprintf(fWfile, "namespace Adas {\n");
    fprintf(fWfile, "namespace AFramework {\n");
    fprintf(fWfile, "namespace ABase {\n");
    fprintf(fWfile, "namespace ADASManager {\n");

    fprintf(fWfile, "\n");

    fprintf(fWfile, "typedef struct _%sResStruct{\n", argv[3]);
    fprintf(fWfile, "    unsigned int    length;\n");
    fprintf(fWfile, "    unsigned int    width;\n");
    fprintf(fWfile, "    unsigned int    hight;\n");
    fprintf(fWfile, "    unsigned int    beginIndex;\n");
    fprintf(fWfile, "    unsigned int    endIndex;\n");
    fprintf(fWfile, "    unsigned char   uClsinfo[%d];\n", len +1);
    fprintf(fWfile, "}%sResStruct;\n", argv[3]);
    fprintf(fWfile, "\n");

    AREA area;

    size_t n = fread(&area, sizeof(AREA), 1, fRfile);


    fprintf(fWfile, "static const %sResStruct %sPngResource = {\n", argv[3], argv[3]);
    fprintf(fWfile, "%u, \n", len);
    fprintf(fWfile, "%u, \n", area.width);
    fprintf(fWfile, "%u, \n", area.hight);
    fprintf(fWfile, "%u, \n", area.beginIndex);
    fprintf(fWfile, "%u, \n", area.endIndex);

    do {
        fprintf(fWfile, "\t\"");
        while ((ch = fgetc(fRfile)) != EOF)
        {
            total++;
            fprintf(fWfile, "\\x%02x",ch);

            if (total % 16 == 0)
                break;
        }
        fprintf(fWfile, "\"\n");
    } while (ch != EOF);

    fprintf(fWfile, "};\n");
    fprintf(fWfile, "\n");
    //fprintf(fWfile, "int* g_p%sPngResource = (int*)&%sPngResource;\n", argv[3], argv[3]);

    fprintf(fWfile, "} // namespace ADASManager\n");
    fprintf(fWfile, "} // namespace ABase\n");
    fprintf(fWfile, "} // namespace AFramework\n");
    fprintf(fWfile, "} // namespace Adas\n");
    fprintf(fWfile, "} // namespace Harman\n");

    fprintf(fWfile, "\n");

    fprintf(fWfile, "#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_%s_H__\n", argv[3]);

    fclose(fRfile);
    fclose(fWfile);
    return 0;
}