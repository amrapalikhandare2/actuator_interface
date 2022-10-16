#ifndef CONFIG_PARSER_H_
#define CONFIG_PARSER_H_

#include<json_reader/json_read.h>
#include <memory>

#include "../../socketcan/socketcan.h"
#include "../../canopen/canopen.h"


class ConfigParser {

    public:
    ConfigParser();
    ~ConfigParser();
    private:

    
    public:
    bool parseConfig();
    
    typedef std::shared_ptr<ConfigParser> ConfigParserSPtr;
    typedef std::unique_ptr<ConfigParser> ConfigParserUPtr;

};

#endif
