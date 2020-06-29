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
//#include "ArbreN.h"

using namespace std;

//Miguel Sautie
/*** parser newick format, la determination de bipartitions et distRF***/
/*** 4 fonctions globales et 2 classes (class Arbre (32 fonctions membres) et class Node (18 fonctions membres))  ***/
// coordonees des fonctions les plus importantes: newickparser: ligne 575, insertNode: 316 biparti, RFdistance: 509 , NJ: 688

int BLOSUM62[][25] = {
{4,-1,-2,-2,0,-1,-1, 0,-2,-1,-1,-1,-1,-2,-1, 1, 0, -3, -2, 0, -2, -1, 0, -4},
{-1, 5, 0, -2, -3, 1, 0, -2, 0, -3, -2, 2, -1, -3, -2, -1, -1, -3, -2, -3, -1, 0, -1, -4},
{-2, 0, 6, 1, -3, 0, 0, 0, 1, -3, -3, 0, -2, -3, -2, 1, 0, -4, -2, -3, 3, 0, -1, -4 },
{-2, -2, 1, 6, -3, 0, 2, -1, -1, -3, -4, -1, -3, -3, -1, 0, -1, -4, -3, -3, 4, 1, -1, -4 },
{0, -3, -3, -3, 9, -3, -4, -3, -3, -1, -1, -3, -1,-2,-3,-1,-1, -2, -2, -1, -3, -3, -2, -4} ,
{-1, 1, 0, 0, -3, 5, 2, -2, 0, -3, -2, 1, 0, -3, -1, 0, -1, -2, -1, -2, 0, 3, -1, -4},
{-1, 0, 0, 2, -4, 2, 5, -2, 0, -3, -3, 1, -2, -3, -1, 0, -1, -3, -2, -2, 1, 4, -1, -4},
{ 0,-2, 0, -1, -3, -2, -2,  6, -2, -4, -4, -2, -3, -3, -2,  0, -2, -2, -3, -3, -1, -2, -1, -4},
{-2, 0, 1, -1, -3, 0, 0, -2, 8, -3, -3, -1, -2, -1, -2, -1, -2, -2, 2, -3, 0, 0, -1, -4},
{-1, -3, -3, -3, -1, -3, -3, -4, -3, 4, 2, -3, 1, 0, -3, -2, -1, -3, -1, 3, -3, -3, -1, -4},
{-1, -2, -3, -4, -1, -2, -3, -4, -3, 2, 4, -2, 2, 0, -3, -2, -1, -2, -1, 1, -4, -3, -1, -4},
{-1, 2, 0, -1, -3, 1, 1, -2, -1, -3, -2, 5, -1, -3, -1, 0, -1, -3, -2, -2, 0, 1, -1, -4},
{-1, -1, -2, -3, -1,  0, -2, -3, -2,  1,  2, -1,  5,  0, -2, -1, -1, -1, -1,  1, -3, -1, -1, -4},
{-2,-3,-3,-3,-2,-3,-3,-3,-1, 0, 0, -3, 0, 6, -4, -2, -2, 1, 3, -1, -3, -3, -1, -4},
{-1, -2, -2, -1, -3, -1, -1, -2, -2, -3, -3, -1, -2, -4, 7, -1, -1, -4, -3, -2, -2, -1, -2, -4},
{1, -1, 1, 0, -1, 0, 0, 0, -1, -2, -2, 0, -1, -2, -1, 4, 1, -3, -2, -2, 0, 0, 0, -4},
{0, -1, 0, -1, -1, -1, -1, -2, -2, -1, -1, -1, -1, -2, -1, 1, 5, -2, -2, 0, -1, -1, 0, -4},
{-3, -3, -4, -4, -2, -2, -3, -2, -2, -3, -2, -3, -1, 1, -4, -3, -2, 11, 2, -3, -4, -3, -2, -4},
{-2, -2, -2, -3, -2, -1, -2, -3,  2, -1, -1, -2, -1,  3, -3, -2, -2,  2,  7, -1, -3, -2, -1, -4},
{0,-3,-3,-3,-1,-2,-2,-3,-3 ,3, 1, -2, 1, -1, -2, -2, 0, -3, -1 , 4, -3, -2, -1, -4},
{-2,-1 ,3 , 4, -3, 0, 1, -1, 0, -3, -4, 0, -3, -3, -2, 0, -1, -4, -3, -3, 4, 1, -1,-4},
{-1, 0, 0, 1, -3, 3, 4, -2, 0, -3, -3, 1, -1, -3, -1,  0, -1, -3, -2, -2, 1, 4, -1, -4},
{ 0,-1,-1,-1, -2, -1,-1,-1,-1, -1, -1, -1,-1,-1,-2, 0, 0, -2,-1, -1,-1, -1,-1,-4},
{-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4, -4, -4, -4,-4,-4,-4,-4,-4, -4, 1},
};
char aa[] = {'A','R','N','D','C','Q','E','G','H','I','L','K','M','F','P','S','T','W','Y','V','B','Z','X','*'};

