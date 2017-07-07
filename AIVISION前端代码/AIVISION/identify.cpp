#include "identify.h"
#include "AivisionFromChai/Aivision/Seetaface/include/seetaface.h"

Identify::Identify()
{

}
void Identify::identifyCallInQml(QString imageSource, QString imageSource2){
    this->imageSource=imageSource.mid(8);
    this->imageSource2=imageSource2.mid(8);
    this->start();
}


void Identify::run(){

     //计算人脸特征值

    Seetaface* sf=Seetaface::get();

    Feature f1 = SingleFeatLoader::spawnFeature(*sf, this->imageSource.toStdString());
    Feature f2 = SingleFeatLoader::spawnFeature(*sf, this->imageSource2.toStdString());
    float simi=FaceRecognizer::similarity(*sf, f1, f2);

    //计算出特征值后比较得出结果

    QString data = QString("%1").arg(simi);

    setSimilarity(data);

    emit complete();
    qDebug()<<"identification finished";
}

void Identify::onComplete(){

}

