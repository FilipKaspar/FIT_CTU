#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <memory>
#include <cassert>
using namespace std;

class CDelivery
{
public:
    // ctor
    // dtor

    // add connection from -> to, fluent interface
    CDelivery & addConn ( const string & from, const string & to );

    // returns a map containing shortest path to each customer from any of the depots
    // map key is the customer name, value is a list of nodes on the shortest path (depot -> customer)
    // if there is no path, the value is an empty list
    map<string, list<string>> serveCustomers ( const set<string> & customers, const set<string> & depots ) const;

public:
    multimap<string, string> routes;
};

CDelivery & CDelivery::addConn ( const string & from, const string & to )
{
    routes.emplace( to, from );
    return *this;
}

map<string, list<string>> CDelivery::serveCustomers ( const set<string> & customers, const set<string> & depots ) const
{
    map<string, list<string>> vysledek;

    // vypocet cesty pro kazdeho zakaznika - BFS
    for (const auto &zakaznik : customers)
    {
        queue<string> kNavsteve( {zakaznik} );
        map<string, string> prohledano; // kam - odkud

        prohledano.emplace(zakaznik, "");

        // tvorba navratove cesty pro kazdeho zakaznika - defaultne cesta neexistuje
        vysledek.emplace(zakaznik, list<string>());

        // prohledavani grafu dokud neni sklad zakaznika nebo jsme neprosli vse
        while (!kNavsteve.empty())
        {
            string aktualni = kNavsteve.front();
            kNavsteve.pop();

            // dorazili jsme do nejakeho skladu
            if (depots.find(aktualni) != depots.end())
            {
                // vytvorime cestu od zakaznika do skladu
                list<string> cesta;

                string krok = *depots.find(aktualni);
                while (krok != "")
                {
                    cesta.emplace_back(krok);
                    krok = prohledano[krok];
                }

                vysledek[zakaznik] = cesta;
                break;
            }

            // pridani vsech nenavstivenych sousedu do fronty
            const auto i = routes.equal_range(aktualni);
            for ( auto it = i.first; it != i.second; ++it )
            {
                if (prohledano.find(it->second) == prohledano.end())
                {
                    kNavsteve.push(it->second);
                    prohledano.emplace(it->second, aktualni);
                }
            }
        }
    }
    return vysledek;
}

int main ()
{
    CDelivery t0;
    map<string, list<string>> r;
    t0.addConn("Austin", "Berlin");
    t0.addConn("Chicago", "Berlin");
    t0.addConn("Berlin", "Dallas");
    t0.addConn("Dallas", "Essen");
    t0.addConn("Essen", "Austin");
    t0.addConn("Frankfurt", "Gyor");
    t0.addConn("Gyor", "Helsinki");
    t0.addConn("Helsinki", "Frankfurt");

    /*for(const auto & i : t0.routes){
        cout << i.first << " : " << i.second << endl;
    }*/

    r = t0.serveCustomers(set<string>{"Berlin", "Gyor"}, set<string>{"Essen", "Helsinki"});
    assert ( r == (map<string, list<string>>{ {"Berlin", {"Essen", "Austin", "Berlin"}}, {"Gyor", {"Helsinki", "Frankfurt", "Gyor"}} }) );

    r = t0.serveCustomers(set<string>{"Austin", "Gyor", "Chicago"}, set<string>{"Austin", "Dallas"});
    assert ( r == (map<string, list<string>>{ {"Austin", {"Austin"}}, {"Chicago", { }}, {"Gyor", { }} }) );

    t0.addConn("Chicago", "Helsinki");

    r = t0.serveCustomers(set<string>{"Austin", "Gyor", "Chicago"}, set<string>{"Austin", "Dallas"});
    assert ( r == (map<string, list<string>>{ {"Austin", {"Austin"}}, {"Chicago", { }}, {"Gyor", { }} }) );

    t0.addConn("Berlin", "Chicago");

    r = t0.serveCustomers(set<string>{"Austin", "Gyor", "Chicago"}, set<string>{"Austin", "Dallas"});
    assert ( r == (map<string, list<string>>{ {"Austin", {"Austin"}}, {"Chicago", {"Austin", "Berlin", "Chicago"}}, {"Gyor", {"Austin", "Berlin", "Chicago", "Helsinki", "Frankfurt", "Gyor"}} }) );

    t0.addConn("Essen", "Frankfurt");

    r = t0.serveCustomers(set<string>{"Austin", "Gyor", "Chicago"}, set<string>{"Austin", "Dallas"});
    assert ( r == (map<string, list<string>>{ {"Austin", {"Austin"}}, {"Chicago", {"Austin", "Berlin", "Chicago"}}, {"Gyor", {"Dallas", "Essen", "Frankfurt", "Gyor"}} }) );

    return EXIT_SUCCESS;
}