int getScore(int matr[][25], char alph[], char cc, char LL)
{
   int ci=-1, cL=-1, i=0;
   while ((i < 24)&&((ci==-1)||(cL==-1))){
	if (cc==*(alph + i))
	    ci=i;
	if (LL==*(alph + i))
	    cL=i;
		i++;
	        }
 	if (i==24) { if (ci==-1) ci=--i; if (cL==-1) cL=--i; }
	return matr[ci][cL];
	 }

void InputOut(vector<string>  &names, vector<string> &sequences, string sttr="proteines.fa", string outFile="Outalignment.txt") {
 string seq, str;
 ifstream fileReads(sttr.c_str());
 int c=0, p1,p2=0;
  if (fileReads.is_open()) {
    while (getline (fileReads, str) )
    {
       int p1=str.find(">");
       if (p1!=std::string::npos) {
          names.push_back(str.substr(p1+1, str.length()-1));
          if (p2==1)  sequences.push_back(seq);
          c=0;
		  p2=1;}
       else {
          if (c==0) {
		    seq=str;
		    c=1; }
          else
             seq=seq+str;
	        }
			}
	sequences.push_back(seq);
   // fileReads.close();
   }
	ofstream fout(outFile.c_str());
	int Ls=sequences.size();
	 for( int j = 0; j < Ls; j+=1 )
               {
           fout<<names[j]<<"\t"<<sequences[j]<<endl;
         }
 }
vector< vector<double> > MDistance(vector<string> sequences)
    {
      vector< vector<double> > D;
       string seq, seqB, seqA;
       vector<int> pos;
       vector<double> Daux;
       double Ds;
       int Ls=sequences.size(), sr, p, q, y, psr, qsr, ysr, mx=0;
       int Les=sequences[0].length();
	   for (int i=0;i<Les; i++) {
        for (int j=0; j<Ls; j++) {
        seq=sequences[j];
         if (seq[i]=='-') break;
          }
         if (seq[i]!='-') pos.push_back(i);
         }

       for (int t=0; t<Ls; t++) {
	         seqA=sequences[t];
	        vector<double> Daux;
         for (int tt=0; tt<Ls; tt++) {
            seqB=sequences[tt];
            p=0;q=0;y=0;Ds=0;
        	for (int j=0; j<pos.size(); j++) {
              psr=getScore(BLOSUM62,aa, seqA[pos[j]], seqB[pos[j]]);
              p=p+psr;
              qsr=getScore(BLOSUM62,aa, seqA[pos[j]], seqA[pos[j]]);
              q=q+qsr;
              ysr=getScore(BLOSUM62,aa, seqB[pos[j]], seqB[pos[j]]);
              y=y+ysr;
			  }
	      if (q>y) mx=q;
			else mx=y;
		  Ds=1-((double)p/(double)mx);
          Daux.push_back(Ds);
                  }
         D.push_back(Daux);
         Daux.clear();
                    }
        return D;
                    }

  void printMatrix(vector<string>  names, vector< vector<double> > Dist, string outFile="MD.txt")
     {
	ofstream fout(outFile.c_str());
	int Ls=names.size();
	fout<<"              ";
	for( int j = 0; j < Ls; j+=1 ) fout<<names[j]<<"\t";
	fout<<endl;
	for( int j = 0; j < Ls; j+=1 )  {
		fout<<names[j]<<"\t";
	 for( int i = 0; i < Ls; i+=1 )
               {
           fout<< scientific <<Dist[j][i]<<"   ";
              }
		   fout<<endl;
		   }
         }


