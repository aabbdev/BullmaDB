#ifndef __Console_H__
#define __Console_H__

#include <atomic>
#include <iostream>
#include <string.h>
#include <assert.h>
#include <map>

namespace Bullma::CLI {
	class Console
	{
	public:
		Console();
		~Console();
		static Console* getInstance();
		void run(std::atomic<bool>& run);
	protected:
		static Console* singleton;
	};
}
#endif // __Console_H__