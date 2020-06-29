

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

#include "NWaffine.h"

using namespace std;

struct Indexc
{
    const vector<int>& dia;

    Indexc(const vector<int>& dia): dia(dia) {}

    bool operator()(int a, int b) const { return dia[a] < dia[b]; }
};





int main () {
	vector< vector<int> > V,F,G,E;
	string seqA, seqB, seqA2, seqB2;	
	int rint, rint2;
	seqA="MCAT";
    seqB="MGACCT";    
	rint=NWalign(V,G,E,F,seqA,seqB);
	backtracking (V, E,F,seqA,seqB);
	seqA2="MGAPWYTST";
    seqB2="MAHTYTT"; 
    rint2=NWalign(V,G,E,F,seqA2,seqB2);
	backtracking (V, E,F,seqA2,seqB2);
	cout<<seqA<<endl;
	cout<<seqB<<endl;	
	cout<<rint<<endl<<endl;
	cout<<seqA2<<endl;
	cout<<seqB2<<endl;	
	cout<<rint2<<endl<<endl;
	
	
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

