/****************************************************************************
** Copyright (c) 2021 Adrian Schneider
**
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and associated documentation files (the "Software"),
** to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and/or sell copies of the Software, and to permit persons to whom the
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
** FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
** DEALINGS IN THE SOFTWARE.
**
*****************************************************************************/

#include <iostream>

#include "play.h"
#include "question.h"


// only for fast testing
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
        return std::shared_ptr<Question>(new SumQuestion({0,10}, 2) ); // must be 20
    }
};



/**
 * KidsCalc Main App
 */
int main(int argc, char *argv[])
{
    std::cout << "KidsCalc Application, Adrian Schneider" << std::endl;

    std::shared_ptr<Play> p = std::shared_ptr<Play>(new Play(5, std::shared_ptr<SumFactory>(new SumFactory())));

    std::shared_ptr<Question> q = p->nextQuestion();
    while(q.get() != nullptr)
    {
        std::cout << q->toString() << std::endl;

        std::string answer = "";
        std::cin >> answer;

        q->parseAnswer(answer);

        q = p->nextQuestion();
    }

    return 0;
}
