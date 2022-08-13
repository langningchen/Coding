#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <iostream>
#include <string.h>
#include <map>
#include "jpeg-9e/jpeglib.h"
#include "jpeg-9e/jerror.h"
using namespace std;
short ColorCounter[256][256][256];
struct PICTURE
{
    struct PIXEL
    {
        unsigned char r, g, b;
        bool IsShow;
    };
    PIXEL Data[100][100];
    int Width, Height;
} Picture;
void ReadJpegFile(string FileName)
{
    jpeg_decompress_struct cinfo;
    jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    FILE *InputFilePointer = fopen(FileName.c_str(), "rb");
    if (InputFilePointer == NULL)
    {
        cout << "can't open " << FileName << endl;
        return;
    }
    jpeg_stdio_src(&cinfo, InputFilePointer);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);
    Picture.Width = cinfo.output_width;
    Picture.Height = cinfo.output_height;
    unsigned char *Buffer = (unsigned char *)malloc(cinfo.output_width * cinfo.output_components);
    unsigned int i = 0;
    while (cinfo.output_scanline < cinfo.output_height)
    {
        jpeg_read_scanlines(&cinfo, &Buffer, 1);
        for (unsigned int j = 0; j < cinfo.output_width; j++)
        {
            Picture.Data[i][j].r = Buffer[j * 3];
            Picture.Data[i][j].g = Buffer[j * 3 + 1];
            Picture.Data[i][j].b = Buffer[j * 3 + 2];
            Picture.Data[i][j].IsShow = true;
            ColorCounter[Picture.Data[i][j].r][Picture.Data[i][j].g][Picture.Data[i][j].b]++;
        }
        i++;
    }
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
}
const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
bool vst[100][100];
int dfs(int x, int y, bool Do = false)
{
    int Size = 1;
    if (!Picture.Data[x][y].IsShow)
        return 0;
    if (Do)
        Picture.Data[x][y].IsShow = false;
    vst[x][y] = true;
    for (int i = 0; i < 8; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < Picture.Height &&
            ny >= 0 && ny < Picture.Width &&
            !vst[nx][ny] &&
            Picture.Data[nx][ny].IsShow &&
            (abs(Picture.Data[nx][ny].r - Picture.Data[x][y].r) < 50 ||
             abs(Picture.Data[nx][ny].g - Picture.Data[x][y].g) < 50 ||
             abs(Picture.Data[nx][ny].b - Picture.Data[x][y].b) < 50))
        {
            Size += dfs(nx, ny, Do);
        }
    }
    return Size;
}
int main()
{
    // system("curl https://www.luogu.com.cn/api/verify/captcha -o captcha.jpeg");
    ReadJpegFile("captcha.jpeg");
    freopen("captcha.html", "w", stdout);
    int MaxRed = 0, MaxGreen = 0, MaxBlue = 0, Max = 0;
    for (int r = 0; r < 256; r++)
        for (int g = 0; g < 256; g++)
            for (int b = 0; b < 256; b++)
                if (ColorCounter[r][g][b] > Max)
                {
                    Max = ColorCounter[r][g][b];
                    MaxRed = r;
                    MaxGreen = g;
                    MaxBlue = b;
                }
    for (int i = 0; i < Picture.Height; i++)
        for (int j = 0; j < Picture.Width; j++)
            if (abs(Picture.Data[i][j].r - MaxRed) < 30 ||
                abs(Picture.Data[i][j].g - MaxGreen) < 30 ||
                abs(Picture.Data[i][j].b - MaxBlue) < 30)
                Picture.Data[i][j].IsShow = false;
    for (int i = 0; i < Picture.Height; i++)
    {
        for (int j = 0; j < Picture.Width; j++)
        {
            memset(vst, 0, sizeof(vst));
            if (dfs(i, j) <= 100)
            {
                memset(vst, 0, sizeof(vst));
                dfs(i, j, true);
            }
        }
    }
    for (int i = 0; i < Picture.Height; i++)
    {
        for (int j = 0; j < Picture.Width; j++)
        {
            if (Picture.Data[i][j].IsShow)
                cout << "<font style=\"color: rgb(" << (int)Picture.Data[i][j].r << "," << (int)Picture.Data[i][j].g << "," << (int)Picture.Data[i][j].b << ")\">哦</font>";
            else
                cout << "<font style=\"color: rgba(0,0,0,0)\">哦</font>";
        }
        cout << "<br>";
    }
    return 0;
}