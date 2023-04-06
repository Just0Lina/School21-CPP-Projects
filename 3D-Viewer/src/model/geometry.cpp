#include "geometry.h"

//#include <QDebug>
//#include <QDir>
//#include <QFile>
//#include <QString>
//#include <QVector2D>
//#include <QVector3D>
//#include <QVector>
//#include <string>

#include "../controller/controller.h"

namespace s21 {
struct VertexData {
  QVector3D position;
};

GeometryEngine::GeometryEngine() : indexBuff(QOpenGLBuffer::IndexBuffer) {
  initializeOpenGLFunctions();
  arrayBuff.create();
  indexBuff.create();
}

GeometryEngine::~GeometryEngine() {
  arrayBuff.destroy();
  indexBuff.destroy();
}

void GeometryEngine::parsingObj() {
  QFile file(filepath);
  naming = "";
  if (!file.exists()) {
    return;
  } else {
    naming = file.fileName();
    std::string name = naming.toStdString();
    controller.modelDataFillCall(name);
    vCount = QString::number(controller.GetVertCall().size() / 3);
    fCount = QString::number(controller.GetPolygonCall().size() / 2);

    binding();

    std::vector<unsigned> polygon_tmp = controller.GetPolygonCall();
    QVector<GLuint> indexes;
    for (size_t i = 0; i < polygon_tmp.size(); i++) {
      indexes.push_back(polygon_tmp[i]);
    }

    lines = indexes.size();
    indexBuff.bind();
    indexBuff.allocate(indexes.data(), sizeof(GLuint) * indexes.size());
  }
}

void GeometryEngine::binding() {
  std::vector<double> vert_tmp = controller.GetVertCall();
  QVector<VertexData> vertexes;
  for (size_t j = 0; j < vert_tmp.size(); j += 3) {
    VertexData temp = {
        (QVector3D(vert_tmp[j], vert_tmp[j + 1], vert_tmp[j + 2]))};
    vertexes.push_back(temp);
  }
  arrayBuff.bind();
  arrayBuff.allocate(vertexes.data(), sizeof(VertexData) * vertexes.size());
}

void GeometryEngine::drawing(QOpenGLShaderProgram *m_program) {
  if (f_ver) {
    if (f_sphere) {
      glDisable(GL_POINT_SIZE);
      glEnable(GL_POINT_SMOOTH);
    } else {
      glDisable(GL_POINT_SMOOTH);
      glEnable(GL_POINT_SIZE);
    }
  }
  glPointSize(size_of_ver);

  glLineWidth(lineWidth);

  binding();
  arrayBuff.bind();
  indexBuff.bind();

  quintptr offset = 0;

  int vertexLoc = m_program->attributeLocation("a_position");
  m_program->enableAttributeArray(vertexLoc);
  m_program->setAttributeBuffer(vertexLoc, GL_FLOAT, offset, 3,
                                sizeof(VertexData));

  offset += sizeof(QVector3D);

  int texcoordLoc = m_program->attributeLocation("a_texcoord");
  m_program->enableAttributeArray(texcoordLoc);
  m_program->setAttributeBuffer(texcoordLoc, GL_FLOAT, offset, 2,
                                sizeof(VertexData));

  glDrawElements(GL_LINES, lines, GL_UNSIGNED_INT, nullptr);
}

void GeometryEngine::drawing_vertex(QOpenGLShaderProgram *m_program) {
  if (f_ver) {
    if (f_sphere) {
      glDisable(GL_POINT_SIZE);
      glEnable(GL_POINT_SMOOTH);
      glPointSize(size_of_ver);
    } else {
      glDisable(GL_POINT_SMOOTH);
      glEnable(GL_POINT_SIZE);
      glPointSize(size_of_ver);
    }
  } else {
    glDisable(GL_POINT_SMOOTH);
    glDisable(GL_POINT_SIZE);
    glPointSize(1);
  }

  glLineWidth(lineWidth);

  binding();
  arrayBuff.bind();
  indexBuff.bind();

  quintptr offset = 0;

  int vertexLoc = m_program->attributeLocation("a_position");
  m_program->enableAttributeArray(vertexLoc);
  m_program->setAttributeBuffer(vertexLoc, GL_FLOAT, offset, 3,
                                sizeof(VertexData));

  offset += sizeof(QVector3D);

  int texcoordLoc = m_program->attributeLocation("a_texcoord");
  m_program->enableAttributeArray(texcoordLoc);
  m_program->setAttributeBuffer(texcoordLoc, GL_FLOAT, offset, 2,
                                sizeof(VertexData));

  glDrawElements(GL_POINTS, lines, GL_UNSIGNED_INT, nullptr);
}
}  // namespace s21
