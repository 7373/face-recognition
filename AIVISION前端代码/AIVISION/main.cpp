#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QWindow>
#include <QQmlContext>
#include <QStandardPaths>
#include <QDir>
#include "register.h"
#include "identify.h"
#include "quality.h"
#include "vivoexpression.h"
#include "search.h"
#include "capture.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencvcamera.h"
#include "opencvshowframe.h"
#include "opencvshowframecapture.h"
#include "dataobjectlist.h"
#include <QList>
#include "dataobjectcapture.h"
#include "AivisionFromChai/Aivision/Seetaface/include/seetaface.h"


int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<Register>("cn.chwangteng.Register", 1, 0, "Register");
    qmlRegisterType<Identify>("cn.chwangteng.Identify", 1, 0, "Identify");
    qmlRegisterType<Quality>("cn.chwangteng.Quality", 1, 0, "Quality");
    qmlRegisterType<VivoExpression>("cn.chwangteng.VivoExpression", 1, 0, "VivoExpression");
    qmlRegisterType<Search>("cn.chwangteng.Search", 1, 0, "Search");
    qmlRegisterType<Capture>("cn.chwangteng.Capture", 1, 0, "Capture");

    qmlRegisterType<OpenCVcamera>("OpenCV", 1, 0, "OpenCVcamera");
    qmlRegisterType<OpenCVshowFrame>("OpenCV", 1, 0, "OpenCVshowFrame");
    qmlRegisterType<OpenCVshowFrameCapture>("OpenCV", 1, 0, "OpenCVshowFrameCapture");

    QQmlApplicationEngine engine;

    //指定上下文，设置为图片选择路径
    const QStringList picturePaths = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    const QUrl pictureUrl = QUrl::fromLocalFile(picturePaths.isEmpty() ? QDir::homePath() : picturePaths.first());
    engine.rootContext()->setContextProperty(QStringLiteral("pictureUrl"), pictureUrl);

    //DataObjectList::getInstance()->datalist.append(new DataObjectCapture("file:///C:/Users/chwan/Desktop/timgVW4B6Y3D.jpg"));
    engine.rootContext()->setContextProperty("myModel", QVariant::fromValue(DataObjectList::getInstance()));

    engine.load(QUrl(QLatin1String("qrc:/Main.qml")));


    return app.exec();
}
