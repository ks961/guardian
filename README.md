# guardian

## Overview

**Guardian** A c++ testing library.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)

## Installation

1. Copy all the files from includes to your local includes directory or wherever you prefer.

## Usage
**All Classes, Functions Variables are declared under 'SK' namespace.**
```cpp
#include <vector>
#include <Guardian.hpp>

int main()
{
    SK::Guardian guardian;

    guardian.test_for<int>("Insertion and Access", [](SK::Matcher<int>& matcher) {
        std::vector<int> vec;
        vec.push_back(10);
        vec.push_back(20);
        vec.push_back(30);
        
        matcher.eval("Assert that size is 3", [&](SK::Matcher<int>& matcher){
            matcher.data(vec.size()).equal().to(3);
        }).finished();

        matcher.eval("Assert v[0] is 10, v[1] is 20, and v[2] is 30", [&](SK::Matcher<int>& matcher){
            matcher.data(vec[0]).equal().to(10).verbose();
            matcher.data(vec[1]).equal().to(20).verbose();
            matcher.data(vec[2]).equal().to(30).verbose();
        });

        matcher.eval("iterators to traverse and check values", [&](SK::Matcher<int>& matcher){
            for(const auto& value : vec) {
                matcher.data(value).greater_than().to(0).verbose();
            }
        });
    });

    return 0;
}
```

Now compile and run.