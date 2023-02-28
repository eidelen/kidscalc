
#include <gtest/gtest.h>
#include "factories.h"

TEST(CSVFactory, ReadFile)
{
    std::shared_ptr<CSVFactory> f = std::shared_ptr<CSVFactory>(new CSVFactory("lib/test/test.csv"));

    ASSERT_EQ(f->m_questions.size(), 2);
}
