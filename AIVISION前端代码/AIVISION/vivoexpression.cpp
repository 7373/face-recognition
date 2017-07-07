#include "vivoexpression.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

QTextToSpeech * VivoExpression::m_speech=NULL;

VivoExpression::VivoExpression()
{

}

void VivoExpression::run(){

    bool success=false;

    m_speech->say(QString::fromLocal8Bit("请微笑，请保持微笑"));
    //setHint(QString::fromLocal8Bit("请微笑，请保持微笑"));
    emit HintChanged(QString::fromLocal8Bit("请微笑，请保持微笑"));

    while (!success) {
        for(int i=0;i<1000000000;i++)
        {
           ;
        }
        success=true;
    }

    emit complete();
    m_speech->say(QString::fromLocal8Bit("认证成功"));
}

void VivoExpression::expressionCallInQml(){

    if(!m_speech)
        m_speech = new QTextToSpeech(this);
    this->start();
}

void VivoExpression::onComplete(){

}

void VivoExpression::onHintChanged(QString hint){

}
