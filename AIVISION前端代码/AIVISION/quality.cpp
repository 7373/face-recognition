#include "quality.h"

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "glcm.h"
#include "iostream"
#include "math.h"
#include <QDebug>

using namespace std;
using namespace cv;


Quality::Quality()
{

}

void Quality::run(){
     //计算照片评价值
    Mat image = imread(this->imageSource.toStdString());
        double cast = 0;
        //清晰度
        double t = Quality::DefRto(image);
        if (t>10)
            this->definition="清晰";
        else
            this->definition="模糊，将影响识别效果";

//        cast=color(image);      //色偏
//        printf("色偏指数： %f\n", cast);
//        if (cast>1)
//            printf("存在色偏\n");
//        else
//            printf("不存在色偏\n");
//        printf("\n");

        double avg=0;
        cast=brightness(image, avg);    // 明亮度
        if (cast>1)
        {
            if (avg>0)
                this->brightnession="过亮";
            else
                this->brightnession="过暗";
        }
        else
            this->brightnession="亮度适中";

        GLCM glcm;
        GLCMFeatures features;
        glcm.getGLCM(image,features);

//        cout << "能量： " << features.energy << endl;
//        cout << "熵： " << features.entropy << endl;
//        cout << "对比度： " << features.contrast << endl;
        this->contrast=QString::number(features.contrast);
//        cout << "逆差分矩： " << features.idMoment << endl;
//        cvWaitKey(0);
    //计算出
    emit complete();
    qDebug()<<"quality finished";
}

void Quality::onComplete(){

}


/*
* 函数描述：  DefRto 计算并返回一幅图像的清晰度
*函数参数： frame  彩色帧图
*函数返回值：double   清晰度表示值，针对该视频，当清晰度小于10为模糊，大于14为清楚
*/
double Quality::DefRto(Mat InputImg)
{
    Mat gray;
    cvtColor(InputImg, gray, CV_BGR2GRAY);
    IplImage *img = &(IplImage(gray));
    double temp = 0;
    double DR = 0;
    int i, j;//循环变量
    int height = img->height;
    int width = img->width;
    int step = img->widthStep / sizeof(uchar);
    uchar *data = (uchar*)img->imageData;
    double num = width*height;

    for ( i = 0; i<height-1; i++)
    {
        for (j = 0; j<width-1;j++)
        {
            temp += sqrt((pow((double)(data[(i + 1)*step + j] - data[i*step + j]), 2)+ pow((double)(data[i*step + j + 1] - data[i*step + j]), 2)));
            temp += abs(data[(i + 1)*step + j] - data[i*step + j]) + abs(data[i*step + j + 1] - data[i*step + j]);
        }
    }
    DR = temp / num;
    return DR;
}

double Quality::DefRto(IplImage *InputImg)
{
    IplImage * gray = cvCreateImage(cvGetSize(InputImg), InputImg->depth, 1);
    cvCvtColor(InputImg, gray, CV_BGR2GRAY);
    double temp = 0;
    double DR = 0;
    int i, j;//循环变量
    int height = gray->height;
    int width = gray->width;
    int step = gray->widthStep / sizeof(uchar);
    uchar *data = (uchar*)gray->imageData;
    double num = width*height;

    for (i = 0; i<height-1; i++)
    {
        for (j = 0; j<width-1; j++)
        {

            temp += sqrt((pow((double)(data[(i + 1)*step + j] - data[i*step + j]), 2) + pow((double)(data[i*step + j + 1] - data[i*step + j]), 2)));
            temp += abs(data[(i + 1)*step + j] - data[i*step + j]) + abs(data[i*step + j + 1] - data[i*step + j]);
        }
    }
    DR = temp / num;
    return DR;
}

/*
double Tenegrad(Mat InputImg)
{
    Mat imageGrey;

    cvtColor(InputImg, imageGrey, CV_RGB2GRAY);
    Mat imageSobel;
    Sobel(imageGrey, imageSobel, CV_16U, 1, 1);

    //图像的平均灰度
    double meanValue = 0.0;
    meanValue = mean(imageSobel)[0];

    return meanValue;
}*/

