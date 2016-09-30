#include <iostream>
#include <stdlib.h> // Permite trabajar el cls, pause y otros
#include <locale.h> // Permite utilizar acentos de un lenguaje especificado en Main()
#include <stdio.h> //  Permite utilizar metodo fflush( stdin ) para limpiar la entrada de teclado antes de los getline()
#include <string>
#define L endl
#define A cout<<endl<<"A"; // borrar
#define B cout<<endl<<"B"; // borrar
#define opcResp 10 //Tamaño array de respuestas correctas de Respuesta Brebe e incorrectas de seleccion unica.

using namespace std;


//************************************************************************************
//*                            Listas de datos
//************************************************************************************

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
    struct listaSU*listaSU_ptr;
    struct listaRB*listaRB_ptr;
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
        listaSU_ptr=NULL;
        listaRB_ptr=NULL;
    }
}*P_Examen;

struct respuesta
{
    bool check;
    string resp;
    struct respuesta*sig;
    respuesta(string r)
    {
        check=false;
        resp=r;
        sig=NULL;
    }

}*P_Respuesta;

// Parte del examen, lista con preguntas de Seleccion Unica
struct pregunta
{
    int puntosObt;
    int puntosPre;
    string preg; // string con la pregunta
    string rpsta;// Respuesta correcta SeleUnica
    string opciones[opcResp];
    struct pregunta*sig;
    // Constructor para seleccion unica
    pregunta(string p, string re)
    {
        preg=p;
        rpsta=re;
        sig=NULL;
    }
    // Constructor para Resp Breve
    pregunta(string p)
    {
        preg=p;
        sig=NULL;
    }
}*P_Pregunta;


// Lista
struct selecUnica
{
    string descripcion;
    int puntos;
    int puntosObt;
    struct selecUnica*sig;
    struct pregunta *pregunta_prt;
    selecUnica(string des,int pts)
    {
        descripcion=des;
        puntos=pts;
        sig=NULL;
        pregunta_prt=NULL;
    }
}*P_SelecUnica;

//Lista
struct respBrebe
{
    string descripcion;
    int puntos;
    int puntosObt;
    struct respBrebe*sig;
    struct pregunta*pregunta_prt;
    respBrebe(string des,int pts)
    {
        descripcion=des;
        puntos=pts;
        sig=NULL;
        pregunta_prt=NULL;
    }
}*P_RespBrebe;

//************************************************************************************
//*                             Sublistas de enlace
//************************************************************************************

struct listaSU
{
    struct selecUnica*selecUnica_ptr;
    struct listaSU*sig;
    listaSU()
    {
        selecUnica_ptr=NULL;
        sig=NULL;
    }
};

struct listaRB
{
    struct respBrebe*respBrebe_ptr;
    struct listaRB*sig;
    listaRB()
    {
        respBrebe_ptr=NULL;
        sig=NULL;
    }
};


//************************************************************************************
//*                        Insersiones de datos de Usuario                           *
//************************************************************************************

// Inserta pregunta seleccion unica, opciones el numero de opciones de respuesta.
void insertarPregSelecUnica(struct selecUnica*tempSU,int opci)
{
    string pre,res,opc;
    fflush( stdin );
    getline(cin,pre);
    cout<<"Respuesta Correcta:";
    fflush( stdin );
    getline(cin,res);
    //Creamos la pregunta
    struct pregunta*nPregunta= new pregunta(pre,res);
    nPregunta->opciones[0]=res;//Posicion 0 siempre es la correcta.
    if(P_Pregunta==NULL)P_Pregunta=nPregunta;
    else
    {
        nPregunta->sig=P_Pregunta;
        P_Pregunta=nPregunta;
    }
    //Agregamos las opciones
    for(int i=1; i<opci; i++)
    {
        cout<<L<<"Resp Incorrecta No "<<i<<" :";
        fflush( stdin );
        getline(cin,opc);
        nPregunta->opciones[i]=opc;
        cout<<"<Respuesta Asignada>"<<L;
    }

    // Impresion de comprobacion.
    //cout<<L<<nPregunta->opciones[0];
    //cout<<L<<nPregunta->opciones[1];
    //cout<<L<<nPregunta->opciones[2];

    //Agregamos la pregunta la selecciion unica
    if(tempSU->pregunta_prt==NULL)tempSU->pregunta_prt=nPregunta;
    else
    {
        nPregunta->sig=tempSU->pregunta_prt;
        tempSU->pregunta_prt=nPregunta;
    }
}

