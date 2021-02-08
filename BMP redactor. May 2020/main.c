#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>

#pragma pack (push, 1)
typedef struct
{
    unsigned short signature;
    unsigned int filesize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int pixelArrOffset;
} BitmapFileHeader;

typedef struct
{
    unsigned int headerSize;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bitsPerPixel;
    unsigned int compression;
    unsigned int imageSize;
    unsigned int xPixelsPerMeter;
    unsigned int yPixelsPerMeter;
    unsigned int colorsInColorTable;
    unsigned int importantColorCount;
} BitmapInfoHeader;

typedef struct
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
} Rgb;

#pragma pack(pop)

void printFileHeader(BitmapFileHeader header){
    printf("signature:\t%x (%hu)\n", header.signature, header.signature);
    printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);
    printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
    printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}

void printInfoHeader(BitmapInfoHeader header){
    printf("headerSize:\t%x (%u)\n", header.headerSize, header.headerSize);
    printf("width:     \t%x (%u)\n", header.width, header.width);
    printf("height:    \t%x (%u)\n", header.height, header.height);
    printf("planes:    \t%x (%hu)\n", header.planes, header.planes);
    printf("bitsPerPixel:\t%x (%hu)\n", header.bitsPerPixel, header.bitsPerPixel);
    printf("compression:\t%x (%u)\n", header.compression, header.compression);
    printf("imageSize:\t%x (%u)\n", header.imageSize, header.imageSize);
    printf("xPixelsPerMeter:\t%x (%u)\n", header.xPixelsPerMeter, header.xPixelsPerMeter);
    printf("yPixelsPerMeter:\t%x (%u)\n", header.yPixelsPerMeter, header.yPixelsPerMeter);
    printf("colorsInColorTable:\t%x (%u)\n", header.colorsInColorTable, header.colorsInColorTable);
    printf("importantColorCount:\t%x (%u)\n", header.importantColorCount, header.importantColorCount);
}

struct Commands{
    int cond;
    int x_c;
    int y_c;
    int xl;
    int yl;
    int xr;
    int yr;
    int r;
    int xl2;
    int yl2;
    int xr2;
    int yr2;
    int width;
    int fill;
    int inf;
    float cval;
};

void create_point(Rgb** img, int x,int y, Rgb* colour){
    img[y][x].b=colour->b;
    img[y][x].r=colour->r;
    img[y][x].g=colour->g;
}

void create_line(Rgb** img, int x1,int y1, int x2, int y2, Rgb* colour) {
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    if (abs(deltaX) > abs(deltaY)){
        float k = ((float)deltaY) / ((float)deltaX);
        for (int i = 0;  deltaX > 0 ? i <= deltaX : i >= deltaX; deltaX > 0 ? i++ : i--){
            int x = i + x1;
            int y = (int)(i*k) + y1;
            create_point(img, x, y, colour);
        }
    }
    else{
        float k = ((float)deltaX) / ((float)deltaY);
        for (int i = 0;  deltaY > 0 ? i <= deltaY : i >= deltaY; deltaY > 0 ? i++ : i--){
            int y = i + y1;
            int x = (int)(i*k) + x1;
            create_point(img, x, y, colour);
        }
    }
}

void create_rectange(Rgb** img, int x1,int y1, int x2, int y2, Rgb* colour){
    create_line(img,x1,y1,x2,y1,colour);
    create_line(img,x2,y1,x2,y2,colour);
    create_line(img,x1,y2,x2,y2,colour);
    create_line(img,x1,y2,x1,y1,colour);
}

void create_width_rectangle(Rgb** img, int x1,int y1, int x2, int y2, Rgb* colour,int w){
    if(w==0){
        return;
    }
    if(x1-w<0 || x2-w<0 || y1-w<0 || y2-w<0){
        printf("Error, out of image");
        return;
    }
    Rgb *col=malloc(1*sizeof(Rgb));
    col->r=0;
    col->g=0;
    col->b=0;
    for(int i=0;i<w;i++){
        {
        create_rectange(img,x1-i,y1+i,x2+i,y2-i,colour);
        }
    }
}

