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

    /// Add vertex to DAG
    uint32_t addVertex( const T& vertex )
    {
        vertices.push_back( vertex );
        return vertices.size()-1;
    }

    /// Sets connection weight: vertexIdFrom -> vertexIdTo = weight
    void setEdgeWeight( uint32_t vertexIdFrom, uint32_t vertexIdTo, double weight )
    {
        assert( vertexIdFrom != vertexIdTo && "Edge between same vertex!" );
        Edge c1( vertexIdFrom, vertexIdTo, weight );
        auto iter = edges.find( c1 );
        if( iter == edges.end() )
        {
            //Edge does not exist => create
            edges.insert( c1 );
        }
        else
        {
            //Edge exists already so change weight
            iter->weight = weight; //Changing const ref here
        }
    }

    /// Sets the connection weights between vertexIdFrom <-> vertexIdTo = weight
    void setSymmetricEdgeWeights( uint32_t vertexIdFrom, uint32_t vertexIdTo, double weight )
    {
        assert( vertexIdFrom != vertexIdTo && "Edge between same vertex!" );
        setEdgeWeight( vertexIdFrom, vertexIdTo, weight );
        setEdgeWeight( vertexIdTo, vertexIdFrom, weight );
    }

    /// Prints the connection matrix
    void printEdges() const
    {
        typedef Eigen::SparseMatrix<double> SparseMatrix;
        SparseMatrix m( vertices.size(), vertices.size() );
        for( auto iter = edges.begin(); iter != edges.end(); ++iter )
        {
            uint32_t row = iter->vertexIdFrom;
            uint32_t col = iter->vertexIdTo;
            m.coeffRef( row, col ) = iter->weight;
        }

        std::cout << "Edges: \n" << m << std::endl;
    }

    /// Returns 0 if no connection
    double getEdgeWeight( uint32_t vertexIdFrom, uint32_t vertexIdTo ) const
    {
        //Comparison does not care about weight so does not matter what weight I use here
        auto iter = edges.find( Edge( vertexIdFrom, vertexIdTo, 0.0 ) );
        if( iter == edges.end() )
        {
            return 0.0;
        }
        else
        {
            return iter->weight;
        }
    }

    uint32_t numEdges() const
    {
        return edges.size();
    }

    //Using "potensmetoden" and skipping weights
    vector<double> calculatePageRankings( uint32_t nIterations ) const
    {
        //Set up matrix with edges with unit weights
        vector<uint32_t> nEdgesOut( vertices.size(), 0 );
        for( auto iter = edges.begin(); iter != edges.end(); ++iter )
        {
            uint32_t row = iter->vertexIdFrom;
            nEdgesOut[row]++;
        }

        vector<double> lamdaWeights( vertices.size(), 0.0 );

        for( uint32_t i = 0; i < vertices.size(); ++i )
        {
            uint32_t nOutgoingEdges = nEdgesOut[i];
            if( nOutgoingEdges == 0 )
            {
                lamdaWeights[i] = 0;
            }
            else
            {
                lamdaWeights[i] = 1.0 / double( nOutgoingEdges );
            }
        }


        //Create H matrix
        typedef Eigen::SparseMatrix<double> SparseMatrix;
        SparseMatrix H( vertices.size(), vertices.size() );
        for( auto iter = edges.begin(); iter != edges.end(); ++iter )
        {
            //Edge between vertexIdFrom -> vertexIdTo

            //Each row specifies which vertices points TO the the vertex with id = row
            uint32_t row = iter->vertexIdTo;
            uint32_t col = iter->vertexIdFrom;

            H.coeffRef( row, col ) = lamdaWeights[col];
        }

        std::cout << "H: \n" << H << std::endl;

        //Initial guess
        Eigen::VectorXd eigenVec( vertices.size() );

        double value = 1.0 / double( vertices.size() );
        for( uint32_t i = 0; i < vertices.size(); ++i )
        {
            eigenVec[i] = value;
        }

        for( uint32_t i = 0; i < nIterations; ++i )
        {
            eigenVec = H*eigenVec;
        }

        std::vector<double> result( vertices.size() );
        for( uint32_t i = 0; i < vertices.size(); ++i )
        {
            result[i] = eigenVec[i];
        }

        return result;
    }

private:

    struct Edge
    {
        Edge( uint32_t n1, uint32_t n2, double w ): vertexIdFrom( n1 ), vertexIdTo( n2 ), weight( w ) {}

        uint32_t vertexIdFrom;
        uint32_t vertexIdTo;
        mutable double weight; //Mutable so it can be changed in setEdgeWeight
    };

    vector<T> vertices;

    struct classcomp {
      bool operator() (const Edge& lhs, const Edge& rhs) const
      {
          uint32_t i1 = lhs.vertexIdFrom;
          uint32_t j1 = lhs.vertexIdTo;

          uint32_t i2 = rhs.vertexIdFrom;
          uint32_t j2 = rhs.vertexIdTo;

          if( i1 < i2 ) return true;
          else if( i1 > i2 ) return false;
          else if( i1 == i2 && j1 < j2 ) return true;
          else return false;
      }
    };

    set< Edge, classcomp > edges;
};

#endif // DAG_H
