#include "LoRaRegionModule.h"
#include <stdint.h>

LoRaRegionModule::LoRaRegionModule() 
    : MeshModule("LoRaRegionModule"), OSThread("LoRaRegionThread", 60 * 1000l) {
}

int32_t LoRaRegionModule::runOnce() {
#ifdef DEBUG_PORT
    LOG_INFO("LoRaRegionModule running.");
#endif
    updateRegionFromGPS();
    return 0;
}

bool LoRaRegionModule::updateRegionFromGPS() {
    if (!gpsStatus->getIsConnected()) {
        LOG_INFO("LoRaRegionModule: GPS is not connected, doing nothing.\n");
        return 1;
    }

    if (!gpsStatus->getHasLock()) {
        LOG_INFO("LoRaRegionModule: GPS has no lock, doing nothing.\n");
        return 1;
    }

    meshtastic_Config_LoRaConfig_RegionCode current_gps_region_code = 
        geofence_position(gpsStatus->getLatitude() * 1e-7, gpsStatus->getLongitude() * 1e-7);
    config.lora.region = current_gps_region_code;
    service->reloadConfig(SEGMENT_CONFIG);
    return 0;
}

// Implement the required `wantPacket` function
bool LoRaRegionModule::wantPacket(const meshtastic_MeshPacket* p) {
    // We don't want to handle any packets
    return false;
}

int32_t LoRaRegionModule::pointInPolygon(int32_t polyCorners, float* polygon, float latitude, float longitude) {
    int32_t i;
    int32_t j = polyCorners * 2 - 2;
    int32_t oddNodes = 0;

    for (i = 0; i < polyCorners * 2; i += 2) {
        if ((polygon[i + 1] < latitude && polygon[j + 1] >= latitude ||
             polygon[j + 1] < latitude && polygon[i + 1] >= latitude) &&
            (polygon[i] <= longitude || polygon[j] <= longitude)) {
            oddNodes ^= (polygon[i] + (latitude - polygon[i + 1]) /
                        (polygon[j + 1] - polygon[i + 1]) * (polygon[j] - polygon[i]) < longitude);
        }
        j = i;
    }
    return oddNodes;
}

meshtastic_Config_LoRaConfig_RegionCode LoRaRegionModule::geofence_position(float latitude, float longitude) {
    // Europe, Africa, Middle East and West Asia
    if (longitude > -33.0 && longitude < 87.0) {
        // Belarus and Ukraine
        if (pointInPolygon(8, GeofenceCoordinates::BelarusUkraineF, latitude, longitude) == 1) {
            return meshtastic_Config_LoRaConfig_RegionCode_EU_868;
        }
        // Israel
        else if (pointInPolygon(6, GeofenceCoordinates::IsraelF, latitude, longitude) == 1) {	
            return meshtastic_Config_LoRaConfig_RegionCode_ANZ; // Best guess based on the forum
        }
        // Kazakhstan
        else if (pointInPolygon(10, GeofenceCoordinates::KazakhstanF, latitude, longitude) == 1) {
            return meshtastic_Config_LoRaConfig_RegionCode_EU_868;
        }
        // Russia - RU864
        else if (longitude > 30.0 && latitude > 44.0) {
            return meshtastic_Config_LoRaConfig_RegionCode_RU;
        }
        // India - IN865
        else if (pointInPolygon(9, GeofenceCoordinates::IndiaF, latitude, longitude) == 1) {
            return meshtastic_Config_LoRaConfig_RegionCode_IN;
        }
        // Pakistan - IN865
        else if (pointInPolygon(8, GeofenceCoordinates::PakistanF, latitude, longitude) == 1) {
            return meshtastic_Config_LoRaConfig_RegionCode_IN;
        }
        // Rest of Europe and West Asia - EU868
        else {
            return meshtastic_Config_LoRaConfig_RegionCode_EU_868;
        }
    }
    // North & South America
    else if (longitude <= -33.0) {
        // United States, Canada and Mexico - US902
        if (latitude > 12.5) {
            return meshtastic_Config_LoRaConfig_RegionCode_US;
        }
        // Brazil
        else if (pointInPolygon(9, GeofenceCoordinates::BrazilF, latitude, longitude) == 1) {
            return meshtastic_Config_LoRaConfig_RegionCode_ANZ;
        }
        else {
            return meshtastic_Config_LoRaConfig_RegionCode_US;
        }
    }
    // Russia, China, Japan, South Korea, Australia
    else if (longitude >= 87.0) {
        // Russia - RU864
        if (latitude > 52.0) {
            return meshtastic_Config_LoRaConfig_RegionCode_RU;
        }
        else if (latitude > 22.2) {
            // Bangladesh
            if (pointInPolygon(7, GeofenceCoordinates::BangladeshF, latitude, longitude) == 1) {
                return meshtastic_Config_LoRaConfig_RegionCode_EU_868;
            }
            // North Korea
            else if (pointInPolygon(6, GeofenceCoordinates::North_KoreaF, latitude, longitude) == 1) {
                return meshtastic_Config_LoRaConfig_RegionCode_KR;
            }
            // South Korea
            else if (pointInPolygon(5, GeofenceCoordinates::South_KoreaF, latitude, longitude) == 1) {
                return meshtastic_Config_LoRaConfig_RegionCode_KR;
            }
            // Japan
            else if (pointInPolygon(7, GeofenceCoordinates::JapanF, latitude, longitude) == 1) {
                return meshtastic_Config_LoRaConfig_RegionCode_JP;
            }
            // Hong Kong
            else if ((longitude > 113.62 && longitude < 114.67) && (latitude > 21.6 && latitude < 22.5)) {
                return meshtastic_Config_LoRaConfig_RegionCode_CN;
            }
            else if (pointInPolygon(5, GeofenceCoordinates::ThailandF, latitude, longitude) == 1) {
                return meshtastic_Config_LoRaConfig_RegionCode_TH;
            }
            // South East China Sea
            else if ((longitude > 120.0 && longitude < 123.45) && (latitude > 21.4 && latitude < 25.8)) {
                return meshtastic_Config_LoRaConfig_RegionCode_ANZ;
            }
            // China (Not supported)
            else if (pointInPolygon(12, GeofenceCoordinates::ChinaF, latitude, longitude) == 1) {
                return meshtastic_Config_LoRaConfig_RegionCode_CN;
            }
            // Mongolia
            else if (pointInPolygon(10, GeofenceCoordinates::MongoliaF, latitude, longitude) == 1) {
                return meshtastic_Config_LoRaConfig_RegionCode_US;
            }
            else {
                return meshtastic_Config_LoRaConfig_RegionCode_ANZ;
            }
        }
        // Australia, New Zealand
        else {
            if (pointInPolygon(6, GeofenceCoordinates::AustraliaF, latitude, longitude) == 1) {
                return meshtastic_Config_LoRaConfig_RegionCode_ANZ;
            }
            else if (pointInPolygon(5, GeofenceCoordinates::New_ZealandF, latitude, longitude) == 1) {
                return meshtastic_Config_LoRaConfig_RegionCode_ANZ;
            }
            else if (pointInPolygon(5, GeofenceCoordinates::ThailandF, latitude, longitude) == 1) {
                return meshtastic_Config_LoRaConfig_RegionCode_ANZ;
            }
            else {
                return meshtastic_Config_LoRaConfig_RegionCode_ANZ;
            }
        }
    }
    // Default case if no match is found
    else {
        return meshtastic_Config_LoRaConfig_RegionCode_US;
    }
}
