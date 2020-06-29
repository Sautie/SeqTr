#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>



// Fonctions principales: NWalign (alignement global avec ponderation affine) , backtracking (pour retrouver l'alignment de score maximal),
// NWalignSeqPairs (fonction pour faire tous les alignments possibles entre deux sequences, sequences en format fasta dans un fichier),
// Il ya autres fonctions auxiliares telles que ChosenSeqPairs, similarite, getscore, listseq... utilisees pour construire l'alignement avec arbre etoile,
//choisir la sequence centrale, calculer les sp scores, l'identite entre deux sequences,...


using namespace std;

struct Indexc
{
    const vector<int>& dia;

    Indexc(const vector<int>& dia): dia(dia) {}

    bool operator()(int a, int b) const { return dia[a] < dia[b]; }
};


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

int max(int x, int y, int z=numeric_limits<int>::min())
{
   return x > y ? (x > z ? x : z) : (y > z ? y : z);
}

int max2(int h, int v, int d, vector<string> &trace)
{

   if (h>=d && h>=v)
    {
     if (h==v&&h==d) {
	   trace.push_back("ho");
	   trace.push_back("di");
	   trace.push_back("ve");
	    }
		else if (h==v)
	      {
			trace.push_back("ho");
			trace.push_back("ve");
			  }
		else if (h==d)
		   {
			trace.push_back("ho");
			trace.push_back("di");
			  }
         else if (h>d && h>v)
			trace.push_back("ho");
	  return h;
   }
   else if (d>=v && d>h)
       {
        if (d==v) {
        	trace.push_back("ve");
			trace.push_back("di");
        	 }
		else {
			trace.push_back("di");
        	 }
        return d;
          }
    else if (v>=d && v>h)
      {
      if (d==v) {
        	trace.push_back("ve");
			trace.push_back("di");
        	 }
		else {
			trace.push_back("ve");
        	 }
      	return v;
       }

}
//x:m, y:g2, z:g1

void listSeq(vector<string> &sequences, vector<string> &names, string filename1="data/sequences.fasta")
  {
	int c=0;
	ifstream fileReads(filename1.c_str());
	if (!fileReads) {
      cerr << "error: open file for reading failed!" << endl;
      abort();  // in <cstdlib> header
       }
    string line, sequence, name;
    while (getline(fileReads, line)) {
      if (line.empty()) {
      	 sequences.push_back(sequence);
      	 names.push_back(name);
         continue;
          }
      size_t p = line.find('>');
      if (p!=std::string::npos)
	    {
         name=line.substr(p+1,line.length()-p-1);
		 c=1;
		 }
		 else
		  {
		  if (c==1)
		    sequence=line;
		  else
	        sequence += line;
		    c=0;
		     }
           }
    sequences.push_back(sequence);
    names.push_back(name);
    fileReads.close();
	return;
	}
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

int  NWalign(vector< vector<int> > &V, vector< vector<int> > &G, vector< vector<int> > &E, vector< vector<int> > &F, string seqA, string seqB)
{
 const int GOCOST = 10;
 const int GECOST = 1;
 int N = seqA.length() + 1, M = seqB.length() + 1;

  V.resize(N, vector<int>(M, 0));
  G.resize(N, vector<int>(M, 0));
  E.resize(N, vector<int>(M, 0));
  F.resize(N, vector<int>(M, 0));
V[0][0] = 0;
F[0][0] = 0;
E[0][0] =0;
G[0][0] = 0;
for (int i = 1; i < N; i++) {
      G[i][0] =numeric_limits<int>::min()+1;
      F[i][0] =numeric_limits<int>::min()+1;
	  V[i][0] =-GOCOST-(GECOST*i);
	  E[i][0] =-GOCOST-(GECOST*i);
                      }
 for (int j = 1; j < M; j++) {
      G[0][j] =numeric_limits<int>::min()+1;   //numeric_limits<int>::min()
      E[0][j] =numeric_limits<int>::min()+1;
      V[0][j] =-GOCOST-(GECOST*j);
	  F[0][j] =-GOCOST-(GECOST*j);
                      }
int scr;
 for (int i = 1; i < N; i++) {  //seqA
      for (int j = 1; j < M; j++) {   //seqB
      	scr=getScore(BLOSUM62,aa, seqA[i - 1], seqB[j - 1]);
      	G[i][j] =V[i-1][j-1]+scr;
      	E[i][j] = max(E[i][j - 1]-GECOST, V[i][j-1]-GECOST-GOCOST);
      	F[i][j] =max(F[i - 1][j] - GECOST,V[i - 1][j]-GECOST-GOCOST);
        V[i][j] =max(G[i][j],E[i][j],F[i][j]);
      }
   }

return V[N-1][M-1];
   }
 vector<int> similarite(string seqA, string seqB) {
  	vector<int> simo;
	  int d=0;
  	for (int i = 1; i < seqA.length(); i++) {
  		if (seqA[i]==seqB[i]) d++;
  		}
  	simo.push_back(d);
  	simo.push_back(seqA.length()-d);
	simo.push_back(seqA.length());
  	return simo;
  	 }
