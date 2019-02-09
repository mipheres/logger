#ifndef LOGGER_H
#define LOGGER_H

#include <pthread.h>
#include <queue>
#include <string>


class Logger{
    Logger(const Logger&);/*private copy constructor*/
    Logger& operator=(const Logger&);/*private copy constructor*/
    public:
    Logger();/*constructor*/
    ~Logger();/*destructor*/

    void log(std::string s);
    void logprint();


    private:
    pthread_t t;
    std::queue<std::string> que;
    pthread_mutex_t m;
    pthread_cond_t  c;
    static void*helper(void*);
    // void* shell_logger(void*);
    void* shell_logger();
    bool m_exit;
};
#endif// LOGGER_H
