#ifndef SURPRISER_ACTION_HPP
#define SURPRISER_ACTION_HPP

class SurpriserAction {
public:
    SurpriserAction() = default;
    SurpriserAction(const SurpriserAction&) = delete;
    SurpriserAction& operator=(const SurpriserAction&) = delete;
    virtual ~SurpriserAction() = default;
    virtual void Go() const { };
};

#endif