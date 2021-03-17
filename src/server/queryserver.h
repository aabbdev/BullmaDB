#ifndef __Queryserver_H__
#define __Queryserver_H__
#include <atomic>

namespace Bullma::Server {
    class QueryServer
    {
    public:
        QueryServer();
        ~QueryServer();
        void Start();
        void Stop();
    };
}
#endif // __Queryserver_H__