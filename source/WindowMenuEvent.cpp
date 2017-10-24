
#include "WindowMenuEvent.h"
#include "MainWindow.h"
#include "CommandRecorder.h"

/**
 * @brief WindowMenuEvent::WindowMenuEvent
 * @param macroString
 */
WindowMenuEvent::WindowMenuEvent(const QString &macroString) : QEvent(eventType), macroString_(macroString) {
}

/**
 * @brief WindowMenuEvent::WindowMenuEvent
 * @param macroString
 * @param arguments
 */
WindowMenuEvent::WindowMenuEvent(const QString &macroString, const QStringList &arguments) : QEvent(eventType), macroString_(macroString), arguments_(arguments)  {
}

/**
 * @brief WindowMenuEvent::argumentString
 * @return
 */
QString WindowMenuEvent::argumentString() const {
    QStringList args;

    std::transform(arguments_.begin(), arguments_.end(), std::back_inserter(args), [](const QString &arg) {
        return QLatin1Char('"') + CommandRecorder::escapeString(arg) + QLatin1Char('"');
    });

    return args.join(QLatin1String(","));
}

/**
 * @brief WindowMenuEvent::toString
 * @return
 */
QString WindowMenuEvent::toString() const {
    return QString(QLatin1String("%1(%2)")).arg(macroString_, argumentString());
}

/**
 * @brief WindowMenuEvent::actionString
 * @return
 */
QString WindowMenuEvent::actionString() const {
    return macroString_;
}

