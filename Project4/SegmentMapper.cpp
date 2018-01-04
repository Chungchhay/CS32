#include "provided.h"
#include <vector>
#include "MyMap.h"
#include "support.h"

using namespace std;

class SegmentMapperImpl
{
public:
	SegmentMapperImpl();
	~SegmentMapperImpl();
	void init(const MapLoader& ml);
	vector<StreetSegment> getSegments(const GeoCoord& gc) const;
  
private:
  MyMap<GeoCoord, vector<StreetSegment>> m_seg;
};

SegmentMapperImpl::SegmentMapperImpl()
{
}

SegmentMapperImpl::~SegmentMapperImpl()
{
}

void SegmentMapperImpl::init(const MapLoader& ml)
{
  StreetSegment seg;
  size_t numberOfSegments = ml.getNumSegments();
  
  //Run into every street segment in the mapdata.txt file
  for (size_t i = 0; i < numberOfSegments; i++)
  {
    if (ml.getSegment(i, seg))
    {
      //make an empty vector
      vector<StreetSegment> temp = {};
      
      //Run into every attraction in the mapdata.txt file
      size_t numberOfAttractions = seg.attractions.size();
      for (size_t j = 0; j < numberOfAttractions; j++)
      {
        if (m_seg.find(seg.attractions[j].geocoordinates) == nullptr)
          m_seg.associate(seg.attractions[j].geocoordinates, temp);
        
        m_seg.find(seg.attractions[j].geocoordinates)->push_back(seg);
      }
      
      if (m_seg.find(seg.segment.start) == nullptr)
        m_seg.associate(seg.segment.start, temp);
      
      m_seg.find(seg.segment.start)->push_back(seg);
      
      if (m_seg.find(seg.segment.end) == nullptr)
        m_seg.associate(seg.segment.end, temp);
      
      m_seg.find(seg.segment.end)->push_back(seg);

    }
  }
}

vector<StreetSegment> SegmentMapperImpl::getSegments(const GeoCoord& gc) const
{
	const vector<StreetSegment> *segments = m_seg.find(gc);
  
  if (segments != nullptr)
    return *segments;
  
  return {};
}

//******************** SegmentMapper functions ********************************

// These functions simply delegate to SegmentMapperImpl's functions.
// You probably don't want to change any of this code.

SegmentMapper::SegmentMapper()
{
	m_impl = new SegmentMapperImpl;
}

SegmentMapper::~SegmentMapper()
{
	delete m_impl;
}

void SegmentMapper::init(const MapLoader& ml)
{
	m_impl->init(ml);
}

vector<StreetSegment> SegmentMapper::getSegments(const GeoCoord& gc) const
{
	return m_impl->getSegments(gc);
}
