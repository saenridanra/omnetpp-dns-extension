/* Copyright (c) 2014-2015 Andreas Rain

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */


#ifndef MDNSRESPONSESCHEDULER_H_
#define MDNSRESPONSESCHEDULER_H_

#include <omnetpp.h>
#include <TimeEventSet.h>
#include <UDPSocket.h>
#include <IPvXAddress.h>
#include <IPvXAddressResolver.h>
#include <DNS.h>
#include <DNSCache.h>
#include <DNSSimpleCache.h>
#include <DNSTTLCache.h>
#include <MDNS.h>
#include <glib.h>
#include <glib/gprintf.h>

namespace ODnsExtension {

typedef struct MDNSResponseJob{
    unsigned int id;
    ODnsExtension::TimeEvent* e;
    ODnsExtension::DNSRecord* r;

    IPvXAddress* querier;

    int done;
    int suppressed;
    int flush_cache;

    // when the job has to be performed.
    simtime_t delivery;
} mdns_response_job;

class MDNSResponseScheduler
{
    protected:
        ODnsExtension::TimeEventSet* timeEventSet;
        GList* jobs;
        GList* history;
        GList* suppressed;

        UDPSocket* outSock; // socket on which to send the data via multicast...
        ODnsExtension::DNSTTLCache* auth_cache; // cached auth records for aux walks
        ODnsExtension::DNSTTLCache* cache; // cache reference

        unsigned int id_count = 0;

        virtual ODnsExtension::MDNSResponseJob* new_job(ODnsExtension::DNSRecord* r, int done, int suppress);
        virtual ODnsExtension::MDNSResponseJob* find_job(ODnsExtension::DNSRecord* r);
        virtual ODnsExtension::MDNSResponseJob* find_history(ODnsExtension::DNSRecord* r);
        virtual ODnsExtension::MDNSResponseJob* find_suppressed(ODnsExtension::DNSRecord* r, IPvXAddress* querier);
        virtual void done(ODnsExtension::MDNSResponseJob* rj);
        virtual void remove_job(ODnsExtension::MDNSResponseJob* rj);
        virtual void suppress(ODnsExtension::DNSRecord* r, int flush_cache, IPvXAddress* querier, int immediately);
        virtual int appendTransitiveEntries(ODnsExtension::DNSRecord* r, GList** anlist, int* packetSize, int* ancount);
        virtual int appendFromCache(char* hash, GList** anlist, int* packetSize, int* ancount);
        virtual int appendRecord(ODnsExtension::DNSRecord* r, GList** anlist, int* packetSize, int* ancount);
        virtual int preparePacketAndSend(GList* anlist, int ancount, int packetSize);
    public:
        MDNSResponseScheduler(ODnsExtension::TimeEventSet* _timeEventSet);
        virtual ~MDNSResponseScheduler();

        static void elapseCallback(ODnsExtension::TimeEvent* e, void* data, void* thispointer);
        virtual void post(ODnsExtension::DNSRecord* r,  int flush_cache, IPvXAddress* querier, int immediately);
        virtual void elapse(ODnsExtension::TimeEvent* e, void* data);
        virtual void check_dup(ODnsExtension::DNSRecord* r, int flush_cache);

        virtual void setSocket(UDPSocket* sock){
            outSock = sock;
        }
        virtual void setCache(ODnsExtension::DNSTTLCache* _cache){
            cache = _cache;
        }
        virtual void setAuthCache(ODnsExtension::DNSTTLCache* _cache){
            auth_cache = _cache;
        }
};

#define MDNS_RESPONSE_ON_PROBE 250 // for probes we only wait up to 250ms
#define MDNS_RESPONSE_WAIT 500 // wait up to 500 msec, + some random delay..

} /* namespace ODnsExtension */

#endif /* MDNSRESPONSESCHEDULER_H_ */
