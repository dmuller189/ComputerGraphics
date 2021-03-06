#pragma once

#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>

#include "ObjReader.h"

/**
 * This is just a basic OpenGL widget that will allow a change of background color.
 */
class BasicWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

private:
    QString vertexShaderString() const;
    QString fragmentShaderString() const;
    void createShader();
    QOpenGLVertexArrayObject vao_;
    
    ObjReader bunny = ObjReader("../../objects/bunny_centered.obj");
    ObjReader monkey = ObjReader("../../objects/monkey_centered.obj");
    ObjReader obj;
    
    boolean showBunny = true;
    boolean wireFrameShow = false;

protected:
    // Required interaction overrides
    void keyReleaseEvent(QKeyEvent* keyEvent) override;

    // Required overrides form QOpenGLWidget
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    QOpenGLBuffer b_vbo_;
    QOpenGLBuffer b_ibo_;
    QOpenGLBuffer m_vbo_;
    QOpenGLBuffer m_ibo_;
    QOpenGLShaderProgram shaderProgram_;



public:
    BasicWidget(QWidget* parent = nullptr);
    virtual ~BasicWidget();

    // Make sure we have some size that makes sense.
    QSize sizeHint() const { return QSize(800, 600); }
};
