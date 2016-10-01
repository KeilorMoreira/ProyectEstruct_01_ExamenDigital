#include <iostream>
#include <stdlib.h> // Permite trabajar el cls, pause y otros
#include <locale.h> // Permite utilizar acentos de un lenguaje especificado en Main()
#include <stdio.h> //  Permite utilizar metodo fflush( stdin ) para limpiar la entrada de teclado antes de los getline()
#include <string>
#include <sstream>  // Ayuda en las conversiones de int a string utilizando streaming.
#define L endl
#define opcResp 10 //Tamaño array de respuestas correctas de Respuesta Brebe e incorrectas de seleccion unica.



using namespace std;


//************************************************************************************
//*                       Estructuras abstractas: Listas de datos
//************************************************************************************

/*
TDA examen, lista doble, falta decidir forma de enlace
con partes(SelecUnica y RespBrebe que son sublistas)
*/
struct examen
{

    float nota;
    string codigo,materia,fecha;
    float porcentaje;
    int puntosTotales;
    int puntosObt;
    struct examen*sig,*ant;
    struct listaSU*listaSU_ptr;
    struct listaRB*listaRB_ptr;
    examen(string cod,string mater,string fech,float porc)
    {
        nota=0;
        puntosObt=0;
        puntosTotales=0;
        codigo=cod;
        materia=mater;
        porcentaje=porc;
        fecha=fech;
        sig=NULL;
        ant=NULL;
        listaSU_ptr=NULL;
        listaRB_ptr=NULL;
    }
}*P_Examen;


// Lista
struct selecUnica
{
    string instrucciones,codigo;
    int puntosSeccion;
    int puntosObt;
    int cantPreg;
    struct selecUnica*sig;
    struct preguntaSU *listaPreguntasSU;
    selecUnica(string inst,int ptSec,int cantP)
    {
        instrucciones=inst;
        puntosSeccion=ptSec;
        cantPreg=cantP;
        sig=NULL;
        listaPreguntasSU=NULL;
    }
}*P_SelecUnica;

//Lista
struct respBrebe
{
    string instrucciones,codigo;
    int puntosSeccion;
    int puntosObt;
    int cantPreg;
    struct respBrebe*sig;
    struct preguntaRB*listaPreguntasRB;
    respBrebe(string inst,int ptSec,int cantP)
    {
        instrucciones=inst;
        puntosSeccion=ptSec;
        cantPreg=cantP;
        sig=NULL;
        listaPreguntasRB=NULL;
    }
}*P_RespBrebe;


struct preguntaSU
{
    string codigo,materia,pregunta;
    bool correcto;
    string respuestas[opcResp];
    struct preguntaSU*sig,*ant;
    preguntaSU(string cod, string mate,string preg)
    {
        codigo=cod;
        materia=mate;
        pregunta=preg;
        ant=NULL;
        sig=NULL;
    }
}*P_PreguntaSU;

struct preguntaRB
{
    string codigo,materia,pregunta;
    struct preguntaRB*sig,*ant;
    struct respuestaRB*listaRespuestasRB;
    preguntaRB(string cod, string mate,string preg)
    {
        codigo=cod;
        materia=mate;
        pregunta=preg;
        ant=NULL;
        sig=NULL;
        listaRespuestasRB=NULL;
    }
}*P_PreguntaRB;

struct respuestasRB{
    string codigo; // codigo de la pregunta a la que pertenece.
    char respuesta[];
    string buffer; // es la variable en la cual se almacena la respuesta del usuario.
    int digitos;  // Corresponde al tamaño del atributo respuesta.
    int asiertos; // Corresponde a la cantidad de coincidencias entre elementos de buffer y respuesta.
    float porcAsiertos; // Es el valor de asiertos de forma porcentual, asiertos*100/digitos. escala 0/100.
    struct respuestasRB*sig;
    respuestasRB(string cod){
        codigo=cod;
        digitos= sizeof respuesta;
        asiertos=0;
        porcAsiertos=0;
        sig=NULL;
    }
}*P_RespuestasRB;

