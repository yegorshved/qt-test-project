QT += gui core widgets network

CONFIG += c++14

SOURCES += \
        controller.cpp \
        main.cpp \
        udp.cpp \
        worker.cpp

HEADERS += \
  controller.h \
  udp.h \
  worker.h

#QMAKE_CXXFLAGS += -fsanitize=address -fsanitize=leak -fsanitize=undefined -fno-omit-frame-pointer
#QMAKE_LFLAGS += -fsanitize=address -fsanitize=leak -fsanitize=undefined
#valgrind.target = run_with_valgrind
#valgrind.commands = valgrind --leak-check=full --track-origins=yes $$DESTDIR/$$TARGET
#QMAKE_EXTRA_TARGETS += valgrind