void insertarPregRespBrebe(struct respBrebe*tempRB,int resps)
{
    string pre,res,opc;

    fflush( stdin );
    getline(cin,pre);
    //Creamos la pregunta
    struct pregunta*nPregunta= new pregunta(pre);
    if(P_Pregunta==NULL)P_Pregunta=nPregunta;
    else
    {
        nPregunta->sig=P_Pregunta;
        P_Pregunta=nPregunta;
    }
    for (int j=0; j<resps; j++)
    {
        cout<<L<<"Respuesta corecta ["<<j+1<<"] : ";
        fflush( stdin );
        getline(cin,res);
        nPregunta->opciones[j]=res;
    }
    //Comprobacion
    //cout<<L<<nPregunta->opciones[0];
    //cout<<L<<nPregunta->opciones[1];

    //Agregamos la pregunta la selecciion unica
    if(tempRB->pregunta_prt==NULL)tempRB->pregunta_prt=nPregunta;
    else
    {
        nPregunta->sig=tempRB->pregunta_prt;
        tempRB->pregunta_prt=nPregunta;
    }
}

void insertarSU(struct examen*nodoExamen,struct selecUnica*nodoSU)
{

    struct selecUnica*tempSec=nodoExamen->listaSU_ptr->selecUnica_ptr;?????????????????????????????????????????
    A
    if(tempSec==NULL)tempSec=nodoSU;
    else
    {
        nodoSU->sig=tempSec;
        tempSec=nodoSU;
    }

}

void insertarRB(struct examen*nodoExamen,struct respBrebe*nodoRB)
{
    struct respBrebe*tempSec=nodoExamen->listaRB_ptr->respBrebe_ptr;
    if(tempSec==NULL)tempSec=nodoRB;
    else
    {
        nodoRB->sig=tempSec;
        tempSec=nodoRB;
    }
}

void agregarSU(struct examen*nodoExamen)
{
    string des;
    int pts,opc,pre;
    //Creamos el nodo de seleccion
    cout<<L<<"Encabezado del ejercicio: ";
    fflush( stdin );
    getline(cin,des);
    cout<<L<<"Cantidad de ejercios en la seccion: ";
    fflush( stdin );
    cin>>pre;
    cout<<L<<"Cantidad de opciones de respuesta: ";
    fflush( stdin );
    cin>>opc;
    cout<<L<<"Cantidad de puntos por respuesta: ";
    fflush( stdin );
    cin>>pts;
    struct selecUnica*nodoSU=new selecUnica(des, pts);
    for(int i=0; i<pre; i++)
    {
        cout<<"Pegunta No "<<i+1<<" :";
        insertarPregSelecUnica(nodoSU,opc);
    }
    // Asignamos el nodo creado a la lista

    insertarSU(nodoExamen,nodoSU);

}

