#include <iostream> 
#include <queue>
#include "Exception.h"
#include "Seq.h"
#include "ArraySeq.h"
#include <algorithm>


using namespace std;

float RandomFloat(float min, float max)//random
{
    return (float)(rand()) / RAND_MAX * (max - min) + min;
}

class Item
{
public:
    double weight;
    double value;
    double volume;
    double max_weigth;
    double max_volume;
    bool operator > (const Item& rhs) const {
        return value / ((weight/max_weigth) * (volume/ max_volume)) < rhs.value / ((rhs.weight/rhs.max_weigth) * (rhs.volume/ rhs.max_volume));
    }
    bool operator < (const Item& rhs) const {
        return value / ((weight / max_weigth) * (volume / max_volume)) > rhs.value / ((rhs.weight / rhs.max_weigth) * (rhs.volume / rhs.max_volume));
    }
    void operator = (const Item& rhs) {
        value = rhs.value;
        weight = rhs.weight;
        volume = rhs.volume;
    }

    friend ostream& operator<< (std::ostream& out, const Item& point);
};

ostream& operator<< (ostream& out, const Item& point)
{
    out << point.weight << " " << point.value << " " << point.volume;

    return out;
}


struct Node
{
    int level, bound;
    double weight, profit, volume, sumvolume;
};

bool cmp(Item a, Item b)
{
    double r1 = a.value / ((a.weight / a.max_weigth) * (a.volume / a.max_volume));
    double r2 = b.value / ((b.weight / b.max_weigth) * (b.volume / b.max_volume));
    return r1 > r2;
};


double bound(Node u, int n, double W, Sequence<Item>* arr, double max_volume)
{

    if (u.weight >= W)
        return 0;

    if (u.volume >= max_volume)
        return 0;


    double profit_bound = u.profit;

    int j = u.level + 1;
    double totweight = u.weight;
    double totvolume = u.volume;


    while ((j < n) && (totweight + arr->Get(j).weight <= W) && (totvolume + arr->Get(j).volume <= max_volume)) //arr[j].weight <= W
    {
        totweight += arr->Get(j).weight;
        profit_bound += arr->Get(j).value;
        totvolume += arr->Get(j).volume;
        j++;
    }

    return profit_bound;
}

template <class T>
double knackpack(double W, T* arr, int n, double max_volume)
{
 
    queue<Node> Q; 
   
    Node u, v;


    u.level = -1;
    u.profit = u.weight = u.volume = u.sumvolume = 0; // корневой
    Q.push(u);
   

 
    double maxProfit = 0;

    while (!Q.empty()) 
    {
        
        u = Q.front();
        
        Q.pop();
        

      
        if (u.level == -1)
            v.level = 0;

        
        if (u.level == n - 1)
            continue; 


        v.level = u.level + 1;


        v.weight = u.weight + arr->Get(v.level).weight; 
        v.profit = u.profit + arr->Get(v.level).value;
        v.volume  = u.volume + arr->Get(v.level).volume;


        if (v.weight <= W && v.volume <= max_volume && v.profit > maxProfit)
            maxProfit = v.profit;

        v.bound = bound(v, n, W, arr, max_volume);
 
        if (v.bound > maxProfit)
           Q.push(v); //не происходит перевеса на этом эл-те
 
        v.weight = u.weight;
        v.profit = u.profit;
        v.volume = u.volume;
        v.bound = bound(v, n, W, arr, max_volume);
        if (v.bound > maxProfit)
            Q.push(v);
    }

    return maxProfit;
}


int main()
{
    double max_volume;
    cout << "Enter backpack's volume: ";
    cin >> max_volume;
    //cout << endl;

    double max_weigth;
    cout << "Enter backpack's weigth: ";
    cin >> max_weigth;
    cout << endl;

    cout << "Enter backpack's size";
    int size;
    cout << endl;
    cin >> size;

    Item* arr = new Item[size];

    cout << "Select a data entry method : 1 - random, 2 - by yourself";
    int choice;
    cout << endl;
    cin >> choice;
    if (choice == 2) {
        for (int i = 0; i < size; i++) {
            cout << "Enter Item number " << i;
            cout << endl;

            cout << "Weight: ";
            cin >> arr[i].weight;
            //cout << endl;

            cout << "Value: ";
            cin >> arr[i].value;
            //cout << endl;

            cout << "Volume: ";
            cin >> arr[i].volume;
            cout << endl;

            arr[i].max_volume = max_volume;
            arr[i].max_weigth = max_weigth;

            cout << endl;
        }
    }
    if (choice == 1) {
        for (int i = 0; i < size; i++) {
            arr[i].weight = RandomFloat(0, max_weigth / 10.0);
            arr[i].value = RandomFloat(0, 150.0);
            arr[i].volume = RandomFloat(0, max_volume / 10.0);

            arr[i].max_volume = max_volume;
            arr[i].max_weigth = max_weigth;
        }
    }
    if (choice != 1 && choice != 2) throw Exception("Incorrect parametr");

    sort(arr, arr + size);

    Sequence<Item>* set = new ArraySequence<Item>(arr, size);
	
    cout << "Weigth     Value     Volume" << endl;
	for (int i = 0; i < set->GetLength(); i++) {
		cout << set->Get(i) << " ";
        cout << endl;
	}



    cout << endl;

    int n = set->GetLength();

    cout << "Maximum possible profit = " << knackpack(max_weigth, set, n, max_volume);

    return 0;
}

