#include <future>
#include "then.hpp"
#include <iostream>

int main()
{
  {
    auto f1 = std::async([]
    {
      std::cout << "task 1 on thread " << std::this_thread::get_id() << std::endl;
    });

    auto f2 = then(f1, [](std::future<void>&)
    {
      std::cout << "task 2 on thread " << std::this_thread::get_id() << std::endl;
    });

    auto f3 = then(f2, [](std::future<void>&)
    {
      std::cout << "task 3 on thread " << std::this_thread::get_id() << std::endl;
    });
    
    f3.wait();
  }

  {
    auto f1 = std::async(std::launch::async, []
    {
      std::cout << "task 1 on thread " << std::this_thread::get_id() << std::endl;
      return 1;
    });

    auto f2 = then(f1, std::launch::async, [](std::future<int>& f)
    {
      std::cout << "task 2 on thread " << std::this_thread::get_id() << " received " << f.get() << std::endl;
      return 2;
    });

    auto f3 = then(f2, std::launch::async, [](std::future<int>& f)
    {
      std::cout << "task 3 on thread " << std::this_thread::get_id() << " received " << f.get() << std::endl;
      return 3;
    });

    std::cout << "parent task received " << f3.get() << " from continuation" << std::endl;
  }

  return 0;
}

