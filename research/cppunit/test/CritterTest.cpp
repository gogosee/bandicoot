#include <cppunit/extensions/HelperMacros.h>
#include "Critter.h"
#include "CritterTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( CritterTest );

void CritterTest::TestMemorySmoke(void) {
  Memory m;
  CPPUNIT_ASSERT(  m.AssociatedP(0) );
  CPPUNIT_ASSERT(! m.AssociatedP(42) );
  CPPUNIT_ASSERT(  m.AssociatedP(3) ); /* this should fail */
}

