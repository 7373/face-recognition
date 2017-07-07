#include "opencvcapture.h"

OpenCVcapture::OpenCVcapture(QObject *parent) : QObject(parent)
{

}

OpenCVcapture::~OpenCVcapture()
{

}

bool OpenCVcapture::run() const
{
    return m_run;
}


void OpenCVcapture::setRun(bool r)
{
    m_run = r;
}

