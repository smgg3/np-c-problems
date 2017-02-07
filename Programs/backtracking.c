 #include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define LEN 10
#define target 15
//#define FILENAME "8.txt"
#define FILENAME "txt10.txt"
//#define FILENAME "DAGS1.txt"
//#define FILENAME "c-fat200-5.clq.txt"
//#define FILENAME "p_hat300-3.clq.txt"
//#define FILENAME "hamming8-4.clq.txt"
//#define FILENAME "johnson8-4-4.clq.txt"
//#define FILENAME "C125.9.clq.txt"
//#define FILENAME "gen200_p0.9_44.b.txt"
//#define FILENAME "san200_0.7_2.clq.txt"
//#define FILENAME "sanr200_0.7.clq.txt"
//#define FILENAME "brock200_1.b.txt"
//#define FILENAME "r500.5.txt"
//#define FILENAME "MANN_a45.clq.b.txt" 
//#define FILENAME "keller6.clq.txt" 

// Number of vertices in the graph
#define V 4
 
void printSolution(int color[]);
 
/* A utility function to check if the current color assignment
   is safe for vertex v */
int isSafe (int v, int graph[V][V], int color[], int c)
{ int i;
    for (i = 0; i < V; i++)
        if (graph[v][i] && c == color[i])
            return 0;
    return 1;
}
 
/* A recursive utility function to solve m coloring problem */
int graphColoringUtil(int graph[V][V], int m, int color[], int v)
{
    /* base case: If all vertices are assigned a color then
       return true */
    if (v == V)
        return 1;
 int c;
    /* Consider this vertex v and try different colors */
    for ( c = 1; c <= m; c++)
    {
        /* Check if assignment of color c to v is fine*/
        if (isSafe(v, graph, color, c))
        {
           color[v] = c;
 
           /* recur to assign colors to rest of the vertices */
           if (graphColoringUtil (graph, m, color, v+1) == 1)
             return 1;
 
            /* If assigning color c doesn't lead to a solution
               then remove it */
           color[v] = 0;
        }
    }
 
    /* If no color can be assigned to this vertex then return false */
    return 0;
}
 
/* This function solves the m Coloring problem using Backtracking.
  It mainly uses graphColoringUtil() to solve the problem. It returns
  false if the m colors cannot be assigned, otherwise return true and
  prints assignments of colors to all vertices. Please note that there
  may be more than one solutions, this function prints one of the
  feasible solutions.*/
int graphColoring(int graph[V][V], int m)
{
    // Initialize all color values as 0. This initialization is needed
    // correct functioning of isSafe()
    int *color = new int[V];
    for (int i = 0; i < V; i++)
       color[i] = 0;
 
    // Call graphColoringUtil() for vertex 0
    if (graphColoringUtil(graph, m, color, 0) == false)
    {
      printf("Solution does not exist");
      return 0;
    }
 
    // Print the solution
    printSolution(color);
    return 1;
}
 
/* A utility function to print solution */
void printSolution(int color[])
{
    printf("Solution Exists:"
            " Following are the assigned colors \n");
    for (int i = 0; i < V; i++)
      printf(" %d ", color[i]);
    printf("\n");
}
 
// driver program to test above function
int main()
{
    /* Create following graph and test whether it is 3 colorable
      (3)---(2)
       |   / |
       |  /  |
       | /   |
      (0)---(1)
    */
    int graph[V][V] = {{0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0},
    };
    int m = 3; // Number of colors
    graphColoring (graph, m);
    return 0;
}
