#include <QApplication>

#include "glwidget.h"
#include <iostream>

using namespace std;

void printOpenGLInfo() {
    const GLubyte* version = glGetString(GL_VERSION);
    cout << version << endl;

    const GLubyte* vendor = glGetString(GL_VENDOR);
    cout << vendor << endl;

    const GLubyte* renderer = glGetString(GL_RENDERER);
    cout << renderer << endl;

    const GLubyte* shaderVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    cout << shaderVersion << endl;

    int numExtensions;
    glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);

    for(int i = 0; i < numExtensions; i++) {
        const GLubyte* extension = glGetStringi(GL_EXTENSIONS,i);
        cout << extension << endl;
    }

}

int main(int argc, char** argv) {
    QApplication a(argc, argv);

    QGLFormat format;
    format.setVersion(3,3);  // set a modern version of OpenGL
    format.setProfile(QGLFormat::CoreProfile); 
    format.setDoubleBuffer(false);
    format.setDepth(false);

    GLWidget glWidget(format);
    qreal pixelRatio = glWidget.devicePixelRatio();
    glWidget.resize(640/pixelRatio,480/pixelRatio);
    glWidget.show();

    printOpenGLInfo();

    return a.exec();
}
