#include "BezierObj.h"

BezierObj::BezierObj(int val)
{
    this->Set_maxCurves(10);
    this->Set_isClosed(false);
    this->Setprecision(val);
    this->Setselected_curve(this->curves.end());
    //ctor
}

BezierObj::~BezierObj()
{
    //dtor
}


int BezierObj::add_curve(){

    if(this->curves.size() < this->Get_maxCurves()){

        /** Cria a curva com a precisão determinada*/
        BezierCurve curve(this->Getprecision());

        /** Caso não seja a primeira curva adicionada,
         ** já adiciono o último ponto da última curva a ela, para manter conectividade das curvas */
        if( ! this->curves.empty()){
            Vertex3d temp  = this->curves.back().GetcontrolPoints().back();
            curve.add_pt(temp.GetX(), temp.GetY());
        }

        /** Adiciona a curva na lista de curvas*/
        this->curves.push_back(curve);
        return this->curves.size();
    }
    return -1;
}

int BezierObj::add_pt(int x, int y){
    /** Ponto é sempre adicionado a última curva da lista*/
    if(this->curves.empty() || curves.back().Getdegree() == curves.back().GetmaxDegree()){
        if(this->add_curve() == -1){
            return -1;
        }
    }
    /** Ponto é adicionado a última curva da lista */
    return curves.back().add_pt(x, y);
}

void BezierObj::remove_curve(){
    /** Remove a curva se ela não tiver mais que 1 ponto e for de um extremo da lista de curvas*/
    /** Remove o ponto se ele não for ponto de junção de curvas */
    BezierCurve *temp = &*(this->Getselected_curve());
    /** Se o ponto não for do extremo de uma curva */
    if( ! temp->selected_pt_isBegin() && ! temp->selected_pt_isLast()){
        if(temp->Getdegree() > 1){
            temp->remove_pt();
            std::cout<<"Removendo ponto do meio da curva"<<std::endl;
        }
    /** Se o ponto não for do fim de uma curva do começo da lista de curvas ou não for o começo de uma curva do fim da lista */
    } else if( (temp->selected_pt_isBegin() && this->selected_curve_isBegin())
              || ( temp->selected_pt_isLast() && this->selected_curve_isLast() )) {
                temp->remove_pt();
                if(temp->Getdegree() < 1){
                    (&*(this->Getselected_curve()))->clear_curve();
                    this->curves.erase(this->Getselected_curve());
                }
    }

    temp->Setselected_pt(temp->GetcontrolPoints().end());
    this->Setselected_curve(this->curves.end());
    this->Setselected_curve2(this->curves.end());
}

void BezierObj::match_pt (int x, int y, bool rem){

    /** Reseto a curva selecionada pro fim da lista*/
    bool curve_seted = false;
    this->Setselected_curve(this->curves.end());
    this->Setselected_curve2(this->curves.end());
    std::list<BezierCurve>::iterator iter;
    for ( iter = this->curves.begin(); iter != this->curves.end(); iter++){
        BezierCurve *temp = &*iter;
        temp->match_pt(x, y, false);
        if( ! temp->selected_pt_isEnd()){
            if(curve_seted){
                this->Setselected_curve2(iter);
                break;
            } else{
                this->Setselected_curve(iter);
                curve_seted = true;
                /**Caso tenha dado match seta a curva selecionada e verifica se posso remover o ponto*/
                /** E remove a curva caso necessário*/
                if(rem){
                    this->remove_curve();
                    break;
                }
            }

        }
    }
}

void BezierObj::moveSelected_pt(int x, int y){
    /** Move ponto e demais pontos se for de junção */
    BezierCurve *temp = &*(this->Getselected_curve());
    temp->moveSelected_pt(x, y);
    if( ! this->selected_curve2_isEnd()){
        BezierCurve *temp2 = &*(this->Getselected_curve2());
        temp2->moveSelected_pt(x, y);
    }
}

bool BezierObj::selected_curve_isEnd(){
    return this->Getselected_curve() == this->curves.end();
}

bool BezierObj::selected_curve_isBegin(){
    return this->Getselected_curve() == this->curves.begin();
}

bool BezierObj::selected_curve_isLast(){
    return this->Getselected_curve() == (--this->curves.end());
}

bool BezierObj::selected_curve2_isEnd(){
    return this->Getselected_curve2() == this->curves.end();
}

bool BezierObj::selected_curve2_isBegin(){
    return this->Getselected_curve2() == this->curves.begin();
}

bool BezierObj::selected_curve2_isLast(){
    return this->Getselected_curve2() == (--this->curves.end());
}

void BezierObj::drawCurves(){

    glDisable(GL_LIGHTING);
    std::list<BezierCurve>::iterator iter = this->curves.begin();
    for( ; iter != this->curves.end(); iter++){
        BezierCurve temp = *iter;
        if(temp.Getdegree() > 0){
            temp.drawCurve();
        }
    }
    glEnable(GL_LIGHTING);
}

void BezierObj::drawControlPoints(){

    std::list<BezierCurve>::iterator iter = this->curves.begin();
    for( ; iter != this->curves.end(); iter++){
        BezierCurve temp = *iter;
        temp.drawControlPoints();
    }
}

void BezierObj::drawCurvesPoints(){

    std::list<BezierCurve>::iterator iter = this->curves.begin();
    for( ; iter != this->curves.end(); iter++){
        BezierCurve temp = *iter;
        if(temp.Getdegree() > 0){
            temp.drawCurvePoints();
        }
    }
}

void BezierObj::drawControlPolygon(){

    std::list<BezierCurve>::iterator iter = this->curves.begin();
    for( ; iter != this->curves.end(); iter++){
        BezierCurve temp = *iter;
        if(temp.Getdegree() > 0){
            temp.drawControlPolygon();
        }
    }
}

void BezierObj::drawLabels(){

    std::list<BezierCurve>::iterator iter = this->curves.begin();
    for( ; iter != this->curves.end(); iter++){
        BezierCurve temp = *iter;
        temp.drawLabels();
    }
}

std::list <Vertex3d> BezierObj::GetcurvesPoints(){

    std::list <Vertex3d> ret, aux;
    std::list<BezierCurve>::iterator iter = this->curves.begin();
    for( ; iter != this->curves.end(); iter++){
        BezierCurve temp = *iter;
        aux = temp.GetcurvePoints();
        ret.insert(ret.end(), aux.begin(), aux.end());
    }
    return ret;
}

void BezierObj::clear_obj(){

    std::list<BezierCurve>::iterator iter = this->curves.begin();
    for( ; iter != this->curves.end(); iter++){
        BezierCurve temp = *iter;
        temp.clear_curve();
    }
    this->curves.clear();
}
