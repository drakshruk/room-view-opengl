#include <glview.h>

void glView::paintRoom(double a, double r, double g, double b, bool carcas)
{
    if (carcas) glBegin(GL_LINE_LOOP);
    else glBegin(GL_QUADS);

    glColor3d(1, 0, 0); // Pol
    glNormal3d(0., -1., 0.);
    glVertex3d(a, 0, a);
    glVertex3d(a, 0, -a);
    glVertex3d(-a, 0, -a);
    glVertex3d(-a, 0, a);

    if (split && !carcas)
    {
        glColor3d(r, g, b);

        glNormal3d(1., 0., 0.);
        for (int i = -a; i < 0; i++)
            for (int j = -a; j < a; j++)
            {
                glVertex3d(-a, i, j);
                glVertex3d(-a, i, j + 1);
                glVertex3d(-a, i + 1, j + 1);
                glVertex3d(-a, i + 1, j);
            }

        glNormal3d(-1., 0., 0.);
        for (int i = -a; i < 0; i++)
            for (int j = -a; j < a; j++)
            {
                glVertex3d(a, i, j);
                glVertex3d(a, i + 1, j);
                glVertex3d(a, i + 1, j + 1);
                glVertex3d(a, i, j + 1);
            }

        glNormal3d(0., 0., -1.);
        for (int i = -a; i < a; i++)
            for (int j = -a; j < 0; j++)
            {
                glVertex3d(i, j, a);
                glVertex3d(i, j + 1, a);
                glVertex3d(i + 1, j + 1, a);
                glVertex3d(i + 1, j, a);
            }

        glNormal3d(0., 0., 1.);
        for (int i = -a; i < a; i++)
            for (int j = -a; j < 0; j++)
            {
                glVertex3d(i, j, -a);
                glVertex3d(i + 1, j, -a);
                glVertex3d(i + 1, j + 1, -a);
                glVertex3d(i, j + 1, -a);
            }
    }
    else
    {
        glColor3d(0.3, 0.3, 0.3);
        glNormal3d(0., -1., 0.);
        glVertex3d(a, 0, a);
        glVertex3d(a, 0, -a);
        glVertex3d(-a, 0, -a);
        glVertex3d(-a, 0, a);

        glColor3d(r, g, b);

        glNormal3d(1., 0., 0.);
        glVertex3d(-a, 0, a);
        glVertex3d(-a, -a, a);
        glVertex3d(-a, -a, -a);
        glVertex3d(-a, 0, -a);

        glNormal3d(0., 0., 1.);
        glVertex3d(-a, 0, -a);
        glVertex3d(-a, -a, -a);
        glVertex3d(a, -a, -a);
        glVertex3d(a, 0, -a);

        glNormal3d(-1., 0., 0.);
        glVertex3d(a, 0, -a);
        glVertex3d(a, -a, -a);
        glVertex3d(a, -a, a);
        glVertex3d(a, 0, a);

        glNormal3d(0., 0., -1.);
        glVertex3d(a, 0, a);
        glVertex3d(a, -a, a);
        glVertex3d(-a, -a, a);
        glVertex3d(-a, 0, a);
    }

    glEnd();
    glPushMatrix();
    paintBox(-a, 0, -a, 2 * a, -a / 25, a / 100, 0.5, 0.4, 0.2, carcas);
    glTranslated(0, 0, 2 * a - a / 100);
    paintBox(-a, 0, -a, 2 * a, -a / 25, a / 100, 0.5, 0.4, 0.2, carcas);
    glTranslated(0, 0, -2 * a + a / 100);
    glRotated(90, 0, -1, 0);
    paintBox(-a, 0, -a, 2 * a, -a / 25, a / 100, 0.5, 0.4, 0.2, carcas);
    glTranslated(0, 0, 2 * a - a / 100);
    paintBox(-a, 0, -a, 2 * a, -a / 25, a / 100, 0.5, 0.4, 0.2, carcas);
    glPopMatrix();

}

void glView::paintTable(double x0, double y0, double z0, double length2, double height2, double width2, bool carcas)
{
    GLdouble r = 0.5; // 0.5
    GLdouble g = 0.4; // 0.4
    GLdouble b = 0.2; // 0.2

    glPushMatrix();
    glTranslated(x0, y0, z0);

    if (split && !carcas)
    {
        paintBoxwithoutUp(0, height2 - 2, 0, length2, 2, width2, r, g, b, carcas);

        for (int i = 1; i < length2; i++)
            for (int j = 1; j < width2; j++)
            {
                glNormal3d(0, -1, 0);
                glColor3d(r, g, b);

                glBegin(GL_QUADS);

                glVertex3d(i, height2 - 2, j);
                glVertex3d(i, height2 - 2, j + 1);
                glVertex3d(i + 1, height2 - 2, j + 1);
                glVertex3d(i + 1, height2 - 2, j);
                glEnd();
            }
    }
    else
        paintBox(0, height2 - 2, 0, length2, 2, width2, r, g, b, carcas);


    paintBox(2, 0, 2, 3, height2, 3, r, g, b, carcas);
    paintBox(length2 - 5, 0, 2, 3, height2, 3, r, g, b, carcas);
    paintBox(2, 0, width2 - 5, 3, height2, 3, r, g, b, carcas);
    paintBox(length2 - 5, 0, width2 - 5, 3, height2, 3, r, g, b, carcas);

    glPopMatrix();
}

