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

    /// Sets connection weight: nodeIdFrom -> nodeIdTo = weight
    void setConnectionWeight( uint32_t nodeIdFrom, uint32_t nodeIdTo, double weight )
    {
        assert( nodeIdFrom != nodeIdTo && "Connection between same node!" );
        Connection c1( nodeIdFrom, nodeIdTo, weight );
        auto iter = connections.find( c1 );
        if( iter == connections.end() )
        {
            //Connection does not exist => create
            connections.insert( c1 );
        }
        else
        {
            //Connection exists already so change weight
            iter->weight = weight; //Changing const ref here
        }
    }

    /// Sets the connection weights between nodeIdFrom <-> nodeIdTo = weight
    void setSymmetricConnectionWeights( uint32_t nodeIdFrom, uint32_t nodeIdTo, double weight )
    {
        assert( nodeIdFrom != nodeIdTo && "Connection between same node!" );
        setConnectionWeight( nodeIdFrom, nodeIdTo, weight );
        setConnectionWeight( nodeIdTo, nodeIdFrom, weight );
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

    /// Returns 0 if no connection
    double getConnectionWeight( uint32_t nodeIdFrom, uint32_t nodeIdTo ) const
    {
        //Comparison does not care about weight so does not matter what weight I use here
        auto iter = connections.find( Connection( nodeIdFrom, nodeIdTo, 0.0 ) );
        if( iter == connections.end() )
        {
            return 0.0;
        }
        else
        {
            return iter->weight;
        }
    }

    uint32_t numConnections() const
    {
        return connections.size();
    }

    //Using "potensmetoden" and skipping weights
    vector<double> calculatePageRankings( uint32_t nIterations ) const
    {
        //Set up matrix with connections with unit weights
        vector<uint32_t> nConnectionsOut( nodes.size(), 0 );
        for( auto iter = connections.begin(); iter != connections.end(); ++iter )
        {
            uint32_t row = iter->nodeIdFrom;
            nConnectionsOut[row]++;
        }

        vector<double> lamdaWeights( nodes.size(), 0.0 );

        for( uint32_t i = 0; i < nodes.size(); ++i )
        {
            uint32_t nOutgoingConnections = nConnectionsOut[i];
            if( nOutgoingConnections == 0 )
            {
                lamdaWeights[i] = 0;
            }
            else
            {
                lamdaWeights[i] = 1.0 / double( nOutgoingConnections );
            }
        }


        //Create H matrix
        typedef Eigen::SparseMatrix<double> SparseMatrix;
        SparseMatrix H( nodes.size(), nodes.size() );
        for( auto iter = connections.begin(); iter != connections.end(); ++iter )
        {
            //Connection between nodeIdFrom -> nodeIdTo

            //Each row specifies which nodes points TO the the node with id = row
            uint32_t row = iter->nodeIdTo;
            uint32_t col = iter->nodeIdFrom;

            H.coeffRef( row, col ) = lamdaWeights[col];
        }

        std::cout << "H: \n" << H << std::endl;

        //Initial guess
        Eigen::VectorXd eigenVec( nodes.size() );

        double value = 1.0 / double( nodes.size() );
        for( uint32_t i = 0; i < nodes.size(); ++i )
        {
            eigenVec[i] = value;
        }

        for( uint32_t i = 0; i < nIterations; ++i )
        {
            eigenVec = H*eigenVec;
        }

        std::vector<double> result( nodes.size() );
        for( uint32_t i = 0; i < nodes.size(); ++i )
        {
            result[i] = eigenVec[i];
        }

        return result;
    }

private:

    struct Connection
    {
        Connection( uint32_t n1, uint32_t n2, double w ): nodeIdFrom( n1 ), nodeIdTo( n2 ), weight( w ) {}

        uint32_t nodeIdFrom;
        uint32_t nodeIdTo;
        mutable double weight; //Mutable so it can be changed in setConnectionWeight
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
