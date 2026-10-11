#include <MercuryCAN/controller/receiver.hpp>

int (*jumpToApp)(void) = static_cast<int(*)(void)>(0x1000);

void startBootloader(void) {
}

int main(void) {
    volatile uint8_t magicWord = 0;

    Can::Model::Message rxEntryMsg(
        0x001,
        &magicWord 
    );

    Can::Controller::Receiver rx;
    
    if (rx.awaitMessage(rxEntryMsg, 100) && 0x80 == magicWord)
        startBootloader();
    else
        jumpToApp();
}
