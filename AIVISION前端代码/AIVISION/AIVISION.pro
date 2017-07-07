QT += texttospeech
QT += qml quick

CONFIG += c++11

SOURCES += main.cpp \
    register.cpp \
    identify.cpp \
    quality.cpp \
    vivoexpression.cpp \
    search.cpp \
    opencvcapture.cpp \
    opencvcamera.cpp \
    opencvshowframe.cpp \
    opencvaction.cpp \
    opencvcommonaction.cpp \
    utils.cpp \
    capture.cpp \
    opencvactioncapture.cpp \
    opencvshowframecapture.cpp \
    dataobjectcapture.cpp \
    dataobjectlist.cpp \
    AivisionFromChai/Aivision/Seetaface/faceRecognizer.cpp \
    AivisionFromChai/Aivision/Seetaface/seetaface.cpp \
    AivisionFromChai/Aivision/Seetaface/singleFeatLoader.cpp \
    glcm.cpp \
    urlconfig.cpp

INCLUDEPATH += AivisionFromChai/opencv/build/include \
                AivisionFromChai/seetaface/include

LIBS += -L../AIVISION/AivisionFromChai/opencv/build/x86/vc12/lib \
        -L../AIVISION/AivisionFromChai/seetaface/lib/x86 \
        -L../AIVISION/AivisionFromChai/gdi \
        -lopencv_highgui2413 \
        -lopencv_core2413 \
        -lopencv_imgproc2413 \
        -lFaceDetection \
        -lFaceAlignment \
        -lFaceIdentification \
        -lGdi32

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    register.h \
    identify.h \
    quality.h \
    vivoexpression.h \
    search.h \
    opencvcapture.h \
    opencvcamera.h \
    opencvshowframe.h \
    opencvaction.h \
    opencvcommonaction.h \
    utils.h \
    capture.h \
    opencvactioncapture.h \
    opencvshowframecapture.h \
    dataobjectcapture.h \
    dataobjectlist.h \
    AivisionFromChai/Aivision/Seetaface/include/seetaface.h \
    AivisionFromChai/Aivision/Seetaface/include/util.h \
    glcm.h \
    urlconfig.h
