#ifndef GRAPH_H
#define GRAPH_H

/******************************************************************************
 *  AUTHOR         : Jousha McDermott, Seongkyoo Maeng, Chak Hei Tin
 *  Project #2     : I Love Baseball
 *  CLASS          : CS 008
 *  DUE DATE       : 06/02/2020
 ******************************************************************************/

#include <iostream>
#include <cstdlib>
#include <set>
#include <cassert>
#include <math.h>
#include <vector>

using namespace std;

/*******************************************
 * class Graph
 * - This class creates an graph object which
 * represents map using adjacency matrix.
 ******************************************/

template <class T>
class Graph
{
public:
    /***********************
     ** MEMBER CONSTANTS **
    ************************/
    static const size_t MAXIMUM = 32;

    /******************
     ** CONSTRUCTOR **
    *******************/
    Graph( ) { _vertices = 0; }

    /************************************
     ** MODIFICATION MEMBER FUNCTIONS **
    *************************************/
    void add_vertex(const T& label);
    void add_edge(size_t source, size_t target, size_t weight);
    void remove_edge(size_t source, size_t target);
    T& operator[](size_t vertex);

    /********************************
     ** CONSTANT MEMBER FUNCTIONS **
    *********************************/
    size_t size( ) const { return _vertices; }
    bool is_edge(size_t source, size_t target) const;
    set<size_t> neighbors(size_t vertex) const;
    vector<int> unvisitedNeighbors(size_t vertex, bool visited[]) const;
    T operator[](size_t vertex) const;
    size_t getWeight(size_t fromIndex, size_t toIndex) const;


    /***********************
     ** GRAPH ALGORITHMS **
    ************************/
    void dijkstra(size_t source);
    void prim( );
    void kruskal( );
    size_t minIndex(size_t distance[], bool allowed_set[]);
    void getPath( vector<size_t>& store, size_t parent[], size_t target);
    vector<size_t> getVertices(size_t source, size_t target);
    vector<int> getVerticesJosh(int source, int target);
    vector<vector<int>> getDistanceMatrix();
    vector<int> minPathV1(int source);
    vector<int> minPathV2(int source);
    int getPathWeight(vector<int>);
    vector<int> minPathV1(int source, bool allowed[]);
    vector<int> minPathV2(int source, bool allowed[]);



    /**********************
     ** PRINT FUNCTION **
    ***********************/
    void print( );
    void printDijkstra(size_t distance[]);
    void printPrim(size_t store_edge[]);
    void printKruskal(size_t store_edge_i[], size_t store_edge_j[]);
    bool allVisited(bool visited[]);
    bool allVisited(bool visited[], bool allowed[]);
    int getMinIndex(vector<int> list, bool visited[]);
    int getMinIndex(vector<int> list, bool visited[],bool allowed[]);
private:
    size_t _edges[MAXIMUM][MAXIMUM];  // 2D array for graph's edges
    T _labels[MAXIMUM];               // array for graph's labels
    size_t _vertices;                 // number of vertices
};

/***********************
 ** MEMBER CONSTANTS **
************************/

/********************************************************
 * static const size_t MAXIMUM = _______
 * ------------------------------------------------------
 * Postcondition: the maximum number of vertices that a
 * graph can have.
 ********************************************************/

/******************
 ** CONSTRUCTOR **
*******************/

/********************************************************
 * Graph( )
 * ------------------------------------------------------
 * Postcondition: the graph has been initialized with
 * no vertices and no edges.
 ********************************************************/

/************************************
 ** MODIFICATION MEMBER FUNCTIONS **
*************************************/

/********************************************************
 * void add_vertex(const T& label)
 * ------------------------------------------------------
 * Precondition: size( ) < MAXIMUM
 * Postcondition: The size of the graph has been
 * increased by adding one new vertex. This new vertex
 * has the specified label and no edges.
 ********************************************************/

template <class T>
void Graph<T>::add_vertex(const T& label)
{
    size_t new_vertex_number;
    size_t other_number;

    assert(size( ) < MAXIMUM);
    new_vertex_number = _vertices;
    _vertices++;

    for(other_number = 0; other_number < _vertices; other_number++)
    {
        _edges[other_number][new_vertex_number] = 0;
        _edges[new_vertex_number][other_number] = 0;
    }

    _labels[new_vertex_number] = label;
}

