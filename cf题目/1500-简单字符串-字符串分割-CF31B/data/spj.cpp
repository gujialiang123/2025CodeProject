#include "testlib.h"
#include <string>
// Ŀǰֻ֧�� testlib�� 
// ѡ����ȷ���� quitf(_ok, '')
// testlib ��github https://github.com/MikeMirzayanov/testlib
using namespace std;
int main(int argc, char *argv[])
{
    /*
   * inf������
   * ouf��ѡ�����
   * ans����׼���
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
