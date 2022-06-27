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
#ifndef QUESTION_H
#define QUESTION_H

#include <string>


/**
 * @brief Calculation question interface.
 */
class Question
{

public:

    Question();
    virtual ~Question();

    /**
     * Return string representation of question.
     * @return String
     */
    virtual std::string toString() const = 0;

    /**
     * Parse and store the given anser.
     * @param answer as string.
     */
    virtual void parseAnswer(const std::string& answer) = 0;

    /**
     * Was qustion solved correctly.
     */
    virtual bool isCorrect() const = 0;

    /**
     * Was the question answered.
     */
    bool isAnswered() const;

protected:
    bool m_answered;
};


/**
 * @brief Factory for calculation questions
 */
class QuestionFactory
{
public:

    /**
     * Creates questions. Question should be crated randomly.
     * @return Question
     */
    virtual std::shared_ptr<Question> createQuestion() = 0;
};

#endif // QUESTION_H
