#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

volatile bool g_quit_flag = false;

void thread_func(int thrID){

    while(!g_quit_flag){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        printf("Thread %d is running...\n", thrID);
    }
    printf("Thread %d is exiting...\n", thrID);
}

int basic_usage(){

    std::vector<std::thread> threads;
    for(int i = 0; i < 3; i++){
        threads.push_back(std::thread(thread_func, i));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    g_quit_flag = true;

    for(auto& t : threads){
        t.join();
    }
    printf("All threads are exited.\n");

    return 0;
}

int main(int argc, char* argv[]){

    printf("****** %s ******\n", PROJECT_NAME);

    basic_usage();

    return 0;
}