#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include "tree.hh"
//#include "tree_util.hh"

using namespace std;

///// 1 construir lista de leaves no repetidas...  input: listTree, output: listLabels

vector<string> getLeafLabels(vector< vector<tree<string> > >& PartTree, int y)
 {
   vector<string> listLabels;
   tree<string>::iterator it;
   for (int i= 0; i < PartTree[y].size(); i++) {
		it=PartTree[y][i].begin();
		tree<string>::leaf_iterator lii=PartTree[y][i].begin_leaf(it);
	 while(lii!=PartTree[y][i].end_leaf(it)) {
			 listLabels.push_back(*lii);
			 ++lii;
			        }
     	}
     sort(listLabels.begin(), listLabels.end());
     listLabels.erase(unique(listLabels.begin(), listLabels.end() ), listLabels.end());
    return listLabels;
 	}

//// 2 show labels

void printScrLabels(const vector<string> & listLabels) {
 int lL=listLabels.size();
  for (int i= 0; i <lL; i++) {
  cout<<listLabels[i]<<" ";
     }
  }

///// 3 construccion de lista de arcos internos: pares de nodos internos padres-hijos input: listTree, output: vec2
 // construir lista  pares  para tripletes: matriz 2d; para arboles en general: matriz 3d

vector< vector<tree<string>::iterator> > IntEdges(const vector< vector<tree<string> > >& PartTree, int y) {
 vector< vector<tree<string>::iterator> > vec2;
 tree<string>::iterator ite,li;
 //vector< vector<string > > vec2;
 for (int i= 0; i < PartTree[y].size(); i++) {
 vector<tree<string>::iterator> row;
 //vector<string> row;
 ite=PartTree[y][i].begin();
	while(ite!=PartTree[y][i].end()) {
		if ((PartTree[y][i].number_of_children(ite)>0)&&(ite!=PartTree[y][i].begin()) ) {
		     li=PartTree[y][i].parent(ite);
		     row.push_back(li);
		      //cout<<*li<<" ";
		     row.push_back(ite);
		      //cout<<*ite<<endl;
                                  }
		++ite;
		             }
	vec2.push_back(row); 	//pares padre-hijo internos por arbol
    row.clear();
   	}
   	return vec2;
  }
     ///// 4 clados de nodos internos hijos, input: listTree, vec2, output: children
   // children  arbreXenfantXhijos  para arboles tripletes
  vector<vector<string> >  TriChClades(const vector< vector<tree<string> > >& PartTree, const vector< vector<tree<string>::iterator> >& vec2, int y) {

    tree<string>::leaf_iterator ite;
    vector<vector<string> > children;
         for (int i= 0; i < PartTree[y].size(); i++) {
            children.push_back(vector<string> ());
    	    ite=PartTree[y][i].begin_leaf(vec2[i][1]);
			//cout<<*ite<<" ";
    	    	while(ite!=PartTree[y][i].end_leaf(vec2[i][1])){
    	          children[i].push_back(*ite);
				 //cout<<*ite<<" ";
     	   	      ++ite;
                       	}
           //          cout<<children[i].size()<<endl;
            		}
            		return children;
            	}
      /////
    ///// 5 clados de nodos internos padres, input: listTree, vec2, children, output: Pchildren
        // Pchildren  arbolXpadreXhijos tripletes, para tripletes: vector; para arboles en general: matriz 3 d
 vector<string> TriRClades(const vector< vector<tree<string> > >& PartTree, const vector< vector<tree<string>::iterator> >& vec2, const vector<vector<string> >& children, int y) {
    vector<string>  Pchildren;
    tree<string>::iterator ite;
    for (int i= 0; i < PartTree[y].size(); i++) {
		 	ite=PartTree[y][i].begin_leaf(vec2[i][0]);
			while(ite!=PartTree[y][i].end_leaf()) {
			int yy=0;
			while ((yy<2)&&(*ite!=children[i][yy])&&(PartTree[y][i].number_of_children(ite)==0)) yy++; // los iteradores de leaves no funcionan por eso anadi la tercera condicion
			//cout<<endl<<y<<" "<<vec3[iii].size()<<endl;
			if (yy==2)  {
			Pchildren.push_back(*ite);
			//cout<<*ite<<endl;
			}
	           	++ite;
			 }
              		}
              		return Pchildren;
              }

   /*void TriClades(const vector< vector<tree<string> > >& PartTree, int y) {

   	vector< vector<tree<string>::iterator> > vec2;
   	 vector<vector<string> > children;
   	 vector<string> Pchildren;

   	 vec2=IntEdges(listTree);
     TriChClades(listTree, vec2, children);
     Pchildren=TriRClades (listTree, vec2, children);

     }*/

 /////  listree vec2 children pchildren

      ///// 6 formar grapho con clados hijos de nodo interno hijo, input: children, output: Mbgraph
    vector< vector<string > > GraphBuildA(const vector<vector<string> >& children) {

	vector< vector<string > > Mbgraph;
	vector<string > bgraph;

    bgraph.push_back(children[0][0]);
    bgraph.push_back(children[0][1]);
    Mbgraph.push_back(bgraph);

    int c=0,j=0, i=0,jj=0;
    for (int i= 1; i < children.size(); i++)  {
    c=0;j=0; jj=0;
     while (j<Mbgraph.size()){
     jj=0;
      while (jj<Mbgraph[j].size()){
       if (((children[i][0]==Mbgraph[j][jj+1])||(children[i][0]==Mbgraph[j][jj]))||((children[i][1]==Mbgraph[j][jj])||(children[i][1]==Mbgraph[j][jj+1]))   )
    		{
      			    // pour v v; v f; f v;
				  if (!(((children[i][0]==Mbgraph[j][jj+1])||(children[i][0]==Mbgraph[j][jj]))&&((children[i][1]==Mbgraph[j][jj])||(children[i][1] == Mbgraph[j][jj+1]))))
    	          {
     	               c=1;   // vf; fv
                      } else {
                  c=2; } // vv
				  break;
              }
              jj=jj+2;
                        }
				  if (c==1||c==2) break;
				  j++;
                   }

        if (c==0) {
           Mbgraph[++j].push_back(children[i][0]);
    	   Mbgraph[j].push_back(children[i][1]);
                 }
         else if (c==1){
            Mbgraph[j].push_back(children[i][0]);
    		Mbgraph[j].push_back(children[i][1]);
    			   }
       }

       return Mbgraph;
	    }
     ///// listree vec2 children pchildren MbgraphCh
	 ///// 7 completar grafo con hijos-hojas de nodos raices, input: Pchildren, Mbgraph, output: Mbgraph
	void GraphBuildB(const vector<string>& Pchildren, vector< vector<string > >& Mbgraph) {
	vector<vector<string> >::iterator r;
    vector<string>::iterator rr;
    int c;

    int ii, Ls=Mbgraph.size();
    vector<string> componente;

    for (int i= 0; i < Pchildren.size(); i++)  {
	//anadir componentes de un solo punto
	 c=0;
	 for (r = Mbgraph.begin(); r != Mbgraph.end(); r++) {
       for (rr = r->begin(); rr != r->end(); rr++) {
        if (Pchildren[i]==(*rr)) {c=1; break;}
                                                   }
        if (c==1) break;
                                               }

	 if (c==0) {
	            componente.push_back(Pchildren[i]);
	            Mbgraph.push_back(componente);
				componente.clear();
				}
   		//conteo de arboles por particion
			//si tamano es dos, dos hijos
			//si tamano uno, un hijo
			// si no hay arboles en la particion, y mas de dos, entonces tantos hijos como nodos diferentes
                  }
		 }

	void printScrGraph(const vector< vector<string > > & Mbgraph) {
	 ///// 9 showing graphe
	 vector<vector<string> >::const_iterator r;
     vector<string>::const_iterator rr;

	  for (r = Mbgraph.begin(); r != Mbgraph.end(); r++) {
        for (rr = r->begin(); rr != r->end(); rr++) {
         cout<<(*rr)<<" ";
         }
        cout<<endl;
             }
			 }
	void printScrGraphS(const vector<vector< vector<string > > >& MMbgraph) {
	vector<vector<vector<string> > >::const_iterator r;
     vector<vector<string> >::const_iterator rr;
       vector<string> ::const_iterator rrr;

	  for (r = MMbgraph.begin(); r != MMbgraph.end(); r++) {
	  	for (rr = r->begin(); rr != r->end(); rr++) {
        for (rrr = rr->begin(); rrr != rr->end(); rrr++) {
       //  cout<<(*rrr)<<" ";
         }
       // cout<<endl;
             }
         //  cout<<endl;
		 //  cout<<endl;
            }
	}

	 // 8 reducir graphe de arcos por componente conexo a graphe de vertices por componente conexo, input Mbgraph, output: Mbgraph
   	 void E2VGraph(vector< vector<string > > & Mbgraph)
		{
	      int i=0;
          while (i<Mbgraph.size()) {
		    sort(Mbgraph[i].begin(), Mbgraph[i].end());
            Mbgraph[i].erase(unique(Mbgraph[i].begin(), Mbgraph[i].end() ), Mbgraph[i].end());
            i++;
		    }
		 }
     ////
    vector< vector<string > > GraphBuild(const vector<string>& Pchildren, const vector<vector<string> >& children) {

	   vector< vector<string > > Mbgraph;

	    Mbgraph=GraphBuildA(children);
	    GraphBuildB(Pchildren, Mbgraph);
	    E2VGraph(Mbgraph);

	 return Mbgraph;
	  }

  TreePartition(vector< vector<string > >& Mbgraph, vector< vector<tree<string> > >& PartTree, unsigned int y, unsigned int h) {

       //vector<pair<unsigned int, unsigned int> >& index,
       vector<tree<string> > list;
	   tree<string>::iterator it;
	   bool growth=false;
       unsigned int ii, c;

       // indice del componente y el numero de arboles
       ii=0;
          while (ii<Mbgraph.size()) {
          	unsigned int iii=0;
          	if (Mbgraph[ii].size()>=3){
             for (unsigned int i= 0; i < PartTree[y].size(); i++) {
	         	it=PartTree[y][i].begin(); c=0;
	         	tree<string>::leaf_iterator lii=PartTree[y][i].begin_leaf(it);
	            while(lii!=PartTree[y][i].end_leaf(it)) {
			       iii=0;
			       while((iii<Mbgraph[ii].size())&&((*lii)!=Mbgraph[ii][iii])){ iii++; }
			          if (iii<Mbgraph[ii].size()) c=c+1;
			          ++lii;
			                    }
		           if (c==3)	{
				                    list.push_back(PartTree[y][i]);
									 }
		                          }
				//if (list.size()>0) index.push_back(make_pair(h,ii));
				PartTree.push_back(list);
				list.clear();
		                         	}
 	        ii++;
       	                }

		 // if (PartTree.size()>lp)	growth=true;
		  //return growth;
		  }


	int MaxCompTree(int CompArbres[], int &Lv) {
       	   int maximum=0;
       	   for (int i= 0; i < Lv; i++) {
		   maximum=(CompArbres[i]>maximum)?CompArbres[i]:maximum;
		   }
		   return maximum;
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

int main(int, char **)
   {
   tree<string> tr, Supertr;
   tree<string>::iterator li,ite,it,top, one, two;
   vector<tree<string>::iterator>  iteroTree;
   vector< vector<string > > Mbgraph;
   //vector<pair<unsigned int, unsigned int> > index;
   vector< vector<tree<string> > > PartTree;
   string s1="(((a2,b1)a2b1, c1, c2)a2b1c1c2, a1)a1a2b1c1c2";
   string s2="(((((a2,b1)a2b1),c1)a2b1c1,c2)a2b1c1c2, a1)a1a2b1c1c2";
   string s3="(((((a2,b1)a2b1),c2)a2b1c1,c1)a2b1c1c2, a1)a1a2b1c1c2";
   string s4="(((a2,b1)a2b1,(c1,c2)c1c2)a2b1c1c2,a1)a1a2b1c1c2";

   int y=0, k, p, Lcs;

   vector< vector<tree<string>::iterator> > vec2;
   vector<vector<string> > children;
   vector<string> Pchildren;

   vector<string> arrLab;
   vector<tree<string> > arrTree, arrTree2;

   top=tr.begin();
   one=tr.insert(top, "R0");
   tr.append_child(one, "c2");
   two=tr.append_child(one, "R1");
   tr.append_child(two, "b1");
   tr.append_child(two, "a2");
   arrTree.push_back(tr);
   tr.clear();

   top=tr.begin();
   one=tr.insert(top, "R0");
   tr.append_child(one, "a1");
   two=tr.append_child(one, "R1");
   tr.append_child(two, "a2");
   tr.append_child(two, "c2");
   arrTree.push_back(tr);
   tr.clear();

    top=tr.begin();
   one=tr.insert(top, "R0");
   tr.append_child(one, "a1");
   two=tr.append_child(one, "R1");
   tr.append_child(two, "a2");
   tr.append_child(two, "b1");
   arrTree.push_back(tr);
   tr.clear();

   top=tr.begin();
   one=tr.insert(top, "R0");
   tr.append_child(one, "a1");
   two=tr.append_child(one, "R1");
   tr.append_child(two, "c2");
   tr.append_child(two, "b1");
   arrTree.push_back(tr);
   tr.clear();

   arrTree2=arrTree;

   top=tr.begin();
   one=tr.insert(top, "R0");
   tr.append_child(one, "a1");
   two=tr.append_child(one, "R1");
   tr.append_child(two, "c2");
   tr.append_child(two, "c1");
   arrTree2.push_back(tr);
   tr.clear();

   top=tr.begin();
   one=tr.insert(top, "R0");
   tr.append_child(one, "a1");
   two=tr.append_child(one, "R1");
   tr.append_child(two, "b1");
   tr.append_child(two, "c1");
   arrTree2.push_back(tr);
   tr.clear();

   top=tr.begin();
   one=tr.insert(top, "R0");
   tr.append_child(one, "a1");
   two=tr.append_child(one, "R1");
   tr.append_child(two, "a2");
   tr.append_child(two, "c1");
   arrTree2.push_back(tr);
   tr.clear();

   top=tr.begin();
   one=tr.insert(top, "R0");
   tr.append_child(one, "c1");
   two=tr.append_child(one, "R1");
   tr.append_child(two, "b1");
   tr.append_child(two, "a2");
   arrTree2.push_back(tr);
   tr.clear();
   arrTree=arrTree2;
   //cout<<arrTree.size();
   string ar="(c2,(a2,b1)); (a1,(a2,c2)); (a1,(a2,b1)); (a1,(c2,b1)); (a1,(c1,c2)); (a1,(b1,c1)); (a1,(a2,c1)); (c1,(b1,a2))";
   string ar2="(a2,(c1,c2,a2,b1)); (c1,c2,(a2,b1))";
   PartTree.push_back(arrTree);
   arrTree.clear();
   arrLab=getLeafLabels(PartTree,0);
   int s=1;
   string chain=arrLab[0];
   while (s<arrLab.size()) {chain=chain+arrLab[s]; s++; }
   //printScrLabels(arrLab);
  // int LLab=arrLab.size();
   unsigned int i, ii;
   //MMbGraph=MGraphfill(Mbgraph, 0);
   //ii++;
   vector<vector< vector<string > > > MMbgraph;
   int sPart=PartTree.size();
    y=0;ii=0;
    cout<<ar<<endl<<endl;
    cout<<ar2<<endl<<endl<<endl;
   while (y<sPart) {
     vec2=IntEdges(PartTree,y);
     //cout<<ii<<endl;
     children=TriChClades(PartTree, vec2, y);
     Pchildren=TriRClades(PartTree, vec2, children, y);
     Mbgraph=GraphBuild(Pchildren, children);
     //printScrGraph(Mbgraph);
     MMbgraph.push_back(vector<vector<string> >());
     for(int j=0;j<Mbgraph.size();j++)
     {
       MMbgraph[ii].push_back(vector<string>());
       for(int k=0;k<Mbgraph[j].size();k++)
       {
           MMbgraph[ii][j].push_back(Mbgraph[j][k]);
       }
       }

     TreePartition(Mbgraph, PartTree, y, ii);
     ii++;
   	 Mbgraph.clear();
   	 sPart=PartTree.size();
	 y++;
   }
   printScrGraphS(MMbgraph);

  /* for(int j=0;j<index.size();j++) {
   	cout<<index[j].first<<" ";
   	cout<<index[j].second<<endl;
   }*/
   p=0;
   size_t found=std::string::npos;
   for (int i = 0; i < MMbgraph.size(); i++) {

      if (i==0) {
      	top=Supertr.begin();
        iteroTree.push_back(Supertr.insert(top, chain)); p++;
              }

    for (int j = 0; j < MMbgraph[i].size(); j++){
    	found=std::string::npos;
        if (MMbgraph[i][j].size()>=2)  {
        	   s=1;
			   chain=MMbgraph[i][j][0];

               while (s<MMbgraph[i][j].size()) {chain=chain+MMbgraph[i][j][s]; s++; }

               //k=iteroTree.size()-1;
               k=iteroTree.size()-1; Lcs=chain.size();

               while ((k>=0)&&(found==std::string::npos)) {
                  if ((*iteroTree[k]).size()>Lcs) {
				//  cout<<endl<<Lcs;
				  found=(*iteroTree[k]).find(chain);      }
                          k--;
                            }

		         iteroTree.push_back(Supertr.append_child(iteroTree[k+1], chain));


		       if (MMbgraph[i][j].size()==2) {
			      Supertr.append_child(iteroTree[k+2], MMbgraph[i][j][0]);
			      Supertr.append_child(iteroTree[k+2], MMbgraph[i][j][1]);
			            }

		       else if (MMbgraph[i][j].size()>=3){
		    //label construction
		    // node insertion and labeling
				  int cc, d=0, u=i+1, con=0;
				  bool gg=false;
		          cc=0;

		          while (d<MMbgraph[i][j].size()&&cc!=MMbgraph[i][j].size()){
				  u=con;
		          gg=false;
		          while(u<MMbgraph.size()){
                    for (int uu = 0; uu < MMbgraph[u].size(); uu++)   {
                     for (int uuu = 0; uuu < MMbgraph[u][uu].size(); uuu++) {

		                  if (MMbgraph[i][j][d]==MMbgraph[u][uu][uuu]) {
		                      cc=cc+1; gg=true;
		                      	    }
							   if (gg) break;
							        }
							   if (gg) break;
									}
								if (gg) {
									con=u; break;
								     }
									u++ ;
		                      	      }
		                      	  d++;
		                              }
		                     if (cc!=MMbgraph[i][j].size()) {
							 for (int ii = 0; ii < MMbgraph[u].size(); ii++)
							      Supertr.append_child(iteroTree[k+2], MMbgraph[i][j][ii]);
							      }

			                       }
	              }
	         else if (MMbgraph[i][j].size()==1) {
	         	int s=0;
				chain=MMbgraph[i][j][s];
	         	k=iteroTree.size()-1; Lcs=chain.size();
               //iteroTree.size()
               while ((k>=0)&&(found==std::string::npos)) {
                  if ((*iteroTree[k]).size()>Lcs) found=(*iteroTree[k]).find(chain);
                          k--;
                        }
     	        Supertr.append_child(iteroTree[k+1], MMbgraph[i][j][0]);
	         	}

               }
       }


    cout<<"Build:"<<endl<<endl;
   	print_tree_bracketed(Supertr, std::cout);

   	vector< vector<tree<string>::iterator> > poly;
   	vector<tree<string>::iterator> rowpoly;

	tree<string>::iterator itt;
   	int lp=8;
   	cout<<endl;
   	for (int i= 3; i < lp; i++) {
   	itt=Supertr.begin();
	while(itt!=Supertr.end()) {
		if (Supertr.number_of_children(itt)==i) {
		tree<string>::sibling_iterator sib=Supertr.begin(itt);
	   while(sib!=Supertr.end(itt)) {
         //cout << (*sib) <<" ";
         rowpoly.push_back(sib);
         ++sib;
         }
         cout<<endl;
         poly.push_back(rowpoly);
         rowpoly.clear();
			 }
		++itt;
		}

   	 	}
   	cout<<"Build G:"<<endl;
//s1="(((a2,b1)a2b1, c1, c2)a2b1c1c2, a1)a1a2b1c1c2";
cout<<endl<<s2<<endl;
cout<<endl<<s3<<endl;
cout<<endl<<s4<<endl;


   	 // function pour extraire feuilles de toutes les politomies
   	//function subsets
	 // funcion for integer partition
	 // bell numbers



 return 0;
  }
