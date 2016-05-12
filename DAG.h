#ifndef DAG_H
#define DAG_H

#include <vector>
#include <set>
#include <iostream>

#include "Eigen/Sparse"

#include "common.h"

using namespace std;



template<class T>
class DAG
{
public:
    DAG(){}

    /// Add node to DAG
    uint32_t addNode( const T& node )
    {
        nodes.push_back( node );
        return nodes.size()-1;
    }

    /// Create a connection from nodeIdFrom to nodeIdTo with weight
    void createConnection( uint32_t nodeIdFrom, uint32_t nodeIdTo, double weight )
    {
        connections.emplace( nodeIdFrom, nodeIdTo, weight );
    }

    /// Create a symmetric connection between two nodes and give the connection a weight
    void createSymmetricConnection( uint32_t nodeIdFrom, uint32_t nodeIdTo, double weight )
    {
        connections.emplace( nodeIdFrom, nodeIdTo, weight );
        connections.emplace( nodeIdTo, nodeIdFrom, weight );
    }

    /// Prints the connection matrix
    void printConnections() const
    {
        typedef Eigen::SparseMatrix<double> SparseMatrix;
        SparseMatrix m( nodes.size(), nodes.size() );
        for( auto iter = connections.begin(); iter != connections.end(); ++iter )
        {
            uint32_t row = iter->nodeIdFrom;
            uint32_t col = iter->nodeIdTo;
            m.coeffRef( row, col ) = iter->weight;
        }

        std::cout << "Connections: \n" << m << std::endl;
    }

private:

    struct Connection
    {
        Connection( uint32_t n1, uint32_t n2, double w ): nodeIdFrom( n1 ), nodeIdTo( n2 ), weight( w ) {}

        uint32_t nodeIdFrom;
        uint32_t nodeIdTo;
        double weight;
    };

    vector<T> nodes;

    struct classcomp {
      bool operator() (const Connection& lhs, const Connection& rhs) const
      {
          uint32_t i1 = lhs.nodeIdFrom;
          uint32_t j1 = lhs.nodeIdTo;

          uint32_t i2 = rhs.nodeIdFrom;
          uint32_t j2 = rhs.nodeIdTo;

          if( i1 < i2 ) return true;
          else if( i1 > i2 ) return false;
          else if( i1 == i2 && j1 < j2 ) return true;
          else return false;
      }
    };

    set< Connection, classcomp > connections;
};

#endif // DAG_H
