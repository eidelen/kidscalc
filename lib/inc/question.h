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
#include <memory>
#include <utility>
#include <vector>


/**
 * @brief Calculation question interface.
 */
class Question
{

public:

    Question();
    virtual ~Question();

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

    /**
     * Return string representation of question.
     * @return String
     */
    std::string toString() const;

    /**
     * Get the right answer as string.
     * @return Righ answer string.
     */
    virtual std::string getRightAnswer() const;

protected:
    int getRandomIntegerInRange(std::pair<int,int> numberRange) const;
    bool m_answered;
    std::string m_questionAsString;
    std::string m_trueResultAsString;
};


class SumQuestion : public Question
{
public:
    /**
     * Ctor for summation question
     * @param numberRange The range in which the used numbers are
     * @param length How many number are summed
     */
    SumQuestion(std::pair<int,int> numberRange, size_t length);

    virtual ~SumQuestion();

    // Question interface
    void parseAnswer(const std::string &answer) override;
    bool isCorrect() const override;

private:
    int m_trueResult;
    int m_givenResult;
};

class SubQuestion : public Question
{
public:
    /**
     * Ctor for subtraction question
     * @param numberRange The range in which the used numbers are
     * @param length How many number are summed
     * @param canBeNegative If true, result can be signed. Otherwise result will be positive.
     */
    SubQuestion(std::pair<int,int> numberRange, size_t length, bool canBeNegative);

    virtual ~SubQuestion();

    // Question interface
    void parseAnswer(const std::string &answer) override;
    bool isCorrect() const override;

private:
    int m_trueResult;
    int m_givenResult;
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
