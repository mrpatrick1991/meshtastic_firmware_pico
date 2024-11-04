#include "LoRaRegionModule.h"
#include <stdint.h>

LoRaRegionModule::LoRaRegionModule() 
    : MeshModule("LoRaRegionModule"), OSThread("LoRaRegionThread", 60*1000l) {
}

int32_t LoRaRegionModule::runOnce() {
#ifdef DEBUG_PORT
    LOG_INFO("LoRaRegionModule running.");
#endif
    updateRegionFromGPS();
    return 0;
}

void LoRaRegionModule::updateRegionFromGPS() {

    if (!gpsStatus->getIsConnected()) {
        LOG_INFO("LoRaRegionModule: GPS is not connected, doing nothing.\n");
        return;
    }

    if (!gpsStatus->getHasLock()) {
        LOG_INFO("LoRaRegionModule: GPS has no lock, doing nothing.\n");
        return;
    }

    /*meshtastic_Config_LoRaConfig_RegionCode current_gps_region_code = Lorawan_Geofence_position(gpsStatus->getLatitude()*1e-7, gpsStatus->getLongitude()*1e-7);

    if (current_gps_region_code != config.lora.region){
        LOG_INFO("LoRaRegionModule: GPS has a lock and is connected, setting corresponding LoRa region.\n");
        service->reloadConfig(SEGMENT_CONFIG);
    }

    else {
        LOG_INFO("LoRaRegionModule: LoRa region matches GPS location, doing nothing.\n");
    }*/
}

// Implement the required `wantPacket` function
bool LoRaRegionModule::wantPacket(const meshtastic_MeshPacket* p) {
    // we don't want to handle any packets
    return false;
}

