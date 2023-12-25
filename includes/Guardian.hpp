/*
MIT License

Copyright (c) 2023 ks961

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

1. Proper attribution to the original author's GitHub account must be provided in a professional manner.
This attribution should prominently display the GitHub account username associated with the original work.

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once
#include <iostream>

namespace SK { 

    enum MatchState {
        ERROR,
        FAILED,
        SUCCESS,
    };

    enum MatchFor {
        EQUAL,
        LESSTHAN,
        GREATERTHAN,
        LESSTHANEQUAL,
        GREATERTHANEQUAL,
    };

    /**
     * @brief                           Matcher Class for data matching.
     * @tparam T:                       Data type for Matching data.
    */
    template <typename T>
    class Matcher {
        public:
            Matcher();

            /**
             * @brief               run function is small segmenet to run unit test.
             * @tparam Lambda:      Anonymous Callback Function for compile-time Type inference. [ Don't pass anything ]
             * @param std::string:  Unit Test description.
             * @param Lambda:       Callback function to add your test ->
             * [&](SK::Matcher<data_type>& matcher){
             * }.
             * @return  Matcher<T>&
            */
            template <typename Lambda>
            Matcher<T>& eval(std::string, Lambda);

            /**
             * @brief       To pass the the data that could be used to match.
             * @param T:    Data type of data to be passed.
             * @return  Matcher<T>&
            */
            Matcher<T>& data(T);

            /**
             * @brief       Data to be matched.
             * @param T:    Data type of data to be passed.
             * @return  Matcher<T>&
            */
            Matcher<T>& to(T);
            
            /**
             * @brief   Data equality check.
             * @return  Matcher<T>&
            */
            Matcher<T>& equal();
            
            /**
             * @brief   Conditionals or result inverted checks.
             * @return  Matcher<T>&
            */
            Matcher<T>& does_not();

            /**
             * @brief   Check if value expected value is less.
             * @return  Matcher<T>&
            */
            Matcher<T>& less_than();

            /**
             * @brief   Check if value expected value is greater.
             * @return  Matcher<T>&
            */
            Matcher<T>& greater_than();


            /**
             * @brief   Check if value expected value is true.
             * @return  Matcher<T>&
            */
            Matcher<T>& is_true(bool data);

            /**
             * @brief   Check if value expected value is false.
             * @return  Matcher<T>&
            */
            Matcher<T>& is_false(bool data);

            /**
             * @brief               Check if function throws exception.
             * @tparam Lambda:      Auto type inference lambda callback function [ Don't pass anything ].
             * @param Lambda:       Callback function to test if throws -> [&](){ }
            */
            template <typename Lambda>
            void throws(Lambda callback);

            /**
             * @brief   Logs if eval segment | block Test state.
            */
            void finished();

            /**
             * @brief   Logs Test result state.
            */
            void verbose(std::string="");

            /**
             * @brief   returns current MatchState.
             * @return  MatchState
            */
            MatchState __state__();

        private:
            T m_expected_data;
            MatchFor m_match_for;
            bool m_is_not { false };
            std::string m_expect_info;
            MatchState m_match_state { MatchState::SUCCESS };

            /**
             * @brief   Checks if 'this->is_not' is true or false.
             * @return  bool
            */
            bool check_if_not();
    };

    class Guardian {
        public:
            Guardian();

            /**
             * @brief                           Create a group of Tests.
             * @tparam T:                       Data type for Matching data.
             * @tparam Lambda:                  Anonymous Function for Type inference. [ Don't pass anything ]
             * @param test_description:         Test description.
             * @param test_callback_function:   Callback function to add your expectation for test.
            */
            template <typename T, typename Lambda>
            void test_for(std::string, Lambda);

            /**
             * @brief       Log Test description and info.
             * @param log:  Log data.
            */
            void log(std::string log);

            void log_divider(size_t length);

            bool test_success();

            ~Guardian();
        private:
            bool success { false };
            size_t test_ran { 0 };
    };

    #include "Guardian.cpp"
}