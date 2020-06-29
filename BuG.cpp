#include<iostream>
#include <algorithm>
#include<string>
#include<list>
#include<vector>
#include <stack>
#include <map>
#include "tree.hh"

using namespace std;

///////////////////////////// int partitions
vector<vector<int> > IntPart(int n)
{
      int part[n], k = 0;

     vector<vector<int> > dd;
     vector<int> ddv;
     part[k] = n;

    while(k>=0)
    {

        for(int i=0;i<=k+1;i++)
        ddv.push_back(part[i]);
        dd.push_back(ddv);
        ddv.clear();
        int re = 0;

       while (k >= 0 && part[k] == 1)
        {
            re += part[k];
			k--;
        }

    if (k>=0) {
        part[k]--;
        re++;
       while (re > part[k])
        {
            part[k+1] = part[k];
            re = re - part[k];
            k++;
        }
        part[k+1] = re;
        k++;
         }
    }
    return dd;
}
 /////////////////////////////////// combinations of strings
void combA(vector<vector<string> > &dd,vector<string> &ensemble, int size, int left, int index, list<string> &l){
     vector<string> ddv;
    if(left==0){
        for(list<string>::iterator it=l.begin(); it!=l.end() ; ++it)
        ddv.push_back(*it);
        dd.push_back(ddv);
        return;
       }
    for(int i=index; i<size;i++){
        l.push_back(ensemble[i]);
        combA(dd, ensemble,size,left-1,i+1,l);
        l.pop_back();
       }
    }

 /////////////////////////////////// combinations of string tree iterators
void combAIt(vector<vector<tree<string>::iterator> > &dd,vector<tree<string>::iterator> &ensemble, int size, int left, int index, list<tree<string>::iterator> &l){
	 // vector< vector<tree<string>::iterator> > vec2;
     vector<tree<string>::iterator> ddv;
    if(left==0){
        for(list<tree<string>::iterator>::iterator it=l.begin(); it!=l.end() ; ++it)
        ddv.push_back(*it);
        dd.push_back(ddv);
        return;
             }
    for(int i=index; i<size;i++){
        l.push_back(ensemble[i]);
        combAIt(dd, ensemble,size,left-1,i+1,l);
        l.pop_back();
                }
          }

//////////////////////////////////////fonction pour generer les partitions du gBu (des noeds de plus de 2 fils); Entree: vector of strings which label the child nodes

