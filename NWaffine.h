#ifndef NWAFFINE_H
#define NWAFFINE_H


extern int BLOSUM62[][25];

extern char aa[];


int max(int x, int y, int z=numeric_limits<int>::min());

int max2(int h, int v, int d, vector<string> &trace);
 
void listSeq(vector<string> &sequences, vector<string> &names, string filename1="data/sequences.fasta");

int getScore(int matr[][25], char alph[], char cc, char LL);

int  NWalign(vector< vector<int> > &V, vector< vector<int> > &G, vector< vector<int> > &E, vector< vector<int> > &F, string seqA, string seqB);

vector<int> similarite(string seqA, string seqB);

void backtracking (vector< vector<int> > &V, vector< vector<int> > &E, vector< vector<int> > &F, string &seqA, string &seqB);

 void  NWalignSeqPairs(string filename, vector< vector<string > > &align, vector< vector<string > > &Mnames, vector<int> &scores);
 
 vector< vector<string > > ChosenSeqPairs(string filename1, vector< vector<string > > &align, vector< vector<string > > &Mnames, vector<int> &scores, string Name);
#endif
