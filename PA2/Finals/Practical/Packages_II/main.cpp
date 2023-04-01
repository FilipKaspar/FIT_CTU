#include<iostream>
#include<cassert>
#include<vector>
#include<set>
#include<map>
#include<string>
#include<unordered_map>
#include<memory>
#include<unordered_set>
#include<queue>
#include<list>
#include<sstream>
#include<cstring>

using namespace std;

class CPkg{
public:
    //TODO constructor
    CPkg(const string & name){
        this->name = name;
    }
    //TODO addDep(string)
    CPkg & addDep(const string & name){
        dependencies.insert(name);
        return *this;
    }

public:
    set<string> dependencies;
    string name;
};
class CPkgSys{
public:
    //TODO addPkg
    CPkgSys & addPkg (const CPkg & src){
        packages.insert(make_pair(src.name,src.dependencies));
        return *this;
    }

    void checkDep(const string & src, set<string> & checked, set<string> & toInstall){
        bool found = false;
        for(const auto & all : packages){
            if(all.first == src){
                if(checked.count(src)){
                    return;
                }
                else{
                    found = true;
                    if(installed.count(src)){
                        break;
                    }
                    toInstall.insert(src);
                    checked.insert(src);
                    for(const auto & dep : packages.find(src)->second) {
                        checkDep(dep,checked,toInstall);
                    }
                }
            }
        }

        if(!found){
            throw invalid_argument("Package not found.");
        }
    }


    //TODO install(list<string> )
    set<string> install(const list<string> & src){
        /*for(const auto & i : packages){
            cout << i.first << ":" << flush;
            for(const auto & p : i.second){
                cout << p << ", " << flush;
            }
            cout << endl;
        }*/

        set<string> toBeInstall;
        set<string> checked;
        for(const auto & toInstall : src){
            checkDep(toInstall, checked, toBeInstall);
        }

        for(const auto & toIns : toBeInstall){
            installed.insert(toIns);
        }

        return toBeInstall;
    }

    //TODO operator <<
    friend ostream & operator << (ostream & os, const CPkgSys & src){
        long unsigned int k = 0;
        for(const auto & i : src.installed){
            k++;
            os << i;
            if(k < src.installed.size()) os << ", ";
        }
        return os;
    }
public:
    map<string, set<string>> packages;
    set<string> installed;
};

int main(){
    CPkgSys s;
    stringstream ss;
    s.addPkg(CPkg("ssh").addDep("sudo").addDep("apt"))
            .addPkg(CPkg("sudo").addDep("git").addDep("c++"));
    s.addPkg(CPkg("apt"))
            .addPkg(CPkg("c++").addDep("c").addDep("asm").addDep("fortran"));
    s.addPkg(CPkg("git"))
            .addPkg(CPkg("c").addDep("kekw"))
            .addPkg(CPkg("kekw"))
            .addPkg(CPkg("asm"))
            .addPkg(CPkg("fortran"));
    s.addPkg(CPkg("python").addDep("bash").addDep("sadge"))
            .addPkg(CPkg("karel").addDep("python"))
            .addPkg(CPkg("bash").addDep("sadge"))
            .addPkg(CPkg("sadge"))
            .addPkg(CPkg("cython").addDep("dev"));
    s.addPkg(CPkg("perl"));

    ss << s;
    assert(ss.str() == "");
    ss.clear();
    ss.str("");

    set<string> t1 = s.install(list<string> {"sudo"});
    assert(t1 == (set<string> {"asm", "c", "c++", "fortran", "git", "kekw", "sudo"}));
    set<string> t2 = s.install(list<string> {"ssh", "c++"});
    assert(t2 == (set<string> {"apt", "ssh"}));

    ss << s;
    assert(ss.str() == "apt, asm, c, c++, fortran, git, kekw, ssh, sudo");
    ss.clear();
    ss.str("");

    try{
        set<string> e = s.install(list<string> {"karel", "cython"});
        assert("Sem ses nemel dostat debilku" == nullptr);
    }
    catch(const invalid_argument & e){
        assert(strcmp("Package not found.", e.what()) == 0);
    }
    set<string> t3 = s.install(list<string> {"karel", "fortran", "git"});
    assert(t3 == (set<string> {"bash", "karel", "python", "sadge"}));

    s.addPkg(CPkg("java").addDep("utils"))
            .addPkg(CPkg("utils").addDep("VB"))
            .addPkg(CPkg("VB").addDep("java"));

    set<string> t4 = s.install(list<string> {"java", "perl"});
    assert(t4 == (set<string> {"VB", "java", "perl", "utils"}));

    ss << s;
    assert(ss.str() == "VB, apt, asm, bash, c, c++, fortran, git, java, karel, kekw, perl, python, sadge, ssh, sudo, utils");
    ss.clear();
    ss.str("");

    CPkgSys k;
    k.addPkg(CPkg("ssh").addDep("sudo").addDep("apt"))
            .addPkg(CPkg("sudo").addDep("git"));
    k.addPkg(CPkg("apt"));
    k.addPkg(CPkg("git"))
            .addPkg(CPkg("c").addDep("kekw"))
            .addPkg(CPkg("kekw"))
            .addPkg(CPkg("asm"))
            .addPkg(CPkg("fortran"));
    k.addPkg(CPkg("python").addDep("bash").addDep("sadge"))
            .addPkg(CPkg("karel").addDep("python"))
            .addPkg(CPkg("bash").addDep("sadge"))
            .addPkg(CPkg("sadge"));
    k.addPkg(CPkg("perl").addDep("no"));

    set<string> t5 = k.install(list<string> {"asm"});
    assert(t5 == (set<string> {"asm"}));
    set<string> t6 = k.install(list<string> {"python", "ssh"});
    assert(t6 == (set<string> {"apt", "bash", "git", "python", "sadge", "ssh", "sudo"}));

    try{
        set<string> t7 = k.install(list<string> {"perl", "c"});
        assert("Sem ses nemel dostat debilku" == nullptr);
    }
    catch(const invalid_argument & e){
        assert(strcmp("Package not found.", e.what()) == 0);
    }
    set<string> t8 = k.install(list<string> {"c", "ssh", "karel"});

    assert(t8 == (set<string> {"c", "karel", "kekw"}));

    ss << k;
    assert(ss.str() == "apt, asm, bash, c, git, karel, kekw, python, sadge, ssh, sudo");
    ss.clear();
    ss.str("");

}