void backtracking (vector< vector<int> > &V, vector< vector<int> > &E, vector< vector<int> > &F, string &seqA, string &seqB) {
   int i = seqA.length(), j = seqB.length();
   while (i > 0 || j > 0) {
      if (V[i][j] == E[i][j]) {
         seqA.insert(i, 1, '-');
         j--;
      } else if (V[i][j] == F[i][j]) {
         seqB.insert(j, 1, '-');
         i--;
      } else {
         i--, j--;
      }
      }
      cout<<endl<<j;
      return;
   }

 void  NWalignSeqPairs(string filename, vector< vector<string > > &align, vector< vector<string > > &Mnames, vector<int> &scores) {
 	vector< vector<int> > V,F,G,E;
 	vector<string> sequences;
   	vector<string> names;
	listSeq(sequences, names);
	ofstream fout(filename.c_str());
	if (!fout) {
      cerr << "error: open file for output failed!" << endl;
      abort();  // in <cstdlib> header
         }
    int Ls, rint;
	vector<int> sima;
	Ls=sequences.size();
	vector< string > sequencesA=sequences;
	fout <<endl;
    for( int j = 0; j < Ls; j+=1) {
      vector <string> AuxNames;
      vector <string> AuxSequences;
    for( int i = j+1; i < Ls; i+=1)
      {
        fout<<"Sequences: "<<names[j]<<", "<<names[i]<<endl;
        AuxNames.push_back(names[j]); AuxNames.push_back(names[i]);
        rint=NWalign(V, G, E, F, sequences[j], sequences[i]);
        scores.push_back(rint);
        backtracking (V, E, F, sequences[j], sequences[i]);
        sima=similarite(sequences[j], sequences[i]);
        fout<<"score: "<<rint<<"  similarite: "<<sima[0]<<"/"<<sima[2]<<endl;
        fout<<sequences[j]<<endl;
        fout<<sequences[i]<<endl<<endl;
        AuxSequences.push_back(sequences[j]); AuxSequences.push_back(sequences[i]);
        sequences[j]=sequencesA[j];
        sequences[i]=sequencesA[i];
        Mnames.push_back(AuxNames);
		 align.push_back(AuxSequences);
		 AuxNames.clear();
		 AuxSequences.clear();
        V.clear(); G.clear();E.clear(); F.clear();
               }

      }
 	return;
 	}


vector< vector<string > > ChosenSeqPairs(string filename1, vector< vector<string > > &align, vector< vector<string > > &Mnames, vector<int> &scores, string Name)
{
ofstream fout(filename1.c_str());
	if (!fout) {
      cerr << "error: open file for output failed!" << endl;
      abort();  // in <cstdlib> header
         }
vector<int > sscores, auxsort;
vector<vector<string >  > salign, sMnames;

for(size_t i = 0; i < scores.size(); ++i)
        auxsort.push_back(i);
sort(auxsort.begin(), auxsort.end(), Indexc(scores));

for(size_t i = 0; i < scores.size(); ++i)
        sscores.push_back(scores[auxsort[i]]);

for(size_t i = 0; i < scores.size(); ++i) {
	    salign.push_back ( vector<string>() );
        salign[i].push_back(align[auxsort[i]][0]);
        salign[i].push_back(align[auxsort[i]][1]);
    	}

for(size_t i = 0; i < scores.size(); ++i) {
	    sMnames.push_back ( vector<string>() );
        sMnames[i].push_back(Mnames[auxsort[i]][0]);
        sMnames[i].push_back(Mnames[auxsort[i]][1]);
    	}
vector<string > auxChalign;
vector< vector<string > > MChalign;
for( int i = 0; i < sMnames.size(); i+=1) {
	for( int j = 0; j < 2; j+=1) {
	   if (sMnames[i][j]==Name) {
	     auxChalign.push_back(salign[i][0]); auxChalign.push_back(salign[i][1]);
		 fout<<"Sequences: "<<sMnames[i][0]<<", "<<sMnames[i][1]<<" Score: "<<sscores[i]<<endl;
		 fout<<salign[i][0]<<endl<<salign[i][1]<<endl;
	     }
		}
		MChalign.push_back(auxChalign);
		auxChalign.clear();
	}
return 	MChalign;
}



