
#include <gtest/gtest.h>
#include "factories.h"

TEST(CSVFactory, ReadFile)
{
    std::shared_ptr<CSVFactory> f = std::shared_ptr<CSVFactory>(new CSVFactory("lib/test/test.csv"));
    ASSERT_EQ(f->m_questions.size(), 2);
}

TEST(CSVFactory, Functionality)
{
    std::shared_ptr<CSVFactory> f = std::shared_ptr<CSVFactory>(new CSVFactory("lib/test/test.csv"));

    ASSERT_TRUE(f->getTotalNumberOfQuestions().first);
    ASSERT_EQ(f->getTotalNumberOfQuestions().second, 2);

    auto q1 = f->createQuestion();
    ASSERT_EQ(q1->getQuestion(), "q1");
    ASSERT_EQ(q1->getRightAnswer(), "a1");
    ASSERT_FALSE(q1->isAnswered());
    q1->parseAnswer("a1");
    ASSERT_TRUE(q1->isAnswered());
    ASSERT_TRUE(q1->isCorrect());

    auto q2 = f->createQuestion();
    ASSERT_EQ(q2->getQuestion(), "q2");
    ASSERT_EQ(q2->getRightAnswer(), "a2");

    auto q3 = f->createQuestion();
    ASSERT_EQ(q3.get(), nullptr);
}
