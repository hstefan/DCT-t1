#include "Observable.hpp"

using namespace hstefan::util;


void Observable::registerObserver(Listener* listener)
{
   observers.push_back(listener);
}

void Observable::removeObserver(Listener* listener)
{
   observers.remove(listener);
}

void Observable::notifyObservers()
{
   for(std::list<Listener*>::iterator it = observers.begin(); it != observers.end(); ++it)
      (*it)->notify();
}
