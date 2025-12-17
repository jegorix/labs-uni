#include"headre.hpp"

int main() {
    string restart;
    do{
        run();
        restart = safeGetLine(cin, currentLang, "Do u wana repeate this task(y/n) y - yes, n - no: ");
        
    }while(restart != "n" && restart != "N");
    cout << "Exiting ...";
    return 0;
}