#ifndef NODE_H
#define NODE_H
#pragma once

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

class Node {
     std::string nom;
    int h;
    double dGau;
    double dDro;
    Node* gau;
    Node* dro;
	Node* mere;
public:
    Node() :nom (" "),h (0), dGau(0), dDro(0), gau(NULL),dro(NULL), mere(NULL) {}
    Node(const Node&);
    Node& operator=(const Node&);
    ~Node();
    void setNom( std::string Name) { nom = Name; };
    void setHau(int he) { h=he; };
    void setGau(Node* Left) { gau = Left; };
    void setDro(Node* Right) { dro = Right; };
	void setdGau(double dleft) { dGau = dleft; };
	void setdDro(double dright) { dDro = dright; };
	void setMere(Node* peremere) { mere = peremere; };
     std::string getNom() { return nom; };
    int getHau() { return h; };
    Node* getGau() { return gau; };
    Node* getDro() { return dro; };
	double getdGau() { return dGau; };
    double getdDro() { return dDro; };
    void getDro(Node* &droi) { droi=dro; };
    void getGau(Node* &gauch) { gauch=gau; };
	Node* getMere() { return mere; };
};

#endif
