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

        vector<float> vertexData;
        vector<float> normalsData;
        for (int i = 0; i < data.vertices.size(); i++)
        {
            vertexData.push_back(data.vertices[i]);

            QVector3D normal(0.0f, 1.0f, 0.0f); // Simple fake normal pointing up (adjust accordingly)
            normalsData.push_back(normal.x());
            normalsData.push_back(normal.y());
            normalsData.push_back(normal.z());
        }

        vbo.create();
        vbo.bind();
        vector<float> combinedData;
        combinedData.insert(combinedData.end(), vertexData.begin(), vertexData.end());
        combinedData.insert(combinedData.end(), normalsData.begin(), normalsData.end());
        vbo.allocate(combinedData.data(), static_cast<int>(combinedData.size() * sizeof(float)));

        shaderProgram.bind();
        shaderProgram.enableAttributeArray(0);
        shaderProgram.setAttributeBuffer(0, GL_FLOAT, 0, 3, 6 * sizeof(float));
        shaderProgram.enableAttributeArray(1); // Normal attribute
        shaderProgram.setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(float), 3, 6 * sizeof(float)); // Normal buffer
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
        QVector3D viewPos(0.0f, 0.0f, 5.0f);   // Example camera position

        shaderProgram.setUniformValue("lightPos", lightPos);
        shaderProgram.setUniformValue("viewPos", viewPos);

        glEnable(GL_LINE_SMOOTH);

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
