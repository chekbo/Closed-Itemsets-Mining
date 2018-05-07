#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <cmath>
#include "context.h"

using namespace std;

void th(context c,int sup,vector<vector<int>> &res){
  res = c.close((double)sup/100);
}

int main(int argc,char** argv){
  //context global
  context c(argv[1]);
  /*{
    vector<vector<int>> fermeture = c.close((double)atoi(argv[2])/100);
    cout << "Liste fermetures global : "  << endl ;
    for(int i = 0; i < fermeture.size();++i){
      sort(fermeture[i].begin(),fermeture[i].end());
      for(int j = 0; j < fermeture[i].size();++j)
	cout << (char)(fermeture[i][j]+65);
      cout << ",";
    }
    cout << endl;
    }*/
  //sous context
  vector<context> vc;
  vector<vector<vector<int>>> result;
  int NUM_THREAD = atoi(argv[3]);
  //Creation des sous context
  for(int i = 0; i < NUM_THREAD;++i){
    vc.push_back(context(c,round(c.size_i/NUM_THREAD)*i,round(c.size_i/NUM_THREAD)*(i+1)));
    result.push_back(vector<vector<int>>());
  }
  //Lancement des thread
  vector<thread> para;
  for(int i = 0; i < NUM_THREAD;++i)
    para.push_back(thread(th,vc[i],atoi(argv[2]),ref(result[i])));
  
  //Attente fin de thread
  for(int i = 0; i < NUM_THREAD;++i)
    para[i].join();
  //Affichage des fermetures locals
  for(int t = 0; t < NUM_THREAD;++t){
    cout << "Liste fermetures locales : " << t << endl ;
    vector<vector<int>> fermeture(result[t]);
    for(int i = 0; i < fermeture.size();++i){
      sort(fermeture[i].begin(),fermeture[i].end());
      for(int j = 0; j < fermeture[i].size();++j)
	cout << (char)(fermeture[i][j]+65);
      cout << ",";
    }
    cout << endl;
  }
  
  //Intersection
  vector<vector<int>> inter(result[0]);
  for(int i = 1; i < NUM_THREAD;++i){
    inter = c.unif(inter,result[i]);
  }
  //Eleminer les support faibles CA MARCHE
  for(int i = 0; i < inter.size(); ++i){
    if(c.support(inter[i]) < (double)atoi(argv[2])/100){
      inter.erase(inter.begin()+i);
      i--;
    }
  }
  //Affichage des fermetures globals
    cout << "Liste fermetures lfinal : " << endl ;
    vector<vector<int>> fermeture(inter);
    for(int i = 0; i < fermeture.size();++i){
      sort(fermeture[i].begin(),fermeture[i].end());
      for(int j = 0; j < fermeture[i].size();++j)
	cout << (char)(fermeture[i][j]+65);
      cout << ",";
    }
    cout << endl;
    
  return 0;
}
