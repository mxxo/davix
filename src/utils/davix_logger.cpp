/*
 * This File is part of Davix, The IO library for HTTP based protocols
 * Copyright (C) 2013  Adrien Devresse <adrien.devresse@cern.ch>, CERN
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
*/

#include <vector>
#include <cstdio>
#include <cstdarg>
#include <davix_internal.hpp>
#include <utils/davix_logger.hpp>


const int BUFFER_SIZE =4096;
const char* prefix = "DAVIX";

const char* SCOPE_FILE =    "file";
const char* SCOPE_HTTP =    "http";
const char* SCOPE_POSIX =   "posix";
const char* SCOPE_XML =     "xml";
const char* SCOPE_SSL =     "ssl";
const char* SCOPE_HEADER =  "header";
const char* SCOPE_BODY =    "body";
const char* SCOPE_CHAIN =   "chain";
const char* SCOPE_CORE =    "core";
const char* SCOPE_GRID =    "grid";
const char* SCOPE_SOCKET =  "socket";
const char* SCOPE_LOCKS =   "locks";
const char* SCOPE_ALL =     "all";


const std::string davix_log_scope[] = {
    SCOPE_FILE,
    SCOPE_POSIX,
    SCOPE_XML,
    SCOPE_SSL,
    SCOPE_HEADER,
    SCOPE_BODY,
    SCOPE_CHAIN,
    SCOPE_CORE,
    SCOPE_GRID,
    SCOPE_SOCKET,
    SCOPE_LOCKS,
    SCOPE_ALL
};


const int num_of_scopes = sizeof(davix_log_scope)/sizeof(*davix_log_scope);
std::vector<std::string> log_scope_vec;

static int internal_log_mask = 0;
static int internal_trace_level = DAVIX_LOG_ALL;
static bool debug = false;

static void (*_fhandler)(void* userdata, int mgs_level, const char* msg) = NULL;
static void* _log_handler_userdata = NULL;






namespace Davix{


void logStr(int scope, int log_level, const std::string & str){
    if(_fhandler){
        _fhandler(_log_handler_userdata, log_level, str.c_str());
    }else{
        if(scope & LOG_SCOPE_NEON){ // libneon logs
            fmt::print(stdout, "{}", str);
        }else{  // davix logs
            fmt::print(stdout,"{}({}): {}\n", prefix, davix_get_log_scope(scope), str);
        }
    }
}


} // Davix














extern "C" void davix_set_log_level(int log_mask){
    internal_log_mask = log_mask;
}

extern "C" int davix_get_log_level(){
    return internal_log_mask;
}



static void internal_log_handler(int log_mask, const char * msg,  va_list ap){
    char buffer[BUFFER_SIZE];

    vsnprintf(buffer, BUFFER_SIZE-1, msg, ap);
    buffer[BUFFER_SIZE-1] ='\0';
    Davix::logStr(log_mask, log_mask, buffer);
}



extern "C" void davix_vlogger(int log_mask, const char* msg, va_list va){
    internal_log_handler(log_mask, msg, va);
}



extern "C" void davix_logger(int log_mask, const char * msg, ...){
    va_list va;
    va_start(va, msg);
    davix_vlogger(log_mask, msg, va);
    va_end(va);
}


extern "C"  void davix_set_log_handler( void (*fhandler)(void* userdata, int mgs_level, const char* msg), void* userdata){
    _fhandler = fhandler;
    _log_handler_userdata = userdata;
}

void davix_set_trace_level(int trace_level){
    internal_trace_level = trace_level;
}

int davix_get_trace_level(){
    return internal_trace_level;
}

void davix_set_log_scope(const std::string & scope){
    for(int i = 0; i < num_of_scopes; ++i){
        if(scope.compare(davix_log_scope[i]) == 0){
            switch(i){
                case 0:
                    internal_log_mask |= LOG_FILE;
                    break;
                case 1:  
                    internal_log_mask |= LOG_POSIX;
                    break;
                case 2:  
                    internal_log_mask |= LOG_XML;
                    break;
                case 3:  
                    internal_log_mask |= LOG_SSL;
                    break;
                case 4:  
                    internal_log_mask |= LOG_HEADER;
                    break;
                case 5:  
                    internal_log_mask |= LOG_BODY;
                    break;
                case 6:  
                    internal_log_mask |= LOG_CHAIN;
                    break;
                case 7:  
                    internal_log_mask |= LOG_CORE;
                    break;
                case 8:  
                    internal_log_mask |= LOG_GRID;
                    break;
                case 9:  
                    internal_log_mask |= LOG_SOCKET;
                    break;
                case 10:  
                    internal_log_mask |= LOG_LOCKS;
                    break;
                case 11:  
                    internal_log_mask |= LOG_ALL;
                    break;                    
            }
        }
    }
}

std::string davix_get_log_scope(int scope_mask){
    std::string scope_name;
    switch(scope_mask){
        case LOG_FILE:
            scope_name = SCOPE_FILE;
            break;
        case LOG_POSIX:
            scope_name = SCOPE_POSIX;
            break;
        case LOG_XML:
            scope_name = SCOPE_XML;
            break;
        case LOG_SSL:
            scope_name = SCOPE_SSL;
            break;
        case LOG_HEADER:
            scope_name = SCOPE_HEADER;
            break;
        case LOG_BODY:
            scope_name = SCOPE_BODY;
            break;
        case LOG_CHAIN:
            scope_name = SCOPE_CHAIN;
            break;
        case LOG_CORE:
            scope_name = SCOPE_CORE;
            break;
        case LOG_GRID:
            scope_name = SCOPE_GRID;
            break;
        case LOG_SOCKET:
            scope_name = SCOPE_SOCKET;
            break;
        case LOG_LOCKS:
            scope_name = SCOPE_LOCKS;
            break;
        case LOG_ALL:
            scope_name = SCOPE_ALL;
            break;
    }
    return scope_name;    
}


void davix_set_log_debug(bool dbg){
    debug = dbg;
}

bool davix_get_log_debug(){
    return debug;
}

