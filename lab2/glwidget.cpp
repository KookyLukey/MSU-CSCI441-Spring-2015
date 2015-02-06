#include "glwidget.h"
#include <iostream>

using namespace std;

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) {
}

GLWidget::~GLWidget() {
}

void GLWidget::initializeGL() {
    initializeOpenGLFunctions();

    float x1,x2,x3,y1,y2,y3;
    float r1,r2,r3,g1,g2,g3,b1,b2,b3;

    //Gets 3 coordinate points from user

    cout << "Your triangle can be a max of 640 pixels wide and 480 pixels tall \n";
    cout << "Please enter your first set of coordinates: ";
    cin >> x1 >> y1;
    cout << "Your coordinates for this point are (" << x1 << "," << y1 << ")\n";

    cout << "Please enter your second set of coordinates: ";
    cin >> x2 >> y2;
    cout << "Your coordinates for this point are (" << x2 << "," << y2 << ")\n";

    cout << "Please enter your third set of coordinates: ";
    cin >> x3 >> y3;
    cout << "Your coordinates for this point are (" << x3 << "," << y3 << ")\n";

    //Gets 3 color values for each point

    cout << "Please enter your rgb colors for point one ranging from 0 to 1 (r value, g value, b value)\n";
    cin >> r1 >> g1 >> b1;
    cout << "Your r value is: " << r1 <<" Your g value is: " << g1 << " Your b value is: " << b1 << "\n";

    cout << "Please enter your rgb colors for point one ranging from 0 to 1 (r value, g value, b value)\n";
    cin >> r2 >> g2 >> b2;
    cout << "Your r value is: " << r2 <<" Your g value is: " << g2 << " Your b value is: " << b2 << "\n";

    cout << "Please enter your rgb colors for point one ranging from 0 to 1 (r value, g value, b value)\n";
    cin >> r3 >> g3 >> b3;
    cout << "Your r value is: " << r3 <<" Your g value is: " << g3 << " Your b value is: " << b3 << "\n";



    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Create a new Vertex Array Object on the GPU which
    // saves the attribute layout of our vertices.
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // position data for a single triangle
    Point pts[3] = {
        Point(x1,y1),
        Point(x2,y2),
        Point(x3,y3)
    };

    Color rgb[3] = {
        Color(r1,g1,b1),
        Color(r2,g2,b2),
        Color(r3,g3,b3)
    };

//    x1 =  -1 + x1 * (1/320);
//    x2 =  -1 + x2 * (1/320);
//    x3 =  -1 + x3 * (1/320);
//    cout << x1 << " " << x2 << " " << x3;

//    y1 = 1 - y1 * (1/240);
//    y2 = 1 - y2 * (1/240);
//    y3 = 1 - y3 * (1/240);
//    cout << y1 << " " << y2 << " " << y3;

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



    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rgb), rgb, GL_STATIC_DRAW);

    // Load our vertex and fragment shaders into a program object
    // on the GPU
    //GLuint colorProgram = loadShaders();

    // Bind the attribute "position" (defined in our vertex shader)
    // to the currently bound buffer object, which contains our
    // position data for a single triangle. This information
    // is stored in our vertex array object.
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    //GLint colorIndex = glGetAttribLocation(colorProgram, "color");
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
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
        "layout(location = 1) in vec3 vertexColor;\n"
        "out vec3 fragmentColor;\n"
        "void main() {\n"
        "  gl_Position = vec4(position.x, position.y, 0, 1);\n"
        "  fragmentColor = vertexColor;\n"
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
        "in vec3 fragmentColor;\n"
        "out vec3 color;\n"
        "void main() {\n"
        "  color_out = vec4(1.0, 1.0, 1.0, 1.0);\n"
        "  color = fragmentColor;\n"
        "\n"
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
//    pt_w.x = -1 + pt_w.x * (1/320);
//    cout << pt_w.x << "\n";
//    pt_w.y = 1 - pt_w.y * (1/240);
//    cout << pt_w.y << "\n";

    return pt_w;
}


