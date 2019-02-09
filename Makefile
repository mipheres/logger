all: app.cpp logger.h logger.cpp
	# g++ -o app -pthread app.cpp logger.h logger.cpp
	g++ -g -o app -pthread app.cpp  logger.cpp
