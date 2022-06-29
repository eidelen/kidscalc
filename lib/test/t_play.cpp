
#include <gtest/gtest.h>
#include "play.h"
#include "question.h"

class SumFactory : public QuestionFactory
{
public:
    SumFactory(): QuestionFactory()
    {
    }

    ~SumFactory()
    {
    }

    std::shared_ptr<Question> createQuestion() override
    {
        return std::shared_ptr<Question>(new SumQuestion({4,4}, 5) ); // must be 20
    }
};


TEST(Play, GetQuestions)
{
    auto p = new Play(3, std::shared_ptr<QuestionFactory>(new SumFactory()));

    ASSERT_EQ(p->nbrOfQuestions(), 3);
    ASSERT_EQ(p->nbrOfQuestionsAlreadyAsked(), 0);

    std::shared_ptr<Question> q1 = p->nextQuestion();
    std::shared_ptr<Question> q2 = p->nextQuestion();
    std::shared_ptr<Question> q3 = p->nextQuestion();
    std::shared_ptr<Question> q4 = p->nextQuestion();

    ASSERT_FALSE(q1.get()==nullptr);
    ASSERT_FALSE(q2.get()==nullptr);
    ASSERT_FALSE(q3.get()==nullptr);
    ASSERT_TRUE(q4.get()==nullptr);

    delete p;
}
