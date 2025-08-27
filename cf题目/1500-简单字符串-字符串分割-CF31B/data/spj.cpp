#include "testlib.h"
#include <string>
// 目前只支持 testlib库 
// 选手正确返回 quitf(_ok, '')
// testlib 的github https://github.com/MikeMirzayanov/testlib
using namespace std;
int main(int argc, char *argv[])
{
    /*
   * inf：输入
   * ouf：选手输出
   * ans：标准输出
   */
    registerTestlibCmd(argc, argv);
    string in     = inf.readString();
    string output = ouf.readString();
    string Answer = ans.readString();
    if (Answer == "No solution") {
        if (output == "No solution") quitf(_ok, "right");
        else quitf(_wa, "wrong1");
    }
    string ou;
    for (auto c : output) {
        if (c != ',') ou += c;
    }
    if (ou == in) quitf(_ok, "right");
    else quitf(_wa, "wrong2");
}
