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

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

#include "factories.h"

QuestionFactory::QuestionFactory()
{

}

std::pair<bool,size_t> QuestionFactory::getTotalNumberOfQuestions() const
{
    return {false, std::numeric_limits<size_t>::max()};
}

/***********************************************/

SumFactory::SumFactory(std::pair<int,int> numberRange, size_t length): QuestionFactory(),
    m_numberRange(numberRange), m_length(length)
{
}

SumFactory::~SumFactory()
{
}

std::shared_ptr<Question> SumFactory::createQuestion()
{
    return std::shared_ptr<Question>(new SumQuestion(m_numberRange, m_length) );
}


/***********************************************/

SubFactory::SubFactory(std::pair<int,int> numberRange, size_t length): QuestionFactory(),
    m_numberRange(numberRange), m_length(length)
{
}

SubFactory::~SubFactory()
{
}

std::shared_ptr<Question> SubFactory::createQuestion()
{
    return std::shared_ptr<Question>(new SubQuestion(m_numberRange, m_length, false) );
}


/***********************************************/


CSVFactory::CSVFactory(const std::string &filePath): m_qIdx(0)
{
    std::ifstream csvFile(filePath);

    std::string line;
    while (std::getline(csvFile, line))
    {
        size_t cPos = line.find(",");
        if(cPos != std::string::npos)
        {
            std::string q = line.substr(0, cPos);
            std::string a = line.substr(cPos + 1);
            m_questions.emplace_back(q, a);
        }
    }
}

CSVFactory::~CSVFactory()
{

}

std::shared_ptr<Question> CSVFactory::createQuestion()
{
    if(m_qIdx >= m_questions.size())
        return std::shared_ptr<Question>(nullptr);

    auto [question, answer] = m_questions.at(m_qIdx++);
    return std::shared_ptr<Question>(new Question(question, answer));
}

std::pair<bool,size_t> CSVFactory::getTotalNumberOfQuestions() const
{
    return {true, m_questions.size()};
}
