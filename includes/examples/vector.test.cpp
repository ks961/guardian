#include <vector>
#include <iostream>
#include <Guardian.hpp>

void vector_tests()
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

    guardian.test_for<int>("Resizing", [](SK::Matcher<int>& matcher){
        std::vector<int> vec;

        matcher.eval("vector resize", [&](SK::Matcher<int>& matcher) {
            vec.resize(4);
            matcher.data(vec.capacity()).equal().to(4).verbose();
        });
    });

    guardian.test_for<int>("Clearing", [](SK::Matcher<int>& matcher){
        std::vector<int> vec;
        matcher.eval("Removing all elements from vector", [&](SK::Matcher<int>& matcher) {
            vec.push_back(1);
            vec.push_back(2);
            vec.clear();
            matcher.data(vec.size()).equal().to(0).verbose();
        });
    });

    guardian.test_for<int>("Erasing", [](SK::Matcher<int>& matcher){
        std::vector<int> vec = {1, 2, 3, 4, 5};
        vec.erase(vec.begin() + 2);

        matcher.eval("Assert size is 4", [&](SK::Matcher<int>& matcher) {
            matcher.data(vec.size()).equal().to(4).verbose();
        });
        
        matcher.eval("Assert v[0] is 1, v[1] is 2, v[2] is 4, v[3] is 5", [&](SK::Matcher<int>& matcher) {
            matcher.data(vec[0]).equal().to(1).verbose();
            matcher.data(vec[1]).equal().to(2).verbose();
            matcher.data(vec[2]).equal().to(4).verbose();
            matcher.data(vec[3]).equal().to(5).verbose();
        });
    });

    guardian.test_for<int>("Copying and Assignment", [](SK::Matcher<int>& matcher){
        std::vector<int> vec1 = {1, 2, 3};
        std::vector<int> vec2;
        vec2 = vec1;

        matcher.eval("Assert vec2 has the same size as vec1", [&](SK::Matcher<int>& matcher) {
            matcher.data(vec2.size()).equal().to(vec1.size());
        }).finished();

        matcher.eval("Assert vec2 has the same elements as vec1", [&](SK::Matcher<int>& matcher) {
            for(size_t idx = 0; idx < vec2.size(); idx++) {
                matcher.data(vec2[idx]).equal().to(vec1[idx]);
            }
        }).finished();
    });

    guardian.test_for<int>("Exception Safety", [](SK::Matcher<int>& matcher){
        std::vector<int> vec;
        matcher.eval("Throws exception", [&](SK::Matcher<int>& matcher) {
            matcher.throws([&](){
                vec.push_back(23);
                vec.resize(1);
                throw std::runtime_error("Exception thrown for vector");
            });
        }).finished();

        matcher.eval("Assert for vec is in a consistent state", [&](SK::Matcher<int>& matcher) {
            matcher.data(vec[0]).equal().to(23).verbose();
            matcher.data(vec.size()).equal().to(1).verbose();
            matcher.data(vec.capacity()).equal().to(1).verbose();
        });
    });


    guardian.test_for<std::vector<int>>("Equality and Inequality", [](SK::Matcher<std::vector<int>>& matcher){
        std::vector<int> v1 = {1, 2, 3};
        std::vector<int> v2 = {1, 2, 3};
        std::vector<int> v3 = {4, 5, 6};
        std::vector<int> v4 = {1, 2, 3};

        matcher.eval("Equality Check b/w v1 and v2", [&](SK::Matcher<std::vector<int>>& matcher) {
            matcher.data(v1).equal().to(v2);
        }).finished();

        matcher.eval("InEquality Check b/w v1 and v3", [&](SK::Matcher<std::vector<int>>& matcher) {
            matcher.data(v1).does_not().equal().to(v3);
        }).finished();

        matcher.eval("Equality chaining", [&](SK::Matcher<std::vector<int>>& matcher) {
            matcher.data(v1).equal().to(v2).equal().to(v4);
        }).finished();
    });

    guardian.test_for<int>("Iterator Validity", [](SK::Matcher<int>& matcher){
        std::vector<int> vec = {1, 2, 3};
        auto it = vec.begin();
        vec.push_back(4);

        matcher.eval("Assert *it is still valid after the push_back", [&](SK::Matcher<int>& matcher) {
            matcher.is_true((it != vec.end()));
        }).finished();
    });
}