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

struct selecUnica
{
    string instrucciones,codigo;
    int puntosSeccion;
    int puntosObt;
    int cantPreg;
    struct selecUnica*sig;
    struct preguntaSU *listaPreguntasSU;
    selecUnica(string cod,string inst,int ptSec,int cantP)
    {
        codigo=cod;
        instrucciones=inst;
        puntosSeccion=ptSec;
        cantPreg=cantP;
        sig=NULL;
        listaPreguntasSU=NULL;
    }
}*P_SelecUnica;

struct respBrebe
{
    string instrucciones,codigo;
    int puntosSeccion;
    int puntosObt;
    int cantPreg;
    struct respBrebe*sig;
    struct preguntaRB*listaPreguntasRB;
    respBrebe(string cod,string inst,int ptSec,int cantP)
    {
        codigo=cod;
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
    int puntosPre;
    bool correcto;
    string respuestas[opcResp];
    struct preguntaSU*sig,*ant;
    preguntaSU(string cod, string mate,string preg,int pts)
    {
        codigo=cod;
        materia=mate;
        pregunta=preg;
        puntosPre=pts;
        ant=NULL;
        sig=NULL;
    }
}*P_PreguntaSU;

struct preguntaRB
{
    string codigo,materia,pregunta;
    int puntosPre;
    struct preguntaRB*sig,*ant;
    struct respuestaRB*listaRespuestasRB;
    preguntaRB(string cod, string mate,string preg,int pts)
    {
        codigo=cod;
        materia=mate;
        pregunta=preg;
        puntosPre=pts;
        ant=NULL;
        sig=NULL;
        listaRespuestasRB=NULL;
    }
}*P_PreguntaRB;

struct respuestasRB
{
    string codigo; // codigo de la pregunta a la que pertenece.
    char respuesta[];
    string buffer; // es la variable en la cual se almacena la respuesta del usuario.
    int digitos;  // Corresponde al tamaño del atributo respuesta.
    int asiertos; // Corresponde a la cantidad de coincidencias entre elementos de buffer y respuesta.
    float porcAsiertos; // Es el valor de asiertos de forma porcentual, asiertos*100/digitos. escala 0/100.
    struct respuestasRB*sig;
    respuestasRB(string cod)
    {
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
    listaPreguntasSU()
    {
        enlacePreguntaSU=NULL;
        sig=NULL;
    }
};

struct listaPreguntasRB
{
    struct preguntaRB*enlacePreguntaRB;
    struct listaPreguntasRB*sig;
    listaPreguntasRB()
    {
        enlacePreguntaRB=NULL;
        sig=NULL;
    }
};

struct listaRespuestasRB
{
    struct respuestasRB*enlaceRespuestasRB;
    struct listaRespuestasRB*sig;
    listaRespuestasRB()
    {
        enlaceRespuestasRB=NULL;
        sig=NULL;
    }
};

//************************************************************************************
//*                        Buscadores de nodos de listas                             *
//************************************************************************************

struct examen*buscarExamen(string cod)
{
    struct examen*tempE=P_Examen;
    if(tempE==NULL)
        return NULL;
    do
    {
        if(tempE->codigo==cod)
            return tempE;
        tempE = tempE->sig;
    }
    while(tempE!=NULL);

    return NULL;
};

struct selecUnica*buscarSU(string cod)
{
    struct selecUnica*tempSU=P_SelecUnica;
    if(tempSU==NULL)
        return NULL;
    do
    {
        if(tempSU->codigo==cod)
            return tempSU;
        tempSU = tempSU->sig;
    }
    while( tempSU!=NULL);

