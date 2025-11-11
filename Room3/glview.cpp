#include "glview.h"
#include "ui_glview.h"
#include "paintObjects.cpp"
#include "OtherFunctions.cpp"

double pi = 4 * atan(1);

glView::glView(QWidget *parent)
      : QOpenGLWidget(parent)
{
    setWindowTitle("bomjor");
        setGeometry(350, 250, 1100, 650);
        connect(&t, SIGNAL(timeout()), this, SLOT(move()));
        dialog = new Dialog();
        connect(dialog, SIGNAL(valuesChanged()), this, SLOT(changeAtten()));
        t.start(10);
        a = 100;

        camPos = { -95,-100,0 };
        lookAt = { 0,-50,0 };
        zoom = 1.0;
        r = 95;
        phi = 0; psi = 0;
        deltaT = { 0,0 };
        time = 0;

        Niva.setPos(15, 0, 0);
        Niva.setVelocity(0.5, 5);
        Niva.setRot(90, 0);
        Niva.setMode(dialog->iDrive);
        Niva.look(1, 0, 0);

        lightPos0[0] = 0.0f; lightPos0[1] = -100.0f; lightPos0[2] = 0.0f; lightPos0[3] = 1.0f;
        lightDiff0[0] = 1.0f; lightDiff0[1] = 1.0f; lightDiff0[2] = 1.0f;
        lightDiff1[0] = 1.0f; lightDiff1[1] = 1.0f; lightDiff1[2] = 0.0f;
        lightDiff2[0] = 1.0f; lightDiff2[1] = 1.0f; lightDiff2[2] = 0.0f;
        lightDiff3[0] = 1.0f; lightDiff3[1] = 1.0f; lightDiff3[2] = 0.0f;

        lightAtten0[0] = dialog->roofAtten[0]; lightAtten0[1] = dialog->roofAtten[1]; lightAtten0[2] = dialog->roofAtten[2];
        lightAtten1[0] = dialog->lampAtten[0]; lightAtten1[1] = dialog->lampAtten[1]; lightAtten1[2] = dialog->lampAtten[2];
        lightAtten2[0] = dialog->carAtten[0]; lightAtten2[1] = dialog->carAtten[1]; lightAtten2[2] = dialog->carAtten[2];
        lightAtten3[0] = dialog->carAtten[0]; lightAtten3[1] = dialog->carAtten[1]; lightAtten3[2] = dialog->carAtten[2];

        split = dialog->split;
        carcas = dialog->carcas;
        X.push_back(30);
        X.push_back(-30);
        X.push_back(-30);
        X.push_back(30);
        X.push_back(30);

        Y.push_back(0);
        Y.push_back(0);
        Y.push_back(0);
        Y.push_back(0);
        Y.push_back(0);

        Z.push_back(30);
        Z.push_back(-30);
        Z.push_back(30);
        Z.push_back(-30);
        Z.push_back(30);

        T.push_back(0);
        T.push_back(25);
        T.push_back(50);
        T.push_back(75);
        T.push_back(100);

        XPol = lagrangePolynomial(T, X);
        YPol = lagrangePolynomial(T, Y);
        ZPol = lagrangePolynomial(T, Z);

}

void glView::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    QOpenGLWidget::setCursor(QCursor(Qt::BlankCursor));
}

void glView::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120, 1, 1, 3000);
    gluLookAt(r * cos(phi), -100, r * sin(phi), 0, -50, 0, 0, -1, 0);
}

