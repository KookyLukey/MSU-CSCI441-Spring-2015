#include "glwidget.h"
#include <iostream>

using namespace std;

GLWidget::GLWidget(const QGLFormat &format, QWidget *parent) : QGLWidget(format, parent) {
    setAutoBufferSwap(false);
}

GLWidget::~GLWidget() {
}

void GLWidget::initializeGL() {
    initializeOpenGLFunctions();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Create a new Vertex Array Object on the GPU which
    // saves the attribute layout of our vertices.
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // position data for a single triangle
    Point pts[3] = {
        Point(0,1),
        Point(1,0),
        Point(0,-1)
    };

    // Create a buffer on the GPU for position data
    GLuint positionBuffer;
    glGenBuffers(1, &positionBuffer);

    // Upload the position data to the GPU, storing
    // it in the buffer we just created.
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pts), pts, GL_STATIC_DRAW);

    // Load our vertex and fragment shaders into a program object
    // on the GPU
    GLuint program = loadShaders();

    // Bind the attribute "position" (defined in our vertex shader)
    // to the currently bound buffer object, which contains our
    // position data for a single triangle. This information 
    // is stored in our vertex array object.
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    GLint positionIndex = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(positionIndex);
    glVertexAttribPointer(positionIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0,0,w,h);
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

GLuint GLWidget::loadShaders() {
    GLuint program = glCreateProgram();

    const GLchar* vertSource = 
        "#version 330\n"
        "in vec2 position;\n"
        "void main() {\n"
        "  gl_Position = vec4(position.x, position.y, 0, 1);\n"
        "}\n";

    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &vertSource, NULL);
    glCompileShader(vertShader);
    {
        GLint compiled;
        glGetShaderiv( vertShader, GL_COMPILE_STATUS, &compiled );
        if ( !compiled ) {
            GLsizei len;
            glGetShaderiv( vertShader, GL_INFO_LOG_LENGTH, &len );

            GLchar* log = new GLchar[len+1];
            glGetShaderInfoLog( vertShader, len, &len, log );
            std::cout << "Shader compilation failed: " << log << std::endl;
            delete [] log;
        }
    }
    glAttachShader(program, vertShader);
    
    const GLchar* fragSource = 
        "#version 330\n"
        "out vec4 color_out;\n"
        "void main() {\n"
        "  color_out = vec4(1.0, 1.0, 1.0, 1.0);\n"
        "}\n";
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragSource, NULL);
    glCompileShader(fragShader);
    {
        GLint compiled;
        glGetShaderiv( fragShader, GL_COMPILE_STATUS, &compiled );
        if ( !compiled ) {
            GLsizei len;
            glGetShaderiv( fragShader, GL_INFO_LOG_LENGTH, &len );

            GLchar* log = new GLchar[len+1];
            glGetShaderInfoLog( fragShader, len, &len, log );
            std::cerr << "Shader compilation failed: " << log << std::endl;
            delete [] log;
        }
    }
    glAttachShader(program, fragShader);

    glLinkProgram(program);
    glUseProgram(program);

    return program;
}

Point GLWidget::w2nd(Point pt_w) {
    /* convert pt_w to normalized device coordinates */
    /* use this method to convert your input coordinates to
       normalized device coordinates */
    return pt_w;
}


