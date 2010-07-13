/**
 * @file test_DigitalSet.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France

 * @author Sebastien Fourey (\c Sebastien.Fourey@greyc.ensicaen.fr )
 * Groupe de Recherche en Informatique, Image, Automatique et
 * Instrumentation de Caen - GREYC (CNRS, UMR 6072), ENSICAEN, France
 *
 * @date 2010/07/01
 *
 * This file is part of the DGtal library
 */

/**
 * Description of test_DigitalSet <p>
 * Aim: simple tests of models of \ref CDigitalSet
 */

#include <cstdio>
#include <cmath>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

#include "DGtal/base/Common.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/kernel/sets/DigitalSetBySTLVector.h"
#include "DGtal/kernel/sets/DigitalSetBySTLSet.h"
#include "DGtal/kernel/sets/DigitalSetSelector.h"
#include "DGtal/kernel/sets/DigitalSetDomain.h"

using namespace DGtal;
using namespace std;


#define INBLOCK_TEST(x) \
  nbok += ( x ) ? 1 : 0; \
  nb++; \
  trace.info() << "(" << nbok << "/" << nb << ") " \
	       << #x << std::endl;

#define INBLOCK_TEST2(x,y) \
  nbok += ( x ) ? 1 : 0; \
  nb++; \
  trace.info() << "(" << nbok << "/" << nb << ") " \
  << y << std::endl;

template < typename DigitalSetType >
bool testDigitalSet( const typename DigitalSetType::DomainType & domain )
{
  typedef typename DigitalSetType::DomainType DomainType;
  typedef typename DomainType::Point Point;
  typedef typename Point::Coordinate Coordinate;
  unsigned int nbok = 0;
  unsigned int nb = 0;
 
  trace.beginBlock ( "Constructor." );

  DigitalSetType set1( domain );
  nbok += set1.size() == 0 ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "Empty set: " << set1 << std::endl;
  trace.endBlock();

  Coordinate t []= { 4, 3, 3 ,4};
  Point p1( t );
  Coordinate t2[] = { 2, 5, 3 ,5};
  Point p2( t2 );
  Coordinate t3[]=  { 2, 5, 3 ,4} ;
  Point p3( t3);

  trace.beginBlock ( "Insertion." );
  set1.insert( p1 );
  set1.insert( p2 );
  set1.insert( p3 );
  set1.insert( p2 );
  nbok += set1.size() == 3 ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "Set (3 elements): " << set1 << std::endl;
  trace.endBlock();

  return nbok == nb;
}

template < typename DigitalDomainType, int props >
bool testDigitalSetSelector( const DigitalDomainType & domain,
			     const std::string & comment )
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
 
  trace.beginBlock ( "Test DigitalSetSelector( " + comment + ")." );

  typedef typename DigitalSetSelector
    < DigitalDomainType, props >::Type SpecificSet; 
  SpecificSet set1( domain );
  set1.insert( domain.lowerBound() );
  set1.insert( domain.upperBound() );
  nbok += set1.size() == 2 ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << comment << " (2 elements): " << set1 << std::endl;

  trace.endBlock();

  return nbok == nb;
}

bool testDigitalSetDomain()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  typedef SpaceND<int,2> Z2;
  typedef HyperRectDomain<Z2> DomainType;
  typedef Z2::Point Point;
  Point p1(  -449, -449  );
  Point p2(  449, 449  );
  DomainType domain( p1, p2 );
  typedef DigitalSetSelector
    < DomainType, BIG_DS + HIGH_ITER_DS + HIGH_BEL_DS >::Type SpecificSet; 
  SpecificSet disk( domain );
  Point c(  0, 0  );
  Point l(  449, 0  );

  trace.beginBlock ( "Creating disk( r=450.0 ) ..." );
  for ( DomainType::ConstIterator it = domain.begin(); 
	it != domain.end();
	++it )
    {
      if ( (*it - c ).norm() < 450.0 )
	// insertNew is very important for vector container.
	disk.insertNew( *it );
    }
  disk.erase( c );
  INBLOCK_TEST( disk.size() == 636100 );
  trace.endBlock();

  typedef DigitalSetDomain< SpecificSet > RestrictedDomain;
  RestrictedDomain disk_domain( disk );
  trace.beginBlock ( "Iterating over disk domain ..." );
  unsigned int nb_in_domain = 0;
  for ( RestrictedDomain::ConstIterator it = disk_domain.begin(); 
	it != disk_domain.end();
	++it )
    {
      ++nb_in_domain;
    }
  INBLOCK_TEST( nb_in_domain == 636100 );
  INBLOCK_TEST( disk_domain.lowerBound() == Point(  -449, -449 ) );
  INBLOCK_TEST( disk_domain.upperBound() == Point(   449,  449 ) );
  trace.endBlock();

  return nbok == nb;
}

int main()
{
  typedef SpaceND<int,4> Space4Type;
  typedef HyperRectDomain<Space4Type> DomainType;
  typedef Space4Type::Point Point;
  
  int t[] =  { 1, 2, 3 ,4};
  Point a ( t );
  int t2[]={ 5, 5, 3 ,5};
  Point b ( t2 );
  trace.beginBlock ( "HyperRectDomain init" );

  ///Domain characterized by points a and b
  DomainType domain ( a,b );
  trace.info() << domain << std::endl;
  trace.info() << "Domain Extent= "<< domain.extent() << std::endl;
  trace.endBlock();
  
  trace.beginBlock( "DigitalSetBySTLVector" );
  bool okVector = testDigitalSet< DigitalSetBySTLVector<DomainType> >( domain );
  trace.endBlock();
  
  trace.beginBlock( "DigitalSetBySTLSet" );
  bool okSet = testDigitalSet< DigitalSetBySTLSet<DomainType> >( domain );
  trace.endBlock();

  bool okSelectorSmall = testDigitalSetSelector
    < DomainType, SMALL_DS+LOW_VAR_DS+LOW_ITER_DS+LOW_BEL_DS >
    ( domain, "Small set" );

  bool okSelectorBig = testDigitalSetSelector
    < DomainType, BIG_DS+LOW_VAR_DS+LOW_ITER_DS+LOW_BEL_DS >
    ( domain, "Big set" );

  bool okSelectorMediumHBel = testDigitalSetSelector
    < DomainType, MEDIUM_DS+LOW_VAR_DS+LOW_ITER_DS+HIGH_BEL_DS >
    ( domain, "Medium set + High belonging test" );

  bool okDigitalSetDomain = testDigitalSetDomain();

  bool res = okVector && okSet 
    && okSelectorSmall && okSelectorBig && okSelectorMediumHBel
    && okDigitalSetDomain;
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}

/** @ingroup Tests **/