vector <vector <vector < vector <string> > > > TreeParti (vector<string> &v) {

	int n;
	vector<vector<string> > combinations;
	list<string> lt;
    vector<vector<int> > gg;
    n=v.size();
	gg=IntPart(n);

    //cout<<gg.size()<<endl;
 /*for(int i=0;i<=gg.size()-1;i++){
    for(int j=0;j<=gg[i].size()-2;j++)
        cout << gg[i][j] << " ";
    cout << endl;}*/
    //n=3
    /*combA(combinations,v,n,3,0,lt);
    cout<<endl;
    for(int i=0;i<=combinations.size()-1;i++){
    for(int j=0;j<=combinations[i].size()-1;j++)
        cout << combinations[i][j] << " ";
    cout << endl;}*/
    cout<<endl;
    vector<vector< vector< vector<string> > > >  PartTemp;
    for(int i=0;i<gg.size();i++){
	   	vector< vector< vector<string> > >   PartTemp0;
	   	int lg; lg=gg[i].size()-1;
       for(int j=0;j<lg;j++) {
       	 if (gg[i][0]==1) lg=1;
       	 combA(combinations,v,n,gg[i][j],0,lt);
         vector< vector<string> > row2;
         for (int r = 0; r< combinations.size(); r++) {
		       vector<string> row;
	  	   for (int rr = 0; rr < combinations[r].size(); rr++) {
       	         row.push_back(combinations[r][rr]);
       	                              }
       	    row2.push_back(row);
			row.clear();
       	                   }
       	    PartTemp0.push_back(row2);
       	    row2.clear();
       	    combinations.clear();
                            }
            PartTemp.push_back(PartTemp0);
            PartTemp0.clear();
        }


/*	for(int i=0;i<=PartTemp.size()-1;i++){
      for(int j=0;j<=PartTemp[i].size()-1;j++) {
	     for(int jj=0;jj<=PartTemp[i][j].size()-1;jj++) {
	       for(int jjj=0;jjj<=PartTemp[i][j][jj].size()-1;jjj++) {
	                cout << PartTemp[i][j][jj][jjj]<< " ";
            }
           cout <<",";
          }
          cout << endl;
	 	}
	 	cout << endl<< endl;
	}         */
	     cout << endl;


	 vector <vector <vector < vector <string> > > > Partitions;
	       Partitions.resize(PartTemp.size());
	       int h=0;
            while (h<PartTemp.size()) {
            Partitions[h].resize(PartTemp[h].size());
            int hh=0;
            while (hh<PartTemp[h].size()) {
			Partitions[h][hh].resize(PartTemp[h][0].size());
            int hhh=0;
            while (hhh<PartTemp[h][0].size()) {
            	Partitions[h][hh][hhh].resize(PartTemp[h][0][hhh].size());      //
            		hhh++;
            	}
            	hh++;
	            }
	            h++;
	           }

	           int u=0;
	           if (PartTemp[0].size()==1)  for(int i=0;i<=PartTemp[0][0][0].size()-1;i++) Partitions[0][0][0][i]=PartTemp[0][0][0][i];
	           u++;
	            while (u<PartTemp.size()) {
	            	int uu=0;
	            	while (uu<PartTemp[u].size()) {
	            		int uuu=0;
	            		while (uuu<PartTemp[u][uu].size()) {

	            	if ((uu==0)&&(uuu==0)&&(PartTemp[u][uu][uuu].size()==1)) {
	            		for(int i=0;i<=PartTemp[u][0].size()-1;i++) Partitions[u][0][i][0]=PartTemp[u][0][i][0];
	            		break;
	            		 }
	            	else if ((uu==0)&&(uuu==0)&&(PartTemp[u][uu][uuu].size()>1))
					  {
	            		for(int i=0;i<=PartTemp[u][0][0].size()-1;i++) Partitions[u][0][0][i]=PartTemp[u][0][0][i];
	            		 }

				    	uuu++;
	           }
	            	  	uu++;
	           }
	            	u++;
	           }

	             cout << endl;

/*	for(int i=0;i<=Partitions.size()-1;i++){
      for(int j=0;j<=Partitions[i].size()-1;j++) {
	     for(int jj=0;jj<=Partitions[i][j].size()-1;jj++) {
	       for(int jjj=0;jjj<=Partitions[i][j][jj].size()-1;jjj++) {
	                cout << Partitions[i][j][jj][jjj]<< " ";
            }
           cout <<",";
          }
          cout << endl;
	 	}
	 	cout << endl<< endl;
	}         */
	//cout << Partitions.size()<<endl;
int u1=1;
while (u1<Partitions.size()-1) {


	                int u3=0;
	            	int u2=1, u=u1;
	            	while (u2<Partitions[u1].size()) {
				//	cout << Partitions[u1].size()<<endl;

				   int uu=u2, uuu=0,dif=0;
				      while (u3<Partitions[u1][0].size()) {   //
	            		if ((u3>0) &&(u2==1)) for (int i=0; i<Partitions[u1][0][u3].size(); i++) Partitions[u1][0][u3][i]=PartTemp[u1][0][u3][i];
						uu=u2;                    //
	            		uuu=0;
	            		dif=0;
	            	while (uuu<PartTemp[u][uu].size()){
	            	int sim=0;
	            	int u22=0;
	            	while (u22<u2) {
	            		int u4=0;
	            		while (u4<Partitions[u1][u22][u3].size()) {
	            			int ww=0;
	            			while (ww<PartTemp[u][uu][uuu].size()){
	            			  if (Partitions[u1][u22][u3][u4]==PartTemp[u][uu][uuu][ww]) {
	            			     sim=1; break; }
	            			ww++;
	            			 }
	            			 if (sim==1) break;
	            			    	u4++;
	                               }
	                          if (sim==1) break;
	                          u22++;
							   	}
						   	if (u22==u2)
						   	{for (int i=0; i<PartTemp[u][uu][uuu].size(); i++) Partitions[u1][u2][u3][i]=PartTemp[u][uu][uuu][i];
							   dif=1; break;}  /// differents
							uuu++;	       //similaires
							}
						if ((dif==1)&&(u2<Partitions[u1].size()-1) ) break;  //
						else if (u2==Partitions[u1].size()-1) u2=1;

						u3++;
						}

	            	  	u2++;
	               }

	            	u1++;
	           }
	        return Partitions;
		     }

