#include <iostream>
#include <stdlib.h> // Permite trabajar el cls, pause y otros
#include <locale.h> // Permite utilizar acentos de un lenguaje especificado en Main()
#include <stdio.h> //  Permite utilizar metodo fflush( stdin ) para limpiar la entrada de teclado antes de los getline()
#include <string>
#include <cctype> // Permite utilizar toupper()
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
    struct listaSU*enlaceSU;
    struct listaRB*enlaceRB;
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
        enlaceSU=NULL;
        enlaceRB=NULL;
    }
}*P_Examen;

struct selecUnica
{
    string instrucciones,codigo;
    int puntosSeccion;
    int puntosObt;
    int cantPreg;
    struct selecUnica*sig;
    struct listaPreguntasSU *enlacePreSU;
    selecUnica(string cod,string inst,int ptSec,int cantP)
    {
        codigo=cod;
        instrucciones=inst;
        puntosSeccion=ptSec;
        cantPreg=cantP;
        sig=NULL;
        enlacePreSU=NULL;
    }
}*P_SelecUnica;

struct respBrebe
{
    string instrucciones,codigo;
    int puntosSeccion;
    int puntosObt;
    int cantPreg;
    struct respBrebe*sig;
    struct listaPreguntasRB*enlacePreRB;
    respBrebe(string cod,string inst,int ptSec,int cantP)
    {
        codigo=cod;
        instrucciones=inst;
        puntosSeccion=ptSec;
        cantPreg=cantP;
        sig=NULL;
        enlacePreRB=NULL;
    }
}*P_RespBrebe;


struct preguntaSU
{
    string codigo,materia,pregunta;
    int puntosPre,puntosObt;
    bool correcto;
    string respuestas[opcResp];
    struct preguntaSU*sig,*ant;
    preguntaSU(string cod, string mate,string preg,int pts)
    {
        codigo=cod;
        materia=mate;
        pregunta=preg;
        puntosPre=pts;
        puntosObt=0;
        ant=NULL;
        sig=NULL;
    }
}*P_PreguntaSU;

struct preguntaRB
{
    string codigo,materia,pregunta;
    int puntosPre,puntosObt;
    struct preguntaRB*sig,*ant;
    struct listaRespuestasRB*enlaceRespuestaRB;
    preguntaRB(string cod, string mate,string preg,int pts)
    {
        codigo=cod;
        materia=mate;
        pregunta=preg;
        puntosPre=pts;
        puntosObt=0;
        ant=NULL;
        sig=NULL;
        enlaceRespuestaRB=NULL;
    }
}*P_PreguntaRB;