int main () {

	vector< vector<int> > V,F,G,E;
	string seqA, seqB, seqA2, seqB2, S1,S2;
	int rint, rint2, rint3;
	seqA="MCAT";     // sequences de reference
    seqB="MGACCT";
	rint=NWalign(V,G,E,F,seqA,seqB); //FONCTION POUR FAIRE L'ALIGNMENT GLOBAL avec SCORE AFFINE, PENALITES de gaps: 10, 1, BLOSUM 62, V G E et F: 4 tables de PD
	                                // utilisees par l'alignement avec ponderation affine
	backtracking (V, E,F,seqA,seqB); //FONCTION POUR RETROUVER L'ALIGNMENT DE SCORE MAXIMAL
	seqA2="MGAPWYTST";
    seqB2="MAHTYTT";
    rint2=NWalign(V,G,E,F,seqA2,seqB2);
	backtracking (V, E,F,seqA2,seqB2);

	S1="MGEIGFTEKQEALVKESWEILKQDIPKYSLHFFSQILEIAPAAKGLFSFLRDSDEVPHNNPKLKAHAVKVFKMTCETAIQLREEGKVVVADTTLQYLGSIHLKSGV";
	S2="MEKVPGEMEIERRERSEELSEAERKAVQATWARLYANCEDVGVAILVRFFVNFPSAKQYFSQFKHMEEPLEMERSPQLRKHACRVMGALNTVVENLHDPEKVS";

	rint3=NWalign(V,G,E,F,S1,S2);
//	backtracking (V, E,F,S1,S2);

	cout<<seqA<<endl;
	cout<<seqB<<endl;
	cout<<rint<<endl<<endl;
	cout<<seqA2<<endl;
	cout<<seqB2<<endl;
	cout<<rint2<<endl<<endl;
	//cout<<S1<<endl;
	//cout<<S2<<endl;
	cout<<rint3<<endl<<endl;


	  // ci-dessous: AUTRES fonctions développées pour l'alignement multiple avec arbre etoile, calcul du SP score, sequence consensus,...
	 // par exemple la fonction NWalignSeqPairs(filename, align, Mnames,Scores)
     //  cette fonction prend les sequences dans le fichier sequences.fasta (par default doit etre dans le dossier, data/)
     //  et fait tous les alignments possibles entre deux sequences... imprime dans le fichier de sortie defini
	 //  en filename, le score, la similarite et l'alignement de score maximal pour chaque paire de sequences.


//   	string filename="data/sequences2.fasta";
//   	string filename1="data/sequencesChosen.fasta";
//	vector<int> Scores;
//   	string Name;
//   	vector< vector<string > > align, Chalign;
//	vector< vector<string > > Mnames;
//   	NWalignSeqPairs(filename, align, Mnames,Scores);
//   	Chalign=ChosenSeqPairs(filename1, align, Mnames, Scores, "S2");
//
//	string filename2="data/multA.align";
//   	ifstream fileRead(filename2.c_str());
//	if (!fileRead) {
//      cerr << "error: open file for reading failed!" << endl;
//      abort();  // in <cstdlib> header
//       }
//    string filename3="data/SPscoreA.align";
//	ofstream fileout(filename3.c_str());
//    string line, seq1, seq2;
//	vector<string > seqalign;
//    while (getline(fileRead, line)) {
//   	 seqalign.push_back(line);
//           }
//    int g[seqalign[0].length()];
//    for(int u=0; u<seqalign[0].length(); u+=1) g[u]=0;
//    //string consensus=seqalign[seqalign.size()-1];
//    for( int j = 0; j < seqalign.size(); j+=1) {
//     seq1=seqalign[j];
//     for(int i = j+1; i < seqalign.size(); i+=1) {
//       seq2=seqalign[i];
//       for(int ii = 0; ii < seq1.length(); ii+=1) {
//         if (seq2[ii]!=seq1[ii]) g[ii]=g[ii]+1;
//           }
//        }
////     int sum1=0;
////     for(int uu = 0; uu < seq1.length(); uu+=1) if (consensus[uu]==seq1[uu]) sum1=sum1+1;
////     fileout<<(float)sum1/(float)seq1.length()<<endl;
//	 }
//
//	 int sum=0;
//	 for(int u=0; u<seqalign[0].length(); u+=1) sum=sum+g[u];
//	 fileout<<"SPscore: "<<sum<<endl;
//	 for(int u=0; u<seqalign[0].length(); u+=1) fileout<<g[u]<<" ";
//	 fileout<<endl;
//

  return 0;
}