//////////////////////////////////////function for gbu partitions (nodes with more than 2 children); Input: vector of string tree iterators which label the child nodes

vector <vector <vector < vector <tree<string>::iterator> > > > TreePartiI (vector<tree<string>::iterator> &v) {
	// vector< vector<tree<string>::iterator> > vec2;
	int n;
	vector<vector<tree<string>::iterator> > combinations;
	list<tree<string>::iterator> lt;
    vector<vector<int> > gg;
    n=v.size();
	gg=IntPart(n);

    vector<vector< vector< vector<tree<string>::iterator> > > >  PartTemp;
    for(int i=0;i<gg.size();i++){
	   	vector< vector< vector<tree<string>::iterator> > >   PartTemp0;
	   	int lg; lg=gg[i].size()-1;
       for(int j=0;j<lg;j++) {
       	 if (gg[i][0]==1) lg=1;
       	 combAIt(combinations,v,n,gg[i][j],0,lt);
         vector< vector<tree<string>::iterator> > row2;
         for (int r = 0; r< combinations.size(); r++) {
		       vector<tree<string>::iterator> row;
	  	   for (int rr = 0; rr < combinations[r].size(); rr++) {
       	         row.push_back(combinations[r][rr]);
       	                              }
       	    row2.push_back(row);
			row.clear();
       	                   }
       	    PartTemp0.push_back(row2);
       	    row2.clear();
       	    combinations.clear();
                            }
            PartTemp.push_back(PartTemp0);
            PartTemp0.clear();
        }

 // initialization of the 4d tree string iterator matrix for graph-Aho partitions
 vector <vector <vector < vector<tree<string>::iterator> > > > Partitions;
	       Partitions.resize(PartTemp.size());
	       int h=0;
            while (h<PartTemp.size()) {
            Partitions[h].resize(PartTemp[h].size());
            int hh=0;
            while (hh<PartTemp[h].size()) {
			Partitions[h][hh].resize(PartTemp[h][0].size());
            int hhh=0;
            while (hhh<PartTemp[h][0].size()) {
            	Partitions[h][hh][hhh].resize(PartTemp[h][0][hhh].size());      //
            		hhh++;
            	}
            	hh++;
	            }
	            h++;
	           }

	           int u=0;
	           if (PartTemp[0].size()==1)  for(int i=0;i<=PartTemp[0][0][0].size()-1;i++) Partitions[0][0][0][i]=PartTemp[0][0][0][i];
	           u++;
	            while (u<PartTemp.size()) {
	            	int uu=0;
	            	while (uu<PartTemp[u].size()) {
	            		int uuu=0;
	            		while (uuu<PartTemp[u][uu].size()) {
	            	if ((uu==0)&&(uuu==0)&&(PartTemp[u][uu][uuu].size()==1)) {
	            		for(int i=0;i<=PartTemp[u][0].size()-1;i++) Partitions[u][0][i][0]=PartTemp[u][0][i][0];
	            		break;
	            		 }
	            	else if ((uu==0)&&(uuu==0)&&(PartTemp[u][uu][uuu].size()>1))
					  {
	            		for(int i=0;i<=PartTemp[u][0][0].size()-1;i++) Partitions[u][0][0][i]=PartTemp[u][0][0][i];
	            		 }

				    	uuu++;
	                 }
	            	  	uu++;
	              }
	            	u++;
	           }
     //   cout << endl;
 //cout << Partitions.size()<<endl;   /// partitions size
 int u1=1;
 while (u1<Partitions.size()-1) {

	                int u3=0;
	            	int u2=1, u=u1;
	            	while (u2<Partitions[u1].size()) {
				//	cout << Partitions[u1].size()<<endl;

				   int uu=u2, uuu=0,dif=0;
				      while (u3<Partitions[u1][0].size()) {   //
	            		if ((u3>0) &&(u2==1)) for (int i=0; i<Partitions[u1][0][u3].size(); i++) Partitions[u1][0][u3][i]=PartTemp[u1][0][u3][i];
						uu=u2;                    //
	            		uuu=0;
	            		dif=0;
	            	while (uuu<PartTemp[u][uu].size()){
	            	int sim=0;
	            	int u22=0;
	            	while (u22<u2) {
	            		int u4=0;
	            		while (u4<Partitions[u1][u22][u3].size()) {
	            			int ww=0;
	            			while (ww<PartTemp[u][uu][uuu].size()){
	            			  if (Partitions[u1][u22][u3][u4]==PartTemp[u][uu][uuu][ww]) {
	            			     sim=1; break; }
	            			ww++;
	            			 }
	            			 if (sim==1) break;
	            			    	u4++;
	                               }
	                          if (sim==1) break;
	                          u22++;
							   	}
						   	if (u22==u2)
						   	{for (int i=0; i<PartTemp[u][uu][uuu].size(); i++) Partitions[u1][u2][u3][i]=PartTemp[u][uu][uuu][i];
							   dif=1; break;}  /// differents
							uuu++;	       //similaires
							}
						if ((dif==1)&&(u2<Partitions[u1].size()-1) ) break;  //
						else if (u2==Partitions[u1].size()-1) u2=1;

						u3++;
						}

	            	  	u2++;
	               }

	            	u1++;
	           }
	        return Partitions;
		}

