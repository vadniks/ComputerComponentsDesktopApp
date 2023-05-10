
#pragma once

#include <QValidator>
#include <QRegularExpression>

class PhoneValidator final : public QValidator {
public:
    State validate(QString& input, int&) const override {
        QRegularExpression regExp(u8"^[\\+]?[(]?[0-9]{3}[)]?[-\\s\\.]?[0-9]{3}[-\\s\\.]?[0-9]{4,6}$");
        return regExp.match(input).hasMatch() ? State::Acceptable : State::Invalid;
    }
};
