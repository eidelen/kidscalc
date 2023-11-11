
#include <algorithm>
#include <gtest/gtest.h>
#include "question.h"
#include "factories.h"


TEST(Question, BaseImpl)
{
    Question* q = new Question("How are you?", "Good");

    ASSERT_FALSE(q->isAnswered());
    ASSERT_FALSE(q->isCorrect());
    ASSERT_STRCASEEQ(q->getQuestion().c_str(), "How are you?");
    ASSERT_STRCASEEQ(q->getRightAnswer().c_str(), "Good");

    q->parseAnswer("Bad");

    ASSERT_TRUE(q->isAnswered());
    ASSERT_FALSE(q->isCorrect());

    q->parseAnswer("Good");

    ASSERT_TRUE(q->isAnswered());
    ASSERT_TRUE(q->isCorrect());

    delete q;
}

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

    int getRndInt(std::pair<int, int> range)
    {
        return getRandomIntegerInRange(range);
    }

    int m_theAnswer;
};

TEST(Question, BasicInterface)
{
    Question* q = new MyQuestion();

    ASSERT_FALSE(q->isAnswered());
    ASSERT_FALSE(q->isCorrect());
    ASSERT_STRCASEEQ(q->getQuestion().c_str(), "1200 + 34");
    ASSERT_STRCASEEQ(q->getRightAnswer().c_str(), "1234");

    q->parseAnswer("9999");

    ASSERT_TRUE(q->isAnswered());
    ASSERT_FALSE(q->isCorrect());

    q->parseAnswer("1234");

    ASSERT_TRUE(q->isAnswered());
    ASSERT_TRUE(q->isCorrect());

    delete q;
}

TEST(Question, RandomInt)
{
    MyQuestion* q = new MyQuestion();

    // test that all numbers in range are at least once generated, when trying enough hard.
    // self evident, this test might fail in rare cases :)

    std::vector<bool> res(10, false);

    for(size_t i = 0; i < 100; i++)
        res.at(q->getRndInt({0, 9})) = true;

    ASSERT_TRUE(std::all_of(res.begin(), res.end(), [](bool v) { return v; }));

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
    ASSERT_STRCASEEQ(q->getQuestion().c_str(), "1200 + 34");

    q->parseAnswer("9999");

    ASSERT_TRUE(q->isAnswered());
    ASSERT_FALSE(q->isCorrect());

    q->parseAnswer("1234");

    ASSERT_TRUE(q->isAnswered());
    ASSERT_TRUE(q->isCorrect());

    delete f;
}

/*****************************************************************/

class MyNumQuest : public NumericQuestion
{
public:
    MyNumQuest() : NumericQuestion(){}
    virtual ~MyNumQuest(){}
    std::string getParsedResult(){return m_givenResultAsString;}
};

TEST(NumericQuestion, Parse)
{
    auto n1 = new MyNumQuest();
    n1->parseAnswer("5");
    ASSERT_STRCASEEQ(n1->getParsedResult().c_str(), "5");
    n1->parseAnswer("555522");
    ASSERT_STRCASEEQ(n1->getParsedResult().c_str(), "555522");
    n1->parseAnswer("-34");
    ASSERT_STRCASEEQ(n1->getParsedResult().c_str(), "-34");
    n1->parseAnswer("-  34");
    ASSERT_STRCASEEQ(n1->getParsedResult().c_str(), "-34");
    n1->parseAnswer("+7");
    ASSERT_STRCASEEQ(n1->getParsedResult().c_str(), "7");
    delete n1;
}

/*******************************************/

TEST(SumQuestion, BasicUsage)
{
    auto s1 = new SumQuestion({5, 5}, 3); // must be 15

    ASSERT_FALSE(s1->isCorrect());
    ASSERT_FALSE(s1->isAnswered());

    ASSERT_STRCASEEQ(s1->getQuestion().c_str(), "5 + 5 + 5");

    s1->parseAnswer("15");

    ASSERT_TRUE(s1->isAnswered());
    ASSERT_TRUE(s1->isCorrect());

    ASSERT_STRCASEEQ(s1->getRightAnswer().c_str(), "15");

    delete s1;
}

