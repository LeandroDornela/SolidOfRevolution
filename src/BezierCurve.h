#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include "Vertex3d.h"
#include <iostream>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "glcText.h"

class BezierCurve
{
    public:
        BezierCurve(int val);
        ~BezierCurve();

        int Getdegree() { return controlPoints.size() - 1; }
        int GetmaxDegree() { return maxDegree; }
        void SetmaxDegree(int val) { maxDegree = val; }
        int Getprecision() { return precision; }
        void Setprecision(int val) { precision = val; }
        std::list <Vertex3d> GetcontrolPoints(){return controlPoints; };
        std::list <Vertex3d> GetcurvePoints(){return interpolatedPoints; };
        int add_pt(int x, int y);
        void remove_pt();
        void match_pt (int x, int y, bool rem);
        std::list <Vertex3d>::iterator Getselected_pt() { return selected_pt; }
        void Setselected_pt(std::list <Vertex3d>::iterator val) { selected_pt = val; }
        void moveSelected_pt(int x, int y);
        Vertex3d interpolate(int degree, float u, std::list <Vertex3d> pts);
        void setCurve();
        void drawCurve();
        void drawControlPoints();
        void drawCurvePoints();
        void drawControlPolygon();
        void drawLabels();
        void printControlPoints();
        void printCurvePoints();
        bool selected_pt_isEnd();
        bool selected_pt_isBegin();
        bool selected_pt_isLast();
        void clear_curve();

    protected:
        int GetpointRadius() { return pointRadius; }
        void SetpointRadius(int val) { pointRadius = val; }
        Vertex3d interpolate1(int degree, float u, std::list <Vertex3d> pts);
        Vertex3d interpolate2(int degree, float u, std::list <Vertex3d> pts);
        Vertex3d interpolate3(int degree, float u, std::list <Vertex3d> pts);

    private:
        int degree;
        int maxDegree;
        int pointRadius;
        int precision;
        glcText labels;
        std::list <Vertex3d>::iterator selected_pt;
        std::list <Vertex3d> controlPoints;
        std::list <Vertex3d> interpolatedPoints;
};

#endif // BEZIERCURVE_H