///////////////////////// function  to print on screen the string partitions
 void partshow(vector <vector <vector < vector <string> > > > & Partitions) {
	             cout << endl;

	for(int i=0;i<=Partitions.size()-1;i++){
      for(int j=0;j<=Partitions[i].size()-1;j++) {
	     for(int jj=0;jj<=Partitions[i][j].size()-1;jj++) {
	       for(int jjj=0;jjj<=Partitions[i][j][jj].size()-1;jjj++) {
	                cout << Partitions[i][j][jj][jjj]<< " ";
            }
           cout <<",";
          }
          cout << endl;
	 	}
	 	cout << endl<< endl;
	}
	}
/////////////////////////////////////////////////////////////////////////////
///////////////////////// function  to print on screen the string partitions  version iterateurs
 void partshowi(vector <vector <vector < vector <tree<string>::iterator> > > >& Partitions) {
	             cout << endl;

	for(int i=0;i<=Partitions.size()-1;i++){
      for(int j=0;j<=Partitions[i].size()-1;j++) {
	     for(int jj=0;jj<=Partitions[i][j].size()-1;jj++) {
	       for(int jjj=0;jjj<=Partitions[i][j][jj].size()-1;jjj++) {
	                cout <<(*Partitions[i][j][jj][jjj])<<" ";
            }
           cout <<",";
          }
          cout << endl;
	 	}
	 	cout << endl<< endl;
	}
	}
/////////////////////////////////////////////////////////////////////////////

unsigned long int fact1(int n)
{
	unsigned long int res;
    if (n == 0 || n == 1) {
        return 1;
    } else  if (n<0)  {
         return 0;
     } else
    {
        res = 1;
        for (int i = 1; i <= n; ++i)
        {
         res *= i;
        }
        return res;
    }
}

unsigned long int doublefact(int n)  // double factorial n!!= n*(n-2)*(n-4)*...

{
    int i;
	unsigned long int res=1;

	if (n == 0 || n == 1) {
        return 1;
    } else  if (n<0)  {
         return 0;
     }
	 else
    {
       for(int i=n;i>=1;i-=2)
       {
       res *=i;
       }
     }
       return res;
}

unsigned long int NLLRBtrees (int n)  // number of leaf labeled rooted binary trees (with n lebeled leaves): (2n-3)!!
 {
 	return doublefact((2*n)-3);
 	}

int bellNumber(int n)  //bell number using bell triangle:  number of partitions of a set.
{
   int bell[n+1][n+1];
   bell[0][0] = 1;
   for (int i=1; i<=n; i++)
   {
      // Explicitly fill for j = 0
      bell[i][0] = bell[i-1][i-1];

      // Fill for remaining values of j
      for (int j=1; j<=i; j++)
         bell[i][j] = bell[i-1][j-1] + bell[i][j-1];
   }
   return bell[n][0];
}

 // number of leaf labeled rooted binary trees (with n lebeled leaves): (2n-3)!! https://en.wikipedia.org/wiki/Double_factorial  https://en.wikipedia.org/wiki/Binary_tree
  // number of leaf labeled unrooted binary trees (with n labeled leaves): (2n-5)!!
  // n!!= 2exp(k)*k!  for all n=2k, k>=0  https://en.wikipedia.org/wiki/Double_factorial
  //n!!=(2k)!/(2exp(k)*k!) for all n=2k-1, k>=1;