class Node {
    string nom;
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
    void setNom(string Name) { nom = Name; };
    void setHau(int he) { h=he; };
    void setGau(Node* Left) { gau = Left; };
    void setDro(Node* Right) { dro = Right; };
	void setdGau(double dleft) { dGau = dleft; };
	void setdDro(double dright) { dDro = dright; };
	void setMere(Node* peremere) { mere = peremere; };
    string getNom() { return nom; };
    int getHau() { return h; };
    Node* getGau() { return gau; };
    Node* getDro() { return dro; };
	double getdGau() { return dGau; };
    double getdDro() { return dDro; };
    void getDro(Node* &droi) { droi=dro; };
    void getGau(Node* &gauch) { gauch=gau; };
	Node* getMere() { return mere; };
};

Node::Node(const Node& aut):gau(NULL),dro(NULL), mere(NULL), nom(aut.nom), h(aut.h), dGau(aut.dGau), dDro(aut.dDro)
{
    if (aut.gau != NULL ) { gau = new Node(*aut.gau);}
    if (aut.dro != NULL) { dro = new Node(*aut.dro);}
    if (aut.mere != NULL) { mere = new Node(*aut.mere);}
}
Node& Node::operator=(const Node& aut)
{
   nom= aut.nom;
   h=aut.h;
   dGau=aut.dGau;
   dDro=aut.dDro;
   Node * left= gau;
   gau= new Node(*aut.gau);
   delete left;

    Node * right = dro;
    dro = new Node(*aut.dro);
    delete right;

    Node * mother = mere;
    mere= new Node(*aut.mere);
    delete mother;

    return *this;
}

Node::~Node()
{
    if (gau!= NULL)  delete gau;
    if (dro!= NULL)  delete dro;
    if (mere!= NULL)  delete mere;

}

class Arbre {

public:
    Arbre();
    ~Arbre();
    Node* getRacine() { return racine; };
    void setRacine(Node* N) { racine = N; };
    void setlevel(Node *k, int le = -1);
	void setlevel2(Node *k, vector <int>& lev, int le = -1);
    bool vide() { return(racine==NULL);}
    void AffArbre(Node *N, int cont=1, int i=4);   //sortie ecran
    void AffArbre2(Node *N, int cont=1, int i=4); //sortie ecran
    void FArbre(Node *N, ofstream &fout, int cont=1, int i=4); // sortie fichier
    bool Feuille(Node* N);
    void postorder(Node *N);
    void preorder(Node *N);
    void postNode(Node* N, vector < string>& leafset, vector < string>& nintset, vector < string>& totset);
    void PrintPostNode(Node* ar);
    void PrintTree(ifstream& fileReads, ofstream& fout) ;
    void insertNode(string pre, Node* &N, string sepa);
	void nintNode(Node* N, vector < Node*>& leafset, vector < Node*>& intset, vector < Node*>& totset);
	void RFBipartitions(string newick, vector < vector <Node*> > &bipart);
	Arbre* NewickParser(string newick, int num=0);
	vector<vector<vector<string> > > Biparti(Arbre* ar1, Node* nor);
	int RFdistance(string newick1, string newick2);
	vector< Node*>  NJ( Node * &NI, vector< vector<double> > V, vector<string> names); //map<pair<string, string>, double>& gre,
	void NJ2(vector<Node *> vectNodes, Node* &N);
	void suppArbre(Node* N);
private:
	Node* racine;
    bool PValable(char open,char close);
    void leafNode(Node* N, vector < Node*>& leafset);
};

Arbre::Arbre() {
    racine = NULL;
}
Arbre::~Arbre() {
    suppArbre(racine);}

