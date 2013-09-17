// Search roundles

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <conio.h>
using namespace std;
typedef unsigned long int uli;
const uli LAST_ELEMENT = 1000000;// 0.5 for max
// el roundleys
struct el_round{
    uli ch;
    uli last_ch;
};

void kill(list <uli> list_sacrifises, list <el_round> &real_sacrifises){
    // убиваем всех по списку
    if (list_sacrifises.empty())
        return;
    for (list <uli>::iterator i = list_sacrifises.begin(); i != list_sacrifises.end(); ++i)
        for (list <el_round>::iterator j = real_sacrifises.begin(); j != real_sacrifises.end(); ++j)
            if ((*i)==(*j).ch)
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
    if (num > LAST_ELEMENT || temp < 1)
        return 1;
    return temp;
}

bool found(uli element, list <el_round> l){
    for (list <el_round>::iterator i = l.begin(); i != l.end(); ++i)
        if ((*i).ch == element)
            return true;
    return false;
}

void clear_l_roundlayes(list <el_round> &l_roundlayes, uli cur){
    list <uli> kill_list;
    for (list <el_round>::iterator i = l_roundlayes.begin(); i != l_roundlayes.end() ; ++i)
        if ((*i).last_ch > cur)
            continue;
        else{ // иначе перещитываем
            uli bouble = sum_befor_div((*i).last_ch);
            for (; bouble < cur && found(bouble, l_roundlayes); bouble = sum_befor_div(bouble))
                ;
            (*i).last_ch = bouble;
            if (bouble < cur)
                kill_list.push_back((*i).ch);
            //cout << (*i).ch;
        }
    kill(kill_list, l_roundlayes);
}

void merge(list <uli> roundlaye, list <el_round> &l_roundlayes, uli cur){
    if (roundlaye.empty())
        return;
    clear_l_roundlayes(l_roundlayes, cur);
    for (list <uli>::iterator i = roundlaye.begin(); i != roundlaye.end(); ++i)
    {
        list <el_round>::iterator j = l_roundlayes.begin();
        for (; j != l_roundlayes.end(); ++j)
            if (*i == (*j).ch)
                break;
        if (j == l_roundlayes.end()) // нет таких как i
        {
            el_round tmp;
            tmp.ch = *i;
            tmp.last_ch = roundlaye.back();
            l_roundlayes.push_back(tmp);
        }
    }
}


int main()
{
    list <el_round> l_roundlayes; // части хороводов в том числе и просто перспективные
    list <uli> max_roundlaye; // максимальный хоровод
    uli last;
    //cout << sum_befor_div(4600);
    //cout << " " << sum_befor_div(sum_befor_div(4600)) ;
    cout << "Enter max: ";
    cin >> last;

    for (uli cur = 1; l_roundlayes.size() < LAST_ELEMENT; cur++)
    {
        list <uli> cur_roundlaye;
        cur_roundlaye.push_back(cur);
        for (uli buble = sum_befor_div(cur); ; buble = sum_befor_div(buble)) // начнем хоровод с текущего (cur)
        {
            if (buble > cur) // цепочка возможно нас устраивает, может она хоровод? пусть живет, пака
            {
                el_round tmp;
                tmp.ch = cur;
                tmp.last_ch = buble;
                l_roundlayes.push_back(tmp);
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
        merge(cur_roundlaye, l_roundlayes, cur);// добавим элементы в l_roundlayes
        //if (cur % 1000 == 0)
       // {
           // cout << cur << " max = " << max_roundlaye.size() << "\n";
            if (cur == last)
            {
                ofstream out("out.txt");
                out << max_roundlaye.size() << "\n";
                for (list <uli>::iterator i = max_roundlaye.begin(); i != max_roundlaye.end(); ++i)
                    out << (*i) << " ";
                break;
            }
       // }
    }
    cout << "found roundlaye for diapozon [1.." << LAST_ELEMENT <<"]\n" ;
    cout << "it's long = " << max_roundlaye.size() << "\n";
    cout << "roundlaye: ";
    for (list <uli>::iterator i = max_roundlaye.begin(); i != max_roundlaye.end(); ++i)
        cout << *i << " ";
    _getch();
    return 0;
}

