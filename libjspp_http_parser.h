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

//#include "v8.h"
//
#include "http_parser.h"
#include <string>
#include <vector>

#define MAX_HEADERS 13
#define MAX_ELEMENT_SIZE 500

//#define MIN(a,b) ((a) < (b) ? (a) : (b))


struct HttpParserMessage {
  const char *name; // for debugging purposes
  const char *raw;
  enum http_parser_type type;
  enum http_method method;
  int status_code;
  char request_path[MAX_ELEMENT_SIZE];
  char request_url[MAX_ELEMENT_SIZE];
  char fragment[MAX_ELEMENT_SIZE];
  char query_string[MAX_ELEMENT_SIZE];
  char body[MAX_ELEMENT_SIZE];
  size_t body_size;
  const char *host;
  const char *userinfo;
  uint16_t port;
  int num_headers;
  enum { NONE=0, FIELD, VALUE } last_header_element;
  char headers [MAX_HEADERS][2][MAX_ELEMENT_SIZE];
  int should_keep_alive;

  const char *upgrade; // upgraded body

  unsigned short http_major;
  unsigned short http_minor;

  int message_begin_cb_called;
  int headers_complete_cb_called;
  int message_complete_cb_called;
  int message_complete_on_eof;
};

class HttpParser;
struct ParserPlusPlus : public http_parser {
HttpParser * m_Parser;
};

class HttpParser
{
protected:
    ParserPlusPlus m_parser;
    std::vector<HttpParserMessage> m_messages;
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
//    size_t parse_pause (const char *buf, size_t len);
//    size_t parse_count_body (const char *buf, size_t len);
};

#endif  // NODE_HTTP_PARSER
