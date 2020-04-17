# NodeMCU-SmartPowerStrip-v2
NodeMCU sketch to control a power strip

### Startup
- Change pins and modify status_relay variable with same number of pins
```cpp
int relay[] = {0, 4, 5, 16};
bool status_relay[] = {false, false, false, false};
```

### Using

- To connect the device to the network visit: __[tzapu/WiFIManager](https://github.com/tzapu/WiFiManager)__
- To call API use a __POST__ request and use JSON for the data.
  - Example: 
  ```json
  {
    "action": "on",
    "pin": 2
  }
  ```

### Development
- [ ] Button to reset wifi

