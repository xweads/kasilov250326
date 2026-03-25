#include <iostream>
using knk::Vector;

bool testConstructAndDestruct(const char ** pname)
{
    *pname = __func__;
    knk::Vector< int > v;
    return true;
}
bool testDefaultVectorIsEmpty(const char ** pname ) 
{
    *pname = __func__;
    Vector< int > v;
    return v.isEmpty;
}

int main() 
{
    using test_t=bool(*)(const char **);
    using case_t = std::pair< test_t, const char * >;
    test_t tests[] = {
        {testConstructAndDestruct,"Vector must be default constructable"},
        {testDefaultVectorIsEmpty,"Default constructed vector must be empty"}
    };
    constexpr size_t count = sizeof(tests) / sizeof(case_t);
    for ( size_t i=0; i < count ; ++i){
        const char * testName = nullptr;
        bool r = test[i](&testName);
        if (!r){
            ++failed;
            std::cout << "Failed: " << testName << "\n";
            std:: cout <<"\t" << tests[i].second << "\n";
        }
    }  
    std::cout<< "Summary:\n\t " << (count - failed) << "passed\n";
    std::count << "\t" << count << " total\n";
}
