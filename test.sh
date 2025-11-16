#!/bin/bash
GREEN="\033[0;32m"
RED="\033[0;31m"
PURPLE="\033[0;35m"
YELLOW="\033[0;33m"
RESET="\033[0m" # No Color

run_command() 
{
    INPUT="$1"

    echo -e "${PURPLE}Input: ${NC}"
    echo -e "$INPUT"

    echo -e "${YELLOW}[Memory Leak Check]${NC}"
    valgrind -q --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --error-exitcode=123 ./cub3D "$INPUT"
    if [ $? -eq 123 ]; then
        echo -e "${RED}Memory Leak: KO${NC}"
    else
        echo -e "${GREEN}Memory Leak: OK${NC}"
    fi

    echo -e "${YELLOW}[FD Leak Check]${NC}"
    valgrind -q --track-fds=yes --error-exitcode=123 ./cub3D "$INPUT"
    if [ $? -eq 123 ]; then
        echo -e "${RED}FD Leak: KO${NC}"
    else
        echo -e "${GREEN}FD Leak: OK${NC}"
    fi

    echo -e "${GREEN}--------------------------------------------------------------------${NC}"
}

run_jason() {
    echo -e "\n\n${YELLOW} Wrong configuration ${NC}"
    echo -e "${YELLOW} =================== ${NC}\n\n"

    run_command "./maps/invalid/no_extension"
    run_command "./maps/invalid/wrong_extension.cubb"
    run_command "./maps/invalid/1_tabs_in_map_array_area.cub"
    run_command "./maps/invalid/2_tabs_in_map.cub"
    run_command "./maps/invalid/3_tabs_before_map_array.cub"
    run_command "./maps/invalid/4_tabs_info_element.cub"
    run_command "./maps/invalid/5_walled_hole_tabs.cub"
    run_command "./maps/invalid/elements_invalid.cub"
    run_command "./maps/invalid/elements_repeated.cub"
    run_command "./maps/invalid/empty.cub"
    run_command "./maps/invalid/extra_players.cub"
    run_command "./maps/invalid/gibberish_text.cub"
    run_command "./maps/invalid/map_middle.cub"
    run_command "./maps/invalid/map_top.cub"
    run_command "./maps/invalid/newline_between_2_maps.cub"
    run_command "./maps/invalid/nonbinary.cub"
    run_command "./maps/invalid/not_fully_walled.cub"
    run_command "./maps/invalid/read_permission_denied.cub"
    run_command "./maps/invalid/repititive_identifier.cub"
    run_command "./maps/invalid/ridicolous_rgb.cub"
    run_command "./maps/invalid/space_between_num_of_colours.cub"
    run_command "./maps/invalid/space_in_floodfill.cub"
    run_command "./maps/invalid/space_in_texture_path.cub"
    run_command "./maps/invalid/wrong_texture_path.cub"
    run_command "./maps/invalid/zero_player.cub"
    run_command "./maps/invalid/too_small_map.cub"

    
    echo -e "\n\n${YELLOW} Correct configuration ${NC}"
    echo -e "${YELLOW} ===================== ${NC}\n\n"

    run_command "./maps/valid/theme_direction/testing/north.cub"
    run_command "./maps/valid/theme_direction/testing/south.cub"
    run_command "./maps/valid/theme_direction/testing/east.cub"
    run_command "./maps/valid/theme_direction/testing/west.cub"
    run_command "./maps/valid/theme_direction/blue_wood/north.cub"
    run_command "./maps/valid/theme_direction/blue_wood/south.cub"
    run_command "./maps/valid/theme_direction/blue_wood/east.cub"
    run_command "./maps/valid/theme_direction/blue_wood/west.cub"
    run_command "./maps/valid/theme_direction/bricks/north.cub"
    run_command "./maps/valid/theme_direction/bricks/south.cub"
    run_command "./maps/valid/theme_direction/bricks/east.cub"
    run_command "./maps/valid/theme_direction/bricks/west.cub"
    run_command "./maps/valid/.cub"
    run_command "./maps/valid/diamond.cub"
    run_command "./maps/valid/leaked_map_no_player.cub"
    run_command "./maps/valid/many.extensions.txt.cub"
    run_command "./maps/valid/no_emptylines.cub"
    run_command "./maps/valid/plus_sign_colour.cub"
    run_command "./maps/valid/spaces_after_comma_colour.cub"
    run_command "./maps/valid/uncoordinated_elements.cub"
    run_command "./maps/valid/walled_hole_space.cub"
    run_command "./maps/valid/whitespaces.cub"
    run_command "./maps/valid/without_corner.cub"
}

run_jason