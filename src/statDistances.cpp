//
//  statDistances.cpp
//  ChamferSubQuad
//
//  Created by David Coeurjolly on 22/12/2013.
//
//

#include <DGtal/base/Common.h>
#include <DGtal/helpers/StdDefs.h>
#include <DGtal/geometry/volumes/distance/ChamferNorm2D.h>
#include <DGtal/arithmetic/IntegerComputer.h>
#include <stdio.h>

using namespace DGtal;

template< typename Mask, typename Point>
double bruteForceDT( Mask &avec, const Point &p, const Point &q)
{
  double maxdot=0;
  typename Mask::Vector d = q-p;
  
  for(typename Mask::ConstIterator it = avec.begin(), itend = avec.end();
      it != itend; ++it)
    if (( (*it)[0]*d[0] + (*it)[1]*d[1]) > maxdot)
      maxdot = (*it)[0]*d[0] + (*it)[1]*d[1];
  return maxdot;
}

int main(int argc, char **argv)
{
  double accum = 0.0;
  
  for(unsigned int N = 3 ; N < 10000; N++)
  {
    ChamferNorm2D<Z2i::Space> mask(N);
    trace.info() << mask<<std::endl;
    Z2i::Point origin(0,0), p;
    trace.beginBlock("10000 distances");
    for(unsigned int k = 0; k < 10000 ; k++)
    {
      p[0] = rand();
      p[1] = rand();
      accum += mask(origin,p);
    }
    double duration = trace.endBlock();
    trace.beginBlock("10000 distances (brute)");
    for(unsigned int k = 0; k < 10000 ; k++)
    {
      p[0] = rand();
      p[1] = rand();
      accum += bruteForceDT(mask,origin,p);
    }
    double duration2 = trace.endBlock();
    std::cout <<N<<" "<<duration<<" "<<duration2<<std::endl;
  }
  trace.info() << accum<<std::endl;
  
  return 0;
}