/****************************************************************************
** Copyright (c) 2022 Adrian Schneider
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

#include <random>
#include <iostream>
#include <algorithm>

#include "question.h"

Question::Question(const std::string &question, const std::string &trueResult) :
    m_answered(false), m_questionAsString(question), m_trueResultAsString(trueResult), m_givenResultAsString("")
{
}

Question::Question(): m_answered(false), m_questionAsString(""), m_trueResultAsString(""), m_givenResultAsString("")
{
}

Question::~Question()
{
}

void Question::parseAnswer(const std::string &answer)
{
    m_givenResultAsString = answer;
    m_answered = true;
}

bool Question::isCorrect() const
{
    return m_trueResultAsString.compare(m_givenResultAsString) == 0;
}

bool Question::isAnswered() const
{
    return m_answered;
}

std::string Question::getQuestion() const
{
    return m_questionAsString;
}

std::string Question::getRightAnswer() const
{
    return m_trueResultAsString;
}

int Question::getRandomIntegerInRange(std::pair<int, int> numberRange) const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(numberRange.first, numberRange.second);
    return dist(gen);
}


/*********************** SumQuestion *********************************/

SumQuestion::SumQuestion(std::pair<int, int> numberRange, size_t length)
{
    int trueResult = 0;
    m_questionAsString = "";

    for(size_t i = 0; i < length; i++)
    {
        int nextOp = getRandomIntegerInRange(numberRange);

        trueResult += nextOp;

        m_questionAsString = m_questionAsString + std::to_string(nextOp);

        if( i+1 < length )
        {
            m_questionAsString = m_questionAsString + " + ";
        }
    }

    m_trueResultAsString = std::to_string(trueResult);
}

SumQuestion::~SumQuestion()
{

}


/********************************************/

SubQuestion::SubQuestion(std::pair<int, int> numberRange, size_t length, bool canBeNegative)
{
    bool tryAnother = true;

    while(tryAnother)
    {
        int trueResult = 0;
        m_questionAsString = "";

        for(size_t i = 0; i < length; i++)
        {
            int nextOp = getRandomIntegerInRange(numberRange);

            if(i == 0)
            {
                // first is chosen positive
                trueResult = nextOp;
            }
            else
            {
                trueResult -= nextOp;
            }

            m_questionAsString = m_questionAsString + std::to_string(nextOp);

            if( i+1 < length )
            {
                m_questionAsString = m_questionAsString + " - ";
            }
        }

        m_trueResultAsString = std::to_string(trueResult);
        tryAnother = (!canBeNegative) && (trueResult < 0);
    }
}

SubQuestion::~SubQuestion()
{

}

/********************************************/

NumericQuestion::NumericQuestion()
{
}

NumericQuestion::~NumericQuestion()
{
}

void NumericQuestion::parseAnswer(const std::string &answer)
{
    m_answered = true;
    m_givenResultAsString = answer;

    // remove all non alphanumeric but not "-" and "+"
    m_givenResultAsString.erase(std::remove_if(m_givenResultAsString.begin(), m_givenResultAsString.end(),  []( auto const& c ) -> bool
    {
        return !(std::isalnum(c) || c == '+' || c == '-');
    } ), m_givenResultAsString.end());
}