void glView::paintGL()
{
    glClearColor(0.7f, 1.0f, 0.7f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(120.0f, 1.0f, 1.0f, 300.0f);
        gluLookAt(r * cos(phi), -100 + psi, r * sin(phi), 0, -50, 0, 0, -1, 0);

        QCursor c = cursor();
        if (this->isActiveWindow())
        {
            c.setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));
        }
        c.setShape(Qt::BlankCursor);
        setCursor(c);

        glTranslated(-deltaT.x(), 0, deltaT.y());
        glScaled(zoom, zoom, zoom);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiff0);
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, lightAtten0[0]);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, lightAtten0[1]);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, lightAtten0[2]);

        glPushMatrix();
            paintRoom(a, 0.066, 0.36, 0.137, carcas);

            glPushMatrix();
                glRotated(180, 0, -1, 0);
                paintDoor(-20, 0, -100, 50, -100, 3, carcas);
            glPopMatrix();

            paintTable(-95, 0, -95, 130, -40, 50, carcas);

            glPushMatrix();
                glTranslated(10, -42, -70);
                glRotated(90, 0, -1, 0);
                paintTableLamp(-20, 0, -10, 20, -40, 20, carcas);
            glPopMatrix();

            paintLamp(0, -100, 0, 5, -10, 5, carcas);
            glPushMatrix();
                glTranslated(-30, -42, -85);
                paintScreen(0, 0, 0, 30, -30, 3, carcas);
                paintKeyboard(5, 0, 15, 25, -3, 15, carcas);
                glRotated(90, 0, -1, 0);
                paintMouse(20, 0, 0, 8, -3, 5, carcas);
            glPopMatrix();

            if (!Niva.iDrive)
                moveNivaInter();
            glPushMatrix();
                glTranslated(Niva.pos.x(), Niva.pos.y(), Niva.pos.z());
                glRotated(Niva.rotCar, 0, -1, 0);
                paintNiva(0, 0, 0, 10, -8, 10, carcas);
                glTranslated(-2, -14, 0);
                paintCrown(2, -7, 7, carcas);
            glPopMatrix();

            glPushMatrix();
                glRotated(270, 0, -1, 0);
                paintChest(-98, 0, -98, 90, -50, 40, carcas);

                glPushMatrix();
                    glTranslated(-45, -30, -85);
                    paintTrain(0, 0, 0, 25, -15, 15, carcas);
                glPopMatrix();

                glPushMatrix();
                    glRotated(180, 0, 0, 1);
                    paintAboba(20, 50, -100, 70, 40, carcas);
                glPopMatrix();
            glPopMatrix();

            glPushMatrix();
                glTranslated(-85, -31, 60);
                glPushMatrix();
                    glRotated(100, 1, 0, 0);
                    glRotated(30, 0, 0, 1);
                    paintLamp(0, 0, 0, 5, -10, 5, carcas);
                glPopMatrix();

                glPushMatrix();
                    glTranslated(0, -4.5, 5);
                    glRotated(140, 1, 0, 0);
                    glRotated(230, 0, 0, 1);
                    paintLamp(0, 0, 0, 5, -10, 5, carcas);
                glPopMatrix();

                glPushMatrix();
                    glTranslated(0, 0, 30);
                    glRotated(90, 0, -1, 0);
                    glRotated(100, 1, 0, 0);
                    glRotated(30, 0, 0, 1);
                    paintLamp(0, 0, 0, 5, -10, 5, carcas);
                glPopMatrix();
            glPopMatrix();

        glPopMatrix();
}

void glView::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_M) {
            dialog->show();
        }
        if ((Niva.iDrive))
        {
            if (e->key() == Qt::Key_Left)
            {
                Niva.setRot(Niva.rotCar + 5 * Niva.carVelocity, Niva.rotWheel + Niva.wheelVelocity);
            }
            if (e->key() == Qt::Key_Right)
            {
                Niva.setRot(Niva.rotCar - 5 * Niva.carVelocity, Niva.rotWheel + Niva.wheelVelocity);
            }
            if (e->key() == Qt::Key_Down)
            {
                Niva.rotate(Niva.rotCar * pi / 180, 1, 0, 0);
                Niva.setPos(Niva.pos.x() - Niva.lookAt.x() * 2,
                    Niva.pos.y(),
                    Niva.pos.z() - Niva.lookAt.z() * 2);
            }
            if (e->key() == Qt::Key_Up)
            {
                Niva.rotate(Niva.rotCar * pi / 180, 1, 0, 0);
                Niva.setPos(Niva.pos.x() + Niva.lookAt.x() * 2,
                    Niva.pos.y(),
                    Niva.pos.z() + Niva.lookAt.z() * 2);
            }
        }
}

void glView::mouseMoveEvent(QMouseEvent *me)
{
    if (me->buttons() == Qt::LeftButton)
    {
        phi += 0.02*(me->pos().x() - this->width() / 2);
        psi += 0.1 * (me->pos().y() - this->height() / 2);
    }
    if (me->buttons() == Qt::RightButton)
    {
        deltaT.setX(deltaT.x() + (me->pos().x() - this->width() / 2)/100.0);
        deltaT.setY(deltaT.y() + (me->pos().y() - this->height() / 2)/100.0);
    }
}

void glView::wheelEvent(QWheelEvent *we)
{
    if(we->angleDelta().y() != 0)
        zoom += we->angleDelta().y() / abs(we->angleDelta().y()) / 100.;
    if (zoom < 0.3) zoom = 0.3;
    if (zoom > 3.) zoom = 3.;
}

void glView::move()
{
    Niva.setRot(Niva.rotCar, Niva.rotWheel + Niva.wheelVelocity);
        time += 0.1;
        if (time >= 100) time = 0;


        update();
}

void glView::changeAtten()
{
    lightAtten0[0] = dialog->roofAtten[0]; lightAtten0[1] = dialog->roofAtten[1]; lightAtten0[2] = dialog->roofAtten[2];
    lightAtten1[0] = dialog->lampAtten[0]; lightAtten1[1] = dialog->lampAtten[1]; lightAtten1[2] = dialog->lampAtten[2];
    lightAtten2[0] = dialog->carAtten[0]; lightAtten2[1] = dialog->carAtten[1]; lightAtten2[2] = dialog->carAtten[2];
    lightAtten3[0] = dialog->carAtten[0]; lightAtten3[1] = dialog->carAtten[1]; lightAtten3[2] = dialog->carAtten[2];

    split = dialog->split;
    carcas = dialog->carcas;
    Niva.setMode(dialog->iDrive);
}