void fill_rectangle(Rgb** img, int x1,int y1, int x2, int y2, Rgb* colour){
    for(int i=y2;i<y1;i++){
        for(int j=x1;j<x2;j++){
            img[i][j].g=colour->g;
            img[i][j].b=colour->b;
            img[i][j].r=colour->r;
        }
    }
}

void create_hexagon_by_sq(Rgb** img,int x1,int y1, int x2, int y2,Rgb* colour){ //А тут делаю шестиугольник толщиною 1
    double tg_15=0.26795;
    int xmax,ymax,xmin,ymin;
    if(x2>x1 && y1>y2){
        ymax=y1;
        ymin=y2;
        xmax=x2;
        xmin=x1;
    }else if(x2<x1 && y1<y2){
        ymax=y2;
        ymin=y1;
        xmax=x1;
        xmin=x2;
    }else{
        printf("error");
    }
    int xc=xmin+(xmax-xmin)/2+tg_15*(xmax-xmin)/2;
    int ya=ymin+(ymax-ymin)/2+tg_15*(ymax-ymin)/2;
    int xb=xmin+(xmax-xmin)/2-tg_15*(xmax-xmin)/2;
    int yf=ymin+(ymax-ymin)/2-tg_15*(ymax-ymin)/2;
    int AC=sqrt((xc-xmax)*(xc-xmax)+(ymax-ya)*(ymax-ya));
    int a=(2*ya-2*ymin+0.5-sqrt((2*ya-2*ymin)*(2*ya-2*ymin)-8*((ymin-ya)*(ymin-ya)-AC*AC)))/4;
    create_line(img,xc,ymax,xmax,ya,colour);
    create_line(img,xmax,ya,xmax-a,ymin+a,colour);
    create_line(img,xb,ymin,xmax-a,ymin+a,colour);
    create_line(img,xmin,yf,xb,ymin,colour);
    create_line(img,xmin,yf,xmin+a+1,ymax-a-1,colour);
    create_line(img,xc,ymax,xmin+a+1,ymax-a-1,colour);
}

void create_width_hexagon_by_sq(Rgb** img,int x1,int y1, int x2, int y2,Rgb* colour,int width){
    for(int i=-width;i<0;i++){
        if(i>-width) {
            create_hexagon_by_sq(img, x1 - i, y1 + i, x2 + i, y2 - i, colour);
            create_hexagon_by_sq(img, x1 - i+1, y1 + i, x2 + i+1, y2 - i, colour);
            create_hexagon_by_sq(img, x1 - i, y1 + i+1, x2 + i, y2 - i+1, colour);
            create_hexagon_by_sq(img, x1 - i+2, y1 + i, x2 + i+2, y2 - i, colour);
            create_hexagon_by_sq(img, x1 - i, y1 + i+2, x2 + i, y2 - i+2, colour);

        }
    }
}


void create_hexagon_by_cir(Rgb** img,int x,int y, int r,Rgb* colour){
    double cos_30=0.866;
    double sin_30=0.5;
    create_line(img,x,y+r,x+(r*cos_30),y+(r*sin_30),colour);
    create_line(img,x+(r*cos_30),y-(r*sin_30),x+(r*cos_30),y+(r*sin_30),colour);
    create_line(img,x,y-r,x+(r*cos_30),y-(r*sin_30),colour);
    create_line(img,x,y-r,x-(r*cos_30),y-(r*sin_30),colour);
    create_line(img,x-(r*cos_30),y-(r*sin_30),x-(r*cos_30),y+(r*sin_30),colour);
    create_line(img,x,y+r,x-(r*cos_30),y+(r*sin_30),colour);
}

void create_width_hexagon_by_cir(Rgb** img,int x,int y, int r,Rgb* colour,int width){
    for(int i=0;i<width;i++){
        create_hexagon_by_cir(img,x,y,r+i,colour);
        if(i>0) {
            create_hexagon_by_cir(img, x - 1, y, r + i, colour);
            create_hexagon_by_cir(img, x + 1, y, r + i, colour);
            create_hexagon_by_cir(img, x, y - 1, r + i, colour);
            create_hexagon_by_cir(img, x, y + 1, r + i, colour);
        }
    }
}

