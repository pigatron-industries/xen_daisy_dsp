#ifndef FrequencyBankInterface_h
#define FrequencyBankInterface_h

/**
 * Represents a bank of related frequencies
 */
class FrequencyBankInterface {
    public:
        virtual float getFrequency(int index) = 0;
};

#endif