void agregarRB(struct examen*nodoExamen)
{
    string des;
    int pts,opc,pre;
    //Creamos el nodo de seleccion
    cout<<L<<"Encabezado del ejercicio: ";
    fflush( stdin );
    getline(cin,des);
    cout<<L<<"Cantidad de ejercios en la seccion: ";
    fflush( stdin );
    cin>>pre;
    cout<<L<<"Cantidad de opciones de respuesta: ";
    fflush( stdin );
    cin>>opc;
    cout<<L<<"Cantidad de puntos por respuesta: ";
    fflush( stdin );
    cin>>pts;
    struct respBrebe*nodoRB=new respBrebe(des, pts);
    for(int i=0; i<pre; i++)
    {
        insertarPregRespBrebe(nodoRB,opc);
    }
    // Asignamos el nodo creado a la lista
    insertarRB(nodoExamen,nodoRB);
}

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
        fflush( stdin );
        getline(cin,eleccion);
        if(eleccion=="1")a="1E";
        else if(eleccion=="2")a="2E";
        else if(eleccion=="3")a="3E";
        else if(eleccion=="4")a="4E";
        else if(eleccion=="5")a="5E";
        else
        {
            system("cls");
            continue;
        }
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
        fflush( stdin );
        getline(cin,eleccion);
        if(eleccion=="1")b="1C";
        else if(eleccion=="2")b="2C";
        else if(eleccion=="3")b="3C";
        else if(eleccion=="4")b="4C";
        else if(eleccion=="5")b="1S";
        else if(eleccion=="5")b="2S";
        else
        {
            system("cls");
            continue;
        }
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
        fflush( stdin );
        getline(cin,eleccion);
        if(eleccion=="1")c="2016";
        else if(eleccion=="2")c="2017";
        else if(eleccion=="3")c="2018";
        else if(eleccion=="4")c="2019";
        else if(eleccion=="5")c="2020";
        else if(eleccion=="6")
        {
            cout<<"Digite: ";
            fflush( stdin );
            getline(cin,c);
        }
        else
        {
            system("cls");
            continue;
        }
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
        fflush( stdin );
        getline(cin,eleccion);
        if(eleccion=="1")mat="Estructuras de Datos.";
        else if(eleccion=="2")mat="Programación Orientada a Objetos.";
        else if(eleccion=="3")mat="Arquitectura de Computadores.";
        else if(eleccion=="4")
        {
            cout<<"Digite: ";
            fflush( stdin );
            getline(cin,mat);
        }
        else
        {
            system("cls");
            continue;
        }
        eleccion="continuar";
        system("cls");
    }
    eleccion="";
    while(eleccion!="continuar")// Asigna grupo.
    {
        cout<<"[1] Grupo 50.\n"
            <<"[2] Grupo 51.\n"
            <<"[3] Otro.\n\n-> ";
        fflush( stdin );
        getline(cin,eleccion);
        if(eleccion=="1")grup="Grupo 50.";
        else if(eleccion=="2")grup="Grupo 51.";
        else if(eleccion=="3")
        {
            cout<<"Digite: ";
            fflush( stdin );
            getline(cin,grup);
        }
        else
        {
            system("cls");
            continue;
        }
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
        fflush( stdin );
        getline(cin,eleccion);
        if(eleccion=="1")porc=0.05;
        else if(eleccion=="2")porc=0.1;
        else if(eleccion=="3")porc=0.15;
        else if(eleccion=="4")porc=0.2;
        else if(eleccion=="5")porc=0.25;
        else if(eleccion=="6")
        {
            cout<<"Digite [ 10% -> 0.1 && 15% -> 0.15 ] : -> ";
            cin>>porc;
        }
        else
        {
            system("cls");
            continue;
        }
        eleccion="continuar";
        system("cls");
    }

    // A crear el nodo.
    cod=a+b+c;
    cout<<"Fecha de aplicacion [DD/MM/AAAA]: -> ";
    fflush( stdin );
    getline(cin,fecha);
    struct examen*nExamen= new examen(cod,mat,grup,fecha,porc);
    if(P_Examen==NULL)
    {
        P_Examen=nExamen;
    }
    else
    {
        nExamen->sig=P_Examen;
        P_Examen->ant=nExamen;
        P_Examen=nExamen;
    }
    //Finalmente insertarmos las partes del examen
    eleccion="";
    while(eleccion!="continuar")// insertar parte
    {
        cout<<L<<"Insertando secciones"<<L;
        cout<<"[1] Selecion Unica\n"
            <<"[2] Respuesta Brebe\n";
        fflush( stdin );
        getline(cin,eleccion);
        if(eleccion=="1"){
                int cant;
                cout<<L<<"Cuantas partes de selecion unica desea agregar?";
                fflush( stdin );
                cin>>cant;
                for(int f=0;f<cant;f++){
                        cout<<L<<"<Insertando parte Selecion Unica No"<<f+1<<" >"<<L;
                        agregarSU(nExamen);
                }
        }
        else if(eleccion=="2"){
            int cant;
                cout<<L<<"Cuantas partes de respuestra brebe desea agregar?";
                fflush( stdin );
                cin>>cant;
                for(int f=0;f<cant;f++){
                        cout<<L<<"<Insertando parte Respuesta Brebe No"<<f+1<<" >"<<L;
                        agregarSU(nExamen);
                }
        }

        else
        {
            system("cls");
            continue;
        }
        cout<<L<<"Desea agregar mas secciones? (s/n)";
        fflush( stdin );
        getline(cin,eleccion);
        if(eleccion=="s")
            continue;
        else if(eleccion=="n")
            eleccion="continuar";
        system("cls");
    }

}


