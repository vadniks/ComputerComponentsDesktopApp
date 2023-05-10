
#pragma once

#include <QValidator>
#include <QRegularExpression>

class PhoneValidator final : public QValidator {
public:
    State validate(QString& input, int&) const override {
        QRegularExpression regExp(u8"^[0-9]{0,12}$");
        return regExp.match(input).hasMatch() ? State::Acceptable : State::Invalid;
    }
};
