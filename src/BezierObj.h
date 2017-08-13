#ifndef BEZIEROBJ_H
#define BEZIEROBJ_H

#include "BezierCurve.h"

class BezierObj
{
    public:
        BezierObj(int val);
        ~BezierObj();
        int Getprecision() { return precision; }
        void Setprecision(int val) { precision = val; }
        int add_curve();
        void remove_curve();
        int add_pt(int x, int y);
        void match_pt (int x, int y, bool rem);
        std::list <BezierCurve>::iterator Getselected_curve() { return selected_curve; }
        void Setselected_curve(std::list <BezierCurve>::iterator val) { selected_curve = val; }
        std::list <BezierCurve>::iterator Getselected_curve2() { return selected_curve2; }
        void Setselected_curve2(std::list <BezierCurve>::iterator val) { selected_curve2 = val; }
        void moveSelected_pt(int x, int y);
        bool selected_curve_isEnd();
        bool selected_curve_isBegin();
        bool selected_curve_isLast();
        bool selected_curve2_isEnd();
        bool selected_curve2_isBegin();
        bool selected_curve2_isLast();
        void drawCurves();
        void drawControlPoints();
        void drawCurvesPoints();
        void drawControlPolygon();
        void drawLabels();
        std::list <BezierCurve> Get_curves(){return curves;};
        std::list <Vertex3d> GetcurvesPoints();
        void clear_obj();

    protected:
        void Set_maxCurves (int val){ maxCurves = val; }
        int Get_maxCurves (){ return maxCurves; }
        void Set_isClosed (bool val){ isClosed = val; }
        bool Get_isClosed (){ return isClosed; }

    private:
        int precision;
        int maxCurves;
        bool isClosed;
        std::list <BezierCurve>::iterator selected_curve;
        std::list <BezierCurve>::iterator selected_curve2;
        std::list <BezierCurve> curves;
};

#endif // BEZIEROBJ_H
