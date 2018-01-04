#ifndef support_hpp
#define support_hpp

#include <stdio.h>
#include "provided.h"

bool operator<(const GeoCoord &a, const GeoCoord &b);

bool operator>(const GeoCoord &a, const GeoCoord &b);

bool operator==(const GeoCoord &a, const GeoCoord &b);



#endif /* support_h */
