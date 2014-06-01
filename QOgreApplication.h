#ifndef MYQAPPLICATION_H
#define MYQAPPLICATION_H

#include "PreProcessor.h"

namespace QtOgre {

/**
 * @brief The MyQApplication class reimplements QApplication to catch all exceptions
 */
class QOgreApplication : public QApplication
{
public:
	inline QOgreApplication(int &argc, char **argv) :
		QApplication(argc, argv) {

	}

	// QCoreApplication interface
public:

	inline bool notify(QObject *obj, QEvent *event)
	{
		try {
			return QApplication::notify(obj, event);
		} catch(const std::exception &ex) {
			std::cerr << ex.what() << std::endl;
		}

		return false;
	}

};

}

#endif // MYQAPPLICATION_H
