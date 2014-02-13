//
//  statVoronoi.cpp
//  ChamferSubQuad
//
//  Created by David Coeurjolly on 30/01/2014.
//
//

#include <DGtal/base/Common.h>
#include <DGtal/helpers/StdDefs.h>
#include <DGtal/geometry/volumes/distance/ChamferNorm2D.h>
#include <DGtal/geometry/volumes/distance/VoronoiMap.h>
#include <DGtal/arithmetic/IntegerComputer.h>
#include <stdio.h>
#include <DGtal/io/boards/Board2D.h>
#include <DGtal/io/colormaps/HueShadeColorMap.h>

using namespace DGtal;

template <typename Predicate>
void constructPredicate(Predicate &mySet, const unsigned int nbSeeds, const unsigned int domSize)
{
  Z2i::Point a(0,0);
  Z2i::Point b(domSize,domSize);
  Z2i::Domain domain(a,b);
  
  for(Z2i::Domain::ConstIterator it = domain.begin(), itend = domain.end();
      it != itend;
      ++it)
    mySet.insertNew( *it );
  
  Z2i::DigitalSet sites(domain);
  for(unsigned int i = 0; i < nbSeeds; i++)
    sites.insert(Z2i::Point( rand() % domSize , rand()% domSize ));
  
  for(Z2i::DigitalSet::ConstIterator it = sites.begin(), itend = sites.end();
      it != itend; ++it)
    mySet.erase (*it);
}


int main(int argc, char **argv)
{
  unsigned int maxN = 3;
  unsigned int domSize = 64;
  unsigned int nbSeeds = domSize;
  
  
  Z2i::Domain domain(Z2i::Point(0,0), Z2i::Point(domSize,domSize));
  
  DigitalSetBySTLSet<Z2i::Domain> mySet(domain);
  constructPredicate<DigitalSetBySTLSet<Z2i::Domain> >(mySet,nbSeeds, domSize);
  
  
  for(unsigned int N = 2 ; N < maxN; )
  {
    ChamferNorm2D<Z2i::Space> mask(N);
    trace.info() << mask<<std::endl;
    Z2i::Point origin(0,0);
   
    trace.beginBlock("DT distances");
  
    typedef VoronoiMap<Z2i::Space, Z2i::DigitalSet, ChamferNorm2D<Z2i::Space> > VoroChamf;
    VoroChamf voro(&domain, &mySet,&mask);
    double duration = trace.endBlock();
    
    std::cout <<mask.size()<<" "<<duration<<std::endl;
    
    N++;
    
#define SVG_EXPORT
    
#ifdef SVG_EXPORT
    Board2D board;
    HueShadeColorMap< int> map(0, 256,2);
    board.setUnit ( LibBoard::Board::UCentimeter );

    for(VoroChamf::Domain::ConstIterator it=voro.domain().begin(),
        itend=voro.domain().end(); it!= itend;
        ++it)
    {
      Z2i::Point p = voro(*it);
      int c = abs(p[1]*11+ p[0]*17);
      if (p == *it)
        board << CustomStyle( (*it).className(), new CustomColors(Color::Black,Color::Black));
      else
        board << CustomStyle( (*it).className(), new CustomColors(map(c%256),map(c%256)));
    
      board << (*it);
    }
    trace.info()<<"Exporting"<<std::endl;
    std::string title = "image-voro-chamf_"+ boost::lexical_cast<std::string>(N) +".png" ;
    board.saveCairo(title.c_str(), Board2D::CairoPNG );
    trace.info()<<"Exporting CAIRO"<<std::endl;

        
    
#endif
    
  }
  
  return 0;
}