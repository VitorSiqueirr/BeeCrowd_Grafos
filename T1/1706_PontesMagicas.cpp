// Algoritmos em Grafos (2022/1/570/COI-A/2332) //
// T1 (1706) - Version 1.5 //

/* 
Codinome: Grupo

Integrantes:
1. Derik Leonardo Rosvadoski Konisk
2. Paula Yanagawa Nizer
3. Vitor Siqueira
*/

// Bibliotecas //
#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

enum Cor {WHITE,GRAY,BLACK};
int color[1001], d[1001], p[1001], f[1001],vertex;
char nota[1001];
int NIL = 0;
int INF = -1;


//bfs para verificar se existe caminho entre s e k
bool BFS(vector<int> adj[], int s, int k){
    if (s== k){
                return true;
    }
    for(int u=0; u<=vertex; u++) {
        color[u] = WHITE;
        d[u] = INF;
        p[u] = NIL;
    }

    color[s] = GRAY;
    d[s] = INF;
    p[s] = NIL;

    queue<int> Q; Q.push(s);

    while( !Q.empty()) {
        
        int u = Q.front(); Q.pop();
        
        for(int v=0; v<adj[u].size(); v++) {
            
            if(color[adj[u][v]] == WHITE) {
                if (adj[u][v]== k){
                    //cout<<"entraaq"<<endl;
                    return true;
                }
                color[adj[u][v]] = GRAY;
                d[adj[u][v]] = d[u] + v;
                p[adj[u][v]] = u;
                p[u] = adj[u][v];
                Q.push(adj[u][v]);
            }
        }
        color[u] = BLACK;
    }
    return false;
}
bool existeCaminho(vector<int> adj[], char nota[]){
    int hasB=0;
    for(int u=1;u<=vertex;u++){
        //para cada vertice do grafo
                
        if(nota[u]=='B'){
            //se a nota for b
        	if(hasB){
        	    //segundo b encontrado
        		if(BFS(adj,hasB,u)){
        		   nota[hasB]='A';//varinha mágica
	               nota[u]='A';//varinha mágica
				}
			    hasB=0; 
		    }
    	    else{
    	        hasB=u;//primeiro b encontrado
	        
    	    }
        }
    }
	for(int u=1;u<=vertex;u++){
		if(nota[u]=='B'){
			return false;
		}
	}
	return true;
}
int main()
{

    int n;//numero de vertices
    int m;//numero de arestas
 
  
	while (cin>> n>>m)
    {   
    	
        bool existe=true;
        
        vertex=n;
        vector<int> adj[vertex+1];
        char notas[1001];
        int u, v;
        int cont=0;
        
        //le nota
        for(int i=1;i<=vertex;i++){
            cin>>nota[i];
        }
        //le e adiciona aresta
        for(int i =1;i<=m;i++){
            cin>>u>>v;
            adj[u].push_back(v);
            adj[v].push_back(u);//grafo não direcionado
        }
      	//conta a quantidade de b
        for(int u=1;u<=vertex;u++){
        	if(nota[u]=='B'){
        	    cont++;
			}
		}
        //se for par 
        if(cont%2==0){
            //verifica se existe caminho entre os dois bs
            if(existeCaminho(adj, nota)){
                cout<<"Y"<<endl;
            }
			else{
				cout<<"N"<<endl;
			}
        }//se for impar
        else{
			cout<<"N"<<endl;
		}
    }
    return 0;
}
