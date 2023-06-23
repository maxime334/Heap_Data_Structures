#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#pragma once

namespace com {
inline int pow(int x, int e) {
  int r;
  if (e == 0)
    return 1;
  if (e % 2 == 0) {
    r = pow(x, e / 2);
    return r * r;
  } else
    return x * pow(x, e - 1);
}
} // namespace com
