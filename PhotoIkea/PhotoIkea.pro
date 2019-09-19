TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp
INCLUDEPATH += /usr/local/Cellar/opencv/4.1.0_1/include/opencv4\
LIBS += -L/usr/local/lib -L/usr/local/Cellar/opencv/4.1.0_1/lib\
     -lopencv_core \
     -lopencv_imgproc \
     -lopencv_features2d\
     -lopencv_highgui \
     -lopencv_imgcodecs

QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
PKGCONFIG += opencv

# /usr/local/Cellar/opencv/4.1.0_1/include/opencv4
#/usr/local/include


#/usr/local/lib
#/usr/local/Cellar/opencv/4.0.1/lib
