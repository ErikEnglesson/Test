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

    nodes.createSymmetricConnection( nodeID0, nodeID1, 1.0 );
    nodes.createSymmetricConnection( nodeID0, nodeID2, 2.0 );
    nodes.createSymmetricConnection( nodeID3, nodeID1, 3.0 );

    nodes.createConnection( nodeID3, nodeID0, 4.0 );

    nodes.printConnections();
}

