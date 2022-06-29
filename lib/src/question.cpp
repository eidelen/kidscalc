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

#include "question.h"

Question::Question(): m_answered(false), m_questionAsString(""), m_trueResultAsString("")
{
}

Question::~Question()
{

}

bool Question::isAnswered() const
{
    return m_answered;
}

std::string Question::toString() const
{
    return m_questionAsString;
}

std::string Question::getRightAnswer() const
{
    return m_trueResultAsString;
}


/*********************** SumQuestion *********************************/

SumQuestion::SumQuestion(std::pair<int, int> numberRange, size_t length)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(numberRange.first, numberRange.second);

    m_trueResult = 0;
    m_questionAsString = "";

    for(size_t i = 0; i < length; i++)
    {
        int nextOp = dist(gen);

        m_trueResult += nextOp;

        m_questionAsString = m_questionAsString + std::to_string(nextOp);

        if( i+1 < length )
        {
            m_questionAsString = m_questionAsString + " + ";
        }
    }

    m_trueResultAsString = std::to_string(m_trueResult);
}

void SumQuestion::parseAnswer(const std::string &answer)
{
    m_answered = true;
    m_givenResult = std::stoi(answer);
}

bool SumQuestion::isCorrect() const
{
    return (m_trueResult == m_givenResult);
}
