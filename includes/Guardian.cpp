#include "Guardian.hpp"
#include <string>


template <typename T>
SK::Matcher<T>::Matcher() {}

template <typename T> 
template <typename Lambda>
SK::Matcher<T>& SK::Matcher<T>::eval(std::string info, Lambda callback)
{
    this->m_expect_info = info;

    try {        
        callback(*this);
    } catch(const std::exception& e) {
        this->m_match_state = SK::MatchState::FAILED;
    }

    return *this;
}

template <typename T>
SK::Matcher<T>& SK::Matcher<T>::to(T expected_data)
{
    try {

        switch (this->m_match_for)
        {
            case SK::MatchFor::EQUAL:
                this->m_match_state = (
                    /* Checking for equality */
                    this->m_expected_data == expected_data && !this->check_if_not() || 
                    /* Checking for 'is not' equal */
                    this->check_if_not() && !(this->m_expected_data == expected_data)
                ) ? MatchState::SUCCESS : MatchState::FAILED;

                break;
            case SK::MatchFor::LESSTHAN:
                this->m_match_state = (
                    this->m_expected_data < expected_data && !this->check_if_not() ||
                    this->check_if_not() && !(this->m_expected_data < expected_data)
                ) ? MatchState::SUCCESS : MatchState::FAILED;

                break;
            case SK::MatchFor::GREATERTHAN:
                this->m_match_state = (
                    this->m_expected_data > expected_data && !this->check_if_not() ||
                    this->check_if_not() && !(this->m_expected_data > expected_data)
                ) ? MatchState::SUCCESS : MatchState::FAILED;
                
                break;
            case SK::MatchFor::LESSTHANEQUAL:
                this->m_match_state = (
                    this->m_expected_data <= expected_data && !this->check_if_not() ||
                    this->check_if_not() && !(this->m_expected_data <= expected_data)
                ) ? MatchState::SUCCESS : 
                                                            MatchState::FAILED;
                break;
            case SK::MatchFor::GREATERTHANEQUAL:
                this->m_match_state = (
                    this->m_expected_data >= expected_data && !this->check_if_not() ||
                    this->check_if_not() && !(this->m_expected_data >= expected_data)
                ) ? MatchState::SUCCESS : MatchState::FAILED;

                break;
        }

    } catch(...) {
            this->m_match_state = MatchState::ERROR;
    }

    return *this;
}

template <typename T>
SK::Matcher<T>& SK::Matcher<T>::data(T data)
{
    this->m_expected_data = data;

    return *this;
}

template <typename T>
SK::Matcher<T>& SK::Matcher<T>::does_not()
{
    this->m_is_not = true;

    return *this;
}

template <typename T>
SK::Matcher<T>& SK::Matcher<T>::equal()
{
    this->m_match_for = SK::MatchFor::EQUAL;    

    return *this;
}

template <typename T>
template <typename Lambda>
void SK::Matcher<T>::throws(Lambda callback)
{
    try {
        callback();
        this->m_match_state = (this->check_if_not()) ? SK::MatchState::SUCCESS 
                                : SK::MatchState::FAILED;
    } catch(...) {
        /* thrown success */
        this->m_match_state = (this->check_if_not()) ? SK::MatchState::FAILED 
                                : SK::MatchState::SUCCESS;
    }
}

template <typename T>
SK::Matcher<T>& SK::Matcher<T>::less_than()
{
    this->m_match_for = SK::MatchFor::LESSTHAN;    

    return *this;
}

template <typename T>
SK::Matcher<T>& SK::Matcher<T>::greater_than()
{
    this->m_match_for = SK::MatchFor::GREATERTHAN;    

    return *this;
}

template <typename T>
SK::Matcher<T>& SK::Matcher<T>::is_true(bool data)
{
    this->m_match_state = (data) ? MatchState::SUCCESS : MatchState::FAILED;

    return *this;
}

template <typename T>
SK::Matcher<T>& SK::Matcher<T>::is_false(bool data)
{
    this->m_match_state = (!data) ? MatchState::SUCCESS : MatchState::FAILED;

    return *this;
}

template <typename T>
SK::MatchState SK::Matcher<T>::__state__()
{
    return this->m_match_state;
}

template <typename T>
bool SK::Matcher<T>::check_if_not()
{
    bool t = this->m_is_not;
    this->m_is_not = false;

    return t;
}

template <typename T>
void SK::Matcher<T>::verbose(std::string end_str)
{
    std::string log_msg;
    switch (this->m_match_state)
    {
        case SK::MatchState::SUCCESS:
            log_msg = "✅ Test Passed Successfully For: ";
            log_msg += "\"" + this->m_expect_info + "\"";
            break;
        case SK::MatchState::ERROR:
            log_msg = "❌ Error running Test For: ";
            log_msg += "\"" + this->m_expect_info + "\"";
            break;
        case SK::MatchState::FAILED:
            log_msg = "❌ Test Failed For: ";
            log_msg += "\"" + this->m_expect_info + "\"";
            break;
    }
    std::cout<<"\t"<<log_msg<<(end_str.length() > 1 ? end_str : "")<<"\n";
}

template <typename T>
void SK::Matcher<T>::finished()
{
    std::string log_msg;
    switch (this->m_match_state)
    {
        case SK::MatchState::SUCCESS:
            log_msg = "✅ Test Successfully Finished For: ";
            log_msg += "\"" + this->m_expect_info + "\"";
            break;
        case SK::MatchState::ERROR:
            log_msg = "❌ Error running Test For: ";
            log_msg += "\"" + this->m_expect_info + "\"";
            break;
        case SK::MatchState::FAILED:
            log_msg = "❌ Failed running Test For: ";
            log_msg += "\"" + this->m_expect_info + "\"";
            break;
    }
    std::cout<<"\t"<<log_msg<<"\n";
}

SK::Guardian::Guardian() {};

void SK::Guardian::log_divider(size_t length)
{
    if(this->test_ran > 1) {
        this->log("");
        for(size_t i = 0; i < length+5; i++) {
            std::cout<<"=";
        }
        this->log("\n");
    }
}

template <typename T, typename Lambda>
void SK::Guardian::test_for(std::string test_group_description, Lambda test_callback_function)
{
    this->test_ran++;
    std::string test_group_head_info = "🟡 Running tests for Group: \"";
    test_group_head_info += test_group_description + "\":-";
    
    this->log_divider(test_group_head_info.length());

    this->log(test_group_head_info);
    
    Matcher matcher = Matcher<T>();

    test_callback_function(matcher);

    std::string log_msg;
    switch (matcher.__state__())
    {
        case SK::MatchState::SUCCESS:
            log_msg = "🟢 All Tests Passed For Group: ";
            log_msg += "\"" + test_group_description + "\"";
            this->log(log_msg);
            this->success = true;
            break;
        case SK::MatchState::ERROR:
            log_msg = "🔴 Error running Tests For Group: ";
            log_msg += "\"" + test_group_description + "\"";
            this->log(log_msg);
            this->success = false;
            break;
        case SK::MatchState::FAILED:
            log_msg = "🔴 Failed running Tests For Group: ";
            log_msg += "\"" + test_group_description + "\"";
            this->log(log_msg);
            this->success = false;
            break;
    }
}


void SK::Guardian::log(std::string log)
{
    std::cout<<log<<"\n";
}

bool SK::Guardian::test_success()
{
    return this-success;
}

SK::Guardian::~Guardian() {};