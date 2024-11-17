#include "OpenGlWidget.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>
using namespace Geometry;
using namespace std;

OpenGlWidget::OpenGlWidget(QWidget* parent)
    : QOpenGLWidget(parent),
    vbo(QOpenGLBuffer::VertexBuffer),
    isInitialized(false)
{
}

OpenGlWidget::~OpenGlWidget() {
    makeCurrent();
    vbo.destroy();
    doneCurrent();
}

void OpenGlWidget::setData(Data inData)
{
    data = inData;
    makeCurrent();
    initializeGL();
    update();
}

QSize OpenGlWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize OpenGlWidget::sizeHint() const
{
    return QSize(800, 800);
}

void OpenGlWidget::initializeGL()
{
    if (data.vertices.size() > 0)
    {
        initializeOpenGLFunctions();
        glEnable(GL_DEPTH_TEST);

        // Load shader program
        bool shaderLoaded = false;

        shaderLoaded = shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "./shaders/vertex.glsl");
        shaderLoaded = shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "./shaders/fragment.glsl");
        shaderProgram.link();

        // Load STL data
        //loadSTL("path/to/your/model.stl");

        // Prepare VBO

        std::vector<float> vertexData;
        for (int i = 0; i < data.vertices.size(); i++)
        {
            vertexData.push_back(data.vertices[i]);
        }

        vbo.create();
        vbo.bind();
        vbo.allocate(vertexData.data(), static_cast<int>(vertexData.size() * sizeof(float)));

        shaderProgram.bind();
        shaderProgram.enableAttributeArray(0);
        shaderProgram.setAttributeBuffer(0, GL_FLOAT, 0, 3, 3 * sizeof(float));
        shaderProgram.release();
        isInitialized = true;
    }
}


void OpenGlWidget::resizeGL(int w, int h) {
    if (isInitialized == true)
    {
        glViewport(0, 0, w, h);
    }
    projection.setToIdentity();
    projection.perspective(45.0f, float(w) / float(h), 0.1f, 100.0f);
}

void OpenGlWidget::paintGL()
{
    if (isInitialized == true)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        updateModelViewMatrix();

        shaderProgram.bind();
        shaderProgram.setUniformValue("projection", projection);
        shaderProgram.setUniformValue("modelView", modelView);

        QVector3D lightPos(0.5f, 0.5f, 1.0f);
        shaderProgram.setUniformValue("lightPos", lightPos);
        shaderProgram.setUniformValue("viewPos", QVector3D(0.0f, 0.0f, 5.0f));

        glLineWidth(3.0f);

        vbo.bind();
        glDrawArrays(GL_LINE_STRIP, 0, data.vertices.size()/3);
        vbo.release();

        shaderProgram.release();
    }
}

void OpenGlWidget::updateModelViewMatrix() {
    modelView.setToIdentity();
    modelView.translate(panOffset.x(), panOffset.y(), -5.0f);
    modelView.scale(zoomLevel);
    modelView.rotate(rotation.x(), 1.0f, 0.0f, 0.0f);
    modelView.rotate(rotation.y(), 0.0f, 1.0f, 0.0f);
    modelView.rotate(rotation.z(), 0.0f, 0.0f, 1.0f);
}

void OpenGlWidget::wheelEvent(QWheelEvent* event) {
    // Zoom in or out
    if (event->angleDelta().y() > 0)
        zoomLevel *= 1.1f;  // Zoom in
    else
        zoomLevel /= 1.1f;  // Zoom out
    update();

}

void OpenGlWidget::mousePressEvent(QMouseEvent* event) {
    lastMousePosition = event->pos();
}

void OpenGlWidget::mouseMoveEvent(QMouseEvent* event) {
    QPoint delta = event->pos() - lastMousePosition;
    lastMousePosition = event->pos();

    if (event->buttons() & Qt::LeftButton) {
        // Rotate model
        rotation.setX(rotation.x() + delta.y() * 0.5f);
        rotation.setY(rotation.y() + delta.x() * 0.5f);
    }
    else if (event->buttons() & Qt::RightButton) {
        // Pan model
        panOffset.setX(panOffset.x() + delta.x() * 0.01f);
        panOffset.setY(panOffset.y() - delta.y() * 0.01f);
    }
    update();
}