void Arbre::suppArbre(Node *N)
{
    if(N==NULL) return;
    if(N->getGau()!= NULL) suppArbre(N->getGau());
    if(N->getDro()!= NULL) suppArbre(N->getDro());
    delete N;
    return;
}
void Arbre::AffArbre(Node *N, int cont, int i)  {
    	if (N==NULL)  {
    	   return;
    	     }
    	 else  {
    	 	AffArbre(N->getDro(),cont+i);
    	 	if (cont> 0)
            cout << setw(cont) << " ";
    	 	cout<<N->getNom()<<endl;
    	    AffArbre(N->getGau(),cont+i);
    	 	}
        }

  void Arbre::AffArbre2(Node *N, int cont, int i)
{
    if(N != NULL) {
        if(N->getDro()) {
            AffArbre2(N->getDro(), cont+i);
        }
        if (cont) {
            cout << setw(cont) << ' ';
        }
        if (N->getDro()) cout<<" /\n" << setw(cont) << ' ';
           cout<< N->getNom() << "\n ";
        if(N->getGau()) {
            cout << setw(cont) << ' ' <<" \\\n";
            AffArbre2(N->getGau(), cont+i);
        }
    }
}
   void Arbre::postorder(Node* N){
    	if(N){
		 postorder(N->getGau());
		 postorder(N->getDro());
		 cout << N->getNom() << ",";
	         }
        }
    void Arbre::preorder(Node* N){
    	if(N){
    	 cout << N->getNom() << ",";
		 preorder(N->getGau());
		 preorder(N->getDro());
	         }
        }
 bool Arbre::Feuille(Node* N)
 	{
	 return (N->getGau()==NULL && N->getDro()==NULL );
	    }

void Arbre::insertNode(string pre,Node* &N, string sep) {
	int b=0;

	 if (N == NULL ) {
        Node* no = new Node(); no->setNom(pre);
        this->setRacine(no); N=this->getRacine();
                }
    else if (sep==",")  {
        if (N->getGau() == NULL) {
            Node* neuN = new Node(); neuN->setNom(pre);  neuN->setMere(N);
			N->setGau(neuN);
                }
		else if (N->getDro() == NULL){
           Node* neuN = new Node(); neuN->setNom(pre);  neuN->setMere(N);
		   N->setDro(neuN);
                 }
          }
    else if (sep=="(")  {
    	if (N->getGau()==NULL) {
          Node* Nu = new Node(); Nu->setNom(pre); Nu->setMere(N);
          N->setGau(Nu); N=N->getGau();
		          	}
          else if (N->getDro()==NULL) {
           Node* Nu = new Node(); Nu->setNom(pre); Nu->setMere(N);
           N->setDro(Nu); N=N->getDro();
        	        }
             	}
    else if (sep==")")  {
         	N=N->getMere();

    	}
    else cout<<"error!!!"<<endl;
}

void Arbre::setlevel(Node *k, int le) {
    if(k == NULL)  {
        return;
    }
    le++;
    setlevel(k->getGau(), le);
    setlevel(k->getDro(), le);
     k->setHau(le);
//     cout << k->getHau() << ",";
}

void Arbre::setlevel2(Node *k, vector <int >& lev, int le) {
    if(k == NULL)  {
        return;
    }
    le++;
    setlevel2(k->getGau(),lev, le);
    setlevel2(k->getDro(), lev, le);
    lev.push_back(le);
}
void Arbre::postNode(Node* N, vector < string>& leafset, vector < string>& nintset, vector < string>& totset){
    	if(N){
		postNode(N->getGau(), leafset, nintset, totset);
		postNode(N->getDro(), leafset, nintset, totset);
		 if (Feuille(N))
		    leafset.push_back(N->getNom());
		 else
		    nintset.push_back(N->getNom());
		 totset.push_back(N->getNom());
		 	         }
        }

void Arbre::PrintPostNode(Node* ar1)
{
    vector <string>::iterator itl, itn, itt;
    vector < string> lset, nset,tset;
    this->AffArbre(ar1);
    cout<<endl;
    this->postNode(ar1, lset,nset,tset);
    for(itl = lset.begin(); itl != lset.end(); itl++) cout << *itl <<" ";
	cout<<endl;
	for(itn = nset.begin(); itn != nset.end(); itn++) cout << *itn <<" ";
	cout<<endl;
	for(itt = tset.begin(); itt != tset.end(); itt++) cout << *itt <<" ";
	cout<<endl;
        }
