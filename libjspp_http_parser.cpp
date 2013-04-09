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
#include "cstralgo.h"

std::set<std::string> m_HTTPRequestStdHeaders;
std::set<std::string> m_HTTPReqspoceStdHeaders;
void InitHTTPRequestStdHeaders() 
{
    //std
    m_HTTPRequestStdHeaders.insert("accept");
    m_HTTPRequestStdHeaders.insert("accept-charset");
    m_HTTPRequestStdHeaders.insert("accept-encoding");
    m_HTTPRequestStdHeaders.insert("accept-language");
    m_HTTPRequestStdHeaders.insert("accept-datetime");
    m_HTTPRequestStdHeaders.insert("authorization");
    m_HTTPRequestStdHeaders.insert("cache-control");
    m_HTTPRequestStdHeaders.insert("connection");
    m_HTTPRequestStdHeaders.insert("cookie");
    m_HTTPRequestStdHeaders.insert("content-length");
    m_HTTPRequestStdHeaders.insert("content-md5");
    m_HTTPRequestStdHeaders.insert("content-type");
    m_HTTPRequestStdHeaders.insert("date");
    m_HTTPRequestStdHeaders.insert("expect");
    m_HTTPRequestStdHeaders.insert("from");
    m_HTTPRequestStdHeaders.insert("host");
    m_HTTPRequestStdHeaders.insert("if-match");
    m_HTTPRequestStdHeaders.insert("if-modified-since");
    m_HTTPRequestStdHeaders.insert("if-none-match");
    m_HTTPRequestStdHeaders.insert("if-range");
    m_HTTPRequestStdHeaders.insert("if-unmodified-since");
    m_HTTPRequestStdHeaders.insert("max-forwards");
    m_HTTPRequestStdHeaders.insert("pragma");
    m_HTTPRequestStdHeaders.insert("proxy-authorization");
    m_HTTPRequestStdHeaders.insert("range");
    m_HTTPRequestStdHeaders.insert("referer");
    m_HTTPRequestStdHeaders.insert("te");
    m_HTTPRequestStdHeaders.insert("upgrade");
    m_HTTPRequestStdHeaders.insert("user-agent");
    m_HTTPRequestStdHeaders.insert("via");
    m_HTTPRequestStdHeaders.insert("warning");
    m_HTTPRequestStdHeaders.insert("origin");
    //Non Std
    m_HTTPRequestStdHeaders.insert("x-requested-with");
    m_HTTPRequestStdHeaders.insert("x-forwarded-for");
    m_HTTPRequestStdHeaders.insert("x-forwarded-for");
    m_HTTPRequestStdHeaders.insert("x-forwarded-proto");
    m_HTTPRequestStdHeaders.insert("front-end-https");
    m_HTTPRequestStdHeaders.insert("x-att-deviceid");
    m_HTTPRequestStdHeaders.insert("x-wap-profile");
    m_HTTPRequestStdHeaders.insert("proxy-connection");
} 

