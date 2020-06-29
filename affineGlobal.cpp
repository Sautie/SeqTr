#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

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

int  NWalign(vector< vector<int> > &V, vector< vector<int> > &G, vector< vector<int> > &E, vector< vector<int> > &F, string &seqA, string &seqB)
{
 const int GOCOST = 10;
 const int GECOST = 1;
 int N = seqA.length() + 1, M = seqB.length() + 1; 

  V.resize(N, vector<int>(M, 0));
  G.resize(N, vector<int>(M, 0));
  E.resize(N, vector<int>(M, 0));
  F.resize(N, vector<int>(M, 0));
  //V[0][0] = F[0][0] = E[0][0] =G[0][0] = 0;
for (int i = 0; i < N; i++) {
      G[i][0] =numeric_limits<int>::min()+1;
      F[i][0] =numeric_limits<int>::min()+1;
	  V[i][0] =-GOCOST-(GECOST*i);
	  E[i][0] =-GOCOST-(GECOST*i);      
                      }
 for (int j = 0; j < M; j++) {
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

/*int i = N - 1, j = M - 1;
 
   while (i > 0 || j > 0) {
      if ((j>=0)&&(i>=0)&&(V[i][j] == E[i][j])) {
         seqA.insert(i, 1, '-');
         j--;
      } else if ((i>=0)&&(j>=0)&&(V[i][j] == F[i][j])) {
         seqB.insert(j, 1, '-');
         i--;
      } else { 
        
         i--, j--;
      }
     cout<<seqA<<endl;
     cout<<seqB<<endl;
   }*/
 

cout<<"aqui"<<endl;    	  
return V[N-1][M-1];
   }
   
/*vector< string > BacktrackA (vector< vector<int> > &V,vector< vector<int> > &E, vector< vector<int> > &F, string &seqA, string &seqB) 
{ 
 int i = V.size()-1, j = V[0].size()-1; 
 string seqAA, seqBB;
 vector< string > seqAlign; 
   while (i > 0 || j > 0) {
      if (V[i][j] == F[i][j]) {
      	if ((i == V.size()-1)&&(j == V[0].size()-1)){
		  seqAA=seqA[i-1];   
		  seqBB="-";
		  } 
		else 
		  {
		   seqAA=seqA[i-1]+seqAA;
		   seqBB="-"+seqBB;
		   }         
         i--;
      } 
	  else if (V[i][j] == E[i][j]) {
      	 if ((i == V.size()-1)&&(j == V[0].size()-1)) {
		  seqAA="-";
		  seqBB=seqB[j-1];
		  } 
		 else
		    {
		   seqBB=seqB[j-1]+seqBB;
		   seqAA="-"+seqAA;
		   }
        j--;
      } else 
	     {
      	 if ((i == V.size()-1)&&(j == V[0].size()-1)) 
		   {
		  seqAA=seqA[i-1];
		  seqBB=seqB[j-1];
		  } 
		 else
		    {
		   seqBB=seqB[j-1]+seqBB;
		   seqAA=seqA[i-1]+seqAA;
		   }
         i--, j--;         
      }  
      
	  cout<<i<<" "<<seqA[i-1]<<" "<<j<<" "<<seqB[j-1]<<endl;
	    
   }
   seqAlign.push_back(seqAA);
   seqAlign.push_back(seqBB);
cout<<endl<<"piss";
 return seqAlign;
   }*/


int main () {
   	string filename="data/sequences1.fasta";
   	vector< vector<int> > V,F,G,E;
   	vector< string > align;
   	string seqA="MGEIGFTEKQEALVKESWEILKQDIPKYSLHFFSQILEIAPAAKGLFSFLRDSDEVPHNNPKLKAHAVKVFKMTCETAIQLREEGKVVVADTTLQYLGSIHLKSGVIDPHFEVVKEALLRTLKEGLGEKYNEEVEGAWSQAYDHLALAIKTEMKQEES";
    string seqB="MEKVPGEMEIERRERSEELSEAERKAVQATWARLYANCEDVGVAILVRFFVNFPSAKQYFSQFKHMEEPLEMERSPQLRKHACRVMGALNTVVENLHDPEKVSSVLSLVGKAHALKHKVEPVYFKILSGVILEVIAEEFANDFPPETQRAWAKLRGLIYSHVTAAYKEVGWVQQVPNATTPPATLPSSGP";
   	int N = seqA.length() + 1, M = seqB.length() + 1; //matrix.resize(N, vector<int>(M, 0));
	vector<string> sequences;
   	vector<string> names; 
   	
	//listSeq(sequences, names);	
    ofstream fout(filename.c_str()); 
    cout<<"pet";
    if (!fout) {
      cerr << "error: open file for output failed!" << endl;
      abort();  // in <cstdlib> header
         }
    int Ls, rint;
    
    rint=NWalign(V, G, E, F, seqA, seqB);
    //align=BacktrackA (V,E, F,seqA,seqB); 
    //fout<<rint<<endl;
    //fout<<seqA<<endl;
    //fout<<seqB<<;    
    
    for (int i = 0; i < N; i++) {              
    for (int j = 0; j < M; j++) {
   	 fout<<V[i][j]<<" "<<endl;
   	 }
    fout<<endl;
     }

	/*Ls=sequences.size();
	rint=getScore(BLOSUM62,aa,'D','C');	//2ieme colonne, 1ier ligne	 
	fout<<rint;
	fout <<endl;
    for( int j = 0; j < Ls; j+=1)
      {
        fout<<names[j]<<endl;
        fout<<sequences[j]<<endl<<endl;
               }
    fout <<endl;
	 for (int i = 0; i < N; i++) {              
     for (int j = 0; j < M; j++) {
     	 fout<<matrix[i][j]<<" ";
     	      }
     	 fout<<endl;
     	  } */	  	  
	 
  return 0;
}   

