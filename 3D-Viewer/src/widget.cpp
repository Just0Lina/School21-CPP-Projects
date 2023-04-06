#include "widget.h"

#include <QDebug>
#include <QMouseEvent>

widget::~widget() {
  makeCurrent();
  doneCurrent();
}

void widget::mousePressEvent(QMouseEvent *e) {
  mousePressPosition = QVector2D(e->pos());
}

void widget::wheelEvent(QWheelEvent *mo) {
  QPoint numDegrees = mo->angleDelta();
  if (numDegrees.y() < 0) {
    zoomScale = zoomScale / 1.1;
  }
  if (numDegrees.y() > 0) {
    zoomScale = zoomScale * 1.1;
  }

  update();
}

void widget::mouseReleaseEvent(QMouseEvent *e) {
  QVector2D diff = QVector2D(e->pos()) - mousePressPosition;
  QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();
  qreal acc = diff.length() / 100.0;
  rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();
  angularSpeed += acc;
}

void widget::timerEvent(QTimerEvent *) {
  angularSpeed *= 0.99;

  if (angularSpeed < 0.01) {
    angularSpeed = 0.0;
  } else {
    rotation =
        QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
    update();
  }
}

void widget::initColors() {
  glClearColor(color_back->redF(), color_back->greenF(), color_back->blueF(),
               0);

  int vertexLocation = m_program.attributeLocation("vertex");
  int colorLocation = m_program.uniformLocation("color");

  m_program.enableAttributeArray(vertexLocation);
  m_program.setUniformValue(colorLocation, *color_ver);
  m_program.disableAttributeArray(vertexLocation);
}

void widget::initColorsFace() {
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(color_back->redF(), color_back->greenF(), color_back->blueF(),
               0);

  int vertexLocation = m_program.attributeLocation("vertex");
  int colorLocation = m_program.uniformLocation("color");

  m_program.enableAttributeArray(vertexLocation);
  m_program.setUniformValue(colorLocation, *color_face);
  m_program.disableAttributeArray(vertexLocation);
}

void widget::initColorsVer() {  // это нужно?
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(color_back->redF(), color_back->greenF(), color_back->blueF(),
               0);

  int vertexLocation = m_program.attributeLocation("vertex");
  int colorLocation = m_program.uniformLocation("color");

  m_program.enableAttributeArray(vertexLocation);
  m_program.setUniformValue(colorLocation, *color_ver);
  m_program.disableAttributeArray(vertexLocation);
}

void widget::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT);
  glClear(GL_DEPTH_BUFFER_BIT);
  glClear(GL_ACCUM_BUFFER_BIT);
  glClear(GL_STENCIL_BUFFER_BIT);
  initShades();
  glFlush();
  geometries = new s21::GeometryEngine();
  if (loadflag == 1) {
    geometries->filepath = filepath;
  }
  geometries->parsingObj();
  geometries->lineWidth = lineWidth;
  geometries->size_of_ver = size_of_ver;
  timer.start(12, this);
}

void widget::updating() { update(); }

void widget::initShades() {
  if (!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                         ":vshader.glsl")) {
    close();
  }
  if (!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                         ":fshader.glsl")) {
    close();
  }
  if (!m_program.link()) {
    close();
  }
  if (!m_program.bind()) {
    close();
  }
}

void widget::resizeGL(int w, int h) {
  qreal aspect = qreal(w) / qreal(h ? h : 1);
  const qreal zNear = 0.1, zFar = 1000.0, fov = 45.0;
  m_projectionMatrix.setToIdentity();
  if (flagParallel) {
    QRectF orthoRect;
    orthoRect.setHeight(h);
    orthoRect.setWidth(w);
    m_projectionMatrix.ortho(-aspect, aspect, -1.0, 1.0, zNear, zFar);
  } else {
    m_projectionMatrix.perspective(fov, aspect, zNear, zFar);
  }
}

void widget::paintGL() {
  initColorsVer();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  initColors();
  initColorsFace();

  QMatrix4x4 modelViewMatrix;
  modelViewMatrix.translate(0.0, 0.0, -5.0);
  modelViewMatrix.rotate(rotation);
  modelViewMatrix.scale(zoomScale);

  m_program.setUniformValue("mvp_matrix", m_projectionMatrix * modelViewMatrix);
  if (geometries->filepath != "") {
    if (typeOfLine == 1) {
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(1, 0x00F0);
      geometries->f_ver = f_ver;
      geometries->f_sphere = f_sphere;
      geometries->drawing(&m_program);
      if (f_ver) {
        initColors();
        geometries->drawing_vertex(&m_program);
      }
      glDisable(GL_LINE_STIPPLE);
    } else {
      initColorsFace();
      geometries->f_ver = f_ver;
      geometries->f_sphere = f_sphere;
      geometries->drawing(&m_program);
      if (f_ver) {
        initColors();
        geometries->drawing_vertex(&m_program);
      }
    }
  }
}
