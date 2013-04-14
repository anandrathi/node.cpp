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

std::tr1::unordered_set<std::string> HttpParser::s_HTTPRequestStdHeaders;
std::tr1::unordered_set<std::string> HttpParser::s_HTTPResponseStdHeaders;

void HttpParser::InitHTTPRequestStdHeaders() 
{
    //std
    s_HTTPRequestStdHeaders.insert("accept");
    s_HTTPRequestStdHeaders.insert("accept-charset");
    s_HTTPRequestStdHeaders.insert("accept-encoding");
    s_HTTPRequestStdHeaders.insert("accept-language");
    s_HTTPRequestStdHeaders.insert("accept-datetime");
    s_HTTPRequestStdHeaders.insert("authorization");
    s_HTTPRequestStdHeaders.insert("cache-control");
    s_HTTPRequestStdHeaders.insert("connection");
    s_HTTPRequestStdHeaders.insert("cookie");
    s_HTTPRequestStdHeaders.insert("content-length");
    s_HTTPRequestStdHeaders.insert("content-md5");
    s_HTTPRequestStdHeaders.insert("content-type");
    s_HTTPRequestStdHeaders.insert("date");
    s_HTTPRequestStdHeaders.insert("expect");
    s_HTTPRequestStdHeaders.insert("from");
    s_HTTPRequestStdHeaders.insert("host");
    s_HTTPRequestStdHeaders.insert("if-match");
    s_HTTPRequestStdHeaders.insert("if-modified-since");
    s_HTTPRequestStdHeaders.insert("if-none-match");
    s_HTTPRequestStdHeaders.insert("if-range");
    s_HTTPRequestStdHeaders.insert("if-unmodified-since");
    s_HTTPRequestStdHeaders.insert("max-forwards");
    s_HTTPRequestStdHeaders.insert("pragma");
    s_HTTPRequestStdHeaders.insert("proxy-authorization");
    s_HTTPRequestStdHeaders.insert("range");
    s_HTTPRequestStdHeaders.insert("referer");
    s_HTTPRequestStdHeaders.insert("te");
    s_HTTPRequestStdHeaders.insert("upgrade");
    s_HTTPRequestStdHeaders.insert("user-agent");
    s_HTTPRequestStdHeaders.insert("via");
    s_HTTPRequestStdHeaders.insert("warning");
    s_HTTPRequestStdHeaders.insert("origin");
    //Non Std
    s_HTTPRequestStdHeaders.insert("x-requested-with");
    s_HTTPRequestStdHeaders.insert("x-forwarded-for");
    s_HTTPRequestStdHeaders.insert("x-forwarded-for");
    s_HTTPRequestStdHeaders.insert("x-forwarded-proto");
    s_HTTPRequestStdHeaders.insert("front-end-https");
    s_HTTPRequestStdHeaders.insert("x-att-deviceid");
    s_HTTPRequestStdHeaders.insert("x-wap-profile");
    s_HTTPRequestStdHeaders.insert("proxy-connection");
} 