void glView::paintBox(double x0, double y0, double z0, double length1, double height1, double width1, GLdouble r, GLdouble g, GLdouble b, bool carcas)
{
    glPushMatrix();
    glTranslated(x0, y0, z0);

    if (carcas) glBegin(GL_LINE_LOOP);
    else glBegin(GL_QUADS);

    glColor3d(r, g, b);
    if (height1 < 0) glNormal3d(0, 1, 0);
    else glNormal3d(0, -1, 0);

    glVertex3d(0, 0, 0);
    glVertex3d(0, 0, width1);
    glVertex3d(length1, 0, width1);
    glVertex3d(length1, 0, 0);

    if (height1 < 0) glNormal3d(0, -1, 0);
    else glNormal3d(0, 1, 0);
    glVertex3d(length1, height1, 0);
    glVertex3d(0, height1, 0);
    glVertex3d(0, height1, width1);
    glVertex3d(length1, height1, width1);

    glNormal3d(1, 0, 0);
    glVertex3d(length1, 0, width1);
    glVertex3d(length1, 0, 0);
    glVertex3d(length1, height1, 0);
    glVertex3d(length1, height1, width1);

    glNormal3d(0, 0, 1);
    glVertex3d(length1, 0, width1);
    glVertex3d(length1, height1, width1);
    glVertex3d(0, height1, width1);
    glVertex3d(0, 0, width1);

    glNormal3d(-1, 0, 0);
    glVertex3d(0, 0, width1);
    glVertex3d(0, height1, width1);
    glVertex3d(0, height1, 0);
    glVertex3d(0, 0, 0);

    glNormal3d(0, 0, -1);
    glVertex3d(0, 0, 0);
    glVertex3d(length1, 0, 0);
    glVertex3d(length1, height1, 0);
    glVertex3d(0, height1, 0);

    glEnd();

    glPopMatrix();
}

void glView::paintBoxwithoutUp(double x0, double y0, double z0, double length1, double height1, double width1, GLdouble r, GLdouble g, GLdouble b, bool carcas)
{
    glPushMatrix();
    glTranslated(x0, y0, z0);

    if (carcas) glBegin(GL_LINE_LOOP);
    else glBegin(GL_QUADS);

    glColor3d(r, g, b);
    if (height1 < 0) glNormal3d(0, 1, 0);
    else glNormal3d(0, -1, 0);


    if (height1 < 0) glNormal3d(0, -1, 0);
    else glNormal3d(0, 1, 0);
    glVertex3d(length1, height1, 0);
    glVertex3d(0, height1, 0);
    glVertex3d(0, height1, width1);
    glVertex3d(length1, height1, width1);

    glNormal3d(1, 0, 0);
    glVertex3d(length1, 0, width1);
    glVertex3d(length1, 0, 0);
    glVertex3d(length1, height1, 0);
    glVertex3d(length1, height1, width1);

    glNormal3d(0, 0, 1);
    glVertex3d(length1, 0, width1);
    glVertex3d(length1, height1, width1);
    glVertex3d(0, height1, width1);
    glVertex3d(0, 0, width1);

    glNormal3d(-1, 0, 0);
    glVertex3d(0, 0, width1);
    glVertex3d(0, height1, width1);
    glVertex3d(0, height1, 0);
    glVertex3d(0, 0, 0);

    glNormal3d(0, 0, -1);
    glVertex3d(0, 0, 0);
    glVertex3d(length1, 0, 0);
    glVertex3d(length1, height1, 0);
    glVertex3d(0, height1, 0);

    glEnd();

    glPopMatrix();
}

void glView::paintWheel(double radius, double WhellWidth, bool carcas)
{
    QVector<QPointF> edge;

    int sides = 6;
    double angleStep = 2 * 4 * atan(1) / sides;

    for (int i = 0; i < sides + 1; ++i)
    {
        double angle = i * angleStep;
        double z = radius * cos(angle);
        double y = -radius * sin(angle); // Р’ Qt РєРѕРѕСЂРґРёРЅР°С‚С‹ y РІРѕР·СЂР°СЃС‚Р°СЋС‚ РІРЅРёР·
        double Z; double Y;
        Z = z;
        Y = y;
        edge.push_back({ Z, Y });
    }

    if (carcas) glBegin(GL_LINE_LOOP);
    else glBegin(GL_QUADS);
    glColor3d(0, 0, 0);
    for (int i = 0; i < edge.size() - 1; i++)
    {
        glNormal3d(0, 0.5 * (edge[i].y() + edge[i + 1].y()), 0.5 * (edge[i].x() + edge[i + 1].x()));
        glVertex3d(0, edge[i].y(), edge[i].x());
        glVertex3d(WhellWidth, edge[i].y(), edge[i].x());
        glVertex3d(WhellWidth, edge[i + 1].y(), edge[i + 1].x());
        glVertex3d(0, edge[i + 1].y(), edge[i + 1].x());
    }
    glEnd();

    if (carcas) glBegin(GL_LINE_LOOP);
    else glBegin(GL_POLYGON);
    glNormal3d(-1, 0, 0);
    for (int i = 0; i < edge.size(); i++)
    {
        glVertex3d(0, edge[i].y(), edge[i].x());
    }
    glEnd();
    if (carcas) glBegin(GL_LINE_LOOP);
    else glBegin(GL_POLYGON);
    glNormal3d(1, 0, 0);
    for (int i = 0; i < edge.size(); i++)
    {
        glVertex3d(WhellWidth, edge[i].y(), edge[i].x());
    }
    glEnd();
}

