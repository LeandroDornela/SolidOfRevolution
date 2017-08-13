#include "BezierCurve.h"

/** Define posicionamento do label em relação ao ponto e prefixo do label**/
#define LABEL_X 3
#define LABEL_Y 3
#define PREFIX "P"


BezierCurve::BezierCurve(int val)
{
    this->Setprecision(val);
    this->SetpointRadius(3);
    this->SetmaxDegree(4);
    this->Setselected_pt(this->controlPoints.end());
    this->labels.setColor(0.0, 0.0, 0.0);
    this->labels.setType(2);
}

BezierCurve::~BezierCurve()
{
    //dtor
}

int BezierCurve::add_pt(int x, int y){

    /** Verifica se cabe um novo ponto no vetor **/
    if( this->Getdegree() < this->GetmaxDegree()){
        /** Adiciona a coordenadas ao ponto temporário **/
        Vertex3d aux;
        aux.SetX((float) x);
        aux.SetY((float) y);
        aux.SetZ(0.0);
        /** Adiciona o ponto na lista */
        this->controlPoints.push_back(aux);
        /** Atualiza pontos da curva */
        this->setCurve();
        /** Retorna grau atual da curva **/
        return this->Getdegree();
    }
    /** Caso não seja possível adicionar um ponto, o retorno informa isso **/
    return -1;
}

void BezierCurve::remove_pt(){

     this->controlPoints.erase(this->Getselected_pt());
     this->setCurve();
}

void BezierCurve::match_pt (int x, int y, bool rem){
    /** Reseto o ponto selecionado pro fim da lista*/
    this->Setselected_pt(this->controlPoints.end());
    std::list<Vertex3d>::iterator iter;
    for ( iter = this->controlPoints.begin(); iter != this->controlPoints.end(); iter++){
        Vertex3d temp = *iter;
        if(temp.GetX() <= (x + this->GetpointRadius()) &&
           temp.GetX() >= (x - this->GetpointRadius()) &&
           temp.GetY() <= (y + this->GetpointRadius()) &&
           temp.GetY() >= (y - this->GetpointRadius())){
            /**Caso tenha dado match seta o ponto selecionado*/
            this->Setselected_pt(iter);
            /** E remove de acordo com o parametro*/
            if(rem){
                remove_pt();
            }
            break;
        }
    }
}

void BezierCurve::moveSelected_pt(int x, int y){

    (&*(this->Getselected_pt()))->SetX((float) x);
    (&*(this->Getselected_pt()))->SetY((float) y);
    this->setCurve();
}

bool BezierCurve::selected_pt_isEnd(){
    return this->Getselected_pt() == this->controlPoints.end();
}

bool BezierCurve::selected_pt_isBegin(){
    return this->Getselected_pt() == this->controlPoints.begin();
}

bool BezierCurve::selected_pt_isLast(){
    return this->Getselected_pt() == (--this->controlPoints.end());
}

Vertex3d BezierCurve::interpolate(int degree, float u, std::list <Vertex3d> pts){

    std::list<Vertex3d>::iterator iter = pts.begin(), iter2 = iter;
    Vertex3d vertex_temp = *iter, vertex_temp2; /** Vertices para fazer a interpolacao do ponto atual com o proximo*/
    float x = 0, y = 0, z = 0; /** Variaveis auxiliares para guardarem as coordenadas*/

    if(degree == 0){
        return vertex_temp;
    }
    /** Versao otimizada para grau 2 */
    if(degree == 1){
        return interpolate1(degree, u, pts);
    }
    /** Versao otimizada para grau 2 */
    if(degree == 2){
        return interpolate2(degree, u, pts);
    }
    /** Versao otimizada para grau 3 */

    if(degree == 3){
        return interpolate3(degree, u, pts);
    }


    std::list <Vertex3d> temp_pts;

    for( ; iter != pts.end(); iter++){
        vertex_temp = *iter;
        iter2++;
        vertex_temp2 = *iter2;
        x = (1.0 - u) * vertex_temp.GetX() + u * vertex_temp2.GetX();
        y = (1.0 - u) * vertex_temp.GetY() + u * vertex_temp2.GetY();
        z = (1.0 - u) * vertex_temp.GetZ() + u * vertex_temp2.GetZ(); // Para interpolar em 3 dimensões **/

        Vertex3d vertex_aux;
        vertex_aux.SetX(x);
        vertex_aux.SetY(y);
        vertex_aux.SetZ(z);

        temp_pts.push_back(vertex_aux);
    }

    return interpolate(degree - 1, u, temp_pts);
}

