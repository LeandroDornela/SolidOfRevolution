#include <iostream>
#include <GL/glui.h>
#include <GL/glut.h>
#include "BezierObj.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>

/** N�mero de segmentos usados na curva **/
#define SEG 10

int prec = SEG;
BezierObj* bezier = new BezierObj(prec*2);
bool polygon = true, label = false, vertex = true, curve = true;

void bezierMotion(int x, int y)
{
    /** Movimenta um ponto selecionado **/
    if(!bezier->selected_curve_isEnd())
    {
        /** Movimenta��o dos pontos em 2d � feita apenas quando o mouse est� na parte 2d da tela*/
        if(x >= 0 && x <= width/6 && y >= 0 && y <= height/3){
            BezierCurve temp  = *bezier->Getselected_curve();
                    Vertex3d temp2 = *temp.Getselected_pt();
            bezier->moveSelected_pt(x, y);
        }
	}
}

void bezierMouse(int button, int state, int x, int y)
{
    if(x <= width/6)
    {
        if(button == GLUT_LEFT_BUTTON)
        {
            if(state == GLUT_DOWN)
            {
                /** N�o permito criar um ponto com o centro em cima do outro, para facilitar a sele��o de ponto.
                 ** Caso isso aconte�a, o ponto � selecionado para movimenta��o
                 **/
                bezier->match_pt(x, y, false);
                if(bezier->selected_curve_isEnd())
                {
                    /** Cria um ponto no local clicado pelo bot�o esquerdo do mouse **/
                    bezier->add_pt(x, y);
                } else{
                    BezierCurve temp  = *bezier->Getselected_curve();
                    Vertex3d temp2 = *temp.Getselected_pt();
                    //std::cout<<"Match point: ["<<temp2.GetX()<<", "<<temp2.GetY()<<"]"<<std::endl;
                }
            }
            else
            {
                if(!bezier->selected_curve2_isEnd()){
                    bezier->Setselected_curve(bezier->Get_curves().end());
                }

            }
        }

        if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        {
            /** Remove ponto existente no local clicado pelo bot�o direito do mouse **/
            bezier->match_pt(x, y, true);
            /** Caso seja necess�rio saber se o ponto foi realmente removido/encontrado,
             ** basta verificar se o retorno de bezier->selected_pt_isEnd() � false
             **/
        }
    }
}

void bezierView()
{
    if(curve)
    {
        /** Desenha a curva usando a fun��o criada para tal **/
        bezier->drawCurves();
    }
	/** Desenha os pontos de controle com um raio maior para facilitar sele��o **/
    if(vertex)
    {
        bezier->drawControlPoints();
    }
    /** Renderiza os labels de cada ponto **/
    if(label)
    {
        bezier->drawLabels();
    }
    /** Desenha pol�gono de controle **/
    if(polygon)
    {
        bezier->drawControlPolygon();
    }
}