/*unsigned int doublefactorial(unsigned int n)
  {
    if (n == 0 || n==1)
      return 1;
    return n*doublefactorial(n-2);
}*/


 unsigned long int NUBTree(int c)  //number of all unique unlabeled binary trees with n vertices Quora or catalan numbers   exponential complexity
  {
                                   // or number of all possible full binary trees with n leaves c(n-1)
  c=c-1;
  if(c<=1)
    return 1;
  unsigned long int sum=0;
  for(int k=0;k<c;k++)
   {
     sum += NUBTree(k)*NUBTree(c-k-1);
    }
   return sum;
  }

  unsigned long int NLBTree(int c)  //number of all unique labeled binary trees with n vertices Quora or catalan numbers   exponential complexity
  {
                                   //
  unsigned long int p;
  p=fact1(c);
  if(c<=1)
    return 1;
  unsigned long int sum=0;
  for(int k=0;k<c;k++)
   {
     sum += NUBTree(k)*NUBTree(c-k-1);
    }
   return sum*p;
  }




  // A dynamic programming based function to find nth  Geekforgeeks  quadratique complexity
// Catalan number
unsigned long int catalanDP(unsigned int n)
{
    // Table to store results of subproblems
    unsigned long int catalan[n+1];

    //vector<unsigned long int >  catalan[n+1];

    // Initialize first two values in table  catalan.push_back(1); catalan.push_back(1);
    catalan[0] = catalan[1] = 1;

    // Fill entries in catalan[] using recursive formula
    for (int i=2; i<=n; i++)
    {
        catalan[i] = 0;      //catalan.push_back(1);
        for (int j=0; j<i; j++)
            catalan[i] += catalan[j] * catalan[i-j-1];
    }

    // Return last entry
    return catalan[n];
}

/*
 * http://www.geeksforgeeks.org/program-nth-catalan-number/  lineal complexity
 */
// Returns value of Binomial Coefficient C(n, k)
unsigned long int binomialCoeff(unsigned int n, unsigned int k) {
    unsigned long int res = 1;

    // Since C(n, k) = C(n, n-k)
    if (k > n - k)
        k = n - k;

    // Calculate value of [n*(n-1)*---*(n-k+1)] / [k*(k-1)*---*1]
    for (int i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }

    return res;
}

// A Binomial coefficient based function to find nth catalan
// number in O(n) time
unsigned long int catalan(unsigned int n) {
    // Calculate value of 2nCn
    unsigned long int c = binomialCoeff(2 * n, n);

    // return 2nCn/(n+1)
    return c / (n + 1);
}

tree<string> NewickParser(string &newick) {
    tree<string>::iterator top;
    tree<string> tr;
	stack<tree<string>::iterator> itero;
    int i, y, c, found3,cc, op;
	found3= newick.find(";");
	if (found3==std::string::npos) cout<<"missing semicolon"<<endl;
	 else i=found3-1;
	 op=i;
	 cc=i-1;
	string pstring="R";
    string pdstring="P";

    while(i>=0)
	 {
	  c=0;
	  while (((i-c)>0)&&(newick[i-c]!=')')&&(newick[i-c]!=',')&&(newick[i-c]!='(')) c++; //   ,...) (....)  )...);
	   i=i-c;
	   if (newick[i] == ')')   //....)
	 	{
		  if (pstring=="R")	 {
		      if (c>0) itero.push(tr.insert(tr.begin(), newick.substr(i+1,c)));  // )phgytf;  push 1a
			      else itero.push(tr.insert(tr.begin(),pstring));		       //);    push 1b

			    pstring="F";
			    }
		 else	{

		     if (c>0) itero.push(tr.append_child(itero.top(), newick.substr(i+1,c))); // ...)a...)  push 2a ok
				      else if (c==0) itero.push(tr.append_child(itero.top(), pdstring)); // .....))    push 2b
				  }
		  }
		else if (newick[i] == '(') {
		        if (cc<op) {
			     if (c>0) tr.append_child(itero.top(), newick.substr(i+1,c));         // (a
			       else tr.append_child(itero.top(), pstring);               // (,
			       }
			       else if ((op-i)>1) {cout<<"error:label on the left"<<endl;  }

			 	op=i;
			 itero.pop();
		}
		else if (newick[i]==',') {
			  if (cc<op)   {    //if (newick[i+1]!='(') {
			  if (c>0) tr.append_child(itero.top(), newick.substr(i+1,c));     //  ...a,b)    a,(b,   a,de(b,  a,b,(b))  a,b)
				 else  tr.append_child(itero.top(), pstring);        //  ...,,)
			}
		else if (newick[i+1]!='(') {cout<<"error:label on the left"<<endl; }

			cc=i;
				}
		i--;
		}
		return tr;
    	}