void copy_the_rectangle(Rgb** img, int x1,int y1, int x2, int y2, int x3,int y3, int x4, int y4){
    int height=abs(y2-y1);
    int width=abs(x2-x1);
    Rgb** new_r=malloc(height*sizeof(Rgb*));
    for(int i=0;i<height;i++){
        new_r[i]=malloc(width*sizeof(Rgb));
    }
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            new_r[i][j].b=img[i+y2][j+x1].b;
            new_r[i][j].g=img[i+y2][j+x1].g;
            new_r[i][j].r=img[i+y2][j+x1].r;
        }
    }
    for(int i=y4;i<y3;i++){
        for(int j=x3;j<x4;j++){
            img[i][j].b=new_r[i-y4][j-x3].b;
            img[i][j].g=new_r[i-y4][j-x3].g;
            img[i][j].r=new_r[i-y4][j-x3].r;
        }
    }
}

int min(int a,int b, int c){
    int min=a;
    if(b<a){
        if (b<c){
            min=b;
        }else{
            min=c;
        }
    }else{
        if(c<a){
            min=c;
        }
    }
    return min;
}

int max(int a,int b, int c){
    int max=a;
    if(b>a){
        if (b>c){
            max=b;
        }else{
            max=c;
        }
    }else{
        if(c>a){
            max=c;
        }
    }
    return max;
}

int check_triangle(int x1,int y1,int x2,int y2,int x3,int y3, int x, int y){
    int s1=(y1-y2)*x+(x2-x1)*y+(x1*y2-x2*y1);
    int s2=(y2-y3)*x+(x3-x2)*y+(x2*y3-x3*y2);
    int s3=(y3-y1)*x+(x1-x3)*y+(x3*y1-x1*y3);
    if((s1>=0 && s2>=0 && s3>=0) || (s1<=0 && s2<=0 && s3<=0)){
        return 1;
    }else{
        return 0;
    }
}

void fill_triangle(Rgb** img,int x1,int y1,int x2,int y2,int x3,int y3,Rgb* col){
    int xmax=max(x1,x2,x3);
    int ymax=max(y1,y2,y3);
    int xmin=min(x1,x2,x3);
    int ymin=min(y1,y2,y3);
    for(int i=ymin;i<ymax;i++){
        for(int j=xmin;j<xmax;j++){
            if(check_triangle(x1,y1,x2,y2,x3,y3,j,i)){
                create_point(img,j,i,col);
            }
        }
    }
}

void fill_hexagon_by_sq(Rgb** img,int x1,int y1, int x2, int y2,Rgb* col){
    double tg_15=0.26795;
    int xmax,ymax,xmin,ymin;
    if(x2>x1 && y1>y2){
        ymax=y1;
        ymin=y2;
        xmax=x2;
        xmin=x1;
    }else if(x2<x1 && y1<y2){
        ymax=y2;
        ymin=y1;
        xmax=x1;
        xmin=x2;
    }else{
        printf("not a square");
    }
    int xc=xmin+(xmax-xmin)/2+tg_15*(xmax-xmin)/2;
    int ya=ymin+(ymax-ymin)/2+tg_15*(ymax-ymin)/2;
    int xb=xmin+(xmax-xmin)/2-tg_15*(xmax-xmin)/2;
    int yf=ymin+(ymax-ymin)/2-tg_15*(ymax-ymin)/2;
    int AC=sqrt((xc-xmax)*(xc-xmax)+(ymax-ya)*(ymax-ya));
    int a=(2*ya-2*ymin-sqrt((2*ya-2*ymin)*(2*ya-2*ymin)-8*((ymin-ya)*(ymin-ya)-AC*AC)))/4;
    fill_triangle(img,xb,ymin+1,xc,ymax,xmax,ya,col);
    fill_triangle(img,xb,ymin+1,xmax-1,ya,xmax-a-1,ymin+a+1,col);
    fill_triangle(img,xb,ymin+1,xc,ymax-1,xmin+a+1,ymax-a-1,col);
    fill_triangle(img,xmin+1,yf,xmin+a+1,ymax-a-1,xb,ymin+1,col);
}

