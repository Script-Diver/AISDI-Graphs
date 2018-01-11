#include <iostream>
#include <list>
#include <queue>
#include <iterator>
#include <vector>

enum Color {white, black};


class Graph
{
  public:
  class Vertex;

  private:
  size_t n;
  std::vector<Vertex> vTab;

  bool isConnected(int, int*);

  public:
  void print();
  void showWideBridges();
  void addEdge(int, int);
  ~Graph();
  Graph(int nv);
};


class Graph::Vertex
{
  public:
  Color color;
  std::list<int> nbr;

  Vertex(Color c = white): color(c) {}
  ~Vertex() {}
  void addNbr(int num) { nbr.push_front(num); }
  void printV() { for(std::list<int>::iterator it = nbr.begin() ; it != nbr.end() ; it++)  std::cout<<*it<<"  "; }
};

Graph::Graph(int nv) : n(nv)
{
  for(int i = 0 ; i < n ; i++) vTab.push_back(white);
}

Graph::~Graph() {}

void Graph::addEdge(int v1, int v2)
{
  vTab[v1].addNbr(v2);
  vTab[v2].addNbr(v1);
}

//UWAGA: zakladamy, ze graf przed usunieciem wierzcholkow jest spojny (zgodnie z trescia zadania)
bool Graph::isConnected(int nb, int *banned)
{
  if(nb >= n) throw std::out_of_range("Zbyt duza liczba wierzcholkow zabronionych");

  int i, num = 0;
  std::queue<int> Q;
  for(i = 0 ; i < nb ; i++) vTab[banned[i]].color = black; //w zadaniu: 2
  for(i = 0 ; i < n ; i++) { if(vTab[i].color == white){ Q.push(i); break; } } //w zadaniu: max 3
  while(!Q.empty()){
    i = Q.front();
    vTab[i].color = black;
    Q.pop();
    for(std::list<int>::iterator it = vTab[i].nbr.begin() ; it != vTab[i].nbr.end() ; it++){
      if(vTab[*it].color == white){ Q.push(*it); vTab[*it].color = black; }
    }
    num++;
  }
  return num == n-nb;
}

void Graph::showWideBridges()
{
  int tmp[2];
  if(n <= 3) return;
  for(int i = 0 ; i < n ; i++){
    tmp[0] = i;
    for(std::list<int>::iterator it = vTab[i].nbr.begin() ; it != vTab[i].nbr.end() ; it++){
      if(i < *it){
        for(int j = 0 ; j < n ; j++) vTab[j].color = white;
        tmp[1] = *it;
        if(isConnected(2, tmp) == false) std::cout<<tmp[0]<<" "<<tmp[1]<<std::endl;
      }
    }
  }
}

void Graph::print()
{
  for(int i = 0 ; i < n ; i++) {  std::cout<<i<<". "; vTab[i].printV(); std::cout<<std::endl;  } 
}

