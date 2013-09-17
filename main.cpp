// Search roundles

#include <iostream>
#include <list>
using namespace std;
typedef unsigned long int uli;
const uli LAST_ELEMENT;

void kill(list <uli> list_sacrifises, list <uli> real_sacrifises){

}

uli sum_div(uli ch){

}

bool found(uli element, list <uli> l){
    for (list <uli>::iterator i = l.begin(); i != l.end; ++i)
        if (*i == element)
            return true;
    return false;
}

void merge(list <uli> roundlaye, list <uli> l_roundlayes){
    if (roundlaye.empty())
        return;
    for (list <uli>::iterator i = roundlaye.begin(); i != roundlaye.end(); ++i)
    {
        for (list <uli>::iterator j = l_roundlayes.begin(); j != l_roundlayes.end(); ++j)
            if (*i==*j)
                break;
        if (j == l_roundlayes.begin()) // нет таких как i
            l_roundlayes.push_back(*i);
    }
}

int main()
{
    list <uli> l_roundlayes; // части хороводов в том числе и просто перспективные
    list <uli> max_roundlaye; // максимальный хоровод

    for (uli cur = 1; l_roundlayes.size() < LAST_ELEMENT; cur++)
    {
        list <uli> cur_roundlaye;
        for (uli buble = sum_div(cur); ; buble = sum_div(buble)) // начнем хоровод с текущего (cur)
        {
            if (buble > cur) // цепочка возможно нас устраивает, может она хоровод? пусть живет, пака
                break;
            if (buble == 1 || buble == cur || !found(bouble, l_roundlayes)) // цепь ведет ясно куда..
            {
                if (buble == cur) // да это цепочка - хоровод
                    if (cur_roundlaye.size() >= max_roundlaye.size()) // и длинна подходящая
                        // там >= поскольку сейчас ищем максимальные хороводы
                        max_roundlaye = cur_roundlaye; // "я тебя запомнил, сейчас ты достойней всех"
                kill(cur_roundlaye, l_roundlayes); // больше не ты, не твои части, не нужны, умри
                break;
            }
            cur_roundlayes.push_back(buble);
        }
        merge(cur_roundlaye, l_roundlayes);// добавим элементы в l_roundlayes
    }


    return 0;
}

