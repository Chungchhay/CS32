#include "provided.h"
#include <string>
#include <vector>
#include <queue>
#include "support.h"
#include <functional>

using namespace std;

class NavigatorImpl
{
public:
    NavigatorImpl();
    ~NavigatorImpl();
    bool loadMapData(string mapFile);
    NavResult navigate(string start, string end, vector<NavSegment>& directions) const;
  
private:
  AttractionMapper m_attr;
  SegmentMapper m_seg;
  MapLoader m_mapLoader;
};



NavigatorImpl::NavigatorImpl()
{
}

NavigatorImpl::~NavigatorImpl()
{
}

bool NavigatorImpl::loadMapData(string mapFile)
{
  if (m_mapLoader.load(mapFile))
  {
    m_attr.init(m_mapLoader);
    m_seg.init(m_mapLoader);
    return true;
  }
  
	return false; 
}

//Struct Node

struct Node {
  //Pointer to parent node
  Node* parent;
  //Distance values
  double f, g, h;
  //Position
  StreetSegment sg;
  
  bool operator>(const Node& n) const {
    return f > n.f;
  }
};

string getDirection(double angle) {
  string dir;
  
  if (angle<= 22.5)
    dir = "east";
  else if (angle <= 67.5)
    dir = "norhteast";
  else if (angle <= 112.5)
    dir = "north";
  else if (angle <= 157.5)
    dir = "northwest";
  else if (angle <= 202.5)
    dir = "west";
  else if (angle <= 247.5)
    dir = "southwest";
  else if (angle <= 292.5)
    dir = "south";
  else if (angle <= 337.5)
    dir = "southeast";
  else if (angle < 360)
    dir = "east";
  
  return dir;
}


