#include "libjspp_http_parser.h"
#include <assert.h>     /* assert */
#include <stdio.h>
#include <string.h>  /* strdup() */
#if !defined(_MSC_VER)
#include <strings.h>  /* strcasecmp() */
#else
#define strcasecmp _stricmp
#endif
#include <stdlib.h>  /* free() */
#include <string>
#include <vector>
#undef TRUE
#define TRUE 1
#undef FALSE
#define FALSE 0


// okThis is a binding to http_parser (https://github.com/joyent/http-parser)
// The goal is to decouple sockets from parsing for more javascript-level
// agility. A Buffer is read from a socket and passed to parser.execute().
// The parser then issues callbacks with slices of the data
//     parser.onMessageBegin
//     parser.onPath
//     parser.onBody
//     ...
// No copying is performed when slicing the buffer, only small reference
// allocations.
/*
static std::string on_headers_sym;
static std::string on_headers_complete_sym;
static std::string on_body_sym;
static std::string on_message_complete_sym;

static std::string method_sym;
static std::string status_code_sym;
static std::string http_version_sym;
static std::string version_major_sym;
static std::string version_minor_sym;
static std::string should_keep_alive_sym;
static std::string upgrade_sym;
static std::string headers_sym;
static std::string url_sym;

static std::string unknown_method_sym;

#define X(num, name, string) static std::string name##_sym;
HTTP_METHOD_MAP(X)
#undef X

static struct http_parser_settings settings;


// This is a hack to get the current_buffer to the callbacks with the least
// amount of overhead. Nothing else will run while http_parser_execute()
// runs, therefore this pointer can be set and used for the execution.
//static Local<Value>* current_buffer;
static char* current_buffer_data;
static size_t current_buffer_len;


#define HTTP_CB(name)                                                         \
  int name(http_parser* p_) {                                          \
    Parser* self = container_of(p_, Parser, parser_);                         \
    return self->name##_();                                                   \
  }                                                                           \
  int name##_()


#define HTTP_DATA_CB(name)                                                    \
  int name(http_parser* p_, const char* at, size_t length) {           \
    Parser* self = container_of(p_, Parser, parser_);                         \
    return self->name##_(at, length);                                         \
  }                                                                           \
  int name##_(const char* at, size_t length)


static inline std::string
method_to_str(unsigned short m) {
  switch (m) {
#define X(num, name, string) case HTTP_##name: return name##_sym;
  HTTP_METHOD_MAP(X)
#undef X
  }
  return unknown_method_sym;
}

*/

   
int HttpParser::srequest_url_cb (http_parser *p, const char *buf, size_t len)
{
  ParserPlusPlus *pParser=reinterpret_cast<ParserPlusPlus*>(p);
  return  pParser->m_Parser->request_url_cb(p, buf, len);
}
int HttpParser::sheader_field_cb (http_parser *p, const char *buf, size_t len)
{
  ParserPlusPlus *pParser=reinterpret_cast<ParserPlusPlus*>(p);
  return pParser->m_Parser->header_field_cb(p, buf, len);
}
int HttpParser::sheader_value_cb (http_parser *p, const char *buf, size_t len)
{
  ParserPlusPlus *pParser=reinterpret_cast<ParserPlusPlus*>(p);
  return pParser->m_Parser->header_value_cb (p, buf, len);
}
int HttpParser::sbody_cb (http_parser *p, const char *buf, size_t len)
{
  ParserPlusPlus *pParser=reinterpret_cast<ParserPlusPlus*>(p);
  return pParser->m_Parser->body_cb(p, buf, len);
}