void glView::paintNiva(double x1, double y1, double z1, double length1, double height1, double width1, bool carcas)
{
    glPushMatrix();
    length1 = abs(length1);
    width1 = abs(width1);

    double xb = length1 / 14;
    double yb = height1 / 8;
    double zb = width1 / 9;

    double rad = 3 * xb;
    double WheellWidth = zb;
    glTranslated(x1, y1 - 2 * rad, z1);

    glPushMatrix();
    glTranslated(-length1 / 2, rad, -3 * zb);

    paintBox(0, 0, 0, length1, 4 * yb, 7 * zb, 1, 1, 1, carcas);
    paintBox(0, 4 * yb, 0, 9 * xb, 3 * yb, 7 * zb, 1, 1, 1, carcas);

    GLfloat lightDir3[3];
    lightDir3[0] = GLfloat(1);
    lightDir3[1] = GLfloat(0);
    lightDir3[2] = GLfloat(0);
    GLfloat lightPos3[4];
    lightPos3[0] = GLfloat(13.5 * xb);
    lightPos3[1] = GLfloat(2.5 * yb);
    lightPos3[2] = GLfloat(2 * zb);
    lightPos3[3] = 1.0f;
    glLightfv(GL_LIGHT3, GL_DIFFUSE, lightDiff3);
    glLightfv(GL_LIGHT3, GL_POSITION, lightPos3);
    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 30.0f);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, lightDir3);
    glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, lightAtten3[0]);
    glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, lightAtten3[1]);
    glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, lightAtten3[2]);

    GLfloat lightDir2[3];
    lightDir2[0] = GLfloat(1);
    lightDir2[1] = GLfloat(0);
    lightDir2[2] = GLfloat(0);
    GLfloat lightPos2[4];
    lightPos2[0] = GLfloat(13.5 * xb);
    lightPos2[1] = GLfloat(2.5 * yb);
    lightPos2[2] = GLfloat(5 * zb);
    lightPos2[3] = 1.0f;
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDiff2);
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30.0f);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lightDir2);
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, lightAtten2[0]);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, lightAtten2[1]);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, lightAtten2[2]);

    paintBox(14 * xb, 2 * yb, 1 * zb, 0.3 * xb, yb, 2 * zb, 1, 1, 0, carcas);
    paintBox(14 * xb, 2 * yb, 4 * zb, 0.3 * xb, yb, 2 * zb, 1, 1, 0, carcas);

    glPushMatrix();
    glTranslated(-WheellWidth, -1.5 * rad, 3 * zb);
    paintWheel(rad, WheellWidth, carcas);
    glPopMatrix();

    glRotated(90, 0, 1, 0);

    glPushMatrix();
    glTranslated(0, 0, 4 * xb);
    glRotated(Niva.rotWheel, -1, 0, 0);
    paintWheel(rad, WheellWidth, carcas);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 0, 11 * xb);
    glRotated(Niva.rotWheel, -1, 0, 0);
    paintWheel(rad, WheellWidth, carcas);
    glPopMatrix();

    glTranslated(-8 * zb, 0, 0);

    glPushMatrix();
    glTranslated(0, 0, 4 * xb);
    glRotated(Niva.rotWheel, -1, 0, 0);
    paintWheel(rad, WheellWidth, carcas);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 0, 11 * xb);
    glRotated(Niva.rotWheel, -1, 0, 0);
    paintWheel(rad, WheellWidth, carcas);
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();
}

void glView::paintCrown(double radius, double WhellWidth, int TeethNumber, bool carcas)
{
    glPushMatrix();
    glRotated(-90, 0, 0, 1);
    QVector<QPointF> edge;

    int sides = TeethNumber;
    double angleStep = 2 * 4 * atan(1) / sides;

    for (int i = 0; i < sides + 1; ++i)
    {
        double angle = i * angleStep;
        double z = radius * cos(angle);
        double y = -radius * sin(angle); // В Qt координаты y возрастают вниз
        double Z; double Y;
        Z = z;
        Y = y;
        edge.push_back({ Z, Y });
    }
    if (carcas) glBegin(GL_LINE_LOOP);
    else glBegin(GL_QUADS);
    glColor3d(1, 1, 0);
    for (int i = 0; i < edge.size() - 1; i++)
    {
        glNormal3d(0, 0.5 * (edge[i].y() + edge[i + 1].y()), 0.5 * (edge[i].x() + edge[i + 1].x()));
        glVertex3d(0, edge[i].y(), edge[i].x());
        glVertex3d(WhellWidth, edge[i].y(), edge[i].x());
        glVertex3d(0, edge[i + 1].y(), edge[i + 1].x());
        glVertex3d(WhellWidth, edge[i + 1].y(), edge[i + 1].x());
    }
    glEnd();
    glPopMatrix();
}