/********************************************************
 * void add_edge(size_t source, size_t target,
 * size_t weight)
 * ------------------------------------------------------
 * Precondition: (source < size( )) and (target < size( ))
 * Postcondition: The graph has all the edges that it
 * originally had, and it also has another edge from
 * the specified source to the specified target.
 * (If this edge was already present, then the graph
 * is unchanged). Additionally, it also keeps track of
 * the given weight of a specific edge.
 ********************************************************/

template <class T>
void Graph<T>::add_edge(size_t source, size_t target, size_t weight)
{
    assert(source < size( ));
    assert(target < size( ));
    _edges[source][target] = weight;
    _edges[target][source] = weight;
}

/********************************************************
 * void remove_edge(size_t source, size_t target)
 * ------------------------------------------------------
 * Precondition: (source < size( )) and (target < size( ))
 * Postcondition: The graph has all the edges that it
 * originally had except for the edge from the specified
 * source to the specified target. (If this edge was not
 * originally present, then the graph is unchanged).
 ********************************************************/

template <class T>
void Graph<T>::remove_edge(size_t source, size_t target)
{
    assert(source < size( ));
    assert(target < size( ));
    _edges[source][target] = 0;
}

/********************************************************
 * T& operator[](size_t vertex)
 * ------------------------------------------------------
 * Precondition: _vertices < size( )
 * Postcondition: The return value is a reference to the
 * label of the specified vertex.
 ********************************************************/

template <class T>
T& Graph<T>::operator[](size_t vertex)
{
    assert(vertex < size( ));
    return _labels[vertex];
}

/********************************
 ** CONSTANT MEMBER FUNCTIONS **
*********************************/

/********************************************************
 * size_t size( ) const
 * ------------------------------------------------------
 * Postcondition: The return value is the number of
 * vertices in the graph.
 ********************************************************/

/********************************************************
 * bool is_edge(size_t source, size_t target) const
 * ------------------------------------------------------
 * Precondition: (source < size( )) and (target < size( ))
 * Postcondition: The return value is true if the graph
 * has an edge from source to target. Otherwise the
 * return value is false.
 ********************************************************/

template <class T>
bool Graph<T>::is_edge(size_t source, size_t target) const
{
    assert(source < size( ));
    assert(target < size( ));
    return _edges[source][target];
}

/********************************************************
 * set<size_t> neighbors(size_t vertex) const
 * ------------------------------------------------------
 * Precondition: (_vertices < size( ))
 * Postcondition: The return value is a set that
 * contains all the vertex numbers of vertices that are
 * the target of an edge whose source is at the specified
 * vertex.
 ********************************************************/
template <class T>
set<size_t> Graph<T>::neighbors(size_t vertex) const
{
    set<size_t> answer;
    size_t i;

    assert(vertex < size( ));

    for(i = 0; i < size( ); i++)
        if(_edges[vertex][i] != 0)
            answer.insert(i);
    return answer;
}

/********************************************************
vector<int> Graph<T>::unvisitedNeighbors(size_t vertex, bool visited[]) const
 * ------------------------------------------------------
 * Precondition: (_vertices < size( ))
 * Postcondition: returns to the answer vector containing
 * all the unvisited vertices from the _edge array
 ********************************************************/
template<class T>
vector<int> Graph<T>::unvisitedNeighbors(size_t vertex, bool visited[]) const
{
    vector<int> answer;
    assert(vertex < size( ));

    for(int i = 0; i < size( ); i++)
        if((_edges[vertex][i] != 0) && !visited[i])
            answer.push_back(i);
    return answer;
}

/********************************************************
 * T operator[](size_t vertex) const
 * ------------------------------------------------------
 * Precondition: vertex < size( )
 * Postcondition: The return value is a reference to the
 * label of the specified vertex.
 ********************************************************/

template <class T>
T Graph<T>::operator[](size_t vertex) const
{
    assert(vertex < size( ));
    return _labels[vertex];
}

/***********************
 ** GRAPH ALGORITHMS **
************************/

/********************************************************
 * void dijkstra(size_t source)
 * ------------------------------------------------------
 * Postcondition: generate a shortest path tree with a
 * given source as root. We maintain two sets, one set
 * contains vertices included in shortest path tree,
 * other set includes vertices not yet included in
 * shortest path tree. At every step of the algorithm,
 * we find a vertex which is in the other set (set of
 * not yet included) and has a minimum distance from
 * the source.
 ********************************************************/

