#include <iostream>
#include <DGtal/base/Common.h>
#include <DGtal/helpers/StdDefs.h>
#include <vector>
#include <cstdlib>
#include <string>
#include <assert.h>
#include <DGtal/io/boards/Board2D.h>

using namespace DGtal;
using namespace std;

typedef Z2i::Vector Vector;
typedef Z2i::Point Point;
typedef vector<Vector> Mask;
typedef int Abscissa;
typedef Mask::const_iterator ConstIterator;


bool LessThan(const Vector &a, const Vector &b)
{
  return (a[0]*b[1] - a[1]*b[0]) < 0;
}


bool LessEqThan(const Vector &a, const Vector &b)
{
  return (a[0]*b[1] - a[1]*b[0]) < 0;
}


/**
 * Generate a mask from m random vectors.
 *
 * @param [in] m the number of vectors.
 * @param [out] aMask the mask to populate.
 *
 */
void populateMask(const unsigned int m, Mask &aMask)
{

  aMask.clear();
  for(unsigned int i=0; i< m; i++)
    aMask.push_back(Vector( i, rand() % 10 ));  //Before
  sort(aMask.begin(), aMask.end(), LessThan );
  
  copy(aMask.begin(), aMask.end(),
       ostream_iterator<Vector>(cout, "\n"));
}

/**
 * Compute the cone in which a point belongs to using logarithmic search.
 */
unsigned int locatePoint(Mask &aMask, const Vector &p)
{
  ASSERT( LessEqThan(aMask[0], p) );
  ASSERT( LessThan(p, aMask[aMask.size()-1] ));
  
  unsigned int top=0;
  unsigned int size = aMask.size();
  while (size >1)
  {
    size = size /2;
    if ( ! LessThan( p , aMask[top+size]))
      top += size;
  }
  return top;
}

/**
 * Compute the cone in which a point belongs to using linear search.
 * When the method ends, the cone is given by iterators
 * [itBegin, itBegin+1]
 *
 * @param[in/out] itBegin the first iterator on the mask range
 * @param[in/out] itEnd the end iterator on the mask range
 * @param p the point to locate
 */
void locatePointComplete(ConstIterator &itBegin, ConstIterator &itEnd, const Vector &p)
{
  while ((itBegin != itEnd) &&
         (! (LessThan(p, *(itBegin+1)))))
  {
    itBegin ++;
  }
}


/**
 *
 *
 **/
Abscissa getVoronoiEdgeAbscissa( Mask& aMask)
{
  
  return 0;
}



int main()
{
  
  trace.info() << "LessThan (2,1) - (1,3) " << (int)LessThan(Vector(2,1), Vector(1,3)) << std::endl;
  trace.info() << "LessThan (2,1) - (3,1) " << (int)LessThan(Vector(2,1), Vector(3,1)) << std::endl;

  //Init
  Mask mask;
  populateMask(10, mask);
  
  
  //Locate
  Vector diag(5,5), p(6,5), q(12,1);
  ConstIterator itb = mask.begin();
  ConstIterator ite = mask.end();
  unsigned int pos =  locatePoint(mask, diag);
  trace.info() << " Locate diag cone = "<< mask[pos]<< " ----- " <<mask[pos+1]<<std::endl;
  itb = mask.begin();
  ite = mask.end();
  locatePointComplete(itb, ite, diag);
  trace.info() << " Locate diag cone complete = "<< *itb<< " ----- " <<*(itb + 1)<<std::endl;
  itb = mask.begin();
  ite = mask.end();
  
  pos = locatePoint( mask, p);
  trace.info() << " Locate p cone p = "<< mask[pos]<< " ----- " <<mask[pos+1]<<std::endl;
  itb = mask.begin();
  ite = mask.end();
  locatePointComplete(itb, ite, p);
  trace.info() << " Locate p cone complete = "<< *itb<< " ----- " <<*(itb + 1)<<std::endl;
  
  //Q
  itb = mask.begin();
  ite = mask.end();
  pos =  locatePoint(mask, q);
  trace.info() << " Locate q cone  = "<< mask[pos]<< " ----- " <<mask[pos+1]<<std::endl;
  itb = mask.begin();
  ite = mask.end();
  locatePointComplete(itb, ite, q);
  trace.info() << " Locate q cone complete = "<< *itb<< " ----- " <<*(itb + 1)<<std::endl;
  
  
  
  Board2D aBoard;
  for(vector<Vector>::const_iterator it = mask.begin(), itend = mask.end(); it != itend ; ++it)
    Display2DFactory::draw(aBoard, *it, Vector(0,0));
  aBoard.saveSVG("mask.svg");
  
  return 0;
  
}
