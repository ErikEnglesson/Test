#include <gtest/gtest.h>
#include "../../Eigen/Dense"
#include "../../DAG.h"

#include "../../common.h"

using namespace Eigen;

struct myNode
{
    myNode( float v ): value(v) {}
    float value;
};

TEST(DAG, Creation)
{
    DAG<myNode> nodes;

    myNode n0(1.0f), n1(2.0f), n2(3.0f), n3(4.0f);
    uint32_t nodeID0 = nodes.addNode( n0 );
    uint32_t nodeID1 = nodes.addNode( n1 );
    uint32_t nodeID2 = nodes.addNode( n2 );
    uint32_t nodeID3 = nodes.addNode( n3 );

    nodes.setSymmetricConnectionWeights( nodeID0, nodeID1, 1.0 );
    nodes.setSymmetricConnectionWeights( nodeID0, nodeID2, 2.0 );
    nodes.setSymmetricConnectionWeights( nodeID3, nodeID1, 3.0 );

    nodes.setConnectionWeight( nodeID3, nodeID0, 4.0 );

    EXPECT_EQ( nodes.numConnections(), 7 );

    //Set weight to the same
    nodes.setConnectionWeight( nodeID3, nodeID0, 4.0 );
    EXPECT_EQ( nodes.numConnections(), 7 );
    EXPECT_EQ( nodes.getConnectionWeight( nodeID3, nodeID0 ), 4.0 );

    //Change weight
    nodes.setConnectionWeight( nodeID3, nodeID0, 3.0 );
    EXPECT_EQ( nodes.numConnections(), 7 );
    EXPECT_EQ( nodes.getConnectionWeight( nodeID3, nodeID0 ), 3.0 );

    nodes.setConnectionWeight( nodeID0, nodeID3, 5.0 );
    EXPECT_EQ( nodes.numConnections(), 8 );

    nodes.printConnections();

}

TEST(DAG, PageRank)
{
    DAG<myNode> nodes;

    myNode n0(1.0f), n1(2.0f), n2(3.0f), n3(4.0f);
    uint32_t nodeID0 = nodes.addNode( n0 );
    uint32_t nodeID1 = nodes.addNode( n1 );
    uint32_t nodeID2 = nodes.addNode( n2 );
    uint32_t nodeID3 = nodes.addNode( n3 );

    nodes.setConnectionWeight( nodeID0, nodeID1, 1.0 );
    nodes.setConnectionWeight( nodeID1, nodeID2, 1.0 );
    nodes.setConnectionWeight( nodeID1, nodeID3, 1.0 );
    nodes.setConnectionWeight( nodeID2, nodeID1, 1.0 );
    nodes.setConnectionWeight( nodeID2, nodeID3, 1.0 );
    nodes.setConnectionWeight( nodeID2, nodeID0, 1.0 );
    nodes.setConnectionWeight( nodeID3, nodeID0, 1.0 );


    std::vector<double> rankings = nodes.calculatePageRankings( 14 );
    for(uint32_t i = 0; i < rankings.size(); ++i )
    {
        std::cout << "NodeID: " << i << ", has rank: " << rankings[i] << std::endl;
    }

    auto maxElement = std::max_element( rankings.begin(), rankings.end() );
    uint32_t index = std::distance( rankings.begin(), maxElement );
    std::cout << "NodeID: " << index << ", has the highest rank! \n";

}


