#include "capture.h"
#include "dataobjectlist.h"
#include "dataobjectcapture.h"

Capture::Capture()
{

}
void Capture::run(){

     //计算人脸特征值
    for(int i=0;i<1000000000;i++)
    {
       ;
    }
    //计算出特征值后比较得出结果

}

void Capture::captureCallInQml(){
    //DataObjectList::datalist.append(new DataObjectCapture("file:///C:/Users/chwan/Desktop/timgVW4B6Y3D.jpg"));


    qDebug()<<DataObjectList::getInstance()->datalist.size()<<endl;
}

void Capture::stopCallInQml(){

}
