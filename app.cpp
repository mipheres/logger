#include <iostream>
#include <vector>
#include <sstream>
#include "logger.h"

static void* log_client(void*l);

int main(int argc,char* argv[])
{
    std::cout<<"Hello fun.logger\n";

    std::vector<pthread_t> threads;

    Logger l;
    for(int i=0;i<10;i++){
        pthread_t t;
        
        pthread_create(&t,NULL,log_client,(void*)&l);
        threads.push_back(t);
    }

    for(int i=0;i<threads.size();i++){
        pthread_join(threads[i],NULL);
    }

    //l.logprint();
    // std::cout<<"Goodbye  fun.logger\n";
    return 0;
}

static void* log_client(void* l)
{
    Logger *pl=(Logger*)l;

    for(int i=0;i<10;i++){
        std::stringstream ss;
        ss<<"Log: Thread #"<<pthread_self()<<" Line #"<<i;
        pl->log(ss.str());
    }

    pthread_exit(NULL);

}