template <class T>
void Graph<T>::dijkstra(size_t source) {
    size_t distance[_vertices];
    bool allowed_set[_vertices];
    size_t allowed_size, next, i, sum;
    int parent[_vertices];
    parent[source]=-1;

    for(i = 0; i <= _vertices; i++)
    {
        distance[i] = INFINITY;  // initialize the distance array to all infinity
        allowed_set[i] = true;   // initialize the allowed set to all true
    }

    distance[source] = 0;
    for(allowed_size = 1; allowed_size <= _vertices; allowed_size++)
    {
        next = minIndex(distance, allowed_set); // index of minium distance

        allowed_set[next] = false; // not an allowed set now

        for(i = 0; i < _vertices; i++)
        {
            if((allowed_set[i]) && (is_edge(next, i)) && distance[next] != INFINITY)
            {
                sum = distance[next] + _edges[next][i];
                if(sum < distance[i])
                {
                    distance[i] = sum;
                    parent[i] = next;
                }
            }
        }
    }
    printDijkstra(distance); // print the shortest path for all cities
}

/********************************************************
 * void prim( )
 * ------------------------------------------------------
 * Postcondition: starts with an empty spanning tree.
 * Maintain two sets of vertices, the first set contains
 * the vertices already included in the MST, the other
 * set contains the vertices not yet included. At every
 * step, it considers all the edges that connect the
 * two sets, and picks the minimum weight edge from
 * these edges. After picking the edge, it moves the
 * other endpoint of the edge to the set containing MST.
 ********************************************************/

template <class T>
void Graph<T>::prim( )
{
    size_t store_edge[_vertices];
    size_t key_weight[_vertices];
    bool allowed_set[_vertices];
    size_t allowed_size, next, i;

    for(i = 0; i <= _vertices; i++)
    {
        key_weight[i] = INFINITY;  // initialize the key array to all infinity
        allowed_set[i] = true;   // initialize the allowed set to all true
    }

    key_weight[0] = 0;  // this will allow this vertex to be picked first
    store_edge[0] = 0; // root node is the first node which is initalized to 0

    for(allowed_size = 0; allowed_size < _vertices - 1; allowed_size++)
    {
        next = minIndex(key_weight, allowed_set); // index of minium distance

        allowed_set[next] = false; // not an allowed set now

        for(i = 0; i < _vertices; i++)
        {
            // Check if it is allowed set, if the edge exists,
            if((allowed_set[i]) && (is_edge(next, i)) &&
                    _edges[next][i] < key_weight[i])
            {
                store_edge[i] = next; // keeps the index (edges)
                key_weight[i] = _edges[next][i]; // keeps the weight
            }
        }
    }

    printPrim(store_edge);
}

/********************************************************
 * void kruskal( )
 * ------------------------------------------------------
 * Postcondition: simialr to prim's algorithm, however,
 * it always takes the shortest path even if the edges
 * are not neighbors of one and another. Maintain two
 * sets of vertices, the first set contains
 * the vertices already included in the MST, the other
 * set contains the vertices not yet included. At every
 * step, it considers all the edges that connect the
 * two sets, and picks the minimum weight edge from
 * these edges. After picking the edge, it moves the
 * other endpoint of the edge to the set containing MST.
 ********************************************************/

template <class T>
void Graph<T>::kruskal( )
{
    size_t store_edge_i[_vertices];
    size_t store_edge_j[_vertices];
    bool allowed_set[_vertices];
    T temp_label[_vertices];
    size_t allowed_size = 0;
    size_t i, j, min_weight;

    for(size_t i = 0; i < _vertices; i++)
    {
        store_edge_i[i] = 0; // initialize store edge i as all zeros
        store_edge_j[i] = 0; // initialize store edge j as all zeros
        allowed_set[i] = true; // initialize the allowed set to all true
        temp_label[i] = _labels[i]; // initialize a temp label
    }

    while(allowed_size < _vertices - 1)
    {
        min_weight = 9999999;
        int next_i, next_j;

        for(i = 0; i < _vertices; i++)
            for(j = 0; j < _vertices; j++)
                if(temp_label[i] != temp_label[j] && allowed_set[i] &&
                        is_edge(i, j) && _edges[i][j] < min_weight)
                {
                    min_weight = _edges[i][j];
                    next_i = i;
                    next_j = j;
                }

        temp_label[next_i] = temp_label[next_j];
        store_edge_i[allowed_size] = next_i;
        store_edge_j[allowed_size] = next_j;
        allowed_set[next_i] = false; // not an allowed set now
        allowed_size++;
    }
    printKruskal(store_edge_i, store_edge_j);
}

