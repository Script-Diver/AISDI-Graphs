#include "Graph.hpp"
#include <cstdlib> //exit()
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

bool test(int, char**);
void performTests(int, char**);
string to_String(int);

int main(int argc, char** argv)
{
  performTests(argc, argv);
  return 0;
}

void performTests(int argc, char** argv)
{
  if(argc == 1){ cerr<<"Poprawna skladnia: "<<argv[0]<<" plik[i]\n"; exit(EXIT_FAILURE); }
  for(int i = 1 ; i < argc ; i++) if(test(i, argv) == false) cout<<"Test nie powiodl sie"<<endl;
}

bool test(int i, char**argv)
{
  int n, v1, v2;
  ifstream fin(argv[i]);
  if(!fin.is_open()){ cerr<<"Nie mozna otworzyc pliku "<<argv[1]<<endl; fin.clear(); return false; }

  fin>>n;
  if(n <= 0){ std::cout<<"Nie mozna stworzyc grafu o niedodatniej ("<<n<<") liczbie wierzcholkow"<<std::endl; return false; }

  Graph g(n);

  while(!fin.eof()){
    fin>>v1;
    if(fin.eof()){ break; }
    fin>>v2;
    g.addEdge(v1, v2);
  }

  std::cout<<std::endl<<"GRAF:"<<std::endl;
  g.print();
  std::cout<<"MOSTY:"<<std::endl;
  g.showWideBridges();

  fin.clear();
  fin.close();
  return true;
}