bool Valid(char open,char close)
{
	static map<char, char> parentheses;
	parentheses['('] = ')';
	if(parentheses[open]==close) return true;
	return false;
}
bool ValidNewick(string tstring)// ValidNewick(string tstring)
{
	stack<char>  S;
	int foundf,founds;
	foundf=tstring.rfind(";");
	if (foundf==std::string::npos) return false;
	foundf=tstring.rfind(")");
	founds=tstring.find("(");
	tstring=tstring.substr(founds,foundf-founds+1);


	for (string::iterator it = tstring.begin(); it!=tstring.end(); ++it)
	{
		if((*it) == '(')
			S.push(*it);
		else if((*it)== ')')
		{

			if(S.empty() || !Valid(S.top(),*it))
				return false;
			else
				S.pop();
		}
	}
   return S.empty() ? true:false;
}

// Print everything under this root in a flat, bracketed structure.

void print_subtree_bracketed(const tree<string>& t, tree<string>::iterator iRoot, std::ostream& str)
	{
	if(t.empty()) return;
	if (t.number_of_children(iRoot) == 0) {
		str << *iRoot;
		}
	else {
		// parent

		str << "(";
		// child1, ..., childn
		int siblingCount = t.number_of_siblings(t.begin(iRoot));
		int siblingNum;
		tree<string>::sibling_iterator iChildren;
		for (iChildren = t.begin(iRoot), siblingNum = 0; iChildren != t.end(iRoot); ++iChildren, ++siblingNum) {
			// recursively print child
		  	print_subtree_bracketed(t,iChildren,str);
			// comma after every child except the last one
			if (siblingNum != siblingCount ) {
				str << ", ";
				}

			}
		str << ")";
		str << *iRoot;
		}
	}

void print_tree_bracketed(const tree<string>& t, std::ostream& str)
	{
	int headCount = t.number_of_siblings(t.begin());
	int headNum = 0;
	for(tree<string>::sibling_iterator iRoots = t.begin(); iRoots != t.end(); ++iRoots, ++headNum) {
		print_subtree_bracketed(t,iRoots,str);
		if (headNum != headCount) {
			str << std::endl;
			}
		}
	}


int main()
{

 //HACER VERSION CON PARTITION DE ITERADORES

	vector <vector <vector < vector <string> > > > Partitions;
	//vector <vector <vector < vector <tree<string>::iterator> > > > Partitions;
    //string vv[]={"a1","b1","b2","c1","d1"};
   // vector<string> v(&vv[0], &vv[0]+5);
    vector<string> v;
    //vector<tree<string>::iterator> v;

	string newick;
    tree<string> tu;
    newick="(v,(a,t,g),f)c;";

//	vector< vector<tree<string>::iterator> > polyit;
   	//vector<tree<string>::iterator> rowpolyit;

   vector< vector<string> > poly;
   vector <string> rowpoly;

	if (ValidNewick(newick)) {
	    tu=NewickParser(newick);
        print_tree_bracketed(tu, std::cout);
		cout<<endl; }

    tree<string>::iterator itt;
   	int lp=4;
   	cout<<endl;
   	for (int i= 3; i < lp; i++) {
   	 itt=tu.begin();
	  while(itt!=tu.end()) {
	   if (tu.number_of_children(itt)==i) {
		tree<string>::sibling_iterator sib=tu.begin(itt);
	    while(sib!=tu.end(itt)) {
         cout << (*sib) <<" ";
         rowpoly.push_back(*sib);
         ++sib;
                    }
         cout<<endl;
         poly.push_back(rowpoly);  //polytomies
         rowpoly.clear();
			             }
		   ++itt;
		           }

}




    return 0;
}