/********************************************************
 * size_t minIndex(size_t distance[], bool allowed_set[])
 * ------------------------------------------------------
 * Postcondition: Given the distance array (sum of the
 * weight from the source to a target), it provides the
 * minimum index in the array based on the allowed set
 * and shortest path.
 ********************************************************/

template <class T>
size_t Graph<T>::minIndex(size_t distance[], bool allowed_set[])
{
    size_t min_distance = INFINITY;
    size_t next;

    for (size_t i = 0; i < _vertices; i++)
        if (distance[i] <= min_distance && allowed_set[i])
        {
            min_distance = distance[i]; // keep track of the minimum distance
            next = i; // next will be the index of the minimum distane
        }

    return next;
}

/********************************************************
 * void print( )
 * ------------------------------------------------------
 * Postcondition: Prints the adjacency matrix of the
 * graph (prints the weight of each index).
 ********************************************************/

template <class T>
void Graph<T>::print( )
{
    for(size_t i = 0; i < size( ); i++)
    {
        for(size_t j = 0; j < size( ); j++)
            cout << _edges[i][j] << " ";
        cout << endl;
    }
}

/********************************************************
 * void printDijkstra(size_t distance[])
 * ------------------------------------------------------
 * Postcondition: Given the distance array (sum of the
 * weight from the source to a target), it prints the
 * distance and what has been visited from each weight.
 ********************************************************/

template <class T>
void Graph<T>::printDijkstra(size_t distance[])
{
    for (size_t i = 0; i < _vertices; i++)
    {
        cout << _labels[i] << ": " << distance[i] << " {";

        for(size_t j = 0; j <= i; j++)
        {
            if(i != j)
                cout << _labels[j] << ", ";
            else
                cout << _labels[j];
        }
        cout << "}" << endl;
    }
}

/********************************************************
 * void printPrim(size_t store_edge[])
 * ------------------------------------------------------
 * Postcondition: Given the store_edge array (has edges
 * that has the shortest weight), it prints the weight
 * of the two cities and where it was visited.
 ********************************************************/

template <class T>
void Graph<T>::printPrim(size_t store_edge[])
{
    for(size_t i = 1; i < _vertices; i++)
    {
        cout << "(" << _labels[store_edge[i]] << ", " << _labels[i] << ") "
             << _edges[i][store_edge[i]] << endl;
    }
}

/********************************************************
 * void printKruskal(size_t store_edge_i[], size_t
 * store_edge_j[])
 * ------------------------------------------------------
 * Postcondition: Given the store_edges array (has edges
 * that has the shortest weight), it prints the weight
 * of the two cities and where it was visited.
 ********************************************************/

template <class T>
void Graph<T>::printKruskal(size_t store_edge_i[], size_t store_edge_j[])
{
    int total = 0;
    for(size_t i = 0; i < _vertices - 1; i++)
    {
        cout << "(" << _labels[store_edge_i[i]] << ", " <<
                _labels[store_edge_j[i]] << ") "
             << _edges[store_edge_i[i]][store_edge_j[i]] << endl;
        total += _edges[store_edge_i[i]][store_edge_j[i]];
    }

   cout << "total: " << total;
}

/********************************************************
 * bool Graph<T>::allVisited(bool visited[])
 * ------------------------------------------------------
 * Precondition: visited[] (bool) //IN - the array to
 *               check visited vertices
 * Postcondition: return true if all the vertices were
 *                visited, false otherwise
 ********************************************************/
template <class T>
bool Graph<T>::allVisited(bool visited[])
{
    for (int i=0;i<_vertices;i++)
    {
        if (visited[i] == false)
        {
            return false;
        }
    }
    return true;
}

/********************************************************
 * bool Graph<T>::allVisited(bool visited[], bool allowed[])
 * ------------------------------------------------------
 * Precondition: visited[] (bool) //IN - the array to
 *               check visited vertices
 *               allowed[] (bool) //IN - the array to
 *               allow unvisited vertice to continue
 * Postcondition: return true if all the vertices were
 *                visited, false otherwise
 ********************************************************/
template<class T>
bool Graph<T>::allVisited(bool visited[], bool allowed[])
{
    for (int i=0;i<_vertices;i++)
    {
        if (visited[i] == false)
        {
            if (!allowed[i])
                continue;
            return false;
        }
    }
    return true;
}

