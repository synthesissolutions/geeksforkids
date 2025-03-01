import board
import displayio
import terminalio
import rotaryio
import digitalio
import math
import keypad

from adafruit_display_text import label
from adafruit_bitmap_font import bitmap_font
from adafruit_display_shapes.rect import Rect

speed = 50
volume = 50

def hide_all_headings():
    i = 0
    while i < len(menu_options):
        menu_options[i]["heading_group"].hidden = True
        i += 1

def hide_all_submenus():
    i = 0
    while i < len(menu_options):
        menu_options[i]["submenu_group"].hidden = True
        i += 1

def draw_main_menu(selected_option):
    # Place selected item
    menu_options[selected_option]["menu_item"].anchored_position = (0, 0)
    menu_options[selected_option]["menu_item"].color = menu_item_selected_color
    menu_options[selected_option]["menu_item"].font = selected_item_font

    # Place items above the selected item
    if selected_option != 0:
        j = selected_option - 1
        while j >= 0:
            menu_options[j]["menu_item"].anchored_position = (0, 0 - math.floor(menu_item_vertical_spacing * 1.2) - (selected_option - j - 1)*menu_item_vertical_spacing)
            menu_options[j]["menu_item"].color = menu_item_color
            menu_options[j]["menu_item"].font = standard_font
            j -= 1
            
    # Place items below the selected item
    if selected_option != len(menu_options):
        j = selected_option + 1
        while j < len(menu_options):
            menu_options[j]["menu_item"].anchored_position = (0, 0 + math.floor(menu_item_vertical_spacing * 1.2) + (j - selected_option - 1)*menu_item_vertical_spacing)
            menu_options[j]["menu_item"].color = menu_item_color
            menu_options[j]["menu_item"].font = standard_font
            j += 1

    display.refresh()

def draw_secondary_menu(primary_menu, selected_secondary_option):
    submenu_items = primary_menu["submenu"]

    # Place selected item
    submenu_items[selected_secondary_option]["submenu_item"].anchored_position = (0, 0)
    submenu_items[selected_secondary_option]["submenu_item"].color = menu_item_selected_color
    submenu_items[selected_secondary_option]["submenu_item"].font = selected_item_font

    # Place items above the selected item
    if selected_secondary_option != 0:
        j = selected_secondary_option - 1
        while j >= 0:
            submenu_items[j]["submenu_item"].anchored_position = (0, 0 - math.floor(menu_item_vertical_spacing * 1.2) - (selected_secondary_option - j - 1)*menu_item_vertical_spacing)
            submenu_items[j]["submenu_item"].color = menu_item_color
            submenu_items[j]["submenu_item"].font = standard_font
            j -= 1
            
    # Place items below the selected item
    if selected_secondary_option != len(submenu_items):
        j = selected_secondary_option + 1
        while j < len(submenu_items):
            submenu_items[j]["submenu_item"].anchored_position = (0, 0 + math.floor(menu_item_vertical_spacing * 1.2) + (j - selected_secondary_option - 1)*menu_item_vertical_spacing)
            submenu_items[j]["submenu_item"].color = menu_item_color
            submenu_items[j]["submenu_item"].font = standard_font
            j += 1

    display.refresh()


# Returns True if long press
# Returns False if short press
def number_control_loop(number_option):
    button_press_started = 0
    number_group.hidden = False
    current_value = number_option["value"]
    min = number_option["min"]
    max = number_option["max"]

    if current_value < min:
        current_value = min
    elif current_value > max:
        current_value = max

    number_value.text = str(current_value)
    encoder.position = current_value

    display.refresh()

    while True:
        event = buttons.events.get()

        if encoder.position != current_value:
            if encoder.position < min:
                encoder.position = min
            elif encoder.position > max:
                encoder.position = max

            current_value = encoder.position
            number_value.text = str(current_value)
            number_option["value"] = current_value

            display.refresh()

        if event:
            if event.pressed:
                if button_press_started == 0:
                    button_press_started = event.timestamp
            if event.released:
                number_group.hidden = True
                return button_press_started > 0 and event.timestamp - button_press_started > 3000

# Returns True if long press
# Returns False if short press
def speed_control_loop():
    speed_group.hidden = False

    return_value = number_control_loop(speed_option)
    speed_group.hidden = True

    return return_value

# Returns True if long press
# Returns False if short press
def volume_control_loop():
    volume_group.hidden = False

    return_value = number_control_loop(volume_option)
    volume_group.hidden = True

    return return_value

