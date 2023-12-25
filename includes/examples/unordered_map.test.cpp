#include <iostream>
#include <Guardian.hpp>
#include <unordered_map>

bool unordered_map_test()
{
        SK::Guardian guardian;

        guardian.test_for<int>("Hashtable mapping from int ➡️  int", [](auto& matcher) {
            std::unordered_map<int, int> map;

            size_t max_element = 1000;

            matcher.eval("Insert function.", [&](auto& matcher) {
                for(size_t idx = 0; idx < max_element; idx++) {
                    map.insert(std::pair<int, int>(idx, idx+1));
                }
            }).finished(); /* To Test if a block or function is finished without any error at the end */


            matcher.eval("Get function", [&](SK::Matcher<int>& matcher) {
                for(size_t idx = 0; idx < max_element; idx++) {
                    auto data = map[idx];

                    /* versbose logging for each test ran in loop */
                    matcher.data(idx).less_than().to(data).verbose();
                }
            });

            /* Test boolean based output */
            matcher.eval("Remove function", [&](auto& matcher) {
                for(size_t idx = 0; idx < max_element; idx++) {
                    auto data = map.erase(idx);

                    matcher.is_true(data);
                }
            }).finished();
    });

    /* Test if function or block throws errors as excepted */
    guardian.test_for<int>("Test for runtime error checks", [&](SK::Matcher<int>& matcher) {
        matcher.eval("Throws error", [&](SK::Matcher<int>& matcher) {
            matcher.throws([&]() {
                throw std::runtime_error("Throws error");
            });
        }).finished();
    });

    /* Inverted Test cases */
    guardian.test_for<int>("Test for no runtime error checks", [&](SK::Matcher<int>& matcher) {
 
        matcher.eval("Doesn't Throws error", [&](SK::Matcher<int>& matcher) { 
            matcher.does_not().throws([&]() {
            });

        }).finished();
    });

    return guardian.test_success();
}