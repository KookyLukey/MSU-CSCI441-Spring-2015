#ifndef __GLWIDGET__INCLUDE__
#define __GLWIDGET__INCLUDE__

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <glm/glm.hpp>

// glm by default uses degrees, but that functionality
// is deprecated so GLM_FORCE_RADIANS turns off some 
// glm warnings
#define GLM_FORCE_RADIANS

using namespace glm;

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

    public:
        GLWidget(QWidget *parent=0);
        ~GLWidget();

    protected:
        void initializeGL();
        void resizeGL(int w, int h);
        void paintGL();

        void mousePressEvent(QMouseEvent *event);
        void keyPressEvent(QKeyEvent *event);

    private:
        GLuint loadShaders();
        static const GLchar* readShader(const char* filename);

        GLuint positionBuffer;
        bool outline;
        GLenum drawMode;

        vec2 pts[3];
        int num_pts;
};

#endif