Vertex3d BezierCurve::interpolate1(int degree, float u, std::list <Vertex3d> pts){

    std::list<Vertex3d>::iterator iter = pts.begin();
    Vertex3d vertex_temp = *iter;
    float x = 0, y = 0, z = 0; /** Variaveis auxiliares para guardarem as coordenadas*/

    /** Versao otimizada para grau 1 */
    float one_minus_u = 1 - u;

    x += vertex_temp.GetX() * one_minus_u;
    y += vertex_temp.GetY() * one_minus_u;
    z += vertex_temp.GetZ() * one_minus_u;

    iter++;
    vertex_temp = *iter;

    x += vertex_temp.GetX() * u;
    y += vertex_temp.GetY() * u;
    z += vertex_temp.GetZ() * u;

    vertex_temp.SetX(x);
    vertex_temp.SetY(y);
    vertex_temp.SetZ(z);

    return vertex_temp;
}

Vertex3d BezierCurve::interpolate2(int degree, float u, std::list <Vertex3d> pts){

    std::list<Vertex3d>::iterator iter = pts.begin();
    Vertex3d vertex_temp = *iter;
    float x = 0, y = 0, z = 0; /** Variaveis auxiliares para guardarem as coordenadas*/

    /** Versao otimizada para grau 2 */
    float u_square = u * u;
    float one_minus_u = 1 - u;
    float one_minus_u_square = one_minus_u * one_minus_u;

    x += vertex_temp.GetX() * one_minus_u_square;
    y += vertex_temp.GetY() * one_minus_u_square;
    z += vertex_temp.GetZ() * one_minus_u_square;

    iter++;
    vertex_temp = *iter;

    x += vertex_temp.GetX() * 2 * one_minus_u * u;
    y += vertex_temp.GetY() * 2 * one_minus_u * u;
    z += vertex_temp.GetZ() * 2 * one_minus_u * u;

    iter++;
    vertex_temp = *iter;

    x += vertex_temp.GetX() * u_square;
    y += vertex_temp.GetY() * u_square;
    z += vertex_temp.GetZ() * u_square;

    vertex_temp.SetX(x);
    vertex_temp.SetY(y);
    vertex_temp.SetZ(z);

    return vertex_temp;
}

Vertex3d BezierCurve::interpolate3(int degree, float u, std::list <Vertex3d> pts){

    std::list<Vertex3d>::iterator iter = pts.begin();
    Vertex3d vertex_temp = *iter;
    float x = 0, y = 0, z = 0; /** Variaveis auxiliares para guardarem as coordenadas*/

    /** Versao otimizada para grau 3 */
    float u_square = u * u;
    float u_cubic = u_square * u;
    float one_minus_u = 1 - u;
    float one_minus_u_square = one_minus_u * one_minus_u;
    float one_minus_u_cubic = one_minus_u_square * one_minus_u;

    x += vertex_temp.GetX() * one_minus_u_cubic;
    y += vertex_temp.GetY() * one_minus_u_cubic;
    z += vertex_temp.GetZ() * one_minus_u_cubic;

    iter++;
    vertex_temp = *iter;

    x += vertex_temp.GetX() * 3 * one_minus_u_square * u;
    y += vertex_temp.GetY() * 3 * one_minus_u_square * u;
    z += vertex_temp.GetZ() * 3 * one_minus_u_square * u;

    iter++;
    vertex_temp = *iter;

    x += vertex_temp.GetX() * 3 * one_minus_u * u_square;
    y += vertex_temp.GetY() * 3 * one_minus_u * u_square;
    z += vertex_temp.GetZ() * 3 * one_minus_u * u_square;

    iter++;
    vertex_temp = *iter;

    x += vertex_temp.GetX() * u_cubic;
    y += vertex_temp.GetY() * u_cubic;
    z += vertex_temp.GetZ() * u_cubic;

    vertex_temp.SetX(x);
    vertex_temp.SetY(y);
    vertex_temp.SetZ(z);

    return vertex_temp;
}

void BezierCurve::drawCurve(){

    std::list<Vertex3d>::iterator iter = this->interpolatedPoints.begin();
    glColor3f(0.2, 0.2, 0.6);
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    for( ; iter != this->interpolatedPoints.end(); iter++){
        Vertex3d temp = *iter;
        glVertex3f(temp.GetX(), temp.GetY(), temp.GetZ());
    }
    glEnd();
}

