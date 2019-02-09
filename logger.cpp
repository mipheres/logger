#include "logger.h"
#include <iostream>

typedef void* (*THREADFUNCPTR)(void*);

Logger::Logger(){
    std::cout<<"Logger Constructor\n";
    
    m_exit=false;

    pthread_mutex_init(&m,NULL);
    pthread_cond_init(&c,NULL);
    // std::ofstream ofs("log.txt",std::ofstream::out);
    ofs.open("log.txt",std::ofstream::out);
    ofs<<"Log file\n"; 

    pthread_create(&t,NULL,(THREADFUNCPTR)&Logger::helper,this);
}

Logger::~Logger(){
    std::cout<<"Logger Destructor\n";

    pthread_mutex_lock(&m);
    m_exit=true;
    pthread_mutex_unlock(&m);
    pthread_cond_signal(&c);
    pthread_join(t,NULL);

    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&c);

    ofs.close(); 
}

void Logger::log(std::string s)
{
    pthread_mutex_lock(&m);
    que.push(s);
    pthread_cond_signal(&c);
    pthread_mutex_unlock(&m);
}

void* Logger::helper(void* args)
{
    Logger *l=static_cast<Logger*>(args);
    l->shell_logger();
}


void* Logger::shell_logger()
{
    std::cout<<"shell_logger\n";

    while(1){
        pthread_mutex_lock(&m);
         // while(que.empty()){
         if(!m_exit){
             pthread_cond_wait(&c,&m);
         }
        /*que not empty*/
        pthread_mutex_unlock(&m);
        while(!que.empty()){
            pthread_mutex_lock(&m);
            // std::cout<<que.front()<<"\n";
            ofs<<que.front()<<"\n";
            que.pop(); 
            pthread_mutex_unlock(&m);
        }
        if(m_exit){
            break;
        }
    }

    pthread_exit(NULL);
}

