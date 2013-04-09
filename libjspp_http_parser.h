// Copyright Joyent, Inc. and other Node contributors.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef NODE_HTTP_PARSER
#define NODE_HTTP_PARSER
#include "http_parser.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>    // std::lexicographical_compare
#include <cctype>       // std::tolower
#include <cstring>

#define MAX_HEADERS 13
#define MAX_ELEMENT_SIZE 2048
#define MAX_ELEMENT_SIZE 2048

//HTTP Request
/*
accept
accept-charset
accept-encoding
accept-language
accept-datetime
authorization
cache-control
connection
cookie
content-length
content-md5
content-type
date
expect
from
host
if-match
if-modified-since
if-none-match
if-range
if-unmodified-since
max-forwards
pragma
proxy-authorization
range
referer
te
upgrade
user-agent
via
warning
origin
 * */

extern std::set<std::string> m_HTTPRequestStdHeaders;
extern std::set<std::string> m_HTTPReqspoceStdHeaders;
void InitHTTPRequestStdHeaders();
void InitHTTPResponceStdHeaders();

struct ciLessLibC : public std::binary_function<std::string, std::string, bool> {
    bool operator()(const std::string &lhs, const std::string &rhs) const {
        return strcasecmp(lhs.c_str(), rhs.c_str()) < 0 ? 1 : 0;
    }
};

//#define MIN(a,b) ((a) < (b) ? (a) : (b))
struct HeadersField {
    std::string Field;
    std::string Value;
};

struct StdHeadersField {
    bool isSet;
    std::string Value;
};

typedef std::vector<HeadersField> HEADERSFIELD;
typedef std::map< std::string,  StdHeadersField > STDHTTPHEADERSFIELDMAP;

struct HttpParserMessage {
  std::string m_name; // for debugging purposes
  const char *m_raw;
  enum http_parser_type m_type;
  enum http_method m_method;
  int m_status_code;
  char m_request_path[MAX_ELEMENT_SIZE];
  std::string m_request_url;
  char m_fragment[MAX_ELEMENT_SIZE];
  char m_query_string[MAX_ELEMENT_SIZE];
  std::string m_body;
  size_t m_body_size;
  
  std::string m_host;
  std::string m_userinfo;
  uint16_t m_port;
  size_t m_num_headers;
  enum { NONE=0, FIELD, VALUE } m_last_header_element;
  HEADERSFIELD m_headersFields;
  STDHTTPHEADERSFIELDMAP m_StdHeadersFields;
  int m_should_keep_alive;

  std::string m_upgrade; // upgraded body

  unsigned short m_http_major;
  unsigned short m_http_minor;

  int m_message_begin_cb_called;
  int m_headers_complete_cb_called;
  int m_message_complete_cb_called;
  int m_message_complete_on_eof;
};

class HttpParser;
struct ParserPlusPlus : public http_parser {
HttpParser * m_Parser;
};

class HttpParser
{
protected:
    HttpParserMessage m_message;
    int m_num_messages;
    std::vector<std::string> m_fields;  // header fields
    std::vector<std::string> m_values;  // header values
    std::string m_url;
    int m_currently_parsing_eof;
    int m_num_fields;
    //int m_num_values;
    bool have_flushed;
    bool got_exception;
    http_parser_settings m_settings;
    ParserPlusPlus m_ParserPlusPlus;
    //static methods
    static int srequest_url_cb (http_parser *p, const char *buf, size_t len);
    static int sheader_field_cb (http_parser *p, const char *buf, size_t len);
    static int sheader_value_cb (http_parser *p, const char *buf, size_t len);
    static int sbody_cb (http_parser *p, const char *buf, size_t len);
    static int scount_body_cb (http_parser *p, const char *buf, size_t len);
    static int smessage_begin_cb (http_parser *p);
    static int sheaders_complete_cb (http_parser *p);
    static int smessage_complete_cb (http_parser *p);
    //methods
    int request_url_cb(http_parser *p, const char *buf, size_t len);
    int header_field_cb (http_parser *p, const char *buf, size_t len);
    int header_value_cb (http_parser *p, const char *buf, size_t len);
    int body_cb (http_parser *p, const char *buf, size_t len);
    int count_body_cb (http_parser *p, const char *buf, size_t len);
    int message_begin_cb (http_parser *p);
    int headers_complete_cb (http_parser *p);
    int message_complete_cb (http_parser *p);

    //void parser_init(enum http_parser_type type);
    //void parser_free ();
    void DeInit();
public:
    void Init(enum http_parser_type type);
    size_t parse (const char *buf, size_t len);
    ParserPlusPlus& getParserPlusPlus() {return m_ParserPlusPlus;}    
    std::string m_tempstr;
    std::string m_tempHeader;
    STDHTTPHEADERSFIELDMAP::iterator m_it;
//    size_t parse_pause (const char *buf, size_t len);
//    size_t parse_count_body (const char *buf, size_t len);
};

#endif  // NODE_HTTP_PARSER
