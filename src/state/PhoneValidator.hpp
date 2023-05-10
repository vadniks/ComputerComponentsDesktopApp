
#pragma once

#include <QValidator>
#include <QRegularExpression>

class PhoneValidator final : public QValidator {
public:
    State validate(QString& input, int&) const override {
        return QRegularExpression(u8"^[0-9]{0,12}$").match(input).hasMatch()
            ? State::Acceptable
            : State::Invalid;
    }
};
