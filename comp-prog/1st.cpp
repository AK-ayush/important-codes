#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char const *argv[]) {
  vector<int> vector1;
  vector<int> vector2;

  vector1.push_back(10);
  vector1.push_back(20);

  vector2.push_back(100);
  vector2.push_back(200);


  vector<vector<int>>vector_2d;
  vector_2d.push_back(vector1);
  vector_2d.push_back(vector2);

  cout<<vector_2d[1][0]<<endl;
  vector1.at(0)=1000;

  cout<<vector_2d[1].at(0)<<endl;
  cout<<vector1.at(0)<<endl;  //.at() method does the bounds checking

  enum Direction{
    left, right, up, down
  };
  Direction heading {left};

  switch (/* expression */) {
    case /* value */:
  }

  //Range based for-loop
  int scores [] {100, 90, 97};
  for (auto score : scores) {
    cout<<score<<endl;
  }
  return 0;
}


// g++ -Wall --std=c++14 1st.cpp  -o 1st

/*

import cudf
import numpy as np
import cupy
from numba import cuda

x_cpu = np.random.randint(1000, size=(10, 2), dtype=np.int32)
x_gpu = cuda.to_device(x_cpu)
df = cudf.DataFrame.from_gpu_matrix(x_gpu)
df

*/