NavResult NavigatorImpl::navigate(string start, string end, vector<NavSegment> &directions) const
{
  StreetSegment seg;
  GeoCoord firstStart;
  GeoCoord firstEnd;
  GeoCoord lastStart;
  GeoCoord lastEnd;
  
  NavSegment startingPoint;
  NavSegment endingPoint;
  
  GeoSegment x , y;
  
  string streetEnd;
  string streetStart;
  
  bool isStreetStart = false;
  bool isStreetEnd = false;
  bool found = false;
  
  //Check if the vector is not empty, erase it
  if (directions.empty())
    directions.clear();
  
  for (size_t i = 0; i < m_mapLoader.getNumSegments(); i++)
  {
    if (m_mapLoader.getSegment(i, seg))
    {
      if (seg.streetName == start)
      {
        firstStart = seg.segment.start;
        firstEnd = seg.segment.end;
        x.start = seg.segment.start;
        x.end = seg.segment.end;
        
        startingPoint.m_command = NavSegment::PROCEED;
        startingPoint.m_direction = angleOfLine(seg.segment);
        startingPoint.m_streetName = seg.streetName;
        startingPoint.m_distance = distanceEarthMiles(seg.segment.start, seg.segment.end);
        startingPoint.m_geoSegment.start = seg.segment.start;
        startingPoint.m_geoSegment.end = seg.segment.end;
        directions.push_back(startingPoint);
        streetStart = startingPoint.m_streetName;
        
        found = true;
        isStreetStart = true;
      }
      
      for (size_t j = 0; j < seg.attractions.size(); j++)
      {
        if (seg.attractions[j].name == start)
          
        {
          firstStart = seg.attractions[j].geocoordinates;
          firstEnd = seg.segment.end;
          x.start = seg.segment.start;
          x.end = seg.segment.end;
          GeoSegment temp(firstStart, firstEnd);
          
          startingPoint.m_command = NavSegment::PROCEED;
          startingPoint.m_direction = angleOfLine(temp);
          startingPoint.m_streetName = seg.streetName;
          startingPoint.m_distance = distanceEarthMiles(firstStart, seg.segment.end);
          startingPoint.m_geoSegment.start = seg.attractions[j].geocoordinates;
          startingPoint.m_geoSegment.end = seg.segment.end;
          directions.push_back(startingPoint);
          streetStart = startingPoint.m_streetName;
          found = true;
        }
      }
    }
    
    if (found == true)
      break;
  }
  
  if (found == false)
    return NAV_BAD_SOURCE;
  
  found = false;
  
  for (size_t i = 0; i < m_mapLoader.getNumSegments(); i++)
  {
    if (m_mapLoader.getSegment(i, seg))
    {
      if (seg.streetName == end)
      {
        lastStart = seg.segment.start;
        lastEnd = seg.segment.end;
        streetEnd = seg.streetName;
        y.start = seg.segment.start;
        y.end = seg.segment.end;
        
        endingPoint.m_command = NavSegment::PROCEED;
        endingPoint.m_direction = angleOfLine(seg.segment);
        endingPoint.m_streetName = seg.streetName;
        endingPoint.m_distance = distanceEarthMiles(seg.segment.start, seg.segment.end);
        endingPoint.m_geoSegment.start = seg.segment.start;
        endingPoint.m_geoSegment.end = seg.segment.end;
        found = true;
        isStreetEnd = true;
      }
      
      for (size_t j = 0; j < seg.attractions.size(); j++)
      {
        if (seg.attractions[j].name == end)
        {
          lastStart = seg.segment.start;
          lastEnd = seg.attractions[j].geocoordinates;
          streetEnd = seg.streetName;
          y.start = seg.segment.start;
          y.end = seg.segment.end;
          GeoSegment temp(lastStart, lastEnd);
          
          endingPoint.m_command = NavSegment::PROCEED;
          endingPoint.m_direction = angleOfLine(temp);
          endingPoint.m_streetName = seg.streetName;
          endingPoint.m_distance = distanceEarthMiles(seg.segment.start, seg.segment.end);
          endingPoint.m_geoSegment.start = seg.segment.start;
          endingPoint.m_geoSegment.end = seg.segment.end;
          
          found = true;
        }
      }
    }
    
    if (found == true)
      break;
  }
  
  if (found == false)
    return NAV_BAD_DESTINATION;
  
  //Check if start and end are from the same location
  if (start == end)
    return NAV_SUCCESS;
  

  //Check if both are attracttions
  if (!isStreetStart && !isStreetEnd)
  {
    if (x.start == y.start && x.end == y.end)
    {
      directions.clear();
      startingPoint.m_command = NavSegment::PROCEED;
      startingPoint.m_direction = angleOfLine(seg.segment);
      startingPoint.m_streetName = seg.streetName;
      startingPoint.m_distance = distanceEarthMiles(seg.segment.start, seg.segment.end);
      startingPoint.m_geoSegment.start = seg.segment.start;
      startingPoint.m_geoSegment.end = seg.segment.end;
      directions.push_back(startingPoint);
    }
  }
  

  priority_queue<Node, vector<Node>, greater<Node>> pq;
  vector<Node> nodeVec;
  
  //Construct starting node
  Node startNode;
  startNode.parent = nullptr;
  startNode.g = distanceEarthMiles(firstStart, firstEnd);
  startNode.h = 0;
  startNode.f = 0;
  startNode.sg.segment.start = firstStart;
  startNode.sg.segment.end = firstEnd;
  startNode.sg.streetName = streetStart;
  pq.push(startNode);
  
  bool flag = true;
  
  while(flag) {
    
    //Pop out Node from priority queue
    Node nodeParent = pq.top();
    
    //Add to the nodeVector for full path
    nodeVec.push_back(nodeParent);
    
    //visited.insert(nodeParent);
    pq.pop();
  
    //Clear priority queue
    pq = priority_queue<Node, vector<Node>, greater<Node>>();
  
    vector<StreetSegment> temp = m_seg.getSegments(nodeParent.sg.segment.end);
    
    //Find all possible street segments to take
    for (size_t i = 0; i < temp.size(); i++)
    {
      //Check if we have reached our destination
      if(isStreetEnd)
      {
        if(temp[i].streetName == end)
        {
          flag = false;
          break;
        }
      }
      else
      {
        for (size_t j = 0; j < temp[i].attractions.size(); j++)
        {
          if (temp[i].attractions[j].name == end)
          {
            flag = false;
            break;
          }
        }
      }
      
      Node n;
      
      //Initialize parent
      n.parent = &nodeParent;

      //Calculate distance to this street segment
      n.g = nodeParent.g + distanceEarthMiles(temp[i].segment.start, temp[i].segment.end);
    
      //Calculate the distance from this street segment to end
      n.h = distanceEarthMiles(temp[i].segment.end, lastEnd);
    
      //Set f
      n.f = n.g + n.h;
      
      //Get street segment
      n.sg = temp[i];
      if(flag == false) {
        n.sg.segment.end = lastEnd;
        nodeVec.push_back(n);
        break;
      }

      pq.push(n);
    }
  }
  
  if (flag == true)
    return NAV_NO_ROUTE;
  
  //Iterate through entire nodeVec and create Nav segments
  for(size_t i = 0; i < nodeVec.size(); i++) {
    Node n;
    n.sg.segment.start = nodeVec[i].sg.segment.start;
    n.sg.segment.end = nodeVec[i].sg.segment.end;
    n.sg.streetName = nodeVec[i].sg.streetName;
    string dir;

    if (i != 0 && nodeVec[i].sg.streetName != nodeVec[i - 1].sg.streetName) {
      if (angleOfLine(n.sg.segment) < 180)
        dir = "left";
      else
        dir = "right";
      
      NavSegment navTurn(dir, nodeVec[i + 1].sg.streetName);
      //push into the direction vector
      directions.push_back(navTurn);
    }
    
    NavSegment nav(getDirection(angleOfLine(n.sg.segment)), n.sg.streetName, distanceEarthMiles(n.sg.segment.start, n.sg.segment.end), n.sg.segment);
    //push into the direction vector
    directions.push_back(nav);
  }

  double totalDistance = 0;
  for (int i = 0; i < directions.size(); i++)
  {
    if (directions[i].m_command == 0)
      totalDistance += directions[i].m_distance;
  }
  
  return NAV_SUCCESS;
}


//******************** Navigator functions ************************************

// These functions simply delegate to NavigatorImpl's functions.
// You probably don't want to change any of this code.

Navigator::Navigator()
{
    m_impl = new NavigatorImpl;
}

Navigator::~Navigator()
{
    delete m_impl;
}

bool Navigator::loadMapData(string mapFile)
{
    return m_impl->loadMapData(mapFile);
}

NavResult Navigator::navigate(string start, string end, vector<NavSegment>& directions) const
{
    return m_impl->navigate(start, end, directions);
}