    return NULL;
};

struct respBrebe*buscarRB(string cod)
{
    respBrebe*tempRB=P_RespBrebe;
    if(tempRB==NULL)
        return NULL;
    do
    {
        if(tempRB->codigo==cod)
            return tempRB;
        tempRB = tempRB->sig;
    }
    while(tempRB!=NULL);
    return NULL;
};

struct preguntaSU*buscarPreguntaSU(string cod)
{
    struct preguntaSU*tempPreSU=P_PreguntaSU;
    if(tempPreSU==NULL)
        return NULL;
    do
    {
        if(tempPreSU->codigo==cod)
            return tempPreSU;
        tempPreSU = tempPreSU->sig;
    }
    while( tempPreSU!=NULL);
    return NULL;
};

struct preguntaRB*buscarPreguntaRB(string cod)
{
    struct preguntaRB*tempPreRB=P_PreguntaRB;
    if(tempPreRB==NULL)
        return NULL;
    do
    {
        if(tempPreRB->codigo==cod)
            return tempPreRB;
        tempPreRB = tempPreRB->sig;
    }
    while(tempPreRB!=NULL);

    return NULL;
};


//************************************************************************************
//*                            Validaciones varias                                   *
//************************************************************************************

// URL Fuente: http://diagramas-de-flujo.blogspot.com/2013/03/validar-fecha-ingresada-codigo-c.html
string validarFecha()
{
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

void insertarExamen(string cod,string materia,string fecha,float porcentaje)
{
    // examen(string cod,string mater,string fech,float porc)
    struct examen*nExamen= new examen(cod,materia,fecha,porcentaje);
    if(P_Examen==NULL)P_Examen=nExamen;
    else
    {
        nExamen->sig=P_Examen;
        P_Examen->ant=nExamen;
        P_Examen=nExamen;
    }
}

void insertarSU(string cod,string inst,int ptSec,int cantPre)
{
    // selecUnica(string inst,int ptSec,int cantP)
    struct selecUnica*nnSU= new selecUnica(cod,inst,ptSec,cantPre);
    if(P_SelecUnica==NULL)P_SelecUnica=nnSU;
    else
    {
        nnSU->sig=P_SelecUnica;
        P_SelecUnica=nnSU;
    }
}

void insertarRB(string cod,string inst,int ptSec,int cantPre)
{
    // respBrebe(string cod,string inst,int ptSec,int cantP)
    struct respBrebe*nnRB= new respBrebe(cod,inst,ptSec,cantPre);
    if(P_RespBrebe==NULL)P_RespBrebe=nnRB;
    else
    {
        nnRB->sig=P_RespBrebe;
        P_RespBrebe=nnRB;
    }
}

void insertarPreguntaSU(string cod, string mate,string preg,int pts)
{
    //preguntaSU(string cod, string mate,string preg,int pts)
    struct preguntaSU*nnPreSU=new preguntaSU(cod,mate,preg,pts);
    if(P_PreguntaSU==NULL)//si la lista esta vacia
        P_PreguntaSU=nnPreSU;
    else
    {
        struct preguntaSU * actual=P_PreguntaSU;
        struct preguntaSU * ant=NULL;
        while((actual !=NULL)&&(pts < actual->puntosPre))
        {
            ant=actual;
            actual =actual->sig;
        }
        if(actual ==NULL)//se inserta al final de la lista
        {
            ant->sig=nnPreSU;
            nnPreSU->ant=ant;
        }
        else if(ant==NULL)//se inserta al inicio de la lista
        {
            nnPreSU->sig=P_PreguntaSU;
            P_PreguntaSU->ant=nnPreSU;
            P_PreguntaSU=nnPreSU;
        }
        else //insertar en medio
        {
            ant->sig=nnPreSU;
            actual->ant=nnPreSU;
            nnPreSU->sig=actual;
            nnPreSU->ant=ant;
        }
    }
}

void insertarPreguntaRB(string cod, string mate,string preg,int pts)
{
    //preguntaRB(string cod, string mate,string preg,int pts)
    struct preguntaRB*nnPreRB=new preguntaRB(cod,mate,preg,pts);
    if(P_PreguntaRB==NULL)//si la lista esta vacia
        P_PreguntaRB=nnPreRB;
    else
    {
        struct preguntaRB * actual=P_PreguntaRB;
        struct preguntaRB * ant=NULL;
        while((actual !=NULL)&&(pts < actual->puntosPre))
        {
            ant=actual;
            actual =actual->sig;
        }
        if(actual ==NULL)//se inserta al final de la lista
        {
            ant->sig=nnPreRB;
            nnPreRB->ant=ant;
        }
        else if(ant==NULL)//se inserta al inicio de la lista
        {
            nnPreRB->sig=P_PreguntaRB;
            P_PreguntaRB->ant=nnPreRB;
            P_PreguntaRB=nnPreRB;
        }
        else //insertar en medio
        {
            ant->sig=nnPreRB;
            actual->ant=nnPreRB;
            nnPreRB->sig=actual;
            nnPreRB->ant=ant;
        }
    }
}


//************************************************************************************
//*                         Asignadores de punteros
//************************************************************************************

void asignarSU(int codExamen,int codSU){


}



//************************************************************************************
//*                              Impresiones varias                                        *
//************************************************************************************



//************************************************************************************
//*                       Funciones de administracion de aplicacion                                        *
//************************************************************************************

void datosPredefinidos(){
    //Examenes
    insertarExamen("Mat1S2016","Matematica","25/09/2016",0.30);
    insertarExamen("Esp1S2016","Español","25/09/2016",0.30);
    insertarExamen("Cie1S2016","Ciencias","25/09/2016",0.30);
    insertarExamen("Est1S2016","Estudios Sociales","25/09/2016",0.30);
    //Partes
    insertarRB("RB-001","Responda lo que se le solicite de forma brebe y concisa. ",30,10);
    insertarRB("RB-002","Responda lo que se le solicite de forma brebe y concisa. ",20,10);
    insertarSU("RB-003","Responda lo que se le solicite de forma brebe y concisa. ",30,30);
    insertarSU("RB-004","Responda lo que se le solicite de forma brebe y concisa. ",30,15);
    //Preguntas SU
    insertarPreguntaSU("codigo","Matematica","Pregunta n1",1);
    insertarPreguntaSU("codigo","Matematica","Pregunta n2",3);
    insertarPreguntaSU("codigo","Español","Pregunta n1",2);
    insertarPreguntaSU("codigo","Español","Pregunta n2",5);
    insertarPreguntaSU("codigo","Español","Pregunta n3",4);
    insertarPreguntaSU("codigo","Estudios Sociales","Pregunta n1",3);
    insertarPreguntaSU("codigo","Estudios Sociales","Pregunta n2",2);
    insertarPreguntaSU("codigo","Ciencias","Pregunta n1",5);
    insertarPreguntaSU("codigo","Ciencias","Pregunta n2",4);
    //Preguntas RB
    insertarPreguntaRB("codigo","Matematica","Pregunta n1",1);
    insertarPreguntaRB("codigo","Matematica","Pregunta n2",3);
    insertarPreguntaRB("codigo","Español","Pregunta n3",2);
    insertarPreguntaRB("codigo","Ciencias","Pregunta n4",5);
    insertarPreguntaRB("codigo","Ciencias","Pregunta n5",4);

}

//************************************************************************************
//*                        Funciones de Usuario estandard                            *
//************************************************************************************



int main()
{
    setlocale(LC_ALL, "spanish"); // Asigna lenguaje español como predeterminado.
    //preguntaSU(string cod, string mate,string preg,int pts)
    datosPredefinidos();

    struct preguntaSU*temp=P_PreguntaSU;
    while(temp!=NULL)
    {
        cout<<L<<"Codigo: "<<temp->codigo;
        cout<<L<<"Materia: "<<temp->materia;
        cout<<L<<"Pregunta: "<<temp->pregunta;
        cout<<L<<"Puntos: "<<temp->puntosPre<<L;
        temp=temp->sig;
    }




    return 0;
}
