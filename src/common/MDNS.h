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


#ifndef MDNS_H_
#define MDNS_H_

#include <omnetpp.h>
#include <DNS.h>
#include <DNSTools.h>
#include "DNSPacket_m.h"

namespace ODnsExtension {

// definition of a structure for services
typedef struct MDNSService{

} mdns_service;

typedef struct MDNSKey{
   char* name;
   uint16_t type;
   uint16_t _class;
} mdns_key;

// utility functions:
int isProbe(DNSPacket* p);
int isAnnouncement(DNSPacket* p);
int isQuery(DNSPacket* p);
int isResponse(DNSPacket* p);

int compareMDNSKey(ODnsExtension::MDNSKey* key1, ODnsExtension::MDNSKey* key2);

/**
 * @brief createQuestion
 *
 * Creates a dnsquestion from params
 */
DNSQuestion* createQuestion(char* name, unsigned short type, unsigned short _class);

/**
 * @brief createQuestionFromKey
 *
 * Creates a dnsquestion from an MDNSKey
 */
DNSQuestion* createQuestionFromKey(MDNSKey* key);


}

#endif /* MDNS_H_ */