def main_menu_loop():
    current_menu_option = 0
    encoder.position = 0
    top_level_menu_options_group.hidden = False
    draw_main_menu(current_menu_option)

    while True:
        event = buttons.events.get()

        if event and event.released:
            current_menu_option = encoder.position
            top_level_menu_options_group.hidden = True

            secondary_menu_loop(menu_options[current_menu_option])
            # Once we return from the secondary menu, need to repaint primary menu
            top_level_menu_options_group.hidden = False
            encoder.position = current_menu_option
            draw_main_menu(current_menu_option)

        elif encoder.position != current_menu_option:
            if encoder.position < 0:
                encoder.position = 0
                # make sure we didn't jump multiple positions
                if encoder.position != current_menu_option:
                    current_menu_option = 0
                    draw_main_menu(current_menu_option)
            elif encoder.position >= len(menu_options):
                encoder.position = len(menu_options) - 1
                # make sure we didn't jump multiple positions
                if encoder.position != current_menu_option:
                    current_menu_option = encoder.position
                    draw_main_menu(current_menu_option)
            else:
                # Adjust the selected menu item
                current_menu_option = encoder.position
                draw_main_menu(current_menu_option)


def secondary_menu_loop(current_primary_menu):
    current_menu_option = 0
    encoder.position = current_menu_option
    current_primary_menu["submenu_group"].hidden = False
    current_primary_menu["heading_group"].hidden = False

    draw_secondary_menu(current_primary_menu, current_menu_option)

    while True:
        event = buttons.events.get()

        if event and event.released:
            if encoder.position == 0:
                # Back option selected
                # Return to primary menu loop
                current_primary_menu["submenu_group"].hidden = True
                current_primary_menu["heading_group"].hidden = True
                return
            else:
                custom_settings_loop(current_primary_menu["submenu"][current_menu_option])
                # Returning from settings loop, need to repaint this menu
                draw_secondary_menu(current_primary_menu, current_menu_option)

        elif encoder.position != current_menu_option:
            if encoder.position < 0:
                encoder.position = 0
                # make sure we didn't jump multiple positions
                if encoder.position != current_menu_option:
                    current_menu_option = encoder.position
                    draw_secondary_menu(current_primary_menu, current_menu_option)
            elif encoder.position >= len(current_primary_menu["submenu"]):
                encoder.position = len(current_primary_menu["submenu"]) - 1
                # make sure we didn't jump multiple positions
                if encoder.position != current_menu_option:
                    current_menu_option = encoder.position
                    draw_secondary_menu(current_primary_menu, current_menu_option)
            else:
                # Adjust the selected menu item
                current_menu_option = encoder.position
                draw_secondary_menu(current_primary_menu, current_menu_option)


def custom_settings_loop(settings_item):
    print("custom setting")

display = board.DISPLAY
encoder = rotaryio.IncrementalEncoder(board.ENC_B, board.ENC_A)
buttons = keypad.Keys((board.KNOB_BUTTON,), value_when_pressed=False)
standard_font = bitmap_font.load_font("/fonts/Orbitron-Light-19.bdf")
selected_item_font = bitmap_font.load_font("/fonts/Orbitron-Light-23.bdf")

speed_option = { "name": "Speed", "id": 0, "type": "integer", "min": 0, "max": 100, "default": 50, "value": 50 }
volume_option = { "name": "Volume", "id": 0, "type": "integer", "min": 0, "max": 100, "default": 50, "value": 50 }

menu_options = [
    {
        "name": "Linear Actuator", 
        "submenu": [
            {"name": "<< Back"}, 
            {"name": "Min", "id": 1, "type": "integer", "min": -100, "max": 100},
            {"name": "Center", "id": 2, "type": "integer", "min": -100, "max": 100},
            {"name": "Max", "id": 3, "type": "integer", "min": -100, "max": 100}]
    }, 
    {
        "name": "Remote Control", 
        "submenu": [
            {"name": "<< Back"},
            {"name": "Use RC", "id": 4, "type": "boolean"},
            {"name": "Steering Min", "id": 5, "type": "integer", "min": 0, "max": 2000},
            {"name": "Steering Center", "id": 6, "type": "integer", "min": 0, "max": 2000},
            {"name": "Steering Max", "id": 7, "type": "integer", "min": 0, "max": 2000},
            {"name": "Throttle Min", "id": 8, "type": "integer", "min": 0, "max": 2000},
            {"name": "Throttle Center", "id": 9, "type": "integer", "min": 0, "max": 2000},
            {"name": "Throttle Max", "id": 10, "type": "integer", "min": 0, "max": 2000}]
    }, 
    {
        "name": "Analog/PWM",
        "submenu": [
            {"name": "<< Back"},
            {"name": "Steering PWM", "id": 11, "type": "boolean"},
            {"name": "Throttle PWM", "id": 12, "type": "boolean"}]
    }, 
    {
        "name": "Direction",
        "submenu": [
            {"name": "<< Back"},
            {"name": "Invert Steer", "id": 13, "type": "boolean"},
            {"name": "Invert Throttle", "id": 14, "type": "boolean"}]
    }, 
    {
        "name": "Steering",
        "submenu": [
            {"name": "<< Back"},
            {"name": "Min", "id": 15, "type": "integer", "min": 0, "max": 1024},
            {"name": "Center", "id": 16, "type": "integer", "min": 0, "max": 1024},
            {"name": "Max", "id": 17, "type": "integer", "min": 0, "max": 1024}]
    }, 
    {
        "name": "Throttle",
        "submenu": [
            {"name": "<< Back"},
            {"name": "Min", "id": 18, "type": "integer", "min": 0, "max": 1024},
            {"name": "Center", "id": 19, "type": "integer", "min": 0, "max": 1024},
            {"name": "Max", "id": 20, "type": "integer", "min": 0, "max": 1024}],
    }]