void Arbre::nintNode(Node* N, vector < Node*>& leafset, vector < Node*>& intset, vector < Node*>& totset)
     {
    	if(N){
		nintNode(N->getGau(), leafset, intset,totset);
		nintNode(N->getDro(), leafset, intset, totset);

		 if (Feuille(N))
		    leafset.push_back(N);
		  else
		    intset.push_back(N);
		totset.push_back(N);
		 	}
        }
void Arbre::leafNode(Node* N, vector < Node*>& leafset)
     {
    	if(N){
		leafNode(N->getGau(), leafset);
		leafNode(N->getDro(), leafset);
		 if (Feuille(N))
		    leafset.push_back(N);

		 	}
        }

vector<vector<vector<string> > > Arbre::Biparti(Arbre* ar1, Node* nor)
{
   vector < Node*> leafN;
    stack <Node*> g1;
    stack <Node*> g2;
    g1.push(nor);
    Node* nor2;
    vector < vector <Node*> > Nv;
	while (!g1.empty())
    {
        nor2 =g1.top();
        g2.push(nor2);
        g1.pop();
        vector <Node*> vaux;
        if (!ar1->Feuille(nor2))
		   { //&&
           if (!(ar1->getRacine()==nor2)) {
		     vaux.push_back(nor2);
             if (Feuille(nor2->getGau()))   vaux.push_back(nor2->getGau());
		     if (Feuille(nor2->getDro()))   vaux.push_back(nor2->getDro());
		      Nv.push_back(vaux);
               vaux.clear();
              }

             }
    	if (nor2->getGau())  g1.push(nor2->getGau());
        if (nor2->getDro())  g1.push(nor2->getDro());
    }
	 int f=0, r=0;
	 for (int i =0; i<Nv.size(); i++) {
	 	if ((f==0)&&(Nv[i][0]->getMere()==ar1->getRacine())&&(Feuille(Nv[i][0]))){
		 r=i;f=3;
	      	}
			}
	if (f==0) {
	  for (int i =0; i<Nv.size(); i++) {
	 	if (Nv[i][0]->getMere()==ar1->getRacine()){
		 r=i; f=1;
	      	}
			}
				}
	 if ((Nv.size()>r) && (f==1))
             {
             Nv.erase( Nv.begin() + r);
                }
    leafNode(ar1->getRacine(), leafN);
    int Lf=leafN.size();
    int Ls=Nv.size();
    vector<vector<vector<string> > > preBipart(Ls, vector<vector<string> >(2, vector<string>(Lf, " ")));
    int uu=0,u=Ls-1, w=1, y;
     while (u>=0) {
          Node* naux;
          int a=u;
        while (a<=(Ls-1)){
          naux=Nv[a][0];
		  if (a==u)  {
		  while(w<Nv[u].size()) {
           preBipart[uu][0][w-1]=Nv[u][w]->getNom();
           w++; }
           }
           y=a+1;
	       while (y<=(Ls-1)){
			int b=1;
	         while ((b<Nv[y].size())&&(Nv[y][0]->getMere()==naux)) {
	             preBipart[uu][0][w-1]=Nv[y][b]->getNom();
	             b++; w++;
				  }
	      	y++;
	      	     }
	      	a++;
	      	   }
       u--; w=1; uu++;
     }
     int g=0, gg, yy, ggp=0;
     vector <string> vse, se;
     while (g<Ls)  {
     gg=0;ggp=0;
	 yy=0;
     while (yy<leafN.size())  {
        gg=0;
		 while ((gg<preBipart[g][0].size())&&(preBipart[g][0][gg]!=" ")&&(preBipart[g][0][gg]!=leafN[yy]->getNom())) gg++;
          if ((gg==preBipart[g][0].size())or(preBipart[g][0][gg]==" ")) {preBipart[g][1][ggp]=leafN[yy]->getNom(); ggp++; }
      yy++;
       }
       g++;
       }
    return preBipart;
}

 int Arbre::RFdistance(string newick1, string newick2)  {
 	vector<vector<vector<string> > > bipart1;
 	vector<vector<vector<string> > > bipart2;
	Arbre* ar1 = new Arbre();
 	Arbre* ar2 = new Arbre();
    ar1=ar1->NewickParser(newick1);
    ar2=ar2->NewickParser(newick2);
    bipart1=ar1->Biparti(ar1, ar1->getRacine());
    bipart2=ar2->Biparti(ar2, ar2->getRacine());
    int i, i2, j, j2, rf, c, k, k2, s;
    rf=0;
	i=0;
    while(i<bipart1.size()) {
     i2=0; s=0;
      while (i2<bipart2.size()) {
	  	j=0;
        while (j<2) {
           j2=0;
           while (j2<2) {
	          int t=0, pp=0, nn=0; k=0; k2=0; c=0;
	          while (bipart1[i][j][pp]!=" ") pp++;
	          while (bipart2[i2][j2][nn]!=" ") nn++;
	          if (nn==pp) {
	          	//cout<<bipart1[i][j].size()<<endl;
	          while (k<bipart1[i][j].size()&&bipart1[i][j][k]!=" ") {
	          	     k2=0;
	          	  while (k2<bipart2[i2][j2].size()&&bipart2[i2][j2][k2]!=" ")  //(bipart2[i2][j2][k2].length()==bipart1[i][j][k].length())
					{
	          	  	   if (bipart1[i][j][k]==bipart2[i2][j2][k2])  { c++;
						  // cout<<c<<"  ";
						   }
	          	  	    k2++;
	          	  	        }
	          	  	    t=k2;
	          	  	    k++;
	          	  	     }
					   if ((nn==c)){
	                   rf=rf+2;
				       s=1; break;}
                         }
						if (s==1) break;
						    j2++;
	          	  	}

            if (s==1) break;
            j++;
          }
        if (s==1) break;
       i2++;
       }
    i++;
   }
   int Sb1= bipart1.size();
   int Sb2= bipart2.size();
   int Dst=0;
   Dst=Sb1+Sb2-rf;
   return Dst;
     }