struct respuestasRB
{
    string codigo; // codigo de la pregunta a la que pertenece.
    bool contestada;
    string respuesta;
    string buffer; // es la variable en la cual se almacena la respuesta del usuario.
    int digitos;  // Corresponde al tamaño del atributo respuesta.
    int asiertos; // Corresponde a la cantidad de coincidencias entre elementos de buffer y respuesta.
    float porcAsiertos; // Es el valor de asiertos de forma porcentual, asiertos*100/digitos. escala 0/100.
    struct respuestasRB*sig;
    respuestasRB(string cod,int digit,string resp)
    {
        codigo=cod;
        digitos= digit;
        respuesta=resp;
        asiertos=0;
        porcAsiertos=0;
        sig=NULL;
    }
    void validarRespuesta()
    {
        for(int i=0; i<digitos; i++)
        {
            if(toupper(respuesta[i])==toupper(buffer[i]))
                asiertos++;
        }
        porcAsiertos= asiertos*100/digitos;
        if((porcAsiertos>=80)&&(porcAsiertos!=0))
            contestada=true;
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

struct respuestasRB*buscarRespuestaRB(string cod)
{
    struct respuestasRB*tempResRB=P_RespuestasRB;
    if(tempResRB==NULL)
        return NULL;
    do
    {
        if(tempResRB->codigo==cod)
            return tempResRB;
        tempResRB = tempResRB->sig;
    }
    while(tempResRB!=NULL);

    return NULL;

};

//************************************************************************************
//*                            Validaciones varias                                   *
//************************************************************************************

// URL Fuente: http://diagramas-de-flujo.blogspot.com/2013/03/validar-fecha-ingresada-codigo-c.html
string validarFecha()
{
    string fecha;
    int d,m,y;
    bool bisiesto = false;
    cout << "Introduce el dia: ";
    cin >> d;
    cout << "Introduce el mes: ";
    cin >> m;
    cout << "Introduce el anio: ";
    cin >> y;
    //comprobamos si el año es bisiesto
    if(((y%4==0)&&(y%100!=100)) || (y%400==0))
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

void insertarRespuestasRB(string code,string respuesta)
{
    int digitos = sizeof respuesta;
    respuestasRB*tempRRB = new respuestasRB(code,digitos,respuesta);

    if(P_RespuestasRB==NULL)
    {
        P_RespuestasRB=tempRRB;
    }
    else
    {
        tempRRB->sig=P_RespuestasRB;
        P_RespuestasRB=tempRRB;
    }
}

//************************************************************************************
//*                         Asignadores de punteros
//************************************************************************************

void asignarSU(string codExamen,string codSU)
{
    struct examen*tempE=buscarExamen(codExamen);
    struct selecUnica*tempSU=buscarSU(codSU);
    if((tempE!=NULL)&&(tempSU!=NULL))
    {
        struct listaSU *nn= new listaSU();
        nn->enlaceSU=tempSU;//se enlaza con el curso a matricular
        nn->sig= tempE->enlaceSU;//se enlaza con la sublista ya existente del estudiante
        tempE->enlaceSU=nn;// el nn pasa a ser el primer nodo de la sublista matricula
    }
}

void asignarRB(string codExamen,string codRB)
{
    struct examen*tempE=buscarExamen(codExamen);
    struct respBrebe*tempRB=buscarRB(codRB);
    if((tempE!=NULL)&&(tempRB!=NULL))
    {
        struct listaRB *nn= new listaRB();
        nn->enlaceRB=tempRB;//se enlaza con el curso a matricular
        nn->sig= tempE->enlaceRB;//se enlaza con la sublista ya existente del estudiante
        tempE->enlaceRB=nn;// el nn pasa a ser el primer nodo de la sublista matricula
    }
}

void asignarPreguntaSU(string codSU,string codPreSU)
{
    struct selecUnica *tempSU= buscarSU(codSU);//ya visto en clase
    struct preguntaSU *tempPreSU =buscarPreguntaSU(codPreSU);//ya visto en clase

    if((tempSU!=NULL)&&(tempPreSU!=NULL))
    {
        struct listaPreguntasSU *nn= new listaPreguntasSU();
        nn->enlacePreguntaSU=tempPreSU;//se enlaza con el curso a matricular
        nn->sig= tempSU->enlacePreSU;//se enlaza con la sublista ya existente del estudiante
        tempSU->enlacePreSU=nn;// el nn pasa a ser el primer nodo de la sublista matricula
    }


}

void asignarPreguntaRB(string codRB,string codPreRB)
{
    struct respBrebe *tempRB= buscarRB(codRB);//ya visto en clase
    struct preguntaRB *tempPreRB =buscarPreguntaRB(codPreRB);//ya visto en clase

    if((tempRB!=NULL)&&(tempPreRB!=NULL))
    {
        struct listaPreguntasRB *nn= new listaPreguntasRB();
        nn->enlacePreguntaRB=tempPreRB;//se enlaza con el curso a matricular
        nn->sig= tempRB->enlacePreRB;//se enlaza con la sublista ya existente del estudiante
        tempRB->enlacePreRB=nn;// el nn pasa a ser el primer nodo de la sublista matricula
    }
}

void asignarRespuestaRB(string codPreRB)
{
    struct preguntaRB *tempPreRB= buscarPreguntaRB(codPreRB);//ya visto en clase
    struct respuestasRB *tempResp = P_RespuestasRB;//ya visto en clase
    while(tempResp!=NULL){
        if((tempPreRB!=NULL)&&(tempResp->codigo==codPreRB))
            {
                struct listaRespuestasRB *nn= new listaRespuestasRB();
                nn->enlaceRespuestasRB=tempResp;//se enlaza con el curso a matricular
                nn->sig= tempPreRB->enlaceRespuestaRB;//se enlaza con la sublista ya existente del estudiante
                tempPreRB->enlaceRespuestaRB=nn;// el nn pasa a ser el primer nodo de la sublista matricula
            }
            tempPreRB=tempPreRB->sig;
    }
}
//************************************************************************************
//*                              Impresiones varias                                        *
//************************************************************************************

//************************************************************************************
//*                              Pedir Datos                                         *
//************************************************************************************
void pedirExamen()
{
    string cod,mat,fec;
    float por;
    cout<<"Ingrese el codigo del examen"<<L;
    fflush( stdin );
    cin>>cod;
    cout<<"Ingrese la materia"<<L;
    fflush( stdin );
    cin>>mat;
    cout<<"Ingrese la fecha de ejecucion"<<L;
    fflush( stdin );
    cin>>fec;
    cout<<"Ingrese el valor porcentual del examen(0.2 = 20%)"<<L;
    fflush( stdin );
    cin>>por;
    insertarExamen(cod,mat,fec,por);
}

void pedirSeccionRC()
{
    string cod,enc;
    int punSec,cantPre;
    cout<<"Ingrese el codigo de la sección: "<<L;
    fflush( stdin );
    cin>>cod;
    cout<<"Ingrese en cabezado: "<<L;
    fflush( stdin );
    cin>>enc;
    cout<<"Ingrese cuantos puntos vale la sección: "<<L;
    fflush( stdin );
    cin>>punSec;
    cout<<"Cantidad preguntas de la seccion: "<<L;
    fflush( stdin );
    cin>>cantPre;
    //(string cod,string inst,int ptSec,int cantPre)
    insertarRB(cod,enc,punSec,cantPre);
}

void pedirSeccionSU()
{
    string cod,enc;
    int Cpun,Cpre;
    cout<<"Ingrese el codigo de la seccion: "<<L;
    fflush( stdin );
    cin>>cod;
    cout<<"Ingrese encabezado: "<<L;
    fflush( stdin );
    cin>>enc;
    cout<<"Ingrese el puntaje de esta sección: "<<L;
    fflush( stdin );
    cin>>Cpun;
    cout<<"Ingrese la cantidad de preguntas de la seccion: "<<L;
    fflush( stdin );
    cin>>Cpre;
    //(string cod,string inst,int ptSec,int cantPre)
    insertarSU(cod,enc,Cpun,Cpre);
}

void pedirSolucionRC()
{
    int opc;
    string cod,mat,resp;
    cout<<"Ingrese el codigo de la pregunta: "<<L;
    fflush( stdin );
    cin>>cod;
    cout<<"Cuantas opciones de respuesta: "<<L;
    fflush( stdin );
    cin>>opc;
    for(int i=0; i<opc; i++)
    {
        cout<<"Respuesta No "<<i+1<<" :";
        fflush( stdin );
        getline(cin,resp);
        insertarRespuestasRB(cod,resp);
    }
}

void pedirRespuestaCorta(string cod)
{
    string mat,enc;
    int pun;
    cout<<"Ingrese la materia"<<L;
    fflush( stdin );
    cin>>mat;
    cout<<"Ingrese en cabesado"<<L;
    fflush( stdin );
    cin>>enc;
    cout<<"Ingrese el puntaje de examen de esta pregunta"<<L;
    fflush( stdin );
    cin>>pun;
    insertarPreguntaRB(cod,mat,enc,pun);
}

void pedirSelecionUnica(string cod)
{
    string mat,enc;
    int pun;
    cout<<"Ingrese la materia"<<L;
    fflush( stdin );
    cin>>mat;
    cout<<"Ingrese en cabesado"<<L;
    fflush( stdin );
    cin>>enc;
    cout<<"Ingrese el puntaje de examen de esta precunta"<<L;
    fflush( stdin );
    cin>>pun;
    insertarPreguntaSU(cod,mat,enc,pun);
}

//************************************************************************************
//*                       Funciones de administracion de aplicacion                                        *
//************************************************************************************

void validarPuntosExamen(){

    struct examen*tempExamen = P_Examen; // Entramos a lista de Examenes
    while(tempExamen!=NULL){
        struct listaSU*tempSU=tempExamen->enlaceSU;// Entramos a lista Seleccion Unica
        while(tempSU!=NULL){
            tempExamen->puntosObt+=tempSU->enlaceSU->puntosSeccion;
            struct listaPreguntasSU* tempPreSU = tempSU->enlaceSU->enlacePreSU; // Entramos a la lista preguntas Seleccion Unica
            while(tempPreSU!=NULL){
            tempSU->enlaceSU->puntosSeccion+=tempPreSU->enlacePreguntaSU->puntosPre;
            tempPreSU=tempPreSU->sig;
            }
        tempSU=tempSU->sig;
        }
        //
        struct listaRB*tempRB=tempExamen->enlaceRB;// Entramos a lista Seleccion Unica
        while(tempRB!=NULL){
            tempExamen->puntosObt+=tempRB->enlaceRB->puntosSeccion;
            struct listaPreguntasRB* tempPreRB = tempRB->enlaceRB->enlacePreRB; // Entramos a la lista preguntas Seleccion Unica
            while(tempPreRB!=NULL){
            tempRB->enlaceRB->puntosSeccion+=tempPreRB->enlacePreguntaRB->puntosPre;
            tempPreRB=tempPreRB->sig;
            }
        tempRB=tempRB->sig;
        }
        tempExamen->sig=tempExamen;
    }
}

void datosPredefinidos()
{
    //Examenes
    insertarExamen("Mat1S2016","Matematica","25/09/2016",0.30);
    insertarExamen("Esp1S2016","Español","25/09/2016",0.30);
    insertarExamen("Cie1S2016","Ciencias","25/09/2016",0.30);
    insertarExamen("Est1S2016","Estudios Sociales","25/09/2016",0.30);
    //Partes
    insertarRB("RB-001","Responda lo que se le solicite de forma brebe y concisa. ",30,10);
    insertarRB("RB-002","Responda lo que se le solicite de forma brebe y concisa. ",20,10);
    insertarSU("SU-001","Responda lo que se le solicite de forma brebe y concisa. ",30,30);
    insertarSU("SU-002","Responda lo que se le solicite de forma brebe y concisa. ",30,15);
    asignarRB("Mat1S2016","RB-001");
    asignarRB("Esp1S2016","RB-002");
    asignarSU("Mat1S2016","SU-001");
    asignarSU("Esp1S2016","SU-002");
    //Preguntas SU
    insertarPreguntaSU("preSU001","Matematica","Pregunta n1",1);
    insertarPreguntaSU("preSU002","Matematica","Pregunta n2",3);
    insertarPreguntaSU("preSU003","Español","Pregunta n1",2);
    insertarPreguntaSU("preSU004","Español","Pregunta n2",5);
    insertarPreguntaSU("preSU005","Español","Pregunta n3",4);
    insertarPreguntaSU("preSU006","Estudios Sociales","Pregunta n1",3);
    insertarPreguntaSU("preSU007","Estudios Sociales","Pregunta n2",2);
    insertarPreguntaSU("preSU008","Ciencias","Pregunta n1",5);
    insertarPreguntaSU("preSU009","Ciencias","Pregunta n2",4);
    asignarPreguntaSU("SU-001","preSU001");
    asignarPreguntaSU("SU-001","preSU002");
    asignarPreguntaSU("SU-001","preSU001");
    asignarPreguntaSU("SU-002","preSU003");
    asignarPreguntaSU("SU-002","preSU004");
    asignarPreguntaSU("SU-002","preSU005");
    asignarPreguntaSU("SU-002","preSU006");
    //Preguntas RB
    insertarPreguntaRB("preRB001","Matematica","Pregunta n1",1);
    insertarPreguntaRB("preRB002","Matematica","Pregunta n2",3);
    insertarPreguntaRB("preRB003","Español","Pregunta n3",2);
    insertarPreguntaRB("preRB004","Ciencias","Pregunta n4",5);
    insertarPreguntaRB("preRB005","Ciencias","Pregunta n5",4);
    asignarPreguntaSU("RB-001","preRB001");
    asignarPreguntaSU("RB-001","preRB002");
    asignarPreguntaSU("RB-001","preRB001");
    asignarPreguntaSU("RB-002","preRB003");
    asignarPreguntaSU("RB-002","preRB004");
    asignarPreguntaSU("RB-002","preRB005");
    asignarPreguntaSU("RB-002","preRB006");
    //


}

void crearParteSU(struct examen*temp)
{
    int cant,ptr;
    struct selecUnica*tem=P_SelecUnica;
    struct preguntaSU*tempo;
    string eleccion = "", sN,respu;
    cout<<L<<"Cuantas partes de selecion unica desea agregar?";
    fflush( stdin );
    cin>>cant;
    for(int f=0; f<cant; f++)
    {
        cout<<L<<"<Insertando parte Selecion Unica No"<<f+1<<" >"<<L;
        pedirSeccionSU();
        asignarSU(temp->codigo,P_SelecUnica->codigo);
        for(int i=0; i<P_SelecUnica->cantPreg; i++)
        {
            cout<<"Ingrese el codigo de la pregunta"<<L;
            fflush( stdin );
            cin>>sN;
            pedirSelecionUnica(sN);
            asignarPreguntaSU(P_SelecUnica->codigo,sN);
            cout<<"Ingrese el numero de repuestas para esta pregunta"<<L;
            fflush( stdin );
            cin>>ptr;
            tempo=buscarPreguntaSU(sN);
            cout<<"(Primero debe ir la obcion correcta)"<<L;
            for(int i=0; i<ptr; i++)
            {
                cout<<"Ingrese la respuesta"<<L;
                fflush( stdin );
                cin>>respu;
                tempo->respuestas[i]=respu;
            }
        }
    }
}

void crearParteRC(struct examen*temp)
{
    int cant,ptr;
    struct selecUnica*tem=P_SelecUnica;
    struct respBrebe*tempor=P_RespBrebe;
    struct preguntaSU*tempo;
    struct preguntaRB*tempo2;
    string eleccion = "", sN,respu;
    cout<<L<<"Cuantas partes de respuestra corta desea agregar?";
    fflush( stdin );
    cin>>cant;
    for(int f=0; f<cant; f++)
    {
        cout<<L<<"<Insertando parte Respuesta corta No"<<f+1<<" >"<<L;
        pedirSeccionRC();
        asignarRB(temp->codigo,P_RespBrebe->codigo);
        for(int i=0; i<P_RespBrebe->cantPreg; i++)
        {
            cout<<"Ingrese el codigo de la pregunta"<<L;
            fflush( stdin );
            cin>>sN;
            pedirSelecionUnica(sN);
            asignarPreguntaSU(P_RespBrebe->codigo,sN);
            cout<<"Ingrese el numero de repuestas para esta pregunta"<<L;
            fflush( stdin );
            cin>>ptr;
            tempo2=buscarPreguntaRB(sN);
            for(int i=0; i<ptr; i++)
            {
                pedirSolucionRC();
            }
            asignarRespuestaRB(sN);
        }
    }
}

void crearExamen()
{
    cout<<L;
    pedirExamen();
    int cant,ptr;
    struct selecUnica*tem=P_SelecUnica;
    struct respBrebe*tempor=P_RespBrebe;
    struct preguntaSU*tempo;
    struct preguntaRB*tempo2;
    string eleccion = "", sN,respu;
    cout<<L<<"Insertando secciones\n[1] Selecion Unica\n[2] Respuesta Brebe\n";
    fflush( stdin );
    getline(cin,eleccion);
    if(eleccion=="1")
    {
        crearParteSU(P_Examen);
    }
    else if(eleccion=="2")
    {
        crearParteRC(P_Examen);
    }
}

void modifiCarExamen(string code)
{
    struct examen*tem2 = P_Examen;

    while(tem2->sig!=NULL)
    {
        cout<<"   Codigo: "<<tem2->codigo<<"   Materia: "<<tem2->materia<<"   Fecha: "<<tem2->fecha<<"   Porcentaje: "<<tem2->porcentaje;
        tem2=tem2->sig;
    }
    string x,f,c;
    float p;
    buscarExamen(code);
    if(buscarExamen(code)!=NULL)
    {
        cout<<"1.Fecha de ejecusion\n2.Porcentaje\n3.Codigo de examen\n4.";
        fflush( stdin );
        cin>>x;
        if(x=="1")
        {
            cout<<"Ingrese la nueva Fecha: ";
            fflush( stdin );
            cin>>f;
            buscarExamen(code)->fecha=f;
        }
        if(x=="2")
        {
            cout<<"Ingrese el nuevo Porcetaje: ";
            fflush( stdin );
            cin>>p;
            buscarExamen(code)->porcentaje=p;
        }
        if(x=="3")
        {
            cout<<"Ingrese el nuevo Codigo: ";
            fflush( stdin );
            cin>>c;
            buscarExamen(code)->codigo=c;
        }
    }
}
//************************************************************************************
//*                        Funciones de Usuario estandard                            *
//************************************************************************************

void resolverExamen(string cod){



}


int main()
{
    setlocale(LC_ALL, "spanish"); // Asigna lenguaje español como predeterminado.
    //preguntaSU(string cod, string mate,string preg,int pts)
    datosPredefinidos();
    /*
    struct preguntaSU*temp=P_PreguntaSU;
    while(temp!=NULL)
    {
        cout<<L<<"Codigo: "<<temp->codigo;
        cout<<L<<"Materia: "<<temp->materia;
        cout<<L<<"Pregunta: "<<temp->pregunta;
        cout<<L<<"Puntos: "<<temp->puntosPre<<L;
        temp=temp->sig;
    }
    */
    string resp="respuesta";
    int digi = sizeof resp;
    struct respuestasRB*tempR = new respuestasRB("codigo",digi,resp);
    tempR->buffer="RESSTA";
    tempR->validarRespuesta();
    cout<<L<<"Nota Asierto: "<<tempR->porcAsiertos;
    cout<<L<<"Contestada: "<<tempR->contestada;
    crearExamen();
    return 0;
}
