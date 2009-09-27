
#include "tar.h"

int main(int argc, char* argv[])
{
    if (argc > 1) {
        TarStream t;
        QFile a(argv[1]);
        a.open(QIODevice::ReadOnly);
        t.open(QDir("e"), &a, TarStream::UntarMode);
    }
}