void InitHTTPResponceStdHeaders()
{
    m_HTTPReqspoceStdHeaders.insert("access-control-allow-origin");
    m_HTTPReqspoceStdHeaders.insert("accept-ranges");
    m_HTTPReqspoceStdHeaders.insert("age");
    m_HTTPReqspoceStdHeaders.insert("allow");
    m_HTTPReqspoceStdHeaders.insert("cache-control");
    m_HTTPReqspoceStdHeaders.insert("connection");
    m_HTTPReqspoceStdHeaders.insert("content-encoding");
    m_HTTPReqspoceStdHeaders.insert("content-language");
    m_HTTPReqspoceStdHeaders.insert("content-length");
    m_HTTPReqspoceStdHeaders.insert("content-location");
    m_HTTPReqspoceStdHeaders.insert("content-md5");
    m_HTTPReqspoceStdHeaders.insert("content-disposition");
    m_HTTPReqspoceStdHeaders.insert("content-range");
    m_HTTPReqspoceStdHeaders.insert("content-type");
    m_HTTPReqspoceStdHeaders.insert("date");
    m_HTTPReqspoceStdHeaders.insert("etag");
    m_HTTPReqspoceStdHeaders.insert("expires");
    m_HTTPReqspoceStdHeaders.insert("last-modified");
    m_HTTPReqspoceStdHeaders.insert("link");
    m_HTTPReqspoceStdHeaders.insert("location");
    m_HTTPReqspoceStdHeaders.insert("p3p");
    m_HTTPReqspoceStdHeaders.insert("pragma");
    m_HTTPReqspoceStdHeaders.insert("proxy-authenticate");
    m_HTTPReqspoceStdHeaders.insert("refresh");
    m_HTTPReqspoceStdHeaders.insert("retry-after");
    m_HTTPReqspoceStdHeaders.insert("server");
    m_HTTPReqspoceStdHeaders.insert("set-cookie");
    m_HTTPReqspoceStdHeaders.insert("status");
    m_HTTPReqspoceStdHeaders.insert("strict-transport-security");
    m_HTTPReqspoceStdHeaders.insert("trailer");
    m_HTTPReqspoceStdHeaders.insert("transfer-encoding");
    m_HTTPReqspoceStdHeaders.insert("vary");
    m_HTTPReqspoceStdHeaders.insert("via");
    m_HTTPReqspoceStdHeaders.insert("warning");
    m_HTTPReqspoceStdHeaders.insert("www-authenticate");
    
    m_HTTPReqspoceStdHeaders.insert("x-frame-options");
    m_HTTPReqspoceStdHeaders.insert("x-xss-protection");
    m_HTTPReqspoceStdHeaders.insert("x-content-security-policy");
    m_HTTPReqspoceStdHeaders.insert("x-webkit-csp");
    m_HTTPReqspoceStdHeaders.insert("x-content-type-options");
    m_HTTPReqspoceStdHeaders.insert("x-powered-by");
    m_HTTPReqspoceStdHeaders.insert("x-ua-compatible");
}


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
  m_message.m_request_url.assign(buf, len);
  return 0;
}
int HttpParser::header_field_cb (http_parser *p, const char *buf, size_t len)
{
    cstralgo::tolowerLen(const_cast<char*>(buf), len);
    if (m_message.m_last_header_element != HttpParserMessage::FIELD) {
        m_message.m_num_headers++;
        if(m_message.m_num_headers > m_message.m_headersFields.size()) {
            HeadersField hf;
            m_message.m_headersFields.push_back(hf);
        }
        m_tempHeader.assign(buf, len);
        //m_message.m_headersFields[m_message.m_num_headers-1].Field.assign(buf, len);
    } else {
        m_tempHeader.append(buf, len);
        //m_message.m_headersFields[m_message.m_num_headers-1].Field.append(buf, len);
    }
    m_message.m_last_header_element = HttpParserMessage::FIELD;

  return 0;
}
int HttpParser::header_value_cb (http_parser *p, const char *buf, size_t len)
{
    m_message.m_last_header_element = HttpParserMessage::VALUE;
    m_it = m_message.m_StdHeadersFields.find(m_tempHeader);
    if(m_it!=m_message.m_StdHeadersFields.end()) {
        m_it->second.Value.assign(buf, len);
        m_it->second.isSet=true;
    }else {
        m_message.m_headersFields[m_message.m_num_headers-1].Value.assign(buf, len);
    }
   return 0;
}

int HttpParser::body_cb(http_parser *p, const char *buf, size_t len)
{
  m_message.m_body.append(buf,len);  
  m_message.m_body_size += len;
  return 0;
}
int HttpParser::count_body_cb (http_parser *p, const char *buf, size_t len)
{
  m_message.m_body_size += len;
  return 0;
}
int HttpParser::message_begin_cb (http_parser *p)
{
  m_message.m_message_begin_cb_called = 1;
  return 0;
}

int HttpParser::headers_complete_cb (http_parser *p)
{
  m_message.m_method = (http_method)p->method;
  m_message.m_status_code = p->status_code;
  m_message.m_http_major = p->http_major;
  m_message.m_http_minor = p->http_minor;
  m_message.m_headers_complete_cb_called = 1;
  m_message.m_should_keep_alive = http_should_keep_alive(p);
  return 0;
}

int HttpParser::message_complete_cb (http_parser *p)
{
  if (m_message.m_should_keep_alive != http_should_keep_alive(p))
  {
    fprintf(stderr, "\n\n *** Error http_should_keep_alive() should have same "
                    "value in both on_message_complete and on_headers_complete "
                    "but it doesn't! ***\n\n");
    assert(0);
    abort();
  }
  m_message.m_message_complete_cb_called = TRUE;
  m_message.m_message_complete_on_eof = m_currently_parsing_eof;
  m_num_messages++;
  return 0;
}


size_t HttpParser::parse (const char *buf, size_t len)
{
  size_t nparsed;
  m_currently_parsing_eof = (len == 0);
  nparsed = http_parser_execute(static_cast<http_parser*>(&m_ParserPlusPlus), &m_settings, buf, len);
  return nparsed;
}

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
    
    //memset(&tm,sizeof(HttpParserMessage), 0);
    //m_messages.push_back(tm);
}





//NODE_MODULE(node_http_parser, node::InitHttpParser)
