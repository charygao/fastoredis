#include "common/logger.h"

#include <fstream>
#include <string.h>
#include <iostream>

#include "common/file_system.h"
#include "common/multi_threading/types.h"

namespace
{
    const std::string &get_logger_path()
    {
        static std::string result = common::file_system::prepare_path("~/" PROJECT_NAME_LOWERCASE ".log");
        return result;
    }

    common::multi_threading::mutex_t lock_;
}

namespace common
{
    namespace logging
    {
        Logger::Logger()
            : outStream_(NULL)
        {
        #ifdef NDEBUG
            outStream_ = new std::ofstream(get_logger_path().c_str());
            string16_ofstream *file = dynamic_cast<string16_ofstream*>(outStream_);
            if(!file || (file && !file->is_open()))
            {
                 outStream_  = &std::cerr;
                 *outStream_ << log_level_to_text(L_WARNING) << " Output file not open!\n";
            }            
        #else
            outStream_ = &std::cerr;
        #endif
            *outStream_ << "LOG STARTED\n";
        }

        Logger::~Logger()
        {
            outStream_->flush();
            if(outStream_ && outStream_ != &std::cerr){
                std::ofstream *file = dynamic_cast<std::ofstream*>(outStream_);
                if(file){
                    file->close();
                }
                delete outStream_;
            }
        }

        void Logger::printTradeSafe(LEVEL_LOG level, const std::string &data)
        {
            multi_threading::unique_lock<multi_threading::mutex_t> lock(lock_);
            *outStream_ << log_level_to_text(level) << " " << data;
        }
    }

    void DEBUG_MSG_PERROR(const char *function, int err)
    {
        const char* strer = strerror(err);
        return DEBUG_MSG_FORMAT<256>(logging::L_ERROR, "function: %s, %s\n", function, strer);
    }
}
