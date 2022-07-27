#include "Controller.h"

int main(int argc, char* argv[]) {
    try{
        Controller controller(argc, argv);
        controller.run();
    }catch (ControllerException& e){
        cerr << e.what() << endl;
        exit(1);
    }
    return 0;
}