void HttpParser::InitHTTPResponceStdHeaders()
{
    s_HTTPResponseStdHeaders.insert("access-control-allow-origin");
    s_HTTPResponseStdHeaders.insert("accept-ranges");
    s_HTTPResponseStdHeaders.insert("age");
    s_HTTPResponseStdHeaders.insert("allow");
    s_HTTPResponseStdHeaders.insert("cache-control");
    s_HTTPResponseStdHeaders.insert("connection");
    s_HTTPResponseStdHeaders.insert("content-encoding");
    s_HTTPResponseStdHeaders.insert("content-language");
    s_HTTPResponseStdHeaders.insert("content-length");
    s_HTTPResponseStdHeaders.insert("content-location");
    s_HTTPResponseStdHeaders.insert("content-md5");
    s_HTTPResponseStdHeaders.insert("content-disposition");
    s_HTTPResponseStdHeaders.insert("content-range");
    s_HTTPResponseStdHeaders.insert("content-type");
    s_HTTPResponseStdHeaders.insert("date");
    s_HTTPResponseStdHeaders.insert("etag");
    s_HTTPResponseStdHeaders.insert("expires");
    s_HTTPResponseStdHeaders.insert("last-modified");
    s_HTTPResponseStdHeaders.insert("link");
    s_HTTPResponseStdHeaders.insert("location");
    s_HTTPResponseStdHeaders.insert("p3p");
    s_HTTPResponseStdHeaders.insert("pragma");
    s_HTTPResponseStdHeaders.insert("proxy-authenticate");
    s_HTTPResponseStdHeaders.insert("refresh");
    s_HTTPResponseStdHeaders.insert("retry-after");
    s_HTTPResponseStdHeaders.insert("server");
    s_HTTPResponseStdHeaders.insert("set-cookie");
    s_HTTPResponseStdHeaders.insert("status");
    s_HTTPResponseStdHeaders.insert("strict-transport-security");
    s_HTTPResponseStdHeaders.insert("trailer");
    s_HTTPResponseStdHeaders.insert("transfer-encoding");
    s_HTTPResponseStdHeaders.insert("vary");
    s_HTTPResponseStdHeaders.insert("via");
    s_HTTPResponseStdHeaders.insert("warning");
    s_HTTPResponseStdHeaders.insert("www-authenticate");
    
    s_HTTPResponseStdHeaders.insert("x-frame-options");
    s_HTTPResponseStdHeaders.insert("x-xss-protection");
    s_HTTPResponseStdHeaders.insert("x-content-security-policy");
    s_HTTPResponseStdHeaders.insert("x-webkit-csp");
    s_HTTPResponseStdHeaders.insert("x-content-type-options");
    s_HTTPResponseStdHeaders.insert("x-powered-by");
    s_HTTPResponseStdHeaders.insert("x-ua-compatible");
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

int HttpParser::sfragment_cb(http_parser *p, const char *buf, size_t len)
{
  ParserPlusPlus *pParser=reinterpret_cast<ParserPlusPlus*>(p);
  return  pParser->m_Parser->fragment_cb(p, buf, len);
}
   
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
  printf("request url %s\n", m_message.m_request_url.c_str() );
  return 0;
}


int HttpParser::fragment_cb(http_parser *p, const char *buf, size_t len)
{
  //strncat(messages[num_messages].m_fragment, p, len);
  m_message.m_fragment.assign(buf, len);
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
        printf("Header STD %s=%s\n", m_it->first.c_str(),m_it->second.Value.c_str());
    } else {
        m_message.m_headersFields[m_message.m_num_headers-1].Field=m_tempHeader;
        m_message.m_headersFields[m_message.m_num_headers-1].Value.assign(buf, len);
        printf("Header %s=%s\n", m_message.m_headersFields[m_message.m_num_headers-1].Field.c_str(),
        m_message.m_headersFields[m_message.m_num_headers-1].Value.c_str() );
    }
   return 0;
}

