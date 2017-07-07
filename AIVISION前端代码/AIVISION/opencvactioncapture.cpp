#include "opencvactioncapture.h"
#include "dataobjectlist.h"
#include <QDateTime>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <QDebug>
#include <string>
#include "AivisionFromChai/Aivision/Seetaface/include/seetaface.h"
#include <QDebug>
#include <Windows.h>
#include <wingdi.h>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <urlconfig.h>
using namespace cv;


QNetworkAccessManager *OpenCVactionCapture::mNetManager = NULL;

OpenCVactionCapture::OpenCVactionCapture()
{
    this->rolename="识别中";
    this->hasrole=false;
}

OpenCVactionCapture::~OpenCVactionCapture(){

}

void OpenCVactionCapture::action(cv::Mat *imgin, cv::Mat *&imgout, bool domosaic){


    if(!imgin)
    {
        return ;
    }
    long t0 = cv::getTickCount();



    std::vector<seeta::FaceInfo> faces=Seetaface::get()->detect(*imgin);

    long t1 = cv::getTickCount();
    double secs = (t1 - t0)/cv::getTickFrequency();

    qDebug() << "Detections takes " << secs << " seconds " << endl;
  #ifdef USE_OPENMP
    qDebug() << "OpenMP is used." << endl;
  #else
    qDebug() << "OpenMP is not used. " << endl;
  #endif

  #ifdef USE_SSE
    qDebug() << "SSE is used." << endl;
  #else
    qDebug() << "SSE is not used." << endl;
  #endif

//    qDebug() << "Image size (wxh): " << img_data.width << "x"
//        << img_data.height << endl;

    cv::Rect face_rect;
    int32_t num_face = static_cast<int32_t>(faces.size());

    for (int32_t i = 0; i < num_face; i++) {
      face_rect.x = faces[i].bbox.x;
      face_rect.y = faces[i].bbox.y;
      face_rect.width = faces[i].bbox.width;
      face_rect.height = faces[i].bbox.height;

      cv::rectangle(*imgin, face_rect, CV_RGB(0, 0, 255), 4, 8, 0);

      if(domosaic)
        Blender::mosaic(*imgin,face_rect);

      paDrawString(*imgin,this->rolename.c_str(), Point(face_rect.x, face_rect.y), Scalar(255,0,0), 50, true, true);
    }

    if(num_face<=0){
        hasrole=false;
        this->rolename="识别中";
    }

    if(!hasrole&&num_face>0){
        //计算出特征值
        Seetaface* sf=Seetaface::get();
        Feature feature = SingleFeatLoader::spawnFeatureWithMat(*sf, *imgin);
        connect(this->mNetManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onHttpFinish(QNetworkReply*)));
        if( !mNetManager ) {
            mNetManager = new QNetworkAccessManager(this);
        }

        QString url=URLCONFIG::SEARCH_URL;

        //将计算出的特征值传递给服务器查询

        //边界的时候这里加两杠
        QString boundary = "----weasdashDsdesd";
        //起始边界
        QString startBoundary = "--" + boundary;
        //最终结束边界
        QString endBoundary = "\r\n--" + boundary + "--\r\n";
        //设置传输类型
        QString qContentType = "multipart/form-data; boundary=" + boundary;

        //要发送的内容，这不是人脸要发送的内容，是我自己测试用的
        QByteArray content;
        QString tempStr = startBoundary;

        tempStr = "\r\n";
        tempStr +=startBoundary;
        tempStr += "\r\nContent-Disposition: form-data; name=\"feature\"\r\n\r\n";
        for(int i=0;i<2047;i++)
            tempStr +=QString::number(feature.feat[i])+" ";
        tempStr+=QString::number(feature.feat[2047]);
        content.append(tempStr.toUtf8());

        content.append(endBoundary);

        //构造http请求
        QNetworkRequest req;
        QSslConfiguration config;
        config.setPeerVerifyMode(QSslSocket::VerifyNone);
        config.setProtocol(QSsl::TlsV1SslV3);
        req.setSslConfiguration(config);
        req.setUrl(QUrl(url));
        req.setHeader(QNetworkRequest::ContentTypeHeader, qContentType.toLatin1());
        QNetworkReply * reply = mNetManager->post(req, content);
    }


//    cv::namedWindow("Test", cv::WINDOW_AUTOSIZE);
//    cv::imshow("Test", img);
//    cv::waitKey(0);
//    cv::destroyAllWindows();

      imgout=imgin;

    IplImage qImg;
    qImg = IplImage(*imgout); // cv::Mat -> IplImage
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    int timeT = time.toTime_t();
    QString strtime = QString::number(timeT);
    QString path="C:/zFetch/capture/"+strtime+".jpg";
    char*  ch;
    QByteArray ba = path.toLatin1();
    ch=ba.data();
    cvSaveImage(ch, &qImg);
    DataObjectList::getInstance()->add(path);
    qDebug()<<path;
}


void OpenCVactionCapture::GetStringSize(HDC hDC, const char* str, int* w, int* h)
{
    SIZE size;
    GetTextExtentPoint32A(hDC, str, strlen(str), &size);
    if(w != 0) *w = size.cx;
    if(h != 0) *h = size.cy;
}

