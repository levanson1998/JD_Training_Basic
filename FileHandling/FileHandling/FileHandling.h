#ifdef FILEHANDLING_EXPORTS
#define FILEHANDLING_API __declspec(dllexport) 
#else
//#define DLLTEST_API __declspec(dllimport) 
#define FILEHANDLING_API
#endif

#include "array"

struct rectangle
{
    std::array<double, 2> xy1;
    std::array<double, 2> xy2;
    std::array<double, 2> xy3;
    std::array<double, 2> xy4;
};

struct line
{
    std::array<double, 2> xy1;
    std::array<double, 2> xy2;
};

struct circle
{
    std::array<double, 2> o;
    double r;
};

class FileHandling
{
public:
    static FILEHANDLING_API double Doublex2(double a);
    void ProcRectangle();
    void ProcLine();
    void ProcCircle();
};