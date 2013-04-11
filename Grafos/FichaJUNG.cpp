#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>

void exercicio1();
void exercicio2();
void exercicio3();


void exercicio1()
{
    GraphViewer *gv = new GraphViewer(600, 600, true);

    gv->createWindow(600, 600);
    
    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");
 
    gv->addNode(0);
    gv->addNode(1);
    
    gv->addEdge(0, 0, 1, EdgeType::UNDIRECTED);
    gv->removeNode(1);
    gv->addNode(2);
    gv->addEdge(1, 0, 2, EdgeType::UNDIRECTED);
    gv->setVertexLabel(2, "cool vertex label");
    gv->setEdgeLabel(1, "cool edge label");
    gv->setVertexColor(2, "green");
    gv->setEdgeColor(1, "yellow");
    getchar();
    gv->closeWindow();
}

void exercicio2()
{
    GraphViewer *gv = new GraphViewer(600, 600, false);
    //gv->setBackground("background.jpg");
    gv->createWindow(600, 600);

    gv->addNode(0, 300, 50 );
    gv->addNode(1, 318, 58 );
    gv->addNode(2, 325, 75 );
    gv->addNode(3, 318, 93 );
    gv->addNode(4, 300, 100 );
    gv->addNode(5, 282, 93 );
    gv->addNode(6, 275, 75 );
    gv->addNode(7, 282, 58 );
    gv->addNode(8, 150, 200 );
    gv->addNode(9, 300, 200 );
    gv->addNode(10, 450, 200);
    gv->addNode(11, 300, 400);
    gv->addNode(12, 200, 550);
    gv->addNode(13, 400, 550);
    
    gv->addEdge(0, 0, 1, EdgeType::UNDIRECTED);
    gv->addEdge(1, 1, 2, EdgeType::UNDIRECTED);
    gv->addEdge(2, 2, 3, EdgeType::UNDIRECTED);
    gv->addEdge(3, 3, 4, EdgeType::UNDIRECTED);
    gv->addEdge(4, 4, 5, EdgeType::UNDIRECTED);
    gv->addEdge(5, 5, 6, EdgeType::UNDIRECTED);
    gv->addEdge(6, 6, 7, EdgeType::UNDIRECTED);
    gv->addEdge(7, 7, 0, EdgeType::UNDIRECTED);
    gv->addEdge(8, 4, 9, EdgeType::UNDIRECTED);
    gv->addEdge(9, 9, 8, EdgeType::UNDIRECTED);
    gv->addEdge(10, 9, 10, EdgeType::UNDIRECTED);
    gv->addEdge(11, 9, 11, EdgeType::UNDIRECTED);
    gv->addEdge(12, 11, 12, EdgeType::UNDIRECTED);
    gv->addEdge(13, 11, 13, EdgeType::UNDIRECTED);
    
    sleep(2);
    int counter = 1;
    while (counter < 10) {
        gv->removeNode(12);
        gv->removeNode(13);
        
        gv->addNode(14, 250, 550);
        gv->addNode(15, 350, 550);
        
        gv->addEdge(14, 11, 14, EdgeType::UNDIRECTED);
        gv->addEdge(15, 11, 15, EdgeType::UNDIRECTED);
        
        gv->rearrange();
        usleep(100000);
        
        gv->removeNode(14);
        gv->removeNode(15);
        
        gv->addNode(12, 200, 550);
        gv->addNode(13, 400, 550);
        gv->addEdge(14, 11, 12, EdgeType::UNDIRECTED);
        gv->addEdge(15, 11, 13, EdgeType::UNDIRECTED);
        gv->rearrange();
        usleep(100000);
    }

    gv->closeWindow();
}

void exercicio3()
{
    GraphViewer *gv = new GraphViewer(600, 600, false);
    //gv->setBackground("background.jpg");
    gv->createWindow(600, 600);
    
    ifstream nodes, edges;
    nodes.open ("nos.txt");
    edges.open("arestas.txt");
    string node;
    string edge;
    
    while (!nodes.eof() ) {
        getline(nodes, node);
        char * cstr = new char [node.length()+1];
        std::strcpy (cstr, node.c_str());
        int id, x, y;
        sscanf(cstr, "%d;%d;%d", &id, &x, &y);
        gv->addNode(id, x, y);
        delete cstr;
    }
    
    while (!edges.eof() ) {
        getline(edges, edge);
        char * cstr = new char [edge.length()+1];
        std::strcpy (cstr, edge.c_str());
        int id, to, from;
        sscanf(cstr, "%d;%d;%d", &id, &to, &from);
        gv->addEdge(id, to, from, EdgeType::UNDIRECTED);
        delete cstr;
    }

    nodes.close();
    edges.close();
    return;
}


int main() {
    cout << "close" << endl;
	//exercicio1();
	//exercicio2();
	exercicio3();
	getchar();
	return 0;
}
