#include <iostream>
#include <string>
using namespace std;
void logMsg(const string &msg, int level = 1)
{
    const string tag[] = {"INFO", "WARNING", "ERROR"};
    cout << "[" << tag[level] << "]" << msg << endl;
}
double intrest(double principal, double rate, int time = 1)
{
    return (principal * rate * time) / 100.0;
}
int main()
{
    logMsg("System started.");
    logMsg("This is an info message.", 0);
    logMsg("This is a warning message.", 1);
    logMsg("This is an error message.", 2);
    cout << "Simple intrest for principal=1000, rate=5, time=2: " << intrest(10000, 2) << endl;
    cout << "Simple intrest for principal=1000, rate=5: " << intrest(10000, 2, 9) << endl;
    return 0;
}