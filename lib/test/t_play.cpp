
#include <gtest/gtest.h>
#include "play.h"
#include "question.h"
#include "factories.h"

class MySumFactory : public QuestionFactory
{
public:
    MySumFactory(): QuestionFactory()
    {
    }

    ~MySumFactory()
    {
    }

    std::shared_ptr<Question> createQuestion() override
    {
        return std::shared_ptr<Question>(new SumQuestion({4,4}, 5) ); // must be 20
    }
};


TEST(Play, GetQuestions)
{
    auto p = new Play(3, std::shared_ptr<QuestionFactory>(new MySumFactory()));

    {
        auto[right, wrong, answered, unanswered, successrate] = p->getStat();

        ASSERT_EQ(unanswered, 0);
        ASSERT_EQ(answered, 0);
        ASSERT_EQ(right, 0);
        ASSERT_EQ(wrong, 0);
        ASSERT_NEAR(successrate, 0.0, 0.0001);
    }

    std::shared_ptr<Question> q1 = p->nextQuestion();
    std::shared_ptr<Question> q2 = p->nextQuestion();
    std::shared_ptr<Question> q3 = p->nextQuestion();
    std::shared_ptr<Question> q4 = p->nextQuestion();

    ASSERT_FALSE(q1.get()==nullptr);
    ASSERT_FALSE(q2.get()==nullptr);
    ASSERT_FALSE(q3.get()==nullptr);
    ASSERT_TRUE(q4.get()==nullptr); // 4th is nullptr

    {
        auto[right, wrong, answered, unanswered, successrate] = p->getStat();

        ASSERT_EQ(unanswered, 3);
        ASSERT_EQ(answered, 0);
        ASSERT_EQ(right, 0);
        ASSERT_EQ(wrong, 3);
        ASSERT_NEAR(successrate, 0.0, 0.0001);
    }


    delete p;
}

TEST(Play, AnswerQuestions)
{
    auto p = new Play(3, std::shared_ptr<QuestionFactory>(new MySumFactory()));

    std::shared_ptr<Question> q1 = p->nextQuestion();
    std::shared_ptr<Question> q2 = p->nextQuestion();
    q1->parseAnswer("20");
    q2->parseAnswer("15");

    {
        auto[right, wrong, answered, unanswered, successrate] = p->getStat();

        ASSERT_EQ(unanswered, 0);
        ASSERT_EQ(answered, 2);
        ASSERT_EQ(right, 1);
        ASSERT_EQ(wrong, 1);
        ASSERT_NEAR(successrate, 0.5, 0.0001);
    }

    // get 3rd question but dont answer yet
    std::shared_ptr<Question> q3 = p->nextQuestion();

    {
        auto[right, wrong, answered, unanswered, successrate] = p->getStat();

        ASSERT_EQ(unanswered, 1);
        ASSERT_EQ(answered, 2);
        ASSERT_EQ(right, 1);
        ASSERT_EQ(wrong, 2);
        ASSERT_NEAR(successrate, 0.5, 0.0001);
    }

    q3->parseAnswer("20");

    {
        auto[right, wrong, answered, unanswered, successrate] = p->getStat();

        ASSERT_EQ(unanswered, 0);
        ASSERT_EQ(answered, 3);
        ASSERT_EQ(right, 2);
        ASSERT_EQ(wrong, 1);
        ASSERT_NEAR(successrate, 0.666666, 0.0001);
    }

    delete p;
}

TEST(Play, GetTotalNbrQuestions)
{
    auto p = new Play(3, std::shared_ptr<QuestionFactory>(new MySumFactory()));
    ASSERT_EQ(p->getNumberOfQuestions(), 3);
    delete p;
}

TEST(Play, OverwriteNbrOfQuestionByFactory)
{
    auto p = new Play(3, std::shared_ptr<QuestionFactory>(new CSVFactory("lib/test/test.csv"))); // has only 2 questions
    ASSERT_EQ(p->getNumberOfQuestions(), 2);
    delete p;
}