int HttpParser::scount_body_cb (http_parser *p, const char *buf, size_t len)
{
  ParserPlusPlus *pParser=reinterpret_cast<ParserPlusPlus*>(p);
  return pParser->m_Parser->count_body_cb(p, buf, len);
}
int HttpParser::smessage_begin_cb (http_parser *p)
{
  ParserPlusPlus *pParser=reinterpret_cast<ParserPlusPlus*>(p);
  return pParser->m_Parser->message_begin_cb (p);
}
int HttpParser::sheaders_complete_cb (http_parser *p)
{
  ParserPlusPlus *pParser=reinterpret_cast<ParserPlusPlus*>(p);
  return pParser->m_Parser->headers_complete_cb(p);
}
int HttpParser::smessage_complete_cb (http_parser *p)
{
  ParserPlusPlus *pParser=reinterpret_cast<ParserPlusPlus*>(p);
  return pParser->m_Parser->message_complete_cb(p);
}
/////////////////////////Statics END
int HttpParser::request_url_cb(http_parser *p, const char *buf, size_t len)
{
  strncat(m_messages[m_num_messages].request_url, buf, len);
  return 0;
}
int HttpParser::header_field_cb (http_parser *p, const char *buf, size_t len)
{
  HttpParserMessage *m = &m_messages[m_num_messages];
  if (m->last_header_element != HttpParserMessage::FIELD)
    m->num_headers++;

  strncat(m->headers[m->num_headers-1][0], buf, len);

  m->last_header_element = HttpParserMessage::FIELD;

  return 0;
}
int HttpParser::header_value_cb (http_parser *p, const char *buf, size_t len)
{
  HttpParserMessage  *m = &m_messages[m_num_messages];
  strncat(m->headers[m->num_headers-1][1], buf, len);
  m->last_header_element = HttpParserMessage::VALUE;

  return 0;
}
int HttpParser::body_cb(http_parser *p, const char *buf, size_t len)
{
  m_messages[m_num_messages].body.append(buf,len);  
  //strncat(m_messages[m_num_messages].body, buf, len);
  m_messages[m_num_messages].body_size += len;
 // printf("body_cb: '%s'\n", requests[num_messages].body);
  return 0;
}
int HttpParser::count_body_cb (http_parser *p, const char *buf, size_t len)
{
  m_messages[m_num_messages].body_size += len;
  return 0;
}
int HttpParser::message_begin_cb (http_parser *p)
{
  m_messages[m_num_messages].message_begin_cb_called = 1;
  return 0;
}

int HttpParser::headers_complete_cb (http_parser *p)
{
  m_messages[m_num_messages].method = (http_method)p->method;
  m_messages[m_num_messages].status_code = p->status_code;
  m_messages[m_num_messages].http_major = p->http_major;
  m_messages[m_num_messages].http_minor = p->http_minor;
  m_messages[m_num_messages].headers_complete_cb_called = 1;
  m_messages[m_num_messages].should_keep_alive = http_should_keep_alive(p);
  return 0;
}

int HttpParser::message_complete_cb (http_parser *p)
{
  if (m_messages[m_num_messages].should_keep_alive != http_should_keep_alive(p))
  {
    fprintf(stderr, "\n\n *** Error http_should_keep_alive() should have same "
                    "value in both on_message_complete and on_headers_complete "
                    "but it doesn't! ***\n\n");
    assert(0);
    abort();
  }
  m_messages[m_num_messages].message_complete_cb_called = TRUE;

  m_messages[m_num_messages].message_complete_on_eof = m_currently_parsing_eof;

  m_num_messages++;
  HttpParserMessage  tm;
  memset(&tm,sizeof(HttpParserMessage), 0);
  m_messages.push_back(tm);
  return 0;
}


size_t HttpParser::parse (const char *buf, size_t len)
{
  size_t nparsed;
  m_currently_parsing_eof = (len == 0);
  nparsed = http_parser_execute(static_cast<http_parser*>(&m_ParserPlusPlus), &m_settings, buf, len);
  return nparsed;
}

/*size_t HttpParser::parse_count_body (const char *buf, size_t len)
{
  size_t nparsed;
  m_currently_parsing_eof = (len == 0);
  nparsed = http_parser_execute(static_cast<http_parser*>(&m_parser), &settings_count_body, buf, len);
  return nparsed;
}

size_t HttpParser::parse_pause (const char *buf, size_t len)
{
  size_t nparsed;
  http_parser_settings s = settings_pause;
  m_currently_parsing_eof = (len == 0);
  m_current_pause_parser = &s;
  nparsed = http_parser_execute(static_cast<http_parser*>(&m_parser), current_pause_parser, buf, len);
  return nparsed;
}*/

void HttpParser::DeInit()
{
//    delete m_parser;
//    m_parser=0;
}

void HttpParser::Init(enum http_parser_type type)
{
    m_num_messages = 0;
    HttpParserMessage  tm;
    memset(&tm,sizeof(HttpParserMessage), 0);
    //    assert(m_parser == NULL);
    //    m_parser = new ParserPlusPlus;
    m_ParserPlusPlus.m_Parser=this;
    http_parser_init(static_cast<http_parser*>(&m_ParserPlusPlus), type);
    m_settings.on_message_begin = HttpParser::smessage_begin_cb;
    m_settings.on_header_field = HttpParser::sheader_field_cb;
    m_settings.on_header_value = HttpParser::sheader_value_cb;
    m_settings.on_url = HttpParser::srequest_url_cb;
    m_settings.on_body = HttpParser::sbody_cb;
    m_settings.on_headers_complete = HttpParser::sheaders_complete_cb;
    m_settings.on_message_complete = HttpParser::smessage_complete_cb;
    
    memset(&tm,sizeof(HttpParserMessage), 0);
    m_messages.push_back(tm);
    
}





//NODE_MODULE(node_http_parser, node::InitHttpParser)
