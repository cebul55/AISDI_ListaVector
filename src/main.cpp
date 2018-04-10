#include <cstddef>
#include <cstdlib>
#include <string>
#include <chrono>

#include "Vector.h"
#include "LinkedList.h"

namespace
{

template <typename T>
using LinearCollection = aisdi::LinkedList<T>;

template<typename T>
using VectorCollection = aisdi::Vector<T>;

void perfomAppendTest(LinearCollection <int> l , VectorCollection <int> v)
{
  auto start = std::chrono::system_clock::now();
  for(int i = 0 ; i < 100000 ; i++)
    l.append(i);
  auto end = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsedSecondsL = end - start;
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);

  std::cout << "finished appending to list at "<< std::ctime(&end_time)
            << "elapsed time: "<<elapsedSecondsL.count() <<"s\n";

  start = std::chrono::system_clock::now();
  for(int i = 0 ; i < 100000 ; i++)
    v.append(i);
  end = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsedSecondsV = end - start;
  std::time_t end_timeV = std::chrono::system_clock::to_time_t(end);

  std::cout << "finished appending to vector at "<< std::ctime(&end_timeV)
            << "elapsed time: "<<elapsedSecondsV.count() <<"s\n";

}
void eraseTest(LinearCollection <int> l, VectorCollection <int> v)
{
  auto start = std::chrono::system_clock::now();
  l.erase(l.begin(), l.end());
  auto end = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsedSeconds = end - start;
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);

  std::cout << "finished erasing list at "<< std::ctime(&end_time)
            << "elapsed time: "<<elapsedSeconds.count() <<"s\n";

  start = std::chrono::system_clock::now();
  v.erase(v.begin(), v.end());
  end = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsedSecondsV = end - start;
  std::time_t end_timeV = std::chrono::system_clock::to_time_t(end);

  std::cout << "finished erasing vector at "<< std::ctime(&end_timeV)
            << "elapsed time: "<<elapsedSecondsV.count() <<"s\n";
}

void prependTest(LinearCollection <int> l, VectorCollection <int> v)
{
  auto start = std::chrono::system_clock::now();
  for(int i = 0 ; i < 100000 ; i++)
    l.prepend(i);
  auto end = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsedSecondsL = end - start;
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);

  std::cout << "finished prepending to list at "<< std::ctime(&end_time)
            << "elapsed time: "<<elapsedSecondsL.count() <<"s\n";

  start = std::chrono::system_clock::now();
  for(int i = 0 ; i < 10000 ; i++)
    v.prepend(i);
  end = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsedSecondsV = end - start;
  std::time_t end_timeV = std::chrono::system_clock::to_time_t(end);

  std::cout << "finished prepending to vector at "<< std::ctime(&end_timeV)
            << "elapsed time: "<<elapsedSecondsV.count() <<"s\n";
}
} // namespace

/*int main(int argc, char** argv)
{
  const std::size_t repeatCount = argc > 1 ? std::atoll(argv[1]) : 10000;
  for (std::size_t i = 0; i < repeatCount; ++i)
    perfomTest();
  return 0;
}*/
int main()
{
  LinearCollection <int> l;
  VectorCollection <int> v;
  perfomAppendTest(l ,v);
  eraseTest(l , v);
  prependTest(l , v);
  eraseTest(l , v);


/*  LinearCollection<int>::iterator i = j.begin();
  for(int a = 0 ; a < 2 ; a++)
  {
    std::cout<<"HM "<<*i<<std::endl;
    ++i;
  }*/
  return 0;
}

