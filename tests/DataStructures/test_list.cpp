#include "../../List.h"

TEST(ListTests, Add)
{
    List<int> myList;
    myList.add( 0 ); myList.add( 1 );
    myList.add( 2 ); myList.add( 1 );
    myList.print();
    EXPECT_EQ( 4, myList.size() );
}

TEST(ListTests, AddAndRemove) {
    List<int> myList;
    myList.add( 0 ); myList.add( 1 );
    myList.add( 2 ); myList.add( 1 );

    printf("Removing value 1 from list!\n");
    myList.remove(1);
    myList.print();

    printf("Adding 1 and 1338!\n");
    myList.add( 1 ); myList.add( 1338 );
    myList.print();
    EXPECT_EQ( 4, myList.size() );
}
