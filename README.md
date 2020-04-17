# NodeMCU-SmartPowerStrip-v2
NodeMCU sketch to control a power strip

### Startup
- Change pins and modify status_relay variable with same number of pins
```cpp
int relay[] = {0, 4, 5, 16};
bool status_relay[] = {false, false, false, false};
```

### Development
- [ ] Button to reset wifi

## Using

- To connect the device to the network visit: __tzapu/WiFIManager (https://github.com/tzapu/WiFiManager)__
