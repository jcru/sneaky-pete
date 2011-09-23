#ifndef __NOVAGUEST_CONFIGFILE_H
#define __NOVAGUEST_CONFIGFILE_H

#include "confuse.h"
#include <string>

class Configfile {
public:
    Configfile(const char * config_path);
    ~Configfile();
    int get_int(const std::string & key);
    std::string get_string(const std::string & key);
private:
    cfg_t *cfg;

};

#endif