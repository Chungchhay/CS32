#include "support.h"


bool operator<(const GeoCoord &a, const GeoCoord &b)
{
  if (a.latitude == b.latitude)
    return a.longitude < b.longitude;
  
  return a.latitudeText < b.latitudeText;
}

bool operator>(const GeoCoord &a, const GeoCoord &b)
{
  if (a.latitude == b.latitude)
    return a.longitude > b.longitude;

  return a.latitudeText > b.latitudeText;
}

bool operator==(const GeoCoord &a, const GeoCoord &b)
{
  return (a.latitudeText == b.latitudeText && a.longitudeText == b.longitudeText);
}