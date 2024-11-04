#pragma once

#include "MeshModule.h"
#include "MeshService.h"
#include "concurrency/OSThread.h"
#include "GPS.h"

using namespace concurrency;

class LoRaRegionModule : public MeshModule, public OSThread {
public:
    LoRaRegionModule();

protected:
    virtual int32_t runOnce() override;
    virtual bool wantPacket(const meshtastic_MeshPacket* p) override; // Implement required pure virtual function
private:
    void updateRegionFromGPS();
};