void glView::paintDoor(double x0, double y0, double z0, double length1, double height1, double width1, bool carcas)
{
    glPushMatrix();
    glTranslated(x0, y0, z0);
    glRotated(0, 0, 1, 0);

    GLdouble r = 0.5;
    GLdouble g = 0.4;
    GLdouble b = 0.2;

    paintBox(0, 0, 0, length1, height1, width1 / 3, r, g, b, carcas);

    paintBox(length1 / 21, 0, width1 / 3, 2 * length1 / 21, 36 * height1 / 37, width1 / 3, r, g, b, carcas);
    paintBox(18 * length1 / 21, 0, width1 / 3, 2 * length1 / 21, 36 * height1 / 37, width1 / 3, r, g, b, carcas);
    paintBox(length1 / 21, 34 * height1 / 37, width1 / 3, 19 * length1 / 21, 2 * height1 / 37, width1 / 3, r, g, b, carcas);

    paintBox(4 * length1 / 21, 0, width1 / 3, 13 * length1 / 21, 19 * height1 / 37, width1 / 3, r, g, b, carcas);

    paintBox(4 * length1 / 21, 19 * height1 / 37, width1 / 3, 1 * length1 / 21, 14 * height1 / 37, width1 / 3, r, g, b, carcas);
    paintBox(10 * length1 / 21, 19 * height1 / 37, width1 / 3, 1 * length1 / 21, 14 * height1 / 37, width1 / 3, r, g, b, carcas);
    paintBox(16 * length1 / 21, 19 * height1 / 37, width1 / 3, 1 * length1 / 21, 14 * height1 / 37, width1 / 3, r, g, b, carcas);

    paintBox(4 * length1 / 21, 32 * height1 / 37, width1 / 3, 13 * length1 / 21, 1 * height1 / 37, width1 / 3, r, g, b, carcas);
    paintBox(4 * length1 / 21, 25 * height1 / 37, width1 / 3, 13 * length1 / 21, 1 * height1 / 37, width1 / 3, r, g, b, carcas);

    paintBox(5 * length1 / 21, 12 * height1 / 37, 2 * width1 / 3, 2 * length1 / 21, 4 * height1 / 37, width1 / 3, 0, 0, 0, carcas);

    glPopMatrix();
}

void glView::paintChest(double x0, double y0, double z0, double length1, double height1, double width1, bool carcas)
{
    glPushMatrix();
    glTranslated(x0, y0, z0);
    glRotated(0, 0, 1, 0);

    GLdouble r = 0.5;
    GLdouble g = 0.4;
    GLdouble b = 0.2;

    double xb, yb, zb;
    xb = length1 / 37;
    yb = height1 / 17;
    zb = width1 / 14;

    paintBox(xb, 0, zb, 2 * xb, 2 * yb, 2 * zb, 0, 0, 0, carcas);
    paintBox(xb, 0, 10 * zb, 2 * xb, 2 * yb, 2 * zb, 0, 0, 0, carcas);
    paintBox(34 * xb, 0, zb, 2 * xb, 2 * yb, 2 * zb, 0, 0, 0, carcas);
    paintBox(34 * xb, 0, 10 * zb, 2 * xb, 2 * yb, 2 * zb, 0, 0, 0, carcas);

    paintBox(0, 2 * yb, 0, length1, 8 * yb, width1 - zb, r, g, b, carcas);

    paintBox(0, 10 * yb, 0, xb, 7 * yb, width1 - zb, r, g, b, carcas);
    paintBox(18 * xb, 10 * yb, 0, xb, 6 * yb, width1 - zb, r, g, b, carcas);
    paintBox(36 * xb, 10 * yb, 0, xb, 7 * yb, width1 - zb, r, g, b, carcas);

    paintBox(0, 10 * yb, 0, length1, 7 * yb, zb, r, g, b, carcas);
    paintBox(0, 16 * yb, 0, length1, yb, width1 - zb, r, g, b, carcas);

    r = 0.55;
    g = 0.389;
    b = 0.2;

    paintBox(xb, 3 * yb, 13 * zb, 17 * xb, 6 * yb, zb, r, g, b, carcas);
    paintBox(19 * xb, 3 * yb, 13 * zb, 17 * xb, 6 * yb, zb, r, g, b, carcas);

    paintBox(9 * xb, 6 * yb, 14 * zb, xb, 2 * yb, zb, 0, 0, 0, carcas);
    paintBox(27 * xb, 6 * yb, 14 * zb, xb, 2 * yb, zb, 0, 0, 0, carcas);

    glPopMatrix();
}

