#include "catch.hpp"

#include "ResourceManager.hpp"

TEST_CASE("copy semantics", "[]")
{
    {
        ResourceManager rm1;
        ResourceManager rm2{rm1};

        REQUIRE(rm1.get() == rm2.get());

        ResourceManager rm3;
        rm3 = rm2;
        REQUIRE(rm1.get() == rm3.get());
        // test extention:
        ResourceManager rm4, rm5;
        ResourceManager rm6{rm5};
        rm5 = rm4;
        REQUIRE(rm4.get() == rm5.get());
        //  nie wiem jak ale chce sprawdzic czy bo przypisaniu do rm5 rm4 rm6 nadal ma dostep do
        //  obiektu:
        REQUIRE_NOTHROW(rm6.get());
        rm5 = rm5;
        REQUIRE_NOTHROW(rm5.get());
    }
    REQUIRE(ConstructionTracker::live == 0);
}
