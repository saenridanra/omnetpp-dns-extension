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


#ifndef MDNSQUERYSCHEDULER_H_
#define MDNSQUERYSCHEDULER_H_

#include <omnetpp.h>
#include <TimeEventSet.h>
#include <UDPSocket.h>
#include <IPvXAddress.h>
#include <IPvXAddressResolver.h>
#include <DNS.h>
#include <DNSCache.h>
#include <DNSTTLCache.h>
#include <MDNS.h>
#include <MDNS_Privacy.h>
#include <glib.h>

namespace ODnsExtension {

typedef struct MDNSQueryJob{
    unsigned int id;
    ODnsExtension::TimeEvent* e;
    ODnsExtension::MDNSKey* key;
    int done;

    // when the job has to be performed.
    simtime_t delivery;

} query_job;

class MDNSQueryScheduler
{
    protected:
        void* resolver;
        ODnsExtension::TimeEventSet* timeEventSet;
        GList* jobs;
        GList* history;

        UDPSocket* outSock; // socket on which to send the data via multicast...
        UDPSocket* privacySock;
        IPvXAddress multicast_address = IPvXAddressResolver().resolve("225.0.0.1");

        GHashTable* private_service_table;
        GHashTable* friend_data_table;
        GHashTable* instance_name_table;
        int hasPrivacy = 0;

        ODnsExtension::DNSTTLCache* cache; // cache reference

        unsigned int id_count = 0;

        void (*callback) (void*, void*);

        virtual ODnsExtension::MDNSQueryJob* new_job(ODnsExtension::MDNSKey* key);
        virtual ODnsExtension::MDNSQueryJob* find_job(ODnsExtension::MDNSKey* key);
        virtual ODnsExtension::MDNSQueryJob* find_history(ODnsExtension::MDNSKey* key);
        virtual void done(ODnsExtension::MDNSQueryJob* qj);
        virtual void remove_job(ODnsExtension::MDNSQueryJob* qj);
        virtual GList* append_cache_entries(MDNSKey* key, GList* list);
        virtual int append_question(MDNSKey* key, GList** qlist, GList** anlist, int *packetSize, int* qdcount, int* ancount, int is_private);
        virtual int preparePacketAndSend(GList* qlist, GList* anlist, GList* nslist, GList* arlist, int qdcount, int ancount, int nscount, int arcount, int packetSize, int TC, int is_private);

    public:
        MDNSQueryScheduler(ODnsExtension::TimeEventSet* _timeEventSet, UDPSocket* _outSock, void* resolver);
        virtual ~MDNSQueryScheduler();
        static void elapseCallback(ODnsExtension::TimeEvent* e, void* data, void* thispointer);
        virtual void post(ODnsExtension::MDNSKey* key, int immediately);
        virtual void check_dup(ODnsExtension::MDNSKey* key);
        virtual void elapse(ODnsExtension::TimeEvent* e, void* data);

        void setCallback(void (_callback) (void*, void*)){
            callback = _callback;
        }

        virtual void setSocket(UDPSocket* sock){
            outSock = sock;
        }
        virtual void setCache(ODnsExtension::DNSTTLCache* _cache){
            cache = _cache;
        }

        virtual void setPrivacyData(GHashTable* private_service_table, GHashTable* friend_data_table, GHashTable* instance_name_table, UDPSocket* privacySocket){
            this->private_service_table = private_service_table;
            this->friend_data_table = friend_data_table;
            this->instance_name_table = instance_name_table;
            this->privacySock = privacySocket;
            hasPrivacy = 1;
        }
};

} /* namespace ODnsExtension */

#endif /* MDNSQUERYSCHEDULER_H_ */
