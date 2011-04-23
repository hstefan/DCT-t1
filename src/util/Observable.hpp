#ifndef HSTEFAN_OBSERVABLE_HPP
#define HSTEFAN_OBSERVABLE_HPP

#include <list>
#include "Listener.hpp"

namespace hstefan
{
   namespace util
   {
      class Observable
      {
      public:
         void registerObserver(Listener* listener);
         void removeObserver(Listener* listener);
         void notifyObservers();
      protected:
         std::list<Listener*> observers;
      };
   }
}
#endif