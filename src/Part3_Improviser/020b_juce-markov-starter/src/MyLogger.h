// MyLogger.h
#include <juce_core/juce_core.h>

class MyLogger : public juce::Logger
{
public:
    MyLogger(const juce::File &logFileToUse) : logFile(logFileToUse)
    {
        logFile.create();
    }

    void logMessage(const juce::String &message) override
    {
        auto timestamp = juce::Time::getCurrentTime().toString(true, true);
        logFile.appendText("[" + timestamp + "] " + message + "\n");
    }

private:
    juce::File logFile;
};