bool Arbre::PValable(char open,char close)
     {
	  static map<char, char> parentheses;
	  parentheses['('] = ')';
	  if(parentheses[open]==close) return true;
	  return false;
       }

Arbre* Arbre::NewickParser(string newick, int num)
{
	stack<char>  S;
	int founds, c, i=0, h=0, cmax=0, p=0;
	string  ra;
	string::iterator end_pos = remove(newick.begin(), newick.end(), ' ');
    newick.erase(end_pos, newick.end());
	i=newick.find("(");
	Node* N= new Node();
	N=NULL;i=0; int pin=0;
	while(i<newick.length())
	 {
	  c=0;
	  while (((i+c)<newick.length())&&(newick[i+c]!=')')&&(newick[i+c]!=',')&&(newick[i+c]!='(')) c++;
	  if ((i+c)<newick.length()) {
	  if (newick[i+c] == '(') {
	  	    if (i==0) this->insertNode("R",N, "(");
	  	    else {
	  	       h++;
	  	        if (h>cmax) cmax=h;
			    if (num==0) {
                 string strpin; stringstream pout;
                 pout << pin; strpin = pout.str(); pin++;
				 strpin="I"+strpin;
			     this->insertNode(strpin, N, "(");
			    }
				else if (num==1)
				  this->insertNode("I",  N, "(");
				else
				  this->insertNode(" ", N, "(");
	  		  }
	  		S.push('(');

	     }
	  else if (newick[i+c] == ',') {
	  	   if (newick[i-1] != ')') {
	  	   	h=0;
	  	   	if (c>0) this->insertNode(newick.substr(i,c),  N, ",");
	  		else     this->insertNode(" ", N, ",");

			  }
	    }
	  else if (newick[i+c] == ')') {
	  	     if(S.empty() || !PValable(S.top(),newick[i+c]))  {
	  		  		   this->setRacine(NULL);
   				    return this;
   				     }
			     else
				    S.pop();
	         if (newick[i-1]== ',') {
	           p=0;
	           if (c>0) this->insertNode(newick.substr(i,c),  N, ",");
	  		   else     this->insertNode(" ",  N, ",");

	                     }
				this->insertNode(" ",  N, ")");
				 h--;
	                    }
	      }
	        i=i+c+1;
	      }
	  this->getRacine()->setHau(cmax);
	    return this;
	 }

