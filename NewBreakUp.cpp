#include <algorithm>
#include <string>
#include <iostream>
#include <stack>
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

bool ValidParantheses(string tstring)
{
	stack<char>  S;
	string::iterator it = tstring.begin();
	for (; it!=tstring.end(); ++it)
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

}

template<class T>
void print_tree_bracketed(const tree<T>& t, std::ostream& str)
	{
	int headCount = t.number_of_siblings(t.begin());
	int headNum = 0;
	for(typename tree<T>::sibling_iterator iRoots = t.begin(); iRoots != t.end(); ++iRoots, ++headNum) {
		print_subtree_bracketed(t,iRoots,str);
		if (headNum != headCount) {
			str << std::endl;
			}
		}
	}


// Print everything under this root in a flat, bracketed structure.

template<class T>
void print_subtree_bracketed(const tree<T>& t, typename tree<T>::iterator iRoot, std::ostream& str)
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
		typename tree<T>::sibling_iterator iChildren;
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
		std::cout << (*it) << "  "<<tr.depth(it) << "  "<<tr.number_of_children(it)<< "  "<<tr.number_of_siblings(it)<< std::endl << std::flush;
		++it;
		}

		}

int main(int, char **)
   {
   tree<string> tr;
   tree<string>::iterator top, one, two, loc, banana;
   //string word, sword, racine,line="(B:0.2,yt,(C:0.3,rt45,D:0.4)E:0.5,U,hu,gt)F:45;";
   //string word, sword, racine,line="(B:0.2,yt,(C:0.3,rt45,D:0.4),U,hu,gt)F:0.123;";
    //string word, sword, racine, line="(B:0.2,yt,((C:0.3,rt45,D:0.4),U),hu,gt)F:0.123;";               //ok
   //string word, sword, racine,line="(B:0.2,yt,((C:0.3,rt45,D:0.4),U),hu,gt)F:0.123;";   ok
   //string word, sword, racine,line="(B:0.2,yt,(C:0.3,(rt45,uy7),D:0.4),U,hu,gt)F:0.123;";0ok
    //string word, sword, racine,line="(B:0.2,(tt,gt),(C:0.3,(rt45,uy7),D:0.4),U,hu,gt)F:0.123;"; ok
    //string word, sword, racine,line="(B:0.2,(tt,gt),(C:0.3,(uy7,(tf,gy)),D:0.4),U,hu,gt)F:0.123;"; //ok
    //string word, sword, racine,line="(B:0.2,(uy,er),(tt,gt),(C:0.3,(uy7,(tf,gy)),D:0.4),U,hu,gt)F:0.123;"; //ok
    //string word, sword, racine,line="(B:0.2,(uy,er),(tt,gt),(C:0.3,(uy7,(tf,gy)),D:0.4),U,hu,gt)F:0.123;"; //ok
     //string word, sword, racine,line="(B:0.2,(er),(tt,gt),(C:0.3,(uy7,(tf,gy)),D:0.4),U,hu,gt)F:0.123;";  //ok
      //string word, sword, racine,line="(,(,),(,),,,(C:0.3,(uy7,(tf,gy)),D:0.4),U,hu,gt)F:0.123;";
      //string word, sword, racine,line="(B:0.2,(er),(tt,gt),(C:0.3,(uy7,(tf,gy)rte),D:0.4),U,hu,gt)F:0.123;";
      //string word, sword, racine,line="(B:0.2,(er),(tt,gt),(C:0.3,(uy7,(tf,gy)rte),D:0.4),U,hu,gt)F:0.123;";

		//string word, sword, racine,line="(a1,(c2,(b1,a2)))32;";
        //string word, sword, racine,line="((a1,a2,a3),(c2,(b1,a2)));";
        //string word, sword, racine,line="(d1,(c1,c2,(a1,b1)));";

    string word, sword, racine, newick;
    newick="((w),t,(u),u,y)e;";
    int  c=0, foundc,found0, found,found1,found2, found11,found3= newick.find(";"), found4;
    stack<tree<string>::iterator> itero;
    if (found3!=std::string::npos) {
      found=newick.rfind(")",found3);     // found: ) 33
      racine=newick.substr(found+1,found3-found-1);
    if (racine.length()>0) itero.push(tr.insert(tr.begin(), racine));
     else  itero.push(tr.insert(tr.begin()," "));
       }

  while(found!=0) {
	found2 = newick.rfind(")", found-1);            //found2 ")"    25
	found1 = newick.rfind("(", found-1);
	//cout<<found1<<" "<<found2<<endl;
	if (((found1==std::string::npos)&&(found2!=std::string::npos))||((found2!=std::string::npos)&&(found1!=std::string::npos)&&(found2>found1)))
	{
		foundc=newick.find(",",found2);
	    //cout<<foundc<<" "<<found2<<endl;                   //  ),(    coma	//

		if ((foundc!=std::string::npos)&&(foundc<found)) {      //"(B:0.2,(tt,gt),(C:0.3,(rt45,uy7),D:0.4),U,hu,gt)F:0.123;"
		word=newick.substr(foundc+1,found-foundc-1);             //"(A:0.1,B:0.2,(C:0.3,D:0.4)E:0.5,U)F:0.123;"  found:( )  u				                                     //),)    ),(
		//cout<<endl<<word<<endl;                                //U line="(B:0.2,yt,((C:0.3,rt45,D:0.4),U),hu,gt)F:0.123;"
		found4=word.find(",");	found0=0;
		if ((foundc-found2==1)&&(found-foundc==1)) itero.push(tr.append_child(itero.top(), "R0"));
		else  {
		if (found4==std::string::npos) tr.append_child(itero.top(), word);  //
		else {
		//cout<<endl<<found4<<endl;   //U
		while(found4!=std::string::npos) {
			sword=word.substr(found0,found4-found0);
			//cout<<endl<<sword<<endl;
			//cout<<endl<<found4<<endl;
			found0=found4+1;
			found4=word.find(",",found0);
			//cout<<endl<<found4<<endl;
			if ((found4-found0)==0) tr.append_child(itero.top(),"p1");
			else tr.append_child(itero.top(), sword);
		    }

		if (found4==std::string::npos) tr.append_child(itero.top(), word.substr(found0,word.length()-found0));
		 }

		   word=newick.substr(found2+1,foundc-found2-1);      //  )E:0.5
		    //cout<<endl<<word<<endl;
	    	if (word.length()>0)  itero.push(tr.append_child(itero.top(), word));
	    	else itero.push(tr.append_child(itero.top(), "p2"));
		 } }
		 else {
		//cout<<endl<<found2<<" "<<found<<" "<<found3<<endl;
	 	if ((found-found2-1)>0) word=newick.substr(found2+1,found-found2-1);        //  )),  g)F:9),  "(B:0.2,(tt,gt),(C:0.3,(rt45,uy7),D:0.4),U,hu,gt)F:0.123;"
//		 	else word=line.substr(found2+1,found-found2);
		 	//word=newick.substr(found2+1,found-found2-1);
		 	//cout<<endl<<word<<endl;
		 	if (word.length()>1)  itero.push(tr.append_child(itero.top(), word));
	    	else itero.push(tr.append_child(itero.top(), "p3"));
		 	//cout<<endl<<word<<endl;
		  }
	    //cout<<endl<<word<<endl;  //E:0.5
		c=0;
		found=found2;
	}
	if (((found1!=std::string::npos)&&(found2==std::string::npos))||((found2!=std::string::npos)&&(found1!=std::string::npos)&&(found1>found2)))
	 {
	    word=newick.substr(found1+1,found-found1-1-c);     //"(B:0.2,yt,(C:0.3,(rt45,uy7),D:0.4),U,hu,gt)F:0.123;";
	   // found11 = newick.rfind("(", found2-1);
	    //if
	cout<<endl<<word<<" "<<c<<endl;
	//	word=line.substr(foundc+1,found-foundc-1-c);  //"(A:0.1,B:0.2,(C:0.3,D:0.4)E:0.5,U)F:0.123;" "(w,t,(u),u,(r))e;"; "(w,t,(u),u,y)e;"; ok
		found4=word.find(",");

		found0=0;

	cout<<endl<<found4<<" "<<c<<endl;

		while(found4!=std::string::npos) {
			sword=word.substr(found0,found4-found0);
			found0=found4+1;
			found4=word.find(",",found0);
			cout<<endl<<found4<<" "<<found0<<endl;
			if ((found4-found0)==0) tr.append_child(itero.top(),"r");
			else tr.append_child(itero.top(), sword);

		    }
		if (found4==std::string::npos) tr.append_child(itero.top(), word.substr(found0,word.length()-found0));
	    itero.pop() ;
	 c=1;
	 found=found1;
	 }
     //cout<<endl<<found<<endl;
	}
   /*found1=found3;

     while((found1>=0)) {
     	found3 = newick.rfind(")", found3-1);            //found2 ")"    25
	    found1 = newick.rfind("(", found1-1);
	   //if (found3==std::string::npos) found3=0;
	    if (found3!=std::string::npos)  {
          if ((found3>found1))   //(),
            {
            foundc=newick.find(",",found3);
             if	((foundc!=std::string::npos)&&(foundc<found))
             {
             	word=.substr(foundc+1,found-foundc-1);
              	found4=word.find(",");
              	if ((foundc-found3==1)&&(found-foundc==1)) itero.push(tr.append_child(itero.top(), "R0"));


             	 }

            found=found3;
           }
          else if ((found1>0)&&(found1>found3))
              {

		   itero.pop() ;
          found11=found1;
         }
         }
		 else (found1>0) {


         found11=found1;
          }

      }  */

     print_tree_bracketed(tr, std::cout);
     //cout<<endl;
    // print_tree(tr, tr.begin(), tr.end());





   }