/********************************************************
 * vector<int> Graph<T>::getVerticesJosh(int source, int target)
 * ------------------------------------------------------
 * Precondition: source (int) //IN - the starting vertice
 *               target (int) //IN - the ending vertice
 * Postcondition: return to the vector containing the vertices
 *                needed for the trip
 ********************************************************/
template <class T>
vector<int> Graph<T>::getVerticesJosh(int source, int target)
{
    int largeInt = 100000000;
    size_t distance[_vertices];
    bool visited[_vertices];
    int parent[_vertices];
    for (int i=0;i<_vertices;i++)
    {
        parent[i] = largeInt;
        distance[i] = largeInt;
        visited[i] = false;
    }
    int currentNode = source;
    parent[source] = -1;
    visited[source] = true;
    distance[source] = 0;

    while (!allVisited(visited))
    {
        vector<int> neighborVec = unvisitedNeighbors(currentNode,visited);

        for (int i = 0; i < neighborVec.size(); i++) //unvis neighbors
        {
            if((distance[currentNode]+_edges[currentNode][neighborVec[i]])<
                    distance[neighborVec[i]])
            {
                distance[neighborVec[i]] = distance[currentNode]+
                        _edges[currentNode][neighborVec[i]];
                parent[neighborVec[i]] = currentNode;
            }
        }
        visited[currentNode] = true;
        if (allVisited(visited))
            {break;}
        int nextIndex = 0;
        int minDistance = INT_MAX;
        for (int i = 0; i < _vertices; i++)
        {
            if (!visited[i] && distance[i] < minDistance)
            {
                minDistance = distance[i];
                nextIndex = i;
            }
        }
        currentNode = nextIndex;
    }

    int par = parent[target];
    vector<int> retVal;

    retVal.push_back(target);


    while (par != -1)
    {
        retVal.push_back(par);
        par = parent[par];
    }


    reverse(retVal.begin(),retVal.end());
    return retVal;
}

/********************************************************
 * vector<int> Graph<T>::getVertices(int source, int target)
 * ------------------------------------------------------
 * Precondition: source (int) //IN - the starting vertice
 *               target (int) //IN - the ending vertice
 * Postcondition: return to the vector containing the vertices
 *                needed for the trip
 ********************************************************/
template <class T>
vector<size_t> Graph<T>::getVertices(size_t source, size_t target)
{
    vector<size_t> answer;
    size_t distance[_vertices];
    bool allowed_set[_vertices];
    size_t allowed_size, next, i, sum;
    size_t store_sets[_vertices];

    for(i = 0; i <= _vertices; i++)
    {
        store_sets[i] = -1;
        distance[i] = INFINITY;  // initialize the distance array to all infin
        allowed_set[i] = true;   // initialize the allowed set to all true
    }

    distance[source] = 0;
    answer.push_back(source);

    for(allowed_size = 1; allowed_size <= _vertices; allowed_size++)
    {
        next = minIndex(distance, allowed_set); // index of minium distance

        allowed_set[next] = false; // not an allowed set now

        for(i = 0; i < _vertices; i++)
        {
            if((allowed_set[i]) && (is_edge(next, i)) &&
                    distance[next] != INFINITY)
            {
                sum = distance[next] + _edges[next][i];
                if(sum < distance[i])
                {
                    store_sets[i] = next;
                    distance[i] = sum;
                }
            }
        }

        if(next == target)
            break;
    }

    getPath(answer, store_sets, target);

    for(size_t i = 0; i < answer.size( ); i++)
        cout << _labels[answer.at(i)] << endl;

    return answer;
}

/********************************************************
 * void Graph<T>::getPath(vector<size_t>& store, size_t parent[],size_t target)
 * ------------------------------------------------------
 * Postcondition: given the source and the target and the vector of vertices,
 * it takes all the paths using recursive method and put the vertices in
 * the store vector.
 ********************************************************/
template <class T>
void Graph<T>::getPath(vector<size_t>& store, size_t parent[], size_t target)
{
    if(parent[target] == -1)
        return;

    getPath(store, parent, parent[target]);
    store.push_back(target);
}

/********************************************************
 * size_t Graph<T>::getWeight(size_t fromIndex, size_t toIndex) const
 * ------------------------------------------------------
 * Postcondition: given the starting index and the end index,
 * it returns to a number of total weight between these two index
 ********************************************************/
