#include <iostream>
#include <stdlib.h> // Permite trabajar el cls, pause y otros
#include <locale.h> // Permite utilizar acentos de un lenguaje especificado en Main()
#define L endl
using namespace std;



//#######################   Listas de datos  #############################
/*
TDA examen, lista doble, falta decidir forma de enlace
con partes(SelecUnica y RespBrebe que son sublistas)
*/
struct examen
{

    float nota;
    string codigo,materia,grupo,fecha;
    float porcentje;
    float puntosTotales;
    float puntosObt;
    struct examen*sig,*ant;
    struct partes*secciones_ptr;
    examen(string cod,string mater,string grp,string fech,float porc)
    {
        nota=0;
        puntosObt=0;
        puntosTotales=0;
        grupo=grp;
        codigo=cod;
        materia=mater;
        porcentje=porc;
        fecha=fech;
        sig=NULL;
        ant=NULL;
        secciones_ptr=NULL;
    }
}*primeroExamen;

// Parte del examen, lista con preguntas de Seleccion Unica
struct pregSelecUnic
{
    int puntosObt;
    int puntosPre;
    string pregunta; // string con la pregunta
    struct pregSelecUnic*sig;
    struct selecUnica *enlaceSel_ptr;
    pregSelecUnic(int pO,int pP,string p)
    {
        puntosObt=pO;
        puntosPre=pP;
        pregunta=p;
        sig=NULL;
        enlaceSel_ptr=NULL;
    }
}*p_PregSel;

