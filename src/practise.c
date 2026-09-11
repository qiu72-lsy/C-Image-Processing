#include<stdio.h>
#include<stdlib.h>
typedef struct{
    int width;
    int height;
    int maxgray;
    unsigned char *data;
}GrayImage;
int main(void){
    char magic[3];
    int w,h,mg;
    scanf("%s %d %d %d",magic,&w,&h,&mg);
    if(magic[0]!='P' || magic[1]!='2'){
        printf("不是P2格式PGM\n");
        return 1;
    }
    int n=w*h;
    GrayImage *img=(GrayImage*)malloc(sizeof(GrayImage));
    if(img==NULL){
        printf("内存分配失败");
        return 1;
    }
    img->width=w;
    img->height=h;
    img->maxgray=mg;
    img->data = (unsigned char *)malloc(n * sizeof(unsigned char));
    if(img->data==NULL){
        printf("内存分配失败");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        int v;
        scanf("%d",&v);
        img->data[i] = (unsigned char)v;
    }
    free(img->data);
    free(img);
    return 0;
}