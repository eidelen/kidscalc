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
    SumFactory(std::pair<int,int> numberRange, size_t length): QuestionFactory()
    {
        m_numberRange = numberRange;
        m_length = length;
    }

    ~SumFactory()
    {
    }

    std::shared_ptr<Question> createQuestion() override
    {
        return std::shared_ptr<Question>(new SumQuestion(m_numberRange, m_length) );
    }

    std::pair<int,int> m_numberRange;
    size_t m_length;
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

    argparse::ArgumentParser kidsCalcArgs("KidsCalc");
    kidsCalcArgs.add_argument("number_ops").help("Number of operators").scan<'i', size_t>();
    kidsCalcArgs.add_argument("lower_range").help("Min number used in calculation").scan<'i', int>();
    kidsCalcArgs.add_argument("upper_range").help("Max number used in calculation").scan<'i', int>();
    kidsCalcArgs.add_argument("-add").help("Addition questions").default_value(true).implicit_value(true);
    kidsCalcArgs.add_argument("-sub").help("Subtraction questions").default_value(false).implicit_value(true);
    kidsCalcArgs.add_argument("number_calcs").help("Number of questions").scan<'i', size_t>();

    try
    {
        kidsCalcArgs.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err)
    {
        std::cerr << err.what() << std::endl;
        std::cerr << kidsCalcArgs;
        std::exit(1);
    }

    size_t nbrOps = kidsCalcArgs.get<size_t>("number_ops");
    int lowerR = kidsCalcArgs.get<int>("lower_range");
    int upperR = kidsCalcArgs.get<int>("upper_range");
    size_t nbrQuestions = kidsCalcArgs.get<size_t>("number_calcs");

    std::shared_ptr<QuestionFactory> fact;

    if(kidsCalcArgs["-sub"] == true)
    {
        fact = std::shared_ptr<SubFactory>(new SubFactory());
    }
    else
    {
        fact = std::shared_ptr<SumFactory>(new SumFactory({lowerR, upperR}, nbrOps));
    }


    bool goToPlay = true;

    while(goToPlay)
    {
        std::shared_ptr<Play> p = std::shared_ptr<Play>(new Play(nbrQuestions, fact));

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
