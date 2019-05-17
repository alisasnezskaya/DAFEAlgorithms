/****************************************************************************
Жадные алгоритмы

**Атлеты.**

В город *N* приехал цирк с командой атлетов. Они хотят удивить горожан
города *N* --- выстроить из своих тел башню максимальной высоты. Башня
--- это цепочка атлетов, первый стоит на земле, второй стоит у него на
плечах, третий стоит на плечах у второго и т.д.

Каждый атлет характеризуется силой s_i (kg) и массой m_i (kg).
Сила --- это максимальная масса, которую атлет способен держать у себя
на плечах.

К сожалению ни один из атлетов не умеет программировать, так как всю
жизнь они занимались физической подготовкой, и у них не было времени на
изучение языков программирования. Помогите им, напишите программу,
которая определит максимальную высоту башни, которую они могут
составить.

Известно, что если атлет тяжелее, то он и сильнее:
если m_i > m_j, то s_i > s_j.

Атлеты равной массы могут иметь различную силу.

*Формат входных данных:*

Вход содержит только пары целых чисел --- массу и силу атлетов. Число
атлетов 1 ≤ *n* ≤ 100000. Масса и сила являются положительными целыми
числами меньше, чем 2000000.

*Формат выходных данных:*

Выход должен содержать натуральное число --- максимальную высоту башни.

  in  | out
 -----+-----
  3 4 | 3
  2 2 |
  7 6 |
  4 5 |
 -----+-----
****************************************************************************/


#include <iostream> 
#include <algorithm> 
#include <vector> 

using namespace std; 

bool comp( pair<int, int> a, pair<int, int> b ) 
{ 
    return a.first < b.first; 
} 

int main() 
{ 
    int a, b; 
    vector < pair<int,int> > athlete; 
    while( !cin.eof() ) 
    { 
        cin >> a >> b; 
        pair<int, int> k (a, b); 
        athlete.push_back(k); 
    } 
    
    sort( athlete.begin(), athlete.end(), comp ); 
    int count = 1; 
    int max = athlete[0].first; 
    for( int i = 1; i < athlete.size(); i++ ) 
    { 
        if( athlete[i].second >= max ) 
        { 
            max += athlete[i].first; 
            count++; 
        } 
    } 
    cout << count; 
    return 0; 
}

