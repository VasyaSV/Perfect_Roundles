// Search roundles

#include <iostream>
#include <list>
#include <string>
using namespace std;
typedef unsigned long int uli;
const uli LAST_ELEMENT = 10000000;// 0.5 for max

void kill(list <uli> list_sacrifises, list <uli> &real_sacrifises){
    // убиваем всех по списку
    for (list <uli>::iterator i = list_sacrifises.begin(); i != list_sacrifises.end(); ++i)
        for (list <uli>::iterator j = real_sacrifises.begin(); j != real_sacrifises.end(); ++j)
            if (*i==*j)
            {
                real_sacrifises.erase(j);
                break;
            }
}

uli sum_div(uli num){ // Сложность O(sqrt(n))
    uli sum = 1, k = 1, i;
       if (num == 1)
          return num;
       while ((num & 1) == 0)
       {
          k <<= 1;
          num >>= 1;
       }
       k = (k << 1) - 1;
       if (num == 1)
          return k;
       else
          sum = k;
       for(i = 3; i*i <= num; i += 2)
       {
          k = 1;
          while(num % i == 0)
          {
             k *= i;
             num /= i;
          }
          if (k > 1)
             sum *= ((k * i) - 1)/(i - 1);
       }
       if (num > 1)
          sum *= num + 1;
       return sum;
}

uli sum_befor_div(uli num){
    uli temp = sum_div(num)-num;
    if (num > LAST_ELEMENT)
        return 1;
    return temp;
}

bool found(uli element, list <uli> l){
    for (list <uli>::iterator i = l.begin(); i != l.end(); ++i)
        if (*i == element)
            return true;
    return false;
}

void merge(list <uli> roundlaye, list <uli> &l_roundlayes){
    if (roundlaye.empty())
        return;
    for (list <uli>::iterator i = roundlaye.begin(); i != roundlaye.end(); ++i)
    {
        list <uli>::iterator j = l_roundlayes.begin();
        for (; j != l_roundlayes.end(); ++j)
            if (*i==*j)
                break;
        if (j == l_roundlayes.end()) // нет таких как i
            l_roundlayes.push_back(*i);
    }
}

int main()
{
    list <uli> l_roundlayes; // части хороводов в том числе и просто перспективные
    list <uli> max_roundlaye; // максимальный хоровод
    cout << sum_befor_div(1210) << " ";
    cout << sum_befor_div(1184);


    for (uli cur = 1; l_roundlayes.size() < LAST_ELEMENT; cur++)
    {
        list <uli> cur_roundlaye;
        cur_roundlaye.push_back(cur);
        for (uli buble = sum_befor_div(cur); ; buble = sum_befor_div(buble)) // начнем хоровод с текущего (cur)
        {
            if (buble > cur) // цепочка возможно нас устраивает, может она хоровод? пусть живет, пака
            {
                l_roundlayes.push_back(buble);
                break;
            }
            if (buble == 1 || buble == cur || !found(buble, l_roundlayes)) // цепь ведет ясно куда..
            {
                if (buble == cur) // да это цепочка - хоровод
                    if (cur_roundlaye.size() >= max_roundlaye.size()) // и длинна подходящая
                        // там >= поскольку сейчас ищем максимальные хороводы
                        max_roundlaye = cur_roundlaye; // "я тебя запомнил, сейчас ты достойней всех"
                // поиск
                kill(cur_roundlaye, l_roundlayes); // больше не ты, не твои части, не нужны, умри
                cur_roundlaye.clear();
                break;
            }
            cur_roundlaye.push_back(buble);
        }
        merge(cur_roundlaye, l_roundlayes);// добавим элементы в l_roundlayes
    }
    cout << "found roundlaye for diapozon [1.." << LAST_ELEMENT <<"]\n" ;
    cout << "it's long = " << max_roundlaye.size() << "\n";
    cout << "roundlaye: ";
    for (list <uli>::iterator i = max_roundlaye.begin(); i != max_roundlaye.end(); ++i)
        cout << *i << " ";
    return 0;
}