//************************************************************************************
//*                   Insersiones de datos predefinidos
//************************************************************************************
/*
void addUS(string des,int pts,int npreg,string preg[],int nResp,string resp[]) //string pre,string res,int op,string opc[]){
{

//Constructores:
                //pregunta(string p, string re)
                //respuesta(string r)
                //selecUnica(string des,int pts)


    struct selecUnica*nodoSU=new selecUnica(des, pts);
    for(int i; i<Npre; i++)
    {
        struct pregunta*nPregunta= new pregunta(preg,resp);
        nPregunta->opciones[0]=res;//Posicion 0 siempre es la correcta.
        if(P_Pregunta==NULL)P_Pregunta=nPregunta;
        else
        {
            nPregunta->sig=P_Pregunta;
            P_Pregunta=nPregunta;
        }
        //Agregamos las opciones
        for(int i=1; i<opci; i++)
        {
            cout<<L<<"Resp Incorrecta No "<<i<<" :";
            getline(cin,opc);
            nPregunta->opciones[i]=opc;
            cout<<"<Respuesta Asignada>"<<L;
        }

        //Agregamos la pregunta la selecciion unica
        if(tempSU->pregunta_prt==NULL)tempSU->pregunta_prt=nPregunta;
        else
        {
            nPregunta->sig=tempSU->pregunta_prt;
            tempSU->pregunta_prt=nPregunta;
        }
    }
    insertarSU(nodoExamen,nodoSU);
}

void addRB(string pre,int op,string opc[])
{
    struct pregunta*nPregunta= new pregunta(pre);
    if(P_Pregunta==NULL)P_Pregunta=nPregunta;
    else
    {
        nPregunta->sig=P_Pregunta;
        P_Pregunta=nPregunta;
    }
    for(int i=0; i<op; i++)
    {
        nPregunta->opciones[i]=opc[i];
    }
}

// Funcion para insertar examenes ejemplo.
void insertExam(string cod,string mat,string grup,string fecha,float porc)
{
    struct examen*nExamen= new examen(cod,mat,grup,fecha,porc);
    if(P_Examen==NULL)P_Examen=nExamen;
    else
    {
        nExamen->sig=P_Examen;
        P_Examen->ant=nExamen;
        P_Examen=nExamen;
    }
}
*/

//************************************************************************************
//*                                      Menu                                        *
//************************************************************************************

int main()
{
    setlocale(LC_ALL, "spanish"); // Asigna lenguaje español como predeterminado.
    insertarExamen();

    return 0;
}
