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

#ifndef __OPP_DNS_EXTENSION_DNSLOCALCACHE_H_
#define __OPP_DNS_EXTENSION_DNSLOCALCACHE_H_

#include <omnetpp.h>
#include "DNSServerBase.h"
#include "DNS.h"
#include "DNSTTLCache.h"
#include <string.h>
#include <glib.h>
#include <math.h>

/**
 * @brief DNSLocalCache a simple DNS proxy implementation. Similar to the AuthServer
 * but it only checks the cache and otherwise forwards the question to the AuthServer
 * if the question can not be answered using the cache.
 *
 * @author Andreas Rain, Distributed Systems Group, University of Konstanz
 */
class DNSLocalCache : public DNSServerBase
{
  public:
    int recursion_available;
    int response_count;

  protected:
  public:
        virtual void initialize(int stage);
        virtual void handleMessage(cMessage *msg);

        /**
         * @brief appendAuthority
         *  Appends NS records to the authority section of the response.
         * @params
         *      ns_list : list in which NS records have to be put in.
         *      ns_records : pointer to the count of ns_records.
         *
         * @return
         *      returns the ns_list after updating it.
         */
        virtual GList* appendAuthority(GList *ns_list, int *ns_records);

        /**
         * @brief appendAdditionals
         *  Appends A and AAAA records to the ar_list, based
         *  on NS records in the ns_list
         * @params
         *      ns_list : list of NS records
         *      ar_list : list in which A and AAAA records for NS records are stored
         *      ns_records : pointer to the count of ar_records.
         *
         * @return
         *      returns the ar_list after updating it.
         */
        virtual GList* appendAdditionals(GList *ns_list, GList* ar_list, int *ns_records);

        /**
         * @brief appendEntries
         *  Appends entries to a list based on the hash passed to the method.
         *
         * @params
         *      hash - hash value of the form label:type:class
         *      dstlist - list in which the records are stored
         *      type - the type to look for
         *      num_records - pointer to a counter variable for the size of the list
         *
         * @return
         *      returns the updated list
         */
        virtual GList* appendEntries(char *hash, GList *dstlist, int type, int *num_records);

        /**
         * @brief appendTransitiveEntries
         *  Appends entries to a list based on records in srclist
         *
         * @params
         *      srclist - source list, based on the data values of these records, other records are searched in the catalog.
         *      dstlist - list in which the records are stored
         *      DNS_TYPE_STR - string form of the dns type
         *      DNS_TYPE_VALUE - integer value of the dns type
         *      ar_records - pointer to a counter variable for the size of ar_list
         */
        virtual GList* appendTransitiveEntries(GList *srclist, GList *dstlist, const char* DNS_TYPE_STR, int DNS_TYPE_VALUE, int *ar_records);
        /**
        *
        */
        DNSPacket* handleQuery(ODnsExtension::Query *query);
};

#endif
