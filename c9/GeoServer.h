#ifndef GeoServer_h
#define GeoServer_h

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Location.h"
#include "Area.h"
#include "User.h"

#include "VectorUtil.h"

class GeoServerListener {
public:
   virtual void updated(const User& user) = 0;
};

class GeoServer {
public:
   void track(const std::string& user);
   void stopTracking(const std::string& user);
   void updateLocation(const std::string& user, const Location& location);

   bool isTracking(const std::string& user) const;
   Location locationOf(const std::string& user) const;

   bool isDifferentUserInBounds(
         const std::pair<std::string, Location>& each,
         const std::string& user,
         const Area& box) const;

   std::vector<User> usersInBox(
         const std::string& user, double widthInMeters, double heightInMeters,
         GeoServerListener* listener=nullptr) const;

private:
   std::unordered_map<std::string, Location> locations_;

   std::unordered_map<std::string, Location>::const_iterator 
      find(const std::string& user) const;
};

#endif
