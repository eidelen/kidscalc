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

#include <argparse/argparse.hpp>

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
        return std::shared_ptr<Question>(new SumQuestion({0, 10}, 2) );
    }
};

class SubFactory : public QuestionFactory
{
public:
    SubFactory(): QuestionFactory()
    {
    }

    ~SubFactory()
    {
    }

    std::shared_ptr<Question> createQuestion() override
    {
        return std::shared_ptr<Question>(new SubQuestion({0, 10}, 2, false) );
    }
};


/**
 * KidsCalc Main App
 */
int main(int argc, char *argv[])
{
    std::cout << "KidsCalc Application, Sohyi & Adrian Schneider" << std::endl << std::endl;

    bool goToPlay = true;

    while(goToPlay)
    {
        std::shared_ptr<Play> p = std::shared_ptr<Play>(new Play(5, std::shared_ptr<SubFactory>(new SubFactory())));

        std::shared_ptr<Question> q = p->nextQuestion();
        while(q.get() != nullptr)
        {
            std::cout << " " << q->toString() << " = ";

            std::string answer = "";
            std::cin >> answer;

            q->parseAnswer(answer);

            if( q->isCorrect() )
            {
                std::cout << " 😍" << std::endl << std::endl;
            }
            else
            {
                std::cout << " 🤨 " << "The correct answer is " << q->getRightAnswer() << std::endl << std::endl;
            }

            q = p->nextQuestion();
        }

        auto[right, wrong, answered, unanswered, successRate] = p->getStat();

        std::cout << "You got " << right << " right and " << wrong << " wrong." << std::endl;

        if(successRate > 0.9999)
        {
            std::cout << " 🏆🏆🏆🏆🏆🏆🏆🏆" << std::endl;
        }
        else if(successRate > 0.7999)
        {
            std::cout << " 🥰🥰🥰" << std::endl;
        }
        else if(successRate > 0.4999)
        {
            std::cout << " 👌👌" << std::endl;
        }
        else if(successRate > 0.1999)
        {
            std::cout << " 🐈" << std::endl;
        }
        else
        {
            std::cout << " 🙈" << std::endl;
        }

        std::cout << std::endl << "Press \"s\" to start again. Press \"x\" to quit: " << std::endl;
        std::string ctrInput = "";
        std::cin >> ctrInput;

        if(ctrInput == "x")
            goToPlay = false;

        std::cout << std::endl << std::endl;
    }

    return 0;
}
