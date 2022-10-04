#include <iostream>
#include <string>
#include <typeinfo>
#include <memory>
#include <cstdlib>
#include <cxxabi.h>
#include <boost/type_index.hpp>

// template<typename T>
// void Func(T&& obj)  // universal reference 必须是模板参数
// {
//     using boost::typeindex::type_id_with_cvr;
//     std::cout << "obj = " << obj << '\n';
//     std::cout << "T = " << type_id_with_cvr<T>().pretty_name() << '\n';
// }



int main(void)
{
	// std::string str = "Test";
	// Func(str);
	// Func(std::move(str));

	// system("pause");
    {
    char* name = abi::__cxa_demangle(typeid(std::string).name(), nullptr, nullptr, nullptr);
    std::cout << name;
    free(name);
    }
	return 0;
}