void BezierCurve::setCurve (){

    float t , i;
    t = 1.0 / this->precision;
    int j;
    std::list<Vertex3d>::iterator iter = this->controlPoints.begin();
    Vertex3d temp = *iter;
    this->interpolatedPoints.clear();
    if(this->Getdegree() >= 0){
        /** Adiciona o primeiro ponto, já que ele será interpolado **/
        this->interpolatedPoints.push_back(temp);
        for(i = t, j = 1; j < this->precision; i += t, j += 1){
            /** Calcula e adiciona uma quantidade de pontos compatível com o número de segmentos especificado **/
            temp = interpolate(this->Getdegree(), i, this->controlPoints);
            this->interpolatedPoints.push_back(temp);
        }
        /** Adiciona o último ponto, já que ele será interpolado também **/
        iter = this->controlPoints.end();
        iter--;
        temp = *iter;
        this->interpolatedPoints.push_back(temp);
    }
}

void BezierCurve::printControlPoints(){

    std::list<Vertex3d>::iterator iter = this->controlPoints.begin();
    printf("\n~~~~~~~~ Pontos de controle ~~~~~~~~\n");
    for(int i = 0 ; iter != this->controlPoints.end(); iter++, i++){
        Vertex3d temp = *iter;
        printf("\nPonto %i ", i);
        temp.print();
    }
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void BezierCurve::printCurvePoints(){

    std::list<Vertex3d>::iterator iter = this->interpolatedPoints.begin();
    printf("\n~~~~~~~~ Pontos interpolados ~~~~~~~~\n");
    for(int i = 0 ; iter != this->interpolatedPoints.end(); iter++, i++){
        Vertex3d temp = *iter;
        printf("\nPonto %i ", i);
        temp.print();
    }
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void BezierCurve::drawControlPoints(){

    glDisable(GL_LIGHTING);
    std::list<Vertex3d>::iterator iter = this->controlPoints.begin();
    glPointSize(2*this->GetpointRadius());
    glBegin(GL_POINTS);
    for( int i=0; iter != this->controlPoints.end(); iter++, i++){
        Vertex3d temp = *iter;
        if(this->selected_pt == iter){
           /** Caso o ponto esteja selecionado, a cor dele muda para destacá-lo dos demais **/
           glColor3f(1.0, 1.0, 0.0);
        } else{
           glColor3f(0.0, 0.6, 0.0);
        }
        glVertex3f(temp.GetX(), temp.GetY(), temp.GetZ());
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

void BezierCurve::drawCurvePoints(){

    glDisable(GL_LIGHTING);
    std::list<Vertex3d>::iterator iter = this->interpolatedPoints.begin();
    glPointSize(2*this->GetpointRadius());
    glColor3f(0.0, 1.0, 0.3);
    glBegin(GL_POINTS);
    for( ; iter != this->interpolatedPoints.end(); iter++){
        Vertex3d temp = *iter;
        glVertex3f(temp.GetX(), temp.GetY(), temp.GetZ());
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

void BezierCurve::drawControlPolygon(){

   glDisable(GL_LIGHTING);
   std::list<Vertex3d>::iterator iter = this->controlPoints.begin();
   glLineWidth(1.0);
   glColor3f(0.7, 0.0, 0.0);
   glBegin(GL_LINE_STRIP);
   for( ; iter != this->controlPoints.end(); iter++){
       Vertex3d temp = *iter;
       glVertex3f(temp.GetX(), temp.GetY(), temp.GetZ());
   }
   glEnd();
   glEnable(GL_LIGHTING);
}

void BezierCurve::drawLabels(){

   glDisable(GL_LIGHTING);
   std::list<Vertex3d>::iterator iter = this->controlPoints.begin();
   for(int i = 0; iter != this->controlPoints.end(); iter++, i++){
       Vertex3d temp = *iter;

       char l_temp[sizeof(PREFIX) + 3];
       snprintf(l_temp, sizeof(PREFIX) + 3, "%s%i", PREFIX, i);
       this->labels.setPos((int)(temp.GetX() + LABEL_X), (int)(temp.GetY() + LABEL_Y));
       this->labels.setString(l_temp);
       if(selected_pt == iter){
           /** Caso o ponto esteja selecionado, a cor do label dele muda para destacá-lo dos demais **/
           glColor3f(1.0, 1.0, 0.0);
       } else{
           glColor3f(0.0, 0.0, 0.0);
       }

       this->labels.render();
   }
   glEnd();
   glEnable(GL_LIGHTING);
}

void BezierCurve::clear_curve(){
    this->controlPoints.clear();
    this->Setselected_pt(this->controlPoints.end());
    this->setCurve();
}
