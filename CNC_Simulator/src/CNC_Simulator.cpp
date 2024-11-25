#include "CNC_Simulator.h"
#include <QGridLayout>
#include <QFileDialog>
#include "OBJReader.h"
#include "PathCreator.h"
#include <iostream>
using namespace std;

void CNC_Simulator::setupUi()
{
    loadFile = new QPushButton("Load File", this);
    simulate = new QPushButton("Simulate", this);
    openglWindowInput = new OpenGlWidget(this);
    openglWindowOutput = new OpenGlWidget(this);

    QGridLayout* layout = new QGridLayout(this);

    graphicsSynchronizer = new GraphicsSynchronizer(openglWindowInput, openglWindowOutput);

    layout->addWidget(loadFile, 0, 0, 1, 1);
    layout->addWidget(simulate, 0, 1, 1, 1);
    layout->addWidget(openglWindowInput, 1, 0, 1, 1);
    layout->addWidget(openglWindowOutput, 1, 1, 1, 1);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(layout);
}

OpenGlWidget::Data CNC_Simulator::convertTrianglulationToGraphicsObject(const Triangulation& inTriangulation)
{
    OpenGlWidget::Data data;
    for (Triangle triangle : inTriangulation.Triangles)
    {
        vector<Point> pts = triangle.Points();
        Point normal = triangle.Normal();

        for (size_t i = 0; i < pts.size(); i++)
        {
            data.vertices.push_back(inTriangulation.uniqueNumbers[pts[i].X()]);
            data.vertices.push_back(inTriangulation.uniqueNumbers[pts[i].Y()]);
            data.vertices.push_back(inTriangulation.uniqueNumbers[pts[i].Z()]);
            data.normals.push_back(inTriangulation.uniqueNumbers[normal.X()]);
            data.normals.push_back(inTriangulation.uniqueNumbers[normal.Y()]);
            data.normals.push_back(inTriangulation.uniqueNumbers[normal.Z()]);
            data.colors.push_back(1.0);
            data.colors.push_back(0.0);
            data.colors.push_back(0.0);
        }
    }
    data.drawStyle = OpenGlWidget::DrawStyle::TRIANGLES;
    return data;
}

OpenGlWidget::Data CNC_Simulator::convertPolylinesToGraphicsObject(const vector<vector<SurfacePoint>>& polylines)
{
    OpenGlWidget::Data data;
    for (auto polyline : polylines)
    {
        for (auto point : polyline)
        {
            data.vertices.push_back(point.X());
            data.vertices.push_back(point.Y());
            data.vertices.push_back(point.Z());
            data.colors.push_back(1.0);
            data.colors.push_back(0.0);
            data.colors.push_back(0.0);
        }
    }
    data.drawStyle = OpenGlWidget::DrawStyle::LINES;
    return data;
}

OpenGlWidget::Data CNC_Simulator::convertBoundingBoxToGraphicsObject(Triangulation& tri)
{
    OpenGlWidget::Data data;
    vector<SurfacePoint> vertices = tri.boundingBox.getBounds();
    vector<pair<int, int>> edges = {
       {4, 6}, {6, 7}, {7, 5}, {5, 4}, // Bottom face
       {0, 2}, {2, 3}, {3, 1}, {1, 0}, // Top face
       {4, 0}, {6, 2}, {7, 3}, {5, 1}  // Vertical edges
    };
    
    for (const auto& edge : edges) {
        int start = edge.first;
        int end = edge.second;
        data.vertices.push_back(vertices[start].X());
        data.vertices.push_back(vertices[start].Y());
        data.vertices.push_back(vertices[start].Z());
        data.colors.push_back(1.0); // R
        data.colors.push_back(0.0); // G
        data.colors.push_back(0.0); // B

        data.vertices.push_back(vertices[end].X());
        data.vertices.push_back(vertices[end].Y());
        data.vertices.push_back(vertices[end].Z());
        data.colors.push_back(1.0); // R
        data.colors.push_back(0.0); // G
        data.colors.push_back(0.0); // B
    }
    data.drawStyle = OpenGlWidget::DrawStyle::LINES;
    return data;
}

CNC_Simulator::CNC_Simulator(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();

    connect(loadFile, &QPushButton::clicked, this, &CNC_Simulator::onLoadFileClick);
    connect(simulate, &QPushButton::clicked, this, &CNC_Simulator::onSimulateClick);
}

CNC_Simulator::~CNC_Simulator()
{}

void CNC_Simulator::onSimulateClick()
{
    PathCreator pc;
    vector<vector<SurfacePoint>> vectorOfPoints = pc.createPath(inTri, 20, -20);

    //OpenGlWidget::Data data = convertPolylinesToGraphicsObject(vectorOfPoints);
    OpenGlWidget::Data data =  convertBoundingBoxToGraphicsObject(inTri);
    openglWindowOutput->addObject(data);

    cout << "Total number of polylines: " << vectorOfPoints.size() << endl;
    cout << "Polylines data is set successfully" << endl;
}


void  CNC_Simulator::onLoadFileClick()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "", tr("files (*.stl *.obj)"));

    if (!fileName.isEmpty())
    {
        inputFilePath = fileName;
        readFile(inputFilePath);
    }
    else
    {
        msgBox.setText("No file was selected");
        msgBox.exec();
    }
    OpenGlWidget::Data data = convertTrianglulationToGraphicsObject(inTri);
    openglWindowInput->addObject(data);
}

void CNC_Simulator::readFile(const QString& inFileName)
{
    if (inFileName.endsWith(".obj", Qt::CaseInsensitive))
    {
        OBJReader reader;
        reader.read(inFileName.toStdString(), inTri);
        cout << "Obj file is read successfully" << endl;
    }
    /*else if (inFileName.endsWith(".stl", Qt::CaseInsensitive))
    {
        STLReader reader;
        reader.read(inFileName.toStdString(), inTri);
    }*/
}
