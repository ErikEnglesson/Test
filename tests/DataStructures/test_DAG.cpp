#include <gtest/gtest.h>
#include "../../Eigen/Dense"
#include "../../DAG.h"
#include "../../common.h"

using namespace Eigen;

struct myVertex
{
    myVertex( float v ): value(v) {}
    float value;
};

TEST(DAG, Creation)
{
    DAG<myVertex> graph;

    myVertex n0(1.0f), n1(2.0f), n2(3.0f), n3(4.0f);
    uint32_t vertexID0 = graph.addVertex( n0 );
    uint32_t vertexID1 = graph.addVertex( n1 );
    uint32_t vertexID2 = graph.addVertex( n2 );
    uint32_t vertexID3 = graph.addVertex( n3 );

    graph.setSymmetricEdgeWeights( vertexID0, vertexID1, 1.0 );
    graph.setSymmetricEdgeWeights( vertexID0, vertexID2, 2.0 );
    graph.setSymmetricEdgeWeights( vertexID3, vertexID1, 3.0 );

    graph.setEdgeWeight( vertexID3, vertexID0, 4.0 );

    EXPECT_EQ( graph.numEdges(), 7 );

    //Set weight to the same
    graph.setEdgeWeight( vertexID3, vertexID0, 4.0 );
    EXPECT_EQ( graph.numEdges(), 7 );
    EXPECT_EQ( graph.getEdgeWeight( vertexID3, vertexID0 ), 4.0 );

    //Change weight
    graph.setEdgeWeight( vertexID3, vertexID0, 3.0 );
    EXPECT_EQ( graph.numEdges(), 7 );
    EXPECT_EQ( graph.getEdgeWeight( vertexID3, vertexID0 ), 3.0 );

    graph.setEdgeWeight( vertexID0, vertexID3, 5.0 );
    EXPECT_EQ( graph.numEdges(), 8 );

    graph.printEdges();

}

TEST(DAG, PageRank)
{
    DAG<myVertex> graph;

    myVertex n0(1.0f), n1(2.0f), n2(3.0f), n3(4.0f);
    uint32_t vertexID0 = graph.addVertex( n0 );
    uint32_t vertexID1 = graph.addVertex( n1 );
    uint32_t vertexID2 = graph.addVertex( n2 );
    uint32_t vertexID3 = graph.addVertex( n3 );

    graph.setEdgeWeight( vertexID0, vertexID1, 1.0 );
    graph.setEdgeWeight( vertexID1, vertexID2, 1.0 );
    graph.setEdgeWeight( vertexID1, vertexID3, 1.0 );
    graph.setEdgeWeight( vertexID2, vertexID1, 1.0 );
    graph.setEdgeWeight( vertexID2, vertexID3, 1.0 );
    graph.setEdgeWeight( vertexID2, vertexID0, 1.0 );
    graph.setEdgeWeight( vertexID3, vertexID0, 1.0 );


    std::vector<double> rankings = graph.calculatePageRankings( 14 );
    for(uint32_t i = 0; i < rankings.size(); ++i )
    {
        std::cout << "vertexID: " << i << ", has rank: " << rankings[i] << std::endl;
    }

    auto maxElement = std::max_element( rankings.begin(), rankings.end() );
    uint32_t index = std::distance( rankings.begin(), maxElement );
    std::cout << "vertexID: " << index << ", has the highest rank! \n";

}