template <class T>
size_t Graph<T>::getWeight(size_t fromIndex, size_t toIndex) const
{
    return _edges[fromIndex][toIndex];
}

/********************************************************
 * vector<vector<int>> Graph<T>::getDistanceMatrix()
 * ------------------------------------------------------
 * Postcondition: returns to the vector containing the
 * vertices from the matrix which are needed for the trip
 ********************************************************/
//outer index is the source, inner is the destination
template<class T>
vector<vector<int>> Graph<T>::getDistanceMatrix()
{
    vector<vector<int>> result;
    for (int index=0;index<_vertices;index++)
    {

        int largeInt = 100000000;
        size_t distance[_vertices];
        bool visited[_vertices];
        int parent[_vertices];
        for (int i=0;i<_vertices;i++)
        {
            parent[i] = largeInt;
            distance[i] = largeInt;
            visited[i] = false;
        }
        int currentNode = index;
        parent[index] = -1;
        visited[index] = true;
        distance[index] = 0;

        while (!allVisited(visited))
        {
            vector<int> neighborVec = unvisitedNeighbors(currentNode,visited);

            for (int i = 0; i < neighborVec.size(); i++) //unvis neighbors
            {
                if((distance[currentNode]+_edges[currentNode][neighborVec[i]])<
                        distance[neighborVec[i]])
                {
                    distance[neighborVec[i]] = distance[currentNode]+
                            _edges[currentNode][neighborVec[i]];
                    parent[neighborVec[i]] = currentNode;
                }
            }
            visited[currentNode] = true;
            if (allVisited(visited))
                {break;}
            int nextIndex = 0;
            int minDistance = INT_MAX;
            for (int i = 0; i < _vertices; i++)
            {
                if (!visited[i] && distance[i] < minDistance)
                {
                    minDistance = distance[i];
                    nextIndex = i;
                }
            }
            currentNode = nextIndex;
        }
        vector<int> distanceVector(distance, distance + sizeof distance /
                                   sizeof distance[0]);
        result.push_back(distanceVector);
    }
    return result;
}

/********************************************************
 * vector<int> Graph<T>::minPathV1(int source)
 * ------------------------------------------------------
 * Precondition: source (int) //IN - the starting vertex
 * Postcondition: returns to the vector containing the
 * vertices for the mininum path from the source
 ********************************************************/
template<class T>
vector<int> Graph<T>::minPathV1(int source)
{
    int current = source;
    bool visited[_vertices];
    for (int i=0;i<_vertices;i++)
    {
        visited[i] = false;
    }
    vector<int> totalPath;
    vector<vector<int>> distanceMatrix = getDistanceMatrix();
    visited[source]=true;
    totalPath.push_back(source);
    while (!allVisited(visited))
    {
        int nextVertex = getMinIndex(distanceMatrix[current],visited);
        totalPath.pop_back();
        vector<int> tempPath = getVerticesJosh(current,nextVertex);
        for (int i=0;i<tempPath.size();i++)
        {
            totalPath.push_back(tempPath[i]);
        }
        visited[nextVertex] = true;
        current = nextVertex;
    }
    return totalPath;
}

/********************************************************
 * vector<int> Graph<T>::minPathV2(int source)
 * ------------------------------------------------------
 * Precondition: source (int) //IN - the starting vertex
 * Postcondition: returns to the vector containing the
 * vertices for the mininum path from the source
 ********************************************************/
template<class T>
vector<int> Graph<T>::minPathV2(int source)
{
    int current = source;
    bool visited[_vertices];
    for (int i=0;i<_vertices;i++)
    {
        visited[i] = false;
    }
    vector<int> totalPath;
    vector<vector<int>> distanceMatrix = getDistanceMatrix();
    visited[source]=true;
    totalPath.push_back(source);
    while (!allVisited(visited))
    {
        int nextVertex = getMinIndex(distanceMatrix[current],visited);
        totalPath.pop_back();
        vector<int> tempPath = getVerticesJosh(current,nextVertex);
        for (int i=0;i<tempPath.size();i++)
        {
            visited[tempPath[i]] = true;
            totalPath.push_back(tempPath[i]);
        }
        visited[nextVertex] = true;
        current = nextVertex;
    }
    return totalPath;
}

/********************************************************
 * int Graph<T>::getPathWeight(vector<int> path)
 * ------------------------------------------------------
 * Precondition: path (vector<int>) //IN - the vector of
 *               vertices for the path
 * Postcondition: returns to the weight of the path
 ********************************************************/
