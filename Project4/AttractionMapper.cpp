#include "provided.h"
#include <string>
#include "MyMap.h"
#include <cctype>
#include "support.h"
using namespace std;

class AttractionMapperImpl
{
public:
	AttractionMapperImpl();
	~AttractionMapperImpl();
	void init(const MapLoader& ml);
	bool getGeoCoord(string attraction, GeoCoord& gc) const;
  void operator=(const GeoCoord &other);
  
private:
  MyMap<string, GeoCoord> m_attr;
};

AttractionMapperImpl::AttractionMapperImpl()
{
}

AttractionMapperImpl::~AttractionMapperImpl()
{
}

void AttractionMapperImpl::operator=(const GeoCoord &other)
{
  
}

void AttractionMapperImpl::init(const MapLoader& ml)
{
  StreetSegment seg;
  
  //Run into every street segment in the mapdata.txt file
  for (size_t i = 0; i < ml.getNumSegments(); i++)
  {
    if (ml.getSegment(i, seg))
    {
      //Run into every attraction in the mapdata.txt file
      for (size_t j = 0; j < seg.attractions.size(); j++)
      {
        string str = "";
        
        for(size_t k = 0; k < seg.attractions[j].name.size(); k++) {
          if(isalpha(seg.attractions[j].name[k])) {
            str += tolower(seg.attractions[j].name[k]);
          } else {
            str += seg.attractions[j].name[k];
          }
        }
        
        m_attr.associate(str, seg.attractions[j].geocoordinates);
      }
    }
  }
}

bool AttractionMapperImpl::getGeoCoord(string attraction, GeoCoord& gc) const
{
  string str = "";
  //Check attraction
  for(int i = 0; i < attraction.size(); i++) {
    if(isalpha(attraction[i])) {
      str+=tolower(attraction[i]);
    } else {
      str+= attraction[i];
    }
  }
  cout << str << endl;
  const GeoCoord *a = m_attr.find(str);
  
  if (a != nullptr)
  {
    gc.longitude = a->longitude;
    gc.latitude = a->latitude;
    gc.longitudeText = a->longitudeText;
    gc.latitudeText = a->latitudeText;
    return true;
  }
  
	return false; 
}

//******************** AttractionMapper functions *****************************

// These functions simply delegate to AttractionMapperImpl's functions.
// You probably don't want to change any of this code.

AttractionMapper::AttractionMapper()
{
	m_impl = new AttractionMapperImpl;
}

AttractionMapper::~AttractionMapper()
{
	delete m_impl;
}

void AttractionMapper::init(const MapLoader& ml)
{
	m_impl->init(ml);
}

bool AttractionMapper::getGeoCoord(string attraction, GeoCoord& gc) const
{
	return m_impl->getGeoCoord(attraction, gc);
}
