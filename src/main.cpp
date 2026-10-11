#include <MercuryCAN/controller/receiver.hpp>
#include <MercuryCAN/controller/transmitter.hpp>

static Can::Controller::Receiver*   rx = nullptr;
static Can::Controller::Tranmitter* tx = nullptr;

void startBootloader(void) {
}

void jumpToApp(void) {
}

int main(void) {
    rx = new Can::Controller::Receiver();
    tx = new Can::Controller::Transmitter();

    volatile uint8_t magicWord = 0;

    Can::Model::Message rxEntryMsg(
        0x001,
        &magicWord 
    );
    
    if (rx->awaitMessage(rxEntryMsg, 100) && 0x80 == magicWord)
        startBootloader();
    else
        jumpToApp();
}