template<class T>
int Graph<T>::getPathWeight(vector<int> path)
{
    if (path.size()<=1)
        return -1;
    int totalDistance = 0;
    for (int i=1;i< path.size();i++)
    {
        totalDistance+=getWeight(path[i-1],path[i]);
    }
    return totalDistance;
}

/********************************************************
 * vector<int> Graph<T>::minPathV1(int source, bool allowed[])
 * ------------------------------------------------------
 * Precondition: source (int) //IN - the starting vertex
 *               allowed[] (bool) //IN - array to check the vertices
 * Postcondition: returns to the vector containing the
 * vertices for the mininum path from the source
 ********************************************************/
template<class T>
vector<int> Graph<T>::minPathV1(int source, bool allowed[])
{
    int current = source;
    bool visited[_vertices];
    for (int i=0;i<_vertices;i++)
    {
        visited[i] = false;
    }
    vector<int> totalPath;
    vector<vector<int>> distanceMatrix = getDistanceMatrix();
    visited[source]=true;
    totalPath.push_back(source);
    while (!allVisited(visited,allowed))
    {
        int nextVertex = getMinIndex(distanceMatrix[current],visited,allowed);
        totalPath.pop_back();
        vector<int> tempPath = getVerticesJosh(current,nextVertex);
        for (int i=0;i<tempPath.size();i++)
        {
            totalPath.push_back(tempPath[i]);
        }
        visited[nextVertex] = true;
        current = nextVertex;
    }
    return totalPath;
}

/********************************************************
 * vector<int> Graph<T>::minPathV2(int source, bool allowed[])
 * ------------------------------------------------------
 * Precondition: source (int) //IN - the starting vertex
 *               allowed[] (bool) //IN - array to check the vertices
 * Postcondition: returns to the vector containing the
 * vertices for the mininum path from the source
 ********************************************************/
template<class T>
vector<int> Graph<T>::minPathV2(int source, bool allowed[])
{
    int current = source;
    bool visited[_vertices];
    for (int i=0;i<_vertices;i++)
    {
        visited[i] = false;
    }
    vector<int> totalPath;
    vector<vector<int>> distanceMatrix = getDistanceMatrix();
    visited[source]=true;
    totalPath.push_back(source);
    while (!allVisited(visited,allowed))
    {
        int nextVertex = getMinIndex(distanceMatrix[current],visited,allowed);
        totalPath.pop_back();
        vector<int> tempPath = getVerticesJosh(current,nextVertex);
        for (int i=0;i<tempPath.size();i++)
        {
            visited[tempPath[i]] = true;
            totalPath.push_back(tempPath[i]);
        }
        visited[nextVertex] = true;
        current = nextVertex;
    }
    return totalPath;
}

/********************************************************
 * int Graph<T>::getMinIndex(vector<int> list, bool visited[])
 * ------------------------------------------------------
 * Precondition: list (vector<int>) //IN - the vector of weights
 *               visited[] (bool) //IN - array to check if the vertex
 *                                       is visited
 * Postcondition: returns to the minimum index from the list
 ********************************************************/
template<class T>
int Graph<T>::getMinIndex(vector<int> list, bool visited[])
{
    int min = INT_MAX;
    int retVal = -1;
    for (int i=0;i<list.size();i++)
    {
        if (visited[i])
            continue;
        if (list[i] <= min)
        {
            min = list[i];
            retVal = i;
        }

    }
    return retVal;

}

/********************************************************
 * int Graph<T>::getMinIndex(vector<int> list, bool visited[], bool allowed[])
 * ------------------------------------------------------
 * Precondition: list (vector<int>) //IN - the vector of weights
 *               visited[] (bool) //IN - array to check if the vertex
 *                                       is visited
 *               allowed[] (bool) //IN - array to check if vertex is allowed
 * Postcondition: returns to the minimum index from the list
 ********************************************************/
template<class T>
int Graph<T>::getMinIndex(vector<int> list, bool visited[], bool allowed[])
{
    int min = INT_MAX;
    int retVal = -1;
    for (int i=0;i<list.size();i++)
    {
        if (visited[i] || !allowed[i])
            continue;
        if (list[i] <= min)
        {
            min = list[i];
            retVal = i;
        }

    }
    return retVal;}

#endif // GRAPH_H