void glView::paintLamp(double x0, double y0, double z0, double length1, double height1, double width1, bool carcas)
{
    glPushMatrix();
    glTranslated(x0 - length1 / 2, y0, z0 - width1 / 2);

    double xb, yb, zb;
    xb = length1 / 5;
    yb = height1 / 8;
    zb = width1 / 5;

    paintBox(2 * xb, 0, zb, xb, yb, 3 * zb, 1, 1, 1, carcas);
    paintBox(xb, 0, 2 * zb, xb, yb, zb, 1, 1, 1, carcas);
    paintBox(3 * xb, 0, 2 * zb, xb, yb, zb, 1, 1, 1, carcas);

    paintBox(2 * xb, -yb, zb, xb, yb, 3 * zb, 0, 0, 0, carcas);
    paintBox(xb, -yb, 2 * zb, xb, yb, zb, 0, 0, 0, carcas);
    paintBox(3 * xb, -yb, 2 * zb, xb, yb, zb, 0, 0, 0, carcas);
    paintBox(xb, -2 * yb, zb, 3 * xb, yb, 3 * zb, 0, 0, 0, carcas);

    paintBox(xb, -6 * yb, 0, 3 * xb, 3 * yb, 5 * zb, 1, 1, 0, carcas);
    paintBox(0, -6 * yb, zb, 5 * xb, 3 * yb, 3 * zb, 1, 1, 0, carcas);
    paintBox(xb, -7 * yb, zb, 3 * xb, 5 * yb, 3 * zb, 1, 1, 0, carcas);

    glPopMatrix();
}

void glView::paintKeyboard(double x0, double y0, double z0, double length1, double height1, double width1, bool carcas)
{
    glPushMatrix();
    glTranslated(x0, y0, z0);

    GLdouble r = 0.18;
    GLdouble g = 0.31;
    GLdouble b = 0.31;

    double xb, yb, zb;
    xb = length1 / 19;
    yb = height1 / 1.5;
    zb = width1 / 11;


    paintBox(0, 0, 0, length1, yb, width1, 0, 0, 0, carcas);
    glRotated(180, 1, 0, 0);
    glRotated(180, 0, 1, 0);
    glTranslated(-length1, -2 * yb - yb / 2, 0);

    for (int i = 0; i < 9; i++)
    {
        paintBox((2 * i + 1) * xb, yb, zb, xb, yb / 2, zb, r, g, b, carcas);
    }

    for (int i = 0; i < 5; i++)
    {
        paintBox(3 * xb + (2 * i + 1) * xb, yb, 3 * zb, xb, yb / 2, zb, r, g, b, carcas);
        paintBox(3 * xb + (2 * i + 1) * xb, yb, 7 * zb, xb, yb / 2, zb, r, g, b, carcas);
    }

    for (int i = 0; i < 4; i++)
    {
        paintBox(4 * xb + (2 * i + 1) * xb, yb, 5 * zb, xb, yb / 2, zb, r, g, b, carcas);
    }

    paintBox(xb, yb, 3 * zb, 2 * xb, yb / 2, zb, r, g, b, carcas);
    paintBox(xb, yb, 7 * zb, 2 * xb, yb / 2, zb, r, g, b, carcas);
    paintBox(14 * xb, yb, 3 * zb, 2 * xb, yb / 2, zb, r, g, b, carcas);
    paintBox(14 * xb, yb, 7 * zb, 2 * xb, yb / 2, zb, r, g, b, carcas);

    paintBox(xb, yb, 5 * zb, 3 * xb, yb / 2, zb, r, g, b, carcas);
    paintBox(13 * xb, yb, 5 * zb, 3 * xb, yb / 2, zb, r, g, b, carcas);

    paintBox(17 * xb, yb, 3 * zb, 1 * xb, yb / 2, zb, r, g, b, carcas);
    paintBox(17 * xb, yb, 5 * zb, 1 * xb, yb / 2, zb, r, g, b, carcas);
    paintBox(17 * xb, yb, 7 * zb, 1 * xb, yb / 2, zb, r, g, b, carcas);

    paintBox(1 * xb, yb, 9 * zb, 1 * xb, yb / 2, zb, r, g, b, carcas);
    paintBox(3 * xb, yb, 9 * zb, 1 * xb, yb / 2, zb, r, g, b, carcas);
    paintBox(5 * xb, yb, 9 * zb, 7 * xb, yb / 2, zb, r, g, b, carcas);

    paintBox(13 * xb, yb, 9 * zb, 2 * xb, yb / 2, zb, r, g, b, carcas);
    paintBox(16 * xb, yb, 9 * zb, 2 * xb, yb / 2, zb, r, g, b, carcas);

    glPopMatrix();
}