encoder.position = 0

menu_item_vertical_spacing = 28
menu_item_color = 0xCCCCCC
menu_item_selected_color = 0x00FF00
heading_color = 0xFFFFFF
heading_background_color = 0x00FF00

main = displayio.Group()
display.root_group = main

top_level_menu_options_group = displayio.Group(scale=1)
top_level_menu_options_group.x = 120
top_level_menu_options_group.y = 120
top_level_menu_options_group.hidden = True

main.append(top_level_menu_options_group)

display.auto_refresh = False

i = 0
while i < len(menu_options):
    heading_group = displayio.Group(scale=1)
    heading_group.x = 120
    heading_group.y = 40
    heading_group.hidden = True

    y_position = math.floor(menu_item_vertical_spacing / 2) + (menu_item_vertical_spacing * (i - 1)) 
    y_heading_position = 20
    menu_item = label.Label(standard_font, text=menu_options[i]["name"], color=menu_item_color, anchor_point=(0.5, 0.5), anchored_position=(0,y_position), scale=1)
    heading = label.Label(standard_font, text=menu_options[i]["name"], color=heading_color, anchor_point=(0.5, 0.5), anchored_position=(0,0), scale=1)
    heading_background = Rect(-120, -20, 240, 40, fill=heading_background_color)

    menu_options[i]["menu_item"] = menu_item
    menu_options[i]["heading_group"] = heading_group

    top_level_menu_options_group.append(menu_item)
    heading_group.append(heading_background)
    heading_group.append(heading)

    # Create submenu items
    j = 0
    submenu_group = displayio.Group(scale=1)
    submenu_group.x = 120
    submenu_group.y = 120
    submenu_group.hidden = True
    menu_options[i]["submenu_group"] = submenu_group
    main.append(submenu_group)
    while j < len(menu_options[i]["submenu"]):
        submenu_item = label.Label(standard_font, text=menu_options[i]["submenu"][j]["name"], color=menu_item_color, anchor_point=(0.5, 0.5), anchored_position=(0, 0))
        menu_options[i]["submenu"][j]["submenu_item"] = submenu_item
        submenu_group.append(submenu_item)

        j += 1

    # Add heading_group last so it is drawn above the submenus
    main.append(heading_group)

    i += 1

# Setup Speed
speed_group = displayio.Group(scale=1)
speed_group.x = 120
speed_group.y = 40
speed_group.hidden = True
speed_heading = label.Label(standard_font, text="Speed", color=heading_color, anchor_point=(0.5, 0.5), anchored_position=(0,0), scale=1)
speed_heading_background = Rect(-120, -20, 240, 40, fill=0x0000FF)

speed_group.append(speed_heading_background)
speed_group.append(speed_heading)
main.append(speed_group)

# Setup Volume
volume_group = displayio.Group(scale=1)
volume_group.x = 120
volume_group.y = 40
volume_group.hidden = True
volume_heading = label.Label(standard_font, text="Volume", color=heading_color, anchor_point=(0.5, 0.5), anchored_position=(0,0), scale=1)
volume_heading_background = Rect(-120, -20, 240, 40, fill=0xFF00FF)

volume_group.append(volume_heading_background)
volume_group.append(volume_heading)
main.append(volume_group)

number_group = displayio.Group(scale=1)
number_group.x = 120
number_group.y = 120
number_group.hidden = True
number_value = label.Label(selected_item_font, text="0", color=0xFFFF00, anchor_point=(0.5, 0.5), anchored_position=(0,0), scale=2)

number_group.append(number_value)
main.append(number_group)

boolean_group = displayio.Group(scale=1)
boolean_group.x = 120
boolean_group.y = 120
boolean_group.hidden = True
boolean_value = label.Label(selected_item_font, text="True", color=0xFFFF00, anchor_point=(0.5, 0.5), anchored_position=(0,0), scale=2)

boolean_group.append(boolean_value)
main.append(boolean_group)

while True:
    if speed_control_loop():
        main_menu_loop()

    if volume_control_loop():
        main_menu_loop()