void fill_hexagon_by_cir(Rgb** img,int x,int y, int r,Rgb* col){
    double cos_30=0.866;
    double sin_30=0.5;
    fill_triangle(img,x,y,x-(r*cos_30),y+(r*sin_30),x,y+r,col);
    fill_triangle(img,x,y,x,y+r,x+(r*cos_30),y+(r*sin_30),col);
    fill_triangle(img,x,y,x+(r*cos_30),y+(r*sin_30),x+(r*cos_30),y-(r*sin_30),col);
    fill_triangle(img,x,y,x+(r*cos_30),y-(r*sin_30),x,y-r,col);
    fill_triangle(img,x,y,x,y-r,x-(r*cos_30),y-(r*sin_30),col);
    fill_triangle(img,x,y,x-(r*cos_30),y-(r*sin_30),x-(r*cos_30),y+(r*sin_30),col);
}

void print_help(){
    printf("-u or --upleft - coordinats of upper-left angel of rectangle\n");
    printf("-l or --downright - coordinats of lower-right angel of rectangle\n");
    printf("-w or --width - value of width of borders\n");
    printf("-r or --radius - radius of circle\n");
    printf("-c or --centre - coordinats of circle's centre\n");
    printf("-f or --fill - fill the figure\n");
    printf("--inputfile - name of input file\n");
    printf("--outputfile - name of output file\n");
    printf("--rectangle - draw a rectangle\n");
    printf("--color - choose the color\n");
    printf("--hexagonsq - draw a hexagon by coord of square\n");
    printf("--hexagoncir - draw a hexagon by coord of centre of circle and radius\n");
    printf("--help or -? or -h - call a reference\n");
    printf("--inf - call an information about file\n");
    printf("--copyarea - copy part of picture\n");
    printf("--contrast - change contrast of image\n");
    printf("--uplarea - coord of upper-left angle of area where you are going to place part of picture\n");
    printf("--uprarea - coord of lower-right angle of area where you are going to place part of picture\n");
}

int choose_color(char* str, Rgb* col){ //Функция цвета
    if (strcmp("red", str)==0){
        col->r = 255;
        col->g = 0;
        col->b = 0;
        return 1;
    }
    if (strcmp("white", str)==0){
        col->r = 255;
        col->g = 255;
        col->b = 255;
        return 1;
    }
    if (strcmp("pink", str) == 0){
        col->r=255;
        col->g=0;
        col->b=255;
        return 1;
    }
    if (strcmp("lime", str) == 0){
        col->r = 0;
        col->g = 255;
        col->b = 0;
        return 1;
    }
    if (strcmp("green", str) == 0){
        col->r = 0;
        col->g = 128;
        col->b = 0;
        return 1;
    }
    if (strcmp("blue", str) == 0){
        col->r = 0;
        col->g = 0;
        col->b = 255;
        return 1;
    }
    if (strcmp("black", str) == 0){
        col->r = 0;
        col->g = 0;
        col->b = 0;
        return 1;
    }
    if (strcmp("yellow", str) == 0){
        col->r = 255;
        col->g = 255;
        col->b = 0;
        return 1;
    }
    if (strcmp("orange", str) == 0){
        col->r = 255;
        col->g = 128;
        col->b = 0;
        return 1;
    }
    if (strcmp("purple", str) == 0){
        col->r = 128;
        col->g = 0;
        col->b = 255;
        return 1;
    }
    if (strcmp("grey", str) == 0){
        col->r = 128;
        col->g = 128;
        col->b = 128;
        return 1;
    }
    printf("Color doesn't find\n"); //Всегда выполняется это условие
    return 0;
}

int is_valid_rect(int x1,int y1,int x2,int y2,unsigned int height,unsigned int width, int w){
    if(x1<0 || y2<0 || x1>x2 || y2>y1 || x2>width || y1>height || x1-w<0 || y1+w>height || x2+w>width || y2-w<0){
        printf("Wrong coordinats or out of image\n");
        return 0;
    }
    return 1;
}