//************************************************************************************
//*                             Sublistas de enlace (punteros heterogenios)
//************************************************************************************

struct listaSU
{
    struct selecUnica*enlaceSU;
    struct listaSU*sig;
    listaSU()
    {
        enlaceSU=NULL;
        sig=NULL;
    }
};

struct listaRB
{
    struct respBrebe*enlaceRB;
    struct listaRB*sig;
    listaRB()
    {
        enlaceRB=NULL;
        sig=NULL;
    }
};

struct listaPreguntasSU
{
    struct preguntaSU*enlacePreguntaSU;
    struct listaPreguntasSU*sig;
    listaPreguntasSU(){
        enlacePreguntaSU=NULL;
        sig=NULL;
    }
};

struct listaPreguntasRB
{
    struct preguntaRB*enlacePreguntaRB;
    struct listaPreguntasRB*sig;
    listaPreguntasRB(){
        enlacePreguntaRB=NULL;
        sig=NULL;
    }
};

struct listaRespuestasRB
{
    struct respuestasRB*enlaceRespuestasRB;
    struct listaRespuestasRB*sig;
    listaRespuestasRB(){
        enlaceRespuestasRB=NULL;
        sig=NULL;
    }
};

//************************************************************************************
//*                        Buscadores de nodos de listas                             *
//************************************************************************************

struct examen*buscarExamen()
{

    return NULL;
};

struct selecUnica*buscarSU()
{

    return NULL;
};

struct respBrebe*buscarRB()
{

    return NULL;
};

struct preguntaSU*buscarPreguntaSU()
{

    return NULL;
};

struct preguntaRB*buscarPreguntaRB()
{

    return NULL;
};


//************************************************************************************
//*                            Validaciones varias                                   *
//************************************************************************************

// URL Fuente: http://diagramas-de-flujo.blogspot.com/2013/03/validar-fecha-ingresada-codigo-c.html
string validarFecha(){
    string fecha;
    int d,m,y, i;
    bool bisiesto = false;
    cout << "Introduce el dia: ";
    cin >> d;
    cout << "Introduce el mes: ";
    cin >> m;
    cout << "Introduce el anio: ";
    cin >> y;
    //comprobamos si el año es bisiesto
    if(y%4==0 && y%100!=100 || y%400==0)
        bisiesto = true;
    //comprobamos que los datos ingresados esten en un rango valido
    if(d>0 && d<32 && m>0 && m<13 && y>0)
    {
        if(m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12)
        {
            cout<<"";
        }
        else
        {
            if(m==2 && d<30 && bisiesto)
                cout<<"";
            else if(m==2 && d<29 && !bisiesto)
                cout<<"";
            else if(m!=2 && d<31)
                cout<<"";
            else
                return "no valida";
        }
    }
    else
        return "no valida";
    stringstream dia;
    stringstream mes;
    stringstream anio;
    dia<<d;
    mes<<m;
    anio<<y;

    fecha+= dia.str()+"/"+mes.str()+"/"+anio.str();
    return fecha;
}


//************************************************************************************
//*                        Insersiones datos a listas                           *
//************************************************************************************

void insertarExamen()
{

}

void insertarSU()
{
}

void insertarRB()
{
}

void insertarPreguntaSU()
{
}

void insertarPreguntaRB()
{
}


//************************************************************************************
//*                         Asignadores de punteros
//************************************************************************************




//************************************************************************************
//*                              Impresiones varias                                        *
//************************************************************************************



//************************************************************************************
//*                       Funciones de administracion de aplicacion                                        *
//************************************************************************************

//************************************************************************************
//*                        Funciones de Usuario estandard                            *
//************************************************************************************



int main()
{
    //setlocale(LC_ALL, "spanish"); // Asigna lenguaje español como predeterminado.





    return 0;
}
