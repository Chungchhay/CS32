#include "provided.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "support.h"
using namespace std;

class MapLoaderImpl
{
public:
	MapLoaderImpl();
	~MapLoaderImpl();
	bool load(string mapFile);
	size_t getNumSegments() const;
	bool getSegment(size_t segNum, StreetSegment& seg) const;
  
private:
  vector<StreetSegment> vec;
};

MapLoaderImpl::MapLoaderImpl()
{
}

MapLoaderImpl::~MapLoaderImpl()
{
  for (size_t i = 0; i < vec.size(); i++)
  {
    for (size_t j = 0; j < vec[i].attractions.size(); j++)
      vec[i].attractions.clear();
    
    vec.clear();
  }
}

bool MapLoaderImpl::load(string mapFile)
{
  ifstream infile(mapFile); 
  if (!infile)
  {
    cerr << "Error: Cannot open data.txt!" << endl;
    return false;
  }
  
  string m_name, seg, attr;
  
  //First we have to read the name
  while (getline(infile, m_name))
  {
    StreetSegment temp;
    string lat1, lon1, lat2, lon2, lat3, lon3;
    int k;
    
    //Get lat and long
    getline(infile, seg);
    
    //First coord
    string delimiter = ", ";
    lat1 = seg.substr(0, seg.find(delimiter));
    seg.erase(0, seg.find(delimiter) + delimiter.length());
    
    
    delimiter = " ";
    lon1 = seg.substr(0, seg.find(delimiter));
    seg.erase(0, seg.find(delimiter) + delimiter.length());
    
    //Second coord
    delimiter = ",";
    lat2 = seg.substr(0, seg.find(delimiter));
    seg.erase(0, seg.find(delimiter) + delimiter.length());

    lon2 = seg;
    
    //GeoCoord for lat and lon start and end
    GeoCoord a(lat1, lon1);
    GeoCoord b(lat2, lon2);
    
    //GeoSegment for 2 GeoCoord
    GeoSegment m_segment(a, b);
    
    //store the name the of street and the segment into streetSegment
    temp = {m_name, m_segment};
    
    m_name = "";
    string m_attr;
    getline(infile, m_attr);
    k = stoi(m_attr);
    
    for (int i = 0; i < k; i++)
    {
      getline(infile, attr);
      
      //Separate its name from lat and long
      string delimiter = "|";
      m_name = attr.substr(0, attr.find(delimiter));
      attr.erase(0, attr.find(delimiter) + delimiter.length());
      
      //get lat and long
      delimiter = ", ";
      lat3 = attr.substr(0, attr.find(delimiter));
      attr.erase(0, attr.find(delimiter) + delimiter.length());
      
      lon3 = attr;
      
      //Store lat and long
      GeoCoord c(lat3, lon3);
      
      Attraction m_attr = {m_name, c};
      temp.attractions.push_back(m_attr);
    }
  
    vec.push_back(temp);
  }
  
	return true;
}

size_t MapLoaderImpl::getNumSegments() const
{
  //Return the size of the vector
  return vec.size();
}

bool MapLoaderImpl::getSegment(size_t segNum, StreetSegment &seg) const
{
  //Since segNum is size_t, it is also positive
  //We just need to check if it is less than the size of the vector
  //Store each data into seg
  if (segNum < getNumSegments())
  {
    if (!seg.attractions.empty())
      seg.attractions.clear();
      
    seg.streetName = vec[segNum].streetName;
    
    seg.segment.start.latitudeText = vec[segNum].segment.start.latitudeText;
    seg.segment.start.longitudeText = vec[segNum].segment.start.longitudeText;
    seg.segment.start.latitude = vec[segNum].segment.start.latitude;
    seg.segment.start.longitude = vec[segNum].segment.start.longitude;
    
    seg.segment.end.latitudeText = vec[segNum].segment.end.latitudeText;
    seg.segment.end.longitudeText = vec[segNum].segment.end.longitudeText;
    seg.segment.end.latitude = vec[segNum].segment.end.latitude;
    seg.segment.end.longitude = vec[segNum].segment.end.longitude;
    
    for (int i = 0; i < vec[segNum].attractions.size(); i++)
    {
      Attraction temp = vec[segNum].attractions[i];
      seg.attractions.push_back(temp);
    }
    
    return true;
  }
	return false;
}

//******************** MapLoader functions ************************************

// These functions simply delegate to MapLoaderImpl's functions.
// You probably don't want to change any of this code.

MapLoader::MapLoader()
{
	m_impl = new MapLoaderImpl;
}

MapLoader::~MapLoader()
{
	delete m_impl;
}

bool MapLoader::load(string mapFile)
{
	return m_impl->load(mapFile);
}

size_t MapLoader::getNumSegments() const
{
	return m_impl->getNumSegments();
}

bool MapLoader::getSegment(size_t segNum, StreetSegment& seg) const
{
   return m_impl->getSegment(segNum, seg);
}
