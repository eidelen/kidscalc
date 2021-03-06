
#include <algorithm>
#include <gtest/gtest.h>
#include "question.h"


class MyQuestion: public Question
{
public:
    MyQuestion(): Question()
    {
        m_questionAsString = "1200 + 34";
        m_trueResultAsString = "1234";
    }

    ~MyQuestion()
    {

    }

    // Question interface

    void parseAnswer(const std::string & answer) override
    {
        m_answered = true;
        m_theAnswer = std::stoi(answer) ;
    }

    bool isCorrect() const override
    {
        return m_answered && m_theAnswer == (1200 + 34);
    }

    int m_theAnswer;
};

TEST(Question, BasicInterface)
{
    Question* q = new MyQuestion();

    ASSERT_FALSE(q->isAnswered());
    ASSERT_FALSE(q->isCorrect());
    ASSERT_STRCASEEQ(q->toString().c_str(), "1200 + 34");
    ASSERT_STRCASEEQ(q->getRightAnswer().c_str(), "1234");

    q->parseAnswer("9999");

    ASSERT_TRUE(q->isAnswered());
    ASSERT_FALSE(q->isCorrect());

    q->parseAnswer("1234");

    ASSERT_TRUE(q->isAnswered());
    ASSERT_TRUE(q->isCorrect());

    delete q;
}


class MyFactory : public QuestionFactory
{
public:
    MyFactory(): QuestionFactory()
    {

    }

    ~MyFactory()
    {

    }

    std::shared_ptr<Question> createQuestion() override
    {
        return std::shared_ptr<MyQuestion>(new MyQuestion);
    }
};


TEST(QuestionFactory, BasicInterface)
{
    auto f = new MyFactory();

    auto q = f->createQuestion();

    ASSERT_FALSE(q->isAnswered());
    ASSERT_FALSE(q->isCorrect());
    ASSERT_STRCASEEQ(q->toString().c_str(), "1200 + 34");

    q->parseAnswer("9999");

    ASSERT_TRUE(q->isAnswered());
    ASSERT_FALSE(q->isCorrect());

    q->parseAnswer("1234");

    ASSERT_TRUE(q->isAnswered());
    ASSERT_TRUE(q->isCorrect());

    delete f;
}

/*****************************************************************/

TEST(SumQuestion, BasicUsage)
{
    auto s1 = new SumQuestion({5, 5}, 3); // must be 15

    ASSERT_FALSE(s1->isCorrect());
    ASSERT_FALSE(s1->isAnswered());

    ASSERT_STRCASEEQ(s1->toString().c_str(), "5 + 5 + 5");

    s1->parseAnswer("15");

    ASSERT_TRUE(s1->isAnswered());
    ASSERT_TRUE(s1->isCorrect());

    ASSERT_STRCASEEQ(s1->getRightAnswer().c_str(), "15");

    delete s1;
}

TEST(SumQuestion, Heavy)
{
    for(size_t i = 2; i < 100; i++ )
    {
        auto s = new SumQuestion({0, 100}, i);

        std::string qstr = s->toString();

        ASSERT_EQ(i-1, std::count(qstr.begin(), qstr.end(), '+'));

        delete s;
    }
}

/*****************************************************************/

TEST(SubQuestion, BasicUsage)
{
    auto s1 = new SubQuestion({5, 5}, 3, true); // must be -5

    ASSERT_FALSE(s1->isCorrect());
    ASSERT_FALSE(s1->isAnswered());

    ASSERT_STRCASEEQ(s1->toString().c_str(), "5 - 5 - 5");

    s1->parseAnswer("-6");

    ASSERT_TRUE(s1->isAnswered());
    ASSERT_FALSE(s1->isCorrect());

    s1->parseAnswer("-5");

    ASSERT_TRUE(s1->isAnswered());
    ASSERT_TRUE(s1->isCorrect());

    ASSERT_STRCASEEQ(s1->getRightAnswer().c_str(), "-5");

    delete s1;
}

TEST(SubQuestion, HeavyPos)
{
    for(size_t i = 2; i < 100; i++ )
    {
        auto s = new SubQuestion({0, 100}, 3, false);

        std::string qstr = s->toString();

        ASSERT_EQ(2, std::count(qstr.begin(), qstr.end(), '-'));

        ASSERT_GE(std::stoi(s->getRightAnswer()), 0);

        delete s;
    }
}

TEST(SubQuestion, HeavyNeg)
{
    for(size_t i = 2; i < 100; i++ )
    {
        auto s = new SubQuestion({0, 100}, 3, true);

        std::string qstr = s->toString();

        ASSERT_EQ(2, std::count(qstr.begin(), qstr.end(), '-'));

        delete s;
    }
}
