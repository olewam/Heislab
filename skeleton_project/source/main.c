#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "floor_operations.h"
#include "button_operations.h"

int main(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    int floor;
    HardwareMovement movement = HARDWARE_MOVEMENT_UP;

    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    hardware_command_movement(movement);

    while(1){
        stop_button_pushed(movement);

        if(hardware_read_floor_sensor(0)){
            movement = HARDWARE_MOVEMENT_UP;
            hardware_command_movement(movement);
        }
        if(hardware_read_floor_sensor(HARDWARE_NUMBER_OF_FLOORS - 1)){
            movement = HARDWARE_MOVEMENT_DOWN;
            hardware_command_movement(movement);
        }
  	set_current_floor_light(floor);

    floor = current_floor(floor);
    printf("%d\n", floor);

    }
}
