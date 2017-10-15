#include <type_traits>

template<class T1, class T2 = void, class Enable = void>
struct One
{
    static_assert(std::is_same<Enable,void>::value,"'Enable' template parameter should never be implement");
};

template<class T1, class T2> 
struct One<T1, T2, typename std::enable_if<std::is_same<T2,void>::value>::type>
{ 
    T1 field1;
};

template<class T1, class T2> 
struct One<T1, T2, typename std::enable_if<!std::is_same<T2,void>::value>::type> : public One<T1>
{ 
    T2 field2;
};

int main()
{

    One<int> tint;
    One<int, float> tintfloat;
//    One<int, float, char> tbad;


    tintfloat.field1;
    tintfloat.field2;
    tint.field1;
    //tint.field2;

    return 0;
}