void glView::paintMouse(double x0, double y0, double z0, double length1, double height1, double width1, bool carcas)
{
    glPushMatrix();
    glTranslated(x0, y0, z0);

    GLdouble r = 0.18;
    GLdouble g = 0.31;
    GLdouble b = 0.31;

    double xb, yb, zb;
    xb = length1 / 6;
    yb = height1 / 3;
    zb = width1 / 5;

    paintBox(0, 0, 0, 5 * xb, yb, width1, 0, 0, 0, carcas);
    paintBox(5 * xb, 0, zb, xb, yb, 3 * zb, 0, 0, 0, carcas);

    paintBox(3 * xb, yb, 0, 3 * xb, yb, 5 * zb, r, g, b, carcas);
    paintBox(2 * xb, yb, 0, 1 * xb, yb, 2 * zb, r, g, b, carcas);
    paintBox(2 * xb, yb, 3 * zb, 1 * xb, yb, 2 * zb, r, g, b, carcas);
    paintBox(5 * xb, yb, zb, xb, yb, 3 * zb, r, g, b, carcas);

    paintBox(0, yb, zb, 2 * xb, yb, zb, r, g, b, carcas);
    paintBox(0, yb, 3 * zb, 2 * xb, yb, zb, r, g, b, carcas);

    paintBox(2 * xb, 0, 2 * zb, 2 * xb, 3 * yb, zb, 0, 0, 0, carcas);

    glPopMatrix();
}

void glView::paintScreen(double x0, double y0, double z0, double length1, double height1, double width1, bool carcas)
{
    glPushMatrix();
    glTranslated(x0, y0, z0);

    GLdouble r = 0.18;
    GLdouble g = 0.31;
    GLdouble b = 0.31;

    double xb, yb, zb;
    xb = length1 / 21;
    yb = height1 / 15;
    zb = width1 / 5;

    paintBox(4 * xb, 0, 0, 13 * xb, yb, 5 * zb, r, g, b, carcas);

    paintBox(9 * xb, yb, zb, 3 * xb, 3 * yb, 2 * zb, 0, 0, 0, carcas);
    paintBox(7 * xb, 4 * yb, zb, 7 * xb, 4 * yb, 1 * zb, 0, 0, 0, carcas);

    paintBox(0, 4 * yb, 2 * zb, length1, 11 * yb, zb / 2, r, g, b, carcas);

    paintBox(xb, 5 * yb, 2.5 * zb, 19 * xb, 9 * yb, zb / 2, 0, 0, 0, carcas);

    paintBox(0, 4 * yb, 2.5 * zb, xb, 11 * yb, 1.5, r, g, b, carcas);
    paintBox(length1 - xb, 4 * yb, 2.5 * zb, xb, 11 * yb, 1.5, r, g, b, carcas);

    paintBox(xb, height1 - yb, 2.5 * zb, length1 - 2 * xb, yb, 1.5, r, g, b, carcas);
    paintBox(xb, 4 * yb, 2.5 * zb, length1 - 2 * xb, yb, 1.5, r, g, b, carcas);

    glPopMatrix();
}

