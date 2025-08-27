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
    int x = ouf.readInt();
    int y = ouf.readInt();

    int k = ans.readInt();
    while (k--) {
        int xx = ans.readInt();
        int yy = ans.readInt();
        quitf(_ok, "right");
    }
    quitf(_wa, "wrong");
}