double Quality::Tenegrad(Mat InputImg)//Tenegrad 标准
{
    Mat gray;
    cvtColor(InputImg, gray, CV_BGR2GRAY);
    IplImage *src = &(IplImage(gray));
    int row = src->height;//height对应行数
    int col = src->width; //width对应行数
    int widthstep = src->widthStep;
    uchar *data = (uchar*)src->imageData;
    double S = 0;
    for (int x = 1; x<row - 1; x++)
    {
        uchar *pre_row = data + (x - 1)*widthstep;
        uchar *cur_row = data + x*widthstep;
        uchar *nex_row = data + (x + 1)*widthstep;
        int Sx, Sy;
        for (int y = 1; y<col - 1; y++)
        {
            //**********************************************/
            //当前邻域：
            //pre_row[y-1],pre_row[y],pre_row[y+1];
            //cur_row[y-1],cur_row[y],cur_row[y+1];
            //nex_row[y-1],nex_row[y],nex_row[y+1];

            //Gx =-1,0,1       Gy =1, 2, 1
            //    -2,0,2           0, 0, 0
            //    -1,0,1          -1,-2,-1
            //**********************************************/
            Sx = (uchar)pre_row[y + 1] + 2 * (uchar)cur_row[y + 1] + (uchar)nex_row[y + 1]//一定要转为uchar
                - (uchar)pre_row[y - 1] - 2 * (uchar)cur_row[y - 1] - (uchar)nex_row[y - 1];
            Sy = (uchar)nex_row[y - 1] + 2 * (uchar)nex_row[y] + (uchar)nex_row[y + 1]
                - (uchar)pre_row[y - 1] - 2 * (uchar)pre_row[y] - (uchar)pre_row[y + 1];
            S += Sx*Sx + Sy*Sy;
        }
    }
    return S / (row - 2) / (col - 2);
}

//色偏
double Quality::color(Mat InputImg)
{
    Mat gray;
    cvtColor(InputImg, gray, CV_BGR2Lab);
    //由于OpenCV定义的格式是uint8，这里输出的gray从标准的0～100，-127～127，-127～127，被映射到了0～255，0～255，0～255空间
    double a = 0, b = 0;
    int HistA[256], HistB[256];
    for (int i = 0; i<256; i++)
    {
        HistA[i] = 0;
        HistB[i] = 0;
    }
    for (int i = 0; i<gray.rows; i++)
    {
        for (int j = 0; j<gray.cols; j++){
            a += (double)(gray.at<Vec3b>(i, j)[1] - 128);//在计算过程中，要考虑将CIE L*a*b*空间还原后同
            b += (double)(gray.at<Vec3b>(i, j)[2] - 128);
            int x = gray.at<Vec2b>(i, j)[1];
            int y = gray.at<Vec3b>(i, j)[2];
            HistA[x]++;
            HistB[y]++;
        }
    }
    int MN = gray.rows*gray.cols;
    double da = a / (double)MN;
    double db = b / (double)MN;
    double D = sqrt(da*da + db*db);
    double Ma = 0, Mb = 0;
    for (int i = 0; i<256; i++)
    {
        Ma += abs(i - 128 - da)*HistA[i];//计算范围-128～127
        Mb += abs(i - 128 - db)*HistB[i];
    }
    Ma /= (double)MN;
    Mb /= (double)MN;
    double M = sqrt(Ma*Ma + Mb*Mb);
    double cast = D / M;

    return cast;
}

//亮度
double Quality::brightness(Mat InputImg, double& avg)
{
    Mat gray;
    cvtColor(InputImg, gray, CV_BGR2GRAY);
    double sum = 0;
    double cast = 0;
    int Hist[256];
    for (int i = 0; i<256; i++)
        Hist[i] = 0;
    for (int i = 0; i<gray.rows; i++)
    {
        for (int j = 0; j<gray.cols; j++){
            sum += double(gray.at<uchar>(i, j) - 128);//在计算过程中，考虑128为亮度均值点
            int x = gray.at<uchar>(i, j);
            Hist[x]++;
        }
    }
    int MN = gray.rows*gray.cols;
    avg = sum / (double)MN;
    double Ma = 0;
    for (int i = 0; i<256; i++)
    {
        Ma += abs(i - 128 - avg)*Hist[i];
    }
    Ma /= (double)MN;
    cast = abs(avg / Ma);

    return cast;
}
/*
double light(IplImage * image, double& avg)
{
    IplImage * gray = cvCreateImage(cvGetSize(image), image->depth, 1);
    cvCvtColor(image, gray, CV_BGR2GRAY);
    double sum = 0;
    CvScalar scalar;
    int ls[256];
    for (int i = 0; i<256; i++)
        ls[i] = 0;
    for (int i = 0; i<gray->height; i++)
    {
        for (int j = 0; j<gray->width; j++)
        {
            scalar = cvGet2D(gray, i, j);
            sum += (scalar.val[0] - 128);
            int x = (int)scalar.val[0];
            ls[x]++;
        }
    }
    avg = sum / (gray->height * gray->width);
    double total = 0;
    double mean = 0;
    for (int i = 0; i<256; i++)
    {
        total += abs(i - 128 - avg)* ls[i];
    }
    mean = total / (gray->height * gray->width);
    double cast = abs(avg / mean);
    return cast;
}*/
