
#include <gtest/gtest.h>
#include "task.h"


TEST(Task, Ctor)
{
    Task* t = new Task(58);
    ASSERT_EQ(t->id(), 58);
    delete t;
}