int HttpParser::body_cb(http_parser *p, const char *buf, size_t len)
{
  m_message.m_body.append(buf,len);  
  m_message.m_body_size += len;
  printf("Body[%s] Len[%d]\n", m_message.m_body.c_str(), (int)m_message.m_body_size);
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

  int rv = http_parser_parse_url(m_message.m_request_url.c_str(), m_message.m_request_url.size(),
    0, &m_message.m_http_parser_url);
    m_message.url_UF_SCHEMA.assign(
        m_message.m_request_url.c_str() + m_message.m_http_parser_url.field_data[UF_SCHEMA].off,
        m_message.m_http_parser_url.field_data[UF_SCHEMA].len);
    m_message.url_UF_HOST.assign(
        m_message.m_request_url.c_str() + m_message.m_http_parser_url.field_data[UF_HOST].off,
        m_message.m_http_parser_url.field_data[UF_HOST].len);
    m_message.url_UF_PORT.assign(
        m_message.m_request_url.c_str() + m_message.m_http_parser_url.field_data[UF_PORT].off,
        m_message.m_http_parser_url.field_data[UF_PORT].len);
    m_message.url_UF_PATH.assign(
        m_message.m_request_url.c_str() + m_message.m_http_parser_url.field_data[UF_PATH].off,
        m_message.m_http_parser_url.field_data[UF_PATH].len);
    m_message.url_UF_QUERY.assign(
        m_message.m_request_url.c_str() + m_message.m_http_parser_url.field_data[UF_QUERY].off,
        m_message.m_http_parser_url.field_data[UF_QUERY].len);
    m_message.url_UF_FRAGMENT.assign(
        m_message.m_request_url.c_str() + m_message.m_http_parser_url.field_data[UF_FRAGMENT].off,
        m_message.m_http_parser_url.field_data[UF_FRAGMENT].len);
    m_message.url_UF_USERINFO.assign(
        m_message.m_request_url.c_str() + m_message.m_http_parser_url.field_data[UF_USERINFO].off,
        m_message.m_http_parser_url.field_data[UF_USERINFO].len);
  printf("SCHEMA(%s)\n HOST(%s)\n PORT(%s)\n PATH(%s)\n QUERY(%s)\n FRAGMENT(%s)\n  USERINFO(%s)\n",
  m_message.url_UF_SCHEMA.c_str(),
  m_message.url_UF_HOST.c_str(),
  m_message.url_UF_PORT.c_str(),
  m_message.url_UF_PATH.c_str(),
  m_message.url_UF_QUERY.c_str(),
  m_message.url_UF_FRAGMENT.c_str(),
  m_message.url_UF_USERINFO.c_str()  );
  rv=rv; 
  printf("Method=%d;m_status_code=%d;http_major=%d;http_minor=%d;headers_complete_cb_called=%d;m_should_keep_alive=%d\n", 
  m_message.m_method,
  m_message.m_status_code,
  m_message.m_http_major,
  m_message.m_http_minor ,
  m_message.m_headers_complete_cb_called ,
  m_message.m_should_keep_alive 
  );
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
  printf("message_complete\n");
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

void HttpParser::ReInit() {
    m_num_messages = 0;
    HttpParserMessage  tm;
    memset(&tm,sizeof(HttpParserMessage), 0);
    //    assert(m_parser == NULL);
    //    m_parser = new ParserPlusPlus;
    m_ParserPlusPlus.m_Parser=this;
    http_parser_init(static_cast<http_parser*>(&m_ParserPlusPlus), m_http_parser_type);
    m_settings.on_message_begin = HttpParser::smessage_begin_cb;
    m_settings.on_header_field = HttpParser::sheader_field_cb;
    m_settings.on_header_value = HttpParser::sheader_value_cb;
    m_settings.on_url = HttpParser::srequest_url_cb;
    m_settings.on_body = HttpParser::sbody_cb;
    m_settings.on_headers_complete = HttpParser::sheaders_complete_cb;
    m_settings.on_message_complete = HttpParser::smessage_complete_cb;
    for ( auto it = m_message.m_StdHeadersFields.begin(); it != m_message.m_StdHeadersFields.end(); ++it ) {
        it->second.isSet=false;
    }  
}

void HttpParser::Init(enum http_parser_type type)
{
    printf("HttpParser::Init\n");
    m_http_parser_type=type;
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
    
    
    //type==HTTP_BOTH , HTTP_REQUEST , HTTP_RESPONSE
    StdHeadersField sf;
    if(type==HTTP_REQUEST ) {
        for ( auto it = s_HTTPRequestStdHeaders.begin(); it != s_HTTPRequestStdHeaders.end(); ++it ) {
            //printf("static req header = %s\n", it->c_str());
            m_message.m_StdHeadersFields[*it]=sf;
            
        } 
    } else if(type==HTTP_RESPONSE ) {
        for ( auto it = s_HTTPResponseStdHeaders.begin(); it != s_HTTPResponseStdHeaders.end(); ++it ) {
            //printf("static resp header = %s\n", it->c_str());
            m_message.m_StdHeadersFields[*it]=sf;
        } 
    }  else {
        for ( auto it = s_HTTPRequestStdHeaders.begin(); it != s_HTTPRequestStdHeaders.end(); ++it ) {
            //printf("static req header = %s\n", it->c_str());
            m_message.m_StdHeadersFields[*it]=sf;
        } 
        for ( auto it = s_HTTPResponseStdHeaders.begin(); it != s_HTTPResponseStdHeaders.end(); ++it ) {
            //printf("static resp header = %s\n", it->c_str());
            m_message.m_StdHeadersFields[*it]=sf;
        } 
    }
    //memset(&tm,sizeof(HttpParserMessage), 0);
    //m_messages.push_back(tm);
}


//NODE_MODULE(node_http_parser, node::InitHttpParser)
