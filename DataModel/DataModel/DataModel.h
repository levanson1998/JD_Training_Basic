#ifdef DATAMODEL_EXPORTS
#define DATAMODEL_API __declspec(dllexport) 
#else
//#define DLLTEST_API __declspec(dllimport) 
#define DATAMODEL_API
#endif


class DataModel
{
public: 
    void ReadFile();
    void SaveFile();
};