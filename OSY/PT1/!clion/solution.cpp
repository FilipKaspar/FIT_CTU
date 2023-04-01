#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <climits>
#include <cfloat>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
#include <array>
#include <iterator>
#include <set>
#include <list>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <deque>
#include <memory>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <stdexcept>
#include <condition_variable>
#include <pthread.h>
#include <semaphore.h>
#include "progtest_solver.h"
#include "sample_tester.h"
using namespace std;
#endif /* __PROGTEST__ */

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
class CCompanyHandler{
public:
    explicit CCompanyHandler(ACompany & id){
        company_id = id;
    }

//private:
    ACompany company_id;

    thread wait_thread;
    thread solved_thread;

    queue<pair<unsigned long int,AProblemPack>> problems;
    // Long int - indicates how many problems from pack has been loaded to solver if = problempack.size + 2. Then whole pack is finished
};

class COptimizer
{
public:
    static bool                        usingProgtestSolver                     ( void )
    {
        return true;
    }
    static void                        checkAlgorithm                          ( AProblem                              problem )
    {
        // dummy implementation if usingProgtestSolver() returns true
    }
    void start (int threadCount);
    void stop ();
    void addCompany (ACompany company );
    void waitThreads(CCompanyHandler & company);
    void solveThreads(CCompanyHandler & company);
    void workingThreads(AProgtestSolver & solver);

private:
    condition_variable to_solve_empty;
    condition_variable to_send_empty;
    mutex wrk1;

    vector<CCompanyHandler> companies;

    vector<thread> work_threads;
    queue<CCompanyHandler*> all_problems;
    vector<pair<unsigned long int, AProblemPack>*> problems_to_set;
};

// TODO: COptimizer implementation goes here
void COptimizer::addCompany(ACompany company) {
    CCompanyHandler comp(company);
    companies.push_back(move(comp));
}

void COptimizer::start(int threadCount) {
    for(auto & company : companies){
        company.wait_thread = thread(&COptimizer::waitThreads, this, ref(company));
        company.solved_thread = thread(&COptimizer::solveThreads, this, ref(company));
    }

    auto solver = createProgtestSolver();
    for(int i = 0; i < threadCount; i++){
        work_threads.emplace_back(&COptimizer::workingThreads, this,ref(solver));
    }
}

void COptimizer::waitThreads(CCompanyHandler & company) {
    AProblemPack cur_problem_pack = company.company_id->waitForPack();
    unique_lock<mutex> lock(wrk1);
    lock.unlock();
    while(cur_problem_pack != nullptr){
        company.problems.push(make_pair(0, cur_problem_pack));

        lock.lock();
        all_problems.push(&company);
        lock.unlock();

        to_solve_empty.notify_one();
        cur_problem_pack = company.company_id->waitForPack();
    }

}

void COptimizer::solveThreads(CCompanyHandler & company) {
    while(true){
        unique_lock<mutex> lock(wrk1);
        to_solve_empty.wait(lock, [&company]() {
            if(company.problems.empty()) return false;
            if(!company.problems.front().second) return false;
            return company.problems.front().first == company.problems.front().second->m_Problems.size() + 2; });


        auto problems = &company.problems.front();
        if(!problems->second) break;
        while(problems->first == problems->second->m_Problems.size() + 2){
            company.company_id->solvedPack(problems->second);
            company.problems.pop();
            problems = &company.problems.front();
        }
    }
}


void COptimizer::workingThreads(AProgtestSolver & solver) {
    while(true){
        unique_lock<mutex> lock(wrk1);
        to_solve_empty.wait(lock, [this]() { return !all_problems.empty(); });

        auto cur_company = all_problems.front();
        all_problems.pop();
        if(!cur_company) break;
        auto cur_problem = &cur_company->problems.front();
        if(!cur_problem->second) continue;
        lock.unlock();

        for(auto problem = cur_problem->second->m_Problems.begin() + int(cur_problem->first);
                 problem != cur_problem->second->m_Problems.end(); problem++) {
            if (solver->hasFreeCapacity()) {
                lock.lock();
                solver->addProblem(*problem); // Maybe check if returned 0, but should be covered by hasFreeCapacity
                lock.unlock();
            } else {
                break;
            }
            cur_problem->first++;
        }

        if(cur_problem->second->m_Problems.size() == cur_problem->first - 1) {
            lock.lock();
            problems_to_set.push_back(cur_problem);
            lock.unlock();
        }
        //If we used all the problems, set to counter to the size of the problem array

        lock.lock();
        // Checking here one more time, in case the last problem has been loaded, therefore the for loop is gonna end and it would have to
        // wait for another thread call to call the solve method
        if(!solver->hasFreeCapacity()){
            lock.unlock();
            auto copy_solver = solver;
            lock.lock();
            solver = createProgtestSolver();
            lock.unlock();
            copy_solver->solve();
            lock.lock();
            for(auto & problem : problems_to_set){
                problem->first = problem->second->m_Problems.size() + 2;
            }
            problems_to_set.clear();
            lock.unlock();
            to_send_empty.notify_all();
        }
    }
}

void COptimizer::stop() {
    for(auto & company : companies){
        company.problems.push(make_pair(0, nullptr));
        company.wait_thread.join();
    }
    unique_lock<mutex> lock(wrk1);
    all_problems.push(nullptr);
    to_solve_empty.notify_all();
    lock.unlock();
    for(auto & work_thread : work_threads){
        work_thread.join();
    }
    for(auto & company : companies){
        company.solved_thread.join();
    }
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef __PROGTEST__
int                                    main                                    ( void )
{
    COptimizer optimizer;
    ACompanyTest  company = std::make_shared<CCompanyTest> ();
    optimizer . addCompany ( company );
    optimizer . start ( 4 );
    optimizer . stop  ();
    if ( ! company -> allProcessed () )
        throw std::logic_error ( "(some) problems were not correctly processsed" );
    return 0;
}
#endif /* __PROGTEST__ */