void glView::paintBob(double x0, double y0, double z0, double length1, double height1, GLdouble r, GLdouble g, GLdouble b, bool high, bool carcas)
{
    glPushMatrix();
    glTranslated(x0, y0, z0);

    double xb, yb;
    xb = length1 / 11;
    yb = height1 / 11;

    paintBox(0, 0, 0, length1, yb, 1, 1, 1, 1, carcas);

    paintBox(0, yb, 0, 3 * xb, yb, 1, 1, 1, 1, carcas);
    paintBox(8 * xb, yb, 0, 3 * xb, yb, 1, 1, 1, 1, carcas);

    paintBox(0, 2 * yb, 0, 2 * xb, yb, 1, 1, 1, 1, carcas);
    paintBox(9 * xb, 2 * yb, 0, 2 * xb, yb, 1, 1, 1, 1, carcas);
    paintBox(3 * xb, 2 * yb, 0, 5 * xb, yb, 1, 1, 1, 1, carcas);

    paintBox(0, 3 * yb, 0, xb, 5 * yb, 1, 1, 1, 1, carcas);
    paintBox(10 * xb, 3 * yb, 0, xb, 5 * yb, 1, 1, 1, 1, carcas);

    paintBox(0, 8 * yb, 0, 2 * xb, yb, 1, 1, 1, 1, carcas);
    paintBox(9 * xb, 8 * yb, 0, 2 * xb, yb, 1, 1, 1, 1, carcas);
    paintBox(3 * xb, 8 * yb, 0, 5 * xb, yb, 1, 1, 1, 1, carcas);

    paintBox(0, 9 * yb, 0, 3 * xb, yb, 1, 1, 1, 1, carcas);
    paintBox(8 * xb, 9 * yb, 0, 3 * xb, yb, 1, 1, 1, 1, carcas);

    paintBox(0, 10 * yb, 0, length1, yb, 1, 1, 1, 1, carcas);

    paintBox(3 * xb, 2 * yb, 0, 5 * xb, yb, 1, 1, 1, 1, carcas);
    paintBox(3 * xb, 8 * yb, 0, 5 * xb, yb, 1, 1, 1, 1, carcas);

    paintBox(2 * xb, 3 * yb, 0, xb, 5 * yb, 1, 1, 1, 1, carcas);
    paintBox(8 * xb, 3 * yb, 0, xb, 5 * yb, 1, 1, 1, 1, carcas);

    paintBox(3 * xb, 3 * yb, 0, xb, yb, 1, 1, 1, 1, carcas);
    paintBox(7 * xb, 3 * yb, 0, xb, yb, 1, 1, 1, 1, carcas);
    paintBox(7 * xb, 7 * yb, 0, xb, yb, 1, 1, 1, 1, carcas);
    paintBox(3 * xb, 7 * yb, 0, xb, yb, 1, 1, 1, 1, carcas);


    paintBox(3 * xb, yb, 0, 5 * xb, yb, 1, 1, 0, 0, carcas);
    paintBox(3 * xb, 9 * yb, 0, 5 * xb, yb, 1, 1, 0, 0, carcas);
    paintBox(xb, 3 * yb, 0, xb, 5 * yb, 1, 1, 0, 0, carcas);
    paintBox(9 * xb, 3 * yb, 0, xb, 5 * yb, 1, 1, 0, 0, carcas);

    paintBox(2 * xb, 2 * yb, 0, xb, yb, 1, 1, 0, 0, carcas);
    paintBox(8 * xb, 2 * yb, 0, xb, yb, 1, 1, 0, 0, carcas);
    paintBox(2 * xb, 8 * yb, 0, xb, yb, 1, 1, 0, 0, carcas);
    paintBox(8 * xb, 8 * yb, 0, xb, yb, 1, 1, 0, 0, carcas);

    paintBox(5 * xb, 5 * yb, 0, xb, yb, 1, 1, 0, 0, carcas);


    paintBox(4 * xb, 3 * yb, 0, 3 * xb, yb, 1, 0, 0, 0, carcas);
    paintBox(3 * xb, 4 * yb, 0, xb, yb, 1, 0, 0, 0, carcas);
    paintBox(7 * xb, 4 * yb, 0, xb, yb, 1, 0, 0, 0, carcas);

    paintBox(4 * xb, 4 * yb, 0, 3 * xb, yb, 1, r, g, b, carcas);
    paintBox(5 * xb, 6 * yb, 0, xb, yb, 1, r, g, b, carcas);
    paintBox(4 * xb, 7 * yb, 0, 3 * xb, yb, 1, r, g, b, carcas);


    paintBox(3 * xb, 6 * yb, 0, xb, yb, 1, 0, 0, 1, carcas);
    paintBox(7 * xb, 6 * yb, 0, xb, yb, 1, 0, 0, 1, carcas);


    if (high == false)
    {
        paintBox(4 * xb, 6 * yb, 0, xb, yb, 1, 1, 1, 1, carcas);
        paintBox(6 * xb, 6 * yb, 0, xb, yb, 1, 1, 1, 1, carcas);

        paintBox(3 * xb, 5 * yb, 0, 2 * xb, yb, 1, r, g, b, carcas);
        paintBox(6 * xb, 5 * yb, 0, 2 * xb, yb, 1, r, g, b, carcas);
    }
    else
    {
        paintBox(4 * xb, 6 * yb, 0, xb, yb, 1, 1, 0.64, 0, carcas);
        paintBox(6 * xb, 6 * yb, 0, xb, yb, 1, 1, 0.64, 0, carcas);

        paintBox(3 * xb, 5 * yb, 0, 2 * xb, yb / 2, 1, r, g, b, carcas);
        paintBox(6 * xb, 5 * yb, 0, 2 * xb, yb / 2, 1, r, g, b, carcas);
        paintBox(3 * xb, 5.5 * yb, 0, 2 * xb, yb / 2, 1, 0.5450980392156863, 0.4313725490196078, 0.6823529411764706, carcas);
        paintBox(6 * xb, 5.5 * yb, 0, 2 * xb, yb / 2, 1, 0.5450980392156863, 0.4313725490196078, 0.6823529411764706, carcas);
    }

    glPopMatrix();
}

void glView::paintAboba(double x0, double y0, double z0, double length1, double height1, bool carcas)
{
    glPushMatrix();
    glTranslated(x0, y0, z0);

    double xb, yb;
    xb = length1 / 33;
    yb = height1 / 13;

    paintBox(0, 0, 0, length1, yb, 2, 0.807843137254902, 0.6549019607843137, 0.4666666666666667, carcas);
    paintBox(0, 12 * yb, 0, length1, yb, 2, 0.807843137254902, 0.6549019607843137, 0.4666666666666667, carcas);

    paintBox(0, yb, 0, xb, 11 * yb, 2, 0.807843137254902, 0.6549019607843137, 0.4666666666666667, carcas);
    paintBox(32 * xb, yb, 0, xb, 11 * yb, 2, 0.807843137254902, 0.6549019607843137, 0.4666666666666667, carcas);

    glRotated(180, 0, 1, 0);
    glTranslated(-length1, 0, -1);

    paintBob(xb, yb, 0, 11 * xb, 11 * yb, 0.4980392156862745, 0.2823529411764706, 0.1607843137254902, false, carcas);
    paintBob(11 * xb, yb, 0, 11 * xb, 11 * yb, 1, 1, 0, false, carcas);
    paintBob(21 * xb, yb, 0, 11 * xb, 11 * yb, 0.2235294117647059, 1, 0.0784313725490196, true, carcas);

    glPopMatrix();
}

