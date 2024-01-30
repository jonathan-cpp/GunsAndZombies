#pragma once

//////////////////////////////////////////////////////////
// Standard Library Headers
//////////////////////////////////////////////////////////

#include <stdio.h>
#include <memory>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <stack>

//////////////////////////////////////////////////////////
// Thirdparty Headers
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Project Headers
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

template<typename T>
using UniquePtr = std::unique_ptr<T>; 

template<typename T>
using SharedPtr = std::shared_ptr<T>; 

template<typename T>
using WeakPtr = std::weak_ptr<T>; 

using uint8 = unsigned char;

#define log(x) std::cout << x
#define logl(x) std::cout << x << std::endl
