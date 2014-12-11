//
// Generated file, do not edit! Created by opp_msgc 4.5 from src/utils/../messages/DNSPacket.msg.
//

#ifndef _DNSPACKET_M_H_
#define _DNSPACKET_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0405
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// cplusplus {{
#include "../common/DNS.h"

typedef struct ODnsExtension::DNSQuestion DNSQuestion;
typedef struct ODnsExtension::DNSRecord DNSRecord;
// }}



/**
 * Class generated from <tt>src/utils/../messages/DNSPacket.msg</tt> by opp_msgc.
 * <pre>
 * packet DNSPacket {
 *     unsigned short id;
 *     unsigned short options; 
 *     unsigned short qdcount; 
 *     unsigned short ancount;
 *     unsigned short nscount;
 *     unsigned short arcount;
 *     
 *     DNSQuestion questions[]     @sizeGetter(getNumQuestions)
 *                                 @sizeSetter(setNumQuestions)
 *                                 @sizetype(short);
 *     
 *     DNSRecord   answers[]       @sizeGetter(getNumAnswers)
 *                                 @sizeSetter(setNumAnswers)
 *                                 @sizetype(short);
 *     
 *     DNSRecord   authorities[]   @sizeGetter(getNumAuthorities)
 *                                 @sizeSetter(setNumAuthorities)
 *                                 @sizetype(short);
 *     
 *     DNSRecord   additional[]    @sizeGetter(getNumAdditional)
 *                                 @sizeSetter(setNumAdditional)
 *                                 @sizetype(short);
 * }
 * </pre>
 */
class DNSPacket : public ::cPacket
{
  protected:
    unsigned short id_var;
    unsigned short options_var;
    unsigned short qdcount_var;
    unsigned short ancount_var;
    unsigned short nscount_var;
    unsigned short arcount_var;
    DNSQuestion *questions_var; // array ptr
    short questions_arraysize;
    DNSRecord *answers_var; // array ptr
    short answers_arraysize;
    DNSRecord *authorities_var; // array ptr
    short authorities_arraysize;
    DNSRecord *additional_var; // array ptr
    short additional_arraysize;

  private:
    void copy(const DNSPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const DNSPacket&);

  public:
    DNSPacket(const char *name=NULL, int kind=0);
    DNSPacket(const DNSPacket& other);
    virtual ~DNSPacket();
    DNSPacket& operator=(const DNSPacket& other);
    virtual DNSPacket *dup() const {return new DNSPacket(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual unsigned short getId() const;
    virtual void setId(unsigned short id);
    virtual unsigned short getOptions() const;
    virtual void setOptions(unsigned short options);
    virtual unsigned short getQdcount() const;
    virtual void setQdcount(unsigned short qdcount);
    virtual unsigned short getAncount() const;
    virtual void setAncount(unsigned short ancount);
    virtual unsigned short getNscount() const;
    virtual void setNscount(unsigned short nscount);
    virtual unsigned short getArcount() const;
    virtual void setArcount(unsigned short arcount);
    virtual void setNumQuestions(short size);
    virtual short getNumQuestions() const;
    virtual DNSQuestion& getQuestions(short k);
    virtual const DNSQuestion& getQuestions(short k) const {return const_cast<DNSPacket*>(this)->getQuestions(k);}
    virtual void setQuestions(short k, const DNSQuestion& questions);
    virtual void setNumAnswers(short size);
    virtual short getNumAnswers() const;
    virtual DNSRecord& getAnswers(short k);
    virtual const DNSRecord& getAnswers(short k) const {return const_cast<DNSPacket*>(this)->getAnswers(k);}
    virtual void setAnswers(short k, const DNSRecord& answers);
    virtual void setNumAuthorities(short size);
    virtual short getNumAuthorities() const;
    virtual DNSRecord& getAuthorities(short k);
    virtual const DNSRecord& getAuthorities(short k) const {return const_cast<DNSPacket*>(this)->getAuthorities(k);}
    virtual void setAuthorities(short k, const DNSRecord& authorities);
    virtual void setNumAdditional(short size);
    virtual short getNumAdditional() const;
    virtual DNSRecord& getAdditional(short k);
    virtual const DNSRecord& getAdditional(short k) const {return const_cast<DNSPacket*>(this)->getAdditional(k);}
    virtual void setAdditional(short k, const DNSRecord& additional);
};

inline void doPacking(cCommBuffer *b, DNSPacket& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, DNSPacket& obj) {obj.parsimUnpack(b);}


#endif // _DNSPACKET_M_H_
