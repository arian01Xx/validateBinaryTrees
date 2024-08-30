#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <vector>
#include <iostream>
#include <queue>

using namespace std;

class SolutionFourtyOne{
public:
	bool validateBinaryTreeNodes(int n, vector<int>& leftChild, vector<int>& rightChild){
		vector<int> inDegree(n,0);
		//contar las entradas de cada nodo
		for(int i=0; i<n; ++i){
			//en todo arbol binario solo debe haber una entrada por cada nodo
			if(leftChild[i] != -1){
				inDegree[leftChild[i]]++;
				if(inDegree[leftChild[i]] > 1) return false;
			}
			if(rightChild[i] != -1){
				inDegree[rightChild[i]]++;
				if(inDegree[rightChild[i]] > 1) return false;
			}
		}
		//verificar si hay un solo nodo raiz (nodo sin padre)
		int rootCount=0;
		int rootNode=-1;
		for(int i=0; i<n; ++i){
			if(inDegree[i]==0){
				rootCount++;
				rootNode=i; //este es el nodo padre
			}
		}
		//debe haber exactamente un nodo raíz
		if(rootCount != 1) return false;
		//verificar que no haya ciclos y que todos los nodos sean accesibles desde la raiz
		queue<int> q;
		vector<bool> visited(n,false);
		q.push(rootNode); //arranca desde el nodo padre encontrado
		visited[rootNode]=true;
		int count=0;
		while(!q.empty()){
			int node=q.front();
			q.pop();
			count++;
			if(leftChild[node] != -1){
				//si ya fue visitado entonces es un ciclo cerrado
				if(visited[leftChild[node]]) return false;
				visited[leftChild[node]]=true; //sino se le marca como visitado
				q.push(leftChild[node]);
			}
			if(rightChild[node] != -1){
				if(visited[rightChild[node]]) return false;
				visited[rightChild[node]]=true;
				q.push(rightChild[node]);
			}
		}
		//si todos los nodos fueron visitados, entonces es un arbol valido
		return count==n;
	}
};

#endif