// Parte del examen, lista con preguntas de Respuesta Brebe
struct pregRespBrebe
{
    int puntosObt;
    int puntosPre;
    string pregunta; // string con la pregunta
    struct pregRespBrebe*sig;
    struct RespBrebe *enlaceRespBre_ptr;
    pregRespBrebe(int pO,int pP,string p)
    {
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
struct partes
{
    struct selecUnica*L_selecUnica;
    struct RespBrebe*L_respBrebe;
    struct partes*sig;
    partes()
    {
    }
};

// Puntero heterogenio, sublista de pregSelecUnic
struct selecUnica
{
    string descripcion;
    int puntos;
    int puntosObt;
    struct selecUnica*sig;
    struct pregSelecUnic *pregSelUni_prt;
    selecUnica(string des,int pts,int ptsOb)
    {
        descripcion=des;
        puntos=pts;
        puntosObt=ptsOb;
        sig=NULL;
        pregSelUni_prt=NULL;
    }
};

// Puntero heterogenio, sublista de pregRespBrebe
struct RespBrebe
{
    string descripcion;
    int puntos;
    int puntosObt;
    struct RespBrebe*sig;
    struct pregRespBrebe*pregRespBre_prt;
    RespBrebe(string des,int pts,int ptsO)
    {
        descripcion=des;
        puntos=pts;
        puntosObt=ptsO;
        sig=NULL;
        pregRespBre_prt=NULL;
    }
};


//####################     Insersiones de datos de Usuario    ########################

//Cnstr: (string cod,string mater,string grp,string fech,float porc)
void insertarExamen()
{
    string a,b,c,cod,mat,grup,fecha; // Variables
    float porc;
    string eleccion="";
    while(eleccion!="continuar")// Asigna parte: a
    {
        cout<<"[1] 1 Examen Parcial.\n"
            <<"[2] 2 Examen Parcial.\n"
            <<"[3] 3 Examen Parcial.\n"
            <<"[4] 4 Examen Parcial.\n"
            <<"[5] 5 Examen Parcial.\n\n-> ";
        getline(cin,eleccion);
        if(eleccion=="1")a="1E";
        else if(eleccion=="2")a="2E";
        else if(eleccion=="3")a="3E";
        else if(eleccion=="4")a="4E";
        else if(eleccion=="5")a="5E";
        else{system("cls");continue;}
        eleccion="continuar";
        system("cls"); // Limpia la pantalla
    }
    eleccion=""; // Vaciamos para que entre al siguiente while
    while(eleccion!="continuar")// Asigna parte: b
    {
        cout<<"[1] 1 Cuatrimestre.\n"
            <<"[2] 2 Cuatrimestre.\n"
            <<"[3] 3 Cuatrimestre.\n"
            <<"[4] 4 Cuatrimestre.\n"
            <<"[5] 1 Semestre.\n"
            <<"[6] 2 Semestre.\n\n-> ";
        getline(cin,eleccion);
        if(eleccion=="1")b="1C";
        else if(eleccion=="2")b="2C";
        else if(eleccion=="3")b="3C";
        else if(eleccion=="4")b="4C";
        else if(eleccion=="5")b="1S";
        else if(eleccion=="5")b="2S";
        else{system("cls");continue;}
        eleccion="continuar";
        system("cls");
    }
    eleccion="";
    while(eleccion!="continuar")// Asigna parte: c
    {
        cout<<"[1] 2016.\n"
            <<"[2] 2017.\n"
            <<"[3] 2018.\n"
            <<"[4] 2019.\n"
            <<"[5] 2020.\n"
            <<"[6] Otro.\n\n-> ";
        getline(cin,eleccion);
        if(eleccion=="1")c="2016";
        else if(eleccion=="2")c="2017";
        else if(eleccion=="3")c="2018";
        else if(eleccion=="4")c="2019";
        else if(eleccion=="5")c="2020";
        else if(eleccion=="6"){cout<<"Digite: ";getline(cin,c);}
        else{system("cls");continue;}
        eleccion="continuar";
        system("cls");
    }
    eleccion="";
    while(eleccion!="continuar")// Asigna materia
    {
        cout<<"[1] Estructuras de Datos.\n"
            <<"[2] Programación Orientada a Objetos.\n"
            <<"[3] Arquitectura de Computadores.\n"
            <<"[4] Otro.\n\n-> ";
        getline(cin,eleccion);
        if(eleccion=="1")mat="Estructuras de Datos.";
        else if(eleccion=="2")mat="Programación Orientada a Objetos.";
        else if(eleccion=="3")mat="Arquitectura de Computadores.";
        else if(eleccion=="4"){cout<<"Digite: ";getline(cin,mat);}
        else{system("cls");continue;}
        eleccion="continuar";
        system("cls");
    }
    eleccion="";
    while(eleccion!="continuar")// Asigna grupo.
    {
        cout<<"[1] Grupo 50.\n"
            <<"[2] Grupo 51.\n"
            <<"[3] Otro.\n\n-> ";
        getline(cin,eleccion);
        if(eleccion=="1")grup="Grupo 50.";
        else if(eleccion=="2")grup="Grupo 51.";
        else if(eleccion=="3"){cout<<"Digite: ";getline(cin,grup);}
        else{system("cls");continue;}
        eleccion="continuar";
        system("cls");
    }
    eleccion="";
    while(eleccion!="continuar")// Asigna porcentaje.
    {
        cout<<"[1] 5%.\n"
            <<"[2] 10%.\n"
            <<"[3] 15%.\n"
            <<"[4] 20%.\n"
            <<"[5] 25%.\n"
            <<"[6] Otro.\n\n-> ";
        getline(cin,eleccion);
        if(eleccion=="1")porc=0.05;
        else if(eleccion=="2")porc=0.1;
        else if(eleccion=="3")porc=0.15;
        else if(eleccion=="4")porc=0.2;
        else if(eleccion=="5")porc=0.25;
        else if(eleccion=="6"){cout<<"Digite [ 10% -> 0.1 && 15% -> 0.15 ] : -> ";cin>>porc;}
        else{system("cls");continue;}
        eleccion="continuar";
        system("cls");
    }

    // A crear el nodo.
    cod=a+b+c;
    cout<<"Fecha de aplicacion [DD/MM/AAAA]: -> ";getline(cin,fecha);
    struct examen*nExamen= new examen(cod,mat,grup,fecha,porc);
    if(primeroExamen==NULL)
    {
        primeroExamen=nExamen;
    }
    else
    {
        nExamen->sig=primeroExamen;
        primeroExamen->ant=nExamen;
        primeroExamen=nExamen;
    }
}

//#########################  Funciones de datos predefinidos ########################
// Funcion para insertar examenes ejemplo.
void insertExam(string cod,string mat,string grup,string fecha,float porc)
{
    struct examen*nExamen= new examen(cod,mat,grup,fecha,porc);
    if(primeroExamen==NULL)
    {
        primeroExamen=nExamen;
    }
    else
    {
        nExamen->sig=primeroExamen;
        primeroExamen->ant=nExamen;
        primeroExamen=nExamen;
    }
}

int main()
{
    setlocale(LC_ALL, "spanish"); // Asigna lenguaje español como predeterminado.

    insertExam("codigo1","materia1","grupo1","fecha1",0.1);
    insertExam("codigo2","materia2","grupo2","fecha2",0.2);
    insertExam("codigo3","materia3","grupo3","fecha3",0.3);
    // Codigo de comprobacion
    struct examen *t = primeroExamen;
    while(t!=NULL){
        cout<<"Cod:     "<<t->codigo<<L;
        cout<<"Materia: "<<t->materia<<L;
        cout<<"grupo:   "<<t->grupo<<L;
        cout<<"fecha:   "<<t->fecha<<L;
        cout<<"Porcent: "<<t->porcentje<<L<<L;
        t = t->sig;
    }
    //insertarExamen(); // insersion por el usuario
    return 0;
}
