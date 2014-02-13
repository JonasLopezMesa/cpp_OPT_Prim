//
//  grafo.cpp
//  Práctica_Grafos
//
//  Created by Jonás López Mesa on 27/03/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "grafo.h"


//////////////////////////////////////////////CONSTRUCTOR
GRAFO::GRAFO(char nombrefichero[]){ 
    unsigned int i, j, k, p;              //variables de recorrido yde almacenaje de información
	ElementoLista dummy;                    //variable tipo ElementoLista que va a almacenar las variables j y c
	ifstream tex;                           //variable tipo ifstream que es la que irá recogiendo los datos del fichero
    cout << nombrefichero << endl;
	tex.open(nombrefichero);                //Se abre el fichero en la variable text
	if (tex.is_open())                      //Si el fichero se abrió correctamente entonces:
	{
		LS.clear();                         //vacía la lista de adyacencia de los predecesores
		tex >> n >> m >> dirigido;          //saca los tres primeros valores de tex: el número de nodos, el número de arístas y si el grafo 
        cout << m;
                                            //es dirigido o no
		LS.resize(n);                       //Redimensiona el vector LS(lista de sucesores) para que tenga tamaño n(números de nodos)
		for (k=0;k<m;k++)                   //por cada una de las aristas hacer:
		{
			tex >> i >> j >> p;             //recoge el nodo y a donde se dirije su arista
			dummy.c=p;                      //asigna el valor del coste a dummy.c
			dummy.j=j-1;                    //asigna el valor de a que nodo se dirije la arista a dummy.j
			LS[i - 1].push_back(dummy);     // introduce el la lista de adyacencia el valor de dummy, tanto la c como la j.
			if ( dirigido == 0 )            //si el grafo no es dirigido, entonces:
			{
				dummy.j=i-1;                //a continuación de la anterior j, asigna una arista en sentido contrario.
                                            //nodo de origen
				dummy.c=p;                //añade el coste de esa arista
				LS[j-1].push_back(dummy);   //introduce dummy en el vector de adyacencia
			}
		}
	}
	tex.close();                            //cierra el archivo
}

/////////////////////////////////////////////DESTRUCTOR
GRAFO::~GRAFO(){ 
    LS.clear(); //vacía la lista de adyacencia de los sucesores
}

void GRAFO::MostrarGrafo(){
    cout << "Atriburos del Grafo" << endl; 
    cout << n << " " << m << " " << dirigido << endl;
    cout << "Lista de Sucesores" << endl;
    for (int k=0; k < LS.size(); k++) {
        for (int w=0; w < LS[k].size(); w++) {
            cout << k+1 << "--->" << LS[k][w].j+1 << " [ " << LS[k][w].c << " ]" << endl;
        }
    }

}

void GRAFO::Prim() {
    vector<bool> M;
    vector<int> costedeconexion;
    vector<unsigned> pred;
    unsigned inicio, candidato;
    
    M.resize(n, false);
    costedeconexion.resize(n, maxint);
    pred.resize(n, UERROR);

    cout << "Introduce el nodo de inicio: " << endl;
    cin >> inicio;
    costedeconexion[inicio-1] = 0;
    pred[inicio-1] = inicio-1;
    
    do {
        int min = maxint;
        candidato = UERROR;
        for (unsigned i = 0; i < LS.size(); i++) {
            if (M[i] == false) {
                if (costedeconexion[i] != maxint) {
                    if (costedeconexion[i] < min) {
                        //costedeconexion[i] = min;
                        candidato = i;
                        min = costedeconexion[i];
                    }
                }
            }
        }
        if (candidato != UERROR) {
            int no = 1;
            M[candidato] = true;
            //cout << LS[candidato].size() << endl;
            if (LS[candidato].size() != 0) {
                
                for (int j = 0; j < LS[candidato].size(); j++) {
                    no = 1;
                    if ((costedeconexion[LS[candidato][j].j] > LS[candidato][j].c)) {
                        //if (LS[candidato][j].j != pred[j] && LS[candidato][j].j != candidato) {
                            for (int i = 0; i < n; i++) {
                                cout << "i " << i << " | LS[candidato][j].j " << LS[candidato][j].j <<  " | pred[i] " << pred[i] << " | candidato " << candidato << " | coste " << costedeconexion[i] <<endl;
                                if (i == candidato && pred[i] == LS[candidato][j].j) {
                                    no = 0;
                                }
                            }
                            if (no == 1) {
                                costedeconexion[LS[candidato][j].j] = LS[candidato][j].c;
                                pred[LS[candidato][j].j] = candidato;
                                cout << "Insertando arista {" << candidato << ", " << LS[candidato][j].j << "} en el arbol." << endl;
                            }
                        //}
                    }
                }
            }
            
        }
        
    } while (candidato != UERROR);
    cout << "------------------------------------------------------" << endl;
    unsigned s = 0;
    for (int j = 0; j < n; j++) {
        if (costedeconexion[j] == maxint) {
            s = 1;
        }
    }
    if (s == 0) {
        int m = 0;
        for (int r = 0; r < n; r++) {
            m = m + costedeconexion[r];
        }
        cout << "              ÁRBOL ÓPTIMO DE PESO: " << m << endl;
        for (int i = 0; i < n; i++) {
            if (pred[i] == i && costedeconexion[i] == 0) {
                
            } else {
                cout << pred[i]+1 << "--->" << i+1 << " [ " << costedeconexion[i] << " ] " << endl;
            }
        }
    } else {
        cout << "No existe el árbol generador de mínimo coste" << endl;
    }
    cout << "------------------------------------------------------" << endl;
    cout << "    ----------------------------------------------    " << endl;
    cout << "------------------------------------------------------" << endl;
}

