void OpenCVactionCapture::paDrawString(Mat& dst, const char* str, Point org, Scalar color, int fontSize, bool italic, bool underline)
{
    CV_Assert(dst.data != 0 && (dst.channels() == 1 || dst.channels() == 3));

    int x, y, r, b;
    if(org.x > dst.cols || org.y > dst.rows) return;
    x = org.x < 0 ? -org.x : 0;
    y = org.y < 0 ? -org.y : 0;

    LOGFONTA lf;
    lf.lfHeight         = - fontSize ;
    lf.lfWidth          = 0 ;
    lf.lfEscapement     = 0 ;
    lf.lfOrientation    = 0 ;
    lf.lfWeight         = 5;
    lf.lfItalic         = italic ;  //斜体
    lf.lfUnderline      = underline ;   //下划线
    lf.lfStrikeOut       = 0 ;
    lf.lfCharSet        = DEFAULT_CHARSET ;
    lf.lfOutPrecision    = 0 ;
    lf.lfClipPrecision    = 0 ;
    lf.lfQuality         = PROOF_QUALITY ;
    lf.lfPitchAndFamily  = 0 ;
    strcpy (lf.lfFaceName, "黑体");

    HFONT hf = CreateFontIndirectA(&lf);
    HDC hDC = CreateCompatibleDC(0);
    HFONT hOldFont = (HFONT)SelectObject(hDC, hf);

    int strBaseW = 0, strBaseH = 0;
    int singleRow = 0;
    char buf[1 << 12];
    strcpy(buf, str);

    //处理多行
    {
        int nnh = 0;
        int cw, ch;
        const char* ln = strtok(buf, "\n");
        while(ln != 0)
        {
            GetStringSize(hDC, ln, &cw, &ch);
            strBaseW = max(strBaseW, cw);
            strBaseH = max(strBaseH, ch);

            ln = strtok(0, "\n");
            nnh++;
        }
        singleRow = strBaseH;
        strBaseH *= nnh;
    }

    if(org.x + strBaseW < 0 || org.y + strBaseH < 0)
    {
        SelectObject(hDC, hOldFont);
        DeleteObject(hf);
        DeleteObject(hDC);
        return;
    }

    r = org.x + strBaseW > dst.cols? dst.cols - org.x - 1 : strBaseW - 1;
    b = org.y + strBaseH > dst.rows ? dst.rows - org.y - 1 : strBaseH - 1;
    org.x = org.x < 0 ? 0 : org.x;
    org.y = org.y < 0 ? 0 : org.y;

    BITMAPINFO bmp = {0};
    BITMAPINFOHEADER& bih = bmp.bmiHeader;
    int strDrawLineStep = strBaseW * 3 % 4 == 0 ? strBaseW * 3 : (strBaseW * 3 + 4 - ((strBaseW * 3) % 4));

    bih.biSize=sizeof(BITMAPINFOHEADER);
    bih.biWidth=strBaseW;
    bih.biHeight=strBaseH;
    bih.biPlanes=1;
    bih.biBitCount=24;
    bih.biCompression=BI_RGB;
    bih.biSizeImage=strBaseH * strDrawLineStep;
    bih.biClrUsed=0;
    bih.biClrImportant=0;

    void* pDibData = 0;
    HBITMAP hBmp = CreateDIBSection(hDC, &bmp, DIB_RGB_COLORS, &pDibData, 0, 0);

    CV_Assert(pDibData != 0);
    HBITMAP hOldBmp = (HBITMAP)SelectObject(hDC, hBmp);

    //color.val[2], color.val[1], color.val[0]
    SetTextColor(hDC, RGB(255, 255, 255));
    SetBkColor(hDC, 0);
    //SetStretchBltMode(hDC, COLORONCOLOR);

    strcpy(buf, str);
    const char* ln = strtok(buf, "\n");
    int outTextY = 0;
    while(ln != 0)
    {
        TextOutA(hDC, 0, outTextY, ln, strlen(ln));
        outTextY += singleRow;
        ln = strtok(0, "\n");
    }
    uchar* dstData = (uchar*)dst.data;
    int dstStep = dst.step/sizeof(dstData[0]);
    unsigned char* pImg = (unsigned char*)dst.data + org.x * dst.channels() + org.y * dstStep;
    unsigned char* pStr = (unsigned char*)pDibData + x * 3;
    for(int tty = y; tty <= b; ++tty)
    {
        unsigned char* subImg = pImg + (tty - y) * dstStep;
        unsigned char* subStr = pStr + (strBaseH - tty - 1) * strDrawLineStep;
        for (int ttx = x; ttx <= r; ++ttx)
        {
            for (int n = 0; n < dst.channels(); ++n){
                double vtxt = subStr[n] / 255.0;
                int cvv =  vtxt * color.val[n] + (1 - vtxt) * subImg[n];
                subImg[n] = cvv > 255 ? 255 : (cvv < 0 ? 0 : cvv);
            }

            subStr += 3;
            subImg += dst.channels();
        }
    }

    SelectObject(hDC, hOldBmp);
    SelectObject(hDC, hOldFont);
    DeleteObject(hf);
    DeleteObject(hBmp);
    DeleteDC(hDC);
}

//信号来自QNetworkAccessManager
void OpenCVactionCapture::onHttpFinish(QNetworkReply* reply){
    //对reply进行解析
    if(reply->error()==QNetworkReply::NoError){
        QJsonParseError json_error;
        QJsonDocument parse_doucment = QJsonDocument::fromJson(reply->readAll(), &json_error);
        if(json_error.error == QJsonParseError::NoError)
        {
            if(parse_doucment.isObject())
            {
                QJsonObject obj = parse_doucment.object();
                if(obj.contains("name"))
                {
                    QJsonValue name_value = obj.take("name");
                    if(name_value.isString())
                    {
                        this->rolename=string((const char *)name_value.toString().toLocal8Bit());
                        //this->rolename=name_value.toString().toStdString();
                    }
                }
             }
        }
    }
}
