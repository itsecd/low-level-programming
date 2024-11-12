#include <scope_timer.hpp>
#include <span>
#include <vector>

struct user{
    int age;
    float money;
};

double avg_money(std::span<const user> users){
    float result {};
    for(auto& u: users){
        result += u.money;   // 1 operation
    }
    return (double)result/users.size();
}

user avg_user(std::span<const user> users){
    long long age{};
    float money{};
    for(auto& u: users){
        age += u.age;       //2 operations
        money += u.money;
    }
    age = (double)age/users.size();
    money = money /users.size();
    return {(int)age, money};
}

constexpr size_t USERS_COUNT = 16;

int main(){
    std::vector<user> users(USERS_COUNT);
    for(auto& u: users)
    {
        u.age = rand() % 130;
        u.money = rand();
    }

    {
        scope_timer<std::nano> _{"Average money computation"};
        volatile float money = avg_money(users);
    }

    {
        scope_timer<std::nano> _{"Average age and money computation"};
        volatile user u = avg_user(users);
    }



}