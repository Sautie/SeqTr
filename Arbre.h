#ifndef ARBRE_H
#define ARBRE_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <set>
#include <stack>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include "Node.h"

class Arbre {

public:
    Arbre();
    ~Arbre();
    Node* getRacine() { return racine; };
    void setRacine(Node* N) { racine = N; };
    void setlevel(Node *k, int le = -1);
	void setlevel2(Node *k, std::vector <int>& lev, int le = -1);
    bool vide() { return(racine==NULL);}
    void AffArbre(Node *N, int cont=1, int i=4);   //sortie ecran
    void AffArbre2(Node *N, int cont=1, int i=4); //sortie ecran
    void FArbre(Node *N, std::ofstream &fout, int cont=1, int i=4); // sortie fichier
    bool Feuille(Node* N);
    void postorder(Node *N);
    void preorder(Node *N);
    void postNode(Node* N, std::vector < std::string>& leafset, std::vector < std::string>& nintset, std::vector < std::string>& totset);
    void PrintPostNode(Node* ar);
    void PrintTree(std::ifstream& fileReads, std::ofstream& fout) ;
    void insertNode(std::string pre, Node* &N, std::string sepa);
	void nintNode(Node* N, std::vector < Node*>& leafset, std::vector < Node*>& intset, std::vector < Node*>& totset);
	void RFBipartitions(std::string newick, std::vector < std::vector <Node*> > &bipart);
	Arbre* NewickParser(std::string newick, int num=0);
	std::vector<std::vector<std::vector<std::string> > > Biparti(Arbre* ar1, Node* nor);
	int RFdistance(std::string newick1, std::string newick2);
	std::vector< Node*>  NJ( Node * &NI, std::vector< std::vector<double> > V, std::vector<std::string> names); //map<pair<string, string>, double>& gre,
	void NJ2(std::vector<Node *> vectNodes, Node* &N);
	void suppArbre(Node* N);
private:
	Node* racine;
    bool PValable(char open,char close);
    void leafNode(Node* N, std::vector < Node*>& leafset);
};

#endif