int is_validsq(int x1,int y1,int x2,int y2){
    if(abs(x1-x2)!=abs(y1-y2)){
        printf("Wrong coordinats. Not a square.\n");
        return 0;
    }
    return 1;
}

void change_con_of_pic(Rgb** img,float con_value,int H_img,int W_img) {
    double avg = 0;
    int tmp;
    for (int i = 0; i < H_img; i++) {
        for (int j = 0; j < W_img; j++) {
            avg = avg + img[i][j].r * 0.299 + img[i][j].g * 0.587 + img[i][j].b * 0.114;
        }
    }
    avg=(int)(avg/(H_img*W_img));
    for (int i = 0; i < H_img; i++) {
        for (int j = 0; j < W_img; j++) {
             tmp=(int)(avg+con_value*(img[i][j].r-avg));
             if (tmp<0){
                 tmp=0;
             }else if(tmp>255){
                 tmp=255;
             }else{
                 img[i][j].r=tmp;
             }
            tmp=(int)(avg+con_value*(img[i][j].b-avg));
            if (tmp<0){
                tmp=0;
            }else if(tmp>255){
                tmp=255;
            }else{
                img[i][j].b=tmp;
            }
            tmp=(int)(avg+con_value*(img[i][j].g-avg));
            if (tmp<0){
                tmp=0;
            }else if(tmp>255){
                tmp=255;
            }else{
                img[i][j].g=tmp;
            }
        }
    }
}

