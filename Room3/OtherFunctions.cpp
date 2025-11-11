#include <glview.h>

QVector<double> glView::multiplication(QVector<double> Pol, double d)
{
    for (int i = 0; i < Pol.size(); i++)
        Pol[i] *= d;

    while (Pol.back() == 0 && Pol.size() > 1)
    {
        Pol.pop_back();
    }

    return Pol;
}

QVector<double> glView::multiplication(QVector<double> A, QVector<double> B)
{
    QVector<double> Pol(A.size() + B.size() - 1, 0.0);

    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < B.size(); ++j) {
            Pol[i + j] += A[i] * B[j];
        }
    }

    while (Pol.back() == 0 && Pol.size() > 1)
    {
        Pol.pop_back();
    }

    return Pol;
}

QVector<double> glView::addition(QVector<double> A, QVector<double> B)
{
    QVector<double> Pol;
    while (A.size() != B.size())
        if (A.size() > B.size())
            B.push_back(0);
        else
            if (A.size() < B.size())
                A.push_back(0);
    for (int i = 0; i < A.size(); i++)
        Pol.push_back(A[i] + B[i]);

    while (Pol.back() == 0 && Pol.size() > 1)
    {
    Pol.pop_back();
    }

    return Pol;
}

QVector<double> glView::lagrangePolynomial(QVector<double> X, QVector<double> Y)
{
    int n = X.size();

    QVector<double> P;
    for (int i = 0; i < n; i++)
        P.push_back(0);

    for (int i = 0; i < n; i++)
    {
        QVector<double> L;
        L.push_back(1);
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                L = multiplication(L, QVector<double>{-X[j], 1});
                L = multiplication(L, 1 / (X[i] - X[j]));
            }
        }
        P = addition(P, multiplication(L, Y[i]));
    }

    while (P.back() == 0 && P.size() > 1)
    {
        P.pop_back();
    }

    return P;
}

double glView::PolValue(QVector<double> Pol, double x0)
{
    double S = 0;

    for (int i = 0; i < Pol.size(); i++)
        S += Pol[i] * pow(x0, i);

    return S;
}

QVector<double> glView::PolDerivative(QVector<double> Pol)
{
    while (Pol.back() == 0 && Pol.size() > 1)
    {
        Pol.pop_back();
    }

    QVector<double> PolD;
    for (int i = 0; i < Pol.size() - 1; i++)
    {
        PolD.push_back(Pol[i + 1] * (i + 1));
    }
    return PolD;
}

void glView::moveNivaInter()
{
    QVector3D Niva_Pos_current;
    QVector3D Niva_Pos_next;
    QVector3D Niva_Direction;

    double nextTimeStep;
    nextTimeStep = (time+0.1 >= 100) ? 0 : time+0.001;

    Niva_Pos_current = {(float)PolValue(XPol,time),(float)PolValue(YPol,time),(float)PolValue(ZPol,time)};
    Niva_Pos_next = {(float)PolValue(XPol,nextTimeStep),(float)PolValue(YPol,nextTimeStep),(float)PolValue(ZPol,nextTimeStep)};
    Niva_Direction = Niva_Pos_next - Niva_Pos_current;

    double alpha = Niva_Direction.x() / sqrt( (Niva_Direction.x() * Niva_Direction.x()) + (Niva_Direction.z() * Niva_Direction.z()) );

    double angle;
    if (Niva_Direction.x() <= 0)
    {
        if (Niva_Direction.z() <= 0)
            angle=-45*acos(alpha)/(atan(1));
        else
            angle = 45*acos(alpha)/(atan(1));
    }
    else
    {
        if (Niva_Direction.z() <= 0)
            angle= -45*acos(alpha)/(atan(1));
        else
            angle = 45*acos(alpha)/(atan(1));
    }
    Niva.setPos(Niva_Pos_current.x(),Niva_Pos_current.y(),Niva_Pos_current.z());
    Niva.setRot(angle, Niva.rotWheel);
}
