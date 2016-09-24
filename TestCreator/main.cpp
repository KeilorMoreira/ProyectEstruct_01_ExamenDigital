#include <iostream>

using namespace std;


//#######################   Listas de datos  #############################
/*
TDA examen, lista doble, falta decidir forma de enlace
con partes(SelecUnica y RespBrebe que son sublistas)
*/
struct examen{
    float nota;
    string materia;
    string grupo;
    string parcial;
    int puntosObt;
    float porcentje;
    int puntosTotales;
    struct examen*sig,*ant;
    struct partes*secciones_ptr;
    examen(float n,string m,int pO,int pT,float p,string g,string par){
        nota=n;
        puntosObt=pO;
        puntosTotales=pT;
        materia=m;
        porcentje=p;
        grupo=g;
        parcial=par;
        sig=NULL;
        ant=NULL;
        secciones_ptr=NULL;
    }
}*primeroExamen;

// Parte del examen, lista con preguntas de Seleccion Unica
struct pregSelecUnic{
    int puntosObt;
    int puntosPre;
    string pregunta; // string con la pregunta
    struct pregSelecUnic*sig;
    struct selecUnica *enlaceSel_ptr;
    pregSelecUnic(int pO,int pP,string p){
        puntosObt=pO;
        puntosPre=pP;
        pregunta=p;
        sig=NULL;
        enlaceSel_ptr=NULL;
    }
}*p_PregSel;

// Parte del examen, lista con preguntas de Respuesta Brebe
struct pregRespBrebe{
    int puntosObt;
    int puntosPre;
    string pregunta; // string con la pregunta
    struct pregRespBrebe*sig;
    struct RespBrebe *enlaceRespBre_ptr;
    pregRespBrebe(int pO,int pP,string p){
        puntosObt=pO;
        puntosPre=pP;
        pregunta=p;
        sig=NULL;
        enlaceRespBre_ptr=NULL;
    }
}*p_PregRespBre;

//#######################   Sublistas de enlace  #############################
/*
Puntero heterogenio de enlace a examen que tiene 2 tipos de listas
una para las tipo seleccion y otra para las de respuesta brebe.
*/
struct partes{
    struct selecUnica*L_selecUnica;
    struct RespBrebe*L_respBrebe;
    struct partes*sig;
    partes(){
    }
};

// Puntero heterogenio, sublista de pregSelecUnic
struct selecUnica{
    string descripcion;
    int puntos;
    int puntosObt;
    struct selecUnica*sig;
    struct pregSelecUnic *pregSelUni_prt;
    selecUnica(string des,int pts,int ptsOb){
        descripcion=des;
        puntos=pts;
        puntosObt=ptsOb;
        sig=NULL;
        pregSelUni_prt=NULL;
    }
};

// Puntero heterogenio, sublista de pregRespBrebe
struct RespBrebe{
    string descripcion;
    int puntos;
    int puntosObt;
    struct RespBrebe*sig;
    struct pregRespBrebe*pregRespBre_prt;
    RespBrebe(string des,int pts,int ptsO){
        descripcion=des;
        puntos=pts;
        puntosObt=ptsO;
        sig=NULL;
        pregRespBre_prt=NULL;
    }
};



int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
