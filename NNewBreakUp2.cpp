#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include <stack>
#include <unordered_set>
#include <map>
#include "tree.hh"
//#include "tree_util.hh"

using namespace std;

// Function to check whether two characters are opening
// and closing of same type.
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

int MaxDepth(string treeString)
{
	int currMax = 0; // current count
    int max = 0;    // overall maximum count
	for(int i =0;i<treeString.length();i++)
	{
		if(treeString[i] == '(')
		{	currMax++;
              if (currMax> max)
                max = currMax;
                 }
		else if(treeString[i] == ')')
		{
            if (currMax>0)
                currMax--;
            else
                return -1;
		}
	}
return max;
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


void printFileNewick(const tree<string>& t, tree<string>::iterator iRoot, ofstream& str)
	{
	if(t.empty()) return;
	if (t.number_of_children(iRoot) == 0) {
		str << *iRoot;
		}
	else {
		str << "(";
		// child1, ..., childn
		int siblingCount = t.number_of_siblings(t.begin(iRoot));
		int siblingNum;
		tree<string>::sibling_iterator iChildren;
		for (iChildren = t.begin(iRoot), siblingNum = 0; iChildren != t.end(iRoot); ++iChildren, ++siblingNum) {
		  	printFileNewick(t,iChildren,str);
			if (siblingNum != siblingCount ) {
				str << ", ";
				}

			}
		str << ")";
		str << *iRoot;
		}
	}

void printFileTree(const tree<string>& t, ofstream& str)
	{
	int headCount = t.number_of_siblings(t.begin());
	int headNum = 0;
	for(tree<string>::sibling_iterator iRoots = t.begin(); iRoots != t.end(); ++iRoots, ++headNum) {
		printFileNewick(t,iRoots,str);
		if (headNum != headCount) {
			str << std::endl;
			}
		}
	}



void print_tree(const tree<std::string>& tr, tree<std::string>::pre_order_iterator it, tree<std::string>::pre_order_iterator end)
	{
	tree<string>::iterator  loc;
	if(!tr.is_valid(it)) return;
	int rootdepth=tr.depth(it);
	std::cout << "-----" << std::endl;
	cout << tr.depth(it) <<endl;
	while(it!=end) {
		for(int i=0; i<tr.depth(it)-rootdepth; ++i)
			std::cout << "  ";
		std::cout << (*it) <<"  "<<tr.depth(it) <<"  "<<tr.number_of_children(it)<< "  "<<tr.number_of_siblings(it)<< std::endl << std::flush;
		++it;
		}

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

////////////////////////////// breakUp part
// for using before the function TripletsClades
vector< vector<tree<string>::iterator> > InternalEdges (tree<string>& tu) {

	vector< vector<tree<string>::iterator> > vec2;
	tree<string>::iterator li,ite;
	vector<tree<string>::iterator>  row;
	ite=tu.begin();

	while(ite!=tu.end()) {
		if ((tu.number_of_children(ite)>0)&&(ite!=tu.begin()) ) {
		     li=tu.parent(ite);
		     row.push_back(li); //mother
		      //cout<<*li<<" ";
		     row.push_back(ite);
		      //cout<<*ite<<endl;
		      vec2.push_back(row);
		      row.clear();
		           }
		           ite++;
	          }
	return vec2;  //vec2 matrix bi-dimensional (mother, child)
	}

    /////////////////////////////////////////////////// //pour la decomposition en triplets
   //
  void TripletClades (vector< vector<tree<string>::iterator> > vec2, vector<vector<string> >& children, vector<vector<string> >& childrenP, tree<string>& tu) {
     tree<string>::leaf_iterator lite,llite;
	 vector<string> row1;
	 vector<string> row2;
	 //cout<<vec2.size()<<endl;
        for (int i= 0; i < vec2.size(); i++) {

    	    lite=tu.begin_leaf(vec2[i][1]); //child
    	    	while(lite!=tu.end_leaf(vec2[i][1])){
    	    	row1.push_back(*lite);
                lite++;
                       	}
                children.push_back(row1); //leaves or clades of children
				row1.clear();

             llite=tu.begin_leaf(vec2[i][0]); //mother
                while(llite!=tu.end_leaf(vec2[i][0])){
                	int u=0;
                  	while ((u<children[i].size())&&(*llite!=children[i][u])) u++; //leaves which are not included in children
                	if (u==children[i].size()) row2.push_back(*llite);        	  // if they are not included
     	   	      llite++;
                       	}
				 childrenP.push_back(row2);
				row2.clear();
           //          cout<<children[i].size()<<endl;
            		}
            		}

void printSClades (vector<vector<string> >& children)   {
    for(int i=0;i<children.size();i++) {
      for(int ii=0;ii<children[i].size();ii++) {
      cout<<children[i][ii]<<" ";
       }
       cout<<endl;
    	}
    		}

	/////////////////////////////////////////////
	//seulement pour les triplets
	//construction of triplets from children and childrenP (TripletClades: vec2->children +childrenP) stem from one tree
vector<tree<string> > TripletBreakUp (vector< vector<tree<string>::iterator> >& vec2, tree<string>& tu) {
	    vector<vector<string> > children;
        vector<vector<string> > childrenP;

	   vector<tree<string> > triplets;
	   TripletClades (vec2, children, childrenP, tu) ;

		tree<string>::iterator tw, on;
	   for (int i= 0; i < children.size(); i++) {
	     //cout<<i<<endl;
	     for (int ii= 0; ii < childrenP[i].size(); ii++) {
	     	 string s0=(childrenP[i][ii]);

	     	  for (int iii= 0; iii < children[i].size(); iii++) {
	     	  	  string s1=(children[i][iii]);
	     	       for (int r= iii+1; r < children[i].size(); r++) {
	     	       	  string s2=(children[i][r]);
	     	       	  tree<string> tr;
						   string str=s0+s1+s2;
                           on=tr.insert(tr.begin(), str); //root of tr, labeled with s0 s1 s2
                           tr.append_child(on, s0);       //leaf connected to the root
                           string str1=s1+s2;
                           tw=tr.append_child(on, str1);
                           tr.append_child(tw, s1);  // leaf of the fork
						   tr.append_child(tw, s2);   // leaf of the fork
                           triplets.push_back(tr);
	     	                                    	}
	   	               	}
						}

							}
	return triplets;
	}
 //
	 void ArbreSClades (vector< vector<tree<string>::iterator> > vec2, vector<vector<string> >& childrens, vector<vector<string> >& childrenPs, tree<string>& tu) {
	 vector<string> row1s;
	 vector<string> row2s;
	 tree<string>::leaf_iterator lites,llites;
	 //cout<<vec2.size()<<endl;
        for (int i= 0; i < vec2.size(); i++) {

    	    lites=tu.begin_leaf(vec2[i][1]);

    	    	while(lites!=tu.end_leaf(vec2[i][1])){
    	    	row1s.push_back(*lites);
				 lites++;
                       	}
                childrens.push_back(row1s); //leaves or clades of children
				row1s.clear();

           tree<string>::sibling_iterator sib=tu.begin(vec2[i][0]);

		   while(sib!=tu.end(vec2[i][0])) {
		   	  if ((tu.number_of_children(sib)==0)&&(sib!=vec2[i][1]))
		   	      row2s.push_back(*sib);
		   	   else if ((tu.number_of_children(sib)>0)&&(sib!=vec2[i][1])){
		   	    llites=tu.begin_leaf(sib);
		   	    row2s.push_back(*llites);
		   	     }
                   ++sib;
                    }

				 childrenPs.push_back(row2s);
				row2s.clear();
           //          cout<<children[i].size()<<endl;
            		}
            	}

///////////////////////////////////////////////
	// pour la decomposition en arbresS microarbres with polytomies and one internal branch
   	vector<tree<string> > arbreSBreakUp (vector< vector<tree<string>::iterator> >& vec2, tree<string>& tu) {

   		vector<vector<string> > childrens;
        vector<vector<string> > childrenPs;
//   	 tree<string>& tu
	    vector<tree<string> > arbresS;

		ArbreSClades (vec2, childrens, childrenPs, tu) ;
	    tree<string>::iterator mo, to;

	   for (int i= 0; i < childrens.size(); i++) {
	     //cout<<i<<endl;
	     	 string s0=(childrenPs[i][0]);
			 string s00=(childrenPs[i][0]);
	     	 string s1=(childrens[i][0]);

	     	 for (int iii= 1; iii < childrenPs[i].size(); iii++) {
	     	  	  s0=s0+childrenPs[i][iii];
	     	      	}

	     	  for (int iii= 0; iii < childrens[i].size(); iii++) {
	     	  	    s0=s0+childrens[i][iii];
	     	  	    if ((iii+1)<childrens[i].size()) s1=s1+childrens[i][iii+1];
	     	      	}
	     	       	  tree<string> tr;
                           mo=tr.insert(tr.begin(), s0);

				for (int iii= 0; iii < childrenPs[i].size(); iii++) {
	     	  	         tr.append_child(mo, childrenPs[i][iii]);
	     	      	                                 }
                           to=tr.append_child(mo, s1);
                    for (int iii= 0; iii < childrens[i].size(); iii++) {
	     	  	         tr.append_child(to, childrens[i][iii]);
	     	      	                                 }
         arbresS.push_back(tr);

							}
		return arbresS;
								}
///////////////////////////////////////// for printing triplets arbres	 printFileTree
void PrintStrees(vector<tree<string> >& trees) {
	int i=0;
    while (i<trees.size())  {
	print_tree_bracketed(trees[i], std::cout);
	cout<<endl;
	i++;
	          }
	}

void PrintFtrees(vector<tree<string> >& trees, string filename="tripletes.txt") {
   ofstream fout(filename.c_str());
   if (!fout) {
      cerr << "error: open file for output failed!" << endl;
      abort();  // in <cstdlib> header
   }
	int i=0;
    while (i<trees.size())  {
	printFileTree(trees[i], fout);
	fout<<"; ";
	i++;
	          }
	}

///////////////// for parsing many trees in newick format
 vector<tree<string> > NewickTreesParser (string &newickL) {
    vector<tree<string> > TreeNewickArray;
    int foundf, foundp;
    string newick;
    foundp=0;
    foundf=newickL.rfind(";"); //rfind
	while (foundf!=std::string::npos)  {
		if (foundp>0) {
		 newick=newickL.substr(foundf+1,foundp-foundf+1);
		 if (ValidNewick(newick)) {
		 TreeNewickArray.push_back(NewickParser(newick));
		  }
		 }
		foundp=foundf;
		foundf=newickL.rfind(";", foundp-1); //rfind
    }
    newick=newickL.substr(0,foundp-foundf+1);
	if (ValidNewick(newick)) TreeNewickArray.push_back(NewickParser(newick));
	return TreeNewickArray;
	 }
	 // triplet decomposition of several trees, output: triplets in a 2d matrix of triplets, each row: triplets from one tree
  vector<vector<tree<string> > > TripletCollection (string& newickL) {
  	vector< vector<tree<string>::iterator> > vec2;
     vector<tree<string> > TreeNewickArray;
    TreeNewickArray=NewickTreesParser(newickL);
    vector<vector<tree<string> > > MTreeNewickArray;
    for(vector<tree<string> >::iterator it = TreeNewickArray.begin(); it != TreeNewickArray.end(); ++it)
	   {
	  vector<tree<string> > triplets1;
      vec2=InternalEdges(*it);
      triplets1=TripletBreakUp (vec2,(*it));
      vec2.clear();
      MTreeNewickArray.push_back(triplets1);
	  triplets1.clear();
                    }
    return MTreeNewickArray;
     }

// function to convert gene trees to synteny trees, each
vector<tree<string> > Synteny2TreeParser (string &Syntenies, string &trees) {

   unordered_set<string> SynteniesHtable;  //table of syntenies, each row is a set of orthologous/paralogous syntenies
    int foundp, foundf, f, pf;
    foundp=0;
    foundf=Sintenies.find(","); //rfind
    while (foundf!=std::string::npos)  {
       SynteniesHtable.insert(Syntenies.substr(foundp,foundf-foundp));
       foundp=foundf;
       foundf=Sintenies.find(",", foundp+1);
		if (foundf==std::string::npos) {
               f=Sintenies.find(";", foundp+1);
               SynteniesHtable.insert(Syntenies.substr(foundp,f-foundp));                                         }
		                //rfind
          }
   vector<tree<string> > TreeNewickArray;
   TreeNewickArray=NewickTreesParser(trees);    // iterator itr loops from begin() till end()

   for(vector<tree<string> >::iterator it = TreeNewickArray.begin(); it != TreeNewickArray.end(); ++it)
	    {
            tree<string> ::leaf_iterator lite;
            lite=(*it).begin_leaf(); //child
            while(lite!=(*it).end_leaf()){
                  unordered_set<string> :: iterator itr;
                 for (itr = SynteniesHtable.begin(); itr != SynteniesHtable.end(); itr++)
                   if ((*itr).find(*lite)!=std::string::npos) break;
                 if (itr != SynteniesHtable.end()) {
                     string str0, str2="";
                     pf=(*itr).find(*lite);
                     if (pf!=0){
                     str0=(*itr).substr(0,pf);
                     str2=str0+(*lite);
                             	}
                     str0=(*itr).substr(pf+(*lite).length(),(*itr).length()-pf-(*lite).length());
                     str2=str2+str0;
                     (*it).replace(lite, str2);
                                 	}
                  lite++;
                       	}
                //leaves or clades of children
            	}
   return TreeNewickArray;
    }




      // triplet decomposition of several trees, output: triplets from all trees in a vector 1d, the repeated triplets are eliminated
	  // inside the methods:  NewickTreesParser InternalEdges and TripletBreakUp are used
	vector<tree<string> >  FTriBreakUp (string& newickL)   {

	 vector< vector<tree<string>::iterator> > vec2;
     vector<tree<string> > TreeNewickArray;
     TreeNewickArray=NewickTreesParser(newickL);
     vector<tree<string> >  MTreeNewickArray1d;
     //cout<<TreeNewickArray.size()<<endl;  ///////////////////
    for(vector<tree<string> >::iterator it = TreeNewickArray.begin(); it != TreeNewickArray.end(); ++it)
	    {
	    vector<tree<string> > triplets1;
        vec2=InternalEdges(*it);
        triplets1=TripletBreakUp(vec2,(*it));
        //cout<<triplets1.size()<<endl;   /////////////////
        vec2.clear();
    if (it==TreeNewickArray.begin()) {
    for(int i=0; i<triplets1.size(); ++i) MTreeNewickArray1d.push_back(triplets1[i]);
     //cout<<triplets1.size();             /////////////////////
	                    }
    else
	{
    int kk=0;
    while (kk<triplets1.size()) {
       int k=0;
       tree<string>::iterator atree=triplets1[kk].begin();
       while (k<MTreeNewickArray1d.size()) {
	       tree<string>::iterator btree=MTreeNewickArray1d[k].begin();
	       if ((*btree).size()==(*atree).size()) {
	        while((btree!=MTreeNewickArray1d[k].end())&&((*atree)==(*btree))) {
		       ++atree;
			   ++btree;
			                }
					if (btree==MTreeNewickArray1d[k].end())  break;
	                            }

	                k++;
	                            }
	                    if (k==MTreeNewickArray1d.size()) MTreeNewickArray1d.push_back(triplets1[kk]);
	                    kk++;
	                     }
	       }

    }
    return MTreeNewickArray1d;
    }

int main(int, char **)  {

       string newick;
       tree<string> tu;
	   int foundf, foundp,d;
       vector<tree<string> > triplets1, triplets,arbres;
       vector< vector<tree<string>::iterator> > vec2;
       vector<tree<string> > TreeNewickArray;
	   vector<tree<string> >::iterator it;
	  // newick="(a1,(a2,(c2,c3,c4)p1)p2);"; //ok
	    //newick="(a1,(c2,c1,(b1,b2)p1)p2);"; //ok
	  //  newick="((a1,a2),((b1,b2),,(b3,b4)));";//ok


  tu=NewickParser(newick);

	if (ValidNewick(newick)) {
        print_tree_bracketed(tu, std::cout);
		cout<<endl; }

    cout<<endl;

    string newickL;
   string line;
   /*string filename = "tripletes.txt";
   ofstream fout(filename.c_str());
   if (!fout) {
      cerr << "error: open file for output failed!" << endl;
      abort();  // in <cstdlib> header
   }*/
   //out.open("results.txt");
   string filename = "pesos.txt";
   ifstream myfile ("sample.txt");
if (myfile.is_open())
  {
    while ( getline (myfile,newickL) )
    {
      TreeNewickArray=FTriBreakUp (newickL);
      PrintFtrees(TreeNewickArray, "tripletes.txt");
      PrintStrees(TreeNewickArray);

    }
    myfile.close();
  }
  else cout << "Unable to open file";



       }
