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
    return v.isEmpty();
}
bool testSizeOfNonEmptyVector(const char ** pname ){
    *pname = __func__;
    constexpr size_t size = 2;
    Vector< int > v(size,5);
    return v.getSize() == size;
}
bool testSizeOfEmptyVector(const char ** pname ){
    *pname = __func__;
    Vector< int > v(2ull,5);
    return v.getSize()== 2ull;
}

bool testCopyConstructor(const char ** pname ){
    *pname = __func__;
    Vector< int > v;
    v.pushBack(1);
    v.pushBack(2);
    Vector< int > yav = v;
    if ( v.isEmpty() &&  yav.isEmpty()){
        throw std::logic_error("Vectors must be non-empty");
    }
    bool isEqual = yav.getSize() == v.getSize();
    for ( size_t i=0; i < yav.getSize() && isEqual; ++i){
        try{
            isEqual = yav.at(i) == v.at(i);
        }
        catch (...){
            isEqual = false;
        }
    }
    return isEqual;
}

bool testElementCheckedAccess(const char ** pname ){
    *pname = __func__;
    Vector< int > v;
    try {
        int& r = v.at(0);
        return v.at(0) == 2;
    }
    catch (...) {
        return false;
    }
}
bool testElementCheckedOutOfBoundAccess(const char ** pname){
    *panme = __func__;
    Vector< int > v;
    try {
        v.at(0);
        return false;
    } catch ( const std::out_of_range& e) {
        return std::strcmp("id out of bound", text)
    }
     catch (...){
        return true;
    }
}

int main() 
{
    using test_t=bool(*)(const char **);
    using case_t = std::pair< test_t, const char * >;
    case_t tests[] = {
        {testConstructAndDestruct,"Vector must be default constructable"},
        {testDefaultVectorIsEmpty,"Default constructed vector must be empty"},
        {testSizeOfEmptyVector,"Size of empty vector must be zero"},
        {testSizeOfNonEmptyVector,"Size of non-empty vector must be greater than zero"},
        {testElementCheckedAccess,"Inbound access must return lvalue "},
        {testElementCheckedOutOfBoundAccess,""},
        {testCopyConstructor,""},
    };
    constexpr size_t count = sizeof(tests) / sizeof(case_t);
    for ( size_t i=0; i < count ; ++i){
        const char * testName = nullptr;
        bool r = false;
        try {
            r = tests[i].first(&testName);
        } catch ( const std::logic_error& e) {
            std::cout << "[NOT RUN]" << testName << "\n";
            std::cout << "\t" << e.what() << "\n";
        }
        if (!r){
            ++failed;
            std::cout << "Failed: " << testName << "\n";
            std:: cout <<"\t" << tests[i].second << "\n";
        }
    }  
    std::cout<< "Summary:\n\t " << (count - failed) << "passed\n";
    std::cout << "\t" << count << " total\n";
}
