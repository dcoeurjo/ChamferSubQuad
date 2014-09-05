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
#include <DGtal/geometry/volumes/distance/DistanceTransformation.h>
#include <DGtal/arithmetic/IntegerComputer.h>
#include <stdio.h>
#include <DGtal/io/boards/Board2D.h>
#include <DGtal/io/colormaps/HueShadeColorMap.h>
#include <DGtal/geometry/volumes/distance/ExactPredicateLpSeparableMetric.h>
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


using namespace experimental;

int main(int argc, char **argv)
{
  unsigned int maxN = 500;
  unsigned int domSize = 256;
  unsigned int nbSeeds = domSize;


  Z2i::Domain domain(Z2i::Point(0,0), Z2i::Point(domSize,domSize));

  DigitalSetBySTLSet<Z2i::Domain> mySet(domain);
  constructPredicate<DigitalSetBySTLSet<Z2i::Domain> >(mySet,nbSeeds, domSize);


  trace.beginBlock("DT distances");


  typedef VoronoiMap<Z2i::Space, Z2i::DigitalSet, Z2i::L2Metric > VoroChamf;
  typedef DistanceTransformation<Z2i::Space, Z2i::DigitalSet, Z2i::L2Metric > DT;

  
  VoroChamf voro(&domain, &mySet,&Z2i::l2Metric);
  DT dt(&domain, &mySet,&Z2i::l2Metric);
  
  trace.endBlock();


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
  std::string title = "image-voro-chamf_l_2.png" ;
  board.saveCairo(title.c_str(), Board2D::CairoPNG );
  trace.info()<<"Exporting CAIRO"<<std::endl;

  
  double maxv=0;
  for(DT::Domain::ConstIterator it=dt.domain().begin(),
      itend=dt.domain().end(); it!= itend;
      ++it)
    if (dt(*it)>maxv) maxv=dt(*it);
  
  board.clear();
  HueShadeColorMap< double> map2(0, maxv,2);
  for(DT::Domain::ConstIterator it=dt.domain().begin(),
      itend=dt.domain().end(); it!= itend;
      ++it)
  {
      board << CustomStyle( (*it).className(), new CustomColors(map2(dt(*it)),map2(dt(*it))));
    board << (*it);
  }
  trace.info()<<"Exporting"<<std::endl;
  title = "image-dt-chamf_l_2.png" ;
  board.saveCairo(title.c_str(), Board2D::CairoPNG );
  trace.info()<<"Exporting CAIRO"<<std::endl;

  
  
  //5-7-11 metic
  typedef ChamferNorm2D<Z2i::Space> Metric;
  Metric::Directions dirs5711;
  Metric::Directions normals5711;
  //5-7-11 mask
  dirs5711.push_back(Z2i::Vector(0,-1));
  dirs5711.push_back(Z2i::Vector(1,-2));
  dirs5711.push_back(Z2i::Vector(1,-1));
  dirs5711.push_back(Z2i::Vector(2,-1));
  dirs5711.push_back(Z2i::Vector(1,0));
  dirs5711.push_back(Z2i::Vector(2,1));
  dirs5711.push_back(Z2i::Vector(1,1));
  dirs5711.push_back(Z2i::Vector(1,2));
  
  normals5711.push_back(Z2i::Vector(1,-5));
  normals5711.push_back(Z2i::Vector(3,-4));
  normals5711.push_back(Z2i::Vector(4,-3));
  normals5711.push_back(Z2i::Vector(5,-1));
  normals5711.push_back(Z2i::Vector(5,1));
  normals5711.push_back(Z2i::Vector(4,3));
  normals5711.push_back(Z2i::Vector(3,4));
  normals5711.push_back(Z2i::Vector(1,5));
  
  Metric mask5711(dirs5711,normals5711);
  
  
  typedef VoronoiMap<Z2i::Space, Z2i::DigitalSet, Metric> Voro5711;
  typedef DistanceTransformation<Z2i::Space, Z2i::DigitalSet, Metric> DT5711;
  
  Voro5711 voro2(&domain, &mySet,&mask5711);
  DT5711 dt2(&domain, &mySet,&mask5711);
  
  board.clear();
 
  for(Voro5711::Domain::ConstIterator it=voro2.domain().begin(),
      itend=voro2.domain().end(); it!= itend;
      ++it)
  {
    Z2i::Point p = voro2(*it);
    int c = abs(p[1]*11+ p[0]*17);
    if (p == *it)
      board << CustomStyle( (*it).className(), new CustomColors(Color::Black,Color::Black));
    else
      board << CustomStyle( (*it).className(), new CustomColors(map(c%256),map(c%256)));
    
    board << (*it);
  }
  trace.info()<<"Exporting"<<std::endl;
  title = "image-voro-chamf_5711.png" ;
  board.saveCairo(title.c_str(), Board2D::CairoPNG );
  trace.info()<<"Exporting CAIRO"<<std::endl;
  
  maxv=0;
  for(DT5711::Domain::ConstIterator it=dt2.domain().begin(),
      itend=dt2.domain().end(); it!= itend;
      ++it)
    if (dt2(*it)>maxv) maxv=dt2(*it);
  
  HueShadeColorMap< double> map3(0, maxv,2);

  board.clear();
  for(DT5711::Domain::ConstIterator it=dt2.domain().begin(),
      itend=dt2.domain().end(); it!= itend;
      ++it)
  {
    board << CustomStyle( (*it).className(), new CustomColors(map3(dt2(*it)),map3(dt2(*it))));
    board << (*it);
  }
  trace.info()<<"Exporting"<<std::endl;
  title = "image-dt-chamf_5711.png" ;
  board.saveCairo(title.c_str(), Board2D::CairoPNG );
  trace.info()<<"Exporting CAIRO"<<std::endl;
  
  

  return 0;
}