int main(int argc, char* argv[]){
    char inputfile[100];
    char outputfile[100];
    char* bord_color=calloc(10,sizeof(char));
    char* fill_color=calloc(10,sizeof(char));
    struct Commands cmd;
    cmd.cond=0;
    cmd.x_c=-1;
    cmd.y_c=-1;
    cmd.xl=-1;
    cmd.yl=-1;
    cmd.xr=-1;
    cmd.yr=-1;
    cmd.r=0;
    cmd.width=1;
    cmd.fill=0;
    cmd.xl2=-1;
    cmd.yl2=-1;
    cmd.xr2=-1;
    cmd.yr2=-1;
    cmd.inf=0;
    int opt;
    int longInd;
    char* optStr = "u:l:w:r:c:fh?";
    struct option longOpts[]={
            {"inputfile", no_argument, NULL, 0},
            {"outputfile", no_argument, NULL, 0},
            {"rectangle", no_argument, NULL, 0},
            {"centre", required_argument, NULL, 'c'},
            {"radius", required_argument, NULL, 'r'},
            {"color", required_argument, NULL, 0},
            {"fillcolor", required_argument, NULL, 0},
            {"upleft", required_argument, NULL, 'u'},
            {"downright", required_argument, NULL, 'l'},
            {"hexagonsq", no_argument, NULL, 0},
            {"hexagoncir", no_argument, NULL, 0},
            {"width", required_argument, NULL, 'w'},
            {"fill", no_argument, NULL, 'f'},
            {"help", no_argument, NULL, 'h'},
            {"inf", no_argument, NULL, 0},
            {"copyarea", no_argument, NULL, 0},
            {"uplarea",required_argument, NULL, 0},
            {"uprarea",required_argument, NULL, 0},
            {"contrast",required_argument, NULL, 0},
            { NULL, 0, NULL, 0}
    };
    opt = getopt_long(argc, argv, optStr, longOpts, &longInd);
    while(opt!=-1){
        switch (opt) {
            case 'u':
                cmd.xl=atoi(argv[optind - 1]);
                cmd.yl=atoi(argv[optind]);
                break;
            case 'l':
                cmd.xr=atoi(argv[optind - 1]);
                cmd.yr=atoi(argv[optind]);
                break;
            case 'w':
                cmd.width=atoi(argv[optind - 1]);
                break;
            case 'r':
                cmd.r=atoi(argv[optind - 1]);
                break;
            case 'c':
                cmd.x_c=atoi(argv[optind - 1]);
                cmd.y_c=atoi(argv[optind]);
                break;
            case 'f':
                cmd.fill=1;
                break;
            case 0:
                if(strcmp("rectangle", longOpts[longInd].name)==0){
                    cmd.cond=1;
                }
                if(strcmp("hexagonsq", longOpts[longInd].name)==0){
                    cmd.cond=2;
                }
                if(strcmp("hexagoncir", longOpts[longInd].name)==0){
                    cmd.cond=3;
                }
                if(strcmp("copyarea", longOpts[longInd].name)==0){
                    cmd.cond=4;
                }
                if(strcmp("contrast", longOpts[longInd].name)==0){
                    cmd.cond=5;
                    cmd.cval=atof(argv[optind - 1]);
                }
                if(strcmp("inputfile", longOpts[longInd].name)==0){
                    strcpy(inputfile, argv[optind]);
                }
                if(strcmp("outputfile", longOpts[longInd].name)==0){
                    strcpy(outputfile, argv[optind]);
                }
                if(strcmp("color", longOpts[longInd].name)==0){
                    strcpy(bord_color, argv[optind-1]); //Цвет записывается в переменную(Я пробовал динамически, но откати до статического)
                    bord_color[strlen(argv[optind-1])]='\0';
                }
                if(strcmp("fillcolor", longOpts[longInd].name)==0){
                    strcpy(fill_color, argv[optind - 1]);
                    fill_color[strlen(argv[optind-1])]='\0';
                }
                if(strcmp("fill", longOpts[longInd].name)==0){
                    cmd.fill=1;
                }
                if(strcmp("uplarea", longOpts[longInd].name)==0){
                    cmd.xl2=atoi(argv[optind - 1]);
                    cmd.yl2=atoi(argv[optind]);
                }
                if(strcmp("uprarea", longOpts[longInd].name)==0){
                    cmd.xr2=atoi(argv[optind - 1]);
                    cmd.yr2=atoi(argv[optind]);
                }
                if(strcmp("inf", longOpts[longInd].name)==0){
                    cmd.inf=1;
                }
                break;
            case 'h':
            case '?':
                print_help();
                return 0;
        }
        opt = getopt_long(argc, argv, optStr, longOpts, &longInd);
    }
    if(argv[1]==NULL){
        print_help();
        return 0;
    }
    FILE *start_img = fopen(inputfile, "rb");
    if (!start_img || (strstr(inputfile,".bmp")==NULL)){
        printf("File could not be opened.\n");
        return 0;
    }

    BitmapFileHeader bmfh;
    BitmapInfoHeader bmif;

    fread(&bmfh,1,sizeof(BitmapFileHeader),start_img);
    fread(&bmif,1,sizeof(BitmapInfoHeader),start_img);
    if(bmif.bitsPerPixel!=24){
        printf("Unsupported format of BMP file.\n");
        return 0;
    }
    if(cmd.inf==1){
        printInfoHeader(bmif);
    }

    unsigned int Height_of_image = bmif.height;
    unsigned int Width_of_image = bmif.width;

    Rgb **arr = malloc(Height_of_image*sizeof(Rgb*));
    for(int i=0; i<Height_of_image; i++){
        arr[i] = malloc(Width_of_image * sizeof(Rgb) + (Width_of_image*3)%4);
        fread(arr[i],1,Width_of_image * sizeof(Rgb) + (Width_of_image*3)%4,start_img);
    }
    Rgb* border_color=malloc(1*sizeof(Rgb*));
        border_color->b=0;
        border_color->r=0;
        border_color->g=0;
    Rgb* filling_color=malloc(1*sizeof(Rgb*));
        filling_color->b=0;
        filling_color->r=0;
        filling_color->g=0;

    switch (cmd.cond) {
        case 1:
                if(is_valid_rect(cmd.xl,cmd.yl,cmd.xr,cmd.yr,Height_of_image,Width_of_image,cmd.width)){
                    if(cmd.fill==1){
                        if(choose_color(fill_color,filling_color)!=0){
                            fill_rectangle(arr,cmd.xl,cmd.yl,cmd.xr,cmd.yr,filling_color);
                        }else{
                            return 0;
                        }
                    }
                    if(choose_color(bord_color,border_color)==0){
                        return 0;
                    }
                    create_width_rectangle(arr,cmd.xl,cmd.yl,cmd.xr,cmd.yr,border_color,cmd.width);
                }
            break;
        case 2:
            if(cmd.xl<=0 || cmd.yl<=0 || cmd.xl>=Width_of_image || cmd.yl>=Height_of_image || cmd.xr<=0 || cmd.yr<=0 || cmd.xr>=Width_of_image || cmd.yr>=Height_of_image){
                printf("Wrong coordinats. Out of image.\n");
                return 0;
            }
            if(is_validsq(cmd.xl,cmd.yl,cmd.xr,cmd.yr)==0){
                return 0;
            }
            if((cmd.xr-cmd.xl)<2*cmd.width){
                printf("Too thick figure.\n");
                return 0;
            }
            if(cmd.fill==1) {
                if (choose_color(fill_color, filling_color)!=0) {
                    fill_hexagon_by_sq(arr,cmd.xl,cmd.yl,cmd.xr,cmd.yr,filling_color);
                }else{
                    return 0;
                }
            }
            if(choose_color(bord_color,border_color)==0){
                return 0;
            }
                create_width_hexagon_by_sq(arr,cmd.xl,cmd.yl,cmd.xr,cmd.yr,border_color,cmd.width);
                break;
        case 3:
            if((cmd.x_c-cmd.r-cmd.width)<0 || (cmd.x_c+cmd.r+cmd.width)>=Width_of_image || (cmd.y_c-cmd.r-cmd.width)<0 || (cmd.y_c+cmd.r+cmd.width)>=Height_of_image){
                printf("Wrong coordinats. Out of image.\n");
                return 0;
            }
            if(cmd.r<=0){
                printf("Radius should be more than 0.\n");
                return 0;
            }
            if(cmd.fill==1) {
                if (choose_color(fill_color, filling_color)!=0) {
                    fill_hexagon_by_cir(arr,cmd.x_c,cmd.y_c,cmd.r,filling_color);
                }else{
                    return 0;
                }
            }
            if(choose_color(bord_color,border_color)==0){
                return 0;
            }
               create_width_hexagon_by_cir(arr,cmd.x_c,cmd.y_c,cmd.r,border_color,cmd.width);
                break;
        case 4:
            if(is_valid_rect(cmd.xl,cmd.yl,cmd.xr,cmd.yr,Height_of_image,Width_of_image,cmd.width)==0){
                return 0;
            }
            if(is_valid_rect(cmd.xl2,cmd.yl2,cmd.xr2,cmd.yr2,Height_of_image,Width_of_image,cmd.width)==0){
                return 0;
            }
            if((cmd.xr-cmd.xl)!=(cmd.xr2-cmd.xl2) || (cmd.yl-cmd.yr)!=(cmd.yl2-cmd.yr2)){
                printf("Areas are not the same size.\n");
                return 0;
            }
            copy_the_rectangle(arr,cmd.xl,cmd.yl,cmd.xr,cmd.yr,cmd.xl2,cmd.yl2,cmd.xr2,cmd.yr2);
            break;
        case 5:
            if(cmd.cval<0){
                printf("Contrast value should be positive.\n");
                return 0;
            }
            change_con_of_pic(arr,cmd.cval,Height_of_image,Width_of_image);
            break;
    }

        FILE *out_img = fopen(outputfile, "wb");
        bmif.height = Height_of_image;
        bmif.width = Width_of_image;
        fwrite(&bmfh, 1, sizeof(BitmapFileHeader), out_img);
        fwrite(&bmif, 1, sizeof(BitmapInfoHeader), out_img);
        unsigned int w = Width_of_image * sizeof(Rgb) + (Width_of_image * 3) % 4;
        for(int i=0; i<Height_of_image; i++){
            fwrite(arr[i],1,w,out_img);
        }
        free(arr);
        fclose(out_img);

    return 0;
}