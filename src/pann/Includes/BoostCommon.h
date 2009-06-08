/**
 * Includes from Boost library
 * For serialization stuff see @file BoostSerialization.h
 */

#ifndef BOOSTCOMMON_H
#define BOOSTCOMMON_H

//Core dependencies
#include <boost/foreach.hpp>
#include <boost/thread.hpp>
#include <boost/thread/barrier.hpp>
#include <boost/functional/hash.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

//No need in Core
#include <boost/random.hpp> 
#include <boost/tuple/tuple.hpp>
#include <boost/function.hpp>
#include <boost/lexical_cast.hpp>

//Only external Apps
#include <boost/progress.hpp> 
#include <boost/assign/std.hpp>

//Misc.
//#include <boost/lambda/lambda.hpp>
//#include <boost/lambda/bind.hpp>
//#include <boost/any.hpp>
//#include <boost/enable_shared_from_this.hpp>

#endif

