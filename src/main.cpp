#include <MercuryBoot/bootloader.hpp>

int main(void) {
    Bootloader boot;

    if (boot.awaitEntryFrame(100))
        boot.execute();

    boot.resetHardware();

    return boot.jumpToApp();
}
