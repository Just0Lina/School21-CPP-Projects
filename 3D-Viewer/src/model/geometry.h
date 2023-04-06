#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QDir>
#include <QFile>
#include <QString>
#include <QVector2D>
#include <QVector3D>
#include <QVector>

#include <unistd.h>
#include <string>
#include <iostream>

#include "../controller/controller.h"

namespace s21 {
class GeometryEngine : protected QOpenGLFunctions {
    struct VertexData {
        QVector3D position;
    };

 public:
    GeometryEngine();
    virtual ~GeometryEngine();

    QString filepath, vCount, fCount, naming;

    double lineWidth = 1.0;

    unsigned int vertexCount = 0, facetsCount = 0;

    int typeOfLine = 0, flagParallel = 0, flagVertexOn = 0,
    f_ver = 0, f_sphere = 0, size_of_ver = 2;

    void drawing(QOpenGLShaderProgram *m_program);
    void binding();
    void parsingObj();
    void scaling(double val);
    void drawing_vertex(QOpenGLShaderProgram *m_program);

    int countF();
    int countEDGES();

 private:
    QOpenGLBuffer arrayBuff;
    QOpenGLBuffer indexBuff;

    GLsizei lines;
    Controller &controller{Controller::getInstance()};

    //s21::Controller *controller;
};
}

#endif  // GEOMETRY_H