void Arbre::FArbre(Node *N,  ofstream &fout, int cont, int i)  {
	//
    	if (N==NULL)  {
    	   return;
    	     }
    	 else  {
    	 	FArbre(N->getDro(),fout, cont+i);
    	 	if (cont> 0)
            fout << setw(cont) << " ";
    	 	fout<<N->getNom()<<endl;
    	    FArbre(N->getGau(), fout, cont+i);
    	 	}
        }

void Arbre::PrintTree(ifstream& fileReads, ofstream& fout)
{
 string newick, str;
 vector<Arbre*> TreeList;
 vector<string> NewickList;
 //ifstream fileReads(fstr.c_str(), ios::in);
 int c=0, p1,p2=0;
  if (fileReads.is_open()) {
    while (getline (fileReads, str) )
    {
      Arbre* ar1 = new Arbre();
       int p1=str.find(";");
       if (p1!=std::string::npos) {
	     newick=str.substr(0, p1+1);
          ar1=ar1->NewickParser(newick);
         NewickList.push_back(newick);
		 TreeList.push_back(ar1);
			}
   // fileReads.close();
      }
	 }
	int LT=TreeList.size(), i=0;
	int LN=NewickList.size();
//	cout<<endl<<LT;
       while (i<LT) {
       fout<<"Tree  "<<i<<endl;
       fout <<NewickList[i]<<endl<<endl;
       FArbre(TreeList[i]->getRacine(),fout);
       fout<<endl;
       i+=1;
              	 }
	 }


