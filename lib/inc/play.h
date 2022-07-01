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

#ifndef PLAY_H
#define PLAY_H

#include <memory>
#include <vector>

#include "question.h"

/**
 * @brief Calculation play consisting of Questions.
 */
class Play
{

public:

    /**
     * Constructs a play
     * @param nbrOfQuestions Number of questions
     * @param qFactory Questions factory.
     */
    Play(size_t nbrOfQuestions, std::shared_ptr<QuestionFactory> qFactory);

    /**
     * Destructor
     */
    virtual ~Play();

    /**
     * Returns the next question.
     * @return Next question. When no one left, nullptr.
     */
    std::shared_ptr<Question> nextQuestion();

    /**
     * Get statistics of current play.
     * @return nbr right, nbr wrong, nbr answered, nbr unanswered, success rate
     */
    std::tuple<size_t, size_t, size_t, size_t, double> getStat() const;


protected:

    size_t m_nbrOfQuestions;
    size_t m_nbrOfQuestionsAlreadyAsked;
    std::shared_ptr<QuestionFactory> m_qFactory;
    std::vector<std::shared_ptr<Question>> m_questions;
};

#endif // PLAY_H
