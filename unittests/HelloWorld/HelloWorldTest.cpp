#include "blop/HelloWorld/HelloWorld.h"

#include <boost/test/unit_test.hpp>

using namespace blop;

BOOST_AUTO_TEST_CASE(answerToLifeUniverseAndEverything)
{
  HelloWorld h;
  BOOST_CHECK(h.getAnswerToLifeUniverseAndEverything() == 42);
}
