# then
Experimental implementation of future::then()

# C++11 implementation

  template<class T, class Function>
  std::future<typename std::result_of<Function(std::future<T>&)>::type>
    then(std::future<T>& fut, std::launch policy, Function&& f)
  {
    return std::async(policy, [](std::future<T>&& fut, Function&& f)
    {
      fut.wait();
      return std::forward<Function>(f)(fut);
    },
    std::move(fut),
    std::forward<Function>(f)
    );
  }
  
  template<class T, class Function>
  std::future<typename std::result_of<Function(std::future<T>&)>::type>
    then(std::future<T>& fut, Function&& f)
  {
    return then(fut, std::launch::async | std::launch::deferred, std::forward<Function>(f));
  }