TEST(SumQuestion, InputForms)
{
    auto s1 = new SumQuestion({5, 5}, 3); // must be 15

    s1->parseAnswer("   15");
    ASSERT_TRUE(s1->isCorrect());

    s1->parseAnswer("15    ");
    ASSERT_TRUE(s1->isCorrect());

    s1->parseAnswer("15 \n  ");
    ASSERT_TRUE(s1->isCorrect());

    delete s1;
}


TEST(SumQuestion, Negative)
{
    auto s1 = new SumQuestion({-5, -5}, 3); // must be -15

    std::cout << "res" << s1->getRightAnswer() << std::endl;

    s1->parseAnswer("   -15");
    ASSERT_TRUE(s1->isCorrect());

    s1->parseAnswer("-15    ");
    ASSERT_TRUE(s1->isCorrect());

    s1->parseAnswer("-15 \n  ");
    ASSERT_TRUE(s1->isCorrect());

    delete s1;
}

TEST(SumQuestion, Heavy)
{
    for(size_t i = 2; i < 100; i++ )
    {
        auto s = new SumQuestion({0, 100}, i);

        std::string qstr = s->getQuestion();

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

    ASSERT_STRCASEEQ(s1->getQuestion().c_str(), "5 - 5 - 5");

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

        std::string qstr = s->getQuestion();

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

        std::string qstr = s->getQuestion();

        ASSERT_EQ(2, std::count(qstr.begin(), qstr.end(), '-'));

        delete s;
    }
}

/*****************************************************************/

TEST(MulQuestion, BasicUsage)
{
    auto s1 = new MultiplyQuestion({5, 5}, 2); // must be 25

    ASSERT_FALSE(s1->isCorrect());
    ASSERT_FALSE(s1->isAnswered());

    ASSERT_STRCASEEQ(s1->getQuestion().c_str(), "5 * 5");

    s1->parseAnswer("25");

    ASSERT_TRUE(s1->isAnswered());
    ASSERT_TRUE(s1->isCorrect());

    ASSERT_STRCASEEQ(s1->getRightAnswer().c_str(), "25");

    delete s1;
}

TEST(MulQuestion, InputForms)
{
    auto s1 = new MultiplyQuestion({5, 5}, 2); // must be 25

    s1->parseAnswer("   25");
    ASSERT_TRUE(s1->isCorrect());

    s1->parseAnswer("25    ");
    ASSERT_TRUE(s1->isCorrect());

    s1->parseAnswer("25 \n  ");
    ASSERT_TRUE(s1->isCorrect());

    delete s1;
}

TEST(MulQuestion, Heavy)
{
    for(size_t i = 2; i < 100; i++ )
    {
        auto s = new MultiplyQuestion({0, 100}, i);

        std::string qstr = s->getQuestion();

        ASSERT_EQ(i-1, std::count(qstr.begin(), qstr.end(), '*'));

        delete s;
    }
}

/*****************************************************************/

TEST(DivIntQuestion, BasicUsage)
{
    auto s1 = new DivisionQuestionInt({5, 5}); // the only integer division of prime 5 is 1 or 5

    ASSERT_FALSE(s1->isCorrect());
    ASSERT_FALSE(s1->isAnswered());

    std::string q = s1->getQuestion();
    ASSERT_TRUE( q.compare("5 / 5")==0 || q.compare("5 / 1")==0);

    if( q.compare("5 / 5")==0 )
    {
        s1->parseAnswer("1");

        ASSERT_TRUE(s1->isAnswered());
        ASSERT_TRUE(s1->isCorrect());
    }

    if( q.compare("5 / 1")==0 )
    {
        s1->parseAnswer("5");

        ASSERT_TRUE(s1->isAnswered());
        ASSERT_TRUE(s1->isCorrect());
    }

    delete s1;
}
