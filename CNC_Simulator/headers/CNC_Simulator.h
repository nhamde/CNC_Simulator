#pragma once
#include "Triangulation.h"
#include <QPushButton>
#include "OpenglWidget.h"
#include <QMessageBox>
#include <QtWidgets/QMainWindow>

using namespace Geometry;

class CNC_Simulator : public QMainWindow
{
    Q_OBJECT

private:
    void setupUi();
    //OpenGlWidget::Data convertTrianglulationToGraphicsObject(const Triangulation& inTriangulation);
    OpenGlWidget::Data convertPolylinesToGraphicsObject(const vector<vector<SurfacePoint>>& polylines);
    void readFile(const QString&);

public:
    CNC_Simulator(QWidget *parent = nullptr);
    ~CNC_Simulator();

private slots:
    void onLoadFileClick();
    void onSimulateClick();
    //void onTranslateClick();

private:
    QPushButton* loadFile;
    QPushButton* simulate;
    //QPushButton* translate;
    OpenGlWidget* openglWindowInput;
    OpenGlWidget* openglWindowOutput;

    QVector<GLfloat> vertices;


private:
    QString inputFilePath;
    QMessageBox msgBox;
    Triangulation inTri;
};
