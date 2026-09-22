#include <iostream>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

int main(){
    int *shared_data=(int*)mmap(NULL,sizeof(int),
        PROT_READ|PROT_WRITE,
        MAP_SHARED|MAP_ANONYMOUS,-1,0);

    *shared_data=0;

    pid_t pid=fork();

    if(pid==0){
        cout<<"Child writes data"<<endl;
        *shared_data=100;
    }
    else{
        wait(NULL);
        cout<<"Parent reads data: "<<*shared_data<<endl;
    }

    munmap(shared_data,sizeof(int));
    return 0;
}
