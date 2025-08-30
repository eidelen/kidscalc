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

#ifndef FACTORIES_H
#define FACTORIES_H

#include <vector>
#include "question.h"

/**
 * @brief Factory for calculation questions
 */
class QuestionFactory
{
public:

    QuestionFactory();

    /**
     * Creates questions. Question should be crated randomly.
     * @return Question
     */
    virtual std::shared_ptr<Question> createQuestion() = 0;

    /**
     * Is the numer of questions limited, and if yes the number of questions.
     * @return limited and number of questions
     */
    virtual std::pair<bool,size_t> getTotalNumberOfQuestions() const;
};

/**
 * @brief The SumFactory class is the factory for simple random addition questions.
 */
class SumFactory : public QuestionFactory
{
public:
    SumFactory(std::pair<int,int> numberRange, size_t length);

    ~SumFactory();

    std::shared_ptr<Question> createQuestion() override;

    std::pair<int,int> m_numberRange;
    size_t m_length;
};

/**
 * @brief The SubFactory class is the factory for simple random subtractiuon questions.
 */
class SubFactory : public QuestionFactory
{
public:
    SubFactory(std::pair<int,int> numberRange, size_t length);

    ~SubFactory();

    std::shared_ptr<Question> createQuestion() override;

    std::pair<int,int> m_numberRange;
    size_t m_length;
};

/**
 * @brief The MultiplyFactory class is the factory for simple random multiply questions.
 */
class MulFactory : public QuestionFactory
{
public:
    MulFactory(std::pair<int,int> numberRange, size_t length);

    ~MulFactory();

    std::shared_ptr<Question> createQuestion() override;

    std::pair<int,int> m_numberRange;
    size_t m_length;
};

/**
 * @brief The DivisionIntFactory class is the factory for simple random division questions.
 */
class DivFactory : public QuestionFactory
{
public:
    DivFactory(std::pair<int,int> numberRange);

    ~DivFactory();

    std::shared_ptr<Question> createQuestion() override;

    std::pair<int,int> m_numberRange;
};

/**
 * @brief The CSVFactory class reads a CSV file (question,answer).
 */
class CSVFactory: public QuestionFactory
{
public:
    CSVFactory(const std::string& filePath);

    ~CSVFactory();

    std::shared_ptr<Question> createQuestion() override;

    virtual std::pair<bool,size_t> getTotalNumberOfQuestions() const override;

    using QEntry = std::pair<std::string, std::string>;
    std::vector<QEntry> m_questions;
    size_t m_qIdx;
};



/**
 * @brief The VerFactory class is the factory for simple random Verliebte Zahl questions.
 */
class VerFactory : public QuestionFactory
{
public:
    VerFactory(int base);

    ~VerFactory();

    std::shared_ptr<Question> createQuestion() override;

    int m_base;
};

#endif // FACTORIES_H
