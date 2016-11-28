#include <iostream>

using namespace std;




struct vertice{ // representan las ciudades o lugares en el mapa
    string lugar;
    int poblacion;
    int msnm; // metros sobre el nivel del mar
    // enlaces
    struct vertice* sigV;
    struct arco* sublistaArcos;
    vertice(string lug, int pob,int met){
        lugar= lug;
        poblacion = pob;
        msnm = met;
        sigV= NULL;
    }

}*grafo;

struct arco{// representa los caminos
    int distancia;
    string destino; // si fuera un multilista seria un puntero tipo vertice
    int velocidad;// km/h
    struct arco*sigA;
    arco(int d, string dest, int vel){
        distancia = d;
        destino = dest;
        velocidad =  vel;
        sigA = NULL;
    }

};// no posee primero, son sublistas

// incersion al inicio
void insertarV(string lug, int pob, int met){
    struct vertice *nnV = new vertice(lug,pob,met);

    nnV->sigV = grafo;// Incerta al inicio
    grafo = nnV;
}




struct vertice *buscarV(string);
// funcion para insertar un arco al inicio de la sublista
// de arcos del vertice origen
void insertarA(string origen, string dest, int dista, int velo){
    struct vertice *  Ori = buscarV(origen);
    struct vertice *  Des = buscarV(dest);
    if((Ori == NULL)or(Des== NULL)){
        cout<<"\nDatos incorrectos no se encuenta el origen o destino";
        return;
    }
    struct arco*nnA = new arco(dista, dest,velo);
    nnA->sigA = Ori->sublistaArcos;
    Ori->sublistaArcos = nnA;

}

struct vertice* buscarV(string ciudad){
    struct vertice * tempV = grafo;
    while(tempV!=NULL){
        if(tempV->lugar == ciudad)
            return tempV;
        tempV = tempV->sigV;
    }
    return NULL; // no lo encontro
};

void cargarDatos(){
    insertarV("CQ",20, 700);
    insertarV("Florencia",10, 300);
    insertarV("SntaClara",5, 150);
    insertarV("Tanque",5, 150);
    insertarV("Fortuna",5, 400);
    insertarV("Muelle",5, 800);
    insertarV("AguasZarcas",5, 250);
    //
    insertarA("CQ","Florencia",13,60);
    insertarA("CQ","AguasZarcas",17,60);
    insertarA("Florencia","SntaClara",5,60);
    insertarA("SntaClara","Tanque",12,60);
    insertarA("Tanque","Fortuna",18,60);
    insertarA("AguasZarcas","Muelle",20,60);
    insertarA("Muelle","Tanque",22,60);

}

// imprimir el grafo en amplitud: vertice sus arcos...

void amplitud(){
    struct vertice *tempV = grafo;
    struct arco *tempA;
    while(tempV != NULL){
        cout<<"\nVertice: "<<tempV->lugar<<" sus arcos son:";
        tempA = tempV->sublistaArcos;
        while(tempA!=NULL){
            cout<<tempV->lugar<<tempA->destino<<tempA->distancia<<", ";
            tempA = tempA->sigA;
        }
        tempV = tempV->sigV;
    }
}

int main()
{
    cargarDatos();
    amplitud();
    return 0;
}
