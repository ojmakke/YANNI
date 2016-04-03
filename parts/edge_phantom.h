#ifndef EDGE_PHANTOM_H
#define EDGE_PHANTOM_H


// Friend of inheritor
// Makes friends of of the inheritor only see protected :)
template<typename T>
class Node;

template<typename T>
class Edge;

template<typename T>
class Edge_Phantom
{
  friend class Edge<T>;
private:
  // This is for internal use of edge.
  // For dropoff, i.e. assume not connected.
  bool is_connected;

  // Value assigned to the edge
  T value;

  // Value used by the edge, seen by the world
  // Exeriment: Attempting to minimize methods.
  // Attempting to get rid of get_value()..
  T effective_value;

  // Nodes know about these.
  Node<T> *n;	// Link to next nodes
  Node<T> *p;	// Link to previous node.

public:
  Edge_Phantom(){}
};

#endif // EDGE_PHANTOM_H