void glView::paintTrain(double x0, double y0, double z0, double length1, double height1, double width1, bool carcas)
{
    glPushMatrix();
    glTranslated(x0, y0, z0);
    glRotated(0, 0, 1, 0);

    double xb, yb, zb;
    xb = length1 / 16;
    yb = height1 / 8;
    zb = width1 / 7;

    paintBox(xb, yb, zb, 14 * xb, 4 * yb, 5 * zb, 1, 0, 0, carcas);

    paintBox(xb, 0, 0, 3 * xb, 3 * yb, 1 * zb, 0, 0, 0, carcas);
    paintBox(5 * xb, 0, 0, 3 * xb, 3 * yb, 1 * zb, 0, 0, 0, carcas);
    paintBox(xb, 0, 6 * zb, 3 * xb, 3 * yb, 1 * zb, 0, 0, 0, carcas);
    paintBox(5 * xb, 0, 6 * zb, 3 * xb, 3 * yb, 1 * zb, 0, 0, 0, carcas);

    paintBox(9 * xb, 0, 0, 2 * xb, 2 * yb, 1 * zb, 0, 0, 0, carcas);
    paintBox(12 * xb, 0, 0, 2 * xb, 2 * yb, 1 * zb, 0, 0, 0, carcas);
    paintBox(9 * xb, 0, 6 * zb, 2 * xb, 2 * yb, 1 * zb, 0, 0, 0, carcas);
    paintBox(12 * xb, 0, 6 * zb, 2 * xb, 2 * yb, 1 * zb, 0, 0, 0, carcas);

    paintBox(0, yb, 3 * zb, xb, yb, zb, 0, 0, 0, carcas);

    paintBox(xb, 5 * yb, zb, xb, 2 * yb, 5 * zb, 1, 0, 0, carcas);
    paintBox(xb, 7 * yb, zb, 5 * xb, 1 * yb, 5 * zb, 1, 0, 0, carcas);
    paintBox(5 * xb, 5 * yb, zb, xb, 2 * yb, 1 * zb, 1, 0, 0, carcas);
    paintBox(5 * xb, 5 * yb, 5 * zb, xb, 2 * yb, 1 * zb, 1, 0, 0, carcas);

    paintBox(2 * xb, 5 * yb, 1 * zb, 3 * xb, 2 * yb, 5 * zb, 1, 1, 1, carcas);
    paintBox(5 * xb, 5 * yb, 2 * zb, 1 * xb, 2 * yb, 3 * zb, 1, 1, 1, carcas);

    paintBox(9 * xb, 5 * yb, 3 * zb, xb, yb, zb, 0, 0, 0, carcas);
    paintBox(11 * xb, 5 * yb, 3 * zb, xb, yb, zb, 0, 0, 0, carcas);
    paintBox(13 * xb, 5 * yb, 3 * zb, xb, 3 * yb, zb, 0, 0, 0, carcas);

    paintBox(15 * xb, 3 * yb, 3 * zb, 0.2 * xb, yb, zb, 1, 1, 0, carcas);

    glPopMatrix();
}

void glView::paintTableLamp(double x0, double y0, double z0, double length1, double height1, double width1, bool carcas)
{
    glPushMatrix();
    glTranslated(x0, y0, z0);
    glRotated(0, 0, 1, 0);

    GLdouble r = 0;
    GLdouble g = 1;
    GLdouble b = 0;

    double xb = length1 / 21;
    double yb = height1 / 24;
    double zb = width1 / 14;

    paintBox(0, 0, 0, 13 * xb, 2 * yb, 13 * zb, r, g, b, carcas);
    paintBox(5 * xb, 2 * yb, 5 * zb, 3 * xb, 18 * yb, 3 * zb, r, g, b, carcas);
    paintBox(5 * xb, 20 * yb, 5 * zb, 11 * xb, 3 * yb, 3 * zb, r, g, b, carcas);
    paintBox(16 * xb, 19 * yb, 4 * zb, 1 * xb, 5 * yb, 5 * zb, r, g, b, carcas);

    paintBox(17 * xb, 19 * yb, 4 * zb, 4 * xb, 5 * yb, 1 * zb, r, g, b, carcas);
    paintBox(17 * xb, 19 * yb, 8 * zb, 4 * xb, 5 * yb, 1 * zb, r, g, b, carcas);

    paintBox(20 * xb, 19 * yb, 5 * zb, 1 * xb, 5 * yb, 3 * zb, r, g, b, carcas);

    paintBox(17 * xb, 23 * yb, 5 * zb, 3 * xb, 1 * yb, 3 * zb, r, g, b, carcas);

    paintLamp(18.5 * xb, 22 * yb, 6.8 * zb, 1.5 * xb, 3 * yb, 1.5 * zb, carcas);
    GLfloat lightDir1[4] = { 0.0f,1.0f,0.0f };
    GLfloat lightPos1[4] = { GLfloat(18.5 * xb),GLfloat(22 * yb),GLfloat(6.8 * zb), 1.0f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiff1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0f);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightDir1);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, lightAtten1[0]);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, lightAtten1[1]);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, lightAtten1[2]);

    glPopMatrix();
}
