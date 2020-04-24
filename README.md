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

- API:

  | Description | Method | Endpoint | Paramethers |
  | --- | --- | --- | --- |
  | To start the action described in the body | __POST__ | /ps | "*__action__*" and "*__pin__*" |
  | To receive the status of the relays | __GET__ | /ps/status | - |
  | To receive the number of the relays | __GET__ | /ps/get_relay_number | - |

- Supported actions:

    | Action | Description |
    | --- | --- |
    | on | Turn on relay |
    | off | Turn off relay |

- Examples (with 4 relays):
  
  - Request body for "*__/ps__*":
    ```json
        {
          "action": "YOUT_ACTION",
          "pin": YOUR_RELAY_NUMBER
        }
    ```

  - Response body for "*__/ps__*":
    ```json
        {
          "msg": "SOME_MESSAGE"
        }
    ```
  
  - Response body for "*__/ps/status__*":
    ```json
        {
          "relay_1": false,
          "relay_2": true,
          "relay_3": true,
          "relay_4": false
        }
    ```
    * ___true__ indicates that the relay is turned on, __false__ indicates that the relay is turned off_

  - Response body for "*__/ps/get_relay_number__*":
    ```json
        {
          "number": 4
        }
    ```

### Development

- [ ] Button to reset wifi

### Notes

It is possible to use any relay module (1, 2, ..., n) only by changing the pins, adding or removing them, and the whole system will adapt automatically