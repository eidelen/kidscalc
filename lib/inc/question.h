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

    /**
     * Question ctor with given question and answer.
     * @param question
     * @param trueResult
     */
    Question(const std::string& question, const std::string& trueResult);

    Question();
    virtual ~Question();

    /**
     * Parse and store the given anser.
     * @param answer as string.
     */
    virtual void parseAnswer(const std::string& answer);

    /**
     * Was qustion solved correctly.
     */
    virtual bool isCorrect() const;

    /**
     * Was the question answered.
     */
    bool isAnswered() const;

    /**
     * Return string representation of question.
     * @return String
     */
    std::string getQuestion() const;

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
    std::string m_givenResultAsString;
};

class NumericQuestion : public Question
{
public:
    /**
     * Ctor for numeric question
     */
    NumericQuestion();

    virtual ~NumericQuestion();

    virtual void parseAnswer(const std::string &answer) override;
};


class SumQuestion : public NumericQuestion
{
public:
    /**
     * Ctor for random summation question
     * @param numberRange The range in which the used numbers are
     * @param length How many number are summed
     */
    SumQuestion(std::pair<int,int> numberRange, size_t length);

    virtual ~SumQuestion();
};

class SubQuestion : public NumericQuestion
{
public:
    /**
     * Ctor for random subtraction question
     * @param numberRange The range in which the used numbers are
     * @param length How many number are summed
     * @param canBeNegative If true, result can be signed. Otherwise result will be positive.
     */
    SubQuestion(std::pair<int,int> numberRange, size_t length, bool canBeNegative);

    virtual ~SubQuestion();
};

class MultiplyQuestion : public NumericQuestion
{
public:
    /**
     * Ctor for random multiply question
     * @param numberRange The range in which the used numbers are
     * @param length How many number are summed
     */
    MultiplyQuestion(std::pair<int,int> numberRange, size_t length);

    virtual ~MultiplyQuestion();
};

class DivisionQuestionInt : public NumericQuestion
{
public:
    /**
     * Ctor for random division question
     * @param numberRange The range in which the answer is.
     */
    DivisionQuestionInt(std::pair<int,int> numberRange);

    virtual ~DivisionQuestionInt();
};

#endif // QUESTION_H
