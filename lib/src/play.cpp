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


#include "play.h"


Play::Play(size_t nbrOfQuestions, std::shared_ptr<QuestionFactory> qFactory)
    : m_nbrOfQuestions(nbrOfQuestions), m_nbrOfQuestionsAlreadyAsked(0), m_qFactory(qFactory)
{

}

Play::~Play()
{

}

std::shared_ptr<Question> Play::nextQuestion()
{
    if(m_nbrOfQuestionsAlreadyAsked < m_nbrOfQuestions)
    {
        std::shared_ptr<Question> q = m_qFactory->createQuestion();
        m_questions.push_back(q);
        m_nbrOfQuestionsAlreadyAsked++;
        return q;
    }
    else
    {
        return std::shared_ptr<Question>(nullptr);
    }
}

std::tuple<size_t, size_t, size_t, size_t> Play::getStat() const
{
    size_t right = 0;
    size_t wrong = 0;
    size_t answered = 0;
    size_t unanswered = 0;

    for(const auto& q : m_questions)
    {
        q->isAnswered() ? answered++ : unanswered++;
        q->isCorrect() ? right++ : wrong++;
    }

    return {right, wrong, answered, unanswered};
}

