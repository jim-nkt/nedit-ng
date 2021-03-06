
#include "nedit.h"
#include "Main.h"
#include "DialogAbout.h"

#include <QStringList>
#include <QApplication>
#include <QTranslator>

bool IsServer = false;

namespace {

/**
 * @brief messageHandler
 * @param type
 * @param context
 * @param msg
 */
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {

#if defined(NDEBUG)
    // filter out messages that come from Qt itself
    if(!context.file && context.line == 0 && !context.function) {
        return;
    }
#endif

    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", qPrintable(msg), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", qPrintable(msg), context.file, context.line, context.function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info: %s (%s:%u, %s)\n", qPrintable(msg), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", qPrintable(msg), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", qPrintable(msg), context.file, context.line, context.function);
        abort();
    }
}

}

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]) {

    // On linux (and perhaps other UNIX's), we should support -version even
    // when X11 is not running
#ifdef Q_OS_LINUX
    if (qEnvironmentVariableIsEmpty("DISPLAY")) {
		// Respond to -V or -version even if there is no display 
		for (int i = 1; i < argc && strcmp(argv[i], "--"); i++) {

            if (strcmp(argv[i], "-V") == 0 || strcmp(argv[i], "-version") == 0) {
                QString infoString = DialogAbout::createInfoString();
                printf("%s", qPrintable(infoString));
				exit(EXIT_SUCCESS);
			}
		}
		fputs("NEdit: Can't open display\n", stderr);
		exit(EXIT_FAILURE);
    }
#endif

    qInstallMessageHandler(messageHandler);

#if QT_VERSION >= QT_VERSION_CHECK(5, 6, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
#ifdef Q_OS_MACOS
    QCoreApplication::setAttribute(Qt::AA_DontShowIconsInMenus);
    QCoreApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);
#endif
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);


	QApplication app(argc, argv);
	QApplication::setWindowIcon(QIcon(QLatin1String(":/res/nedit.png")));

	QTranslator translator;
	// look up e.g. :/translations/nedit-ng_{lang}.qm
	if (translator.load(QLocale(), QLatin1String("nedit-ng"), QLatin1String("_"), QLatin1String(":/translations"))) {
		app.installTranslator(&translator);
	}

    Main main{app.arguments()};

	// Process events. 
    return app.exec();
}
