#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
    int width;
    int height;
    int max_gray;
    unsigned char *data;
}GrayImage;

GrayImage *load_pgm(const char *filename)
{
/* 1. 打开⽂件，检查是否成功 —— 永远不要跳过这⼀步 */
FILE *fp = fopen(filename, "r");
if (fp == NULL) {
fprintf(stderr, "⽆法打开⽂件: %s\n", filename);
return NULL;
}
/* 2. 读魔数并校验必须是 "P2" */
char magic[3] = {0};
if (fscanf(fp, "%2s", magic) != 1 || strcmp(magic, "P2") != 0) {
fprintf(stderr, "不是 P2 格式的 PGM ⽂件\n");
fclose(fp);
return NULL;
}
/* 3. 申请结构体本⾝ */
GrayImage *img = (GrayImage *)malloc(sizeof(GrayImage));
if(img==NULL){
    fprintf(stderr,"内存分配失败");
    fclose(fp);
    return NULL;
}
/* 4. 读头部三个数：宽、⾼、最⼤灰度值 */
if (fscanf(fp, "%d %d %d",
&img->width, &img->height, &img->max_gray) != 3) {
    fprintf(stderr,"PGM文件读取失败");
    free(img);
    fclose(fp);
    return NULL;
}
if(img->width<=0||img->height<=0){
    fprintf(stderr,"宽高不能小于零");
    free(img);
    fclose(fp);
    return NULL;
}
/* 5. 按尺⼨申请像素数组 */
int n = img->width * img->height;
img->data = (unsigned char *)malloc(n * sizeof(unsigned char));
if(img->data==NULL){
    fprintf(stderr,"内存分配失败");
    fclose(fp);
    return NULL;
}
/* 6. 逐个读像素。注意：⽤ int 中转再赋值给 unsigned char */
for (int i = 0; i < n; i++) {
int v;
if (fscanf(fp, "%d", &v) != 1) {
    fprintf(stderr,"像素数量不足");
    free(img->data);
    free(img);
    fclose(fp);
    return NULL;
}
img->data[i] = (unsigned char)v;
}
fclose(fp);
return img;
}
int save_pgm(const char *filename, const GrayImage *img)
{
if (img == NULL || img->data == NULL) return 0;
FILE *fp = fopen(filename, "w");
if (fp == NULL) { 
    fprintf(stderr,"无法打开文件");
    return 0;
 }
/* 头部：魔数、宽⾼、最⼤灰度值，各占⼀⾏ */
fprintf(fp, "P2\n%d %d\n%d\n", img->width, img->height, img->max_gray);
/* 像素：每⾏输出 width 个数，⾏末换⾏，便于⼈⼯检查 */
for (int r = 0; r < img->height; r++) {
for (int c = 0; c < img->width; c++) {
fprintf(fp, "%d ", img->data[r * img->width + c]);
}
fprintf(fp, "\n");
}
fclose(fp); /* 忘记 fclose，缓冲区可能没落盘，⽂件是不完整的 */
return 1; /* 1 表⽰成功，0 表⽰失败 —— 调⽤⽅要检查返回值 */
}
void free_image(GrayImage *img)
{
if (img == NULL) return; /* 传 NULL 也应当安全，不能崩溃 */
free(img->data); /* 先释放内部指针 */
img->data = NULL;
free(img); /* 再释放结构体本⾝ */
}