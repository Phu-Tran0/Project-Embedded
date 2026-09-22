#include <iostream>
using namespace std;

int global_var=100;

void stack_function(){
    int stack_var=10;
    cout<<"Stack variable address: "<<&stack_var<<endl;
}

int main(){
    int local_var=20;
    int *heap_var=new int(50);

    cout<<"Data(Global): "<<&global_var<<endl;
    cout<<"Stack(Local): "<<&local_var<<endl;
    stack_function();
    cout<<"Heap: "<<heap_var<<endl;

    delete heap_var;
    return 0;
}
