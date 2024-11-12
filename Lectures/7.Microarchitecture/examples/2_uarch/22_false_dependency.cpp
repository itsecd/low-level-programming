#include <vector>
#include <scope_timer.hpp>
#include <random_utils.hpp>
#include <iostream>

std::vector<short> mul4(const std::vector<short>& v){
    std::vector<short> result(v.size());
    for(long long i = 0; i < v.size();++i){
          result[i] = v[i]*4;
    }
    return result;
}


std::vector<short> mul4_bad(const std::vector<short>& v){
    std::vector<short> result(v.size());
    for(long long i = 0; i < v.size();++i){
        asm(
                "mov ax, %1\n\t"
                "lea ax, [eax*4]\n\t" //incomplete rewrite
                "mov %0, ax\n\t"
                : "=m"(result[i])
                : "m"(v[i])
                : "rax"
            );
    }
    return result;
}

std::vector<short> mul4_good(const std::vector<short>& v){
    std::vector<short> result(v.size());
    for(long long i = 0; i < v.size();++i){
        asm(
                "movzx eax, short %1\n\t"
                "lea eax, [eax*4]\n\t"    //complete rewrite
                "mov %0, ax\n\t"
                : "=m"(result[i])
                : "m"(v[i])
                : "rax"
                );
    }
    return result;
}

constexpr size_t SIZE = 16*1024*1024;

int main(){
    std::vector<short> v(SIZE);
    fill_random(v.begin(), v.end());
    std::vector<short> v1, v2, v3;
    {
        scope_timer _("mul_bad");
        v1 = mul4_bad(v);
    }

    {
        scope_timer _("mul_good");
        v2 = mul4_good(v);
    }

    {
        scope_timer _("mul");
        v3 = mul4(v);
    }
    std::cout <<std::boolalpha<< (v1 == v2) << std::endl;
    std::cout <<std::boolalpha<< (v2 == v3) << std::endl;
}