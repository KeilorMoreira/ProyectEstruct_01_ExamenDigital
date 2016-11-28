#include <iostream>

using namespace std;
struct examen{
    float nota;
    string materia;
    string grupo;
    string parcial;
    int puntosObtenidos;
    float porcentje;
    int puntosTotales;
    struct examen*sig,*ant;
    struct examenParte*exaP;
    examen(float n,string m,int pO int pT,float p,string g,string par){
        nota=n;
        puntosObtenidos=pO;
        puntosTotales=pT;
        materia=m;
        porcentje=p;
        grupo=g;
        parcial=par;
        sig=NULL;
        ant=NULL;
        exaP=NULL;
    }
}*primeroExamen;
struct pregunta{
    int puntosOct;
    int puntosPre;
    string encabesado;
    struct pregunta*sig;
    struct preguntaRespuesta*pregResp;
    pregunta(int pO,int pP,string e){
        puntosOct=pO;
        puntosPre=pP;
        encabesado=e;
        sig=NULL;
        pregResp=NULL;
    }
}*primeroPregunta;
struct respuesta{
    string repuetaCor;
    struct respuesta*sig;
    respuesta(){
    }
}*primeroRespuesta;
struct parte{
    string encabesado;
    string tipo;
    string partes;
    int puntos;
    int puntosObt;
    struct partePregunta*parpre;
    struct parte*sig;
    parpre(string e,string p,string t,int pu,int pO){
        encabesado=e;
        tipo=t;
        partes=p;
        puntos=pu;
        puntosObt=pO;
        parpre=NULL;
        sig=NULL;
    }
}*primeraParte;
struct examenParte{
    struct examenParte*sig,*ant;
    struct parte*parE;
};
struct partePregunta{
    struct partePregunta*sig,*ant;
    struct pregunta*preg;
};
struct preguntaRespuesta{
    struct preguntaRespuesta*sig,*ant;
    struct respuesta*resp;
};
void insertarExamen(string m,int pT,string g,string par){
    struct examen*nExamen;
}
int main()
{
    return 0;
}
