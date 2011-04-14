#ifndef HSTEFAN_LISTENER_HPP
#define HSTEFAN_LISTENER_HPP

namespace hstefan
{
	namespace util
	{
		class Listener
		{
		public:
			virtual void notify() = 0;
		};
	}
}

#endif
