#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>
#include <mutex>

template <typename T> class Singleton {
public:
  // Delete any copy constructor and assignment operator
  Singleton(const Singleton &) = delete;
  Singleton &operator=(const Singleton &) = delete;

  // Get the instance of the Singleton
  static T &getInstance() {
    std::call_once(flag, []() { instance.reset(new T()); });
    return *instance;
  }

protected:
  // protected constructor to prevent externatl instantiation
  Singleton() = default;

  // protected destructor to prevent deletion through base class
  virtual ~Singleton() = default;

private:
  // static insatnce of the Singleton
  static std::unique_ptr<T> instance;

  // flag to ensure thread safety during initalization
  static std::once_flag flag;
};

// Initialize static members
template <typename T> std::unique_ptr<T> Singleton<T>::instance = nullptr;

template <typename T> std::once_flag Singleton<T>::flag;

#endif