int main(void)
{
	int i,c=1;
    Arbre* ar1 = new Arbre();
	vector<string>  names, sequences;
	string fstr="arbres.nw";
	string outFile="OutArbres.txt";
	string biparti="Out.txt";
	ofstream fout(biparti.c_str());
	ifstream fileReads(fstr.c_str(), ios::in);
    ar1->PrintTree(fileReads, fout);
    string newi="(OR2J3_Humain,((PCDHA1_Humain,PCDHA1_Bonobo),(PCDHA1_Rat,PCDHA1_Souris)));";
    vector<vector<vector<string> > > uy;
//    vector<vector<vector<string> > > uy;
//  //string newi="((PCDHA1_Humain,OR2J3_Humain),((PCDHA1_Rat,PCDHA1_Souris),PCDHA1_Bonobo));";
//   // string newi="(((PCDHA1_Humain, PCDHA1_Rat), (PCDHA1_Souris, PCDHA1_Bonobo)), OR2J3_Humain);";
//   string newi="(((OR2J3_Humain, PCDHA1_Rat), (PCDHA1_Souris, PCDHA1_Bonobo)), PCDHA1_Humain);";
// // string newi2="((((PCDHA1_Rat,  PCDHA1_Souris),OR2J3_Humain), PCDHA1_Humain),PCDHA1_Bonobo);";
//  string    newi2="((((PCDHA1_Humain,PCDHA1_Souris),PCDHA1_Rat),OR2J3_Humain),PCDHA1_Bonobo);";
    ar1=ar1->NewickParser(newi);
   uy=ar1->Biparti(ar1, ar1->getRacine());
//    cout<<endl;
//    for (int u =0; u<uy.size(); u++) {
//     for (int i =0; i<uy[u].size(); i++) {
//  	  for (int j =0 ; j<uy[u][i].size(); j++) {
//  		cout<<uy[u][i][j]<<" ";
//   		 }
//   	    cout<<"   ";
//	      }
//	 cout<<endl;
//    }
//    Node* nod = new Node();
//  vector<Node *> tre;
//    map<pair<string, string>, double> edges1;
//    vector< vector< vector<double> > > MdNJ;
//    vector< vector<double> > Dis;
//	InputOut(names, sequences);
//	Dis=MDistance(sequences);
//
//    tre=ar1->NJ(nod, Dis , names);
//    cout<<endl;
//    for (int j =0 ; j<tre.size(); j++) {
//  		cout<<tre[j]->getNom()<<" ";
//   		 }
//   	  cout<<endl;
//      Node* nod1 = new Node();
//    ar1->NJ2(tre, nod1);
//  ar1->AffArbre(nod1);
//
//
//   // int dRF;
//  // dRF=ar1->RFdistance(newi, newi2);
//   //cout<<endl<<dRF;
//
////    string newi="((PCDHA1_Humain, OR2J3_Humain), ((PCDHA1_Rat, PCDHA1_Souris), PCDHA1_Bonobo));";
////    ar1=ar1->NewickParser(newi);
////    ar1->Bipart(ar1->getRacine());
//
////
//////	vector< pair<Node*,Node*> > treeEdges;
////    vector< vector<double> > Dis;
////    //ifstream fileReads;
////	InputOut(names, sequences);
////	Dis=MDistance(sequences);
//////	int qsr=getScore(BLOSUM62,aa, 'N','N');
//////	cout<<endl<<qsr;
////	printMatrix(names, Dis);
//////	Arbre* ar1 = new Arbre();
//////    treeEdges=ar1->NJ(Dis, names);
////
////
//



    //Node* N= new Node();
	//Arbre* ar1 = new Arbre();
//    string newi="((PCDHA1_Humain, OR2J3_Humain), ((PCDHA1_Rat, PCDHA1_Souris), PCDHA1_Bonobo));";
//    string newi2="(((PCDHA1_Humain, PCDHA1_Rat), (PCDHA1_Souris, PCDHA1_Bonobo)),OR2J3_Humain);";
//     Arbre* ar1 = new Arbre();
//        ar1=ar1->NewickParser(newi);
//		ar1->PrintPostNode(ar1->getRacine()); int g;
//		ar1->setlevel(ar1->getRacine());
//		vector <int> lev;
//		ar1->setlevel2(ar1->getRacine(), lev);
//	for (int j =0 ; j<lev.size(); j++) {
//  		cout<<lev[j]<<" ";
//   		 }
//   	  cout<<endl;


    //((,),((,),))
//    Arbre* ar1 = new Arbre();
//    vector < vector <Node*> > biparti;
//
//   ar1->RFBipartitions(newi,biparti) ;
//     cout<<endl;
//   for (int i =0; i<biparti.size(); i++) {
//    	for (int j =0 ; j<biparti[i].size(); j++) {
//   		cout<<biparti[i][j]->getNom()<<" ";
//    		 }
//    	  cout<<endl;
//	      }
//


//
//      vector <Node*> nintset1;
//      vector <Node*> leafset1, totset1;
//      //Arbre* ar1 = new Arbre();
//      ar1=ar1->NewickParser(newi);
//     ar1->nintNode(ar1->getRacine(), leafset1, nintset1, totset1);
//
//    		    cout<<"aqui"<<endl;
//    for (int i =0; i<totset1.size(); i++) {
//    		cout<< ar1->getNodeHau(ar1->getRacine(), totset1[i])<<" ";
//	      }
////
////     N=NULL;
//	 ar1=ar1->NewickParser(newi2);
//	 ar1->AffArbre(ar1->getRacine());
//	 ar1->postorder(ar1->getRacine());
//	 //ar1->postNode(ar1->getRacine(), leafset,nintset,totset);
//	ar1->PrintPostNode(ar1->getRacine());
//	   cout<<endl;
//    ar1->AffArbre(ar1->getRacine());
//
//	 ar1=ar1->NewickParser(newi2);
//	   cout<<endl;
//    ar1->AffArbre(ar1->getRacine());
//    vector < vector <Node*> > biparti;
//


//     ar1=NewickParser(newi);
//     	cout<<endl;
//    ar1->AffArbre(ar1->getRacine());
//    cout<<endl;
//    ar1->AffArbre2(ar1->getRacine());
//    ar1=NewickParser(newi2);
//    cout<<endl;
   // ar1->AffArbre(ar1->getRacine());



    return 0;
}


