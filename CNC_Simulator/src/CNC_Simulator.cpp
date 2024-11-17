#include "CNC_Simulator.h"
#include <QGridLayout>
#include <QFileDialog>
#include "OBJReader.h"
#include "PathCreator.h"
#include "STLWriter.h"
#include <iostream>
using namespace std;

void CNC_Simulator::setupUi()
{
    loadFile = new QPushButton("Load File", this);
    simulate = new QPushButton("Simulate", this);
    translate = new QPushButton("Translate", this);
    openglWindowInput = new OpenGlWidget(this);
    openglWindowOutput = new OpenGlWidget(this);

    QGridLayout* layout = new QGridLayout(this);

    layout->addWidget(loadFile, 0, 0, 1, 2);
    layout->addWidget(translate, 0, 2, 1, 2);
    layout->addWidget(simulate, 0, 4, 1, 2);
    layout->addWidget(openglWindowInput, 1, 0, 1, 3);
    layout->addWidget(openglWindowOutput, 1, 3, 1, 3);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(layout);
}

//OpenGlWidget::Data CNC_Simulator::convertTrianglulationToGraphicsObject(const Triangulation& inTriangulation)
//{
//    OpenGlWidget::Data data;
//    for (Triangle triangle : inTriangulation.Triangles)
//    {
//        for (Point point : triangle.Points())
//        {
//            data.vertices.push_back(inTriangulation.uniqueNumbers[point.X()]);
//            data.vertices.push_back(inTriangulation.uniqueNumbers[point.Y()]);
//            data.vertices.push_back(inTriangulation.uniqueNumbers[point.Z()]);
//        }
//
//        Point normal = triangle.Normal();
//
//        for (size_t i = 0; i < 3; i++)
//        {
//            data.normals.push_back(inTriangulation.uniqueNumbers[normal.X()]);
//            data.normals.push_back(inTriangulation.uniqueNumbers[normal.Y()]);
//            data.normals.push_back(inTriangulation.uniqueNumbers[normal.Z()]);
//        }
//    }
//    return data;
//}

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
        }
    }
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
    vector<vector<SurfacePoint>> vectorOfPoints = pc.CreatePath(inTri, 100, -100);

    OpenGlWidget::Data data = convertPolylinesToGraphicsObject(vectorOfPoints);
    openglWindowInput->setData(data);
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
}

//void CNC_Simulator::onTranslateClick()
//{
//    if (!inputFilePath.isEmpty())
//    {
//        QFileDialog dialog(this);
//
//        dialog.setFileMode(QFileDialog::Directory);
//
//        QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
//            "/home",
//            QFileDialog::ShowDirsOnly
//            | QFileDialog::DontResolveSymlinks);
//
//        // Check if directory is selected
//        if (!dir.isEmpty())
//        {
//            QString exportFileName;
//
//            //if (inputFilePath.endsWith(".stl", Qt::CaseInsensitive))
//            //{
//            //    exportFileName = QDir(dir).filePath("output.obj");
//            //    ObjWriter writer;
//            //    writer.write(exportFileName.toStdString(), triangulation);
//
//            //    // reload file to check and load in output renderer
//            //    OBJReader reader;
//            //    reader.read(exportFileName.toStdString(), triangulation);
//            //}
//
//            if (inputFilePath.endsWith(".obj", Qt::CaseInsensitive))
//            {
//                exportFileName = QDir(dir).filePath("output.stl");
//                STLWriter writer;
//                writer.write(exportFileName.toStdString(), inTri);
//            }
//
//            OpenGlWidget::Data data = convertTrianglulationToGraphicsObject(inTri);
//            openglWindowInput->setData(data);
//        }
//        else
//        {
//            msgBox.setText("No directory was selected!");
//            msgBox.exec();
//        }
//    }
//    else
//    {
//        msgBox.setText("Input file was not loaded!");
//        msgBox.exec();
//    }
//}

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
