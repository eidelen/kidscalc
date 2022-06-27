
#include <gtest/gtest.h>
#include "question.h"


class MyQuestion: public Question
{
public:
    MyQuestion(): Question()
    {

    }

    ~MyQuestion()
    {

    }

    // Question interface
    std::string toString() const override
    {
        return "1200 + 34";
    }

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
