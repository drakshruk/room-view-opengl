#ifndef GLVIEW_H
#define GLVIEW_H

#include <QOpenGLWidget>
#include <QtOpenGL/QtOpenGL>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <QVector>
#include <dialog.h>

struct car
{
    QVector3D pos, lookAt;              // pos - координаты, lookAt - куда смотрим
    double rotCar, rotWheel;            //поворот машины и колес
    double carVelocity, wheelVelocity;  // скорость машины и поворота колес
    bool iDrive;                        // если true то катаемся сами, если false то по траектории
    void setPos(double x, double y, double z)
    {
        pos.setX(x);
        pos.setY(y);
        pos.setZ(z);
    }
    void look(double x, double y, double z)
    {
        lookAt.setX(x);
        lookAt.setY(y);
        lookAt.setZ(z);
    }
    void rotate(double phi, double x, double y, double z)
    {
        lookAt.setX(x*cos(phi) - z*sin(phi));
        lookAt.setY(y);
        lookAt.setZ(x*sin(phi) + z*cos(phi));
    }
    void setVelocity(double vC, double vW)
    {
        carVelocity = vC; wheelVelocity = vW;
    }
    void setRot(double rC, double rW)
    {
        rotCar = rC; rotWheel = rW;
    }
    void setMode(bool flag) {iDrive = flag;}
    double mod()
    {
        return sqrt(pos.x()*pos.x()+pos.y()*pos.y()+pos.z()*pos.z());
    }
};

class glView : public QOpenGLWidget
{
        Q_OBJECT
    public:
        glView(QWidget* parent = nullptr);
        void initializeGL();
        void resizeGL(int w, int h);
        void paintGL();

        void paintRoom(double a, double r, double g, double b, bool carcas);
        void paintTable(double x0, double y0, double z0, double length2, double height2, double width2, bool carcas);
        void paintDoor(double x0, double y0, double z0, double length1, double height1, double width1, bool carcas);
        void paintChest(double x0, double y0, double z0, double length1, double height1, double width1, bool carcas);
        void paintLamp(double x0, double y0, double z0, double length1, double height1, double width1, bool carcas);
        void paintKeyboard(double x0, double y0, double z0, double length1, double height1, double width1, bool carcas);
        void paintNiva(double x1, double y1, double z1, double length1, double height1, double width1, bool carcas);
        void paintWheel(double radius, double WhellWidth, bool carcas);
        void paintMouse(double x0, double y0, double z0, double length1, double height1, double width1, bool carcas);
        void paintScreen(double x0, double y0, double z0, double length1, double height1, double width1, bool carcas);
        void paintAboba(double x0, double y0, double z0, double length1, double height1, bool carcas);
        void paintBob(double x0, double y0, double z0, double length1, double height1, GLdouble r, GLdouble g, GLdouble b, bool high, bool carcas);
        void paintBox(double x0, double y0, double z0, double length1, double height1, double width1, GLdouble r, GLdouble g, GLdouble b, bool carcas);
        void paintCrown(double radius, double WhellWidth, int TeethNumber, bool carcas);
        void paintTrain(double x0, double y0, double z0, double length1, double height1, double width1, bool carcas);
        void paintTableLamp(double x0, double y0, double z0, double length1, double height1, double width1, bool carcas);
        void paintBoxwithoutUp(double x0, double y0, double z0, double length1, double height1, double width1, GLdouble r, GLdouble g, GLdouble b, bool carcas);

        //=============STRASHNO========================================
        QVector<double> multiplication(QVector<double> Pol, double d); // Умножение многочлена на число
        QVector<double> multiplication(QVector<double> A, QVector<double> B); // Умножение многочлена на многочлен
        QVector<double> addition(QVector<double> A, QVector<double> B); // Сложение многочленов
        QVector<double> lagrangePolynomial(QVector<double> X, QVector<double> Y);
        double PolValue(QVector<double> Pol, double x0);
        QVector<double> PolDerivative(QVector<double> Pol);
        QVector<double> XPol;
        QVector<double> YPol;
        QVector<double> ZPol;
        void moveNivaInter();
        double time;
        //============================================================

        void keyPressEvent(QKeyEvent* e);
        void mouseMoveEvent(QMouseEvent* me);
        void wheelEvent(QWheelEvent* we);
        car Niva;
        QVector3D camPos, lookAt;
        QPointF deltaT;
        double r, phi, psi, zoom;

        QVector<double> X;
        QVector<double> Y;
        QVector<double> Z;
        QVector<double> T;

        GLfloat lightPos0[4];
        GLfloat lightDiff0[3], lightDiff1[3], lightDiff2[3], lightDiff3[3];
        GLfloat lightAtten0[3], lightAtten1[3], lightAtten2[3], lightAtten3[3];
    public slots:
        void move();
        void changeAtten();
    private:
        Dialog* dialog;
        QTimer t;
        double a;
        bool carcas; bool split;
};
#endif // GLVIEW_H
