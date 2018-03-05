#include <iostream>
#include <random>
#include <utility>
#include <vector>
#include <algorithm>

typedef struct C
{
    float x;
    float y;
    int id;
    bool visited = false;
    bool operator <(struct C& rhs)
    {
        return this->id < rhs.id;
    }
}City;

float sqr(float value)
{
    return value*value;
}

float distance(City m1, City m2)
{
    auto [x1, y1, id1, b1] = m1;
    auto [x2, y2, id2, b2] = m2;
    return sqrt(sqr(x1-x2) + sqr(y1-y2));
}

int factorial(int n)
{
    int product = 1;
    for (int j=1; j<=n; j++ )
    product *= j;
    return product;
}

std::vector<float> bruteforce(std::vector<City> cities)
{
    std::vector<float> results;

    do
    {
        float path = 0.f;
        for(int i = 0; i<cities.size()-1; i++)
            path += distance(cities[i], cities[i+1]);

        results.push_back(path);
    }while(std::next_permutation(cities.begin() + 1, cities.end()));

return results;
}


float always_shortest(std::vector<City>& cities)
{
    if(cities.size() <= 1)
        return 0.f;
    if(cities.size() < 2)
    {
        //std::cout << distance(cities[0], cities[1]) << '\n';
        return distance(cities[0], cities[1]);
    }
        

    auto start = cities[0];
    
    int i = 0, j = 0;
    float shortest_path = distance(start, cities[1]);
    std::vector<City> rest(cities.begin()+1, cities.end());
    //std::cout << "start id : " << start.id << '\n';
    for(auto c : rest)
    {   
        float path = distance(start, c);
        if(path < shortest_path)
        {
            j = i;
            shortest_path = path;
            //std::cout << start.id << " " << c.id << '\n';
        }
        i++;
    }
    std::swap(rest[0], rest[j]);
    
    return shortest_path + always_shortest(rest);
}

 






int main(int argc, char* argv[])
{

    std::random_device rd;
    std::mt19937_64 rng(rd());
    std::uniform_real_distribution<float> range(0, 10);
    const int ilosc_miast = std::atoi(argv[1]);
    
    std::vector<City> cities(ilosc_miast);
    std::vector<City> cities_bf(cities.size());
    std::vector<City> cities_as(cities.size());
    
    int i = 0;
    for(auto&& m : cities)
    {

        m.x = range(rd);
        m.y = range(rd);
        //m.x = i;
        //m.y = i;
        m.id = i;
        i ++;
        
    }

    std::copy(cities.begin(), cities.end(), cities_bf.begin());
    std::copy(cities.begin(), cities.end(), cities_as.begin());


    std::vector<float> wyniki = bruteforce(cities_bf);
    
    float result_as =always_shortest(cities_as); 
    
    std::cout << result_as << "\n\n";


    for(auto w : wyniki)
            std::cout << "wynik : " << w << '\n';
    

    return 0;
}

